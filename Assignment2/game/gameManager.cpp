#include <iostream>
#include "../skiplists/SkipList.cpp"
#include <map>
#include <algorithm>

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

    int getPlayerScore(int ID) {
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