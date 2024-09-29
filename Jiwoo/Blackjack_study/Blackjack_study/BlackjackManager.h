#pragma once
#include "GameManager.h"
#include "Player.h"
#include "Deck.h"

#define BLACK_JACK 21 
#define BUST 21 // ���� ������ �뵵�� �ٸ��Ƿ� �̸� �ٸ���

class BlackjackManager : public GameManager // public ����� base class�� ����鿡 ���� �������� �����̴�.
{
public:

	enum class BlackjackGameState
	{
		Idle, Bet, DistributeCard, Action, DoubleDown, Hit, DealerPlay, Adjustment, ShowResult
	};
	
	void PlayGame(Player& player) override;

private:
	// ��� 4������ ������ ���¸� ��Ÿ���� �������� Ư���� �ִµ�, ����ü�� ������? �ٵ� �̸��� �� �ָ��ϴ�. mGameState�� �̹� �����ֳ�..
	int mBetAmount = 0;
	bool bBust = false;
	bool bBlackjack = false;
	bool bPlayerWin = false;
	BlackjackGameState mGameState = BlackjackGameState::Idle;
	Deck mGameDeck;
	
	Hand playerHand;
	Hand dealerHand;

	void ShowInterface(const Player& player, int& playerSelection) override;
	void ChangeState(const int& playerSelection);
	void PlayAction(Player& player, const int& playerSelection);
	int GetHandValue(const Hand& hand);
	void CheckBustAndBlackjack();
	
	void PrintDealerHand(bool bShowAll); // ���常 ��������, �� ��������
	void PrintPlayerHand();

	void ReturnHandToDeck();
};