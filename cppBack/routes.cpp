#include "routes.hpp"
#include "globals.hpp"
#include <string>
#include <mysql.h>
#include "database.hpp"
#include <iostream>
#include "Classes/SDLL.hpp"
#include "Classes/Branch.hpp"
using namespace std;
using namespace crow;

void setupRoutes(crow::SimpleApp &app)
{



    //!MOOOOOHHHHAAAAMMMMAAAADDDDD
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
                                                      string accountNumber=userList.createAccountNumber(accType);
                                                      string query = "INSERT INTO users (fname, lname, nationalID, birthdate, email, phone, password, address, job, accountType, createAt,accountNumber) VALUES ('" + fName + "', '" + lName + "', '" + natID + "', '" + bDate + "', '" + email + "', '" + phone + "', '" + pass + "', '" + addr + "', '" + job + "', '" + accType + "', '" + createAt + "', '" + accountNumber + "')";
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
                                                              balance,
                                                              accountNumber
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
                                                          return crow::response(400, response);}
    });

    CROW_ROUTE(app, "/api/login")
        .methods("POST"_method, "OPTIONS"_method)([](const request &req){
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
                            {"accountType",userData[9]},
                            {"accountNumber",userData[14]}
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
   





    CROW_ROUTE(app,"/api/get-user-data")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);

        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");

        string email=data.has("email")?(string)data["email"].s():(string)"";
        
        json::wvalue response;
        response["user"]=userList.getDataByEmail(email);
        return crow::response(200,response);


    });


    CROW_ROUTE(app,"/api/send-money")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);
        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");
        string senderAccountNumber=data.has("senderAccountNumber")?(string)data["senderAccountNumber"].s():(string)"";
        int amount=data.has("amount")?stoi((string)data["amount"].s()):0;
        string receiverAccountNumber=data.has("receiverAccountNumber")?(string)data["receiverAccountNumber"].s():(string)"";
        bool status=userList.sendMoney(senderAccountNumber, receiverAccountNumber, amount);
        if(status==false){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "Transaction failed";
            return crow::response(400, response);
        }
        string query = "UPDATE users SET balance = balance - " + to_string(amount) + " WHERE accountNumber = '" + senderAccountNumber + "'";
        if(mysql_query(conn, query.c_str()) != 0)
        {
            string errorMsg = mysql_error(conn);
            cout << "MySQL Query Error: " << errorMsg << endl;
            crow::json::wvalue response;
            response["status"] = "error";
            response["message"] = "somthing went wrong" + errorMsg;
            return crow::response(400, response);
        }
        query = "UPDATE users SET balance = balance + " + to_string(amount) + " WHERE accountNumber = '" + receiverAccountNumber + "'";
        if(mysql_query(conn, query.c_str()) != 0)
        {
            string errorMsg = mysql_error(conn);
            cout << "MySQL Query Error: " << errorMsg << endl;
            crow::json::wvalue response;
            response["status"] = "error";
            response["message"] = "somthing went wrong" + errorMsg;
            return crow::response(400, response);
        }
        query = "INSERT INTO transactions (senderAccount, receiverAccount, amount, date) VALUES ('" + senderAccountNumber + "', '" + receiverAccountNumber + "', " + to_string(amount) + ", '" + currentDate() + "')";
        if(mysql_query(conn, query.c_str()) != 0)
        {
            string errorMsg = mysql_error(conn);
            cout << "MySQL Query Error: " << errorMsg << endl;
            crow::json::wvalue response;
            response["status"] = "error";
            response["message"] = "somthing went wrong" + errorMsg;
            return crow::response(400, response);
        }
        query = "SELECT id FROM transactions WHERE senderAccount = '" + senderAccountNumber + "' AND receiverAccount = '" + receiverAccountNumber + "' AND amount = " + to_string(amount) + " ORDER BY id DESC LIMIT 1";
        if(!mysql_query(conn, query.c_str()))
        {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);
            int transactionId = stoi(row[0]);
            transactionList.insertTransaction(transactionId, senderAccountNumber, receiverAccountNumber, amount, currentDate());
            mysql_free_result(res);
        }
        json::wvalue response;
        response["status"] = "success";
        return crow::response(200, response);
    });





    CROW_ROUTE(app,"/api/user-transaction")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);

        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");

        string accountNumber=data.has("accountNumber")?(string)data["accountNumber"].s():(string)"";
        json::wvalue response;
        response["transactions"]=transactionList.getUserTransactions(accountNumber);
        return crow::response(200,response);
    });
        


    CROW_ROUTE(app,"/api/all-transactions")
    .methods("GET"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);

        json::wvalue response;
        response["transactions"]=transactionList.getAllTransactions();
        return crow::response(200,response);
    });



    CROW_ROUTE(app,"/api/search-transaction")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);

        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");

        int searchId=data.has("searchId")?(int)data["searchId"].i():0;
        json::wvalue response;
        response["transactions"]=transactionList.getTransactionById(searchId);
        return crow::response(200,response);
    });



    CROW_ROUTE(app,"/api/change-password")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);

        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");

        string email=data.has("email")?(string)data["email"].s():(string)"";
        string oldPassword=data.has("oldPassword")?(string)data["oldPassword"].s():(string)"";
        string newPassword=data.has("newPassword")?(string)data["newPassword"].s():(string)"";
        bool checkOldPassword = userList.checkPassword(email, oldPassword);
        if(checkOldPassword==false){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "Old password is incorrect";
            return crow::response(400, response);
        }
        string query="INSERT INTO `password-requests` (`email`, `new-password`) VALUES('"+email+"','"+newPassword+"')";
        if(mysql_query(conn,query.c_str())==0){
                bool found = userList.checkIfUserExist(email);

            if (!found ) {
                json::wvalue response;
                response["status"] = "error";
                response["message"] = "User not found";
                return crow::response(404, response);
            }
            stackPassword.pushRequest(newPassword, email);

    }
        else{
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


    CROW_ROUTE(app,"/api/password-change-requests")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);
        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");
        string email=data.has("email")?(string)data["email"].s():(string)"";
        bool isAdmin = userList.checkIfAdmin(email);
        if(isAdmin==false){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "Unauthorized";
            return crow::response(401, response);
        }
        json::wvalue response;
        response["requests"] = stackPassword.getAllData();
        return crow::response(200, response);
    });

    CROW_ROUTE(app,"/api/approve-password-change")
    .methods("POST"_method,"OPTIONS"_method)
    ([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);
        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");
        string email=data.has("email")?(string)data["email"].s():(string)"";
        string newPassword=data.has("newPassword")?(string)data["newPassword"].s():(string)"";
        string userEmail=data.has("userEmail")?(string)data["userEmail"].s():(string)"";
        bool isAdmin = userList.checkIfAdmin(email);
        if(isAdmin==false){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "Unauthorized";
            return crow::response(401, response);
        }
        if(stackPassword.isEmpty()){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "No password change requests";
            return crow::response(400, response);
        }
            string query = "UPDATE users SET password = '" + newPassword + "' WHERE email = '" + userEmail + "'";
            if(mysql_query(conn, query.c_str()) != 0)
            {
                string errorMsg = mysql_error(conn);
                cout << "MySQL Query Error: " << errorMsg << endl;
                crow::json::wvalue response;
                response["status"] = "error";
                response["message"] = "somthing went wrong" + errorMsg;
                return crow::response(400, response);
            }
            query = "UPDATE `password-requests` SET status = 'approved' WHERE email = '" + userEmail + "' AND status = 'pending'";
            if(mysql_query(conn, query.c_str()) != 0)
            {
                string errorMsg = mysql_error(conn);
                cout << "MySQL Query Error: " << errorMsg << endl;
                crow::json::wvalue response;
                response["status"] = "error";
                response["message"] = "somthing went wrong" + errorMsg;
                return crow::response(400, response);
            }
        userList.updatePassword(userEmail, newPassword);
        stackPassword.popRequest();
        json::wvalue response;
        response["status"] = "success";
        return crow::response(200, response);
        
    });

    CROW_ROUTE(app,"/api/deny-password-change")
    .methods("POST"_method,"OPTIONS"_method)([](const request &req){
        if (req.method == "OPTIONS"_method) return crow::response(200);
        json::rvalue data=json::load(req.body);
        if(!data)return response(400,"Invalid JSON");
        string email=data.has("email")?(string)data["email"].s():(string)"";
        string newPassword=data.has("newPassword")?(string)data["newPassword"].s():(string)"";
        string userEmail=data.has("userEmail")?(string)data["userEmail"].s():(string)"";
        bool isAdmin = userList.checkIfAdmin(email);
        if(isAdmin==false){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "Unauthorized";
            return crow::response(401, response);
        }
        if(stackPassword.isEmpty()){
            json::wvalue response;
            response["status"] = "error";
            response["message"] = "No password change requests";
            return crow::response(400, response);
        }
        string query = "UPDATE `password-requests` SET status = 'denied' WHERE email = '" + userEmail + "' AND status = 'pending' ORDER BY id DESC LIMIT 1";
            if(mysql_query(conn, query.c_str()) != 0)
            {
                string errorMsg = mysql_error(conn);
                cout << "MySQL Query Error: " << errorMsg << endl;
                crow::json::wvalue response;
                response["status"] = "error";
                response["message"] = "somthing went wrong" + errorMsg;
                return crow::response(400, response);
            }
        stackPassword.popRequest();
        json::wvalue response;
        response["status"] = "success";
        return crow::response(200, response);
        });







        
        
        
        
        

        
        
        
        
        

        
        
    }
    
//! yoooooooooooooooosssssssssseeeeeffff



void setupLoanRoutes(crow::SimpleApp &app) {
        CROW_ROUTE(app,"/api/submit-loan-request")
    .methods("POST"_method,"OPTIONS"_method)([](const request &req){
                if (req.method == "OPTIONS"_method) return crow::response(200);
                json::rvalue data=json::load(req.body);
            if(!data)return response(400,"Invalid JSON");
            string email=data.has("email")?(string)data["email"].s():(string)"";
            string duration=data.has("duration")?(string)data["duration"].s():(string)"";
            int money=data.has("moneyOfLoan")?(int)data["moneyOfLoan"]:0;
            if(!userList.checkIfUserExist(email)){
                cout<<1;
                json::wvalue err;
                err["message"]="the user not exist";
                return crow::response(400,err);
            }
            string query="INSERT INTO loans (email,states,duration,loan_cost,date) VALUES('"+email+"',2,'"+duration+"','"+to_string(money)+"','"+currentDate()+"') ";
            if(mysql_query(conn,query.c_str())==0){
                long long id = mysql_insert_id(conn);
                LoanQ.insert(id,email,2,duration,to_string(money),currentDate());
                LoanSSL.insertAtL(id,email,2,duration,to_string(money),currentDate());
                return crow::response(200,"ok");
            }
            else{
                json::wvalue err;
                err["message"]=mysql_error(conn);
                return crow::response(400,err);
            }

    });



    CROW_ROUTE(app, "/api/admin/get-all-loans")
.methods("GET"_method)
([]() {
    return crow::response(200, LoanQ.getAllLoansJSON());
});


CROW_ROUTE(app, "/api/admin/approve-loan")
.methods("POST"_method, "OPTIONS"_method)
([](const crow::request& req) {
    if (req.method == "OPTIONS"_method) return crow::response(200);

    auto data = crow::json::load(req.body);
    if (!data) return crow::response(400, "Invalid JSON");

    int id = data["id"].i();
    std::vector<std::string> data1 = LoanQ.getEmailAndMoney(id);
    std::string email = data1[0];
    std::string money = data1[1];

    int moneyInt = stoi(money);
    string query = "UPDATE loans SET states = 1 WHERE id = " + to_string(id);
    string query2 = "UPDATE users SET balance = balance + " + to_string(moneyInt) +" WHERE email = '" + email + "'";

    if(mysql_query(conn,query.c_str())==0 && mysql_query(conn,query2.c_str())==0){   

    LoanQ.changestates(id, 1); // approveds
    LoanSSL.changestates(id, 1); // approveds
    LoanQ.remove();

        return crow::response(200, "State updated");
        }
        else{
                json::wvalue err;
                err["message"]=mysql_error(conn);
                return crow::response(400,err);
            }


    return crow::response(200, "approved");
});


//////////////////////////////////
CROW_ROUTE(app, "/api/admin/deny-loan")
.methods("POST"_method, "OPTIONS"_method)
([](const crow::request& req) {
    if (req.method == "OPTIONS"_method) return crow::response(200);

    auto data = crow::json::load(req.body);
    if (!data) return crow::response(400, "Invalid JSON");

    int id = data["id"].i();
    string query = "UPDATE loans SET states = 3 WHERE id = " + to_string(id);
    if(mysql_query(conn,query.c_str())==0){   

    LoanQ.changestates(id, 3); // deny
    LoanSSL.changestates(id, 3); // deny
    LoanQ.remove();
        return crow::response(200, "State updated");

        }


    return crow::response(200, "denied");
});




CROW_ROUTE(app, "/api/admin/get-all-loans-history")
.methods("GET"_method)
([]() {
    return crow::response(200, LoanSSL.getAllLoansJSON());
});

CROW_ROUTE(app, "/api/client/get-loans-history")
.methods("GET"_method)
([](const crow::request& req) {
    auto email = req.url_params.get("email");
    return crow::response(200, LoanSSL.getLoansByEmailJSON(email));
});


}
















void setupBranchRoutes(crow::SimpleApp &app) {

    CROW_ROUTE(app, "/api/branches").methods("GET"_method)
    ([&](const crow::request &req){
        auto query_dict = crow::query_string(req.url);
        string search = query_dict.get("search") ? query_dict.get("search") : "";

        crow::json::wvalue result;
        int index = 0;
        Branch* cur = branchList.getAll();

        while(cur) {
            bool include = true;
            if(!search.empty()) {
                stringstream ss;
                ss << cur->id;
                string id_str = ss.str();
                if(cur->branch_name.find(search) == string::npos && id_str.find(search) == string::npos) {
                    include = false;
                }
            }
            if(include) {
                result[index]["id"] = cur->id;
                result[index]["branch_name"] = cur->branch_name;
                result[index]["location_link"] = cur->location_link;
                result[index]["phone"] = cur->phone;
                result[index]["address"] = cur->address;
                index++;
            }
            cur = cur->next;
        }

        return crow::response(result);
    });

    // GET فرع بالـ ID
    CROW_ROUTE(app, "/branches/<int>").methods("GET"_method)
    ([&](int id){
        Branch* branch = branchList.findById(id);
        if(branch) {
            crow::json::wvalue result;
            result["id"] = branch->id;
            result["branch_name"] = branch->branch_name;
            result["location_link"] = branch->location_link;
            result["phone"] = branch->phone;
            result["address"] = branch->address;
            return crow::response(result);
        } else {
            crow::json::wvalue res;
            res["error"] = "Branch not found";
            return crow::response(404, res);
        }
    });

    // POST لإضافة فرع جديد
    CROW_ROUTE(app, "/api/branches").methods("POST"_method)
    ([&](const crow::request &req){
        auto body = crow::json::load(req.body);
        if(!body) {
            crow::json::wvalue resErr;
            resErr["error"] = "Invalid JSON";
            return crow::response(400, resErr);
        }

        string name = body["branch_name"].s();
        string loc = body["location_link"].s();
        string phone = body["phone"].s();
        string addr = body["address"].s();

        static int tempId = 1000;
        Branch* newBranch = new Branch(tempId++, name, loc, phone, addr);
        branchList.insert(newBranch);

        crow::json::wvalue res;
        res["message"] = "Branch added successfully";
        res["branch"]["id"] = newBranch->id;
        res["branch"]["branch_name"] = newBranch->branch_name;
        return crow::response(res);
    });

    // DELETE فرع
    CROW_ROUTE(app, "/branches/<int>").methods("DELETE"_method)
    ([&](int id){
        bool removed = branchList.removeById(id);
        crow::json::wvalue res;
        if(removed) {
            res["message"] = "Branch deleted successfully";
            return crow::response(res);
        } else {
            res["error"] = "Branch not found";
            return crow::response(404, res);
        }
    });

    // PUT لتعديل فرع
    CROW_ROUTE(app, "/branches/<int>").methods("PUT"_method)
    ([&](const crow::request &req, int id){
        Branch* branch = branchList.findById(id);
        if(!branch) {
            crow::json::wvalue resErr;
            resErr["error"] = "Branch not found";
            return crow::response(404, resErr);
        }

        auto body = crow::json::load(req.body);
        if(!body) {
            crow::json::wvalue resErr;
            resErr["error"] = "Invalid JSON";
            return crow::response(400, resErr);
        }

        if(body.has("branch_name")) branch->branch_name = body["branch_name"].s();
        if(body.has("location_link")) branch->location_link = body["location_link"].s();
        if(body.has("phone")) branch->phone = body["phone"].s();
        if(body.has("address")) branch->address = body["address"].s();

        crow::json::wvalue res;
        res["message"] = "Branch updated successfully";
        res["branch"]["id"] = branch->id;
        res["branch"]["branch_name"] = branch->branch_name;
        return crow::response(res);
    });


     // GET كل الفروع للمستخدم
    CROW_ROUTE(app, "/user/branches").methods("GET"_method)
    ([&](){
        crow::json::wvalue result;
        int index = 0;
        Branch* cur = branchList.getAll();

        while(cur) {
            result[index]["branch_name"] = cur->branch_name;       // اسم البنك
            result[index]["area"] = cur->address;                 // اسم المنطقة
            result[index]["phone"] = cur->phone;                 // رقم التليفون
            result[index]["location_link"] = cur->location_link; // لينك اللوكيشن
            index++;
            cur = cur->next;
        }

        return crow::response(result);
    });





}






