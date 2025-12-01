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
string* SLL::validateLogin(string email, string password)
{
    Node *cur = head;
    
    while (cur != nullptr)
    {
        if (cur->email == email && cur->password == password)
        {
            cur->token = generateToken();
            string *lst=new string[11];
            lst[0]=(string)cur->name1;
            lst[1]=(string)cur->name2;
            lst[2]=(string)cur->nationalID;
            lst[3]=(string)cur->birthdate;
            lst[4]=(string)cur->email;
            lst[5]=(string)cur->phone;
            lst[6]=(string)cur->password;
            lst[7]=(string)cur->address;
            lst[8]=(string)cur->job;
            lst[9]=(string)cur->accountType;
            lst[10]=(string)cur->token;
            return lst;
            
        }
        cur = cur->next;
    }
    return nullptr;
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
