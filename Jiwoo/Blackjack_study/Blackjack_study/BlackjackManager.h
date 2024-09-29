#pragma once
#include "GameManager.h"
#include "Player.h"
#include "Deck.h"

#define BLACK_JACK 21 
#define BUST 21 // 같은 수지만 용도가 다르므로 이름 다르게

class BlackjackManager : public GameManager // public 상속은 base class의 멤버들에 대한 접근제한 설정이다.
{
public:

	enum class BlackjackGameState
	{
		Idle, Bet, DistributeCard, Action, DoubleDown, Hit, DealerPlay, Adjustment, ShowResult
	};
	
	void PlayGame(Player& player) override;

private:
	// 얘네 4가지는 게임의 상태를 나타내는 공통적인 특성이 있는데, 구조체로 묶을까? 근데 이름이 좀 애매하다. mGameState를 이미 쓰고있네..
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
	
	void PrintDealerHand(bool bShowAll); // 한장만 보여줄지, 다 보여줄지
	void PrintPlayerHand();

	void ReturnHandToDeck();
};