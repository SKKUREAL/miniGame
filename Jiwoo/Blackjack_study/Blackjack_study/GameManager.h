#pragma once
#include "Player.h"

class GameManager
{
public:
	virtual void PlayGame(Player& player) = 0; // pure virtual function으로, GameManager클래스는 객체로 생성될 수 없고, 반드시 오버라이드해줘야함.

private:
	virtual void ShowInterface(const Player& player, int& playerSelection) = 0; // 플레이어 정보 보여주기만 하는거니까 const 레퍼런스
};