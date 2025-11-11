#include <iostream>
using namespace std;

class Node{
    public:
        int data;
        Node *next;
        Node (int data){
            this->data=data;
            this->next=nullptr;
        }
        Node(){
            next=nullptr;
        }
};


class SLL{
    Node *head;
    public:
    SLL(){
        head=nullptr;
    }
    bool isEmpty(){
        return head==nullptr;
    }

    void InsertAtB(int value){
        Node *newNode=new Node;
        newNode->data=value;
        if(isEmpty()){
            head=newNode;
            return;
        }
        newNode->next=head;
        head=newNode;
    }

    void InsertByIndex(int index,int value){
        Node *newNode=new Node(value);
        if(index==0){
            newNode->next=head;
            head=newNode;
            return;
        }
        Node *cur=head;
        for(int i=0;i<index-1;i++){
            cur=cur->next;
        }
        newNode->next=cur->next;
        cur->next=newNode;

    }


    void display(){
        Node *cur=head;
        while(cur!=nullptr){
            cout<<cur->data<<" ";
            cur=cur->next;
        }
        cout<<endl;
    }

    void R(){
        print(head);
    }
    void print(Node *node){
        if(node==nullptr){
            return;
        }
        print (node->next);
        cout<<node->data<<" ";
    }


};


int main(){
    SLL s1;
    s1.InsertAtB(10);
    s1.InsertAtB(20);
    s1.InsertByIndex(1,15);
    s1.display();

    s1.R();

    return 0;
}