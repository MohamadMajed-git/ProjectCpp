#include <iostream>
#include "crow.h"
#include <string>
#include "Classes/SDLL.hpp"
#include <mysql.h>
using namespace std;

SLL userList; 
MYSQL* conn;

int main()
{
    conn = mysql_init(0);
    const char* ca_path = "ca.pem"; 
    mysql_options(conn, MYSQL_OPT_SSL_CA, ca_path);
    if(conn ==nullptr){
        cout<<"MySQL Initialization Failed"<<endl;
        return 1;
    }
    const char* hostsname=getenv("DB_HOST") ? getenv("DB_HOST") : "db-avnbank-do-user-13724540-0.b.db.ondigitalocean.com";
    const char* user=getenv("DB_USER") ? getenv("DB_USER") : "doadmin";
    const char* pass=std::getenv("DB_PASS") ? std::getenv("DB_PASS") : "";
    const char* dbname="bank-system";
    unsigned int port=25739;
    if(mysql_real_connect(conn,hostsname,user,pass,dbname,port,NULL,0)){
        cout<<"Connected to database successfully"<<endl;
    }
    else{
        cout<<"Connection to database failed"<<endl;
        cout << "Error Details: " << mysql_error(conn) << endl;
        return 1;
    }










    crow::SimpleApp app; 

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


    cout << ">> [START] Server listening on port 10000..." << endl;
    
    app.bindaddr("0.0.0.0").port(10000).multithreaded().run();
    mysql_close(conn);
    return 0;
}