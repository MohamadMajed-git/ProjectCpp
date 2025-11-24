#include "SDLL.hpp"
#include <iostream>
#include <string>
#include <random>

using namespace std;

string SLL::insertAtB(string name1, string name2, string nationalID, string birthdate, string email, string phone, string password, string address, string job, string accountType)
{
    Node *newNode = new Node();
    newNode->name1 = name1;
    newNode->name2 = name2;
    newNode->nationalID = nationalID;
    newNode->birthdate = birthdate;
    newNode->email = email;
    newNode->phone = phone;
    newNode->password = password;
    newNode->address = address;
    newNode->job = job;
    newNode->accountType = accountType;
    newNode->token = generateToken();

    if (head == nullptr)
    {
        head = tail = newNode;
        return newNode->token;
    }
    newNode->next = head;
    head = newNode;
    return newNode->token;
}
void SLL::display()
{
    if (head == nullptr)
    {
        cout << "List is empty" << endl;
        return;
    }
    Node *cur = head;
    while (cur != nullptr)
    {
        cout << cur->name1 << " " << cur->name2 << " " << cur->nationalID << " " << cur->birthdate << " " << cur->email << " " << cur->phone << " " << cur->password << " " << cur->address << " " << cur->job << " " << cur->accountType << endl;
        cur = cur->next;
    }
}
string SLL::validateLogin(string email, string password)
{
    Node *cur = head;
    while (cur != nullptr)
    {
        if (cur->email == email && cur->password == password)
        {
            cur->token = generateToken();
            return cur->token;
        }
        cur = cur->next;
    }
    return "";
}





SLL::Node* SLL::getNodeByEmail(string email)
{
    Node *cur = head;
    while (cur != nullptr)
    {
        if (cur->email == email)
        {
            return cur;
        }
        cur = cur->next;
    }
    return nullptr;
}

string SLL::generateToken()
{
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0,25);
    string token = "";
    for(int i=0;i<26;i++){
        token+=(char)('A'+ dis(gen));
    }
    return token;
}
