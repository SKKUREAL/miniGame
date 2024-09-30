#pragma once
/*#ifndef CARD_HPP
#define CARD_HPP �� �� ���� �ڵ嵵 ���� ��� ������ ����� �Ѵ�,*/
#include<string> // string �ڷ����� ����ϱ� ����

class Card {
public:
	int value; // ī���� ���ڸ� �ֱ� ���� �ʵ�
	std::string suit; // ī���� ������ �ֱ� ���� �ʵ�
	std::string face; // K Q J A�� ���� �ʵ�

	Card(int v, const std::string& f, const std::string& s);// ������. const�� ���ڿ� ���� >> �޸� ���� ���� (������-> ���ʿ��� ���� X)

	Card(); // �⺻ ������ �߰�
	
	Card(const Card& other); // ���� ������ �߰�
	~Card(); // �Ҹ��� �߰�

	bool isAce() const;
};

//#endif ��� ���带 ����� ��� ���� ��Ÿ���� �� �ڵ带 �־������.