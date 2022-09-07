#include <bits/stdc++.h>
using namespace std;

class Stack
{
private:
    int size{};
    int top1{}, top2{};
    int *array{};

public:
    Stack(int size)
    {
        this->size = size;
        top1 = -1;
        top2 = size;
        array = new int[size];
    }
    ~Stack()
    {
        delete[] array;
    }

    bool isFull()
    {
        return top1 >= top2 - 1;
    }

    bool isEmpty(int id)
    {
        if (id == 1)
            return top1 == -1;
        return top2 == size;
    }

    void push(int id, int value)
    {
        assert(!isFull());

        if (id == 1)
            array[++top1] = value;
        else
            array[--top2] = value;
    }

    int peek(int id)
    {
        assert(!isEmpty(id));

        if (id == 1)
            return array[top1];

        return array[top2];
    }

    int pop(int id)
    {
        assert(!isEmpty(id));
        if (id == 1)
            return array[top1--];
        else
            return array[top2++];
    }

    void display()
    {
        for (int i = top1; i >= 0; i--)
            cout << array[i] << " ";
        cout << "\n";

        for (int i = top2; i < size; i++)
            cout << array[i] << " ";
        cout << "\n";
    }
};

int main()
{
    Stack stack(10);
    stack.push(2, 5);
    stack.push(2, 6);
    cout << stack.pop(2) << endl;
    stack.push(2, 7);
    stack.push(2, 9);

    stack.push(1, 4);
    cout << stack.peek(1) << endl;
    cout << stack.peek(2) << endl;

    stack.push(1, 6);
    stack.push(1, 8);
    stack.push(2, 3);
    stack.display();
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}