#pragma once
#include <drogon/HttpController.h>
// #include "../services/CardService.h"

class CardController : public drogon::HttpController<CardController>
{
    public:
        // CardController(std::shared_ptr<CardService> service) : service_(service) {}
        // virtual ~CardController() = default;

        METHOD_LIST_BEGIN
            ADD_METHOD_TO(CardController::uploadCard, "/upload-cards", drogon::Post);
            ADD_METHOD_TO(CardController::createCard, "/cards", drogon::Post);
            ADD_METHOD_TO(CardController::getUserCard, "/cards", drogon::Get);
            ADD_METHOD_TO(CardController::getCardById, "/cards/cardId={1}", drogon::Get);
            ADD_METHOD_TO(CardController::updateCard, "/cards/cardId={1}", drogon::Put);
            ADD_METHOD_TO(CardController::deleteCard, "/cards/cardId={1}", drogon::Delete);
        METHOD_LIST_END

        void createCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
        void getUserCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
        void getCardById(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id);
        void updateCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id);
        void deleteCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id);
        void uploadCard(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
        // void setCardService(std::shared_ptr<CardService> service) { service_ = service; }
        

    // private:
    //     std::shared_ptr<CardService> service_;
};