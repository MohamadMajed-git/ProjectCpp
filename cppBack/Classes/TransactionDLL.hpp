#pragma once
#include <string>
#include <iostream>
#include <crow.h>
using namespace std;


class TransactionDLL{
    struct TransactionNode{
        int id;
        string senderAccountNumber;
        string receiverAccountNumber;
        int amount;
        string date;
        TransactionNode *next=nullptr;
    };
    TransactionNode *head;
    TransactionNode *tail;
    public:
    TransactionDLL(){
        head=nullptr;
        tail=nullptr;
    }
    void insertTransaction(int id, string senderAccountNumber,string receiverAccountNumber,int amount,string date);
    crow::json::wvalue getUserTransactions(string accountNumber);
    crow::json::wvalue getAllTransactions();
};
