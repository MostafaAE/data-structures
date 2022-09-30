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

    // O(log(n))
    void heapify_up(int child_pos)
    {

        int parent_pos = parent(child_pos);

        // stop when parent is smaller (or no parent)
        if (child_pos == 0 || array[parent_pos] <= array[child_pos])
            return;

        swap(array[parent_pos], array[child_pos]);
        heapify_up(parent_pos);
    }

    void heapify_down(int node = 0)
    {
        int child_pos = left(node);
        int right_child = right(node);

        // the node is a leaf node (no children)
        if (child_pos == -1)
            return;

        // if the node have left and right children
        // get the minimum of them
        if (right_child != -1 && array[right_child] < array[child_pos])
            child_pos = right_child;

        // if the node is greater than the minimum of its children
        // swap it with the minimum and repeat
        if (array[node] > array[child_pos])
        {
            swap(array[node], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    // O(n)
    void heapify()
    {
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify_down(i);
    }

    bool is_heap(int parent_pos = 0)
    {
        if (parent_pos == -1)
            return true;

        int left_child = left(parent_pos);
        int right_child = right(parent_pos);

        if (left_child != -1 && array[parent_pos] > array[left_child])
            return false;
        if (right_child != -1 && array[parent_pos] > array[right_child])
            return false;

        return is_heap(left_child) && is_heap(right_child);
    }

public:
    MinHeap()
    {
        array = new int[capacity]{};
        size = 0;
    }

    MinHeap(vector<int> &elements)
    {
        assert((int)elements.size() <= capacity);
        array = new int[capacity]{};
        size = elements.size();

        for (int i = 0; i < (int)elements.size(); i++)
            array[i] = elements[i];

        heapify();
    }

    ~MinHeap()
    {
        delete[] array;
        array = nullptr;
    }

    void push(int key)
    {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    void pop()
    {
        assert(!isempty());
        array[0] = array[--size];
        heapify_down(0);
    }

    int top()
    {
        assert(!isempty());
        return array[0];
    }

    bool isempty()
    {
        return size == 0;
    }

    void print_less_than(int val, int parent_pos = 0)
    {
        assert(!isempty());

        if (parent_pos == -1 || array[parent_pos] >= val)
            return;

        cout << array[parent_pos] << " ";

        print_less_than(val, left(parent_pos));
        print_less_than(val, right(parent_pos));
    }

    bool is_heap(int *p, int n)
    {
        int old_size = size;
        int *old_array = array;

        array = p;
        size = n;

        bool res = is_heap(0);

        size = old_size;
        array = old_array;
        return res;
    }
};

// O(nlogn)
void heap_sort(vector<int> &elements)
{
    MinHeap heap;
    for (int i = 0; i < elements.size(); ++i)
        heap.push(elements[i]);

    for (int i = 0; i < elements.size(); ++i)
    {
        elements[i] = heap.top();
        heap.pop();
    }
}
int main()
{
    int arr[] = {2, 5, 12, 7, 6, 22, 14, 19, 10, 17, 8, 37, 25, 30};

    vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
    MinHeap heap(v);

    cout << heap.is_heap(arr, 13) << endl; // 1

    // heap.print_less_than(10);

    // vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
    // MinHeap heap(v);

    // while (!heap.isempty()) // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
    // {
    //     cout << heap.top() << " ";
    //     heap.pop();
    // }

    // vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};
    // heap_sort(v);
    // for (int i = 0; i < v.size(); ++i) // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
    //     cout << v[i] << " ";

    // MinHeap heap;
    // vector<int> v{2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30};

    // for (int i = 0; i < v.size(); ++i)
    //     heap.push(v[i]);

    // while (!heap.isempty()) // 2 5 6 7 8 10 12 14 17 19 22 25 30 37
    // {
    //     cout << heap.top() << " ";
    //     heap.pop();
    // }

    cout << "\n\nNO RTE\n";

    return 0;
}