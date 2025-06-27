#pragma once
#include <string>
#include <chrono>

struct UserProperties {
    std::string username;
    std::string password;
    std::string email;
};

class User {

    public:
        struct UserType {
            std::string username;
            std::string password;
            std::string email;
        };
        const long id;
        std::string username;
        std::string password;
        std::chrono::system_clock::time_point created_at;
        std::chrono::system_clock::time_point update_at;

        static constexpr auto table_name = "users";
        static constexpr auto primary_key = "id";
};