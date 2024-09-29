#pragma once
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

// 포커 카드 기호와 숫자들. 변경되면 안되므로 const 선언
const map<string, int> cardNumbers = {
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9},
    {"10", 10},
    {"J", 10},
    {"Q", 10},
    {"K", 10},
    {"A", 11}
};
const string cardSymbols[4] = { "Spade", "Clover", "Heart", "Diamond" };

class Card
{
	
public:
	Card(const string& inSymbol, const string& inNumber) // 카드를 생성할때 미리 정의된 기호와 숫자 string을 사용하고, 계속 재사용해야하므로 const 레퍼런스로 복사
		: mSymbol(inSymbol)
		, mNumber(inNumber)
    {
        auto it = cardNumbers.find(inNumber);
        if (it != cardNumbers.end()) {
            mValue = it->second;
        }
        else throw invalid_argument("Invalid card number!");
    };

	inline string getSymbol() const { return mSymbol; }
	inline string getNumber() const { return mNumber; }
    inline int getValue() const { return mValue; }
    void PrintCard();

private:
	string mSymbol = "#";
	string mNumber = "#"; // stl의 string 클래스와 vector 클래스는 내부구현이 RAII를 따르므로, 따로 메모리 관리를 해줄 필요가 없다.
    int mValue = 0;
};