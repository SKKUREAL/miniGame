#pragma once
/*#ifndef CARD_HPP
#define CARD_HPP �� �� ���� �ڵ嵵 ���� ��� ������ ����� �Ѵ�,*/
#include <string> // string �ڷ����� ����ϱ� ����
#include <string_view> // string_view�� ����ϱ� ���� �߰�

// ���� �ѹ��� ����� ����(10.07)
constexpr int DEALER_MIN_SCORE = 17;  // ������ ī�带 �޴� �ּ� ����
constexpr int BLACKJACK = 21;         // ���� ����

class Card {
public:
    int value;
    std::string_view suit;  // std::string_view�� ����
    std::string_view face;  // std::string_view�� ����

    // �����ڴ� const std::string_view&�� ����, ���ڿ� ���� ����
    Card(int v, std::string_view f, std::string_view s);

    Card();
    Card(const Card& other);
    ~Card();

    bool isAce() const;
};


//#endif ��� ���带 ����� ��� ���� ��Ÿ���� �� �ڵ带 �־������.