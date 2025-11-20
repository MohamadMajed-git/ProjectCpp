#include "routes.hpp"
#include "globals.hpp"
#include <string>
#include <mysql.h>
#include "database.hpp"
#include <iostream>
#include "Classes/SDLL.hpp"
using namespace std;




void setupRoutes(crow::SimpleApp& app) {
    
    CROW_ROUTE(app, "/")([]() { return "Server is Online!"; });

    CROW_ROUTE(app, "/api/signup")
        .methods("POST"_method, "OPTIONS"_method)
        ([](const crow::request &req){
            if (req.method == "OPTIONS"_method) return crow::response(200);

            crow::json::rvalue data = crow::json::load(req.body);
            if (!data) return crow::response(400, "Invalid JSON");
            string fName   = data.has("firstName")   ? data["firstName"].s()   : (string)"Unknown";
            string lName   = data.has("lastName")    ? data["lastName"].s()    : (string)"";
            string natID   = data.has("nationalID")  ? data["nationalID"].s()  : (string)"";
            string bDate   = data.has("birthdate")   ? data["birthdate"].s()   : (string)"";
            string email   = data.has("email")       ? data["email"].s()       : (string)"";
            string phone   = data.has("phone")       ? data["phone"].s()       : (string)"";
            string pass    = data.has("password")    ? data["password"].s()    : (string)"";
            string addr    = data.has("address")     ? data["address"].s()     : (string)"";
            string job     = data.has("job")         ? data["job"].s()         : (string)"";
            string accType = data.has("accountType") ? data["accountType"].s() : (string)"";

            userList.insertAtB(
                data.has("firstName") ? (string)data["firstName"].s() : string("Unknown"),
                data.has("lastName") ? (string)data["lastName"].s() : string(""),
                data.has("nationalID") ? (string)data["nationalID"].s() : string(""),
                data.has("birthdate") ? (string)data["birthdate"].s() : string(""),
                data.has("email") ? (string)data["email"].s() : string(""),
                data.has("phone") ? (string)data["phone"].s() : string(""),
                data.has("password") ? (string)data["password"].s() : string(""),
                data.has("address") ? (string)data["address"].s() : string(""),
                data.has("job") ? (string)data["job"].s() : string(""),
                data.has("accountType") ? (string)data["accountType"].s() : string("")
            );
            string query ="INSERT INTO users (fname, lname, nationalID, birthdate, email, phone, password, address, job, accountType) VALUES ('" 
                + fName + "', '"
                + lName + "', '"
                + natID + "', '"
                + bDate + "', '"
                + email + "', '"
                + phone + "', '"
                + pass + "', '"
                + addr + "', '"
                + job + "', '"
                + accType + "')";
                if(mysql_query(conn,query.c_str())==0){
            crow::json::wvalue response;
            response["status"] = "success";
            response["message"] = "User added!";
            return crow::response(200, response);
                }
                else{
                    string errorMsg = mysql_error(conn);
                    cout << "MySQL Query Error: " << errorMsg << endl;
                    crow::json::wvalue response;
                    response["status"] = "error";
                    response["message"] = "User not added!"+errorMsg;
                    return crow::response(400, response);
                }

        });



        
}