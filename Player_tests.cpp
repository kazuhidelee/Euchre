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
    Suit trump;
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

TEST(test_make_trump2)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, SPADES));

    // Bob makes trump
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = bob->make_trump(
        nine_spades, // Upcard
        false,       // Bob is also the dealer
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
        true,        // Bob is not the dealer
        2,
        trump // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, CLUBS);
    delete bob;
}

TEST(test_play_card_cant_follow_suit)
{
    // problem with function. should be nine of hearts for rob because left bower is heart
    //  Bob's hand
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, DIAMONDS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(JACK, HEARTS));

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

    Card rob_card_played2 = rob->play_card(
        led_card, // Jack of Diamonds is led
        HEARTS    // Trump suit
    );

    Card rob_card_played3 = rob->play_card(
        led_card, // Jack of Diamonds is led
        HEARTS    // Trump suit
    );

    Card rob_card_played4 = rob->play_card(
        led_card, // Jack of Diamonds is led
        HEARTS    // Trump suit
    );

    Card rob_card_played5 = rob->play_card(
        led_card, // Jack of Diamonds is led
        HEARTS    // Trump suit
    );

    // Verify the card Bob played
    ASSERT_EQUAL(bob_card_played, Card(JACK, HEARTS));
    ASSERT_EQUAL(rob_card_played, Card(NINE, HEARTS));
    ASSERT_EQUAL(rob_card_played2, Card(TEN, SPADES));
    ASSERT_EQUAL(rob_card_played3, Card(QUEEN, CLUBS));
    ASSERT_EQUAL(rob_card_played4, Card(KING, CLUBS));
    ASSERT_EQUAL(rob_card_played5, Card(ACE, SPADES));

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

    Card played1 = bob->play_card(Card(ACE, HEARTS), CLUBS);
    ASSERT_EQUAL(Card(TEN, SPADES), played1);
    Card played2 = bob->play_card(Card(JACK, SPADES), SPADES);
    ASSERT_EQUAL(Card(ACE, SPADES), played2);

    delete bob;
}

TEST(test_screw_the_dealer)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, CLUBS));

    // Bob makes trump
    Card nine_spades(NINE, SPADES);
    Suit trump;
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

TEST(test_dont_pick_up_trump)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(TEN, CLUBS));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, CLUBS));

    // Bob makes trump
    Card nine_spades(NINE, DIAMONDS);
    Suit trump = SPADES;
    bool orderup = bob->make_trump(
        nine_spades, // Upcard
        true,        // Bob is also the dealer
        1,           // First round
        trump        // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete bob;
}

TEST(test_pick_up_trump)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(ACE, CLUBS));

    // Bob makes trump
    Card nine_spades(NINE, SPADES);
    Suit trump;
    bool orderup = bob->make_trump(
        nine_spades, // Upcard
        true,        // Bob is also the dealer
        1,           // First round
        trump        // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

    delete bob;
}

TEST(one_card)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));
    Card played1 = bob->play_card(Card(ACE, DIAMONDS), CLUBS);
    ASSERT_EQUAL(Card(JACK, SPADES), played1);

    delete bob;
}

TEST(two_cards)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(KING, SPADES));
    Card played1 = bob->play_card(Card(JACK, SPADES), CLUBS);
    ASSERT_EQUAL(Card(JACK, CLUBS), played1);

    delete bob;
}

TEST(test_not_follow_suit)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(KING, SPADES));
    Card played1 = bob->play_card(Card(JACK, SPADES), CLUBS);
    ASSERT_EQUAL(Card(KING, SPADES), played1);

    delete bob;
}

TEST(test_not_follow_suit2)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(KING, SPADES));
    Card played1 = bob->play_card(Card(ACE, HEARTS), DIAMONDS);
    ASSERT_EQUAL(Card(KING, SPADES), played1);

    delete bob;
}

TEST(test_add_and_discard)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_and_discard(Card(TEN, HEARTS));
    // add ten of hearts and discard nine of hearts
    Card played1 = bob->play_card(Card(ACE, HEARTS), DIAMONDS);
    // play ten of hearts
    ASSERT_EQUAL(played1, Card(TEN, HEARTS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_and_discard(Card(NINE, HEARTS));
    // discard nine of hearts and add ten of hearts
    Card played2 = bob->play_card(Card(ACE, HEARTS), DIAMONDS);
    // play ten of hearts
    ASSERT_EQUAL(played2, Card(TEN, HEARTS));

    delete bob;
}

TEST(test_add_and_discard_2)
{
    Player *bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(ACE, CLUBS));
    bob->add_and_discard(Card(TEN, HEARTS));
    // add ten of hearts and discard jack of spades
    Card played1 = bob->play_card(Card(ACE, SPADES), HEARTS);

    ASSERT_EQUAL(played1, Card(QUEEN, CLUBS));

    delete bob;
}

TEST(test_for_euchre)
{
    Player *barb = Player_factory("Barbara", "Simple");
    barb->add_card(Card(JACK, SPADES));
    barb->add_card(Card(NINE, SPADES));
    barb->add_card(Card(TEN, SPADES));
    barb->add_card(Card(ACE, HEARTS));
    barb->add_card(Card(KING, HEARTS));
    // add ten of hearts and discard jack of spades
    Card upcard = Card(JACK, DIAMONDS);
    Suit order_up_suit;

    ASSERT_TRUE(barb->make_trump(upcard, false, 2, order_up_suit));
    ASSERT_EQUAL(order_up_suit, HEARTS);

    delete barb;
}

TEST(test_for_euchre2)
{
    Player *barb = Player_factory("Barbara", "Simple");
    barb->add_card(Card(KING, CLUBS));
    barb->add_card(Card(QUEEN, CLUBS));
    barb->add_card(Card(TEN, HEARTS));
    barb->add_card(Card(NINE, HEARTS));

    ASSERT_EQUAL(Card(KING, CLUBS), barb->lead_card(HEARTS));

    delete barb;
}
TEST_MAIN()
