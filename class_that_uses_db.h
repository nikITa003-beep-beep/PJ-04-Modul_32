#ifndef CLASS_THAT_USES_DB_H
#define CLASS_THAT_USES_DB_H

#include "dbconnection.h"
#include <memory>

class ClassThatUsesDB 
{
public:
    explicit ClassThatUsesDB(std::unique_ptr<DBConnection> connection);

    bool openConnection();
    bool useConnection(const std::string& query);
    void closeConnection();

private:
    std::unique_ptr<DBConnection> connection_;
    bool is_connected_ = false;
};

#endif