#pragma once
#include "Player.h"
#include "Card.h"
#include "Game.h"

class Dealer : public Player {
public:
	Dealer(); //�⺻ ������

	void dealerTurn(Game& game);
};