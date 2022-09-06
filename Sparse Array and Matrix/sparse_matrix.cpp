#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int index{}, data{};
    Node *next{}, *prev{};

    Node(int data, int index) : data(data), index(index){};
    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }
    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class ArrayLinkedList
{
private:
    Node *head{};
    Node *tail{};
    int size{};

public:
    // delete copy and assign to prevent memory leaks and dangling pointers
    // ArrayLinkedList() {}

    ArrayLinkedList(int size) : size(size){};
    ArrayLinkedList(const ArrayLinkedList &) = delete;
    ArrayLinkedList &operator=(const ArrayLinkedList &another) = delete;

    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void set_value(int value, int index)
    {
        if (index >= size || index < 0)
            return;

        Node *new_node = new Node(value, index);

        if (!head)
        {
            head = tail = new_node;
            return;
        }

        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->index == index)
            {
                cur->data = value;
                return;
            }
            else if (cur->index > index)
            {
                link(cur->prev, new_node);
                link(new_node, cur);
                if (cur == head)
                    head = head->prev;
                return;
            }
        }
        link(tail, new_node);
        new_node->next = nullptr;
        tail = new_node;
    }

    void print_array()
    {
        Node *cur = head;
        for (int i = 0; i < size; i++)
        {
            if (cur && cur->index == i)
            {
                cout << cur->data << " ";
                cur = cur->next;
            }
            else
                cout << 0 << " ";
        }

        cout << "\n";
    }

    void print_array_nonzero()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    int get_value(int index)
    {
        if (index >= size || index < 0)
            return 0;

        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->index == index)
                return cur->data;
            else if (cur->index > index)
                break;
        }
        return 0;
    }
    void add(ArrayLinkedList &other)
    {
        if (size != other.size)
            return;

        Node *cur = head, *other_cur = other.head;
        while (cur && other_cur)
        {
            if (cur->index == other_cur->index)
            {
                cur->data += other_cur->data;
                cur = cur->next;
                other_cur = other_cur->next;
            }
            else if (cur->index > other_cur->index)
            {
                set_value(other_cur->data, other_cur->index);
                other_cur = other_cur->next;
            }

            else if (cur->index < other_cur->index)
                cur = cur->next;
        }
        while (other_cur)
        {
            set_value(other_cur->data, other_cur->index);
            other_cur = other_cur->next;
        }
    }

    Node *get_head()
    {
        return head;
    }
};

struct RowNode
{
    int row_index{};
    ArrayLinkedList col_list;

    RowNode *next{}, *prev{};

    RowNode(int row, int cols) : row_index(row), col_list(cols){};
};

class SparseMatrix
{
private:
    RowNode *head{};
    RowNode *tail{};
    int rows{}, cols{};

public:
    SparseMatrix(int rows, int cols) : rows(rows), cols(cols){};
    SparseMatrix(const SparseMatrix &) = delete;
    SparseMatrix &operator=(const SparseMatrix &another) = delete;

    void link(RowNode *first, RowNode *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void set_value(int value, int row, int col)
    {
        if (row >= rows || row < 0 || col >= cols || col < 0)
            return;

        RowNode *new_rownode = new RowNode(row, cols);
        new_rownode->col_list.set_value(value, col);

        if (!head)
        {
            head = tail = new_rownode;
            return;
        }

        for (RowNode *cur = head; cur; cur = cur->next)
        {
            if (cur->row_index == row)
            {
                cur->col_list.set_value(value, col);
                return;
            }
            else if (cur->row_index > row)
            {
                link(cur->prev, new_rownode);
                link(new_rownode, cur);
                if (cur == head)
                    head = head->prev;
                return;
            }
        }
        link(tail, new_rownode);
        new_rownode->next = nullptr;
        tail = new_rownode;
    }

    void print_matrix()
    {
        RowNode *cur = head;
        for (int i = 0; i < rows; i++)
        {
            if (cur && cur->row_index == i)
            {
                cur->col_list.print_array();
                cur = cur->next;
            }
            else
            {
                for (int j = 0; j < cols; j++)
                    cout << 0 << " ";
                cout << "\n";
            }
        }
    }

    void print_matrix_nonzero()
    {
        for (RowNode *cur = head; cur; cur = cur->next)
            cur->col_list.print_array_nonzero();
    }

    void add(SparseMatrix &other)
    {
        if (rows != other.rows && cols != other.cols)
            return;

        RowNode *cur = head, *other_cur = other.head;
        while (cur && other_cur)
        {
            if (cur->row_index == other_cur->row_index)
            {
                cur->col_list.add(other_cur->col_list);
                cur = cur->next;
                other_cur = other_cur->next;
            }
            else if (cur->row_index > other_cur->row_index)
            {
                for (Node *cur = other_cur->col_list.get_head(); cur; cur = cur->next)
                    set_value(cur->data, other_cur->row_index, cur->index);
                other_cur = other_cur->next;
            }

            else if (cur->row_index < other_cur->row_index)
                cur = cur->next;
        }
        while (other_cur)
        {
            for (Node *cur = other_cur->col_list.get_head(); cur; cur = cur->next)
                set_value(cur->data, other_cur->row_index, cur->index);
            other_cur = other_cur->next;
        }
    }
};

int main()
{
    SparseMatrix mat(10, 10);
    SparseMatrix mat2(10, 10);
    mat.set_value(5, 3, 5);
    mat.set_value(7, 3, 7);
    mat.set_value(2, 3, 2);
    mat.set_value(0, 3, 2);
    mat.set_value(6, 5, 6);
    mat.set_value(4, 5, 4);
    mat.set_value(3, 7, 3);
    mat.set_value(1, 7, 1);

    mat2.set_value(5, 1, 9);
    mat2.set_value(6, 3, 8);
    mat2.set_value(9, 9, 9);
    // mat.print_matrix();
    // mat.print_matrix_nonzero();

    mat.add(mat2);
    mat.print_matrix_nonzero();
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}