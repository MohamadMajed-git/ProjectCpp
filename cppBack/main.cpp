//"C:\Program Files\Google\Chrome\Application\chrome.exe" --disable-web-security --user-data-dir="C:\Chrome-dev-session"


#include <iostream>
#include "crow.h"
#include "crow/middlewares/cors.h"
using namespace std;
// mohammad fork
class Stack
{
    int maxSize;
    int top;
    int *list;

public:
    Stack()
    {
        maxSize = 100;
        top = -1;
        list = new int[maxSize];
    }
    Stack(int size)
    {
        maxSize = size;
        top = -1;
        list = new int[maxSize];
    }

    void restart()
    {
        for (int i = 0; i <= top; i++)
        {
            list[i] = 0;
        }
        top = -1;
    }
    bool isEmpty()
    {
        return top == -1;
    }
    bool isFull()
    {
        return top == maxSize - 1;
    }
    int getSize()
    {
        return top + 1;
    }
    int push(int value)
    {
        if (isFull())
        {
            cout << "Stack Overflow" << endl;
            return -1;
        }
        top++;
        list[top] = value;
        return value;
    }
    int pop()
    {
        if (isEmpty())
        {
            cout << "Stack Underflow" << endl;
            return -1;
        }
        return list[top--];
    }
    int peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return list[top];
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        for (int i = 0; i <= top; i++)
        {
            cout << list[i] << "";
        }
        cout << endl;
    }
    int *printResult()
    {
        int *resultArray = new int[top + 1];
        for (int i = top; i >= 0; i--)
        {
            resultArray[top - i] = list[i];
        }
        return resultArray;
    }
};

class LargeNum
{
    Stack *s1 = new Stack();
    Stack *s2 = new Stack();
    Stack *result = new Stack();
    int carry = 0;

public:
    void addLargeNum(string num1, string num2)
    {
        for (int i = 0; i < num1.length(); i++)
        {
            s1->push(num1[i] - '0');
        }
        for (int i = 0; i < num2.length(); i++)
        {
            s2->push(num2[i] - '0');
        }
        while (!s1->isEmpty() || !s2->isEmpty() || carry)
        {
            int sum = carry;
            if (!s1->isEmpty())
            {
                sum += s1->pop();
            }
            if (!s2->isEmpty())
            {
                sum += s2->pop();
            }
            result->push(sum % 10);
            if (sum >= 10)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }
        }
    }
    int getResultSize()
    {
        if (!result->isEmpty())
        {
            return result->getSize();
        }
        return 0;
    }
    int *displayResult()
    {
        if (!result->isEmpty())
        {
            return result->printResult();
        }
        return nullptr;
    }
};

int main()
{
crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]()
     { return "Hello, Crow C++!65"; });

    CROW_ROUTE(app, "/json")
    ([]()
     {
        crow::json::wvalue response;
        response["message"] = "This is a GET JSON response!";
        response["status"] = 200;
        return response; });

    // --- !! فانكشن استقبال البوست الجديدة !! ---
    // هذه النقطة تستمع لطلبات POST فقط على /receive_json
    CROW_ROUTE(app, "/api/submit")
        .methods("POST"_method) // تحديد أن هذا المسار لـ POST
        ([](const crow::request &req)
         {
             // 1. قراءة الـ body القادم من الطلب وتحويله إلى JSON
             crow::json::rvalue data = crow::json::load(req.body);

             // 2. التحقق إذا كان الـ JSON غير صالح أو فارغ
             if (!data)
             {
                 return crow::response(400, "Invalid JSON"); // 400 Bad Request
             }

             // 3. معالجة البيانات (مثال: استخراج اسم مستخدم)
             // نفترض أن الكلاينت سيرسل {"username": "someone"}
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


    CROW_ROUTE(app, "/api/sum")
        .methods("POST"_method)
        ([](const crow::request &req){
            crow::json::rvalue data = crow::json::load(req.body);
            if (!data)
            {
                return crow::response(400, "Invalid JSON");
            }
            LargeNum ln;
            ln.addLargeNum(data["number1"].s(), data["number2"].s());
            crow::json::wvalue response;
            response["status"] = "success";
                         int *result = ln.displayResult();
             int size = ln.getResultSize();
             std::string sumString = "";

             if (result != nullptr)
             {
                 for (int i = 0; i < size; i++)
                 {
                     sumString += std::to_string(result[i]);
                 }
             }
            response["sum"] = sumString;
            return crow::response(200, response);
        });

    std::cout << "Starting Crow server on port 8000..." << std::endl;

    // تشغيل الخادم على بورت 8000
    app.bindaddr("127.0.0.1").port(8000).multithreaded().run();

    return 0;
}
