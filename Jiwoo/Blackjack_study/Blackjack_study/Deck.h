#pragma once
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;

class Deck
{
public:
	Deck() // �����Ҵ��� �ʿ��� Ŭ������, �����ڸ� �����������.
	{
		mCards.reserve(52);
		for (auto inNumber : cardNumbers)
		{
			for (auto inSymbol : cardSymbols)
				mCards.push_back(move(Card(inSymbol, inNumber.first)));
		}
	}
	void Shuffle();
	void PrintDeck();

private:
	vector<Card> mCards;
};