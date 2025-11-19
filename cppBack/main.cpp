#include <iostream>
#include "crow.h"
#include <string> // ضروري

using namespace std;

// ==========================================
// 1. تعريف كلاس وهمي للقائمة
// ==========================================
class SLL {
public:
    void insertAtB(string f, string l, string n, string b, string e, string p, string pass, string addr, string j, string acc) {
        cout << ">> [DATABASE]: User " << f << " added successfully to the list." << endl;
    }
    void display() { cout << "Displaying users..." << endl; }
};

SLL userList; 

// ==========================================
// 2. ميدل وير CORS
// ==========================================
struct CORSHandler {
    struct context {};

    void before_handle(crow::request& req, crow::response& res, context& ctx) {
        cout << ">> [INCOMING]: " << crow::method_name(req.method) << " request to " << req.url << endl;
    }

    void after_handle(crow::request& req, crow::response& res, context& ctx) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
    }
};

// ==========================================
// 3. كلاسات المنطق
// ==========================================
class Stack {
    int maxSize; int top; int *list;
public:
    Stack() { maxSize = 100; top = -1; list = new int[maxSize]; }
    int push(int value) { if (top >= maxSize-1) return -1; list[++top] = value; return value; }
    int pop() { if (top < 0) return -1; return list[top--]; }
    bool isEmpty() { return top == -1; }
    int *printResult() {
        int *resultArray = new int[top + 1];
        for (int i = top; i >= 0; i--) resultArray[top - i] = list[i];
        return resultArray;
    }
    int getSize() { return top + 1; }
};

class LargeNum {
    Stack *s1 = new Stack(); Stack *s2 = new Stack(); Stack *result = new Stack(); int carry = 0;
public:
    void addLargeNum(string num1, string num2) {
        for (char c : num1) s1->push(c - '0');
        for (char c : num2) s2->push(c - '0');
        while (!s1->isEmpty() || !s2->isEmpty() || carry) {
            int sum = carry;
            if (!s1->isEmpty()) sum += s1->pop();
            if (!s2->isEmpty()) sum += s2->pop();
            result->push(sum % 10);
            carry = (sum >= 10) ? 1 : 0;
        }
    }
    int getResultSize() { return result->getSize(); }
    int *displayResult() { return result->isEmpty() ? nullptr : result->printResult(); }
};

// ==========================================
// 4. دالة Main
// ==========================================
int main()
{
    crow::App<CORSHandler> app; 

    CROW_ROUTE(app, "/")([]() { return "Server is Online!"; });

    // مسار التسجيل
    CROW_ROUTE(app, "/api/signup")
        .methods("POST"_method, "OPTIONS"_method)
        ([](const crow::request &req){
            if (req.method == "OPTIONS"_method) return crow::response(200);

            crow::json::rvalue data = crow::json::load(req.body);
            if (!data) return crow::response(400, "Invalid JSON");

            // التعديل هنا: تحويل صريح إلى (string) للطرفين
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

            crow::json::wvalue response;
            response["status"] = "success";
            response["message"] = "User added!";
            return crow::response(200, response);
        });

    // مسار الجمع
    CROW_ROUTE(app, "/api/sum")
        .methods("POST"_method, "OPTIONS"_method)
        ([](const crow::request &req){
            if (req.method == "OPTIONS"_method) return crow::response(200);
            
            crow::json::rvalue data = crow::json::load(req.body);
            if (!data) return crow::response(400, "Invalid JSON");

            LargeNum ln;
            
            // التعديل الجذري هنا لحل مشكلة الـ Type Error
            // قمنا بتحويل crow string إلى std::string صريح
            // وقمنا بتحويل "0" إلى string("0")
            string n1 = data.has("number1") ? (string)data["number1"].s() : string("0");
            string n2 = data.has("number2") ? (string)data["number2"].s() : string("0");

            ln.addLargeNum(n1, n2);
            
            int *res = ln.displayResult();
            string sumStr = "";
            if (res) for(int i=0; i<ln.getResultSize(); i++) sumStr += to_string(res[i]);

            crow::json::wvalue response;
            response["sum"] = sumStr;
            return crow::response(200, response);
        });

    cout << ">> [START] Server listening on port 10000..." << endl;
    
    app.bindaddr("0.0.0.0").port(10000).multithreaded().run();
    return 0;
}