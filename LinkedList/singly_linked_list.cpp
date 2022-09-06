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

    void delete_front()
    {
        if (head)
        {
            if (head == tail)
            {
                delete_node(head);
                head = tail = nullptr;
            }
            else
            {
                Node *temp = head;
                head = head->next;
                delete_node(temp);
            }
        }
    }

    void delete_last()
    {
        if (head)
        {
            if (head == tail)
            {
                delete_node(head);
                head = tail = nullptr;
            }
            else
            {
                Node *cur = head;
                while (cur->next != tail)
                {
                    cur = cur->next;
                }

                tail = cur;
                delete_node(cur->next);
                tail->next = nullptr;
            }
        }
    }

    void delete_nth(int n)
    {
        if (1 > n || n > length)
            return;
        n--;
        Node *cur = head, *prev = nullptr;

        while (n--)
        {
            prev = cur;
            cur = cur->next;
        }

        // if first element
        if (cur == head)
            delete_front();
        // if last element
        else if (cur == tail)
            delete_last();
        // in middle
        else
        {
            prev->next = cur->next;
            delete_node(cur);
        }
    }

    void delete_node_with_key(int val)
    {
        int idx = 1;
        for (Node *cur = head; cur; cur = cur->next, idx++)
        {
            if (cur->data == val)
            {
                delete_nth(idx);
                break;
            }
        }
    }

    Node *get_nth(int n)
    {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++cnt == n)
                return cur;
        }

        return nullptr;
    }

    Node *get_nth_back(int n)
    {
        if (n > length || n < 1)
            return nullptr;
        return get_nth(length - n + 1);
    }

    int search(int val)
    {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next, cnt++)
        {
            if (cur->data == val)
                return cnt;
        }
        return -1;
    }
    int improved_search(int val)
    {
        int cnt = 0;
        for (Node *cur = head, *prev = nullptr; cur; prev = cur, cur = cur->next, cnt++)
        {
            if (cur->data == val)
            {
                if (!prev)
                    return cnt;

                swap(cur->data, prev->data);
                return cnt - 1;
            }
        }
        return -1;
    }

    bool is_same(LinkedList &list)
    {
        Node *cur1 = head, *cur2 = list.head;

        while (cur1 && cur2)
        {
            if (cur1->data != cur2->data)
                return false;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        if (cur1 || cur2)
            return false;

        return true;
    }

    void swap_pairs()
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->next)
            {
                swap(cur->data, cur->next->data);
                cur = cur->next;
            }
        }
    }

    void reverse()
    {
        Node *prev{}, *next{};
        for (Node *cur = head; cur; cur = next)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
        }
        swap(head, tail);
    }

    Node *reverse_recursively(Node *cur)
    {
        if (cur && cur->next)
        {
            Node *rem = reverse_recursively(cur->next);
            rem->next = cur;
            cur->next = nullptr;
        }

        return cur;
    }

    void reverse_recursively()
    {
        reverse_recursively(head);
        swap(head, tail);
    }

    void delete_even_positions()
    {
        for (int i = 2; i <= length; i++)
        {
            delete_nth(i);
        }
    }

    void insert_sorted(int val)
    {
        Node *newNode = new Node(val);
        add_node(newNode);

        // if there are elements
        if (head)
        {
            for (Node *cur = head, *prev{}; cur; prev = cur, cur = cur->next)
            {
                if (cur->data >= val)
                {
                    if (cur == head)
                        head = newNode;
                    else
                        prev->next = newNode;

                    newNode->next = cur;

                    return;
                }
            }
            tail->next = newNode;
            tail = newNode;
        }
        else
            head = tail = newNode;
    }

    void swap_head_tail()
    {
        if (length <= 1)
            return;

        if (length == 2)
        {
            tail->next = head;
            head->next = nullptr;
            swap(head, tail);
            return;
        }
        Node *cur = head;

        while (cur->next != tail)
            cur = cur->next;
        // cur is now the last node before tail
        cur->next = head;
        tail->next = head->next;
        head->next = nullptr;
        swap(head, tail);
    }

    void left_rotate()
    {
        if (length > 1)
        {
            tail->next = head;
            head = head->next;
            tail = tail->next;
            tail->next = nullptr;
        }
    }

    void left_rotate(int k)
    {
        k %= length;
        while (k--)
            left_rotate();
    }

    void left_rotate2(int k)
    {
        if (length <= 1 || k % length == 0)
            return; // 0 or 1 elements or useless rotation
        k %= length;

        Node *cur = get_nth(k);

        tail->next = head;
        tail = cur;
        head = cur->next;
        tail->next = nullptr;
    }

    // here we delete the dups with O(n) but with memory tradeoff
    // we can implement this function in O(n^2) with memory O(1) by using 2 loops
    void remove_duplicates()
    {
        vector<bool> exist(1001, 0);
        Node *cur = head, *prev = nullptr;
        while (cur)
        {
            if (exist[cur->data])
            {
                prev->next = cur->next;
                Node *temp = cur;
                cur = cur->next;
                delete_node(temp);
            }
            else
            {
                exist[cur->data] = 1;
                prev = cur;
                cur = cur->next;
            }
        }
    }

    void remove_last_occurance(int val)
    {
        int idx = 1, last_idx = -1;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->data == val)
                last_idx = idx;

            idx++;
        }
        delete_nth(last_idx);
    }

    void move_to_back(int val)
    {
        if (length > 1)
        {
            Node *cur = head, *prev = nullptr;
            int cnt = 1;
            while (cur && cnt < length)
            {
                if (cur->data == val && cur != tail)
                {
                    if (cur = head)
                        head = head->next;
                    else
                        prev->next = cur->next;

                    tail->next = cur;
                    cur = cur->next;
                    tail = tail->next;
                    tail->next = nullptr;
                }
                else
                {
                    prev = cur;
                    cur = cur->next;
                }
                cnt++;
            }
        }
    }

    int max(Node *cur)
    {
        if (cur == tail)
            return cur->data;

        return std::max(cur->data, max(cur->next));
    }
    int max()
    {
        if (head == nullptr)
            return INT_MIN;

        return max(head);
    }

    void arrange_odd_and_even()
    {
        if (length < 3)
            return;
        int cnt = length / 2;
        Node *prev = head, *cur = head->next;

        while (cnt--)
        {
            prev->next = cur->next;

            tail->next = cur;
            cur->next = nullptr;
            tail = cur;

            cur = prev->next->next;
            prev = prev->next;
        }
    }

    void insert_alternate(LinkedList &list)
    {
        Node *cur1 = head, *cur2 = list.head;

        while (cur1 && cur2)
        {
            Node *list1_next = cur1->next, *new_node = new Node(cur2->data);

            cur1->next = new_node;
            cur1->next->next = list1_next;

            if (cur1 == tail)
                tail = new_node;

            add_node(cur1->next);
            cur1 = list1_next;
            cur2 = cur2->next;
        }

        while (cur2)
        {
            insert_end(cur2->data);
            cur2 = cur2->next;
        }
    }

    void add_big_ints(LinkedList &list)
    {
        Node *cur1 = head, *cur2 = list.head;
        int carry = 0;
        while (cur1 && cur2)
        {
            int sum = carry + cur1->data + cur2->data;
            carry = sum / 10;
            sum %= 10;
            cur1->data = sum;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        while (cur1 && carry)
        {
            int sum = carry + cur1->data;

            carry = sum / 10;
            sum %= 10;

            cur1->data = sum;
            cur1 = cur1->next;
        }
        while (cur2)
        {
            int sum = carry + cur2->data;

            carry = sum / 10;
            sum %= 10;

            insert_end(sum);
            cur2 = cur2->next;
        }

        if (carry)
            insert_end(carry);
    }

    void remove_repeated()
    {
        if (length >= 2)
        {
            Node *cur = head, *prev = nullptr;
            int repeated_val = cur->data - 1;

            while (cur->next)
            {
                if (cur->data == cur->next->data || cur->data == repeated_val)
                {
                    repeated_val = cur->data;

                    // delete cur code
                    // cur could be head or between head & tail
                    if (cur == head)
                    {
                        delete_front();
                        cur = head;
                    }
                    else
                    {
                        prev->next = cur->next;
                        Node *temp = cur->next;
                        delete_node(cur);
                        cur = temp;
                    }
                }

                else
                {
                    prev = cur;
                    cur = cur->next;
                }
            }

            // we have to check the tail and the previous element
            if (cur->data == repeated_val)
            {
                // delete tail
                delete_last();
            }
        }
    }

    void reverse_chain(int k)
    {
        if (k <= 1)
            return;

        int cnt = 1;
        Node *last_in_prev_chain{}, *last_in_cur_chain{}, *prev{}, *next{};
        bool is_first_chain = true;
        for (Node *cur = head; cur; cur = next, cnt++)
        {
            if (cnt % k == 1)
            {
                if (is_first_chain)
                    last_in_prev_chain = last_in_cur_chain = cur;
                else
                {
                    last_in_prev_chain = last_in_cur_chain;
                    last_in_cur_chain = cur;
                }
            }

            // last element in chain
            if (cnt % k == 0)
            {
                if (is_first_chain)
                    head = cur, is_first_chain = false;
                else
                    last_in_prev_chain->next = cur;
            }
            next = cur->next;
            cur->next = prev;
            prev = cur;
        }
        tail = last_in_cur_chain;
        tail->next = nullptr;
    }
};

//******************************************************//
// test functions
void test_insert_end()
{
    cout << "\n\ntest_insert_end\n";
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
    cout << "\n\ntest_insert_front\n";
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

void test_delete_front()
{
    cout << "\n\ntest_delete_front\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.delete_front();
    list.print();
    list.delete_front();
    list.print();

    string expected = "3 4";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_delete_last()
{
    cout << "\n\ntest_delete_last\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.delete_last();
    list.print();
    list.delete_last();
    list.print();

    string expected = "1 2";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_delete_nth()
{
    cout << "\n\ntest_delete_nth\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.delete_nth(3);
    list.print();
    list.delete_nth(3);
    list.print();

    string expected = "1 2";
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
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.print();
    list.delete_node_with_key(3);
    list.print();

    string expected = "1 2 4";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_get_nth()
{
    cout << "\n\ntest_get_nth\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);

    int expected = 3;
    Node *res = list.get_nth(3);
    if (res)
    {
        int result = res->data;
        if (expected != result)
        {
            cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
            assert(false);
        }
        list.debug_print_list("********");
    }
    else
        cout << "nullptr" << endl;
}

void test_is_same()
{
    cout << "\n\ntest_is_same\n";
    LinkedList list1, list2;

    list1.insert_end(1);
    list1.insert_end(2);
    list1.insert_end(3);
    list2.insert_end(1);
    list2.insert_end(2);
    list2.insert_end(3);

    bool expected = true;

    bool result = list1.is_same(list2);

    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list1.debug_print_list("list1 ********");
    list2.debug_print_list("list2 ********");
}

void test_swap_pairs()
{
    cout << "\n\ntest_swap_pairs\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.swap_pairs();
    list.print();

    string expected = "2 1 4 3 5";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_reverse()
{
    cout << "\n\ntest_reverse\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.reverse();
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

void test_delete_even_positions()
{
    cout << "\n\ntest_delete_even_positions\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.insert_end(6);
    list.insert_end(7);
    list.insert_end(8);
    list.delete_even_positions();
    list.print();

    string expected = "1 3 5 7";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_insert_sorted()
{
    cout << "\n\ntest_insert_sorted\n";
    LinkedList list;

    list.insert_sorted(5);
    list.insert_sorted(2);
    list.insert_sorted(3);
    list.insert_sorted(1);
    list.insert_sorted(4);
    list.print();

    string expected = "1 2 3 4 5";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_reverse_recursively()
{
    cout << "\n\ntest13\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.reverse_recursively();
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

void test_swap_head_tail()
{
    cout << "\n\nswap_head_tail\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.swap_head_tail();
    list.print();

    string expected = "4 2 3 1";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_left_rotate()
{
    cout << "\n\ntest_left_rotate\n";
    LinkedList list;

    list.insert_end(6);
    list.insert_end(10);
    list.insert_end(8);
    list.insert_end(15);
    list.left_rotate2(2000000);
    list.print();

    string expected = "6 10 8 15";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_remove_duplicates()
{
    cout << "\n\ntest_remove_duplicates\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(1);
    list.insert_end(1);
    list.insert_end(1);
    list.remove_duplicates();
    list.print();

    string expected = "1 2";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_remove_last_occurance()
{
    cout << "\n\ntest_remove_last_occurance\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(1);
    list.insert_end(1);
    list.insert_end(2);
    list.remove_last_occurance(1);
    list.remove_last_occurance(1);
    list.remove_last_occurance(2);
    list.remove_last_occurance(2);
    list.print();

    string expected = "1";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_move_to_back()
{
    cout << "\n\ntest_move_to_back\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(2);
    list.insert_end(4);
    list.insert_end(1);
    list.move_to_back(1);
    list.print();

    string expected = "2 3 2 4 1 1";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_find_max_recursively()
{
    cout << "\n\ntest_find_max_recursively\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(2);
    list.insert_end(4);
    list.insert_end(10);

    list.print();

    int expected = 10;
    int result = list.max();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_arrange_odd_and_even()
{
    cout << "\n\ntest_arrange_odd_and_even\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);

    list.arrange_odd_and_even();

    list.print();

    string expected = "1 3 5 2 4";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_insert_alternate()
{
    cout << "\n\ntest_insert_alternate\n";
    LinkedList list, list2;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list2.insert_end(6);

    list.insert_alternate(list2);

    list.print();

    string expected = "1 6 2 3";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_add_big_ints()
{
    cout << "\n\ntest_add_big_ints\n";
    LinkedList list, list2;

    list.insert_end(9);
    list.insert_end(6);
    list.insert_end(5);
    list2.insert_end(8);
    list2.insert_end(7);
    list2.insert_end(6);
    list2.insert_end(4);
    list2.insert_end(5);
    list2.insert_end(7);
    list2.insert_end(8);
    list2.insert_end(9);

    list.add_big_ints(list2);

    list.print();

    string expected = "7 4 2 5 5 7 8 9";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_remove_repeated()
{
    cout << "\n\ntest_remove_repeated\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(2);
    list.insert_end(2);
    list.insert_end(3);

    list.remove_repeated();

    list.print();

    string expected = "1 3";
    string result = list.debug_to_string();
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test_reverse_chain()
{
    cout << "\n\ntest24\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.insert_end(6);

    list.reverse_chain(6);

    list.print();

    string expected = "6 5 4 3 2 1";
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
    // test_insert_front();
    // test_delete_front();
    // test_delete_last();
    // test_delete_nth();
    // test_delete_node_with_key();
    // test_get_nth();
    // test_is_same();
    // test_swap_pairs();
    // test_reverse();
    // test_delete_even_positions();
    // test_insert_sorted();
    // test_reverse_recursively();
    // test_left_rotate();
    // test_remove_duplicates();
    // test_remove_last_occurance();
    // test_move_to_back();
    // test_find_max_recursively();
    // test_arrange_odd_and_even();
    // test_insert_alternate();
    // test_add_big_ints();
    // test_remove_repeated();
    test_reverse_chain();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}