#include "LSLL.hpp"
#include "../globals.hpp"
#include <iostream>
#include <string>
#include <crow.h>
#include <vector>
#include <mysql.h>
#include <random>

using namespace std;


string LoanSLL::insertAtL(int id, string email, int states, string duration, string loan_cost, string date) {
    LoanNode* newNode = new LoanNode();
    newNode->id = id;
    newNode->email = email;
    newNode->states = states;
    newNode->duration = duration;
    newNode->loan_cost = loan_cost;
    newNode->date = date;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next=newNode;
        newNode->next = nullptr;
        tail = newNode;
    }

    return to_string(newNode->id);
}

string LoanSLL::insertAtB(int id, string email, int states, string duration, string loan_cost, string date) {
    LoanNode* newNode = new LoanNode();
    newNode->id = id;
    newNode->email = email;
    newNode->states = states;
    newNode->duration = duration;
    newNode->loan_cost = loan_cost;
    newNode->date = date;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }

    return to_string(newNode->id);
}


LoanSLL::LoanNode* LoanSLL::getNodeByEmail(string email) {
    LoanNode* cur = head;
    while (cur != nullptr) {
        if (cur->email == email) return cur;
        cur = cur->next;
    }
    return nullptr;
}


void LoanSLL::deleteNodeByEmail(string email) {
    if (isEmpty()) return;

    LoanNode* cur = head;
    LoanNode* prev = nullptr;

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


bool LoanSLL::isEmpty() {
    return head == nullptr;
}


void LoanSLL::display() {
    if (head == nullptr) {
        cout << "Loan list is empty" << endl;
        return;
    }

    LoanNode* cur = head;
    while (cur != nullptr) {
        cout << cur->id << " | " << cur->email << " | " << cur->states
             << " | " << cur->duration << " | " << cur->loan_cost
             << " | " << cur->date << endl;
        cur = cur->next;
    }
}
void LoanSLL::changestates(int id, int newState) {
    LoanNode* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            temp->states = newState;
            return;
        }
        temp = temp->next;
    }
}

crow::json::wvalue LoanSLL::getAllLoansJSON() {
    vector<crow::json::wvalue> loansList;

    LoanNode* temp = head;
    while (temp != nullptr) {
        crow::json::wvalue loan;
        loan["id"] = temp->id;
        loan["email"] = temp->email;
        loan["states"] = temp->states;
        loan["duration"] = temp->duration;
        loan["loan_cost"] = temp->loan_cost;
        loan["date"] = temp->date;

        loansList.push_back(move(loan));
        temp = temp->next;
    }

    return crow::json::wvalue(loansList);
}

crow::json::wvalue LoanSLL::getLoansByEmailJSON(string email) {
    vector<crow::json::wvalue> loansList;

    LoanNode* temp = head;
    while (temp != nullptr) {
        if (temp->email == email) {
            crow::json::wvalue loan;
            loan["id"] = temp->id;
            loan["email"] = temp->email;
            loan["states"] = temp->states;
            loan["duration"] = temp->duration;
            loan["loan_cost"] = temp->loan_cost;
            loan["date"] = temp->date;

            loansList.push_back(move(loan));
        }
        temp = temp->next;
    }

    return crow::json::wvalue(loansList);
}
void LoanSLL::checklate() {
    LoanNode* temp = head;
    time_t now = time(0);

    while (temp != nullptr) {

        // Only check active loans
        if (temp->states == 1) {

            int year, month, day;
            sscanf(temp->date.c_str(), "%d-%d-%d", &year, &month, &day);

            tm dueDate = {};
            dueDate.tm_year = year - 1900;

                                int durationMonths = 0;

                if (temp->duration == "3 months") {
                    durationMonths = 3;
                } 
                else if (temp->duration == "6 months") {
                    durationMonths = 6;
                } 
                else if (temp->duration == "12 months") {
                    durationMonths = 12;
                } 
                else {
                    durationMonths = 0;
                }
            dueDate.tm_mon  = (month - 1) + durationMonths +1; // ADD MONTHS
            dueDate.tm_mday = day;

            // Normalize date (handles month overflow automatically)
            time_t dueTime = mktime(&dueDate);

            // If current time is after due date → late
            if (difftime(now, dueTime) > 0) {
                    long long cost = stoll(temp->loan_cost);
                    long long lateCost = (cost * 8 /100);;
                    string lateamount = to_string(lateCost);
                    string query ="UPDATE loans SET states = 4, loan_cost = " + lateamount +" WHERE id = " + to_string(temp->id);
                if(mysql_query(conn, query.c_str()) == 0) {

                    LoanSSL.changeAmountLate(temp->id);
                    LoanSSL.changestates(temp->id, 4); // 4 = late
                } else {
                    cout << "Failed to update loan ID " << temp->id << ": " << mysql_error(conn) << endl;
                }

            }
        }

        temp = temp->next;
    }
}

void LoanSLL::changeAmountLate(int id) {
    LoanNode* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            long long int cost = stoll(temp->loan_cost);
            cost *= 1.08; // Increase by 10%
            temp->loan_cost = to_string(cost);
            return;
        }
        temp = temp->next;
    }
}
