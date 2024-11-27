#include <iostream>
#include "Deck.h"
using namespace std;
class Card;
class CardFactory {
  private:
    Deck cards;
    static CardFactory* instance;
  public:
    CardFactory();  
    static CardFactory* getFactory(); // Renvoie l'unique instance de CardFactory
    Deck getDeck();                   // Renvoie un Deck contenant toutes les cartes, mélangées
    CardFactory(const CardFactory&) = delete; // Interdire la copie
    CardFactory& operator=(const CardFactory&) = delete; // Interdire l'affectation
    
};

