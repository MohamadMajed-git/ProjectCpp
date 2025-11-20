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
# نثبت libmariadb-dev وهي الحزمة التي تحتوي على ملفات الهيدر
RUN apt-get update && apt-get install -y \
    g++ \
    build-essential \
    wget \
    libboost-all-dev \
    libmariadb-dev \
    libssl-dev

# 3. تحديد مجلد العمل
WORKDIR /app

# 4. تحميل مكتبة Crow
RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0+5/crow_all.h -O crow.h

# 5. نسخ ملفات المشروع
COPY . .

# 6. تجميع الكود (هنا كان الخطأ وتم تصحيحه)
# التعديل: أضفنا -I/usr/include/mariadb ليجد ملف mysql.h
RUN g++ -o my_server main.cpp \
    -std=c++17 \
    -I. \
    -I/usr/include/mariadb \
    -lpthread \
    -lmariadb

# 7. فتح البورت
EXPOSE 10000

# 8. التشغيل
CMD ["./my_server"]