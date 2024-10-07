#include "Player.h"

Player::Player() : Sum(0), aceCount(0)/*, hand()*/ {}// Player 생성자, 아무것도 없으니 초기값은 0
// hand() 안해줘도 되는 이유: std::vector에서 기본 생성자가 자동으로 호출되기 때문에 굳이 생성자를 초기화할 필요 없음
// 초기화 해줘야 하는 경우: 크기가 정해져 있을 때, 초기 데이터 설정하고 싶을 때

Player::Player(const Player& other) // 복사 생성자
    : hand(other.hand), Sum(other.Sum), aceCount(other.aceCount) {}

Player::~Player() {
    hand.clear(); // 소멸자
}


//카드 추가 함수이다
void Player::addCard(const Card& card) {
	hand.push_back(card); // hand 벡터에 새 카드를 추가

	if (card.isAce()) { // 상수함수라 const 객체에서도 호출할 수 있다.
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

// 플레이어 상태 초기화 함수, 게임이 끝났을 때 사용할 예정
void Player::reset() {
	hand.clear(); // hand 벡터 초기화 함수
	Sum = 0; // 합을 0으로 초기화
	aceCount = 0;
}