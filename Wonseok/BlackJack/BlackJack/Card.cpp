#include "Card.h"

Card::Card(int v, std::string_view f, std::string_view s)
	: value(v), face(f), suit(s) {}  // string_view�� ����

Card::Card()
	: value(0), suit("None"), face("None") {}  // ���ͷ��� string_view�� �ʱ�ȭ ����



Card::Card(const Card& other)
	: value(other.value), suit(other.suit), face(other.face) {} // ���� ������ �߰�


Card::~Card() {
	// �Ҹ��ڴ� ��������� ����
}


bool Card::isAce() const {
	return value == 11; // Ace �ʱ� value �� 11�� ������ value ==11�� 11�� �´��� Ȯ��
						// �´ٸ� true ��ȯ �ƴϸ� false ��ȯ
}