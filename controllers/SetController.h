#pragma once
#include <drogon/HttpController.h>
// #include "../services/CardService.h"

class SetController : public drogon::HttpController<SetController>
{
    public:
        virtual ~SetController() = default;

        METHOD_LIST_BEGIN
            // ADD_METHOD_TO(CardController::createSet, "/cards", drogon::Post);
            // ADD_METHOD_TO(CardController::getUserCard, "/cards", drogon::Get);
            // ADD_METHOD_TO(CardController::getCardById, "/cards/cardId={1}", drogon::Get);
            // ADD_METHOD_TO(CardController::updateCard, "/cards/cardId={1}", drogon::Put);
            // ADD_METHOD_TO(CardController::deleteCard, "/cards/cardId={1}", drogon::Delete);
        METHOD_LIST_END

        void createSet(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
        // void getUserSet(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback);
        // void getCardById(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id);
        // void updateSet(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id);
        // void deleteSet(const drogon::HttpRequestPtr &req, std::function<void (const drogon::HttpResponsePtr &)>&& callback, const long id);
        
    private:
        // std::shared_ptr<CardService> service_;
};