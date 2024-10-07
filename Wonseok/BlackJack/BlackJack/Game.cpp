#include "Game.h"
#include <cstdlib>
#include <ctime>
#include<algorithm> // 랜덤 셔플을 위해 필요함
#include<random>

Game::Game() : playerMoney(initialMoney) { // 플레이어 초기 게임 머니 설정
	std::srand(static_cast<unsigned>(std::time(0))); // 무작위 시드 설정
	initializeDeck(); // 게임 시작 시에 덱을 초기화
}

Game::~Game() {
	deck.clear(); // 게임이 반복되기 때문에 기존 덱 초기화 해야 함.
}

// 덱 초기화 함수
void Game::initializeDeck() {
	
	
	// 4 개의 문양(슈트)
	std::vector<std::string> suits = { "Heart", "Diamond", "Club", "Spade" };

	// 2~10, K Q J A 
	for (const auto& suit : suits) {
		for (int value = 2; value <= 10; ++value)
			deck.push_back(Card(value, std::to_string(value), suit));
		deck.push_back(Card(10, "J", suit)); // K Q J은 동일하게 10으로
		deck.push_back(Card(10, "Q", suit));
		deck.push_back(Card(10, "K", suit));
		deck.push_back(Card(11, "A", suit)); // A는 처음에는 11로 넣는다.
	}

	// 랜덤으로 덱을 섞기

	std::random_device rd;  // 하드웨어 기반 랜덤 생성기
	std::mt19937 g(rd());   // 의사 난수 생성기 (Mersenne Twister)
	std::shuffle(deck.begin(), deck.end(), g);  // std::shuffle로 섞기
}

Card Game::drawRandomCard() {
	if (deck.empty()) {
		std::cout << "deck is empty" << std::endl;
		exit(1); // 그럴 리 없지만 덱이 비어있으면 프로그램 종료
	}
	Card card = deck.back(); // 셔플한 덱 중 마지막 카드 선택
	deck.pop_back(); // 그 카드를 선택 후 제거 이 카드를 플레이어나 딜러에게
	return card;
}

// 게임 시작 화면을 보여주는 함수
void Game::showStartScreen() {
	int choice;
	std::cout << "=== Welcome to MinigameHeaven" << std::endl;
	std::cout << "Player's money: " << playerMoney << std::endl;  // 플레이어의 현재 돈을 표시
	std::cout << "1. Start BlackJack" << std::endl;
	std::cout << "2. Exit" << std::endl;
	std::cin >> choice;

	switch (choice) { // 나중에 게임의 확장성을 위해 switch-choice 사용
	case 1:
		startBlackJack(); // 블랙잭 게임 시작
		break;

	case 2:
		std::cout << "Exiting game." << std::endl;
		exit(0); // 게임 종료
		break;

	default:
		std::cout << "Invalid choice, please try again." << std::endl;
		break; // 예외 처리
	}
	if (playerMoney <= 0) {
		std::cout << "You have no more money left" << std::endl;
		exit(0);
	}
}

// 블랙잭 게임 시작 함수
void Game::startBlackJack() {
	std::cout << "Starting BlackJack!" << std::endl;
	currentState = GameState::PlayerTurn;

	// 첫 번째 턴
	dealer.addCard(drawRandomCard());
	player.addCard(drawRandomCard());
	std::cout << "Dealer's first card:" << dealer.hand[0].face << "," << dealer.hand[0].suit << std::endl;
	std::cout << "Player's first card:" << player.hand[0].face << "," << player.hand[0].suit << std::endl;

	// 두 번째 턴
	dealer.addCard(drawRandomCard());
	player.addCard(drawRandomCard());
	std::cout << "Player's seconds card:" << player.hand[1].face << "," << player.hand[0].suit << std::endl;
	std::cout << "Dealer's second card: ???" << std::endl; // 숨김

	// 블랙잭 예외 처리
	if (player.calculateSum() == BLACKJACK && dealer.calculateSum() != BLACKJACK) {
		blackJackWin();
		currentState = GameState::BlackJack;
		player.reset();
		dealer.reset();
		return;
	}
	else if (dealer.calculateSum() == BLACKJACK) {
		currentState = GameState::GameOver;
		std::cout << "Dealer has BlackJack. You lose" << std::endl;
		player.reset();
		dealer.reset();
		return;
	}
	else if (player.calculateSum() == BLACKJACK && dealer.calculateSum() == BLACKJACK) {
		std::cout << "Both have BlackJack. Push." << std::endl;
		player.reset();
		dealer.reset();
		return;
	}

	int playerChoice;
	std::cout << "Player's turn" << std::endl;
	std::cout << "1. Hit   2. Stay" << std::endl;
	while (std::cin >> playerChoice && playerChoice == 1 && player.calculateSum() < BLACKJACK) {
		player.addCard(drawRandomCard());
		std::cout << "Player hits" << std::endl;
		std::cout << "Player's sum" << player.calculateSum() << std::endl;

		if (player.calculateSum() >= BLACKJACK)
			break;
		std::cout << "Player's turn" << std::endl;
		std::cout << "1. Hit   2. Stay" << std::endl;
	}
	if (player.calculateSum() <= BLACKJACK) {
		dealer.dealerTurn(*this); // this 사용
	}


	determineWinner();
	player.reset();
	dealer.reset();
	
}


// 승자를 결정하는 함수
void Game::determineWinner() {
	int playerSum = player.calculateSum();
	int dealerSum = dealer.calculateSum();

	std::cout << "Player sum:" << playerSum << std::endl;
	std::cout << "Dealer sum:" << dealerSum << std::endl;

	if (playerSum > BLACKJACK) {
		std::cout << "Player busts. Dealer wins" << std::endl;
		playerMoney -= 200;
	}
	else if (dealerSum > BLACKJACK) {
		std::cout << "Dealer busts. Player wins" << std::endl;
		playerMoney += 100;
	}
	else if (playerSum > dealerSum) {
		std::cout << "Player wins" << std::endl;
		playerMoney += 100;
	}
	else if (dealerSum > playerSum) {
		std::cout << "Dealer wins" << std::endl;
		playerMoney -= 200;
	}
	else
		std::cout << "Tie" << std::endl;
	std::cout << "Player's money" << playerMoney << std::endl;
}

void Game::blackJackWin() {
	std::cout << "BlackJack! Player wins 1.5 money" << std::endl;
	playerMoney += 150;
	std::cout << "Player's money" << playerMoney << std::endl;
}

int main() {
	Game game;

	while (game.playerMoney > 0) {  // 플레이어의 돈이 0 이상일 때까지 게임 반복
		game.showStartScreen();     // 게임 시작 화면 및 블랙잭 진행
	}

	std::cout << "You ran out of money. Game over." << std::endl;
	return 0;
}
