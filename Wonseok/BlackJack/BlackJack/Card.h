#pragma once
/*#ifndef CARD_HPP
#define CARD_HPP 이 두 줄의 코드도 같은 헤더 가드의 기능을 한다,*/
#include <string> // string 자료형을 사용하기 위함
#include <string_view> // string_view를 사용하기 위해 추가

// 매직 넘버를 상수로 정의(10.07)
constexpr int DEALER_MIN_SCORE = 17;  // 딜러가 카드를 받는 최소 점수
constexpr int BLACKJACK = 21;         // 블랙잭 점수

class Card {
public:
    int value;
    std::string_view suit;  // std::string_view로 변경
    std::string_view face;  // std::string_view로 변경

    // 생성자는 const std::string_view&로 전달, 문자열 복사 방지
    Card(int v, std::string_view f, std::string_view s);

    Card();
    Card(const Card& other);
    ~Card();

    bool isAce() const;
};


//#endif 헤더 가드를 사용할 경우 끝을 나타내는 이 코드를 넣어줘야함.