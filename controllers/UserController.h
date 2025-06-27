#pragma once
#include "User.h"
#include <memory>
#include <coroutine>
#include <drogon/drogon.h>
#include <drogon/HttpController.h>
#include <drogon/utils/coroutine.h>
#include "services/UserService.h"

class UserController : public drogon::HttpController<UserController>
{
	public:
		virtual ~UserController() = default;
		METHOD_LIST_BEGIN
			ADD_METHOD_TO(UserController::check, "/check", drogon::Get);
			ADD_METHOD_TO(UserController::createUser, "/register", drogon::Post);
			ADD_METHOD_TO(UserController::login, "/token?userId={1}&password={2}", drogon::Post);
			ADD_METHOD_TO(UserController::getInfo, "/{1}/info?token={2}", drogon::Get);
			ADD_METHOD_TO(UserController::validateToken, "/validate_token", drogon::Post);
		METHOD_LIST_END

		void createUser(const drogon::HttpRequestPtr&, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
		void login(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, std::string &&userId, const std::string &password);
		void getInfo(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, std::string userId, const std::string &token) const;
		void check(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
		void validateToken(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);

	private:
		static inline Database database;
		static inline UserService userService;
};
