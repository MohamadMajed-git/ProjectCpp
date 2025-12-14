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

//AHMED
#include "Classes/Branch.hpp"

using namespace std;
//mohammad
extern SLL userList; 
extern MYSQL* conn;
extern QActivateAccounts activateAccounts;
extern TransactionDLL transactionList;
extern StackPassword stackPassword;
//yossef 
extern LoanSLL LoanSSL;
extern LoanQueue LoanQ;
string currentDate();



//AHMED
extern BranchList branchList;