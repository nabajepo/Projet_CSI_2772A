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
}
//Pour Deck
Deck::Deck(){}
Card* Deck::draw(){
    Card* topCard=this->back();
    this->pop_back();
    return topCard;
};
ostream& operator<<(ostream& os, const Deck& deck){
     for (auto card : deck) { // Suppose que Deck est itérable
        os << card->getName() << "\n"; // Écriture directe dans le flux
    }
    return os; 
}
CardFactory::CardFactory(){
    Card* bleu=new Blue();
    Card* chili=new Chili();
    Card* stink=new Stink();
    Card* green=new Green();
    Card* soy=new Soy();
    Card* black=new Black();
    Card* red=new Red();
    Card* garden=new Garden();
    for(int i=0;i<20;i++){
        allCards.push_back(bleu);
    }
    for(int i=0;i<18;i++){
        allCards.push_back(chili);
    }
    for(int i=0;i<16;i++){
        allCards.push_back(stink);
    }
    for(int i=0;i<14;i++){
        allCards.push_back(green);
    }
    for(int i=0;i<12;i++){
        allCards.push_back(soy);
    }
    for(int i=0;i<10;i++){
        allCards.push_back(black);
    }
    for(int i=0;i<8;i++){
        allCards.push_back(red);
    }
    for(int i=0;i<6;i++){
        allCards.push_back(garden);
    }
}
Deck CardFactory::getDeck(){//On melange les cartes 
    random_device rd;
    mt19937 gen(rd());
    shuffle(allCards.begin(),allCards.end(),gen);
    return allCards;
}
CardFactory* CardFactory::getFactory(){
    if (!instance) instance = new CardFactory();
        return instance;}
//pour Hand
Hand::Hand(){}  
Card* Hand::play(){//Ici c'est quand on veut jouer la premiere carte
 Card* topCard=cards.back();
 cards.pop_back();
 return topCard;
}
Card* Hand::top(){
    return cards.back();
}
//pour Player





