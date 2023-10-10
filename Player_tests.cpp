#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name)
{
    Player *alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_make_trump)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, SPADES));

    // Bob makes trump
    Card nine_spades(NINE, SPADES);
    Suit trump = SPADES;
    bool orderup = bob->make_trump(
        nine_spades, // Upcard
        true,        // Bob is also the dealer
        2,           // First round
        trump        // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);

    delete bob;
}

TEST(test_player_card)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, SPADES));
    bob->add_and_discard(Card(NINE, SPADES));
    // discard NINE of HEARTS, add NINE of SPADES
    Card played1 = bob->play_card(Card(ACE, HEARTS), CLUBS);
    ASSERT_EQUAL(Card(NINE, SPADES), played1);
    Card played2 = bob->play_card(Card(JACK, SPADES), SPADES);
    ASSERT_EQUAL(Card(ACE, SPADES), played2);

    delete bob;
}

TEST(test_lead_card)
{
    // Bob's hand
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
        Card(NINE, HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card left_bower(JACK, DIAMONDS);
    ASSERT_EQUAL(card_led, left_bower); // check led card

    delete bob;
}

TEST(test_player_make_trump_and_order_up_true)
{
    // Bob's hand
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(TEN, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, DIAMONDS));

    // Bob makes tump
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = bob->make_trump(
        nine_spades, // Upcard
        false,       // Bob is also the dealer
        2,
        trump // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete bob;
}

TEST(test_play_card_cant_follow_suit)
{
    // Bob's hand
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));

    Player *rob = Player_factory("Rob", "Simple");
    rob->add_card(Card(NINE, HEARTS));
    rob->add_card(Card(TEN, SPADES));
    rob->add_card(Card(QUEEN, CLUBS));
    rob->add_card(Card(KING, CLUBS));
    rob->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card led_card(JACK, DIAMONDS);
    Card bob_card_played = bob->play_card(
        led_card, // Jack of Diamonds is led
        HEARTS    // Trump suit
    );

    Card rob_card_played = rob->play_card(
        led_card, // Jack of Diamonds is led
        HEARTS    // Trump suit
    );

    // Verify the card Bob played
    ASSERT_EQUAL(bob_card_played, Card(JACK, DIAMONDS));
    ASSERT_EQUAL(rob_card_played, Card(TEN, SPADES));
    delete bob;
    delete rob;
}

TEST(test_player_make_trump_and_order_up_false)
{
    // Bob's hand
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(TEN, DIAMONDS));
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(KING, CLUBS));
    bob->add_card(Card(ACE, CLUBS));

    // Bob makes tump
    Card nine_dia(JACK, DIAMONDS);
    Suit trump = SPADES;
    bool orderup = bob->make_trump(
        nine_dia, // Upcard
        false,    // Bob is also the dealer
        2,        // First round
        trump     // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete bob;
}

TEST(test_player_card2)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, SPADES));
    bob->add_and_discard(Card(NINE, SPADES));
    // discard NINE of HEARTS, add NINE of SPADES
    bob->add_and_discard(Card(NINE, CLUBS));
    // discard NINE of SPADES, add NINE of CLUBS
    bob->add_and_discard(Card(NINE, CLUBS));

    Card played1 = bob->play_card(Card(ACE, HEARTS), CLUBS);
    ASSERT_EQUAL(Card(NINE, SPADES), played1);
    Card played2 = bob->play_card(Card(JACK, SPADES), SPADES);
    ASSERT_EQUAL(Card(ACE, SPADES), played2);

    delete bob;
}

TEST_MAIN()
