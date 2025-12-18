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
        long long int balance;
        Node *next=nullptr;

    };
    Node *head;
    Node *tail;
    long long int count;
    long long int senderBalance;

    public:
    SLL(){
        head=nullptr;
        tail=nullptr;
        count=0;
    }
    string insertAtB(string name1, string name2, string nationalID, string birthdate, string email, string phone, string password, string address, string job, string accountType,string currentDate,int balance,string accountNumber,string status);
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
    int getTotalBalance();
    int getUserCount();
    void setTotalBalance(int balance);
    bool isActive(string accountNumber);
    bool isActiveByEmail(string email);
    bool isEmpty();
    void display();
};
