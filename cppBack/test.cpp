//"C:\Program Files\Google\Chrome\Application\chrome.exe" --disable-web-security --user-data-dir="C:\Chrome-dev-session"

#include <iostream>
#include "crow.h"
#include "crow/middlewares/cors.h"
using namespace std;

int main()
{
    // Use the CORS middleware
    crow::App<crow::CORSHandler> app;

    // Configure CORS policy globally
    auto& cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .origin("http://localhost:3000") // Allow requests from this origin
        .methods("POST"_method, "GET"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method) // Add OPTIONS method
        .headers("Content-Type", "Authorization");
    
    // Explicitly handle OPTIONS preflight requests for the /submit route
    CROW_ROUTE(app, "/submit")
        .methods("OPTIONS"_method)
        ([](crow::response& res){
            res.code = 204;
            res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
            res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
            res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
            res.end(); // End the response here
        });

    CROW_ROUTE(app, "/")([](){
        return "Hello from Crow!";
    });
    
    CROW_ROUTE(app, "/submit")
        .methods("POST"_method)
        ([](const crow::request &req)
         {
             crow::json::rvalue data = crow::json::load(req.body);

             if (!data)
             {
                 return crow::response(400, "Invalid JSON");
             }

             string username;
             if (data.has("name"))
             {
                 username = data["name"].s();
             }
             else
             {
                 return crow::response(400, "No name has been sent");
             }

             crow::json::wvalue response2;
             username = "hello " + username + " welcome to cpp server";
             response2["message"] = username;
             return crow::response(200, response2);
         });

    app.port(18080).run();
}
