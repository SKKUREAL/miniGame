#pragma once

#include <string>
using namespace std;

class Player
{
public:
	Player(string&& inName, int inCredit) // 멤버 이니셜라이저로 선언과 동시에 초기화, rvalue reference로 받아서 inName을 그대로 mName으로 이동. 복사 최적화
		: mName(move(inName))
		, mCredit(inCredit)
	{};
	// inline 함수는 헤더파일에 정의도 구현해줘야함. 안그러면 링크 오류 발생
	inline string getName() const { return mName; } // 간단한 함수이므로 inline화하여 런타임 스택 프레임 호출 반환 오버헤드 제거.
	inline int getCredit() const { return mCredit; } // 함수 뒤에 const 키워드를 붙여서 객체의 상태 보호

	void setName(string&& inName); // 레퍼런스 전달로 객체 복사 비용 절감
	void setCredit(int inCredit);
	void decreaseCredit(int amount);
private:
	string mName;
	int mCredit;
};