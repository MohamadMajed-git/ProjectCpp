// #include <iostream>
// using namespace std;

// class Node{
//     public :
//     int data;
//     Node *next=nullptr;
//     Node(int value){
//         data=value;
//     }
// };

// class Queue{
//     Node *front;
//     Node *rear;
//     public:
//     Queue(){
//         front=nullptr;
//         rear=nullptr;
//     }
//     void enqueue(int value){
//         Node *newNode=new Node(value);
//         if(front==nullptr){
//             front=rear=newNode;
//             return;
//         }
//         rear->next=newNode;
//         rear=newNode;
//     }
//     int dequeue(){
//         if(isEmpty()){
//             cout<<"Queue is empty"<<endl;
//             return -1;
//         }
//         Node *temp=front;
//         front=front->next;
//         int dequeuedValue=temp->data;
//         delete temp;
//         return dequeuedValue;    
//     }

//     int queueSize(){
//         int size=0;
//         Node *cur=front;
//         while(cur!=nullptr){
//             size++;
//             cur=cur->next;
//         }
//         return size;
//     }
//     void display(){
//         Node *cur=front;
//         while(cur!=nullptr){
//             cout<<cur->data<<endl;
//             cur=cur->next;
//         }
//         cout<<endl;
//     }

//     bool isEmpty(){
//         return front==nullptr;
//     }
//     int Dfront(){
//         if(isEmpty()){
//             cout<<"Queue is empty"<<endl;
//             return -1;
//         }
//         return front->data;
//     }
//     int Drear(){
//         if(isEmpty()){
//             cout<<"Queue is empty"<<endl;
//             return -1;
//         }
//         return rear->data;
//     }
// };




// int main(){
//     Queue q;
//     q.enqueue(10);
//     q.enqueue(20);
//     q.enqueue(30);
//     q.display();
//     cout<<"Dequeued: "<<q.dequeue()<<endl;
//     q.display();
//     cout<<"Front: "<<q.Dfront()<<endl;
//     cout<<"Rear: "<<q.Drear()<<endl;
//     cout<<"Size: "<<q.queueSize()<<endl;



//     return 0;
// }







#include <iostream>
using namespace std;

class Queue{
    int maxSize;
    int front;
    int rear;
    int *list;
    int count;
    public:
    Queue(int size){
        maxSize=size;
        front=0;
        rear=-1;
        count=0;
        list=new int[maxSize];
    }
    bool isEmpty(){
        return count==0;
    }
    bool isFull(){
        return count==maxSize;
    }
    int queueSize(){
        return count;
    }   
    int enqueue(int value){
        if(isFull()){
            cout<<"Queue Overflow"<<endl;
            return -1;
        }
        rear=(rear+1) % maxSize;
        list[rear]=value;
        count++;
        return value;
    }
    int dequeue(){
        if(isEmpty()){
            cout<<"Queue Underflow"<<endl;
            return -1;
        }
        int dequeuedValue=list[front];
        front=(front+1) % maxSize;
        count--;
        return dequeuedValue;
    }
    int getFront(){
        if(isEmpty()){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        return list[front];
    }
    int getRear(){
        if(isEmpty()){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        return list[rear];
    }
    void display(){
        if(isEmpty()){
            cout<<"Queue is empty"<<endl;
            return;
        }
        for(int i=0;i<count;i++){
            cout<<list[(front+i)%maxSize]<<endl;
        }
        cout<<endl;
    }
};

int main(){
    Queue q(5);
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);
    q.enqueue(60);
    q.display();
    cout<<"Dequeued: "<<q.dequeue()<<endl;
    cout<<"Dequeued: "<<q.dequeue()<<endl;
    q.display();
    q.enqueue(60);
    q.enqueue(70);
    q.display();
    cout<<"Front: "<<q.getFront()<<endl;
    cout<<"Rear: "<<q.getRear()<<endl;
    cout<<"Size: "<<q.queueSize()<<endl;

    return 0;
}



