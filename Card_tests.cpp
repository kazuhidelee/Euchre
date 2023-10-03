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

// Add more test cases here

TEST_MAIN()
