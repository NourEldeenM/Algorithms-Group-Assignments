#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <algorithm>

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
            // cout << "Node: " << element << " already exists.\n";
            return;
        }
        Node *newNode = new Node(element, nodeLevel);
        for (int i = 0; i <= nodeLevel; i++)
        {
            newNode->next[i] = update[i]->next[i]; // newNode will point to its previous node
            update[i]->next[i] = newNode;          // its previous node will point to the new node
        }
        nodeCount++;
        // cout << "Node: " << element << " added successfully\n";
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
            // cout << "Element " << element << " deleted successfully.\n";
        }
        else
        {
            // cout << "Element " << element << " not found.\n";
        }
    }

    int getMax()
    {
        if (head == nullptr) // skiplist empty
            return -1;

        Node *current = head;
        // Traverse each level starting from the highest level down to level 0
        for (int i = maxLevel; i >= 0; i--)
        {
            // Move current node right as far as possible on this level
            while (current->next[i] != nullptr)
            {
                current = current->next[i];
            }
        }

        // After the loops, 'current' should be at the rightmost node on level 0
        return current->data;
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

// int main()
// {
//     skipList SkipList;

//     SkipList.insert(2);
//     SkipList.insert(4);
//     SkipList.insert(1);
//     SkipList.insert(3);
//     SkipList.insert(5);
//     SkipList.insert(7);

//     SkipList.display();

//     SkipList.search(99);
//     SkipList.search(8);
//     SkipList.remove(2);
//     SkipList.remove(7);

//     SkipList.display();
// }

class gameManager
{
private:
    map<int, skipList> scores;

public:
    void enroll(int playerId)
    {
        if (scores.find(playerId) == scores.end())
        {
            cout << "Player " << playerId << " enrolled successfully\n";
            scores[playerId].insert(-2);
            scores[playerId].insert(-1);
            scores[playerId].insert(0);
        }
        else
        {
            cout << "Player with id " << playerId << " already registered\n";
        }
    }

    void updateScore(int playerID, int delta)
    {
        if (scores.find(playerID) == scores.end())
        {
            cout << "Player not found.\n";
            return;
        }
        skipList &playerScore = scores[playerID];
        int oldScore = playerScore.getMax();
        int newScore = oldScore + delta;

        playerScore.remove(oldScore);
        playerScore.insert(newScore);

        cout << "Updated player " << playerID << " score to " << newScore << endl;
    }

    void getTopNPlayers(int n)
    {
        vector<pair<int, int>> sortedPlayers;
        for (auto it = scores.begin(); it != scores.end(); it++)
            sortedPlayers.push_back(make_pair(it->first, it->second.getMax()));

        sort(sortedPlayers.begin(), sortedPlayers.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.second > b.second; });

        int counter = 1;
        for (auto it = sortedPlayers.begin(); it != sortedPlayers.end() && counter <= n; ++it, ++counter)
            cout << counter << ". Player " << it->first << " with score " << it->second << '\n';
    }

    void leave(int playerId)
    {
        if (scores.erase(playerId))
            cout << "Player " << playerId << " left...\n";
        else
            cout << "Player " << playerId << " not in the game\n";
    }

    int getPlayerScore(int playerId)
    {
        return scores[playerId].getMax();
    }
};

class driverProgram
{
private:
    gameManager gm;
    void addPlayer(int ID)
    {
        gm.enroll(ID);
    }

    void removePlayer(int ID)
    {
        gm.leave(ID);
    }

    void incrementPlayerScore(int ID, int points)
    {
        gm.updateScore(ID, points);
    }

    void getTopNPlayers(int count)
    {
        gm.getTopNPlayers(count);
    }

    int getPlayerScore(int ID)
    {
        return gm.getPlayerScore(ID);
    }

public:
    void start()
    {
        cout << "Welcome to the game!\n";
        int choice = 0;
        while (choice != 6)
        {
            cout << "\nMenu:\n";
            cout << "1. Enroll Player\n";
            cout << "2. Remove Player\n";
            cout << "3. Update Player Score\n";
            cout << "4. Get Top N Players\n";
            cout << "5. Get Player Score\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                int playerId;
                cout << "Enter player ID to enroll: ";
                cin >> playerId;
                addPlayer(playerId);
                break;
            }
            case 2:
            {
                int playerId;
                cout << "Enter player ID to remove: ";
                cin >> playerId;
                removePlayer(playerId);
                break;
            }
            case 3:
            {
                int playerId, points;
                cout << "Enter player ID & points to add to update score: ";
                cin >> playerId >> points;
                incrementPlayerScore(playerId, points);
                break;
            }
            case 4:
            {
                int n;
                cout << "Enter number of top players to retrieve: ";
                cin >> n;
                getTopNPlayers(n);
                break;
            }
            case 5:
            {
                int playerId;
                cout << "Enter player ID to get score: ";
                cin >> playerId;
                int score = getPlayerScore(playerId);
                cout << "Player " << playerId << " has a score of " << score << ".\n";
                break;
            }
            case 6:
                cout << "Exiting the game. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main()
{
    driverProgram game;
    game.start();
}