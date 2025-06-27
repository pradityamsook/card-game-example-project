#include "AuthMiddleware.h"
#include <jwt-cpp/jwt.h>

void AuthMiddleware::doFilter(
    const HttpRequestPtr &req,
    const drogon::FilterCallback &fcb,
    const drogon::FilterChainCallback &fccb
) {
    auto authHeader = req->getHeader("Authorization");
    if (authHeader.empty()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode:k401Unauthorized);
        resp->setBody("Missing authentication token");
        return;
    }

    try
    {
        /* code */
        auto token = authHeader.substr(7);
        auto decoded = jwt::decode(token);
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{"your-secret-key"});
        verifier.verify(decoded);

        auto claims = decoded.get_payload_claims();
        req->attributes()->insert("userId", claims["userId"].as_number().to_uint64());

        fccb();
    }
    catch(const std::exception& e)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(HttpStatusCode::k401Unauthorized);
        resp->setBody("Invalid or Expired Token");
        fcb(resp);
        std::cerr << e.what() << '\n';
    }
    
}