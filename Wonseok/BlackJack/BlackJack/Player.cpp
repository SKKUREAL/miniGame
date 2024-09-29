#include "Player.h"

Player::Player() : Sum(0), aceCount(0)/*, hand()*/ {}// Player ������, �ƹ��͵� ������ �ʱⰪ�� 0
// hand() �����൵ �Ǵ� ����: std::vector���� �⺻ �����ڰ� �ڵ����� ȣ��Ǳ� ������ ���� �����ڸ� �ʱ�ȭ�� �ʿ� ����
// �ʱ�ȭ ����� �ϴ� ���: ũ�Ⱑ ������ ���� ��, �ʱ� ������ �����ϰ� ���� ��
 

//ī�� �߰� �Լ��̴�
void Player::addCard(const Card& card) {
	hand.push_back(card); // hand ���Ϳ� �� ī�带 �߰�

	if (card.isAce()) {
		aceCount++;
	}
}

// �� ��� �Լ�
int Player::calculateSum() {
	int Sum = 0;

	for (const auto& card : hand) {
		if (card.isAce()) {
			Sum += 11; //Ace�� �ϴ� 11�� ����Ѵ�.
		}
		else {
			Sum += card.value;
		}
	}
	while (Sum > 21 && aceCount > 0) {
		Sum -= 10;
		aceCount--;
	// ������ 21 �̻��̰� Ace�� ���� ���, Ace �ϳ��� ���� 1�� �����Ѵ�.
	}

	return Sum;
} 

// �÷��̾� ���� �ʱ�ȭ �Լ�, ������ ������ �� ����� ����
void Player::reset() {
	hand.clear(); // hand ���� �ʱ�ȭ �Լ�
	Sum = 0; // ���� 0���� �ʱ�ȭ
	aceCount = 0;
}