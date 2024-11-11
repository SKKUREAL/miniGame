#include "BlackjackManager.h"
#include <iostream>
using namespace std;

void BlackjackManager::PlayGame(Player& player)
{
	cout << "\n\n";
	cout << "####### Black Jack #######\n";
	int playerSelection;

	while (true) // ���� ����
	{
		ShowInterface(player, playerSelection); // Interface�� �����ְ�, �÷��̾��� ������ �޾ƿ�.
		PlayAction(player, playerSelection);
		ChangeState(playerSelection); // �޾ƿ� �÷��̾��� ������ ������� ���� state�� ����
	}
}

void BlackjackManager::ShowInterface(const Player& player, int& playerSelection)
{
	bool bShowAllDealerHand = false;

	// ���� ��º�----------------------------------------------------------------
	cout << "###############################################################\n";
	cout << "\n";
	

	// State dependent ��º�
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

	// ���� ��º�----------------------------------------------------------------
	cout << "\n";
	PrintDealerHand(bShowAllDealerHand);
	cout << "\n";
	cout << "\n";
	PrintPlayerHand();
	cout << "\n";
	cout << "Credit: " << player.getCredit() << "   Bet amount: " << mBetAmount << "\n";
	cout << "###############################################################\n";
	// �÷��̾� �Էº�
	cout << "Your Decision: ";
	while (!(cin >> playerSelection)) { // ��ȿ���� ���� �Է� ���� ó��
		cout << "Invalid Input! Try again...\n";
		cout << "Your Decision: ";
		cin.clear(); // cin ���� �÷��� �ʱ�ȭ
		cin.ignore(10000, '\n'); // �Է� ���ۿ� ���� �ִ� �߸��� ������ ���� (10000�ڸ����� '\n'�� ������ ������ ������ ����)
	}
	// TODO: ���� ����� ����ó��
}

void BlackjackManager::ChangeState(const int& playerSelection)
{
	switch (mGameState) {

	case BlackjackGameState::Idle:
		if (playerSelection == 1) mGameState = BlackjackGameState::Bet;
		else exit(0); // TODO: ���� ������ ������
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
		// ���� ���� �ʱ�ȭ
		mBetAmount = 0;
		bBust = false;
		bBlackjack = false;
		bPlayerWin = false;
		
		mGameDeck.Shuffle();
		break;

	case BlackjackGameState::Bet:
		// �÷��̾� ������ ����
		player.decreaseCredit(playerSelection);
		// ���� �ݾ׿� ����
		mBetAmount = playerSelection;
		break;

	case BlackjackGameState::DistributeCard:
		// �� �ڿ��� ���徿 �̾Ƽ� ������
		mGameDeck.DrawCard(2, playerHand);
		mGameDeck.DrawCard(2, dealerHand);
		break;

	case BlackjackGameState::Action:
		// �÷��̾� �������� ����Ʈ���� üũ
		CheckBustAndBlackjack();
		break;

	case BlackjackGameState::DoubleDown:
		// ī�� �� �� �� �ް�, ���� �ι��
		mGameDeck.DrawCard(1, playerHand);
		mBetAmount *= 2;
		break;

	case BlackjackGameState::Hit:
		// ī�� �� �� �� �ް�, �������� ����Ʈ���� üũ
		mGameDeck.DrawCard(1, playerHand);
		CheckBustAndBlackjack();
		break;

	case BlackjackGameState::DealerPlay:
		if (GetHandValue(dealerHand) >= 17) {
			// ���� �ڵ� ���ĵ�. �ƹ��͵� ����
		}
		else {
			// ���� �ڵ� ��Ʈ
			mGameDeck.DrawCard(1, dealerHand);
		}
		break;

	case BlackjackGameState::Adjustment:
		// ���� Ȯ�� ----------------------------------------------------------
		if (bBlackjack) {
			// ������ ��� �÷��̾� ��
			bPlayerWin = true;
		}
		else if (GetHandValue(dealerHand) > BUST) {
			mBetAmount *= 2; // ���� ����Ʈ ��, ���ñݾ� 1�� ����
			// �÷��̾ ����Ʈ�� ���, ���� ���� ���� �¸�, ������ �÷��̾� �й�
			if (bBust) {
				int diffPlayer = GetHandValue(playerHand) - BUST;
				int diffDealer = GetHandValue(dealerHand) - BUST;
				bPlayerWin = diffPlayer < diffDealer ? true : false;
			}
		}
		else {
			// ���� ����Ʈ �ƴ� ���
			if (bBust) {
				bPlayerWin = false;
			}
			else {
				// �ڵ尡 �� ������ �¸�
				bPlayerWin = GetHandValue(playerHand) > GetHandValue(dealerHand) ? true : false;
			}
		}

		// ���� Ȯ�� �Ϸ�, ���� �ݾ� ó��
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
	// ���� ��� ��ȯ
	for (auto& card : playerHand)
	{
		mGameDeck.InsertCard(move(card));
	}
	playerHand.clear(); // �̵� ������ ���� ũ��� ������ ������ ����. �����������. �� �� ���Ҹ� �Ҹ��� �ҷ�����?? TODO:: ���� �׽�Ʈ�غ��߰��� ��� ���Ҹ� �̵��� ���¿��� ���� Ŭ�����ϸ� �Ҹ��� �Ҹ�����
	for (auto& card : dealerHand)
	{
		mGameDeck.InsertCard(move(card));
	}
	dealerHand.clear();
}
