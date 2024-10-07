#include "Player.h"

Player::Player() : Sum(0), aceCount(0)/*, hand()*/ {}// Player ������, �ƹ��͵� ������ �ʱⰪ�� 0
// hand() �����൵ �Ǵ� ����: std::vector���� �⺻ �����ڰ� �ڵ����� ȣ��Ǳ� ������ ���� �����ڸ� �ʱ�ȭ�� �ʿ� ����
// �ʱ�ȭ ����� �ϴ� ���: ũ�Ⱑ ������ ���� ��, �ʱ� ������ �����ϰ� ���� ��

Player::Player(const Player& other) // ���� ������
    : hand(other.hand), Sum(other.Sum), aceCount(other.aceCount) {}

Player::~Player() {
    hand.clear(); // �Ҹ���
}


//ī�� �߰� �Լ��̴�
void Player::addCard(const Card& card) {
	hand.push_back(card); // hand ���Ϳ� �� ī�带 �߰�

	if (card.isAce()) { // ����Լ��� const ��ü������ ȣ���� �� �ִ�.
		aceCount++;
	}
}

int Player::calculateSum() const {
    int totalSum = 0;
    for (const auto& card : hand) {
        if (card.isAce()) {
            totalSum += 11;
        }
        else {
            totalSum += card.value;
        }
    }
    int aceCount = this->aceCount;
    while (totalSum > BLACKJACK && aceCount > 0) {
        totalSum -= 10;
        aceCount--;
    }
    return totalSum; // 
}

// �÷��̾� ���� �ʱ�ȭ �Լ�, ������ ������ �� ����� ����
void Player::reset() {
	hand.clear(); // hand ���� �ʱ�ȭ �Լ�
	Sum = 0; // ���� 0���� �ʱ�ȭ
	aceCount = 0;
}