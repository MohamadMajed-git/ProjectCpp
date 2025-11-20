# 1. استخدام أوبونتو كأساس
FROM ubuntu:latest

# 2. تحديث النظام وتثبيت المترجم ومكتبات MariaDB/MySQL
RUN apt-get update && apt-get install -y \
    g++ \
    build-essential \
    wget \
    libmariadb-dev \
    libssl-dev

# 3. تحديد مجلد العمل
WORKDIR /app

# 4. تحميل مكتبة Crow (احتياطياً في حال لم تكن موجودة محلياً)
RUN wget https://github.com/CrowCpp/Crow/releases/download/v1.0+5/crow_all.h -O crow.h

# 5. نسخ جميع ملفات المشروع إلى السيرفر
COPY . .

# 6. تجميع الكود (الخطوة الحاسمة)
# لاحظ: قمنا بتضمين Classes/*.cpp لحل مشكلة الـ Linker
RUN g++ -o my_server *.cpp Classes/*.cpp \
    -std=c++17 \
    -I. \
    -I./libs/crow -I./libs/asio \
    -I/usr/include/mariadb \
    -lpthread -lmariadb \
    -DCROW_USE_STANDALONE_ASIO

# 7. فتح البورت
EXPOSE 10000

# 8. أمر التشغيل
CMD ["./my_server"]
```

### 🚀 الخطوات النهائية للرفع (Deploy):

1.  **احفظ الملف:** تأكد أن اسم الملف هو `Dockerfile` (بدون أي امتداد مثل .txt).
2.  **ارفع التعديلات:**
    ```bash
    git add .
    git commit -m "Fixed Dockerfile compilation command"
    git push