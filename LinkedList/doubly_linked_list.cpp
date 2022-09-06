#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data{};
    Node *next{}, *prev{};

    Node(int val) : data(val){};
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

class DoublyLinkedList
{
private:
    Node *head{};
    Node *tail{};
    int length{};

    vector<Node *> debug_data; // add/remove nodes you use

    void debug_add_node(Node *node)
    {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node *node)
    {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }

public:
    // delete copy and assign to prevent memory leaks and dangling pointers
    DoublyLinkedList() {}
    DoublyLinkedList(const DoublyLinkedList &) = delete;
    DoublyLinkedList &operator=(const DoublyLinkedList &another) = delete;

    //******************************************************//
    // These functions are used to debugging and checking data integrity

    // print each node address and value
    void debug_print_address()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }

    void debug_print_node(Node *node, bool is_seperate = false)
    {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr)
        {
            cout << "nullptr\n";
            return;
        }

        if (node->prev == nullptr)
            cout << "X\t";
        else
            cout << node->prev->data << "\t";

        cout << " <= [" << node->data << "]\t => \t";

        if (node->next == nullptr)
            cout << "X\t";
        else
            cout << node->next->data << "\t";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    void debug_print_list(string msg = "")
    {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int)debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n"
             << flush;
    }

    string debug_to_string()
    {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node *cur = head; cur; cur = cur->next)
        {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
        {
            if (len == length - 1) // make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        assert(length == (int)debug_data.size());

        len = 0;
        for (Node *cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == length - 1) // make sure we end at head
                assert(cur == head);
        }
        cout << "\n";
    }

    // These 2 simple functions just to not forget changing the vector and length
    void delete_node(Node *node)
    {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node *node)
    {
        debug_add_node(node);
        ++length;
    }
    //******************************************************//

    //******************************************************//
    // main operations
    void print()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void print_reversed()
    {
        for (Node *cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    void insert_end(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(tail, item);
            tail = item;
        }
        debug_verify_data_integrity();
    }

    void insert_front(int value)
    {
        Node *item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        debug_verify_data_integrity();
    }

    void embed_after(Node *node_before, int value)
    {
        // Add a node with value between node and its next
        Node *middle = new Node(value);
        ++length;
        debug_add_node(middle);

        Node *node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
    }
};

//******************************************************//
int main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}