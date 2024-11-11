#pragma once
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

// ��Ŀ ī�� ��ȣ�� ���ڵ�. ����Ǹ� �ȵǹǷ� const ����
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
	Card(const string& inSymbol, const string& inNumber) // ī�带 �����Ҷ� �̸� ���ǵ� ��ȣ�� ���� string�� ����ϰ�, ��� �����ؾ��ϹǷ� const ���۷����� ����
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
	string mNumber = "#"; // stl�� string Ŭ������ vector Ŭ������ ���α����� RAII�� �����Ƿ�, ���� �޸� ������ ���� �ʿ䰡 ����.
    int mValue = 0;
};