#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Node
{
public:
    int data;
    vector<Node *> next;

    Node(int data, int levels)
    {
        this->data = data;
        next = vector<Node *>(levels + 1, nullptr);
    }
};

class skipList
{
private:
    Node *head;
    int maxLevel;
    int nodeCount;

    int getRandomLevel()
    {
        int level = 0;
        while (level < maxLevel && rand() % 2)
            level++;
        return level;
    }

    int calculateMaxLevel()
    {
        return (nodeCount > 0) ? log2(nodeCount) : 0;
    }

public:
    skipList()
    {
        head = new Node(0, 0);
        maxLevel = 0;
        nodeCount = 0;
        srand(time(nullptr));
    }

    void insert(int element)
    {
        int nodeLevel = getRandomLevel();      // get random level
        int newMaxLevel = calculateMaxLevel(); // calculate maximum level based on number of nodes (log2(n))
        if (newMaxLevel > maxLevel)            // if maximum level increases, adjust the head node, so that it is present in all levels
        {
            head->next.resize(newMaxLevel + 1, nullptr);
            maxLevel = newMaxLevel;
        }

        // find the position to insert new node
        Node *current = head;
        vector<Node *> update(maxLevel + 1, nullptr);

        for (int i = maxLevel; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->data < element)
                current = current->next[i];
            update[i] = current; // insert the last node reached in level i to be updated later
        }

        current = current->next[0];                         // move to the next node in level 0
        if (current != nullptr && current->data == element) // Avoid duplicates
        {
            cout << "Node: " << element << " already exists.\n";
            return;
        }
        Node *newNode = new Node(element, nodeLevel);
        for (int i = 0; i <= nodeLevel; i++)
        {
            newNode->next[i] = update[i]->next[i]; // newNode will point to its previous node
            update[i]->next[i] = newNode;          // its previous node will point to the new node
        }
        nodeCount++;
        cout << "Node: " << element << " added successfully\n";
    }

    void display()
    {
        cout << "Skip List:" << endl;
        for (int i = maxLevel - 1; i >= 0; i--)
        {
            Node *current = head->next[i];
            cout << "Level " << i << ": ";
            while (current != nullptr)
            {
                cout << current->data << " ";
                current = current->next[i];
            }
            cout << endl;
        }
    }

    bool search(int element)
    {
        Node *current = head;

        for (int i = maxLevel; i >= 0; i--)
        {
            while (current->next[i] && current->next[i]->data < element)
                current = current->next[i];
        }
        current = current->next[0];
        if (current != nullptr && current->data == element)
        {
            cout << "Element " << element << " found.\n";
            return true;
        }

        cout << "Element " << element << " not found.\n";
        return false;
    }

    void remove(int element)
    {
        Node *current = head;
        vector<Node *> update(maxLevel + 1, nullptr);

        for (int i = maxLevel; i >= 0; i--)
        {
            while (current->next[i] != nullptr && current->next[i]->data < element)
                current = current->next[i];
            update[i] = current;
        }

        current = current->next[0];
        if (current != nullptr && current->data == element)
        {
            for (int i = 0; i <= maxLevel; i++)
            {
                if (update[i]->next[i] != current)
                    break;
                update[i]->next[i] = current->next[i];
            }
            delete current;
            nodeCount--;
            maxLevel = calculateMaxLevel();
            cout << "Element " << element << " deleted successfully.\n";
        }
        else
        {
            cout << "Element " << element << " not found.\n";
        }
    }

    ~skipList()
    {
        Node *current = head;
        while (current)
        {
            Node *temp = current;
            current = current->next[0];
            delete temp;
        }
    }
};

int main()
{
    skipList SkipList;

    SkipList.insert(2);
    SkipList.insert(4);
    SkipList.insert(1);
    SkipList.insert(3);
    SkipList.insert(5);
    SkipList.insert(7);

    SkipList.display();

    SkipList.search(99);
    SkipList.search(8);
    SkipList.remove(2);
    SkipList.remove(7);

    SkipList.display();
}