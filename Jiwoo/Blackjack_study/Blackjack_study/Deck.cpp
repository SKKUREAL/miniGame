#include "Deck.h"
#include <random>
#include <algorithm>
using namespace std;

// Fisher-Yates Shuffle �˰��� ����. �ð����⵵ O(N)
void Deck::Shuffle()
{
	random_device rd;
	mt19937 gen(rd()); // Mersenne Twister ���� ������

	// Fisher-Yates �˰���
	for (int i = mCards.size() - 1; i > 0; i--)
	{
		uniform_int_distribution<> dist(0, i); // 0���� i���� ���� ����
		int j = dist(gen); // i ������ ���� �ε��� ����
		swap(mCards[i], mCards[j]); // ī�� ��ȯ
	}
}

void Deck::PrintDeck()
{
	for (auto card : mCards)
	{
		cout << card.getSymbol() << ", " << card.getNumber() << "\n";
	}
}

void Deck::DrawCard(int numberToDraw, Hand& hand)
{
	while (numberToDraw--)
	{
		hand.push_back(mCards.back());
		mCards.pop_back();
	}
}

void Deck::InsertCard(Card&& cardToInsert)
{
	mCards.push_back(move(cardToInsert));
}
