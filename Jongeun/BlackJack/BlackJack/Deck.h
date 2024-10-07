#pragma once
#include "Random.h"

class Deck
{
private:
    std::array<Card, 52> m_cards{};
    std::size_t m_nextCardIndex{0};

public:
    Deck()
    {
        std::size_t count{0};
        for (auto suit : Card::allSuits)
            for (auto rank : Card::allRanks)
                m_cards[count++] = Card{rank, suit};
    }

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }
};


