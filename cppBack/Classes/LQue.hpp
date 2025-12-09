#pragma once
#include <iostream>
#include <string>
using namespace std;

class LoanQueue {
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

    LoanQueue() {
        head = nullptr;
        tail = nullptr;
    }

    string insert(int id, string email, int states, string duration, string loan_cost, string date);
    LoanNode* getNodeByEmail(string email);
    void deleteNodeByEmail(string email);
    void remove();
    bool isEmpty();
    void display();
};