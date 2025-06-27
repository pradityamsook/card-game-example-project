#pragma once

#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include <string>
#include <drogon/drogon.h>
#include <trantor/utils/Logger.h>

#include "models/User.h"
#include "plugins/Database.h"
#include "repositories/UserRepository.h"
#include "external/libbcrypt/include/bcrypt/BCrypt.hpp"

class UserService {
    public:
        virtual ~UserService() = default;

        std::string message(std::string message) {
            return message + " " + std::to_string(drogon::k202Accepted);
        }

        Json::Value getUser(std::string username) {
            try
            {
                LOG_INFO << "Service getUser " << "\n";

                User::UserType user = userRepository.getUser(username);

                Json::Value ret;
                ret["username"] = user.username;
                ret["password_hash"] = user.password;
                ret["email"] = user.email;
                return ret;
            }
            catch(drogon::orm::DrogonDbException& e)
            {
                LOG_ERROR << "message() -> Error getUser: " << e.base().what() << "\n";
                throw e;
            }
        }

        Json::Value createUser(UserProperties& userProperties) {
            try 
            {
                LOG_INFO << "Service getUser " << "\n";

                bool done = userRepository.createUser(userProperties);

                Json::Value ret;
                ret["username"] = userProperties.username;
                if (done) {
                    ret["register"] = "Registered Successful";
                    ret["status"] = "successful";
                    return ret;
                }
                ret["register"] = "Registered Unsuccessful";

                return ret;
            }
            catch(drogon::orm::DrogonDbException& e)
            {
                LOG_ERROR << "message() -> Error getUser: " << e.base().what() << "\n";
                throw e;
            }
        }

    private:
        static inline UserRepository userRepository;
};

#endif