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




























