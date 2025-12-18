#include "FixedSSl.hpp"
#include "../globals.hpp"
#include <iostream>
#include <string>
#include <crow.h>
#include <vector>
#include <random>

using namespace std;


string FixedSLL::insertAtL(int id, string email, string duration , long long int amount , long long int profit, string date , int status) {
    FixedNode* newNode = new FixedNode();
    newNode->id = id;
    newNode->email = email;
    newNode->duration = duration;
    newNode->amount = amount;
    newNode->date = date;
    newNode->profit = profit;
    newNode->status = status;

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next=newNode;
        newNode->next = nullptr;
        tail = newNode;
    }

    return to_string(newNode->id);
}

string FixedSLL::insertAtB(int id, string email, string duration , long long int amount , long long int profit, string date ,int status) {
    FixedNode* newNode = new FixedNode();
    newNode->id = id;
    newNode->email = email;
    newNode->duration = duration;
    newNode->amount = amount;
    newNode->date = date;
    newNode->profit = profit;
    newNode->status = status;
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