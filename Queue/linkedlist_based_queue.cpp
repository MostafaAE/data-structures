#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data{};
    Node *next{};

    Node(int val) : data(val){};
};

class Queue
{
private:
    Node *head{};
    Node *tail{};
    int length{};

public:
    bool isEmpty()
    {
        return !head;
    }

    void add_node(Node *node)
    {
        ++length;
    }

    void delete_node(Node *node)
    {
        --length;
        delete node;
    }

    void enqueue(int val)
    {
        Node *newNode = new Node(val);
        add_node(newNode);

        if (!head)
            head = tail = newNode;
        else
            tail->next = newNode, tail = newNode;
    }

    int dequeue()
    {
        assert(!isEmpty());

        int val = head->data;

        if (head == tail)
        {
            delete_node(head);
            head = tail = nullptr;
        }
        else
        {
            Node *temp = head;
            head = head->next;
            delete_node(temp);
        }
        return val;
    }

    void display()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << endl;
    }
};

int main()
{
    Queue qu;
    assert(qu.isEmpty());

    for (int i = 1; i <= 6; ++i)
    {
        qu.enqueue(i);
        qu.display();
    }
    cout << "\n";

    for (int i = 1; i <= 6; ++i)
    {
        assert(!qu.isEmpty());
        qu.dequeue();
        // qu.display();
    }
    cout << "\n";

    for (int i = 1; i <= 6; ++i)
    {
        qu.enqueue(i);
        qu.display();
    }
    cout << "\n";
    qu.dequeue();
    qu.dequeue();
    qu.dequeue();
    qu.enqueue(7);
    qu.enqueue(8);
    qu.enqueue(9);
    qu.display();
    cout << "\n";
    for (int i = 1; i <= 6; ++i)
    {
        assert(!qu.isEmpty());
        qu.dequeue();
        qu.display();
    }
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}
