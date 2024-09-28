#pragma once
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;

// 포커 카드 기호와 숫자들. 변경되면 안되므로 const 선언
// 하드코딩 값들을 저장하는 헤더를 따로 만드는게 나을까? 개선 방안 없나?
const string cardNumbers[13] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
const string cardSymbols[4] = { "Spade","Clover","Heart","Diamond" };

class Deck
{
public:
	Deck() // 동적할당이 필요한 클래스로, 생성자를 정의해줘야함.
	{
		mCards.reserve(52);
		for (auto inNumber : cardNumbers)
		{
			for (auto inSymbol : cardSymbols)
				mCards.push_back(move(Card(inSymbol, inNumber)));
		}
	}
	void Shuffle();
	void PrintDeck();

private:
	vector<Card> mCards;
};