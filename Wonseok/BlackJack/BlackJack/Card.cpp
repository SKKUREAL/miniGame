#include "Card.h"

Card::Card(int v, const std::string& f, const std::string& s)
	: value(v), suit(s), face(f) {} // �ʱ�ȭ ����Ʈ ���

Card::Card(const Card& other)
	: value(other.value), suit(other.suit), face(other.face) {} // ���� ������ �߰�

Card::Card() 
	: value(0), suit("None"), face("None") {} // �⺻ ������ �߰�

Card::~Card() {
	// �Ҹ��ڴ� ��������� ����
}


bool Card::isAce() const {
	return value == 11; // Ace �ʱ� value �� 11�� ������ value ==11�� 11�� �´��� Ȯ��
						// �´ٸ� true ��ȯ �ƴϸ� false ��ȯ
}