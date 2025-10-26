#ifndef REAL_DBCONNECTION_H
#define REAL_DBCONNECTION_H

#include "dbconnection.h"
#include <string>
#include <iostream>

class RealDBConnection : public DBConnection
{
public:
    RealDBConnection(const std::string& connection_string);

    bool open() override;
    void close() override;
    bool execQuery(const std::string& query) override;

private:
    std::string connection_string_;
    bool is_open_ = false;
};

RealDBConnection::RealDBConnection(const std::string& connection_string)
    : connection_string_(connection_string)
{
}

bool RealDBConnection::open()  // подключение к БД
{
    std::cout << "Открытие соединения с: " << connection_string_ << std::endl;
    is_open_ = true;
    return true;
}

void RealDBConnection::close() // закрытие подключения
{
    std::cout << "Закрытие соединения" << std::endl;
    is_open_ = false;
}

bool RealDBConnection::execQuery(const std::string& query) 
{
    if (!is_open_) 
    {
        return false;
    }

    std::cout << "Исполнение запроса: " << query << std::endl;
    return true;
}

#endif