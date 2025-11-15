// #include <iostream>
// using namespace std;

// class Node{
//     public:
//     int data;
//     Node *next;
//     Node(int val){
//         data=val;
//         next=nullptr;
//     }
//     Node(){
//         data=0;
//         next=nullptr;
//     }
// };

// class CLL{
//     Node *head;
//     Node *tail;
//     public:
//     CLL(){
//         head=nullptr;
//         tail=nullptr;
//     }
//     void insertAtB(int value){
//         Node *newNode = new Node(value);
//         if(head==nullptr){
//             head=newNode;
//             tail=newNode;
//             tail->next=head;
//             return;
//         }
//         newNode->next=head;
//         head=newNode;
//         tail->next=head;

//         }
//     void insertAtE(int value){
//         Node *newNode = new Node(value);
//         if(head==nullptr){
//             head=newNode;
//             tail=newNode;
//             tail->next=head;
//             return;
//         }
//         tail->next=newNode;
//         tail=newNode;
//         tail->next=head;
//     }
//     void display(){
//         if(head==nullptr){
//             cout<<"List is empty"<<endl;
//             return;
//         }
//         Node *cur=head;
//         do{
//             cout<<cur->data<<" ";
//             cur=cur->next;
//         }while(cur!=head);
//         cout<<endl;
    
//     }
//     void deleteItem(int value){
//         if(head==nullptr){
//             cout<<"List is empty"<<endl;
//             return;
//         }

//         if(head->data==value){
//             Node *temp=head;
//             head=head->next;
//             tail->next=head;
//             delete temp;
//             return;
//         }

//                 Node *cur=head;
//         do{
//             if(cur->next->data==value){
//                 if(cur->next==tail){
//                     tail=cur;
//                     Node *temp=cur->next;
//                     tail->next=head;
//                     delete temp;
//                     return;
//                 }

//                 Node *temp=cur->next;
//                 cur->next=cur->next->next;

//                 delete temp;
//                 return;
//             }
//             cur=cur->next;
//         }while(cur!=head);
//         cout<<"Item not found"<<endl;
//     }
// };






// int main(){

//     CLL cll;
//     cll.insertAtE(10);
//     cll.insertAtE(20);
//     cll.insertAtB(5);
//     cll.display();
//     cll.deleteItem(20);
//     cll.display();
//     cll.deleteItem(5);
//     cll.display();

//     return 0;
// }












// #include <iostream>
// using namespace std;
// void show(int* value,int size){
//     for(int i=0;i<size;i++){
//         cout<<value[i]<<" ";
//     }
//     cout<<endl;
// }

// int main() {
//     const int size = 5;
//     int value[size] = {5, 3, 8, 6, 2};
//     show(value, size);

//     return 0;
// }







// #include <iostream>
// using namespace std;
// template <class t>
// class Stack{
//     struct Node{
//         t data;
//         Node *next=nullptr;
//     };
//     Node *top;
//     public:
//     Stack(){
//         top=nullptr;
//     }
//     bool isEmpty(){
//         return top==nullptr;
//     }
//     void push(t value){
//         Node *newNode=new Node();
//         newNode->data=value;
//         newNode->next=top;
//         top=newNode;
//     }
//     t pop(){
//         if(isEmpty()){
//             cout<<"stack is empty"<<endl;
//             return -1;
//         }
//         Node *temp=top;
//         t poppedValue=top->data;
//         top=top->next;
//         delete temp;
//         return poppedValue;
//     }
//     t peek(){
//         if(isEmpty()){
//             cout<<"stack is empty"<<endl;
//             return -1;
//         }
//         return top->data;
//     }

//     void display(){
//         if(isEmpty()){
//             cout<<"stack is empty"<<endl;
//             return;
//         }
//         Node *cur=top;
//         while(cur!=nullptr){
//             cout<<cur->data<<" ";
//             cur=cur->next;
//         }
//         cout<<endl;
//     }


// };



// int main(){
//     Stack<int> s;
//     s.push(10);
//     s.push(20);
//     s.push(30);
//     s.display();
//     cout<<"Popped: "<<s.pop()<<endl;
//     s.display();
//     cout<<"Top element: "<<s.peek()<<endl;
//     int x=s.pop();
//     cout<<"Popped: "<<x<<endl;
//     s.display();

// 	for(int i=0;i<1000000000;i++){
// 	s.push(i*10);
// 	}
// 	s.display();







//     return 0;
// }






// #include <iostream>
// using namespace std;
// template<class t>
// class Stack{
// 	struct Node{
// 		t data;
// 		Node *next=nullptr;

// };

// 	Node *top;
// public:
// 	Stack(){
// 	top=nullptr;
// }
// bool isEmpty(){
// 	return top==nullptr;
// }

// void push(t value){
// 	Node *newNode=new Node();
// 	newNode->data=value;
// 	newNode->next=top;
// 	top=newNode;
// }
	
// t pop(){
// 	if(isEmpty()){
// 	cout<<"stack is empty";
// 	return -1;
// }
// 	Node *temp=top;
// 	t popedValue=top->data;
// 	top=top->next;
// 	delete top;
// 	return popedValue;

// }

// t peek(){
// 		if(isEmpty()){
// 	cout<<"stack is empty";
// 	return -1;

// }
// 	return top->data;
// }


// void display(){
// 	Node *cur=top;
// 	while(cur!=nullptr){
// 		cout<<cur->data<<" ";
// 		cur=cur->next;

// }
// 	cout<<endl;
// }







// };



// int main(){

// Stack<int> s1;
// s1.push(10);
// s1.push(20);
// s1.display();
// cout<<s1.pop()<<endl;
// s1.display();
// cout<<s1.peek();






// return 0;
// }



// #include <iostream>
// using namespace std;
// template<class t>
// class Queue{
// 	struct Node{
// 	t data;
// 	Node *next=nullptr;
// };
// 	Node *front;
// 	Node *rear;
// public:
// 	Queue(){
// 	front=rear=nullptr;
// }

// bool isEmpty(){
// 	return front==nullptr&&rear==nullptr;
// }

// void enqueue(t value){
// 	Node *newNode=new Node();
// 	newNode->data=value;
// 	if(isEmpty()){
// 	front=rear=newNode;
// 	return;
// }
// 	rear->next=newNode;
// 	rear=newNode;	
// }
// t dequeue(){
// 	if(isEmpty()){
// 	cout<<"it is empty"<<endl;
// 	return -1;		
// }
// 	if(front==rear){
//         t dequeued=front->data;
// 	delete front;
// 	front=rear=nullptr;
// 	return dequeued;
// }

// 	Node *temp=front;
// 	t dequeued=front->data;
// 	front=front->next;
// 	delete temp;
// 	return dequeued;
// }

// t getFront(){
// 	if(isEmpty()){
// 	return -1;
// }
// 	return front->data;
// }

// t getRear(){
// 	if(isEmpty()){
// 	return -1;
// }
// 	return rear->data;
// }

// void display(){
// 	Node *cur=front;
// 	while(cur!=nullptr){
// 	cout<<cur->data<<" ";
// 	cur=cur->next;	
// }
// 	cout<<endl;
// }

// void search(t value){
// 	Node *cur=front;
// 	while(cur!=nullptr){
// 	if(cur->data==value){
// 	cout<<"it is found : "<<value<<endl;
// 	return;
// }
// 	cur=cur->next;
// }
// 	cout<<"not found"<<endl;
// }






// };

// int main(){

// Queue<int> q;
// q.enqueue(10);
// q.enqueue(20);
// q.display();
// q.search(20);
// q.search(90);
// cout<<q.dequeue()<<endl;
// cout<<q.dequeue()<<endl;
// cout<<q.dequeue()<<endl;
// q.display();

// int *lst;


// return 0;
// }




// #include <iostream>
// using namespace std;

// class Stack{
// int top1;
// int top2;
// int *lst;
// int size;
// public:
// 	Stack(){
// 	size=200;
// 	top1=-1;
// 	top2=size;
// 	lst=new int[size];

// }

// bool isEmpty(){
// 	return top1==-1&&top2==size;
// }
// bool isFull(){
// return top1+1==top2;
// }


// void pushStack1(int value){
// 	if(isFull()){
// 	cout<<"it is full"<<endl;
// 	return;
// }	
// 	if(value<1000){
// 	lst[++top1]=value;
// }
// else{
// cout<<"it i greater than 1000 on stack 1"<<endl;
// }
// }


// void pushStack2(int value){
// 	if(isFull()){
// 	cout<<"it is full"<<endl;
// 	return;
// }	
// 	if(value>1000){
// 	lst[--top2]=value;
// }
// 	else{
// 	cout<<"it i less than 1000 on stack 2"<<endl;
// }

// }

// int size1(){
// 	if(top1>=0){
// 	return top1+1;
// }
// else{
// return 0;
// }
// }

// int size2(){
// 	if(top2<200){
// 	return 200-top2;
// }
// else{
// return 0;
// }
// }

// void display1(){
// 	for(int i=top1;i>=0;i--)
//     cout<<lst[i]<<" ";	
// }
// void display2(){
// 	for(int i=top2;i<size;i++)
// 	cout<<lst[i]<<" ";
// }

// };


// int main(){

// Stack s;
// s.pushStack1(500);
// s.pushStack1(750);
// s.pushStack1(250);
// s.pushStack1(1005);
// s.pushStack2(1060);
// s.pushStack2(1500);
// s.pushStack2(900);
// s.pushStack2(50);
// cout<<s.size2()<<endl;
// cout<<s.size1()<<endl;
// s.display1();
// cout<<endl;
// s.display2();	
// return 0;
// }




// #include <iostream>
// using namespace std;

// class Stack{
// int maxsize;
// int top;
// int *stack;
// public:

// 	Stack(int size){
// 	maxsize=size;
// 	top=-1;
// 	stack=new int[maxsize];
// }

// bool isEmpty(){
// 	return top==-1;
// }
// bool isFull(){
// 	return top==maxsize-1;
// }
// void push(int value){
// 	if(isFull()){
// 		cout<<"stack is full"<<endl;
// 		return;
// }
// 	stack[++top]=value;
	
// }

// int pop(){
// 	if(isEmpty()){
// 	cout<<"it is empty stack"<<endl;
// 	return -1;
// }
// 	return stack[top--];

// }

// void display(){
// 	for(int i=top;i>=0;i--){
// 	cout<<stack[i]<<" ";
// }
// 	cout<<endl;
// }

// int peek(){
// 	if(isEmpty()){
// 	cout<<"it is empty stack"<<endl;
// 	return -1;
// }
// 	return stack[top];
// }

// void search(int value){
// 	if(isEmpty()){
// 	cout<<"it is empty stack"<<endl;
// 	return;
// }
// 	for(int i=0;i<=top;i++){
// 	if(stack[i]==value){
// 	cout<<value<<" it is exist "<<endl;
// 	return;
// }
// }
// 	cout<<value<<" it is not exist "<<endl;
// }
// void clear(){
// 	for(int i=0;i<maxsize;i++){
// 	stack[i]=0;
// }
// top=-1;
// cout<<"stack is cleared"<<endl;
// }

	



// };



// int main(){
// 	Stack s(50);
// 	s.push(10);
// s.push(20);
// s.push(30);
// s.push(40);
// s.display();
// s.pop();
// s.pop();
// s.display();
// s.search(10);
// s.search(70);
// s.clear();
// s.display();

// return 0;
// }



// #include <iostream>
// using namespace std;


// class Queue{
// int front;
// int back;
// int size;
// int *queue;
// int length;


// public:
// 	Queue(int size){
// 	this->size=size;
// 	front=0;
// 	back=this->size-1;
// 	queue=new int[this->size];
// 	length=0;
// }

// bool isEmpty(){
// 	return length==0;
// }
// bool isFull(){
// 	return length==size;
// }

// void enqueue(int value){
// 	if(isFull()){
// 	cout<<"queue is full"<<endl;
// 	return;
// }
// 	back=(back+1)%size;
// 	queue[back]=value;
// 	length++;
// }
// int dequeue(){
// 	if(isEmpty()){
// 	cout<<"queue is empty"<<endl;
// 	return -1;
// }
// 	int dequeuedvalue=queue[front];
// 	front=(front+1)%size;
// 	length--;
// 	return dequeuedvalue;

// }

// void display(){
// 	if(isEmpty()){
// 	cout<<"it is Empty";
// 	return;
// }
// 	int cur=front;
// 	for(int i=0;i<length;i++){
// 	cout<<queue[cur]<<" ";
// 	cur=(cur+1)%size;

// }
// 	cout<<endl;
	
// }

// void search(int value){
// 	if(isEmpty()){
// 	cout<<"queue is empty"<<endl;
// 	return;
// }
// 	int cur=front;
// 	for(int i=0;i<length;i++){
// 	if(queue[cur]==value){
// 	cout<<queue[cur]<<" founded"<<endl;
// 	return;
// }
// 	cur=(cur+1)%size;
// }

// 	cout<<value<<" not found"<<endl;
	
// }



// void clear(){
// 	front=0;
// 	back=size-1;
// 	length=0;
// 	cout<<"queue cleared"<<endl;
// }


// };


// int main(){
// Queue q(20);
// q.enqueue(10);
// q.enqueue(20);
// q.enqueue(30);
// q.display();
// q.dequeue();
// q.display();
// q.search(20);
// q.search(90);
// q.clear();
// q.display();



// return 0;
// }










// #include <iostream>
// using namespace std;
// class Node{	
// 	int data;
// 	Node *next;
// 		public:
// 	Node(int value){
// 	data=value;
// 	next=nullptr;
// }
// 	Node(){
// 	next=nullptr;
// }
// 	void setNext(Node *n){
// 		next=n;
// }
// 	Node* getNext(){
// 	return next;
// }
// 	int getData(){
// 	return data;
// }

// };

// class Queue{
// 	Node* front;
// 	Node* rear;
// 	int length;
// 	public:
// 	Queue(){
// 	front=nullptr;
// 	rear=nullptr;
// 	length=0;
// }
// bool isEmpty(){
// 	return front==0&&rear==0;
// }
// void enqueue(int value){
// 	Node *newNode=new Node(value);
// 	if(isEmpty()){
// 	front=rear=newNode;
// 	length++;
// 	return;
// }
// 	rear->setNext(newNode);
// 	rear=newNode;
// 	length++;
	
// }
// int dequeue(){
// 	Node *temp=front;
// 	if(isEmpty()){
// 	return -1;
// }
// 	if(front==rear){
// 		int dequeued=front->getData();
// 		delete front;
// 		front=rear=nullptr;
// 		length--;
// 		return dequeued;
// 	}
// 	front=front->getNext();
// 	length--;
// 	int dequeued=temp->getData();
// 	delete temp;	
// 	return dequeued;
// }

// void display(){
// 	Node *cur=front;
// 	while(cur!=nullptr){
// 	cout<<cur->getData()<<" ";
// 	cur=cur->getNext();
// }
// 	cout<<endl;
// }
// };



// int main(){
// 	Queue q;
// 	q.enqueue(10);
// 	q.enqueue(20);
// 	q.enqueue(30);
// 	q.display();
// 	q.dequeue();
// 	q.display();


// return 0;
// }



























#include <iostream>
using namespace std;

class Base{
    int x;
    public:
    Base(int val){
        x=val;
        cout<<"Base class constructor called with value: "<<x<<endl;
    }
    virtual void print(){
        cout<<"Base class print function called"<<endl;
    }
    void s(){}
    ~Base(){
        cout<<"Base class destructor called with value: "<<x<<endl;
    }
};
class Derived:public Base{
    int y;
    public:
    Derived(int val1,int val2):Base(val1){
        y=val2;
        cout<<"Derived class constructor called with value: "<<y<<endl;
    }
    void print() override{
        cout<<"Derived class print function called"<<endl;
    }
    ~Derived(){
        cout<<"Derived class destructor called with value: "<<y<<endl;
    }
};

int main(){
    Derived d(10,20);
    d.print();
    return 0;
}



















