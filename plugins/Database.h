// Database.h
#pragma once
#include <drogon/orm/DbClient.h>

class Database {
public:
    static drogon::orm::DbClientPtr getClient() {
        static auto client = drogon::app().getDbClient("postgres");
        if(!client) {
            LOG_FATAL << "Failed to get database client!";
            exit(1);
        }
        return client;
    }
};