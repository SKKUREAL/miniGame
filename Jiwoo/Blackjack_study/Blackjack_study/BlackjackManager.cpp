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
	case BlackjackGameState::Action:
		cout << "Press below keys to ACTION...\n";
		cout << "[1: Stand]  [2: Hit]  [3: Double Down]  [4: Surrender]\n";
		break;
	}

	// ���� ��º�----------------------------------------------------------------
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\n";
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
		mDeck.Shuffle();
		break;

	case BlackjackGameState::Bet:
		// �÷��̾� ������ ����
		player.decreaseCredit(playerSelection);
		// ���� �ݾ׿� ����
		mBetAmount = playerSelection;
		break;

	case BlackjackGameState::DistributeCard:
		
		break;

	case BlackjackGameState::Action:
		
		break;

	case BlackjackGameState::DoubleDown:

		break;

	case BlackjackGameState::Hit:

		break;

	case BlackjackGameState::DealerPlay:
		
		break;

	case BlackjackGameState::Adjustment:
		
		break;
	}
}
