#include <bits/stdc++.h>
using namespace std;

class MinHeap
{
private:
    int *array{};
    int size{};
    int capacity{1000};

    int left(int node)
    {
        int pos = 2 * node + 1;

        return pos >= size ? -1 : pos;
    }

    int right(int node)
    {
        int pos = 2 * node + 2;

        return pos >= size ? -1 : pos;
    }

    int parent(int node)
    {
        return node == 0 ? -1 : (node - 1) / 2;
    }

public:
    MinHeap()
    {
        array = new int[capacity];
        size = 0;
    }

    ~MinHeap()
    {
        delete[] array;
        array = nullptr;
    }

    bool isempty()
    {
        return size == 0;
    }
};

int main()
{
    MinHeap heap;

    return 0;
}