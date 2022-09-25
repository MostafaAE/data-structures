#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data{};
    Node *left{}, *right{};

    Node(int data) : data(data){};
    ~Node()
    {
        cout << "Node: " << data << " is deleted" << endl;
    }
};

class BinarySearchTree
{

private:
    Node *root{};

    void print_preorder(Node *node)
    {
        if (!node)
            return;

        cout << node->data << " ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    void print_postorder(Node *node)
    {
        if (!node)
            return;

        print_postorder(node->left);
        print_postorder(node->right);
        cout << node->data << " ";
    }

    void print_inorder(Node *node)
    {
        if (!node)
            return;

        print_inorder(node->left);
        cout << node->data << " ";
        print_inorder(node->right);
    }

    void parenthesize(Node *node)
    {
        if (!node)
        {
            cout << "()";
            return;
        }
        cout << "(";
        cout << node->data;
        parenthesize(node->left);
        parenthesize(node->right);
        cout << ")";
    }

    string parenthesize_canonical(Node *node)
    {
        vector<string> v;
        if (!node)
            return "()";

        string repr = "(" + to_string(node->data);

        v.push_back(parenthesize_canonical(node->left));
        v.push_back(parenthesize_canonical(node->right));

        sort(v.begin(), v.end());
        for (string s : v)
            repr += s;

        repr += ")";

        return repr;
    }

    int tree_height(Node *root)
    {
        // assert tree is not empty
        assert(root);

        int height_l{}, height_r{};

        if (root->left)
            height_l = 1 + tree_height(root->left);

        if (root->right)
            height_r = 1 + tree_height(root->right);

        return max(height_l, height_r);
    }

    int total_nodes(Node *root)
    {
        if (!root)
            return 0;

        int nodes_count = 1;

        nodes_count += total_nodes(root->left);
        nodes_count += total_nodes(root->right);

        return nodes_count;
    }

    int total_leaves(Node *root)
    {
        // leaf node
        if (!root->left && !root->right)
            return 1;

        int leaves_count = 0;

        if (root->left)
            leaves_count += total_leaves(root->left);
        if (root->right)
            leaves_count += total_leaves(root->right);

        return leaves_count;
    }

    void clear(Node *root)
    {
        if (!root)
            return;

        clear(root->left);
        clear(root->right);

        delete root;
    }

    bool search(Node *node, int val)
    {
        if (!node)
            return false;

        if (node->data == val)
            return root;

        if (val < node->data)
            return search(node->left, val);

        return search(node->right, val);
    }

    void insert(Node *node, int val)
    {
        if (val < node->data)
        {
            if (node->left)
                insert(node->left, val);
            else
                node->left = new Node(val);
        }
        else if (val > node->data)
        {
            if (node->right)
                insert(node->right, val);
            else
                node->right = new Node(val);
        }
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

public:
    BinarySearchTree(int root_value)
    {
        root = new Node(root_value);
    }

    ~BinarySearchTree()
    {
        clear();
    }

    void print_preorder()
    {
        print_preorder(root);
        cout << "\n";
    }

    void print_postorder()
    {
        print_postorder(root);
        cout << "\n";
    }

    void print_inorder()
    {
        print_inorder(root);
        cout << "\n";
    }

    // O(n)
    void print_level_order()
    {
        assert(root);

        queue<Node *> qu;
        qu.push(root);

        int level = 0;

        while (!qu.empty())
        {
            int sz = (int)qu.size();

            // print level
            cout << "\nLevel " << level++ << ": ";

            while (sz--)
            {
                Node *cur = qu.front();
                qu.pop();

                cout << cur->data << " ";

                if (cur->left)
                    qu.push(cur->left);
                if (cur->right)
                    qu.push(cur->right);
            }
        }
        cout << "\n";
    }

    void parenthesize()
    {
        parenthesize(root);
    }

    string parenthesize_canonical()
    {
        return parenthesize_canonical(root);
    }

    int tree_height()
    {
        return tree_height(root);
    }

    int total_nodes()
    {
        return total_nodes(root);
    }

    int total_leaves()
    {
        return total_leaves(root);
    }

    void clear()
    {
        clear(root);
        root = nullptr;
    }

    // iterative search
    bool search_iterative(int val)
    {
        while (root)
        {
            if (root->data == val)
                return true;

            else if (val < root->data)
                root = root->left;

            else
                root = root->right;
        }
        return false;
    }

    // recursive search
    bool search(int val)
    {
        assert(root);
        return search(root, val);
    }

    // iterative insert
    void insert_iterative(int val)
    {
        Node *cur = root;

        while (true)
        {
            if (val < cur->data)
            {
                if (cur->left)
                    cur = cur->left;
                else
                {
                    cur->left = new Node(val);
                    return;
                }
            }

            else if (val > cur->data)
            {
                if (cur->right)
                    cur = cur->right;
                else
                {
                    cur->right = new Node(val);
                    return;
                }
            }
        }
    }

    void insert(int val)
    {
        insert(root, val);
    }

    bool is_bst()
    {
        return is_bst(root);
    }
};

int main()
{
    BinarySearchTree bst(40);

    bst.insert(30);
    bst.insert(50);
    bst.insert(10);
    bst.insert(20);
    bst.insert(50);
    bst.insert(60);
    bst.insert(70);

    cout << bst.is_bst() << endl;

    // bst.print_inorder(); // 10 20 30 40 50 60 70

    // bst.print_preorder(); // 40 30 10 20 50 60 70

    // cout << bst.search(10) << endl; // true
    // cout << bst.search(70) << endl; // true
    // cout << bst.search(0) << endl;  // false
    // cout << bst.search(80) << endl; // false
    // must see it, otherwise RTE
    cout
        << "\n\nNO RTE\n";
    return 0;
}