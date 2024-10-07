#pragma once
#include<vector> // 카드를 저장할 벡터가 필요해서
#include "card.h" // Card 클래스가 필요해서

class Player {
public:
	std::vector<Card> hand; // 플레이어가 받은 카드들
	int Sum; // 현재 플레이어 카드의 합
	int aceCount;

	Player(); //생성자
	Player(const Player& other); // 복사 생성자 추가
	~Player(); // 소멸자 추가

	// 카드 추가 함수
	void addCard(const Card& card);

	// 현재 카드 합 계산 함수
	int calculateSum() const; // const 한수로 변경

	// 플레이어 상태 초기화 함수
	void reset();

};