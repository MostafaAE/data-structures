#include <bits/stdc++.h>
using namespace std;

class Stack
{
private:
    int size{};
    int top{};
    int *array{};

public:
    Stack(int size)
    {
        this->size = size;
        top = -1;
        array = new int[size];
    }

    bool isFull()
    {
        return top == size - 1;
    }

    bool isEmpty()
    {
        return top == -1;
    }

    void push(int value)
    {
        assert(!isFull());

        array[++top] = value;
    }

    int peek()
    {
        assert(!isEmpty());

        return array[top];
    }

    int pop()
    {
        assert(!isEmpty());
        return array[top--];
    }

    void display()
    {
        for (int i = top; i >= 0; i--)
            cout << array[i] << " ";
        cout << "\n";
    }

    void insert_at_bottom_iterative(int value)
    {
        assert(!isFull());
        top++;
        for (int i = top; i > 0; i--)
            array[i] = array[i - 1];
        array[0] = value;
    }

    void insert_at_bottom(int value)
    {
        if (isEmpty())
        {
            push(value);
            return;
        }

        int cur = pop();
        insert_at_bottom(value);
        push(cur);
    }
};

int main()
{
    Stack stack(5);
    stack.push(10);
    stack.push(20);
    stack.push(30);

    // cout << stack.isFull() << endl;
    // cout << stack.peek() << endl;
    // stack.display();
    // stack.pop();

    // cout << stack.isFull() << endl;
    // cout << stack.peek() << endl;
    stack.display();

    stack.insert_at_bottom_iterative(40);
    stack.insert_at_bottom(50);
    stack.display();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}