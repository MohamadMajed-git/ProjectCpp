#include "database.hpp"
#include "globals.hpp"
#include <iostream>
using namespace std;

void connectToDatabase(){
     conn = mysql_init(0);
    const char* ca_path = "ca.pem"; 
    mysql_options(conn, MYSQL_OPT_SSL_CA, ca_path);
    if(conn ==nullptr){
        cout<<"MySQL Initialization Failed"<<endl;
        exit(1);
    }
    // const char* hostsname=getenv("DB_HOST") ? getenv("DB_HOST") : "db-avnbank-do-user-13724540-0.b.db.ondigitalocean.com";
    // const char* user=getenv("DB_USER") ? getenv("DB_USER") : "doadmin";
    // const char* pass=std::getenv("DB_PASS") ? std::getenv("DB_PASS") : "";
    // const char* dbname="bank-system";
    // unsigned int port=25739;
    const char* hostsname="mysql-cpp-project-momolovmomolov12343211-1949.e.aivencloud.com";
    const char* user="avnadmin";
    const char* pass="AVNS_RD-EPPWN0iYoIAnuPzE";
    const char* dbname="bank-system";
    unsigned int port=25739;
    if(mysql_real_connect(conn,hostsname,user,pass,dbname,port,NULL,0)){
        cout<<"Connected to database successfully"<<endl;
    }
    else{
        cout<<"Connection to database failed"<<endl;
        cout << "Error Details: " << mysql_error(conn) << endl;
        exit(1);
    }
}