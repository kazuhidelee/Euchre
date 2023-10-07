#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;
// static const int PACK_SIZE = 24;

TEST(test_pack_default_ctor)
{
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here
TEST(test_deal_one_and_pack)
{
    Pack pack;
    for (int i = SPADES; i <= DIAMONDS; ++i)
    {
        for (int j = NINE; j <= ACE; ++j)
        {
            Suit suit = static_cast<Suit>(i);
            Rank rank = static_cast<Rank>(j);
            Card input = pack.deal_one();
            ASSERT_EQUAL(rank, input.get_rank());
            ASSERT_EQUAL(suit, input.get_suit());
        }
    }
}

TEST(test_shuffle_and_empty)
{
    Pack pack;
    pack.shuffle();
    Card first_card = pack.deal_one();
    ASSERT_EQUAL(first_card, Card(KING, CLUBS));
    ASSERT_FALSE(pack.empty());
    Card second_card = pack.deal_one();
    ASSERT_EQUAL(second_card, Card(JACK, HEARTS));
    ASSERT_FALSE(pack.empty());
    Card third_card = pack.deal_one();
    ASSERT_EQUAL(third_card, Card(NINE, SPADES));
    ASSERT_FALSE(pack.empty());
    for (int i = 0; i < 18; ++i)
    {
        pack.deal_one();
        ASSERT_FALSE(pack.empty());
    }
    Card third_to_last_card = pack.deal_one();
    ASSERT_EQUAL(third_to_last_card, Card(ACE, DIAMONDS));
    ASSERT_FALSE(pack.empty());
    Card second_to_last_card = pack.deal_one();
    ASSERT_EQUAL(second_to_last_card, Card(QUEEN, CLUBS));
    ASSERT_FALSE(pack.empty());
    Card last_card = pack.deal_one();
    ASSERT_EQUAL(last_card, Card(TEN, HEARTS));
    ASSERT_TRUE(pack.empty());
}

TEST_MAIN()
