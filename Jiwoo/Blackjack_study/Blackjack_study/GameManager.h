#pragma once
#include "Player.h"

class GameManager
{
public:
	virtual void PlayGame(Player& player) = 0; // pure virtual function����, GameManagerŬ������ ��ü�� ������ �� ����, �ݵ�� �������̵��������.

private:
	virtual void ShowInterface(const Player& player, int& playerSelection) = 0; // �÷��̾� ���� �����ֱ⸸ �ϴ°Ŵϱ� const ���۷���
};