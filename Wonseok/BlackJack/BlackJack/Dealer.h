#pragma once
#include "Player.h"

class Dealer : public Player {
public:
	Dealer(); //기본 생성자

	void playTurn(); // 딜러 턴 로직: 17 이상 Stay, 16 이하 Hit
};