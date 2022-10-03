#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data{};
    int height{};
    Node *left{}, *right{};

    Node(int data) : data(data){};
    ~Node()
    {
        cout << "Node: " << data << " is deleted" << endl;
    }

    int ch_height(Node *node)
    { // child height
        if (!node)
            return -1;       // -1 for null
        return node->height; // 0 for leaf
    }
    int update_height()
    { // call in end of insert function
        return height = 1 + max(ch_height(left), ch_height(right));
    }
    int balance_factor()
    {
        return ch_height(left) - ch_height(right);
    }
};

class AVLTree
{

private:
    Node *root{};

    void clear(Node *root)
    {
        if (!root)
            return;

        clear(root->left);
        clear(root->right);

        delete root;
    }
    bool search(int target, Node *node)
    {
        if (!node)
            return false;

        if (target == node->data)
            return true;

        if (target < node->data)
            return search(target, node->left);

        return search(target, node->right);
    }

    pair<bool, int> lower_bound(int target, Node *node)
    {
        if (!node)
            return make_pair(false, -1);

        if (target <= node->data)
        {
            pair<bool, int> ans = lower_bound(target, node->left);

            if (ans.first)
                return ans;

            return make_pair(true, node->data);
        }

        return lower_bound(target, node->right);
    }

    pair<bool, int> upper_bound(int target, Node *node)
    {
        if (!node)
            return make_pair(false, -1);

        if (target < node->data)
        {
            pair<bool, int> ans = upper_bound(target, node->left);

            if (ans.first)
                return ans;

            return make_pair(true, node->data);
        }

        return upper_bound(target, node->right);
    }

    Node *left_rotation(Node *P)
    {
        cout << "left_rotation " << P->data << "\n";
        Node *Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
        return Q;
    }

    Node *right_rotation(Node *Q)
    {
        cout << "right_rotation " << Q->data << "\n";
        Node *P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update_height();
        P->update_height();
        return P;
    }

    Node *balance(Node *node)
    {
        // left heavy
        if (node->balance_factor() == 2)
        {
            if (node->left->balance_factor() == -1)
                node->left = left_rotation(node->left);

            node = right_rotation(node);
        }
        // right heavy
        else if (node->balance_factor() == -2)
        {
            if (node->right->balance_factor() == 1)
                node->right = right_rotation(node->right);

            node = left_rotation(node);
        }
        return node;
    }

    Node *insert(int target, Node *node)
    {
        if (target < node->data)
        {
            if (node->left)
                node->left = insert(target, node->left);
            else
                node->left = new Node(target);
        }
        else if (target > node->data)
        {
            if (node->right)
                node->right = insert(target, node->right);
            else
                node->right = new Node(target);
        }

        node->update_height();
        return balance(node);
    }

    // O(h)
    Node *min_node(Node *node)
    {
        Node *cur = node;
        while (cur && cur->left)
            cur = cur->left;

        return cur;
    }

    Node *delete_node(int target, Node *node)
    {
        if (!node)
            return nullptr;

        if (target < node->data)
            node->left = delete_node(target, node->left);
        else if (target > node->data)
            node->right = delete_node(target, node->right);
        else
        {
            // target == node->data
            // found the node: handle deletion

            Node *temp = node;

            if (!node->left && !node->right) // case 1: leaf node
                node = nullptr;
            else if (!node->right) // case 2: 1 left child
                node = node->left;
            else if (!node->left) // case 2: 1 right child
                node = node->right;
            else // case 3: 2 children (left & right)
            {
                // find successor
                Node *successor = min_node(node->right);
                node->data = successor->data;
                node->right = delete_node(successor->data, node->right);
                temp = nullptr;
            }

            if (temp)
                delete temp;
        }
        if (node)
        {
            node->update_height();
            node = balance(node);
        }
        return node;
    }

    void print_inorder(Node *node)
    {
        if (!node)
            return;

        print_inorder(node->left);
        cout << node->data << " ";
        print_inorder(node->right);
    }

    bool is_bst(Node *node, int mn = INT_MIN, int mx = INT_MAX)
    {
        bool status = mn < node->data && node->data < mx;

        if (!status)
            return false;

        bool left_bst{1}, right_bst{1};

        if (node->left)
        {
            if (node->data > node->left->data)
                left_bst = is_bst(node->left, mn, node->data);
            else
                left_bst = false;
        }

        if (left_bst && node->right)
        {
            if (node->data < node->right->data)
                right_bst = is_bst(node->right, node->data, mx);
            else
                right_bst = false;
        }

        return left_bst && right_bst;
    }

    void verify()
    {
        assert(abs(root->balance_factor()) <= 1);
        assert(is_bst(root));
    }

public:
    AVLTree()
    {
    }

    AVLTree(int root_value)
    {
        root = new Node(root_value);
    }

    ~AVLTree()
    {
        clear();
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    bool search(int target)
    {
        assert(root);
        return search(target, root);
    }

    pair<bool, int> lower_bound(int target)
    {
        return lower_bound(target, root);
    }

    pair<bool, int> upper_bound(int target)
    {
        return upper_bound(target, root);
    }

    void insert(int target)
    {
        if (!root)
            root = new Node(target);

        root = insert(target, root);
    }

    void delete_value(int target)
    {
        if (root)
            root = delete_node(target, root);
    }

    void print_inorder()
    {
        print_inorder(root);
    }

    void level_order_traversal()
    {
        if (!root)
            return;

        cout << "******************\n";
        queue<Node *> nodes_queue;
        nodes_queue.push(root);

        int level = 0;
        while (!nodes_queue.empty())
        {
            int sz = nodes_queue.size();

            cout << "Level " << level << ": ";
            while (sz--)
            {
                Node *cur = nodes_queue.front();
                nodes_queue.pop();

                cout << cur->data << " ";
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            level++;
            cout << "\n";
        }
    }
};

void f1()
{
    AVLTree tree;

    for (int i = 0; i <= 32; ++i)
    { // degenerate
        tree.insert(i);
        tree.level_order_traversal();
    }

    tree.delete_value(32);
    tree.level_order_traversal();
    tree.delete_value(31);
    tree.level_order_traversal();
    tree.delete_value(30);
    tree.level_order_traversal();
    tree.delete_value(10);
    tree.level_order_traversal();
}

void lower_bound_test()
{
    AVLTree tree;

    for (int i = 1; i <= 10; ++i)
        tree.insert(i * 10);

    tree.level_order_traversal();

    pair<bool, int> lb = tree.lower_bound(10);
    cout << lb.second << endl;

    lb = tree.lower_bound(1);
    cout << lb.second << endl;

    lb = tree.lower_bound(11);
    cout << lb.second << endl;
    lb = tree.lower_bound(20);
    cout << lb.second << endl;

    lb = tree.lower_bound(21);
    cout << lb.second << endl;

    lb = tree.lower_bound(100);
    cout << lb.second << endl;

    lb = tree.lower_bound(101);
    cout << lb.second << endl;
}

void upper_bound_test()
{
    AVLTree tree;

    for (int i = 1; i <= 10; ++i)
        tree.insert(i * 10);

    tree.level_order_traversal();

    pair<bool, int> ub = tree.upper_bound(10);
    cout << ub.second << endl;

    ub = tree.upper_bound(1);
    cout << ub.second << endl;

    ub = tree.upper_bound(11);
    cout << ub.second << endl;
    ub = tree.upper_bound(20);
    cout << ub.second << endl;

    ub = tree.upper_bound(21);
    cout << ub.second << endl;

    ub = tree.upper_bound(100);
    cout << ub.second << endl;

    ub = tree.upper_bound(101);
    cout << ub.second << endl;
}
int main()
{
    // f1();
    // lower_bound_test();
    upper_bound_test();
    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}

// f1(); output
/*


 Level 0: 0
 Level 1: 1
 ******************
 Level 0: 1
 Level 1: 0 2
 ******************
 Level 0: 1
 Level 1: 0 2
 Level 2: 3
 ******************
 Level 0: 1
 Level 1: 0 3
 Level 2: 2 4
 ******************
 Level 0: 3
 Level 1: 1 4
 Level 2: 0 2 5
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 6
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 6
 Level 3: 7
 ******************
 Level 0: 3
 Level 1: 1 5
 Level 2: 0 2 4 7
 Level 3: 6 8
 ******************
 Level 0: 3
 Level 1: 1 7
 Level 2: 0 2 5 8
 Level 3: 4 6 9
 ******************
 Level 0: 3
 Level 1: 1 7
 Level 2: 0 2 5 9
 Level 3: 4 6 8 10
 ******************
 Level 0: 7
 Level 1: 3 9
 Level 2: 1 5 8 10
 Level 3: 0 2 4 6 11
 ******************
 Level 0: 7
 Level 1: 3 9
 Level 2: 1 5 8 11
 Level 3: 0 2 4 6 10 12
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 12
 Level 3: 0 2 4 6 8 10 13
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 14
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 14
 Level 4: 15
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 13
 Level 3: 0 2 4 6 8 10 12 15
 Level 4: 14 16
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 15
 Level 3: 0 2 4 6 8 10 13 16
 Level 4: 12 14 17
 ******************
 Level 0: 7
 Level 1: 3 11
 Level 2: 1 5 9 15
 Level 3: 0 2 4 6 8 10 13 17
 Level 4: 12 14 16 18
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 17
 Level 3: 0 2 4 6 9 13 16 18
 Level 4: 8 10 12 14 19
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 17
 Level 3: 0 2 4 6 9 13 16 19
 Level 4: 8 10 12 14 18 20
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 19
 Level 3: 0 2 4 6 9 13 17 20
 Level 4: 8 10 12 14 16 18 21
 ******************
 Level 0: 7
 Level 1: 3 15
 Level 2: 1 5 11 19
 Level 3: 0 2 4 6 9 13 17 21
 Level 4: 8 10 12 14 16 18 20 22
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 21
 Level 3: 1 5 9 13 16 18 20 22
 Level 4: 0 2 4 6 8 10 12 14 23
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 21
 Level 3: 1 5 9 13 16 18 20 23
 Level 4: 0 2 4 6 8 10 12 14 22 24
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 23
 Level 3: 1 5 9 13 16 18 21 24
 Level 4: 0 2 4 6 8 10 12 14 20 22 25
 ******************
 Level 0: 15
 Level 1: 7 19
 Level 2: 3 11 17 23
 Level 3: 1 5 9 13 16 18 21 25
 Level 4: 0 2 4 6 8 10 12 14 20 22 24 26
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 25
 Level 3: 1 5 9 13 17 21 24 26
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 27
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 25
 Level 3: 1 5 9 13 17 21 24 27
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 26 28
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 28
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 29
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
 Level 5: 31
 ******************
 Level 0: 15
 Level 1: 7 23
 Level 2: 3 11 19 27
 Level 3: 1 5 9 13 17 21 25 29
 Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 31
 Level 5: 30 32
******************
Level 0: 15
Level 1: 7 23
Level 2: 3 11 19 27
Level 3: 1 5 9 13 17 21 25 29
Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 31
Level 5: 30 32
Node: 32 is deleted
******************
Level 0: 15
Level 1: 7 23
Level 2: 3 11 19 27
Level 3: 1 5 9 13 17 21 25 29
Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 31
Level 5: 30
Node: 31 is deleted
******************
Level 0: 15
Level 1: 7 23
Level 2: 3 11 19 27
Level 3: 1 5 9 13 17 21 25 29
Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
Node: 30 is deleted
******************
Level 0: 15
Level 1: 7 23
Level 2: 3 11 19 27
Level 3: 1 5 9 13 17 21 25 29
Level 4: 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28
Node: 10 is deleted
******************
Level 0: 15
Level 1: 7 23
Level 2: 3 11 19 27
Level 3: 1 5 9 13 17 21 25 29
Level 4: 0 2 4 6 8 12 14 16 18 20 22 24 26 28

 */