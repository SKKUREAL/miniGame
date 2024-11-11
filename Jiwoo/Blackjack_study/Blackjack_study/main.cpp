#pragma once
#include <iostream>
#include "Player.h"
#include "BlackjackManager.h"
#define INITIAL_CREDIT 1000
using namespace std;


#include "Deck.h" // �׽�Ʈ�� ��� ����
void TestCode()
{
	Deck d;
	d.PrintDeck();
	d.Shuffle();
	d.PrintDeck();
}

int main()
{
	cout << "Welcome to JW's Minigame Heaven!\n\n\n";

	cout << "Enter your name: ";
	string inName;
	cin >> inName;
	if (inName == "TEST") // �̸� �Է��� TEST�� TestCode ���� �� ����
	{
		TestCode();
		return 0;
	}
	Player player(move(inName), INITIAL_CREDIT);

	cout << "Welcome " << player.getName() << "!\n"
		<< "Press 1 to play Blackjack\n"
		<< "Press 2 to Exit Game\n";

	int playerSelection;
	cin >> playerSelection;
	switch (playerSelection) {
	case 1:
	{
		BlackjackManager blackjackManager; // case 1�̶�� ���� ������������ ����� ���̹Ƿ�, ���� �Ҵ� ��� ä��
		blackjackManager.PlayGame(player);
	}
	break;
	case 2:
		exit(0);
		break;
	}
}