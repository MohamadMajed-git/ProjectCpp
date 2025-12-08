#include "routes.hpp"
#include "globals.hpp"
#include <string>
#include <mysql.h>
#include "database.hpp"
#include <iostream>
#include "Classes/SDLL.hpp"
using namespace std;
using namespace crow;

void setupRoutes(crow::SimpleApp &app)
{

    CROW_ROUTE(app, "/")([]()
                         { return "Server is Online!"; });
    CROW_ROUTE(app, "/signup")([]()
                               { return "Signup route"; });

    CROW_ROUTE(app, "/api/signup")
        .methods("POST"_method, "OPTIONS"_method)([](const request &req)
                                                  {
                                                      if (req.method == "OPTIONS"_method)
                                                          return crow::response(200);

                                                      json::rvalue data = json::load(req.body);
                                                      if (!data)
                                                          return crow::response(400, "Invalid JSON");
                                                      string fName = data.has("firstName") ? data["firstName"].s() : (string) "Unknown";
                                                      string lName = data.has("lastName") ? data["lastName"].s() : (string) "";
                                                      string natID = data.has("nationalID") ? data["nationalID"].s() : (string) "";
                                                      string bDate = data.has("birthdate") ? data["birthdate"].s() : (string) "";
                                                      string email = data.has("email") ? data["email"].s() : (string) "";
                                                      string phone = data.has("phone") ? data["phone"].s() : (string) "";
                                                      string pass = data.has("password") ? data["password"].s() : (string) "";
                                                      string addr = data.has("address") ? data["address"].s() : (string) "";
                                                      string job = data.has("job") ? data["job"].s() : (string) "";
                                                      string accType = data.has("accountType") ? data["accountType"].s() : (string) "";
                                                      string createAt=currentDate();
                                                      int balance=0;
                                                      string query = "INSERT INTO users (fname, lname, nationalID, birthdate, email, phone, password, address, job, accountType, createAt) VALUES ('" + fName + "', '" + lName + "', '" + natID + "', '" + bDate + "', '" + email + "', '" + phone + "', '" + pass + "', '" + addr + "', '" + job + "', '" + accType + "', '" + createAt + "')";
                                                      if (mysql_query(conn, query.c_str()) == 0)
                                                      {
                                                          string token = userList.insertAtB(
                                                              data.has("firstName") ? (string)data["firstName"].s() : string("Unknown"),
                                                              data.has("lastName") ? (string)data["lastName"].s() : string(""),
                                                              data.has("nationalID") ? (string)data["nationalID"].s() : string(""),
                                                              data.has("birthdate") ? (string)data["birthdate"].s() : string(""),
                                                              data.has("email") ? (string)data["email"].s() : string(""),
                                                              data.has("phone") ? (string)data["phone"].s() : string(""),
                                                              data.has("password") ? (string)data["password"].s() : string(""),
                                                              data.has("address") ? (string)data["address"].s() : string(""),
                                                              data.has("job") ? (string)data["job"].s() : string(""),
                                                              data.has("accountType") ? (string)data["accountType"].s() : string(""),
                                                              createAt,
                                                              balance
                                                            );
                                                            string tokenQuery="UPDATE users SET token = '" + token + "' WHERE email = '" + email + "'";
                                                            if(mysql_query(conn,tokenQuery.c_str())==0){
                                                                activateAccounts.addAccount(fName+" "+lName, email, createAt);
                                                           
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
                                                            response["message"] = "User not added!" + errorMsg;
                                                            return crow::response(400, response);
                                                        }

                                                      }
                                                      else
                                                      {
                                                          string errorMsg = mysql_error(conn);
                                                          cout << "MySQL Query Error: " << errorMsg << endl;
                                                          crow::json::wvalue response;
                                                          response["status"] = "error";
                                                          response["message"] = "User not added!" + errorMsg;
                                                          return crow::response(400, response);
                                                      } });

    CROW_ROUTE(app, "/api/login")
        .methods("POST"_method, "OPTIONS"_method)([](const request &req)
                                                  {
        if (req.method == "OPTIONS"_method) return crow::response(200);
       
        json::rvalue data =json::load(req.body);
        if(!data)return response(400,"Invalid JSON");

        string* userData=userList.validateLogin(
            data.has("email")?(string)data["email"].s():(string)"",
            data.has("password")?(string)data["password"].s():(string)""
        );

        if(userData !=nullptr){
                    string tokenQuery="UPDATE users SET token = '" + userData[10] + "' WHERE email = '" + (data.has("email")?(string)data["email"].s():(string)"")+"'";
                    if(mysql_query(conn,tokenQuery.c_str())==0){

                        json::wvalue response;
                        response["status"]="success";
                        response["message"]="Login successful";
                        response["user"]={
                            {"firstName",userData[0]},
                            {"lastName",userData[1]},
                            {"nationalID",userData[2]},
                            {"birthdate",userData[3]},
                            {"email",userData[4]},
                            {"phone",userData[5]},
                            {"password",userData[6]},
                            {"address",userData[7]},
                            {"job",userData[8]},
                            {"accountType",userData[9]}
                        };
                        response["token"] = userData[10];
                        delete[] userData;
                        return crow::response(200,response);
                         }
                        else{
                            string errorMsg = mysql_error(conn);
                            cout << "MySQL Query Error: " << errorMsg << endl;
                            crow::json::wvalue response;
                            response["status"] = "error";
                            response["message"] = "somthing went wrong" + errorMsg;
                            delete[] userData;
                            return crow::response(400, response);
                        }
        }
        else{
            json::wvalue response;
            response["status"]="error";
            response["message"]="Invalid email or password";
            return crow::response(401,response);
        } });





    CROW_ROUTE(app, "/api/holded-accounts")
        .methods("GET"_method, "OPTIONS"_method)([](const request &req)
                                                {
        if (req.method == "OPTIONS"_method) return crow::response(200);
        json::wvalue response;
        response["accounts"] = activateAccounts.getAccountsJSON();
        return crow::response(200, response);
                                                   
    });


    CROW_ROUTE(app, "/api/holded-accounts/activate")
    .methods("POST"_method, "OPTIONS"_method)([](const request &req)
    {
        if (req.method == "OPTIONS"_method) return crow::response(200);
        string email = activateAccounts.getFront();
        activateAccounts.removeAccount();
        userList.getNodeByEmail(email)->status = "active";
        string query = "UPDATE users SET status = 'active' WHERE email = '" + email + "'";
        if(mysql_query(conn, query.c_str()) != 0)
        {
            string errorMsg = mysql_error(conn);
            cout << "MySQL Query Error: " << errorMsg << endl;
            crow::json::wvalue response;
            response["status"] = "error";
            response["message"] = "somthing went wrong" + errorMsg;
            return crow::response(400, response);
        }
        json::wvalue response;
        response["status"] = "success";
        return crow::response(200, response);
    });

    CROW_ROUTE(app, "/api/holded-accounts/delete")
    .methods("POST"_method, "OPTIONS"_method)([](const request &req)
    {
        if (req.method == "OPTIONS"_method) return crow::response(200);
        string email = activateAccounts.getFront();
        string query = "DELETE FROM users WHERE email = '" + email + "'";
        if(mysql_query(conn, query.c_str()) != 0)
        {
            string errorMsg = mysql_error(conn);
            cout << "MySQL Query Error: " << errorMsg << endl;
            crow::json::wvalue response;
            response["status"] = "error";
            response["message"] = "somthing went wrong" + errorMsg;
            return crow::response(400, response);
        }
        activateAccounts.removeAccount();
        userList.deleteNodeByEmail(email);
        json::wvalue response;
        response["status"] = "success";
        return crow::response(200, response);
    });
   





    CROW_ROUTE(app,"/api/get-balance")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);

        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");

        string email=data.has("email")?(string)data["email"].s():(string)"";
        int balance=userList.getBalanceByEmail(email);
        json::wvalue response;
        response["balance"]=balance;
        return crow::response(200,response);


    });





}
