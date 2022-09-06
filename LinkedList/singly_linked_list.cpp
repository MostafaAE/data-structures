#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data{};
    Node *next{};

    Node(int val) : data(val){};
    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};
class LinkedList
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
    LinkedList() {}
    LinkedList(const LinkedList &) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;

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
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    // visualize nodes
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
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
            assert(len < 10000); // Consider infinite cycle?
        assert(length == len);
        assert(length == (int)debug_data.size());
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
        cout << endl;
    }

    void print_recursive(Node *head)
    {
        if (head == nullptr)
            return;
        cout << head->data << endl;
        print_recursive(head->next);
    }

    void print_recursive_reverse(Node *head)
    {
        if (head == nullptr)
            return;

        print_recursive_reverse(head->next);
        cout << head->data << endl;
    }

    void insert_end(int val)
    {
        Node *newNode = new Node(val);
        add_node(newNode);

        if (!head)
            head = tail = newNode;
        else
            tail->next = newNode, tail = newNode;
    }

    void insert_front(int val)
    {
        Node *newNode = new Node(val);
        add_node(newNode);
        if (!head)
            head = tail = newNode;
        else
            newNode->next = head, head = newNode;
    }
};

//******************************************************//
// test functions
void test_insert_end()
{
    cout << "\n\ntest1\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    // some actions
    list.print();

    string expected = "1 2 3";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_insert_front()
{
    cout << "\n\ntest2\n";
    LinkedList list;

    list.insert_front(1);
    list.insert_front(2);
    list.insert_front(3);
    list.insert_front(4);
    // some actions
    list.print();

    string expected = "4 3 2 1";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

//******************************************************//
int main()
{
    // test_insert_end();
    test_insert_front();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}