#include <bits/stdc++.h>
using namespace std;

class Queue
{
private:
    int size{};
    int added_elements{};
    int front{}, rear{};
    int *array;

public:
    Queue(int size) : size(size)
    {
        array = new int[size];
    };

    bool isFull()
    {
        return added_elements == size;
    }

    bool isEmpty()
    {
        return added_elements == 0;
    }

    int next(int pos)
    {
        // return (pos + 1) % size;

        ++pos;
        if (pos == size)
            pos = 0;
        return pos;
    }
    void enqueue(int val)
    {
        assert(!isFull());
        array[rear] = val;
        rear = next(rear);
        added_elements++;
    }

    int dequeue()
    {
        assert(!isEmpty());
        int temp = array[front];
        front = next(front);
        added_elements--;
        return temp;
    }

    void display()
    {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty())
        {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";

        for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            cout << array[cur] << " ";
        cout << "\n\n";
    }
};

int main()
{
    Queue qu(6);
    assert(qu.isEmpty());
    qu.display();

    for (int i = 1; i <= 6; ++i)
    {
        assert(!qu.isFull());
        qu.enqueue(i);
        qu.display();
    }
    assert(qu.isFull());

    for (int i = 1; i <= 6; ++i)
    {
        assert(!qu.isEmpty());
        qu.dequeue();
        // qu.display();
    }

    for (int i = 1; i <= 6; ++i)
    {
        assert(!qu.isFull());
        qu.enqueue(i);
        qu.display();
    }

    qu.dequeue();
    assert(!qu.isFull());
    qu.enqueue(7);
    assert(qu.isFull());
    qu.display();

    qu.dequeue();
    qu.dequeue();
    assert(!qu.isFull());
    qu.enqueue(8);
    assert(!qu.isFull());
    qu.display();
    qu.enqueue(9);
    assert(qu.isFull());
    qu.display();

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

/*
Front 0 - rear 0	empty

Front 0 - rear 1
1

Front 0 - rear 2
1 2

Front 0 - rear 3
1 2 3

Front 0 - rear 4
1 2 3 4

Front 0 - rear 5
1 2 3 4 5

Front 0 - rear 0	full
1 2 3 4 5 6

Front 0 - rear 1
1

Front 0 - rear 2
1 2

Front 0 - rear 3
1 2 3

Front 0 - rear 4
1 2 3 4

Front 0 - rear 5
1 2 3 4 5

Front 0 - rear 0	full
1 2 3 4 5 6

Front 1 - rear 1	full
2 3 4 5 6 7

Front 3 - rear 2
4 5 6 7 8

Front 3 - rear 3	full
4 5 6 7 8 9

Front 4 - rear 3
5 6 7 8 9

Front 5 - rear 3
6 7 8 9

Front 0 - rear 3
7 8 9

Front 1 - rear 3
8 9

Front 2 - rear 3
9

Front 3 - rear 3	empty
*/