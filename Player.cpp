#include <cassert>
#include <iostream>
#include <array>
#include "Player.hpp"
#include <vector>
#include <algorithm>

using namespace std;

class SimplePlayer : public Player
{
public:
	SimplePlayer(const string &name_input)
		: type("Simple"), name(name_input) {}
	// EFFECTS returns player's name
	const std::string &get_name() const override
	{
		return name;
	}
	// REQUIRES player has less than MAX_HAND_SIZE cards
	// EFFECTS  adds Card c to Player's hand
	void add_card(const Card &c) override
	{
		hand.push_back(c);
	}

	// REQUIRES round is 1 or 2
	// MODIFIES order_up_suit
	// EFFECTS If Player wishes to order up a trump suit then return true and
	//   change order_up_suit to desired suit.  If Player wishes to pass, then do
	//   not modify order_up_suit and return false.
	bool make_trump(const Card &upcard, bool is_dealer,
					int round, Suit &order_up_suit) const override
	{
		Suit up_suit = upcard.get_suit();
		int card_count = 0;
		if (round == 1)
		{
			for (int i = 0; i < hand.size(); ++i)
			{
				if (hand[i].is_left_bower(up_suit) || hand[i].is_right_bower(up_suit) ||
					(hand[i].is_face_or_ace() && hand[i].is_trump(up_suit)))
				{
					card_count += 1;
				}
			}
			if (card_count >= 2)
			{
				order_up_suit = up_suit;
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (round == 2 && !is_dealer)
		{
			for (int i = 0; i < hand.size(); ++i)
			{
				if (hand[i].is_left_bower(up_suit) || hand[i].is_right_bower(up_suit) ||
					(hand[i].is_face_or_ace() && hand[i].is_trump(up_suit)))
				{
					card_count += 1;
				}
			}
			if (card_count >= 1)
			{
				// cout << card_count;
				order_up_suit = up_suit;
				return true;
			}
			else
			{
				// cout << card_count << endl;
				return false;
			}
		}
		else
		{
			order_up_suit = Suit_next(up_suit);
			return true; // Need to implement screw the dealer
		}
	}

	// REQUIRES Player has at least one card
	// EFFECTS  Player adds one card to hand and removes one card from hand.
	void add_and_discard(const Card &upcard) override
	{
		int min_index = 0;
		hand.push_back(upcard);
		Suit upsuit = upcard.get_suit();
		for (int i = 0; i < hand.size(); ++i)
		{
			if (Card_less(hand[i], hand[min_index], upsuit))
			{
				min_index = i;
			}
		}
		hand.erase(hand.begin() + min_index);
	}

	// REQUIRES Player has at least one card
	// EFFECTS  Leads one Card from Player's hand according to their strategy
	//   "Lead" means to play the first Card in a trick.  The card
	//   is removed the player's hand.
	Card lead_card(Suit trump) override
	{
		int max_index = 0;
		bool all_trump = true;
		// Check if all cards are trump
		for (int k = 0; k < hand.size(); ++k)
		{
			if (!(hand[k].is_trump(trump)))
			{
				all_trump = false;
			}
		}
		if (!(all_trump))
		{
			for (int i = 0; i < hand.size(); ++i)
			{
				if (!(hand[i].is_trump(trump)) && (Card_less(hand[max_index], hand[i], trump)))
				{
					max_index = i;
				}
			}
		}
		else
		{
			for (int j = 0; j < hand.size(); ++j)
			{
				if (Card_less(hand[max_index], hand[j], trump))
				{
					max_index = j;
				}
			}
		}
		Card lead = hand[max_index];
		hand.erase(hand.begin() + max_index);
		return lead;
	}

	// REQUIRES Player has at least one card
	// EFFECTS  Plays one Card from Player's hand according to their strategy.
	//   The card is removed from the player's hand.
	Card play_card(const Card &led_card, Suit trump) override
	{
		bool follow_suit = false;
		Suit led_suit = led_card.get_suit();
		int highest = 0;
		int lowest = 0;
		// Check if the player can follow suit
		for (int i = 0; i < hand.size(); ++i)
		{
			if (hand[i].get_suit() == led_suit)
			{
				follow_suit = true;
			}
		}
		if (follow_suit)
		{
			for (int j = 0; j < hand.size(); ++j)
			{
				//does this consider the left bower?? hand[i].is_left_bower()
				if (Card_less(hand[highest], hand[j], led_card, trump) &&
					hand[j].get_suit() == led_suit)
				{
					highest = j;
				}
			}
			Card most = hand[highest];
			hand.erase(hand.begin() + highest);
			return most;
		}
		else
		{
			for (int k = 0; k < hand.size(); ++k)
			{
				if (Card_less(hand[k], hand[lowest], trump))
				{
					lowest = k;
				}
			}
			Card least = hand[lowest];
			hand.erase(hand.begin() + lowest);
			return least;
		}
	}

	// Needed to avoid some compiler errors
	//~Player() {}
private:
	string type;
	string name;
	vector<Card> hand;
};

class HumanPlayer : public Player
{
public:
	HumanPlayer(const string &name_input)
		: type("Human"), name(name_input) {}
	// EFFECTS returns player's name

	const std::string &get_name() const override
	{
		return name;
	}

	// REQUIRES player has less than MAX_HAND_SIZE cards
	// EFFECTS  adds Card c to Player's hand
	void add_card(const Card &c) override
	{
		hand.push_back(c);
	}

	// REQUIRES round is 1 or 2
	// MODIFIES order_up_suit
	// EFFECTS If Player wishes to order up a trump suit then return true and
	//   change order_up_suit to desired suit.  If Player wishes to pass, then do
	//   not modify order_up_suit and return false.
	bool make_trump(const Card &upcard, bool is_dealer,
					int round, Suit &order_up_suit) const override
	{
		string decision;
		print_hand();
		cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
		cin >> decision;
		if (decision != "pass")
		{
			order_up_suit = string_to_suit(decision);
			return true;
		}
		else
		{
			return false;
		}
	}

	// REQUIRES Player has at least one card
	// EFFECTS  Player adds one card to hand and removes one card from hand.
	void add_and_discard(const Card &upcard) override
	{
		int decision;
		print_hand();
		cout << "Discard upcard: [-1]\n";
		cout << "Human player " << name << ", please select a card to discard:\n";
		cin >> decision;
		add_card(upcard);

		if (decision == -1)
		{
			hand.erase(hand.end());
		}
		else
		{
			hand.erase(hand.begin() + decision);
		}
		sort(hand.begin(), hand.end());
	}

	// REQUIRES Player has at least one card
	// EFFECTS  Leads one Card from Player's hand according to their strategy
	//   "Lead" means to play the first Card in a trick.  The card
	//   is removed the player's hand.
	Card lead_card(Suit trump) override
	{
		int decision;
		Card lead;
		print_hand();
		cout << "Human player " << name << ", please select a card:\n";
		cin >> decision;
		lead = hand[decision];
		hand.erase(hand.begin() + decision);
		return lead;
	}

	// REQUIRES Player has at least one card
	// EFFECTS  Plays one Card from Player's hand according to their strategy.
	//   The card is removed from the player's hand.
	Card play_card(const Card &led_card, Suit trump) override
	{
		int decision;
		Card lead;
		print_hand();
		cout << "Human player " << name << ", please select a card:\n";
		cin >> decision;
		lead = hand[decision];
		hand.erase(hand.begin() + decision);
		return lead;
	}

	// Maximum number of cards in a player's hand
	static const int MAX_HAND_SIZE = 5;

	// Needed to avoid some compiler errors
	//~Player() {}
private:
	string type;
	string name;
	vector<Card> hand;
	void print_hand() const
	{
		for (size_t i = 0; i < hand.size(); ++i)
			cout << "Human player " << name << "'s hand: "
				 << "[" << i << "] " << hand[i] << "\n";
	}
};

// EFFECTS: Returns a pointer to a player with the given name and strategy
// To create an object that won't go out of scope when the function returns,
// use "return new Simple(name)" or "return new Human(name)"
// Don't forget to call "delete" on each Player* after the game is over
Player *
Player_factory(const std::string &name,
			   const std::string &strategy)
{
	// We need to check the value of strategy and return
	// the corresponding player type.
	if (strategy == "Simple")
	{
		// The "new" keyword dynamically allocates an object.
		return new SimplePlayer(name);
	}
	// Repeat for each other type of Player
	if (strategy == "Human")
	{
		// The "new" keyword dynamically allocates an object.
		return new HumanPlayer(name);
	}
	// Invalid strategy if we get here
	assert(false);
	return nullptr;
}

// EFFECTS: Prints player's name to os
std::ostream &operator<<(std::ostream &os, const Player &p)
{
	os << p.get_name();
	return os;
}