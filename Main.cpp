#include <iostream>
#include <algorithm>
#include <random>
#include "Card.h"
#include "Chain.h"
#include "Deck.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"
#include "TradeArea.h"
using namespace std;
int main(){
    cout <<"Start program";
    CardFactory m;
    Deck l=m.getDeck();
    cout <<"Voila vos cartes "<<endl;
    cout <<l;
    cout <<"size "<<l.size();
    return 0;
}

