#include <bits/stdc++.h>
using namespace std;

class Vector
{
private:
    int *arr{nullptr};
    int size{};
    int capacity{};

public:
    Vector()
    {
        size = 0;
        capacity = 100;
        arr = new int[capacity]{};
    }

    Vector(int _size)
    {
        if (size < 0)
            size = 1;

        size = _size;
        capacity = _size * 2;
        arr = new int[capacity]{};
    }

    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    int get_size()
    {
        return size;
    }
    int get(int idx)
    {
        assert(0 <= idx && idx < size);
        return arr[idx];
    }

    void set(int idx, int val)
    {
        assert(0 <= idx && idx < size);
        arr[idx] = val;
    }

    void print()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    int find(int val)
    {
        for (int i = 0; i < size; i++)
            if (arr[i] == val)
                return i;

        return -1;
    }

    int get_front()
    {
        return arr[0];
    }
    int get_back()
    {
        return arr[size - 1];
    }

    void push_back(int val)
    {
        if (size == capacity)
            expand_capacity();

        arr[size++] = val;
    }

    void expand_capacity()
    {
        capacity *= 2;
        int *newArr = new int[capacity]{};

        for (int i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }

        swap(arr, newArr);

        delete[] newArr;
    }

    void insert(int idx, int val)
    {
        assert(0 <= idx && idx < size);
        if (size == capacity)
            expand_capacity();

        size++;
        for (int i = size - 1; i > idx; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[idx] = val;
    }

    int pop(int idx)
    {
        assert(0 <= idx && idx < size);
        int temp = arr[idx];

        for (int i = idx; i < size - 1; i++)
            arr[i] = arr[i + 1];
        size--;
        return temp;
    }

    void left_rotate()
    {
        int first_val = arr[0];
        for (int i = 0; i < size - 1; i++)
            arr[i] = arr[i + 1];
        arr[size - 1] = first_val;
    }

    void right_rotate()
    {
        int last_val = arr[size - 1];

        for (int i = size - 1; i > 0; i--)
            arr[i] = arr[i - 1];
        arr[0] = last_val;
    }

    void right_rotate(int times)
    {
        times %= size;

        while (times--)
            right_rotate();
    }

    int find_transposition(int val)
    {
        int idx = find(val);
        if (idx == -1)
            return -1;

        if (idx > 0)
        {
            swap(arr[idx], arr[idx - 1]);
            return (idx - 1);
        }
        return 0;
    }
};

int main()
{
    Vector v(10);

    for (int i = 0; i < 10; i++)
        v.set(i, i);

    v.print();

    v.right_rotate();
    v.print();

    v.left_rotate();
    v.print();

    v.right_rotate(3);
    v.print();

    cout << v.pop(2) << endl;
    v.print();

    v.find_transposition(0);
    v.print();
    v.find_transposition(0);
    v.print();

    return 0;
}