#include "Card.h"

Card::Card(int v, std::string f, std::string s) {
	value = v;
	face = f;
	suit = s;
}

bool Card::isAce() const {
	return value == 11; // Ace �ʱ� value �� 11�� ������ value ==11�� 11�� �´��� Ȯ��
						// �´ٸ� true ��ȯ �ƴϸ� false ��ȯ
}