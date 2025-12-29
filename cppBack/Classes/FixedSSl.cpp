#include "FixedSSl.hpp"
#include "../globals.hpp"
#include <iostream>
#include <string>
#include <crow.h>
#include <vector>
#include <random>
#include <ctime>
#include <mysql.h>

using namespace std;


string FixedSLL::insertAtL(int id, string email, string duration , long long int amount , long long int profit, string date , int status , int nu_of_profits) {
    FixedNode* newNode = new FixedNode();
    newNode->id = id;
    newNode->email = email;
    newNode->duration = duration;
    newNode->amount = amount;
    newNode->date = date;
    newNode->profit = profit;
    newNode->status = status;
    newNode->nu_of_profits = nu_of_profits;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next=newNode;
        newNode->next = nullptr;
        tail = newNode;
    }

    return to_string(newNode->id);
}

string FixedSLL::insertAtB(int id, string email, string duration , long long int amount , long long int profit, string date ,int status , int nu_of_profits) {
    FixedNode* newNode = new FixedNode();
    newNode->id = id;
    newNode->email = email;
    newNode->duration = duration;
    newNode->amount = amount;
    newNode->date = date;
    newNode->profit = profit;
    newNode->status = status;
    newNode->nu_of_profits = nu_of_profits;
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }

    return to_string(newNode->id);
}


FixedSLL::FixedNode* FixedSLL::getNodeByEmail(string email) {
    FixedNode* cur = head;
    while (cur != nullptr) {
        if (cur->email == email) return cur;
        cur = cur->next;
    }
    return nullptr;
}
// 


void FixedSLL::deleteNodeByEmail(string email) {
    if (isEmpty()) return;

    FixedNode* cur = head;
    FixedNode* prev = nullptr;
    while (cur != nullptr) {
        if (cur->email == email) {
            if (cur == head) head = cur->next;
            else prev->next = cur->next;
            if (cur == tail) tail = prev;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}


bool FixedSLL::isEmpty() {
    return head == nullptr;
}


void FixedSLL::display() {
    if (head == nullptr) {
        cout << "Fixed list is empty" << endl;
        return;
    }

    FixedNode* cur = head;
    while (cur != nullptr) {
        cout << cur->id << " | " << cur->email << " | " << cur->duration
             << " | " << cur->amount << " | " << cur->profit << " | " << cur->status << endl;
        cur = cur->next;
    }
}

crow::json::wvalue FixedSLL::getAllFixedJSON() {
    vector<crow::json::wvalue> FixedList;

    FixedNode* temp = head;
       while (temp != nullptr) {
        crow::json::wvalue fixed;
        fixed["id"] = temp->id;
        fixed["email"] = temp->email;
        fixed["duration"] = temp->duration;
        fixed["amount"] = temp->amount;
        fixed["profit"] = temp->profit;
        fixed["date"] = temp->date;
        fixed["status"] = temp->status;

        FixedList.push_back(move(fixed));
        temp = temp->next;
    }

    return crow::json::wvalue(FixedList);
}

crow::json::wvalue FixedSLL::getFixedByEmailJSON(string email) {
    vector<crow::json::wvalue> loansList;

    FixedNode* temp = head;
    while (temp != nullptr) {
        if (temp->email == email) {
            crow::json::wvalue fixed;
            fixed["id"] = temp->id;
            fixed["email"] = temp->email;
            fixed["duration"] = temp->duration;
            fixed["amount"] = temp->amount;
            fixed["profit"] = temp->profit;
            fixed["date"] = temp->date;
            fixed["status"] = temp->status;
            loansList.push_back(move(fixed));
        }
        temp = temp->next;
    }

    return crow::json::wvalue(loansList);
}

void FixedSLL::changeStatusByid(int id, int newStatus) {
    FixedNode* cur = head;
    while (cur != nullptr) {
        if (cur->id == id) {
            cur->status = newStatus;
            return;
        }
        cur = cur->next;
    }
}













void FixedSLL::checktime() {
    FixedNode* temp = head;

    while (temp != nullptr) {

        if (temp->status != 1) {
            temp = temp->next;
            continue;
        }

        int passedMonths = monthsPassed(temp->date);

        int durationMonths = 0;
        if (temp->duration == "3 months") durationMonths = 3;
        else if (temp->duration == "6 months") durationMonths = 6;
        else if (temp->duration == "12 months") durationMonths = 12;
        else {
            cout << "Invalid duration format for Fixed ID " << temp->id << endl;
            temp = temp->next;
            continue;
        }

        int numberOfProfitsToPay = temp->nu_of_profits;

        if (numberOfProfitsToPay >= durationMonths) {
            temp = temp->next;
            continue;
        }

        if (passedMonths > numberOfProfitsToPay) {

            int monthToPay = passedMonths - numberOfProfitsToPay;

            int remainingMonths = durationMonths - numberOfProfitsToPay;
            if (monthToPay > remainingMonths) {
                monthToPay = remainingMonths;
            }

            if (monthToPay <= 0) {
                temp = temp->next;
                continue;
            }

            long long int monthlyProfit = temp->profit / durationMonths;
            numberOfProfitsToPay += monthToPay;

            string accountNumber = userList.getNodeByAccountNumberByEmail(temp->email);
            if (accountNumber == "") {
                cout << "❌ User not found for Fixed ID " << temp->id << endl;
                temp = temp->next;
                continue;
            }

            long long int totalProfitToPay = monthlyProfit * monthToPay;

            string query  = "UPDATE Fixed SET number_of_profit = " + to_string(numberOfProfitsToPay) +
                            " WHERE id = " + to_string(temp->id);

            string query2 = "UPDATE users SET balance = balance + " + to_string(totalProfitToPay) +
                            " WHERE email = '" + temp->email + "'";

            string query3 = "INSERT INTO transactions (senderAccount, receiverAccount, amount, date) "
                            "VALUES ('BANK', '" + accountNumber + "', " +
                            to_string(totalProfitToPay) + ", '" + currentDate() + "')"; 
            string message = "Dear customer, your fixed profit has been credited. Total profit amount: " + to_string(totalProfitToPay);
            string query4 = "INSERT INTO notifications (user, message, status) VALUES ('" + temp->email + "', '" + message + "', 0)";


            if (mysql_query(conn, query.c_str()) == 0 &&
                mysql_query(conn, query2.c_str()) == 0 &&
                mysql_query(conn, query3.c_str()) == 0) {

                temp->nu_of_profits = numberOfProfitsToPay;
                transactionList.insertTransaction(mysql_insert_id(conn),
                                                   "BANK", accountNumber,
                                                   totalProfitToPay, currentDate());
                userList.sendMoney("BANK", accountNumber, totalProfitToPay);
                if(mysql_query(conn, query4.c_str()) == 0)
                NotfiSLL.insertAtB(mysql_insert_id(conn), temp->email, message, 0);
                else
                cout << "❌ Profit Notification insertion failed: " << mysql_error(conn) << endl;
            }
            else {
                cout << "❌ Profit transaction failed: " << mysql_error(conn) << endl;
            }

            if (numberOfProfitsToPay == durationMonths) {

                string query4 = "UPDATE Fixed SET status = 0 WHERE id = " + to_string(temp->id);
                string query5 = "UPDATE users SET balance = balance + " + to_string(temp->amount) +
                                " WHERE email = '" + temp->email + "'";

                string query6 = "INSERT INTO transactions (senderAccount, receiverAccount, amount, date) "
                                "VALUES ('BANK', '" + accountNumber + "', " +
                                to_string(temp->amount) + ", '" + currentDate() + "')";

                string message2 = "Dear customer, your fixed deposit with ID " + to_string(temp->id) + 
                                " has matured. The amount of " + to_string(temp->amount) + 
                                " has been successfully returned to your account.";


                string query7 = "INSERT INTO notifications (user, message, status) VALUES ('" + temp->email + "', '" + message2 + "', 0)";


                if (mysql_query(conn, query4.c_str()) == 0 &&
                    mysql_query(conn, query5.c_str()) == 0 &&
                    mysql_query(conn, query6.c_str()) == 0) {

                    temp->status = 0;
                    transactionList.insertTransaction(mysql_insert_id(conn),
                                                       "BANK", accountNumber,
                                                       temp->amount, currentDate());
                    userList.sendMoney("BANK", accountNumber, temp->amount);
                    if(mysql_query(conn, query7.c_str()) == 0)
                    NotfiSLL.insertAtB(mysql_insert_id(conn), temp->email, message2, 0);
                    else
                    cout << "❌ Maturity Notification insertion failed: " << mysql_error(conn) << endl;
                }
                else {
                    cout << "❌ Maturity transaction failed: " << mysql_error(conn) << endl;
                }
            }
        }

        temp = temp->next;
    }
}





int FixedSLL::monthsPassed(const string& startDate) {
    tm start = {};
    sscanf(startDate.c_str(), "%d-%d-%d",
           &start.tm_year, &start.tm_mon, &start.tm_mday);

    start.tm_year -= 1900;
    start.tm_mon  -= 1;

    time_t now = time(0);
    tm* nowTm = localtime(&now);

    int months = (nowTm->tm_year - start.tm_year) * 12
               + (nowTm->tm_mon - start.tm_mon);

    if (nowTm->tm_mday < start.tm_mday)
        months--;

    return max(0, months); // ensures the last month is counted
}

string FixedSLL::getEmailById(int id) {
    FixedNode* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp->email;
        }
        temp = temp->next;
    }
    return ""; // not found
}














