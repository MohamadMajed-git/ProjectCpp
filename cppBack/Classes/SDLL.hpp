#pragma once
#include <iostream>
#include <string>
#include <crow.h>
using namespace std;
class SLL{
    struct Node{
        string name1;
        string name2;
        string accountNumber;
        string nationalID;
        string birthdate;
        string email;
        string phone;
        string password;
        string address;
        string job;
        string accountType;
        string token;
        string createAt;
        string status;
        int balance;
        Node *next=nullptr;

    };
    Node *head;
    Node *tail;
    public:
    SLL(){
        head=nullptr;
        tail=nullptr;
    }
    string insertAtB(string name1, string name2, string nationalID, string birthdate, string email, string phone, string password, string address, string job, string accountType,string currentDate,int balance,string accountNumber);
    string* validateLogin(string email, string password);//linearr search for email and password
    void deleteNodeByEmail(string email);
    Node* getNodeByEmail(string email);
    Node* getNodeByAccountNumber(string accountNumber);
    bool sendMoney(string SenderAccountNumber,string ReceiverAccountNumber,int amount);
    string generateToken();
    string generateRandomInteger(int length);
    void insertToken(string email);
    crow::json::wvalue getDataByEmail(string email);
    string createAccountNumber(string accountType);
    bool checkIfUserExist(string email);
    bool checkPassword(string email, string password);
    bool checkIfAdmin(string email);
    void updatePassword(string email, string newPassword);
    bool isEmpty();
    void display();
};
