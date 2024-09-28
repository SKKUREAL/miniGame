#include "BlackjackManager.h"
#include <iostream>
using namespace std;

void BlackjackManager::PlayGame(Player& player)
{
	cout << "\n\n";
	cout << "####### Black Jack #######\n";
	int playerSelection;

	while (true) // 게임 진행
	{
		ShowInterface(player, playerSelection); // Interface를 보여주고, 플레이어의 선택을 받아옴.
		PlayAction(playerSelection);
		ChangeState(playerSelection); // 받아온 플레이어의 선택을 기반으로 다음 state를 결정
	}
}

void BlackjackManager::ShowInterface(const Player& player, int& playerSelection)
{
	// 공통 출력부----------------------------------------------------------------
	cout << "###############################################################\n";
	cout << "Round: " << mRoundNum << "\n";
	cout << "\n";

	// State dependent 출력부
	switch (mGameState) {
	case BlackjackGameState::Idle:
		cout << "Press below keys to Play or Exit...\n";
		cout << "[1: Play]  [2: Exit]\n";
		break;
	case BlackjackGameState::Bet:
		cout << "Enter the amount to BET...\n";
		break;
	case BlackjackGameState::Action:
		cout << "Press below keys to ACTION...\n";
		cout << "[1: Stand]  [2: Hit]  [3: Double Down]  [4: Surrender]\n";
		break;
	}

	// 공통 출력부----------------------------------------------------------------
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "Credit: " << player.getCredit() << "   Bet amount: " << mBetAmount << "\n";
	cout << "###############################################################\n";
	// 플레이어 입력부
	cout << "Your Decision: ";
	while (!(cin >> playerSelection)) { // 유효하지 않은 입력 예외 처리
		cout << "Invalid Input! Try again...\n";
		cout << "Your Decision: ";
		cin.clear(); // cin 상태 플래그 초기화
		cin.ignore(10000, '\n'); // 입력 버퍼에 남아 있는 잘못된 데이터 무시 (10000자리까지 '\n'가 나오기 전까지 데이터 무시)
	}
	// TODO: 범위 벗어나는 예외처리
}

void BlackjackManager::ChangeState(const int& playerSelection)
{
	switch (mGameState) {
	case BlackjackGameState::Idle:
		if (playerSelection == 1) mGameState = BlackjackGameState::Bet;
		else exit(0); // 블랙잭 게임장 나가기 여기 구현
		break;
	case BlackjackGameState::Bet:
		mGameState = BlackjackGameState::DistributeCard;
		break;
	case BlackjackGameState::DistributeCard:
		if (bBust || bBlackjack)
		{
			mGameState = BlackjackGameState::Adjustment;
		}
		else
		{
			mGameState = BlackjackGameState::Action;
		}
		break;
	case BlackjackGameState::Action:
		switch (playerSelection) {
		case 2:
			mGameState = BlackjackGameState::Hit;
			break;
		case 3:
			mGameState = BlackjackGameState::DoubleDown;
			break;
		default:
			mGameState = BlackjackGameState::Adjustment;
			break;
		}
		break;
	case BlackjackGameState::DealerPlay:
		mGameState = BlackjackGameState::Adjustment;
		break;
	case BlackjackGameState::Adjustment:
		mGameState = BlackjackGameState::Idle;
		break;
	}
}

void BlackjackManager::PlayAction(const int& playerSelection)
{

}
