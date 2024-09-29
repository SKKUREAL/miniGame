#pragma once
#include "Player.h"
#include "Dealer.h"
#include <iostream>

class Game {
public:
	Player player; //�÷��̾� ��ü
	Dealer dealer; //���� ��ü
	std::vector<Card> deck; // ī�� ��
	int playerMoney; // �÷��̾��� ���� �Ӵ�

	Game(); // �⺻ ������

	// ���� ���� �Լ� (���θ޴�)
	void showStartScreen();

	// ���� ������ �����ϴ� �Լ�
	void startBlackJack();

	// ���и� �����ϴ� �Լ�
	void determineWinner();

	// ���� �¸� �� 1.5�� ���� �Ӵ� �߰�
	void blackJackWin();
	
	// ������ �������� ī�带 �̾��ִ� �Լ�
	Card drawRandomCard();

	//�� �ʱ�ȭ �Լ�
	void initializeDeck();

	//���� ��
	void dealerTurn();
};