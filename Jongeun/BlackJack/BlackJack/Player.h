#pragma once
#include "Card.h"

class Player
{
private:
    int m_score{};
    int m_aceCount{0};

public:
    // We'll use a function to add the card to the player's score
    // Since we now need to count aces
    void addToScore(Card card)
    {
        m_score += card.value();
        if (card.rank == Card::rank_ace)
            ++m_aceCount;
    }

    void consumeAces(int maxScore)
    {
        while (m_score > maxScore && m_aceCount > 0)
        {
            m_score -= 10;
            --m_aceCount;
        }
    }

    int score() { return m_score; }
};
