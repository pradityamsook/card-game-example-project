#pragma once
#include <drogon/Middleware.h>

class AuthMiddlware : public drogon::HttpMiddleware {
    public:
        virtual void doFilter(
            const HttpRequestPtr &req, 
            const drogon::FilterCallback &fcb, 
            const drogon::FilterChainCallback &fccb
        ) override;
};