#pragma once
#include <iostream>
#include <string>
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
    void deleteNodeByEmail(string email);
    bool isEmpty();
    void display();
};