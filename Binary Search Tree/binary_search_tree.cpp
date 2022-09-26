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
            return true;

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

    Node *build_balanced_bst(vector<int> &nums, int start, int end)
    {
        if (start > end)
            return nullptr;

        int mid = (start + end) / 2;

        Node *node = new Node(nums[mid]);

        node->left = build_balanced_bst(nums, start, mid - 1);
        node->right = build_balanced_bst(nums, mid + 1, end);

        return node;
    }

    int kthSmallest(Node *node, int &k)
    {
        if (node->left)
        {
            int res = kthSmallest(node->left, k);
            if (k == 0)
                return res;
        }

        k--;
        if (k == 0)
            return node->data;

        if (node->right)
            return kthSmallest(node->right, k);

        return -1;
    }

    int lowestCommonAncestor(Node *node, int p, int q)
    {

        if (node->data > p && node->data > q)
            return lowestCommonAncestor(root->left, p, q);
        if (node->data < p && node->data < q)
            return lowestCommonAncestor(node->right, p, q);

        return node->data;
    }

    // O(h)
    int min_value(Node *node)
    {
        Node *cur = node;
        while (cur && cur->left)
            cur = cur->left;

        return cur->data;
    }

    // O(h)
    int max_value(Node *node)
    {
        Node *cur = node;
        while (cur && cur->right)
            cur = cur->right;

        return cur->data;
    }

public:
    BinarySearchTree() {}

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

    void build_balanced_bst(vector<int> &nums)
    {
        root = build_balanced_bst(nums, 0, nums.size() - 1);
    }

    int kthSmallest(int k)
    {
        return kthSmallest(root, k);
    }

    int lowestCommonAncestor(int p, int q)
    {

        return lowestCommonAncestor(root, p, q);
    }

    // O(h)
    int min_value()
    {
        return min_value(root);
    }

    // O(h)
    int max_value()
    {
        return max_value(root);
    }
};

int main()
{

    BinarySearchTree bst(40);

    bst.insert(30);
    bst.insert(50);
    bst.insert(10);
    bst.insert(35);
    bst.insert(45);
    bst.insert(60);

    cout << bst.min_value() << endl; // 10
    cout << bst.max_value() << endl; // 10

    // BinarySearchTree bst(40);

    // bst.insert(30);
    // bst.insert(50);
    // bst.insert(10);
    // bst.insert(35);
    // bst.insert(45);
    // bst.insert(60);

    // cout << bst.lowestCommonAncestor(30, 50) << endl; // 40
    // cout << bst.lowestCommonAncestor(10, 35) << endl; // 30
    // cout << bst.lowestCommonAncestor(45, 60) << endl; // 50
    // cout << bst.lowestCommonAncestor(60, 50) << endl; // 50
    // cout << bst.lowestCommonAncestor(60, 10) << endl; // 40

    // BinarySearchTree bst(20);

    // bst.insert(10);
    // bst.insert(80);
    // bst.insert(15);
    // cout << bst.kthSmallest(1) << endl; // 10
    // cout << bst.kthSmallest(2) << endl; // 15
    // cout << bst.kthSmallest(3) << endl; // 20
    // cout << bst.kthSmallest(4) << endl; // 80
    // cout << bst.kthSmallest(6) << endl; // -1

    // BinarySearchTree bst;
    // int arr[] = {10, 20, 30, 40, 50, 60, 70};
    // vector<int> v(arr, arr + 7);
    // bst.build_balanced_bst(v);
    // bst.print_inorder();

    // BinarySearchTree bst(40);

    // bst.insert(30);
    // bst.insert(50);
    // bst.insert(10);
    // bst.insert(20);
    // bst.insert(50);
    // bst.insert(60);
    // bst.insert(70);

    // cout << bst.is_bst() << endl;

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