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

TEST(defult_initialize)
{
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_get_suit_trump)
{
    Card a;
    Card b(JACK, CLUBS);
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(SPADES, a.get_suit(SPADES));
    ASSERT_EQUAL(SPADES, b.get_suit(SPADES));
    ASSERT_EQUAL(HEARTS, c.get_suit(SPADES));
}

TEST(test_face_or_ace)
{
    Card a;
    Card b(JACK, CLUBS);
    Card c(QUEEN, HEARTS);
    Card d(KING, SPADES);
    Card e(ACE, HEARTS);
    ASSERT_FALSE(a.is_face_or_ace());
    ASSERT_TRUE(b.is_face_or_ace());
    ASSERT_TRUE(c.is_face_or_ace());
    ASSERT_TRUE(d.is_face_or_ace());
    ASSERT_TRUE(e.is_face_or_ace());
}

TEST(test_right_bower)
{
    Card a;
    Card b(JACK, CLUBS);
    Card c(QUEEN, HEARTS);
    Card d(JACK, HEARTS);
    Card e(JACK, DIAMONDS);
    ASSERT_FALSE(a.is_right_bower(HEARTS));
    ASSERT_FALSE(b.is_right_bower(HEARTS));
    ASSERT_FALSE(c.is_right_bower(HEARTS));
    ASSERT_TRUE(d.is_right_bower(HEARTS));
    ASSERT_FALSE(e.is_right_bower(HEARTS));
}

TEST(test_left_bower)
{
    Card a;
    Card b(JACK, CLUBS);
    Card c(QUEEN, HEARTS);
    Card d(JACK, HEARTS);
    Card e(JACK, DIAMONDS);
    ASSERT_FALSE(a.is_left_bower(HEARTS));
    ASSERT_FALSE(b.is_left_bower(HEARTS));
    ASSERT_FALSE(c.is_left_bower(HEARTS));
    ASSERT_FALSE(d.is_left_bower(HEARTS));
    ASSERT_TRUE(e.is_left_bower(HEARTS));
}

TEST(test_is_trump)
{
    Card a(NINE, HEARTS);
    Card b(TEN, HEARTS);
    Card c(JACK, HEARTS);
    Card d(QUEEN, HEARTS);
    Card e(KING, HEARTS);
    Card f(ACE, HEARTS);
    Card g(TEN, DIAMONDS);
    Card h(JACK, DIAMONDS);

    ASSERT_TRUE(a.is_trump(HEARTS));
    ASSERT_TRUE(b.is_trump(HEARTS));
    ASSERT_TRUE(c.is_trump(HEARTS));
    ASSERT_TRUE(d.is_trump(HEARTS));
    ASSERT_TRUE(e.is_trump(HEARTS));
    ASSERT_TRUE(f.is_trump(HEARTS));
    ASSERT_FALSE(g.is_trump(HEARTS));
    ASSERT_TRUE(h.is_trump(HEARTS));
}

TEST(test_ostream)
{
    ostringstream expected1;
    ostringstream actual1;
    Card a;
    expected1 << "Two of Spades";
    actual1 << a;
    ASSERT_EQUAL(expected1.str(), actual1.str());

    ostringstream expected2;
    ostringstream actual2;
    Card b(JACK, DIAMONDS);
    expected2 << "Jack of Diamonds";
    actual2 << b;
    ASSERT_EQUAL(expected2.str(), actual2.str());

    ostringstream expected3;
    ostringstream actual3;
    Card c(KING, HEARTS);
    expected3 << "King of Hearts";
    actual3 << c;
    ASSERT_EQUAL(expected3.str(), actual3.str());

    ostringstream expected4;
    ostringstream actual4;
    Card d(FIVE, CLUBS);
    expected4 << "Five of Clubs";
    actual4 << d;
    ASSERT_EQUAL(expected4.str(), actual4.str());
}

TEST(test_istream)
{
    Card a, b, c;
    istringstream expected1("Five of Hearts");
    expected1 >> a;
    ASSERT_EQUAL(a.get_rank(), FIVE);
    ASSERT_EQUAL(a.get_suit(), HEARTS);

    istringstream expected2("Jack of Spades");
    expected2 >> b;
    ASSERT_EQUAL(b.get_rank(), JACK);
    ASSERT_EQUAL(b.get_suit(), SPADES);

    istringstream expected3("King of Diamonds");
    expected3 >> c;
    ASSERT_EQUAL(c.get_rank(), KING);
    ASSERT_EQUAL(c.get_suit(), DIAMONDS);
}

TEST_MAIN()
