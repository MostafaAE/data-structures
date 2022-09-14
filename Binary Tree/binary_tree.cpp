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

    void print_inorder()
    {
        print_inorder(root);
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

    void level_order()
    {
        assert(root);

        queue<pair<Node *, int>> qu;
        qu.push(make_pair(root, 0));
        int level = -1;
        while (!qu.empty())
        {
            auto [cur, cur_level] = qu.front();
            qu.pop();

            // print level
            if (level != cur_level)
            {
                cout << "\nLevel " << cur_level << ": ";
                level++;
            }

            cout << cur->data << " ";

            if (cur->left)
                qu.push(make_pair(cur->left, level + 1));
            if (cur->right)
                qu.push(make_pair(cur->right, level + 1));
        }
        cout << "\n";
    }
};

int main()
{
    BinaryTree bt(1);

    bt.add({2, 4, 7}, {'L', 'L', 'L'});
    bt.add({2, 4, 8}, {'L', 'L', 'R'});
    bt.add({2, 5, 9}, {'L', 'R', 'R'});
    bt.add({3, 6, 10}, {'R', 'R', 'L'});

    bt.level_order();
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