#include "UserController.h"
#include "plugins/Database.h"
#include "../services/UserService.h"
#include "external/libbcrypt/include/bcrypt/BCrypt.hpp"

#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <trantor/utils/Logger.h>

void UserController::check(const drogon::HttpRequestPtr&, 
    std::function<void (const drogon::HttpResponsePtr &)>&& callback) {
    auto resp = drogon::HttpResponse::newHttpResponse();
    std::string msg = userService.message("Try this status code");
    LOG_INFO << msg;
    resp->setStatusCode(drogon::k200OK);
    resp->setBody("Goods");
    callback(resp);
}

void UserController::createUser(const drogon::HttpRequestPtr &req,
    std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
    try {
        // auto client = database.getClient();

        Json::Value ret;
        auto json = req->getJsonObject();
        UserProperties userProperties;
        
        std::string password = BCrypt::generateHash((*json)["password"].asString()); 
        // ret["password"] = password;
        // ret["username"] = (*json)["username"].asString();
        // ret["email"] = (*json)["email"].asString();

        userProperties.username = (*json)["username"].asString();
        userProperties.email = (*json)["email"].asString();
        userProperties.password = password;

        auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
        Json::Value result = userService.createUser(userProperties);

        // auto result = client->execSqlSync(
        //     "INSERT INTO users(username, password_hash, email) VALUES ($1, $2, $3) RETURNING id",
        //     (*json)["username"].asString(),
        //     password,
        //     (*json)["email"].asString()
        // );
        LOG_INFO << result["status"].asString() << "\n";
    
        callback(resp);
        return;
    } catch (drogon::orm::DrogonDbException &e) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k500InternalServerError);
        callback(resp);
        throw e;
    }
}

void UserController::login(const drogon::HttpRequestPtr &req,
                 std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                 std::string &&userId,
                 const std::string &password)
{
    LOG_INFO << "Controller login -> user: " << userId << "\n";
    try
    {
        Json::Value ret;
        User::UserType user{userId, password, ""};
        Json::Value userJson = userService.getUser(user.username);
        Json::StreamWriterBuilder builderJson;
        builderJson["indentation"] = "";
        const std::string outputJson = Json::writeString(builderJson, userJson);
        LOG_INFO << "UserController::login -> get user: " << outputJson << "\n";
        bool validateUserPass = BCrypt::validatePassword(password, userJson["password_hash"].asString());

        if (validateUserPass) {
            ret["result"] = "ok";
            ret["token"] = drogon::utils::getUuid();
            auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
            callback(resp);
        }

        ret["message"] = "Failed login";
        auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(drogon::k401Unauthorized);
        callback(resp);
    }
    catch(drogon::orm::DrogonDbException& e)
    {
        LOG_ERROR << "Error login " << e.base().what() << "\n";
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k500InternalServerError);
        callback(resp);
        throw e;
    }
}

void UserController::getInfo(const drogon::HttpRequestPtr &req,
                   std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                   std::string userId,
                   const std::string &token) const
{
    LOG_DEBUG << "Controller getInfo: " << userId << "\n";

    Json::Value ret;
    ret["result"] = "ok";
    ret["user_name"] = "I'm Drogon";
    ret["user_id"] = userId;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
    return;
}

void UserController::validateToken(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) 
{
    Json::Value ret;
    auto json = req->getJsonObject();
    ret["validate"] = BCrypt::validatePassword((*json)["password"].asString(), (*json)["hash"].asString());
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
    return;
}