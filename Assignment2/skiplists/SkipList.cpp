#include <bits/stdc++.h>

using namespace std;

const int maxNumberOfLevel = 5;
class Node
{
public:
    int data;
    vector<Node *> next;
    Node(int data, int Level) : data(data), next(Level + 1, nullptr) {}
};

class skipList
{
private:
    Node *head;
    int Level;

public:
    skipList()
    {
        head = new Node(0, maxNumberOfLevel);
        Level = 0;
    }

    void insert(int data)
    {
        int newLevel = 0;
        while (newLevel < maxNumberOfLevel and (rand() % 2) == 1)
            newLevel++;

        if (Level < newLevel)
        {
            head->next.resize(newLevel + 1, nullptr);
            Level = newLevel;
        }

        Node *current = head;
        vector<Node *> Update(Level + 1, nullptr);

        for (int i = Level; i >= 0; i--)
        {
            while (current->next[i] and current->next[i]->data < data)
                current = current->next[i];
            Update[i] = current;
        }

        current = current->next[0];
        if (current == nullptr or current->data != data)
        {
            Node *newNode = new Node(data, Level);
            for (int i = 0; i <= newLevel; i++)
            {
                newNode->next[i] = Update[i]->next[i];
                Update[i]->next[i] = newNode;
            }
            cout << "Element " << data << " inserted successfully.\n";
        }
        else
            cout << "Element " << data << " already exists.\n";
    }

    void remove(int data)
    {
        Node *current = head;
        vector<Node *> Update(Level + 1, nullptr);
        for (int i = Level; i >= 0; i--)
        {
            while (current->next[i] and current->next[i]->data < data)
                current = current->next[i];
            Update[i] = current;
        }

        current = current->next[0];
        if (current != nullptr and current->data == data)
        {
            for (int i = 0; i <= Level; i++)
            {
                if (Update[i]->next[i] != current)
                    break;
                else
                    Update[i]->next[i] = current->next[i];
            }

            delete current;
            while (Level > 0 and head->next[Level] == nullptr)
                Level--;

            cout << "Element " << data << " deleted successfully." << endl;
        }
        else
            cout << "Element " << data << " not found." << endl;
    }

    bool search(int data)
    {
        Node *current = head;

        for (int i = Level; i >= 0; i--)
        {
            while (current->next[i] && current->next[i]->data < data)
                current = current->next[i];
        }
        current = current->next[0];
        if (current != nullptr && current->data == data)
        {
            cout << "Element " << data << " found.\n";
            return true;
        }

        cout << "Element " << data << " not found.\n";
        return false;
    }

    void display()
    {

        cout << "skip List:" << endl;
        for (int i = Level; i >= 0; i--)
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
};

int main()
{

    skipList SkipList;

    SkipList.insert(10);
    SkipList.insert(20);
    SkipList.insert(30);
    SkipList.insert(40);
    SkipList.insert(50);

    SkipList.display();

    SkipList.search(20);
    SkipList.search(40);

    SkipList.remove(20);
    SkipList.remove(40);

    SkipList.display();
    return 0;
}