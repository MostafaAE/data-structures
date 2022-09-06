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

    void insert_sorted(int value)
    { // O(n) time - O(1) memory
        // 3 special cases for simplicity
        if (!length || value <= head->data)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else
        {
            // Find the node I am less than. Then I am before it
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (value <= cur->data)
                {
                    embed_after(cur->prev, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();

        // This idea is used in Insertion Sort Algorithm
    }

    void delete_front()
    {
        if (!head)
            return;

        if (head == tail)
        {
            delete_node(head);
            head = tail = nullptr;
        }
        else
        {
            Node *temp = head;
            head->next->prev = nullptr;
            head = head->next;
            delete_node(temp);
        }
    }

    void delete_end()
    {
        if (!head)
            return;

        if (head == tail)
        {
            delete_node(head);
            head = tail = nullptr;
        }
        else
        {
            Node *temp = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete_node(temp);
        }
    }

    Node *delete_and_link(Node *cur)
    {
        Node *ret = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);
        return ret;
    }

    void delete_node_with_key(int val)
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->data == val)
            {

                if (cur == head)
                {
                    delete_front();
                }
                else if (cur == tail)
                {
                    delete_end();
                }
                else
                    delete_and_link(cur);

                return;
            }
        }
    }

    void delete_all_nodes_with_key(int val)
    {
        Node *cur = head, *temp = head;

        while (cur)
        {
            temp = cur;
            cur = cur->next;
            if (temp->data == val)
            {

                if (temp == head)
                {
                    delete_front();
                }
                else if (temp == tail)
                {
                    delete_end();
                }
                else
                    delete_and_link(temp);
            }
        }
    }

    void delete_even_positions()
    {
        if (!head || head == tail)
            return;

        Node *cur = head->next, *to_delete = cur;

        while (cur && cur->next)
        {
            to_delete = cur;
            cur = cur->next->next;
            delete_and_link(to_delete);
        }

        if (cur == tail)
        {
            delete_end();
        }
    }
};
//******************************************************//
// test functions
void test_insert_sorted()
{
    cout << "\n\ntest_insert_sorted\n";
    DoublyLinkedList list;

    list.insert_end(3);
    list.insert_end(5);
    list.insert_end(7);
    list.insert_sorted(2);
    list.insert_sorted(9);
    list.insert_sorted(7);
    list.insert_sorted(4);
    list.insert_sorted(1);

    list.print();
    // list.print_reversed();

    string expected = "1 2 3 4 5 7 7 9";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_delete_front()
{
    cout << "\n\ntest_delete_front\n";
    DoublyLinkedList list;

    list.insert_end(3);
    list.insert_end(5);
    list.insert_end(7);
    list.delete_front();
    list.delete_front();
    list.print();
    // list.print_reversed();

    string expected = "7";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_delete_end()
{
    cout << "\n\ntest_delete_end\n";
    DoublyLinkedList list;

    list.insert_end(3);
    list.insert_end(5);
    list.insert_end(7);
    list.delete_end();
    // list.delete_front();
    list.delete_end();
    list.delete_end();
    list.print();
    // list.print_reversed();

    string expected = "";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_delete_node_with_key()
{
    cout << "\n\ntest_delete_node_with_key\n";
    DoublyLinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.delete_node_with_key(1);
    list.delete_node_with_key(5);
    list.delete_node_with_key(3);
    // list.delete_node_with_key(2);
    // list.delete_node_with_key(4);
    list.print();
    // list.print_reversed();

    string expected = "2 4";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_delete_even_positions()
{
    cout << "\n\ntest5\n";
    DoublyLinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.insert_end(6);
    list.delete_even_positions();

    list.print();
    // list.print_reversed();

    string expected = "1 3 5";
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
    // test_insert_sorted();
    // test_delete_front();
    // test_delete_end();
    // test_delete_node_with_key();
    test_delete_even_positions();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}