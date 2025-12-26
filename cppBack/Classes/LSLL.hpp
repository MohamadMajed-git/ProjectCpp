#pragma once
#include <iostream>
#include <string>
#include<crow.h>
#include <vector>
#include <ctime>
using namespace std;


class LoanSLL {
    private:
    struct LoanNode{
    int id;
    string email;
    int states;
    string duration;
    string loan_cost;
    string date;
    LoanNode* next=nullptr;
    };
    public:
    LoanNode* head;
    LoanNode* tail;
    int len;

    LoanSLL() {
        head = nullptr;
        tail = nullptr;
    }

    string insertAtB(int id, string email, int states, string duration, string loan_cost, string date);
    string insertAtL(int id, string email, int states, string duration, string loan_cost, string date);
    LoanNode* getNodeByEmail(string email);
    crow::json::wvalue getAllLoansJSON();
    crow::json::wvalue getLoansByEmailJSON(string email);
    void deleteNodeByEmail(string email);
    void changestates(int id, int newState);
    bool isEmpty();
    void display();
    void checklate();
};