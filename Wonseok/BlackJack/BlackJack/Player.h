#pragma once
#include<vector> // ī�带 ������ ���Ͱ� �ʿ��ؼ�
#include "card.h" // Card Ŭ������ �ʿ��ؼ�

class Player {
public:
	std::vector<Card> hand; // �÷��̾ ���� ī���
	int Sum; // ���� �÷��̾� ī���� ��
	int aceCount;

	Player(); //������
	Player(const Player& other); // ���� ������ �߰�
	~Player(); // �Ҹ��� �߰�

	// ī�� �߰� �Լ�
	void addCard(const Card& card);

	// ���� ī�� �� ��� �Լ�
	int calculateSum() const; // const �Ѽ��� ����

	// �÷��̾� ���� �ʱ�ȭ �Լ�
	void reset();

};