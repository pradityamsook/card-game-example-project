#include "CardController.h"
// #include "services/CardService.h"

void CardController::createCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback) {
    LOG_DEBUG << "Create card...";
    Json::Value ret;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void CardController::getUserCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback) {
    LOG_DEBUG << "Get user card...";
    Json::Value ret;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void CardController::getCardById(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id) {
    LOG_DEBUG << "Get card by ID: " << id;
    Json::Value ret;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void CardController::updateCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id) {
    LOG_DEBUG << "Update card with ID: " << id;
    Json::Value ret;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void CardController::deleteCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id) {
    LOG_DEBUG << "Delete card with ID: " << id;
    Json::Value ret;
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}


void CardController::uploadCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpRequestPtr &)>&& callback) {
    LOG_INFO << "Upload card: ";
    try
    {

        Json::Value ret;
        auto json = req->getJsonObject();
        drogon::MultiPartParser fileUpload;
        if (fileUpload.parse(req) != 0 || fileUpload.getFiles().size() != 1) {
            auto resp = drogon::HttpResponse::newHttpResponse();
            resp->setBody("Can upload only one file");
            resp->setStatusCode(drogon::k403Forbidden);
            callback(resp);
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}