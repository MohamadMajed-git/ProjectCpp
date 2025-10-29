#include <iostream>
#include "crow.h"

int main()
{
    // تهيئة تطبيق Crow
    crow::SimpleApp app;

    /*************************************************
     * 1. دالة (Route) لاستقبال طلبات JSON
     * (POST /receive_json)
     *************************************************/
    CROW_ROUTE(app, "/receive_json").methods(crow::HTTPMethod::Post)
    ([](const crow::request& req){
        
        // 1. قراءة الـ body الخاص بالطلب وتحويله إلى JSON
        // نستخدم rvalue (read value)
        crow::json::rvalue received_json = crow::json::load(req.body);

        // 2. التحقق من أن الـ JSON صالح
        if (!received_json)
        {
            // إرسال رد خطأ 400 إذا كان الـ JSON غير صالح
            return crow::response(400, "Invalid JSON");
        }

        // 3. استخراج البيانات من الـ JSON
        // نفترض أن العميل سيرسل {"username": "user1", "score": 100}
        std::string username;
        int score;

        // التحقق من وجود الحقول قبل قراءتها
        if (received_json.has("username") && received_json.has("score"))
        {
            username = received_json["username"].s(); // .s() for string
            score = received_json["score"].i();     // .i() for integer
        }
        else
        {
            return crow::response(400, "Missing 'username' or 'score' fields");
        }


        // طباعة البيانات في طرفية الخادم
        CROW_LOG_INFO << "Received JSON data: username = " << username << ", score = " << score;

        // 4. إرسال رد (Response) يؤكد الاستلام
        // نستخدم wvalue (write value) لإنشاء JSON
        crow::json::wvalue response_json;
        response_json["status"] = "success";
        response_json["message"] = "Data received successfully";
        response_json["received_user"] = username;

        return crow::response(200, response_json);
    });

    /*************************************************
     * 2. دالة (Route) لإرسال رد JSON
     * (GET /send_json)
     *************************************************/
    CROW_ROUTE(app, "/send_json").methods(crow::HTTPMethod::Get)
    ([](){
        // 1. إنشاء كائن JSON لإرساله (wvalue - write value)
        crow::json::wvalue data_to_send;

        // 2. تعبئة الكائن بالبيانات
        data_to_send["server_name"] = "MyCrowApp";
        data_to_send["version"] = 1.2;
        data_to_send["active"] = true;

        // يمكنك أيضاً إضافة مصفوفات (arrays)
        data_to_send["features"][0] = "JSON API";
        data_to_send["features"][1] = "Fast";
        data_to_send["features"][2] = "Simple";

        // 3. إرسال الـ JSON كـ response
        return crow::response(200, data_to_send);
    });


    // تشغيل الخادم على البورت 18080
    app.port(18080).run();

    return 0;
}