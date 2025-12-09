#include "TransactionDLL.hpp"
#include <iostream>
#include "../globals.hpp"
#include <vector>
using namespace std;
using namespace crow;

void TransactionDLL::insertTransaction(int id, string senderAccountNumber,string receiverAccountNumber,int amount,string date)
{
    TransactionNode *newNode = new TransactionNode();
    newNode->id = id;
    newNode->senderAccountNumber = senderAccountNumber;
    newNode->receiverAccountNumber = receiverAccountNumber;
    newNode->amount = amount;
    newNode->date = date;

    if (head == nullptr)
    {
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

crow::json::wvalue TransactionDLL::getUserTransactions(string accountNumber)
{
    json::wvalue transactions;
    TransactionNode* cur = head;
    vector<json::wvalue> userTransactions;
    while (cur != nullptr)
    {
        if (cur->senderAccountNumber == accountNumber || cur->receiverAccountNumber == accountNumber){
            json::wvalue transaction;
            transaction["id"] = cur->id;
            transaction["senderAccountNumber"] = cur->senderAccountNumber;
            transaction["receiverAccountNumber"] = cur->receiverAccountNumber;
            transaction["amount"] = cur->amount;
            transaction["date"] = cur->date;
            userTransactions.push_back(transaction);
        }
        cur = cur->next;
    }
    return crow::json::wvalue(userTransactions);
}

json::wvalue TransactionDLL::getAllTransactions()
{
    json::wvalue transactions;
    TransactionNode* cur = head;
    vector<json::wvalue> allTransactions;
    while (cur != nullptr)
    {
            json::wvalue transaction;
            transaction["id"] = cur->id;
            transaction["senderAccountNumber"] = cur->senderAccountNumber;
            transaction["receiverAccountNumber"] = cur->receiverAccountNumber;
            transaction["amount"] = cur->amount;
            transaction["date"] = cur->date;
            allTransactions.push_back(transaction);
        cur = cur->next;
    }
    return crow::json::wvalue(allTransactions);
}



