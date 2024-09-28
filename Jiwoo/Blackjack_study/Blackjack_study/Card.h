#pragma once
#include <string>
using namespace std;

class Card
{
	// TODO: string_view Ŭ���� ��� �ѹ� ����.
public:
	Card(const string& inSymbol, const string& inNumber) // ī�带 �����Ҷ� �̸� ���ǵ� ��ȣ�� ���� string�� ����ϰ�, ��� �����ؾ��ϹǷ� const ���۷����� ����
		: mSymbol(inSymbol)
		, mNumber(inNumber)
	{};
	inline string getSymbol() const { return mSymbol; }
	inline string getNumber() const { return mNumber; }
private:
	string mSymbol = "#";
	string mNumber = "#"; // stl�� string Ŭ������ vector Ŭ������ ���α����� RAII�� �����Ƿ�, ���� �޸� ������ ���� �ʿ䰡 ����.
};