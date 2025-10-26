#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <string>

class DBConnection 
{
public:
    virtual ~DBConnection() = default;

    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool execQuery(const std::string& query) = 0;
};

#endif