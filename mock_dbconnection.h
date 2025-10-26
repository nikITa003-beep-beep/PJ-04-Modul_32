#ifndef MOCK_DBCONNECTION_H
#define MOCK_DBCONNECTION_H

#include "dbconnection.h"
#include <gmock/gmock.h>
#include <iostream>

class MockDBConnection : public DBConnection
{
public:
    MOCK_METHOD(bool, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(bool, execQuery, (const std::string& query), (override));
};

#endif