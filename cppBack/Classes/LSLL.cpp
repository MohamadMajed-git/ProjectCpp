#include "LSLL.hpp"
#include "../globals.hpp"
#include <iostream>
#include <string>
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