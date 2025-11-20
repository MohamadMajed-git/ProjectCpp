# # 1. استخدام أوبونتو كأساس
# FROM ubuntu:latest

# # 2. تحديث النظام وتثبيت الأدوات الضرورية
# # أضفنا wget لتحميل المكتبة
# # وأضفنا libboost-all-dev لأن Crow تعتمد عليها أحياناً لضمان الاستقرار
# RUN apt-get update && apt-get install -y \
#     g++ \
#     build-essential \
#     wget \
#     libboost-all-dev

# # 3. تحديد مجلد العمل
# WORKDIR /app

# # 4. تحميل مكتبة Crow (ملف الـ Header فقط)
# # سنقوم بتحميله وتغيير اسمه إلى crow.h ليتوافق مع كودك
# RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0+5/crow_all.h -O crow.h

# # 5. نسخ باقي ملفات المشروع (main.cpp وغيرها)
# COPY . .

# # 6. تجميع الكود
# # ملاحظة مهمة: أضفنا -lpthread لأن السيرفرات تحتاج تعدد المهام (Threading)
# RUN g++ -o my_server main.cpp -lpthread

# # 7. فتح البورت (للتوضيح)
# EXPOSE 10000

# # 8. التشغيل
# CMD ["./my_server"]

# 1. استخدام أوبونتو كأساس
FROM ubuntu:latest

# 2. تحديث النظام وتثبيت الأدوات الضرورية
# هام جداً: أضفنا libmariadb-dev لأنك تستخدم MySQL
RUN apt-get update && apt-get install -y \
    g++ \
    build-essential \
    wget \
    libboost-all-dev \
    libmariadb-dev \
    libssl-dev

# 3. تحديد مجلد العمل
WORKDIR /app

# 4. تحميل مكتبة Crow (ملف الـ Header فقط)
# ملاحظة: تأكد أنك في كودك تستدعيها هكذا: #include "crow.h"
RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0+5/crow_all.h -O crow.h

# 5. نسخ باقي ملفات المشروع (main.cpp وغيرها)
COPY . .

# 6. تجميع الكود
# التعديلات الهامة هنا:
# 1. -I. : لكي يرى المترجم ملف crow.h الموجود في نفس المجلد
# 2. -lmariadb : لربط مكتبة قاعدة البيانات (بدونها لن يعمل الاتصال)
RUN g++ -o my_server main.cpp -std=c++17 -I. -lpthread -lmariadb

# 7. فتح البورت (للتوضيح لخدمة Render)
EXPOSE 10000

# 8. التشغيل
CMD ["./my_server"]