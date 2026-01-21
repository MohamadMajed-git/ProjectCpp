//start chrome --disable-web-security --user-data-dir="C:\TempChrome"


#include <iostream>
#include "crow.h"
#include <string>
#include <mysql.h>
#include "globals.hpp"
#include "routes.hpp"
#include <time.h> //time library
#include <iomanip> //for put_time
#include <sstream>// to convert time to string
//Mohammad ---------------
#include "database.hpp"
#include "Classes/SDLL.hpp"
#include "Classes/TransactionDLL.hpp"
#include "Classes/StackPassword.hpp"
#include "Classes/QActivateAccounts.hpp"
#include "readData.hpp"


// AHMED------------------
#include "Classes/Branch.hpp" 
// abdelsalam----------------
#include "Classes/FixedSSl.hpp"
#include "Classes/FQue.hpp"

using namespace std;
//mohammad
SLL userList; 
TransactionDLL transactionList;
QActivateAccounts activateAccounts;
MYSQL* conn;
StackPassword stackPassword;
//yossef
LoanSLL LoanSSL;
LoanQueue LoanQ;
notfsll NotfiSLL;

//Abdelsalam
FixedSLL FixedSSL;
FixedQueue FixedQ;

//AHMED 
BranchList branchList;

int main()
{
    
    connectToDatabase();
    readAllDataFromDatabase();
    readAllLoansFromDatabase();
    readAllNotificationsFromDatabase();
    readAllFixedFromDatabase();
    readAllBranchesForUser();
    crow::SimpleApp app; 
    setupRoutes(app); 
    setupLoanRoutes(app);
    setupBranchRoutes(app);
    setupFixedRoutes(app);
    checktimeroute(app);
    setupNotfiRoutes(app);




    cout << "We are on port 10000..." << endl;
    
    app.bindaddr("0.0.0.0").port(10000).multithreaded().run();
    mysql_close(conn);
    return 0;
}





