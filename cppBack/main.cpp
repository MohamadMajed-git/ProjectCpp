#include <iostream>
#include "crow.h"
#include <string>
#include <mysql.h>
#include "database.hpp"
#include "globals.hpp"
#include "routes.hpp"
#include "Classes/SDLL.hpp"
using namespace std;

SLL userList; 
MYSQL* conn;

int main()
{
   
    connectToDatabase();
    crow::SimpleApp app; 
    setupRoutes(app);



    cout << ">> [START] Server listening on port 10000..." << endl;
    
    app.bindaddr("0.0.0.0").port(10000).multithreaded().run();
    mysql_close(conn);
    return 0;
}