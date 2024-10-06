#pragma once
/*#ifndef CARD_HPP
#define CARD_HPP 이 두 줄의 코드도 같은 헤더 가드의 기능을 한다,*/
#include<string> // string 자료형을 사용하기 위함

// 매직 넘버를 상수로 정의(10.07)
constexpr int DEALER_MIN_SCORE = 17;  // 딜러가 카드를 받는 최소 점수
constexpr int BLACKJACK = 21;         // 블랙잭 점수

class Card {
public:
	int value; // 카드의 숫자를 넣기 위한 필드
	std::string suit; // 카드의 문양을 넣기 위한 필드
	std::string face; // K Q J A를 위한 필드

	Card(int v, const std::string& f, const std::string& s);// 생성자. const로 문자열 전달 >> 메모리 낭비 줄임 (참조자-> 불필용한 복사 X)

	Card(); // 기본 생성자 추가
	
	Card(const Card& other); // 복사 생성자 추가 , 사실 블랙잭 게임에서는 복사 생성자를 쓸 일이 없어서 선언 안해줘도 되긴 함.
	~Card(); // 소멸자 추가

	bool isAce() const;
};

//#endif 헤더 가드를 사용할 경우 끝을 나타내는 이 코드를 넣어줘야함.