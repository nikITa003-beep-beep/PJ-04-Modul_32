#include <iostream>
#include "class_that_uses_db.h"
#include "real_dbconnection.cpp"
#include <iostream>

int main() 
{
    auto real_connection = std::make_unique<RealDBConnection>("postgresql://localhost:. . . . .");
    ClassThatUsesDB db_user(std::move(real_connection));

    if (db_user.openConnection()) 
    {
        std::cout << "Connection opened successfully!" << std::endl;

        if (db_user.useConnection("SELECT * FROM users"))
        {
            std::cout << "Query executed successfully!" << std::endl;
        }

        db_user.closeConnection();
        std::cout << "Connection closed." << std::endl;
    }

    return 0;
}