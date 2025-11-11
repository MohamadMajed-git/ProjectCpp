#include <iostream>
using namespace std;

class SNode
{
public:
    int data;
    SNode *next;
    SNode()
    {
        next = nullptr;
    }
    SNode(int val)
    {
        data = val;
        next = nullptr;
    }
};

class DNode
{
public:
    int data;
    DNode *next;
    DNode *prev;
    DNode()
    {
        next = nullptr;
        prev = nullptr;
    }
    DNode(int val)
    {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class SLL
{
    SNode *head;

public:
    SLL()
    {
        head = nullptr;
    }
    void AddNode(int value)
    {
        SNode *newNode = new SNode(value);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        SNode *cur = head;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = newNode;
    }

    void InsertAtB(int value)
    {
        SNode *newNode = new SNode(value);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    void InsertByIndex(int index, int value)
    {
        SNode *newNode = new SNode(value);
        if (index == 0)
        {
            newNode->next = head;
            head = newNode;
            return;
        }
        SNode *cur = head;
        for (int i = 0; i < index - 1; i++)
        {
            if (cur->next == nullptr)
            {
                cout << "Index out of bounds" << endl;
                return;
            }
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
    }

    void deleteItem(int value)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        if (head->data == value)
        {
            SNode *temp = head;
            head = head->next;
            delete temp;
            return;
        }
        SNode *cur = head;
        while (cur->next != nullptr &&cur->next->data != value)
        {
            cur = cur->next;
        }
        if (cur->next == nullptr)
        {
            cout << "Item not found" << endl;
            return;
        }
        SNode *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
    }

    void Search(int value)
    {
        SNode *cur = head;
        while (cur != nullptr)
        {
            if (cur->data == value)
            {
                cout << "Item found  " << value << endl;
                return;
            }
            cur = cur->next;
        }
        cout << "Item not found" << endl;
    }

    void display()
    {
        SNode *cur = head;
        while (cur != nullptr)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

class DLL
{
    DNode *head;
    DNode *tail;

public:
    DLL()
    {
        head = nullptr;
        tail = nullptr;
    }

    void AddNode(int value)
    {
        DNode *newNode = new DNode(value);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void InsertAtB(int value)
    {
        DNode *newNode = new DNode(value);
        if (head == nullptr)
        {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }

    void InsertByIndex(int index, int value)
    {
        DNode *newNode = new DNode(value);
        if (index == 0)
        {
            InsertAtB(value);
            return;
        }
        DNode *cur = head;
        for (int i = 0; i < index - 1; i++)
        {
            if (cur->next == nullptr)
            {
                cout << "Index out of bounds" << endl;
                return;
            }
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next->prev = newNode;
        newNode->prev = cur;
        cur->next = newNode;
    }
    void deleteItem(int value)
    {
        if (head == nullptr)
        {
            cout << "List is empty" << endl;
            return;
        }
        if (head->data == value)
        {
            DNode *temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
            return;
        }
        if (tail->data == value)
        {
            DNode *temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
            return;
        }
        DNode *cur = head;
        while (cur->next != nullptr &&cur->next->data != value )
        {
            cur = cur->next;
        }
        if (cur->next == nullptr)
        {
            cout << "Item not found" << endl;
            return;
        }

        DNode *temp = cur->next;
        cur->next = cur->next->next;
        cur->next->prev = cur;
        delete temp;
    }

    void Search(int value)
    {
        DNode *cur = head;
        while (cur != nullptr)
        {
            if (cur->data == value)
            {
                cout << "Item found  " << value << endl;
                return;
            }
            cur = cur->next;
        }
        cout << "Item not found" << endl;
    }

    void display()
    {
        DNode *cur = head;
        while (cur != nullptr)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

class Stack
{
    DNode *head;
    DNode *tail;
    int top;

public:
    Stack()
    {
        head = nullptr;
        tail = nullptr;
        top = -1;
    }
    bool isEmpty()
    {
        return top == -1;
    }
    void push(int value)
    {
        DNode *newNode = new DNode(value);
        if (head == nullptr)
        {
            head = tail = newNode;
            top++;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        top++;
    }
    void pop()
    {
        if (isEmpty())
        {
            cout << "Stack underflow" << endl;
            return;
        }
        if(head==tail){
            delete head;
            head=tail=nullptr;
            top--;
            return;
        }
        DNode *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete temp;
        top--;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        DNode *cur = head;
        while (cur != nullptr)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    void Clear()
    {
        DNode *cur = head;
        while (cur != nullptr)
        {
            DNode *temp = cur;
            cur = cur->next;
            delete temp;
            top--;
        }
        head = nullptr;
        tail = nullptr;
        top = -1;
    }
    int peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return -1;
        }
        return tail->data;
    }
};

class Queue
{

    DNode *head;
    DNode *tail;

public:
    Queue()
    {

        head = nullptr;
        tail = nullptr;
    }
    bool isEmpty()
    {
        return head == nullptr;
    }
    void enqueue(int value)
    {
        DNode *newNode = new DNode(value);
        if (isEmpty())
        {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue underflow" << endl;
            return;
        }
        DNode *temp = head;
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        delete temp;
    }
    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        DNode *cur = head;
        while (cur != nullptr)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
    void rear()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Rear element: " << tail->data << endl;
    }
    void front()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Front element: " << head->data << endl;
    }

    void Clear()
    {
        DNode *cur = head;
        while (cur != nullptr)
        {
            DNode *temp = cur;
            cur = cur->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
    }
};

int main()
{

    SLL s1;
    s1.AddNode(10);
    s1.AddNode(20);
    s1.AddNode(30);
    s1.display();
    s1.InsertAtB(5);
    s1.display();
    s1.InsertByIndex(2, 25);
    s1.display();
    s1.deleteItem(30);
    s1.display();
    s1.Search(25);
    s1.Search(40);

    cout << "-----------------------" << endl;

    DLL d1;
    d1.AddNode(10);
    d1.AddNode(20);
    d1.AddNode(30);
    d1.display();
    d1.InsertAtB(5);
    d1.display();
    d1.InsertByIndex(2, 25);
    d1.display();
    d1.deleteItem(30);
    d1.display();
    d1.Search(25);
    d1.Search(40);

    cout << "-----------------------" << endl;

    Stack s2;
    s2.push(10);
    s2.push(20);
    s2.push(30);
    s2.display();
    s2.pop();
    s2.display();
    cout << "Top element " << s2.peek() << endl;
    s2.Clear();
    s2.display();

    cout << "-----------------------" << endl;
    Queue q1;
    q1.enqueue(10);
    q1.enqueue(20);
    q1.enqueue(30);
    q1.display();
    q1.dequeue();
    q1.display();
    q1.front();
    q1.rear();
    q1.Clear();
    q1.display();
    return 0;
}
