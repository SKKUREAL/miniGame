#pragma once
#include "Player.h"
#include "Dealer.h"
#include <iostream>

class Game {
public:
	Player player; //플레이어 객체
	Dealer dealer; //딜러 객체
	std::vector<Card> deck; // 카드 덱
	int playerMoney; // 플레이어의 게임 머니

	Game(); // 기본 생성자

	// 게임 시작 함수 (메인메뉴)
	void showStartScreen();

	// 블랙잭 게임을 시작하는 함수
	void startBlackJack();

	// 승패를 결정하는 함수
	void determineWinner();

	// 블랙잭 승리 시 1.5배 게임 머니 추가
	void blackJackWin();
	
	// 덱에서 랜덤으로 카드를 뽑아주는 함수
	Card drawRandomCard();

	//덱 초기화 함수
	void initializeDeck();

	//딜러 턴
	void dealerTurn();
};