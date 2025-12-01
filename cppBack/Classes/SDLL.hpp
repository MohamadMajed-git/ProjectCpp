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
        string token;
        Node *next=nullptr;

    };
    Node *head;
    Node *tail;
    public:
    SLL(){
        head=nullptr;
        tail=nullptr;
    }
    string insertAtB(string name1, string name2, string nationalID, string birthdate, string email, string phone, string password, string address, string job, string accountType);
    string* validateLogin(string email, string password);//linearr search for email and password
    Node* getNodeByEmail(string email);
    string generateToken();
    void insertToken(string email);
    void display();
};