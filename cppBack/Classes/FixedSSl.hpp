#pragma once
#include <iostream>
#include <string>
#include<crow.h>
#include <vector>
using namespace std;


class FixedSLL {
    private:
    struct FixedNode{
    int id;
    string email;
    string duration;
    long long int amount;
    long long int profit;
    string date;
    int status;
    FixedNode* next=nullptr;

    };
    public:
    FixedNode* head;
    FixedNode* tail;
    int len;

    FixedSLL() {
        head = nullptr;
        tail = nullptr;
    }

    string insertAtB(int id, string email, string duration , long long int amount , long long int profit, string date ,int status);
    string insertAtL(int id, string email, string duration , long long int amount , long long int profit, string date , int status);
    FixedNode* getNodeByEmail(string email);
    void changeStatusByid(int id, int newStatus);
    crow::json::wvalue getAllFixedJSON();
    crow::json::wvalue getFixedByEmailJSON(string email);
    void deleteNodeByEmail(string email);
    bool isEmpty();
    void display();
};