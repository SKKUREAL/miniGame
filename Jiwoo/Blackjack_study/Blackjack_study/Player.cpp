#include "Player.h"

void Player::setName(string&& inName) // ���ͷ��� ���� ���� ���� ������ ��������� �� �ʿ� ����.
{
	mName = move(inName);
}

void Player::setCredit(int inCredit)
{
	mCredit = inCredit;
}

void Player::decreaseCredit(int amount)
{
	mCredit -= amount;
}

void Player::addCredit(int amount)
{
	mCredit += amount;
}
