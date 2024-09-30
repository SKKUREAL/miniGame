#include "Card.h"

Card::Card(int v, const std::string& f, const std::string& s)
	: value(v), suit(s), face(f) {} // 초기화 리스트 사용

Card::Card(const Card& other)
	: value(other.value), suit(other.suit), face(other.face) {} // 복사 생성자 추가

Card::Card() 
	: value(0), suit("None"), face("None") {} // 기본 생성자 추가

Card::~Card() {
	// 소멸자는 명시적으로 선언
}


bool Card::isAce() const {
	return value == 11; // Ace 초기 value 는 11기 때문에 value ==11로 11이 맞는지 확인
						// 맞다면 true 반환 아니면 false 반환
}