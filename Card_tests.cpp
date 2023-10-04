#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_card_ctor)
{
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_suit_comparison)
{
    Card ace_hearts(ACE, HEARTS);
    Card ace_diamonds(ACE, DIAMONDS);
    ASSERT_TRUE(ace_hearts < ace_diamonds);
}

TEST(test_less_than)
{
    Card ace_hearts(ACE, HEARTS);
    Card jack_diamond(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(ace_hearts, jack_diamond, HEARTS));
}

TEST(test_suit_next)
{
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
}

TEST(test_bowers)
{
    Card jack_diamond(JACK, DIAMONDS);
    Card jack_hearts(JACK, HEARTS);
    ASSERT_TRUE(jack_diamond.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_diamond.is_left_bower(HEARTS));
}

TEST_MAIN()
