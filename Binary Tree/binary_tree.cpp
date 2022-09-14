#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data{};
    Node *left{}, *right{};

    Node(int data) : data(data){};
};

class BinaryTree
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

    void print_preorder_complete(Node *node)
    {
        if (!node)
        {
            cout << -1 << " ";
            return;
        }

        cout << node->data << " ";
        print_preorder_complete(node->left);
        print_preorder_complete(node->right);
    }

public:
    BinaryTree(int root_value)
    {
        root = new Node(root_value);
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

    void add(vector<int> values, vector<char> directions)
    {
        assert(values.size() == directions.size());

        Node *cur = root;
        for (int i = 0; i < (int)values.size(); i++)
        {

            if (directions[i] == 'L')
            {
                if (cur->left)
                    assert(cur->left->data == values[i]);
                else
                    cur->left = new Node(values[i]);

                cur = cur->left;
            }
            else if (directions[i] == 'R')
            {
                if (cur->right)
                    assert(cur->right->data == values[i]);
                else
                    cur->right = new Node(values[i]);

                cur = cur->right;
            }
            else
                assert(false);
        }
    }

    // O(n)
    void level_order()
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

    void print_preorder_complete()
    {
        print_preorder_complete(root);
        cout << "\n";
    }
};

int main()
{
    BinaryTree bt(1);

    bt.add({2}, {'L'});
    bt.add({3}, {'R'});

    bt.print_preorder_complete();
    // bt.print_inorder();
    // // Create Nodes
    // Node *root = new Node(1);
    // Node *node2 = new Node(2);
    // Node *node3 = new Node(3);
    // Node *node4 = new Node(4);
    // Node *node5 = new Node(5);
    // Node *node6 = new Node(6);
    // Node *node7 = new Node(7);
    // Node *node8 = new Node(8);

    // // Link them!
    // root->left = node2;
    // root->right = node3;

    // node2->left = node4;
    // node2->right = node5;

    // node5->right = node7;

    // node3->right = node6;

    // node6->left = node8;

    // cout << root->left->right->right->data << "\n"; // 7
    // cout << node2->right->right->data << "\n";      // 7
    // cout << node5->right->data << "\n";             // 7
    // cout << node7->data << "\n";                    // 7

    // cout << root->right->right->data << "\n";       // 6
    // cout << root->right->right->left->data << "\n"; // 8
    // cout << root->right->right->right << "\n";      // 0x00

    // print_preorder(root);
    // must see it, otherwise RTE
    cout
        << "\n\nNO RTE\n";
    return 0;
}