#pragma once
#include "Classes/SDLL.hpp"
#include "Classes/QActivateAccounts.hpp"
#include <mysql.h>
using namespace std;
extern SLL userList; 
extern MYSQL* conn;
extern QActivateAccounts activateAccounts;
string currentDate();