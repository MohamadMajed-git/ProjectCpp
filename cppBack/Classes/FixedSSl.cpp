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
        int passedMonths = monthsPassed(temp->date);
    while (temp != nullptr) {
        if (temp->status == 1) { // Only active plans
            int durationMonths = 0;
            if (temp->duration == "3 months") durationMonths = 3;
            else if (temp->duration == "6 months") durationMonths = 6;
            else if (temp->duration == "12 months") durationMonths = 12;


            int effectiveMonths = min(passedMonths, durationMonths);

            // ---------- 1. HANDLE MONTHLY PROFITS ----------
            if (effectiveMonths > temp->nu_of_profits && durationMonths > 0) {
                int monthsToPay = effectiveMonths - temp->nu_of_profits;
                long long int monthlyProfit = temp->profit / durationMonths;
                long long int totalProfitToPay = monthlyProfit * monthsToPay;

                string accountNo = userList.getNodeByEmail(temp->email)->accountNumber;

                // Update nu_of_profits in memory first
                temp->nu_of_profits = effectiveMonths;

                string qProf = "UPDATE Fixed SET number_of_profit = " + to_string(effectiveMonths) + " WHERE id = " + to_string(temp->id);
                string qBal = "UPDATE users SET balance = balance + " + to_string(totalProfitToPay) + " WHERE email = '" + temp->email + "'";
                string qTrans = "INSERT INTO transactions (senderAccount, receiverAccount, amount, date) VALUES ('BANK', '" + accountNo + "', " + to_string(totalProfitToPay) + ", '" + currentDate() + "')";

                if (mysql_query(conn, qProf.c_str()) == 0 &&
                    mysql_query(conn, qBal.c_str()) == 0 &&
                    mysql_query(conn, qTrans.c_str()) == 0) {

                    int transactionId = mysql_insert_id(conn);
                    transactionList.insertTransaction(transactionId, "BANK", accountNo, totalProfitToPay, currentDate());
                    userList.sendMoney("BANK", accountNo, totalProfitToPay);
                }
            }

            // ---------- 2. HANDLE MATURITY (Principal Return) ----------
            if (passedMonths >= temp->nu_of_profits) {
                // Update status in memory first
                temp->status = 0;

                string accountNo = userList.getNodeByEmail(temp->email)->accountNumber;

                string qStat = "UPDATE Fixed SET status = 0 WHERE id = " + to_string(temp->id);
                string qPrin = "UPDATE users SET balance = balance + " + to_string(temp->amount) + " WHERE email = '" + temp->email + "'";
                string qTrans2 = "INSERT INTO transactions (senderAccount, receiverAccount, amount, date) VALUES ('BANK', '" + accountNo + "', " + to_string(temp->amount) + ", '" + currentDate() + "')";

                if (mysql_query(conn, qStat.c_str()) == 0 &&
                    mysql_query(conn, qPrin.c_str()) == 0 &&
                    mysql_query(conn, qTrans2.c_str()) == 0) {

                    int transactionId = mysql_insert_id(conn);
                    transactionList.insertTransaction(transactionId, "BANK", accountNo, temp->amount, currentDate());
                    userList.sendMoney("BANK", accountNo, temp->amount);
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

    return max(0, months + 1); // ensures the last month is counted
}





