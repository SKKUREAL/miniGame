#pragma once
#include "Player.h"
#include "Card.h"
#include "Game.h"

class Dealer : public Player {
public:
	Dealer(); //기본 생성자

	void dealerTurn(Game& game);
};