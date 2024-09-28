#pragma once
#include <string>
using namespace std;

class Card
{
	// TODO: string_view 클래스 사용 한번 보기.
public:
	Card(const string& inSymbol, const string& inNumber) // 카드를 생성할때 미리 정의된 기호와 숫자 string을 사용하고, 계속 재사용해야하므로 const 레퍼런스로 복사
		: mSymbol(inSymbol)
		, mNumber(inNumber)
	{};
	inline string getSymbol() const { return mSymbol; }
	inline string getNumber() const { return mNumber; }
private:
	string mSymbol = "#";
	string mNumber = "#"; // stl의 string 클래스와 vector 클래스는 내부구현이 RAII를 따르므로, 따로 메모리 관리를 해줄 필요가 없다.
};