#pragma once

#include <vector>
#include <string>


std::vector<std::string> dns_lookup(const std::string &host_name, int ipv); //ipv: default=4
bool is_ipv6_address(const std::string &str);
bool is_ipv4_address(const std::string &str);
int socket_connect(const std::string &ip_address, int port);
void download(const std::string &url, const std::string &filename);
auto parsingURL(const std::string &url);
std::string header_value(const std::string &full_header, const std::string &header_name);
int64_t http_get(const std::string &request, const std::string &ip_address, int port, const std::string &fname);