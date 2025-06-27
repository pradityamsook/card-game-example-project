#pragma once
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/DbClient.h>

class Card {
    public:
        const long id;
        long userId;
        std::string title;
        std::string description;
        std::string imagPath;
        std::chrono::system_clock::time_point createAt;
        std::chrono::system_clock::time_point updateAt;

        static constexpr auto tableName = "cards";
        static constexpr auto primaryKey = "id";
};