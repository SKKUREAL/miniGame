#pragma once
/*#ifndef CARD_HPP
#define CARD_HPP 이 두 줄의 코드도 같은 헤더 가드의 기능을 한다,*/
#include<string> // string 자료형을 사용하기 위함

class Card {
public:
	int value; // 카드의 숫자를 넣기 위한 필드
	std::string suit; // 카드의 문양을 넣기 위한 필드
	std::string face; // K Q J A를 위한 필드

	Card(int v, std::string f, std::string s);// 생성자
	
	bool isAce() const;
};

//#endif 헤더 가드를 사용할 경우 끝을 나타내는 이 코드를 넣어줘야함.