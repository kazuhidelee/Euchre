#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Card.hpp"
#include "Pack.hpp"
#include "Player.hpp"
#include "Player.cpp"
using namespace std;

// NEED TO DO:
//  1. keeping track of scores of each team
//  2. determing which player is in which team?,
//  3. tell if the team euchred or marched
class Game
{
public:
    Game(char *argv[])
        : pack_file(argv[1]), decision(argv[2]), points(atoi(argv[3]))
    {
        // player 0 = [4],[5];
        // player 1 = [6],[7];
        // player 2 = [8],[9];
        // player 3 = [10],[11];
        for (int i = 0; i <= 6; i += 2)
        {
            players.push_back(Player_factory(argv[4 + i], argv[4 + i + 1]));
        }
    };

    void play()
    {
        // reading pack from file..
        ifstream ifs(pack_file);
        assert(ifs.is_open());
        Pack pack(ifs);
        // initializing...
        int round = 1;
        int team1_score = 0;
        int team2_score = 0;
        Card upcard;
        Suit order_up_suit;

        // print command line
        while (team1_score < points && team2_score < points)
        // shuffle the deck if user wants to
        {
            suffle(decision);
            // start dealing
            deal(players, pack, upcard, round);
            // determine the trump suit...
            making_trump(players, upcard, round, order_up_suit);
            // start playing...
            play_trick(players, round, order_up_suit);
        }

        // after this is round 2

        assert(false);
    };

private:
    string pack_file;
    string decision;
    int points;
    // Player *player;
    std::vector<Player *> players;
    Pack pack;
    // int round;
    vector<Card> hand;
    static const int PACK_SIZE = 24;
    std::array<Card, PACK_SIZE> cards;

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

    void print_decisions(string name, bool decision, Suit up_suit)
    {
        if (decision)
        {
            cout << name << " "
                 << "orders up" << up_suit << endl;
        }
        else
        {
            cout << name << " " << decision << endl;
        }
    }

    void print_cards_played()
    {
    }

    void print_win_hand(string name1, string name2)
    {
        cout << name1 << " "
             << "and"
             << " " << name2 << " "
             << "wint the hand" << endl;
    }

    void print_score(string name1, string name2, string name3, string name4, int score1, int score2)
    {
        cout << name1 << " "
             << "and"
             << " " << name3 << " "
             << "have " << score1 << " points" << endl;
        cout << name2 << " "
             << "and"
             << " " << name4 << " "
             << "have " << score2 << " points" << endl;
    }

    void suffle(string decision)
    {
        if (decision == "shuffle")
        {
            pack.shuffle();
        }
    }

    void deal(vector<Player *> players, Pack pack, Card &upcard, int round)
    {
        // Player *dealer = players[round % 4];
        // First cicle
        for (int i = 1; i < players.size() + 1; ++i)
        {
            // deals for player left of dealer & their teammate
            if (i % 2 != 0)
            {
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
            }
            // deals for dealer & their teammate
            else
            {
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
            }
        }
        // Second cicle
        for (int i = 1; i < players.size() + 1; ++i)
        {
            if (i % 2 == 0)
            {
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
            }
            else
            {
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
                players[(round % 4 + i) % 4]->add_card(pack.deal_one());
            }
        }
        upcard = pack.deal_one();
    }

    bool making_trump(vector<Player *> players, Card &upcard, int round, Suit &order_up_suit)
    {
        int make_round = 1;
        bool order_up = false;
        for (int i = 1; i < players.size() + 1; ++i)
        {
            // player left of dealer & their teammate making trump
            // cicle 1:
            if (i % 2 != 0)
            {
                order_up = players[(round % 4 + i) % 4]->make_trump(
                    upcard, false, make_round, order_up_suit);
                // print message
                print_decisions(players[(round % 4 + i) % 4]->get_name(), order_up, order_up_suit);
                if (order_up)
                    return true;
            }
            else if (i % 2 == 0)
            {
                // dealer's teammate making trump
                if (i == 2)
                {
                    order_up = players[(round % 4 + i) % 4]->make_trump(
                        upcard, false, make_round, order_up_suit);
                    print_decisions(players[(round % 4 + i) % 4]->get_name(), order_up, order_up_suit);
                    if (order_up)
                        return true;
                }
                // dealer making trump
                else
                {
                    order_up = players[(round % 4 + i) % 4]->make_trump(
                        upcard, true, make_round, order_up_suit);
                    print_decisions(players[(round % 4 + i) % 4]->get_name(), order_up, order_up_suit);
                    if (order_up)
                        return true;
                }
            }
        }
        // if no one orders up during the first round, go another round
        if (!order_up)
            make_round++;
        for (int i = 1; i < players.size() + 1; ++i)
        {
            if (i % 2 != 0)
            {
                order_up = players[(round % 4 + i) % 4]->make_trump(
                    upcard, false, make_round, order_up_suit);
                print_decisions(players[(round % 4 + i) % 4]->get_name(), order_up, order_up_suit);
                if (order_up)
                    return true;
            }
            else if (i % 2 == 0)
            {
                if (i == 2)
                {
                    order_up = players[(round % 4 + i) % 4]->make_trump(
                        upcard, false, make_round, order_up_suit);
                    print_decisions(players[(round % 4 + i) % 4]->get_name(), order_up, order_up_suit);
                    if (order_up)
                        return true;
                }
                else
                {
                    order_up = players[(round % 4 + i) % 4]->make_trump(
                        upcard, true, make_round, order_up_suit);
                    print_decisions(players[(round % 4 + i) % 4]->get_name(), order_up, order_up_suit);
                    if (order_up)
                        return true;
                }
            }
        }
    }

    void play_trick(vector<Player *> players, int &round, Suit trump)
    {
        // make a vector of cards that player have played
        vector<Card> cards_played;
        // the person to the left of dealer leads the card, and let the card let be led_card
        Card led_card = players[round % 4 + 1]->lead_card(trump);
        // first card played is the led card
        cards_played.push_back(led_card);
        cout << led_card << " led by " << players[round % 4 + 1]->get_name() << endl;
        for (int i = 2; i < players.size() + 1; ++i)
        {
            cards_played.push_back(players[(round % 4 + i) % 4]->play_card(led_card, trump));
        }
        // get index of the biggest card in this round/trick
        int max_index = 0;
        for (int j = 0; j < cards_played.size(); ++j)
        {
            if (Card_less(cards_played[max_index], cards_played[j], trump))
            {
                max_index = j;
            }
        }

        cout << players[(max_index + (round % 4 + 1)) % 4]->get_name() << " takes the trick " << endl;

        round++; // increasing the round !

        // INDEX: dealer = 4, lead = 0, lead+1  = 1, lead+2 = 2
        // have to keep track of score after this...
    }

    bool is_march_or_euchred();
};

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
int main(int argc, char *argv[])
{
    if (argc != 12)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    string pack_filename = argv[1];
    string shuffle_decision = argv[2];
    int points_to_win = atoi(argv[3]);
    string player_type_1 = argv[5];
    string player_type_2 = argv[7];
    string player_type_3 = argv[9];
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
        return 1;
    }

    if (player_type_3 != "Simple" && player_type_3 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }
    if (player_type_4 != "Simple" && player_type_4 != "Human")
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
             << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
             << "NAME4 TYPE4" << endl;
        return 1;
    }

    Game game(argv);
    game.play();

    return 0;
}