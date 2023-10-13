#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
using namespace std;

// 1. First, print the executable and all arguments on the first line.
//     Print a single space at the end, which makes it easier to print an array.
// 2. At the beginning of each hand, announce the hand, starting at zero,
//     followed by the dealer and the upcard.
// 3. Print the decision of each player during the making procedure.
//     Print an extra newline when making, adding, and discarding is complete.
// 4. Each of the five tricks is announced, including the lead, cards played and the player that took the trick.
//     Print an extra newline at the end of each trick.
// 5. At the end of the hand, print the winners of the hand. When printing the names of a partnership,
//     print the player with the lower index first.
// 6. If a march occurs, print march! followed by a newline. If euchre occurs,
//     print euchred! followed by a newline. If neither occurs, print nothing.
// 7. Print the score, followed by an extra newline.
// 8. When the game is over, print the winners of the game.

class Game
{
public:
    Game(/* game details */);
    void play();

private:
    std::vector<Player *> players;
    Pack pack;
    // ...
    void print_command_line(string exe, string pack_filename, string shuffle_decision,
                            int points_to_win, string player_name_1, string player_type_1,
                            string player_name_2, string player_type_2, string player_name_3, string player_type_3,
                            string player_name_4, string player_type_4)
    {
        cout << exe << " " << pack_filename << " " << shuffle_decision << " " << points_to_win
             << " " << player_name_1 << " " << player_type_1 << " " << player_name_2 << " "
             << player_type_2 << " " << player_name_3 << " " << player_type_3 << " "
             << player_name_3 << " " << player_type_3 << endl;
    }

    void annoucement(int hand, string dealer, Card upcard)
    {
        cout << "Hand"
             << " " << hand << endl;
        cout << dealer << " "
             << "deals" << endl;
        cout << upcard << "turned up" << endl;
    }

    void print_decisions(string name, string decision)
    {
        cout << name << " " << decision << endl;
    }

    void print_decisions(string name, Suit up_suit)
    {
        cout << name << " "
             << "orders up" << up_suit << endl;
    }

    void print_cards_played()
    {
    }

    void shuffle();
    void deal(/* ... */);
    void make_trump(/* ... */);
    void play_hand(/* ... */);
    // ...
};

int main(int argc, char *argv[])
{
    // checks for 12 arguments
    if (argc != 12)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    string exe = argv[0];
    string pack_filename = argv[1];
    string shuffle_decision = argv[2];
    int points_to_win = atoi(argv[3]);
    string player_name_1 = argv[4];
    string player_type_1 = argv[5];
    string player_name_2 = argv[6];
    string player_type_2 = argv[7];
    string player_name_3 = argv[8];
    string player_type_3 = argv[9];
    string player_name_4 = argv[10];
    string player_type_4 = argv[11];

    ifstream input_file;
    input_file.open((pack_filename).c_str());

    // if input_file is open, if not print error message
    if (!input_file.is_open())
    {
        cout << "Error opening " << pack_filename << endl;
        return 1;
    }

    // if points_to_win is not 1-100 inclusive, print error message
    if (!(points_to_win >= 1 && points_to_win <= 100))
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    // if shuffle_decision is not present, print error message
    if (shuffle_decision != "shuffle" && shuffle_decision != "noshuffle")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    // if player type is not simple or human, print error message
    if (player_type_1 != "Simple" && player_type_1 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    if (player_type_2 != "Simple" && player_type_2 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    if (player_type_3 != "Simple" && player_type_3 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }
    if (player_type_4 != "Simple" && player_type_4 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
    }

    return 0;
}