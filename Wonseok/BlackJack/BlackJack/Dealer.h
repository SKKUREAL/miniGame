#pragma once
#include "Player.h"

class Dealer : public Player {
public:
	Dealer(); //�⺻ ������

	void playTurn(); // ���� �� ����: 17 �̻� Stay, 16 ���� Hit
};