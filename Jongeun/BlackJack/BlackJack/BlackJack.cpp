
/**

TODO: Implemented List 
1. String view
2. lamda function and lamda captures  
3. inline function 
4. std::array 
5. class templete and function templete 
6. friend class and ref qualifier 
7. default argument and delete function 
8. constant expresstion and constexpr and consteval
9. lvalue references and rvalue references 
10. default initialization , delegating initialization 

**/

#include <algorithm> // for std::shuffle
#include <array>
#include <cassert>
#include <iostream>
#include "Random.h"
#include "Card.h"
#include "Deck.h"
#include "Player.h"



namespace Settings
{
    // Maximum score before losing.
    constexpr int bust{21};

    // Minium score that the dealer has to have.
    constexpr int dealerStopsAt{17};
}

bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
        case 'h':
            return true;
        case 's':
            return false;
        }
    }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck &deck, Player &player)
{
    while (player.score() < Settings::bust && playerWantsHit())
    {
        Card card{deck.dealCard()};
        player.addToScore(card);
        player.consumeAces(Settings::bust);

        std::cout << "You were dealt " << card << ". You now have: " << player.score() << '\n';
    }

    if (player.score() > Settings::bust)
    {
        std::cout << "You went bust!\n";
        return true;
    }

    return false;
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck &deck, Player &dealer)
{
    while (dealer.score() < Settings::dealerStopsAt)
    {
        Card card{deck.dealCard()};
        dealer.addToScore(card);
        dealer.consumeAces(Settings::bust);

        std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score() << '\n';
    }

    if (dealer.score() > Settings::bust)
    {
        std::cout << "The dealer went bust!\n";
        return true;
    }

    return false;
}

enum class GameResult
{
    playerWon,
    dealerWon,
    tie
};

GameResult playBlackjack()
{
    Deck deck{};
    deck.shuffle();

    Player dealer{};
    Card card1{deck.dealCard()};
    dealer.addToScore(card1);
    std::cout << "The dealer is showing " << card1 << " (" << dealer.score() << ")\n";

    Player player{};
    Card card2{deck.dealCard()};
    Card card3{deck.dealCard()};
    player.addToScore(card2);
    player.addToScore(card3);
    std::cout << "You are showing " << card2 << ' ' << card3 << " (" << player.score() << ")\n";

    if (playerTurn(deck, player)) // if player busted
        return GameResult::dealerWon;

    if (dealerTurn(deck, dealer)) // if dealer busted
        return GameResult::playerWon;

    if (player.score() == dealer.score())
        return GameResult::tie;

    return (player.score() > dealer.score() ? GameResult::playerWon : GameResult::dealerWon);
}

int main()
{
    switch (playBlackjack())
    {
    case GameResult::playerWon:
        std::cout << "You win!\n";
        return 0;
    case GameResult::dealerWon:
        std::cout << "You lose!\n";
        return 0;
    case GameResult::tie:
        std::cout << "It's a tie.\n";
        return 0;
    }

    return 0;
}
