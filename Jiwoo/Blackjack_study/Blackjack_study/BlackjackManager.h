#pragma once
#include "GameManager.h"
#include "Player.h"

class BlackjackManager : public GameManager // public 상속은 base class의 멤버들에 대한 접근제한 설정이다.
{
public:
	enum class BlackjackGameState
	{
		Idle, Bet, DistributeCard, Action, DoubleDown, Hit, DealerPlay, Adjustment
	};
	void PlayGame(Player& player) override;

private:
	// 얘네 4가지는 게임의 상태를 나타내는 공통적인 특성이 있는데, 구조체로 묶을까? 근데 이름이 좀 애매하다. mGameState를 이미 쓰고있네..
	int mRoundNum = 1;
	int mBetAmount = 0;
	bool bBust = false;
	bool bBlackjack = false;
	BlackjackGameState mGameState = BlackjackGameState::Idle;

	void ShowInterface(const Player& player, int& playerSelection) override;
	void ChangeState(const int& playerSelection);
	void PlayAction(const int& playerSelection);
};