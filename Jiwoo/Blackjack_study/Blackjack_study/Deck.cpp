#include "Deck.h"
#include <random>
#include <algorithm>
using namespace std;

// Fisher-Yates Shuffle 알고리즘 적용. 시간복잡도 O(N)
void Deck::Shuffle()
{
	random_device rd;
	mt19937 gen(rd()); // Mersenne Twister 난수 생성기

	// Fisher-Yates 알고리즘
	for (int i = mCards.size() - 1; i > 0; i--)
	{
		uniform_int_distribution<> dist(0, i); // 0부터 i까지 난수 생성
		int j = dist(gen); // i 이하의 랜덤 인덱스 선택
		swap(mCards[i], mCards[j]); // 카드 교환
	}
}

void Deck::PrintDeck()
{
	for (auto card : mCards)
	{
		cout << card.getSymbol() << ", " << card.getNumber() << "\n";
	}
}
