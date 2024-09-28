#pragma once
#include <iostream>
#include <vector>
#include "Card.h"
using namespace std;

// ��Ŀ ī�� ��ȣ�� ���ڵ�. ����Ǹ� �ȵǹǷ� const ����
// �ϵ��ڵ� ������ �����ϴ� ����� ���� ����°� ������? ���� ��� ����?
const string cardNumbers[13] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
const string cardSymbols[4] = { "Spade","Clover","Heart","Diamond" };

class Deck
{
public:
	Deck() // �����Ҵ��� �ʿ��� Ŭ������, �����ڸ� �����������.
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