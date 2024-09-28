#pragma once

#include <string>
using namespace std;

class Player
{
public:
	Player(string&& inName, int inCredit) // ��� �̴ϼȶ������� ����� ���ÿ� �ʱ�ȭ, rvalue reference�� �޾Ƽ� inName�� �״�� mName���� �̵�. ���� ����ȭ
		: mName(move(inName))
		, mCredit(inCredit)
	{};
	// inline �Լ��� ������Ͽ� ���ǵ� �����������. �ȱ׷��� ��ũ ���� �߻�
	inline string getName() const { return mName; } // ������ �Լ��̹Ƿ� inlineȭ�Ͽ� ��Ÿ�� ���� ������ ȣ�� ��ȯ ������� ����.
	inline int getCredit() const { return mCredit; } // �Լ� �ڿ� const Ű���带 �ٿ��� ��ü�� ���� ��ȣ

	void setName(string&& inName); // ���۷��� ���޷� ��ü ���� ��� ����
	void setCredit(int inCredit);
private:
	string mName;
	int mCredit;
};