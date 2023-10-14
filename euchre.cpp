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

class Game
{
public:
    Game(vector<Player *> players_in)
        : players(players_in){};

    // void play()
    // {
    //     // for (int i = 0; i < players.size(); ++i)
    //     // {
    //     //     Player_factory(players[i]->get_name(), players[i]->get_type());
    //     // }
    //     Player *zero = Player_factory("Bob", "Simple");
    //     Player *one = Player_factory("Bob", "Simple");
    //     Player *two = Player_factory("Bob", "Simple");
    //     Player *three = Player_factory("Bob", "Simple");
    //     // print command line
    //     // decide dealer, upcard

    //     // print dealer and upcard

    //     // print hand and ask pass or pick up suit(make trump)

    //     // print decision

    //     // ask dealer to make trump or no?

    //     // print led and played cards

    //     // print winner for the trink

    //     // print winnte for the round

    //     // keep going...

    //     // announce winner
    // };

private:
    Player *player;
    std::vector<Player *> players;
    Pack pack;
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

    void deal(vector<Player *> players, Pack pack, Card &upcard, int round)
    {
        // Player *dealer = players[round % 4];
        pack.shuffle();
        for (int i = 1; i < players.size() + 1; ++i)
        {
            // deals for player left of dealer & their teammate
            if (i % 2 != 0)
            {
                players[round % 4 + i]->add_card(pack.deal_one());
                players[round % 4 + i]->add_card(pack.deal_one());
                players[round % 4 + i]->add_card(pack.deal_one());
            }
            // deals for dealer & their teammate
            else
            {
                players[round % 4 + i]->add_card(pack.deal_one());
                players[round % 4 + i]->add_card(pack.deal_one());
            }
        }

        upcard = pack.deal_one();
    }

    bool making_trump(vector<Player *> players, Card &upcard, int round, Suit &order_up_suit)
    {

        for (int i = 1; i < players.size() + 1; ++i)
        {
            // player left of dealer & their teammate making trump
            if (i % 2 != 0)
            {
                bool order_up = players[round % 4 + i]->make_trump(
                    upcard, false, round, order_up_suit);
                if (order_up)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else if (i % 2 == 0)
            {
                // dealer's teammate making trump
                if (i == 2)
                {
                    bool order_up = players[round % 4 + i]->make_trump(
                        upcard, false, round, order_up_suit);
                    if (order_up)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                // dealer making trump
                else
                {
                    bool order_up = players[round % 4 + i]->make_trump(
                        upcard, true, round, order_up_suit);
                    if (order_up)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }

    void play_trick(vector<Player *> player, int round, Suit trump)
    {
        // make a vector of cards that player have played
        vector<Card> cards_played;
        // the person to the left of dealer leads the card, and let the card let be led_card
        Card led_card = players[round % 4 + 1]->lead_card(trump);
        // first card played is the led card
        cards_played.push_back(led_card);
        cout << led_card << " led by " << players[round % 4 + 1]->get_name() << endl;
        for (int i = 2; i < player.size(); ++i)
        {
            if (i < player.size())
            {
                // not sure about the indexing tbh
                cards_played.push_back(player[round % 4 + i]->play_card(led_card, trump));
            }
            else
            {
                cards_played.push_back(player[round % 4]->play_card(led_card, trump));
            }
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
        if ((round % 4 + 1 + max_index) < players.size())
        {
            cout << players[round % 4 + 1 + max_index]->get_name() << " takes the trick " << endl;
        }
        else
        {
            cout << players[round % 4 + 1 + max_index]->get_name() << " takes the trick " << endl;
        }
        // INDEX: dealer = 4, lead = 0, lead+1  = 1, lead+2 = 2
        // have to keep track of score after this...
    }
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

    return 0;
}