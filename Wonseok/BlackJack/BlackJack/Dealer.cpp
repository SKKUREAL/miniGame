#include "Dealer.h"
#include <iostream>


// �⺻ ������
Dealer::Dealer() : Player() {

} // Player Ŭ������ �����ڿ� ����

// ���� �߰� ��

void Dealer::dealerTurn(Game& game) {
    while (calculateSum() < DEALER_MIN_SCORE) {
        std::cout << "Dealer hits." << std::endl;
        addCard(game.drawRandomCard());
    }
    std::cout << "Dealer stays." << std::endl;
}