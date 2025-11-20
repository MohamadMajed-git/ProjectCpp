#pragma once
#include <iostream>
#include <string>
using namespace std;
class SLL{
    struct Node{
        string name1;
        string name2;
        string nationalID;
        string birthdate;
        string email;
        string phone;
        string password;
        string address;
        string job;
        string accountType;
        Node *next=nullptr;
    };
    Node *head;
    Node *tail;
    public:
    SLL(){
        head=nullptr;
        tail=nullptr;
    }
    void insertAtB(string name1, string name2, string nationalID, string birthdate, string email, string phone, string password, string address, string job, string accountType);
    void display();
};