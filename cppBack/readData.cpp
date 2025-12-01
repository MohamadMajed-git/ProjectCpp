#include "readData.hpp"
#include "globals.hpp"
#include <mysql.h>
#include <string>
using namespace std;


void readAllDataFromDatabase(){
    MYSQL_ROW row;
    MYSQL_RES* res;
    int qstate=mysql_query(conn,"SELECT fname, lname, nationalID, birthdate, email, phone, password, address, job, accountType FROM users");
    if(!qstate){// all team member qstate will return 0 if the query is successful
        res=mysql_store_result(conn);
        while((row=mysql_fetch_row(res))){
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
                row[9]
            );
        }
        mysql_free_result(res);
        userList.display();
    }
    else{
        cout<<"Query Execution Problem!"<<endl;
    }
    int qstate2=mysql_query(conn,"SELECT * FROM users WHERE status = 'hold'");
    if(!qstate2){// all team member qstate will return 0 if the query is successful
        res=mysql_store_result(conn);
        string name;
        while((row=mysql_fetch_row(res)))
        {
            
            activateAccounts.addAccount(row[1],row[7],row[15]);
        }
        mysql_free_result(res);
    }
    else{
        cout<<"Query Execution Problem!2"<< mysql_error(conn) << endl;
    }
}