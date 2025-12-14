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
    qstate=mysql_query(conn,"SELECT id, senderAccount, receiverAccount, amount, date FROM transactions");
    if(!qstate){
        res=mysql_store_result(conn);
        while((row=mysql_fetch_row(res))){
            transactionList.insertTransaction(
                stoi(row[0]),
                row[1],
                row[2],
                stoi(row[3]),
                row[4]
            );
        }
        mysql_free_result(res);
    }
    else{
        cout<<"Query transactionList Execution Problem!"<<endl;
    }


}

void readAllLoansFromDatabase() {
    MYSQL_ROW row;
    MYSQL_RES* res;
    

    int qstate = mysql_query(conn, "SELECT id, email, states, duration, loan_cost, date FROM loans");
    
    if (!qstate) { // 0 means query successful
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) {
            int id = stoi(row[0]);            
            string email = row[1];            
            int states = stoi(row[2]);       
            string duration = row[3];         
            string loan_cost = row[4];        
            string date = row[5];             
            

            LoanSSL.insertAtL(id, email, states, duration, loan_cost, date);
            if(states == 2){
                LoanQ.insert(id, email, states, duration, loan_cost, date);
            }
        }
        mysql_free_result(res);
        LoanSSL.display(); 
    }
    else {
        cout << "Loan Execution Problem! " << mysql_error(conn) << endl;
    }
}







void readAllBranchesFromDatabase() {
    MYSQL_ROW row;
    MYSQL_RES* res;

    int qstate = mysql_query(conn, "SELECT id, branch_name, location_link, phone, address FROM branches");
    if (!qstate) {
        res = mysql_store_result(conn);
        while ((row = mysql_fetch_row(res))) {
            int id = row[0] ? stoi(row[0]) : 0;
            string name = row[1] ? row[1] : "";
            string loc = row[2] ? row[2] : "";
            string phone = row[3] ? row[3] : "";
            string addr = row[4] ? row[4] : "";

            Branch* newBranch = new Branch(id, name, loc, phone, addr);
            branchList.insert(newBranch);
        }
        mysql_free_result(res);
        cout << "Branches loaded successfully!" << endl;


       
    } else {
        cout << "Query Execution Problem! " << mysql_error(conn) << endl;
    }
}