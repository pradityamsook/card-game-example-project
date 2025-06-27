#pragma once

#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>
#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <trantor/utils/Logger.h>

#include "models/User.h"
#include "plugins/Database.h"

class UserRepository {
    public:
        virtual ~UserRepository() = default;

        User::UserType getUser(std::string username) {
            try
            {
                auto client = database.getClient();
                auto result = client->execSqlSync(
                    "SELECT username, password_hash, email FROM users WHERE username = $1",
                    username
                );
                LOG_INFO << "row affected " << result.affectedRows() << "\n";

                User::UserType user;
                for (auto row : result) {
                    user.username = row["username"].as<std::string>();
                    user.password = row["password_hash"].as<std::string>();
                    user.email = row["email"].as<std::string>();
                }
                return user;
            }
            catch(drogon::orm::DrogonDbException& e)
            {
                LOG_ERROR << "message() -> Error getUser: " << e.base().what() << "\n";
                throw e;
            }  
        }

        bool createUser(UserProperties& userProperties) {
            try
            {
                auto client = database.getClient();
                auto result = client->execSqlSync(
                    "INSERT INTO users(username, password_hash, email) VALUES ($1, $2, $3) RETURNING id",
                    userProperties.username,
                    userProperties.password,
                    userProperties.email
                );

                LOG_INFO << "row affected " << result.affectedRows() << "\n";

                // if (result.affectedRows()) {
                //     return true;
                // }
                return false;
            }
            catch(drogon::orm::DrogonDbException& e)
            {
                LOG_ERROR << "message() -> Error getUser: " << e.base().what() << "\n";
                throw e;
            }
        }

    private:
        static inline Database database;
};

#endif