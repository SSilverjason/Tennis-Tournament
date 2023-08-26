#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class Player        // class player
{
public:
    Player(string name) : name(name), score(0), gamesWon(0), setsWon(0) {}      

    string getName() const { return name; }
    int getScore() const { return score; }
    //void increaseScore() {score+=15}
    void resetScore() { score = 0; }
    int getGamesWon() const { return gamesWon; }
    void increaseGamesWon() { gamesWon++; }
    void resetGamesWon() { gamesWon = 0; }
    int getSetsWon() const { return setsWon; }
    void increaseSetsWon() { setsWon++; }
    void resetSetsWon() { setsWon = 0; }

    void increaseScore()
    {
        if (score == 0 || score==15)
        {
         score += 5;
        }
        score += 10;
    }

private:
    string name;
    int score;
    int gamesWon;
    int setsWon;
};

class Tournament
{
public:
    Tournament() {}

    void addPlayer(Player player)
    {
        players.push_back(player);
    }

    void play() 
    {
        srand(time(0));
        for (int setNum = 1; setNum <= 3; setNum++)
        {
            cout << "SET " << setNum << endl;
            vector<Player> winners;
            random_shuffle(players.begin(), players.end());
            int numPairs = players.size() / 2;
            for (int i = 0; i < numPairs; i++)
            {
                int index1 = i * 2;
                int index2 = index1 + 1;
                cout << players[index1].getName() << " vs " << players[index2].getName() << endl;
                playMatch(players[index1], players[index2]);

                if (players[index1].getSetsWon() > players[index2].getSetsWon())
                {
                    winners.push_back(players[index1]);
                    cout << players[index1].getName() << " wins the match!" << endl;
                }
                else
                {
                    winners.push_back(players[index2]);   
                    cout << players[index2].getName() << " wins the match!" << endl;
                }
                cout << endl;
                cout << "Press any key to continue..." << endl;
                cin.get();

                if (players[index1].getSetsWon() >= 9)
                {
                    winners.push_back(players[index2]);
                }
                else if (players[index2].getSetsWon() >= 9)
                {
                    winners.push_back(players[index1]);
                }
            }

            players = winners;
        }
        cout << "1ST PLACE: " << players[0].getName() << endl;
       if (players.size() == 2)
       {
           cout << "2ND PLACE: " << players[1].getName() << endl;
       }
    }

private:
    vector<Player> players;

    void playMatch(Player& player1, Player& player2)
    {
        srand(time(0));
        player1.resetScore();
        player2.resetScore();
        bool servingPlayer1 = (rand() % 2 == 0);
        int totalPoints = 0;
        int gamesPlayer1 = 0;
        int gamesPlayer2 = 0;
        while (true)
        {
            totalPoints++;
            if (servingPlayer1)
            {
                if (rand() % 2 == 0)
                {
                    player1.increaseScore();
                    cout << player1.getName() << " wins a point. Score: " << player1.getScore() << "/" << player2.getScore() << " (serving)" << endl;
                }
                else
                {
                    player2.increaseScore();
                    cout << player2.getName() << " wins a point. Score: " << player1.getScore() << "/" << player2.getScore() << " (not serving)" << endl;
                }
            }
            else
            {
                if (rand() % 2 == 0)
                {
                    player2.increaseScore();
                    cout << player2.getName() << " wins a point. Score: " << player1.getScore() << "/" << player2.getScore() << " (serving)" << endl;
                }
                else
                {
                    player1.increaseScore();
                    cout << player1.getName() << " wins a point. Score: " << player1.getScore() << "/" << player2.getScore() << " (not serving)" << endl;
                }
            }
            if (player1.getScore() >= 40 || player2.getScore() >= 40)  // check deuce
            {
                if (abs(player1.getScore() - player2.getScore()) >= 2) //check win condition
                {
                    if (player1.getScore() > player2.getScore()) // increase game score
                    {
                        gamesPlayer1++;
                        cout << player1.getName() << " wins the game!" << endl;
                        player1.increaseSetsWon(); // update the number of sets won by player 1
                    }
                    else
                    {
                        gamesPlayer2++;
                        cout << player2.getName() << " wins the game!" << endl;
                        player2.increaseSetsWon(); // update the number of sets won by player 2
                    }
                    player1.resetScore();
                    player2.resetScore();
                    if (gamesPlayer1 == 3 || gamesPlayer2 == 3)
                    {
                        break;
                    }
                }
            }
            servingPlayer1 = !servingPlayer1;
        }

        if (gamesPlayer1 > gamesPlayer2)
        {
            cout << player1.getName() << " wins the set! SET(S) won: " << player1.getSetsWon() << endl;
        }
        else
        {
            cout << player2.getName() << " wins the set! SET(S) won: " << player2.getSetsWon() << endl;
        }
    }
};

int main()
{
    Tournament tournament;
    for (int i = 1; i <= 8; i++)
    {
        cout << "Enter player " << i << " name: ";
        string name;
        cin >> name;
        tournament.addPlayer(Player(name));
    }
    tournament.play();
    return 0;
}