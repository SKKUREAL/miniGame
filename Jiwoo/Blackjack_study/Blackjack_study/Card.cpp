#include "Card.h"
#include <iostream>
using namespace std;

void Card::PrintCard()
{
	cout << "[" << mSymbol << ":" << mNumber << "] ";
}
