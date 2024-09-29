#include "Player.h"

Player::Player() : Sum(0), aceCount(0)/*, hand()*/ {}// Player 생성자, 아무것도 없으니 초기값은 0
// hand() 안해줘도 되는 이유: std::vector에서 기본 생성자가 자동으로 호출되기 때문에 굳이 생성자를 초기화할 필요 없음
// 초기화 해줘야 하는 경우: 크기가 정해져 있을 때, 초기 데이터 설정하고 싶을 때
 

//카드 추가 함수이다
void Player::addCard(const Card& card) {
	hand.push_back(card); // hand 벡터에 새 카드를 추가

	if (card.isAce()) {
		aceCount++;
	}
}

// 합 계산 함수
int Player::calculateSum() {
	int Sum = 0;

	for (const auto& card : hand) {
		if (card.isAce()) {
			Sum += 11; //Ace는 일단 11로 계산한다.
		}
		else {
			Sum += card.value;
		}
	}
	while (Sum > 21 && aceCount > 0) {
		Sum -= 10;
		aceCount--;
	// 점수가 21 이상이고 Ace가 있을 경우, Ace 하나의 값을 1로 변경한다.
	}

	return Sum;
} 

// 플레이어 상태 초기화 함수, 게임이 끝났을 때 사용할 예정
void Player::reset() {
	hand.clear(); // hand 벡터 초기화 함수
	Sum = 0; // 합을 0으로 초기화
	aceCount = 0;
}