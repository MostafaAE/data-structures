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

class BinarySearchTree
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
};

int main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}