#include <bits/stdc++.h>
using namespace std;

class Deque
{
private:
    int size{};
    int added_elements{};
    int front{}, rear{};
    int *array;

public:
    Deque(int size) : size(size)
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

    int prev(int pos)
    {
        // return (pos-1 +size) %size;

        --pos;
        if (pos == -1)
            pos = size - 1;
        return pos;
    }

    void enqueue_rear(int val)
    {
        assert(!isFull());
        array[rear] = val;
        rear = next(rear);
        added_elements++;
    }

    void enqueue_front(int val)
    {
        assert(!isFull());
        front = prev(front);
        array[front] = val;
        added_elements++;
    }

    int dequeue_front()
    {
        assert(!isEmpty());
        int temp = array[front];
        front = next(front);
        added_elements--;
        return temp;
    }

    int dequeue_rear()
    {
        assert(!isEmpty());
        rear = prev(rear);
        int temp = array[rear];
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
    Deque dq(6);
    dq.enqueue_front(3);
    dq.enqueue_front(2);
    dq.enqueue_rear(4);
    dq.enqueue_front(1);

    dq.display();                       // 1 2 3 4
    cout << dq.dequeue_rear() << endl;  // 4
    dq.display();                       // 1 2 3
    cout << dq.dequeue_front() << endl; // 1
    dq.display();                       // 2 3
    cout << dq.dequeue_rear() << endl;  // 3
    cout << dq.dequeue_front() << endl; // 2
    dq.enqueue_rear(7);
    dq.display(); // 7
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}
