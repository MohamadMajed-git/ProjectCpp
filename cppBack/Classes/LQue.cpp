#include "LQue.hpp"
#include "../globals.hpp"
#include <iostream>
#include <string>
#include <random>

using namespace std;

string LoanQueue::insert(int id, string email, int states, string duration, string loan_cost, string date) {
    LoanNode* newNode = new LoanNode();
    newNode->id = id;
    newNode->email = email;
    newNode->states = states;
    newNode->duration = duration;
    newNode->loan_cost = loan_cost;
    newNode->date = date;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    len++;
    return "Inserted Successfully!";
}

bool LoanQueue::isEmpty() {
    return head == nullptr;
}

LoanQueue::LoanNode* LoanQueue::getNodeByEmail(string email) {
    LoanNode* temp = head;
    while (temp != nullptr) {
        if (temp->email == email) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void LoanQueue::deleteNodeByEmail(string email) {
    if (isEmpty()) return;

    LoanNode* temp = head;
    LoanNode* prev = nullptr;

    if (head->email == email) {
        head = head->next;
        delete temp;
        len--;
        if (head == nullptr) tail = nullptr;
        return;
    }


    while (temp != nullptr && temp->email != email) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) return; 

    prev->next = temp->next;
    if (temp == tail) tail = prev;

    delete temp;
    len--;
}

void LoanQueue::display() {
    if (isEmpty()) {
        cout << "Loan Queue is empty.\n";
        return;
    }

    LoanNode* temp = head;

    cout << "---------------- Loan Queue ----------------\n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id
             << " | Email: " << temp->email
             << " | States: " << temp->states
             << " | Duration: " << temp->duration
             << " | Cost: " << temp->loan_cost
             << " | Date: " << temp->date
             << endl;

        temp = temp->next;
    }
    cout << "--------------------------------------------\n";
}
void LoanQueue::remove() {
    if (isEmpty()) {
        return; 
    }

    LoanNode* temp = head;   
    head = head->next;       

    if (head == nullptr) {
        tail = nullptr;
    }

    len--;

    temp->next = nullptr;
}
