#include <vector>
#include <queue>
#include <iostream>
#include <cassert>
using namespace std;

class PriorityQueue
{
private:
	int capacity{1000};
	int *key{};
	int *value{};
	int size{};

	int left(int node)
	{
		int p = 2 * node + 1;
		if (p >= size)
			return -1;
		return p;
	}
	int right(int node)
	{
		int p = 2 * node + 2;
		return p >= size ? -1 : p;
	}
	int parent(int node)
	{
		return node == 0 ? -1 : (node - 1) / 2;
	}

	void heapify_up(int child_pos)
	{
		// stop when parent is smaller (or no parent)
		int par_pos = parent(child_pos);
		if (child_pos == 0 || key[par_pos] > key[child_pos])
			return;

		swap(key[child_pos], key[par_pos]);
		swap(value[child_pos], value[par_pos]);
		heapify_up(par_pos);
	}

	void heapify_down(int parent_pos)
	{ // O(logn)
		int child_pos = left(parent_pos);
		int right_child = right(parent_pos);

		if (child_pos == -1) // no children
			return;
		// is right bigger than left?
		if (right_child != -1 && key[right_child] > key[child_pos])
			child_pos = right_child;

		if (key[parent_pos] < key[child_pos])
		{
			swap(key[parent_pos], key[child_pos]);
			swap(value[parent_pos], value[child_pos]);
			heapify_down(child_pos);
		}
	}

public:
	PriorityQueue()
	{
		key = new int[capacity]{};
		value = new int[capacity]{};
		size = 0;
	}

	~PriorityQueue()
	{
		delete[] key;
		delete[] value;
	}

	int top()
	{
		assert(!isempty());
		return value[0];
	}

	void enqueue(int data, int priority)
	{
		assert(size + 1 <= capacity);
		value[size] = data;
		key[size++] = priority;
		heapify_up(size - 1);
	}

	int dequeue()
	{
		assert(!isempty());
		int ret = value[0];
		key[0] = key[--size];
		value[0] = value[size];

		heapify_down(0);
		return ret;
	}

	bool isempty()
	{
		return size == 0;
	}
};

int main()
{

	PriorityQueue tasks;

	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);
	tasks.enqueue(7761, 7);

	cout << tasks.dequeue() << "\n";
	cout << tasks.dequeue() << "\n";

	tasks.enqueue(1535, 1);
	tasks.enqueue(2815, 2);
	tasks.enqueue(3845, 3);
	tasks.enqueue(3145, 3);

	while (!tasks.isempty())
		cout << tasks.dequeue() << " ";

	return 0;
}

/*
7761
3111
3145 3161 3845 2815 2211 1535 1131

Notice the heap during a heapify-down operation takes an element from bottom
and get it at root then push down.
This means if 2 elements are of same priority, their position in the tree can change randomly
hence we can't guarantee same priority elements to be in the same input order.
For further details: https://stackoverflow.com/questions/19336881/why-isnt-heapsort-stable#:~:text=Heapsort%20is%20not%20stable%20because,the%20last%20of%20the%20list.

"Stable sort algorithms sort elements such that
	order of repeating elements in the input
	is preserved in the output.

	So sorting 1 5 2 5 (assume 1 5A 2 5B) should be 1 2 5A 5B
		If the algorithm guarantee that = Stable sort algorithms
"

Heap sort with its heapify-down will not guarantee that
Heap sort is unstable algorithm


 */
