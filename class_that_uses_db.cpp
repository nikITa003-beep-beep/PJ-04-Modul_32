#include "class_that_uses_db.h"

ClassThatUsesDB::ClassThatUsesDB(std::unique_ptr<DBConnection> connection) : connection_(std::move(connection)) 
{
}

bool ClassThatUsesDB::openConnection() 
{
    if (is_connected_) 
    {
        return true; // Подключено
    }

    is_connected_ = connection_->open();
    return is_connected_;
}

bool ClassThatUsesDB::useConnection(const std::string& query) 
{
    if (!is_connected_) 
    {
        return false; // Нет подключения
    }

    return connection_->execQuery(query);
}

void ClassThatUsesDB::closeConnection() 
{
    if (is_connected_) 
    {
        connection_->close();
        is_connected_ = false;
    }
}