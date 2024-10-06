#pragma once
/*#ifndef CARD_HPP
#define CARD_HPP �� �� ���� �ڵ嵵 ���� ��� ������ ����� �Ѵ�,*/
#include<string> // string �ڷ����� ����ϱ� ����

// ���� �ѹ��� ����� ����(10.07)
constexpr int DEALER_MIN_SCORE = 17;  // ������ ī�带 �޴� �ּ� ����
constexpr int BLACKJACK = 21;         // ���� ����

class Card {
public:
	int value; // ī���� ���ڸ� �ֱ� ���� �ʵ�
	std::string suit; // ī���� ������ �ֱ� ���� �ʵ�
	std::string face; // K Q J A�� ���� �ʵ�

	Card(int v, const std::string& f, const std::string& s);// ������. const�� ���ڿ� ���� >> �޸� ���� ���� (������-> ���ʿ��� ���� X)

	Card(); // �⺻ ������ �߰�
	
	Card(const Card& other); // ���� ������ �߰� , ��� ���� ���ӿ����� ���� �����ڸ� �� ���� ��� ���� �����൵ �Ǳ� ��.
	~Card(); // �Ҹ��� �߰�

	bool isAce() const;
};

//#endif ��� ���带 ����� ��� ���� ��Ÿ���� �� �ڵ带 �־������.