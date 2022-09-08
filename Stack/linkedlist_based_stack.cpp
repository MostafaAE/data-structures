#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int val) : data(val){};
};

class Stack
{
private:
    Node *head{};

public:
    ~Stack()
    {
        while (!isEmpty())
            pop();
    }
    void push(int value)
    {
        Node *item = new Node(value);
        assert(item);
        item->next = head;
        head = item;
    }

    bool isEmpty()
    {
        return !head;
    }

    int pop()
    {
        assert(!isEmpty());

        Node *temp = head;
        int value = temp->data;
        head = head->next;
        delete temp;
        return value;
    }

    int peek()
    {
        assert(!isEmpty());
        int value = head->data;
        return value;
    }

    void display()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }
};
int main()
{

    Stack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    stack.display();              // 30 20 10
    cout << stack.peek() << "\n"; // 30

    while (!stack.isEmpty())
        cout << stack.pop() << " ";
    // 30 20 10
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}