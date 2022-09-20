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

    int tree_max(Node *root)
    {
        // assert tree is not empty
        assert(root);

        int result = root->data;

        if (root->left)
            result = max(result, tree_max(root->left));

        if (root->right)
            result = max(result, tree_max(root->right));

        return result;
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

    bool is_exist(Node *root, int value)
    {
        if (root->data == value)
            return 1;

        bool exist = 0;

        if (!exist && root->left)
            exist |= is_exist(root->left, value);

        if (!exist && root->right)
            exist |= is_exist(root->right, value);

        return exist;
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

    void parenthesize()
    {
        parenthesize(root);
    }

    string parenthesize_canonical()
    {
        return parenthesize_canonical(root);
    }

    int tree_max()
    {
        return tree_max(root);
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

    bool is_exist(int value)
    {
        return is_exist(root, value);
    }
};

int main()
{

    BinaryTree bt(1);
    cout << bt.is_exist(5) << endl; // 0

    bt.add({2, 4}, {'L', 'L'});
    cout << bt.is_exist(5) << endl; // 0

    bt.add({3, 6}, {'R', 'L'});
    cout << bt.is_exist(5) << endl; // 0

    bt.add({2, 5}, {'L', 'R'});
    cout << bt.is_exist(5) << endl; // 1

    bt.add({3, 7}, {'R', 'R'});
    cout << bt.is_exist(5) << endl; // 1

    // BinaryTree bt(1);

    // cout << bt.total_leaves() << endl; // 1

    // bt.add({2}, {'L'});
    // cout << bt.total_leaves() << endl; // 1

    // bt.add({3}, {'R'});
    // cout << bt.total_leaves() << endl; // 2

    // bt.add({2, 4}, {'L', 'L'});
    // bt.add({2, 5}, {'L', 'R'});
    // cout << bt.total_leaves() << endl; // 3

    // bt.add({3, 6}, {'R', 'L'});
    // bt.add({3, 7}, {'R', 'R'});
    // cout << bt.total_leaves() << endl; // 4

    // BinaryTree bt(1);

    // cout << bt.total_nodes() << endl; // 1

    // bt.add({2, 4}, {'L', 'L'});
    // cout << bt.total_nodes() << endl; // 3

    // bt.add({2, 5}, {'L', 'R'});
    // cout << bt.total_nodes() << endl; // 4

    // bt.add({3, 6}, {'R', 'R'});
    // cout << bt.total_nodes() << endl; // 6

    // BinaryTree bt(1);
    // cout << bt.tree_height() << endl; // 0

    // bt.add({2}, {'L'});
    // cout << bt.tree_height() << endl; // 1
    // bt.add({3}, {'R'});
    // cout << bt.tree_height() << endl; // 1

    // bt.add({3, 6}, {'R', 'L'});
    // cout << bt.tree_height() << endl; // 2
    // bt.add({2, 4}, {'L', 'L'});
    // cout << bt.tree_height() << endl; // 2

    // bt.add({2, 4, 5}, {'L', 'L', 'L'});
    // cout << bt.tree_height() << endl; // 3

    // bt.add({2, 4, 5, 6}, {'L', 'L', 'L', 'L'});
    // cout << bt.tree_height() << endl; // 4

    // BinaryTree bt(1);
    // cout << bt.tree_max() << endl; // 1

    // bt.add({2, 4}, {'L', 'L'});
    // cout << bt.tree_max() << endl; // 4
    // bt.add({2, 5}, {'L', 'R'});
    // cout << bt.tree_max() << endl; // 5
    // bt.add({3, 6}, {'R', 'L'});
    // cout << bt.tree_max() << endl; // 6
    // bt.add({3, 7}, {'R', 'R'});
    // cout << bt.tree_max() << endl; // 7

    // BinaryTree bt1(1), bt2(1), bt3(1);

    // bt1.add({2, 4}, {'L', 'L'});
    // bt1.add({2, 5}, {'L', 'R'});
    // bt1.add({3, 6}, {'R', 'R'});

    // bt2.add({2, 4}, {'R', 'R'});
    // bt2.add({2, 5}, {'R', 'L'});
    // bt2.add({3, 6}, {'L', 'L'});

    // bt3.add({2, 4}, {'R', 'R'});
    // bt3.add({2, 5}, {'R', 'L'});
    // bt3.add({3, 6}, {'L', 'R'});

    // cout << bt1.parenthesize_canonical() << endl; // (1(2(4()())(5()()))(3()(6()())))
    // cout << bt2.parenthesize_canonical() << endl; // (1(2(4()())(5()()))(3()(6()())))
    // cout << bt3.parenthesize_canonical() << endl; // (1(2(4()())(5()()))(3()(6()())))

    // bt1.parenthesize(); // (1(2(4()())(5()()))(3()(6()())))
    // cout << "\n";
    // bt2.parenthesize(); // (1(3(6()())())(2(5()())(4()())))
    // cout << "\n";
    // bt3.parenthesize(); // (1(3()(6()()))(2(5()())(4()())))

    // BinaryTree bt(1);

    // bt.add({2}, {'L'});
    // bt.add({3}, {'R'});

    // // bt.print_preorder_complete();
    // // bt.parenthesize();

    // cout << bt.parenthesize_canonical() << endl;

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