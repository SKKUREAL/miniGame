#pragma once
#include "GameManager.h"
#include "Player.h"

class BlackjackManager : public GameManager // public ����� base class�� ����鿡 ���� �������� �����̴�.
{
public:
	enum class BlackjackGameState
	{
		Idle, Bet, DistributeCard, Action, DoubleDown, Hit, DealerPlay, Adjustment
	};
	void PlayGame(Player& player) override;

private:
	// ��� 4������ ������ ���¸� ��Ÿ���� �������� Ư���� �ִµ�, ����ü�� ������? �ٵ� �̸��� �� �ָ��ϴ�. mGameState�� �̹� �����ֳ�..
	int mRoundNum = 1;
	int mBetAmount = 0;
	bool bBust = false;
	bool bBlackjack = false;
	BlackjackGameState mGameState = BlackjackGameState::Idle;

	void ShowInterface(const Player& player, int& playerSelection) override;
	void ChangeState(const int& playerSelection);
	void PlayAction(const int& playerSelection);
};