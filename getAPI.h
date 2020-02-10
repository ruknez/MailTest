#pragma once

#include <vector>
#include <string>
#include <tuple>

/*!
    \brief Делает тоже что и DNS сервер
   
    \param host_name - имя хоста
    \param ipv - версия IP адреса 
    \return вектор IP адресов
*/
std::vector<std::string> dns_lookup(const std::string &host_name, int ipv = 4);

/*!
    \brief Проверяет яляется ли адрес IPv6
   
    \param str - IP addr
    \return - если является true иначе false\
*/
bool is_ipv6_address(const std::string &str);

/*!
    \brief Проверяет яляется ли адрес IPv4
   
    \param str - IP addr
    \return - если является true иначе false
*/
bool is_ipv4_address(const std::string &str);

/*!
    \brief Создает сокет и делает коннект с ним

    Данная функция учитивает особенности сетевого подключения, например
    если сервер к которому производится попытка не может принять соединение из-за высокой
    нагрузки производится повторная попытка. В ОС FreeBSD и Mac OS X ес­ли пер­вая
    по­пыт­ка ус­та­но­вить со­еди­не­ние по­тер­пит не­уда­чу, реа­ли­за­ция со­ке­тов такова что
    но­ве BSD бу­дет про­дол­жать объ­яв­лять не­удач­ны­ми ус­пеш­ные по­пыт­ки со­еди­не­ния, 
    ес­ли ис­поль­зо­вать тот же са­мый де­ск­рип­тор со­ке­та с про­то­ко­лом TCP.

    \param ip_address - IP адрес
    \param port  - порт
    \return сокет с установленным подключением
*/
int socket_connect(const std::string &ip_address, int port);

/*!
    \brief Основная функция в которой происходит парсин входящего URL и формирование GET запроса

    \param url - URL переданные в качестве аргумента программе
*/
void download(const std::string &url);

/*!
    \brief Производит парсин URL

    \param url - URL
    \return относительный пусть на хосте, доменное имя,  порт обычно = 80
*/
std::tuple<std::string, std::string, int> parsingURL(const std::string &url);

/*!
    \brief  Парсит заголовок ответа

    \param full_header - Полный ответ от сервера
    \param header_name - ключевое слово в ответе сервера
    \return размер заголовка
*/
std::string header_value(const std::string &full_header, const std::string &header_name);

/*!
    \brief  Выполняет GET запрос и записывает ответ в файл

    \param request - Get запрос
    \param ip_address - адрес по которому производится запрос
    \param port - порт для соединения по TCP
    \param fname - имя файла в который пишутся данные
    \return размер записанных данных в файл
*/
int64_t http_get(const std::string &request, const std::string &ip_address, int port, const std::string &fname);

/*!
    \brief  Создает имя файла на основе части URL

    \param path - относительный пусть на хосте
    \return имя файла
*/
std::string creatFileName(const std::string &path);

/*!
    \brief  Порверяет вернулся ли ответ с кодом 200

    \param answer - ответ сервера
*/
bool isAnswerOk(const std::string &answer);