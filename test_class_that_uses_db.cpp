#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "class_that_uses_db.cpp"
#include "mock_dbconnection.h"

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

class ClassThatUsesDBTest : public ::testing::Test 
{
protected:
    void SetUp() override 
    {
        mock_connection_ = std::make_unique<NiceMock<MockDBConnection>>();
        mock_ptr_ = mock_connection_.get();
        db_user_ = std::make_unique<ClassThatUsesDB>(std::move(mock_connection_));
    }

    std::unique_ptr<MockDBConnection> mock_connection_;
    MockDBConnection* mock_ptr_;
    std::unique_ptr<ClassThatUsesDB> db_user_;
};

TEST_F(ClassThatUsesDBTest, OpenConnectionSuccess) // ���� ��������� �������� �����������
{
    EXPECT_CALL(*mock_ptr_, open()).WillOnce(Return(true));

    EXPECT_TRUE(db_user_->openConnection());
}

TEST_F(ClassThatUsesDBTest, OpenConnectionFailure) // ���� ���������� �������� �����������
{
    EXPECT_CALL(*mock_ptr_, open()).WillOnce(Return(false));

    EXPECT_FALSE(db_user_->openConnection());
}

TEST_F(ClassThatUsesDBTest, UseConnectionWhenOpenSuccess) // ���� ������������� ����������� ��� �������� ��������
{
    const std::string test_query = "SELECT * FROM users";

    EXPECT_CALL(*mock_ptr_, open()).WillOnce(Return(true));
    EXPECT_CALL(*mock_ptr_, execQuery(test_query)).WillOnce(Return(true));

    EXPECT_TRUE(db_user_->openConnection());

    EXPECT_TRUE(db_user_->useConnection(test_query)); //������������� ����������
}

TEST_F(ClassThatUsesDBTest, UseConnectionWithoutOpening) // ���� ����������� ��� ��������
{
    const std::string test_query = "SELECT * FROM users";

    EXPECT_CALL(*mock_ptr_, execQuery(_)).Times(0); // �� ����� ���� ���������� ���
    EXPECT_FALSE(db_user_->useConnection(test_query));
}

TEST_F(ClassThatUsesDBTest, CloseConnection) // ���� �������� �����������
{
    EXPECT_CALL(*mock_ptr_, open()).WillOnce(Return(true));
    EXPECT_CALL(*mock_ptr_, close()); // ������� ����� close

    EXPECT_TRUE(db_user_->openConnection()); // ������� � �������
    db_user_->closeConnection();
}

TEST_F(ClassThatUsesDBTest, ReopenConnection) //  ���� ���������� ��������
{
    EXPECT_CALL(*mock_ptr_, open())
        .WillOnce(Return(true))
        .WillOnce(Return(true));

    EXPECT_TRUE(db_user_->openConnection());
    EXPECT_TRUE(db_user_->openConnection()); // ������ ������� true, ������ ��� ��� ����������
}

TEST_F(ClassThatUsesDBTest, MultipleQueries) // // ���� ���������� ��������
{
    const std::string query1 = "SELECT * FROM table1";
    const std::string query2 = "INSERT INTO table2 VALUES (1)";

    EXPECT_CALL(*mock_ptr_, open()).WillOnce(Return(true));
    EXPECT_CALL(*mock_ptr_, execQuery(query1)).WillOnce(Return(true));
    EXPECT_CALL(*mock_ptr_, execQuery(query2)).WillOnce(Return(true));

    EXPECT_TRUE(db_user_->openConnection());
    EXPECT_TRUE(db_user_->useConnection(query1));
    EXPECT_TRUE(db_user_->useConnection(query2));
}

TEST_F(ClassThatUsesDBTest, QueryExecutionFailure) // ��������� ���������� �������
{
    const std::string test_query = "INVALID QUERY";

    EXPECT_CALL(*mock_ptr_, open()).WillOnce(Return(true));
    EXPECT_CALL(*mock_ptr_, execQuery(test_query)).WillOnce(Return(false));

    EXPECT_TRUE(db_user_->openConnection());
    EXPECT_FALSE(db_user_->useConnection(test_query));
}