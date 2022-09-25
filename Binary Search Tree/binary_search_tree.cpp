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
};

int main()
{

    // must see it, otherwise RTE
    cout
        << "\n\nNO RTE\n";
    return 0;
}