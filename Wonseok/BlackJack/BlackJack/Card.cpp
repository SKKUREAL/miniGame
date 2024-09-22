#include "Card.h"

Card::Card(int v, std::string f, std::string s) {
	value = v;
	face = f;
	suit = s;
}

bool Card::isAce() const {
	return value == 11; // Ace 초기 value 는 11기 때문에 value ==11로 11이 맞는지 확인
						// 맞다면 true 반환 아니면 false 반환
}