#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <exception>

#include "getAPI.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

//----------------------------------------------------------------------
std::tuple<std::string, std::string, int> parsingURL(const std::string &url)
{
    int offset = 0;
    int port = 0;
    size_t pos1, pos2, pos3, pos4;
    string protocol, domain, path, query;

    if (url.compare(0, 8, "https://") == 0)
    {
        offset = 8;
        //port = 443;
        port = 80;
    }
    else if (url.compare(0, 7, "http://") == 0)
    {
        offset = 7;
        port = 80;
    }
    else
    {
        throw std::invalid_argument("Not correct URL = \"" + url + "\" \n");
    }
    std::cout << "port = " << port << std::endl;

    pos1 = url.find_first_of('/', offset + 1);
    path = pos1 == string::npos ? "" : url.substr(pos1);

    domain = string(url.begin() + offset, pos1 != string::npos ? url.begin() + pos1 : url.end());

    cout << "path = " << path << std::endl;
    cout << "domain = " << domain << std::endl;

    path = (pos2 = path.find("#")) != string::npos ? path.substr(0, pos2) : path;
    string url_port = (pos3 = domain.find(":")) != string::npos ? domain.substr(pos3 + 1) : "";
    domain = domain.substr(0, pos3 != string::npos ? pos3 : domain.length());
    protocol = offset > 0 ? url.substr(0, offset - 3) : "";
    query = (pos4 = path.find("?")) != string::npos ? path.substr(pos4 + 1) : "";
    path = pos4 != string::npos ? path.substr(0, pos4) : path;

    cout << "domain = " << domain << std::endl;

    if (query.length() > 0)
    {
        path.reserve(path.length() + 1 + query.length());
        path.append("?").append(query);
    }
    if (domain.length() == 0)
    {
        throw std::invalid_argument("I cannot find domain in URL = \"" + url + "\" \n");
    }

    return std::make_tuple(path, domain, port);
}

//----------------------------------------------------------------------
vector<string> dns_lookup(const string &host_name, int ipv) //ipv: default=4
{
    vector<string> output;

    struct addrinfo hints, *res, *p;
    int status, ai_family;
    char ip_address[INET6_ADDRSTRLEN];

    ai_family = ipv == 6 ? AF_INET6 : AF_INET;    //v4 vs v6?
    ai_family = ipv == 0 ? AF_UNSPEC : ai_family; // AF_UNSPEC (any), or chosen
    memset(&hints, 0, sizeof hints);
    hints.ai_family = ai_family;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(host_name.c_str(), NULL, &hints, &res)) != 0)
    {
        //cerr << "getaddrinfo: "<< gai_strerror(status) << endl;
        return output;
    }

    for (p = res; p != NULL; p = p->ai_next)
    {
        void *addr;
        if (p->ai_family == AF_INET)
        { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
        }
        else
        { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        // convert the IP to a string
        inet_ntop(p->ai_family, addr, ip_address, sizeof ip_address);
        output.push_back(ip_address);
    }

    freeaddrinfo(res); // free the linked list

    return output;
}
//----------------------------------------------------------------------
bool is_ipv6_address(const string &str)
{
    struct sockaddr_in6 sa;
    // int inet_pton(int af, const char *src, void *dst);
    //преобразует строку символов src в сетевой адрес (типа af), затем копирует полученную структуру с адресом в dst.
    return inet_pton(AF_INET6, str.c_str(), &(sa.sin6_addr)) != 0;
}
//----------------------------------------------------------------------
bool is_ipv4_address(const string &str)
{
    struct sockaddr_in sa;
    return inet_pton(AF_INET, str.c_str(), &(sa.sin_addr)) != 0;
}
//----------------------------------------------------------------------
int socket_connect(const string &ip_address, int port)
{
    int sd = 0;
    const int MAXSLEEP = 128;
    struct sockaddr_in sa;

    memset(&sa, '\0', sizeof(sa));

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip_address.c_str());
    sa.sin_port = htons(port);

    for (int numsec = 1; numsec <= MAXSLEEP; numsec <<= 1)
    {
        if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            throw std::runtime_error("Cannot creat socket for ip = " + ip_address + "\nerrno code = " + strerror(errno) + "\n");

        if (connect(sd, (struct sockaddr *)&sa, sizeof(sa)) == 0)
            return sd;

        close(sd);
        if (numsec <= MAXSLEEP / 2)
            sleep(numsec);
    }
    throw std::runtime_error("Cannot connect for ip = " + ip_address + "\nerrno code = " + strerror(errno) + "\n");
}
//----------------------------------------------------------------------
void download(const string &url)
{
    int ipv = 0;
    vector<string> ip_addresses;

    auto [path, domain, port] = parsingURL(url);

    std::string filename = creatFileName(path);

    if (!is_ipv6_address(domain))
    {
        if (is_ipv4_address(domain))
        {
            ip_addresses.push_back(domain);
        }
        else //if (!is_ipv4_address(domain))
        {
            ip_addresses = dns_lookup(domain, ipv = 4);
        }
    }

    if (ip_addresses.size() > 0)
    {
        stringstream request;
        request << "GET " << path << " HTTP/1.1\r\n";
        request << "Host: " << domain << "\r\n\r\n";

        std::cout << "path  = " << path << std::endl;
        std::cout << "host (domain)  = " << domain << std::endl
                  << std::endl;
        std::cout << "request  = " << request.str() << std::endl;

        for (int i = 0, r = 0, ix = ip_addresses.size(); i < ix && r == 0; i++)
        {
            r = http_get(request.str(), ip_addresses[i], port, filename);
        }
    }
}

//----------------------------------------------------------------------
string header_value(const string &full_header, const string &header_name)
{
    size_t pos = full_header.find(header_name);
    string r;
    if (pos != string::npos)
    {
        size_t begin = full_header.find_first_not_of(": ", pos + header_name.length());
        size_t until = full_header.find_first_of("\r\n\t ", begin + 1);
        if (begin != string::npos && until != string::npos)
        {
            r = full_header.substr(begin, until - begin);
        }
    }
    else
    {
        throw std::runtime_error("cannot patsing heder" + full_header + "\n");
    }
    return r;
}

//----------------------------------------------------------------------
int64_t http_get(const string &request, const string &ip_address, int port, const string &fname)
{
    stringstream header;
    char delim[] = "\r\n\r\n";
    //char buffer[16384];
    char buffer[1024];
    int64_t bytes_sofar = 0, bytes_expected = -1;
    int sd = 0, bytes_received = -1, state = 0;

    ofstream fd(fname.c_str());
    if (!fd.is_open())
        throw std::runtime_error("I cannit open file \"" + fname + "\"\n");

    sd = socket_connect(ip_address, port);

    send(sd, request.c_str(), request.length(), 0);
    while (bytes_sofar != bytes_expected && (bytes_received = recv(sd, buffer, sizeof(buffer), 0)) > 0)
    {
        if (state < static_cast<int>(sizeof(delim) - 1)) //read header
        {
            std::cout << "lolooolo \n";
            std::cout << "bytes_received = " << bytes_received << std::endl;
            int i = 0;
            for (; i < bytes_received && state < static_cast<int>(sizeof(delim) - 1); i++)
            {
                header << buffer[i];
                state = buffer[i] == delim[state] ? state + 1 : 0;
            }
            bytes_received = state == sizeof(delim) - 1 ? bytes_received - i : bytes_received;

            std::cout << "bytes_received = " << bytes_received << std::endl;
            std::cout << "header = " << header.str() << std::endl;
            if (!isAnswerOk(header.str()))
            {
                close(sd);
                fd.close();
                throw std::runtime_error("Not OK answer \n" + header.str() + "\n");
            }
        }
        if (bytes_expected == -1 && state == sizeof(delim) - 1) //parse header
        {
            std::cout << "lolooolo2 \n";
            try
            {
                stringstream(header_value(header.str(), "Content-Length")) >> bytes_expected;
            }
            catch (const std::runtime_error &ex)
            {
                bytes_expected = -2;
                std::cerr << ex.what() << std::endl;
            }
        }
        if (state == sizeof(delim) - 1) //read body
        {
            bytes_sofar += bytes_received;
            fd.write(buffer, bytes_received);
        }
    }
    close(sd);
    fd.close();
    return bytes_sofar;
}

//----------------------------------------------------------------------
std::string creatFileName(const std::string &path)
{
    auto n = path.rfind("/");

    if (n == std::string::npos || (n + 1 == path.size()))
    {
        return "index.html";
    }
    return std::string(path.substr(n + 1));
}

//----------------------------------------------------------------------
bool isAnswerOk(const std::string &answer)
{
    return (answer.find("HTTP/1.1 200 OK") == std::string::npos) ? false : true;
}