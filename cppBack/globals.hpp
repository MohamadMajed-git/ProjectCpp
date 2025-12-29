#pragma once
//mohammad
#include "Classes/SDLL.hpp"
#include "Classes/QActivateAccounts.hpp"
#include "Classes/TransactionDLL.hpp"
#include "Classes/StackPassword.hpp"
#include <mysql.h>
//yossef
#include "Classes/LSLL.hpp"
#include "Classes/LQue.hpp"
#include "Classes/notfisll.hpp"

//AHMED
#include "Classes/Branch.hpp"

//Abdelsalam
#include "Classes/FixedSSl.hpp"
#include "Classes/FQue.hpp"
using namespace std;
//mohammad
extern SLL userList; 
extern MYSQL* conn;
extern QActivateAccounts activateAccounts;
extern TransactionDLL transactionList;
extern StackPassword stackPassword;
//yossef 
extern notfsll NotfiSLL;
extern LoanSLL LoanSSL;
extern LoanQueue LoanQ;
string currentDate();
string dataForYossef();
//Abdelsalam
extern FixedSLL FixedSSL;
extern FixedQueue FixedQ;


//AHMED
extern BranchList branchList;