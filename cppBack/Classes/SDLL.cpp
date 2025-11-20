 #include "SDLL.hpp"
#include <iostream>
using namespace std;
 
 void SLL::insertAtB(string name1, string name2, string nationalID, string birthdate, string email, string phone, string password, string address, string job, string accountType){
        Node *newNode=new Node();
        newNode->name1=name1;
        newNode->name2=name2;
        newNode->nationalID=nationalID;
        newNode->birthdate=birthdate;
        newNode->email=email;
        newNode->phone=phone;
        newNode->password=password;
        newNode->address=address;
        newNode->job=job;
        newNode->accountType=accountType;

        if(head==nullptr){
            head=tail=newNode;
            return;
        }
        newNode->next=head;
        head=newNode;
    }
    void SLL::display(){
        if(head==nullptr){
            cout<<"List is empty"<<endl;
            return;
        }
        Node *cur=head;
        while(cur!=nullptr){
            cout<<cur->name1<<" "<<cur->name2<<" "<<cur->nationalID<<" "<<cur->birthdate<<" "<<cur->email<<" "<<cur->phone<<" "<<cur->password<<" "<<cur->address<<" "<<cur->job<<" "<<cur->accountType<<endl;
            cur=cur->next;
        }
    }