#include "SetController.h"
#include "plugins/Database.h"

// std::unique_ptr<Database> Database::getClient();
static inline Database database;

void SetController::createSet(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback) {
    auto client = database.getClient();
    auto result = client->execSqlSync(
        "SELECT username, password_hash, email FROM users"
    );
}