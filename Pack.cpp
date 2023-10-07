#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"
#include "Card.hpp"
#include <sstream>

using namespace std;

// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack()
{
	for (int i = SPADES; i <= DIAMONDS; ++i)
	{
		for (int j = NINE; j <= ACE; ++j)
		{
			Suit suit = static_cast<Suit>(i);
			Rank rank = static_cast<Rank>(j);
			Card a(rank, suit);
			cards[i * 6 + (j - 7)] = a;
		}
	}
	next = 0;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream &pack_input)
{
	for (int i = 0; i < PACK_SIZE; ++i)
	{
		pack_input >> cards[i];
	}
	next = 0;
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one()
{
	int next_index = next;
	next += 1;
	return cards[next_index];
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset()
{
	next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle()
{
	Card copy[PACK_SIZE];
	int i = 0;
	// put this copy inside the 7 time for loop
	int k = 0;
	for (int j = 0; j < 7; ++j)
	{
		for (i = 0; i < PACK_SIZE; ++i)
		{
			copy[i] = cards[i];
		}
		for (k = 0; k < PACK_SIZE; ++k)
		{
			if (k + (k + 1) < PACK_SIZE)
			{
				cards[(k + (k + 1))] = copy[k];
			}
			else
			{
				cards[(k + (k + 1)) - PACK_SIZE - 1] = copy[k];
			}
		}
	}
	reset();

	// copy over first half and second half of the array using the first copy[i] = cards[i]
	// go through and copy it one by one
	// shuffle 7 times
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const
{
	// if (next > 23)
	// {
	// 	return true;
	// }
	// else
	// {
	// 	return false;
	// }

	return next - PACK_SIZE >= 0;
}
