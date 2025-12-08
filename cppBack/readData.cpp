#include "readData.hpp"
#include "globals.hpp"
#include <mysql.h>
#include <string>
using namespace std;


void readAllDataFromDatabase(){
    MYSQL_ROW row;
    MYSQL_RES* res;
    int balance=0;
    int qstate=mysql_query(conn,"SELECT fname, lname, nationalID, birthdate, email, phone, password, address, job, accountType, createAt,balance,accountNumber FROM users");
    if(!qstate){// all team member qstate will return 0 if the query is successful
        res=mysql_store_result(conn);
        while((row=mysql_fetch_row(res))){
             balance=row[11]?std::stoi(row[11]):0;
            userList.insertAtB(
                row[0],
                row[1],
                row[2],
                row[3],
                row[4],
                row[5],
                row[6],
                row[7],
                row[8],
                row[9],
                row[10],
                balance,
                row[12]
            );
        }
        mysql_free_result(res);
        userList.display();
    }
    else{
        cout<<"Query userlist Execution Problem!"<<endl;
    }
    int qstate2=mysql_query(conn,"SELECT fname, lname, email, createAt FROM users WHERE status = 'hold'");
    if(!qstate2){// all team member qstate will return 0 if the query is successful
        res=mysql_store_result(conn);
        string name1;
        string name2;
        while((row=mysql_fetch_row(res)))
        {
            name1=row[0];
            name2=row[1];
            activateAccounts.addAccount(name1+ " " + name2,row[2],row[3]);
        }
        mysql_free_result(res);
    }
    else{
        cout<<"Query activateAccounts  Execution Problem!2"<< mysql_error(conn) << endl;
    }
}

