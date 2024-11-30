#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
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
    CardFactory m;
    Deck o=m.getDeck();
    cout<<o;
    cout<<o.size()<<endl;
    cout<<m.createCard("Stink")->getName()<<endl;
    return 0;
}

