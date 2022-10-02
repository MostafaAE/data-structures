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

    bool search(int target)
    {
        assert(root);
        return search(root, target);
    }

}

int
main()
{

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}