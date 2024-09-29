#include "Dealer.h"
#include <iostream>


// 기본 생성자
Dealer::Dealer() : Player() {

} // Player 클래스의 생성자와 동일

// 딜러 추가 턴
void Dealer::dealerTurn(Game& game) {
	while (calculateSum() < 17) {
		std::cout << "Dealer hits." << std::endl;
		addCard(game.drawRandomCard());
	}
	std::cout << "Dealer stays." << std::endl;
}