#include <iostream>

using namespace std;

enum Color {
    RED, BLACK
};

class RedBlackTree {
private:
    struct Node {
        int data;
        bool color;
        Node *left, *right, *parent;

        Node(int data) : data(data),
                         left(nullptr),
                         right(nullptr),
                         parent(nullptr),
                         color(RED) {}
    };

    Node *root;

    void leftRotation(Node* & node){
        Node* RightChild = node->right;
        node->right = RightChild->left;
        if(node->right != nullptr)
            node->right->parent = node;
        RightChild->parent = node->parent;
        if(node->parent == nullptr)
            root = RightChild;
        else if (node == node->parent->left)
            node->parent->left = RightChild;
        else
            node->parent->right = RightChild;
        RightChild->left = node;
        node->parent = RightChild;
    }

    void rightRotation(Node* & node){
        Node* LeftChild = node->left;
        node->left = LeftChild->right;
        if(node->left != nullptr)
            node->left->parent = node;
        LeftChild->parent = node->parent;
        if(node->parent == nullptr)
            root = LeftChild;
        else if (node == node->parent->left)
            node->parent->left = LeftChild;
        else
            node->parent->right = LeftChild;
        LeftChild->right = node;
        node->parent = LeftChild;
    }

    Node *insertBST(Node *root, Node *newNode) {
        Node* parent = nullptr;
        Node* cur = root;
        while(cur != nullptr){
            parent = cur;
            if (newNode->data < cur->data) cur = cur->left;
            else cur = cur->right;
        }
        newNode->parent = parent;
        if (parent == nullptr) root = newNode;
        else if(newNode->data < parent->data) parent->left = newNode;
        else parent->right = newNode;

        return root;
    }

    Node *minValueNode(Node *cur) {
        while (cur->left) {
            cur = cur->left;
        }
        return cur;
    }

    Node *deleteBST(Node *root, const int &data) {
        if (root == nullptr)
            return root;

        if (data < root->data)
            root->left = deleteBST(root->left, data);
        else if (data > root->data)
            root->right = deleteBST(root->right, data);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* successor = minValueNode(root->right);
                root->data = successor->data;
                root->right = deleteBST(root->right, successor->data);
            }
        }
        return root;
    }

    void deleteAllTreeNodes(Node *node) {
        if (node != nullptr) {
            deleteAllTreeNodes(node->left);
            deleteAllTreeNodes(node->right);
            delete node;
        }
    }

    void fixInsertRBT(Node* newNode) {
        Node* parent = nullptr;
        Node* grandParent = nullptr;

        while (newNode != root && newNode->color == RED && newNode->parent->color == RED) {
            parent = newNode->parent;
            grandParent = parent->parent;

            // Case: Parent is left child of grandparent
            if (parent == grandParent->left) {
                Node* uncle = grandParent->right;

                // Case 1: Uncle is RED (Recoloring)
                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    newNode = grandParent;
                } else {
                    // Case 2: Node is right child (Left Rotation on Parent)
                    if (newNode == parent->right) {
                        leftRotation(parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    // Case 3: Node is left child (Right Rotation on Grandparent)
                    rightRotation(grandParent);
                    swap(parent->color, grandParent->color);
                    newNode = parent;
                }
            } else { // Parent is right child of grandparent
                Node* uncle = grandParent->left;

                // Case 1: Uncle is RED (Recoloring)
                if (uncle != nullptr && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    newNode = grandParent;
                } else {
                    // Case 2: Node is left child (Right Rotation on Parent)
                    if (newNode == parent->left) {
                        rightRotation(parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    // Case 3: Node is right child (Left Rotation on Grandparent)
                    leftRotation(grandParent);
                    swap(parent->color, grandParent->color);
                    newNode = parent;
                }
            }
        }

        // Root must always be black
        root->color = BLACK;
    }

    void fixDeleteRBT(Node*& root, Node* deletedNode) {
        while (deletedNode != root && deletedNode->color == BLACK) {
            if (deletedNode == deletedNode->parent->left) {
                Node* sibling = deletedNode->parent->right;

                // Case 1: Sibling is RED (Recolor and Rotate Left)
                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    deletedNode->parent->color = RED;
                    leftRotation(deletedNode->parent);
                    sibling = deletedNode->parent->right;
                }

                // Case 2: Sibling's children are BLACK (Recolor Sibling)
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    if (sibling != nullptr) sibling->color = RED;
                    deletedNode = deletedNode->parent;
                } else {
                    // Case 3: Sibling's right child is BLACK (Recolor and Rotate Right on Sibling)
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr) sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotation(sibling);
                        sibling = deletedNode->parent->right;
                    }

                    // Case 4: Sibling's right child is RED (Recolor and Rotate Left on Parent)
                    sibling->color = deletedNode->parent->color;
                    deletedNode->parent->color = BLACK;
                    if (sibling->right != nullptr) sibling->right->color = BLACK;
                    leftRotation(deletedNode->parent);
                    deletedNode = root; // Fix completed
                }
            } else {
                Node* sibling = deletedNode->parent->left;

                // Case 1: Sibling is RED (Recolor and Rotate Right)
                if (sibling != nullptr && sibling->color == RED) {
                    sibling->color = BLACK;
                    deletedNode->parent->color = RED;
                    rightRotation(deletedNode->parent);
                    sibling = deletedNode->parent->left;
                }

                // Case 2: Sibling's children are BLACK (Recolor Sibling)
                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    if (sibling != nullptr) sibling->color = RED;
                    deletedNode = deletedNode->parent;
                } else {
                    // Case 3: Sibling's left child is BLACK (Recolor and Rotate Left on Sibling)
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr) sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotation(sibling);
                        sibling = deletedNode->parent->left;
                    }

                    // Case 4: Sibling's left child is RED (Recolor and Rotate Right on Parent)
                    sibling->color = deletedNode->parent->color;
                    deletedNode->parent->color = BLACK;
                    if (sibling->left != nullptr) sibling->left->color = BLACK;
                    rightRotation(deletedNode->parent);
                    deletedNode = root; // Fix completed
                }
            }
        }

        // Ensure the deleted node is black before exiting
        deletedNode->color = BLACK;
    }

    void displayTree(Node* root, string indent, bool last)
    {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }
            string sColor
                    = (root->color == RED) ? "RED" : "BLACK";
            cout << root->data << "(" << sColor << ")"
                 << endl;
            displayTree(root->left, indent, false);
            displayTree(root->right, indent, true);
        }
    }

public:
    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() {
        deleteAllTreeNodes(root);
    }

    void insertRBT(const int &data) {
        Node *newNode = new Node(data);
        root = insertBST(root, newNode);
        fixInsertRBT(newNode);
    }

    void deleteRBT(const int &data) {
        Node *node = deleteBST(root, data);
        fixDeleteRBT(root, node);
    }

    void displayTree()
    {
        if (root == nullptr)
            cout << "Tree is empty." << endl;
        else {
            cout << "Red-Black Tree:" << endl;
            displayTree(root, "", true);
        }
    }
};

int main() {
    RedBlackTree tree;

    cout << "Inserting values: 10, 20, 30, 15, 25\n";
    tree.insertRBT(10);
    tree.insertRBT(20);
    tree.insertRBT(30);
    tree.insertRBT(15);
    tree.insertRBT(25);
    cout << "Tree after insertions:\n";
    tree.displayTree();

    cout << "\nDeleting value: 20\n";
    tree.deleteRBT(20);
    cout << "Tree after deletion:\n";
    tree.displayTree();

    cout << "\nDeleting value: 15\n";
    tree.deleteRBT(15);
    cout << "Tree after deletion:\n";
    tree.displayTree();

    cout << "\nInserting values: 5, 7\n";
    tree.insertRBT(5);
    tree.insertRBT(7);
    cout << "Tree after new insertions:\n";
    tree.displayTree();

    cout << "\nDeleting value: 10\n";
    tree.deleteRBT(10);
    cout << "Tree after deletion:\n";
    tree.displayTree();

    return 0;
}