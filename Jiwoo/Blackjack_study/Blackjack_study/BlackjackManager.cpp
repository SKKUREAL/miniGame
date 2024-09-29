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
		PlayAction(player, playerSelection);
		ChangeState(playerSelection); // 받아온 플레이어의 선택을 기반으로 다음 state를 결정
	}
}

void BlackjackManager::ShowInterface(const Player& player, int& playerSelection)
{
	bool bShowAllDealerHand = false;

	// 공통 출력부----------------------------------------------------------------
	cout << "###############################################################\n";
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
	case BlackjackGameState::DistributeCard:
		cout << "Distributing cards...\n";
		cout << "Press any key to continue...\n";
		break;
	case BlackjackGameState::Action:
		cout << "Press below keys to ACTION...\n";
		cout << "[1: Stand]  [2: Hit]  [3: Double Down]  [4: Surrender]\n";
		break;
	case BlackjackGameState::DoubleDown:
		cout << "DoubleDown!\n";
		cout << "You get one card, and the bet DOUBLES!\n";
		cout << "Press any key to continue...\n";
		break;
	case BlackjackGameState::Hit:
		cout << "Hit!\n";
		cout << "Press below keys to ACTION...\n";
		cout << "[1: Hit Again!]  [Others: Stand]\n";
		break;
	case BlackjackGameState::DealerPlay:
		cout << "Dealer Playing...\n";
		cout << "Press any key to continue...\n";
		break;
	case BlackjackGameState::Adjustment:
		cout << "Deciding Winner...\n";
		cout << "Press any key to continue...\n";
		break;
	case BlackjackGameState::ShowResult:
		bShowAllDealerHand = true;
		if (bPlayerWin) cout << "You WIN!\n";
		else cout << "You Lose...\n";
		cout << "Dealer Hand Value: " << GetHandValue(dealerHand) << "\n";
		cout << "Your Hand Value: " << GetHandValue(playerHand) << "\n";
		cout << "Press any key to continue...\n";
	}

	// 공통 출력부----------------------------------------------------------------
	cout << "\n";
	PrintDealerHand(bShowAllDealerHand);
	cout << "\n";
	cout << "\n";
	PrintPlayerHand();
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
		else exit(0); // TODO: 블랙잭 게임장 나가기
		break;

	case BlackjackGameState::Bet:
		mGameState = BlackjackGameState::DistributeCard;
		break;

	case BlackjackGameState::DistributeCard:
		mGameState = BlackjackGameState::Action;
		break;

	case BlackjackGameState::Action:
		if (bBust || bBlackjack) {
			mGameState = BlackjackGameState::Adjustment;
			break;
		}
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

	case BlackjackGameState::DoubleDown:
		mGameState = BlackjackGameState::DealerPlay;
		break;

	case BlackjackGameState::Hit:
		if (bBust) {
			mGameState = BlackjackGameState::Adjustment;
			break;
		}
		switch (playerSelection) {
		case 1:
			// hit again
			mGameState = BlackjackGameState::Hit;
			break;
		default:
			// stand
			mGameState = BlackjackGameState::DealerPlay;
			break;
		}
		break;

	case BlackjackGameState::DealerPlay:
		mGameState = BlackjackGameState::Adjustment;
		break;

	case BlackjackGameState::Adjustment:
		mGameState = BlackjackGameState::ShowResult;
		break;
	
	case BlackjackGameState::ShowResult:
		mGameState = BlackjackGameState::Idle;
		break;
	}
}

void BlackjackManager::PlayAction(Player& player, const int& playerSelection)
{
	switch (mGameState) {
	case BlackjackGameState::Idle:
		// 게임 상태 초기화
		mBetAmount = 0;
		bBust = false;
		bBlackjack = false;
		bPlayerWin = false;
		
		mGameDeck.Shuffle();
		break;

	case BlackjackGameState::Bet:
		// 플레이어 돈에서 차감
		player.decreaseCredit(playerSelection);
		// 베팅 금액에 저장
		mBetAmount = playerSelection;
		break;

	case BlackjackGameState::DistributeCard:
		// 덱 뒤에서 두장씩 뽑아서 나눠줌
		mGameDeck.DrawCard(2, playerHand);
		mGameDeck.DrawCard(2, dealerHand);
		break;

	case BlackjackGameState::Action:
		// 플레이어 블랙잭인지 버스트인지 체크
		CheckBustAndBlackjack();
		break;

	case BlackjackGameState::DoubleDown:
		// 카드 한 장 더 받고, 베팅 두배로
		mGameDeck.DrawCard(1, playerHand);
		mBetAmount *= 2;
		break;

	case BlackjackGameState::Hit:
		// 카드 한 장 더 받고, 블랙잭인지 버스트인지 체크
		mGameDeck.DrawCard(1, playerHand);
		CheckBustAndBlackjack();
		break;

	case BlackjackGameState::DealerPlay:
		if (GetHandValue(dealerHand) >= 17) {
			// 딜러 자동 스탠드. 아무것도 안함
		}
		else {
			// 딜러 자동 히트
			mGameDeck.DrawCard(1, dealerHand);
		}
		break;

	case BlackjackGameState::Adjustment:
		// 승자 확인 ----------------------------------------------------------
		if (bBlackjack) {
			// 블랙잭인 경우 플레이어 승
			bPlayerWin = true;
		}
		else if (GetHandValue(dealerHand) > BUST) {
			mBetAmount *= 2; // 딜러 버스트 시, 베팅금액 1배 증가
			// 플레이어도 버스트인 경우, 차이 낮은 쪽이 승리, 같으면 플레이어 패배
			if (bBust) {
				int diffPlayer = GetHandValue(playerHand) - BUST;
				int diffDealer = GetHandValue(dealerHand) - BUST;
				bPlayerWin = diffPlayer < diffDealer ? true : false;
			}
		}
		else {
			// 딜러 버스트 아닌 경우
			if (bBust) {
				bPlayerWin = false;
			}
			else {
				// 핸드가 더 높으면 승리
				bPlayerWin = GetHandValue(playerHand) > GetHandValue(dealerHand) ? true : false;
			}
		}

		// 승자 확인 완료, 베팅 금액 처리
		if (bPlayerWin) {
			player.addCredit(mBetAmount * 2);
		}
		break;

	case BlackjackGameState::ShowResult:
		ReturnHandToDeck();
		break;
	}
}

int BlackjackManager::GetHandValue(const Hand& hand)
{
	int handValue = 0;
	for (auto card : hand)
	{
		handValue += card.getValue();
	}
	return handValue;
}

void BlackjackManager::CheckBustAndBlackjack()
{
	int playerHandValue = GetHandValue(playerHand);
	if (playerHandValue == BLACK_JACK) bBlackjack = true;
	else if (playerHandValue > BUST) bBust = true;
}

void BlackjackManager::PrintDealerHand(bool bShowAll)
{
	cout << "Dealer's Hand: ";
	if (bShowAll) {
		for (auto card : dealerHand)
		{
			card.PrintCard();
		}
	}
	else {
		if (!dealerHand.empty()) {
			dealerHand.front().PrintCard();
			for (int i = 1; i < dealerHand.size(); i++)
			{
				cout << "[Unknown] ";
			}
		}
	}
	cout << "\n";
}

void BlackjackManager::PrintPlayerHand()
{
	cout << "Your Hand: ";
	for (auto card : playerHand)
	{
		card.PrintCard();
	}
	cout << "\n";
}

void BlackjackManager::ReturnHandToDeck()
{
	// 손패 모두 반환
	for (auto& card : playerHand)
	{
		mGameDeck.InsertCard(move(card));
	}
	playerHand.clear(); // 이동 했지만 벡터 크기는 여전히 잡히는 상태. 정리해줘야함. 이 때 원소를 소멸자 불러지나?? TODO:: 따로 테스트해봐야겠음 모든 원소를 이동한 상태에서 벡터 클리어하면 소멸자 불리는지
	for (auto& card : dealerHand)
	{
		mGameDeck.InsertCard(move(card));
	}
	dealerHand.clear();
}
