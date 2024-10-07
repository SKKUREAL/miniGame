#include <cassert>
#include <iostream>
#include <limits>
#include "Random.h"

// Increase amount of new lines if your board isn't
// at the very bottom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
    enum Type
    {
        up,
        down,
        left,
        right,
        maxDirections,
    };

    Direction(Type type)
        :m_type(type)
    {
    }

    Type getType() const
    {
        return m_type;
    }

    Direction operator-() const
    {
        switch (m_type)
        {
        case up:    return Direction{ down };
        case down:  return Direction{ up };
        case left:  return Direction{ right };
        case right: return Direction{ left };
        default:    break;
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ up };
    }

    static Direction getRandomDirection()
    {
        Type random{ static_cast<Type>(Random::get(0, Type::maxDirections - 1)) };
        return Direction{ random };
    }

private:
    Type m_type{};
};

std::ostream& operator<<(std::ostream& stream, Direction dir)
{
    switch (dir.getType())
    {
    case Direction::up:     return (stream << "up");
    case Direction::down:   return (stream << "down");
    case Direction::left:   return (stream << "left");
    case Direction::right:  return (stream << "right");
    default:                break;
    }

    assert(0 && "Unsupported direction was passed!");
    return (stream << "unknown direction");
}

namespace UserInput
{
    bool isValidCommand(char ch)
    {
        return ch == 'w'
            || ch == 'a'
            || ch == 's'
            || ch == 'd'
            || ch == 'q';
    }

    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char getCharacter()
    {
        char operation{};
        std::cin >> operation;
        ignoreLine(); // remove any extraneous input
        return operation;
    }

    char getCommandFromUser()
    {
        char ch{};
        while (!isValidCommand(ch))
            ch = getCharacter();

        return ch;
    }

    Direction charToDirection(char ch)
    {
        switch (ch)
        {
        case 'w': return Direction{ Direction::up };
        case 's': return Direction{ Direction::down };
        case 'a': return Direction{ Direction::left };
        case 'd': return Direction{ Direction::right };
        }

        assert(0 && "Unsupported direction was passed!");
        return Direction{ Direction::up };
    }
};

class Tile
{
public:
    Tile() = default;
    explicit Tile(int number)
        :m_num(number)
    {
    }

    bool isEmpty() const
    {
        return m_num == 0;
    }

    int getNum() const { return m_num; }

private:
    int m_num { 0 };
};

std::ostream& operator<<(std::ostream& stream, Tile tile)
{
    if (tile.getNum() > 9) // if two digit number
        stream << " " << tile.getNum() << " ";
    else if (tile.getNum() > 0) // if one digit number
        stream << "  " << tile.getNum() << " ";
    else if (tile.getNum() == 0) // if empty spot
        stream << "    ";
    return stream;
}

class Board
{
public:

    Board() = default;

    static void printEmptyLines(int count)
    {
        for (int i = 0; i < count; ++i)
            std::cout << '\n';
    }

    friend std::ostream& operator<<(std::ostream& stream, const Board& board)
    {
        // Before drawing always print some empty lines
        // so that only one board appears at a time
        // and it's always shown at the bottom of the window
        // because console window scrolls automatically when there is no
        // enough space.
        for (int i = 0; i < g_consoleLines; ++i)
            std::cout << '\n';

        for (int y = 0; y < s_size; ++y)
        {
            for (int x = 0; x < s_size; ++x)
                stream << board.m_tiles[y][x];
            stream << '\n';
        }

        return stream;
    }

private:
    static constexpr int s_size { 4 };
    Tile m_tiles[s_size][s_size]{
        Tile{ 1 }, Tile { 2 }, Tile { 3 } , Tile { 4 },
        Tile { 5 } , Tile { 6 }, Tile { 7 }, Tile { 8 },
        Tile { 9 }, Tile { 10 }, Tile { 11 }, Tile { 12 },
        Tile { 13 }, Tile { 14 }, Tile { 15 }, Tile { 0 } };
};

int main()
{
    Board board{};
    std::cout << board;

    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << '\n';
    std::cout << "Generating random direction... " << Direction::getRandomDirection() << "\n\n";

    std::cout << "Enter a command: ";
    while (true)
    {
        char ch{ UserInput::getCommandFromUser() };

        // Handle non-direction commands
        if (ch == 'q')
        {
            std::cout << "\n\nBye!\n\n";
            return 0;
        }

        // Handle direction commands
        Direction dir{ UserInput::charToDirection(ch) };

        std::cout << "You entered direction: " << dir << '\n';
    }

    return 0;
}