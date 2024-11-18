#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
class Card;
class CardFactory;
class Hand {
private:
    vector<Card*> cards; // Conteneur pour stocker les cartes de la main

public:
     Hand(){}
    // Constructeur pour construire la main à partir d'un flux istream
    Hand(istream&, const CardFactory*);
    // Ajoute une carte derrière la dernière carte de la main
    Hand& operator+=(Card* card ){
        cards.push_back(card);
        return *this;
    }

    // Renvoie et supprime la première carte de la main
    Card* play();

    // Renvoie mais ne supprime pas la première carte de la main
    Card* top();

    // Renvoie et supprime une carte à une position donnée
    Card* operator[](int index){
       assert(index>=0 && index<cards.size());
       return cards[index];

    }

    // Affiche toutes les cartes dans la main
    friend ostream& operator<<(ostream& os, const Hand& hand){
         for (auto card : hand.cards) { // Suppose que Deck est itérable
           os << card->getName() << "\n"; // Écriture directe dans le flux
         }
         return os;
    }

    
};
