#pragma once
#include <iostream>
#include "Player.h"
#include "BlackjackManager.h"
#define INITIAL_CREDIT 1000
using namespace std;


#include "Deck.h" // 테스트용 헤더 포함
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
	if (inName == "TEST") // 이름 입력이 TEST면 TestCode 실행 후 종료
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
		BlackjackManager blackjackManager; // case 1이라는 작은 스코프에서만 사용할 것이므로, 스택 할당 방식 채용
		blackjackManager.PlayGame(player);
	}
	break;
	case 2:
		exit(0);
		break;
	}
}