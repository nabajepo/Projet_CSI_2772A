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
    //constructeur
    Hand(){}
    // Constructeur pour construire la main à partir d'un flux istream
    Hand(istream&, const CardFactory*);
    // Ajoute une carte derrière la dernière carte de la main
    Hand& operator+=(Card* newCard ){
      cards.push_back(newCard);
      return *this;
    }
    // Renvoie et supprime la première carte de la main
    Card* play(){
      Card* topCard=cards[0];
      cards.erase(cards.begin());
      return topCard;
    }
    // Renvoie mais ne supprime pas la première carte de la main
    Card* top(){return cards[0];}
    // Renvoie et supprime une carte à une position donnée
    Card* operator[](int index){
          assert(index>=0 && index<cards.size());
          return cards[index];
    }
    // Affiche toutes les cartes dans la main
    friend ostream& operator<<(ostream& os, const Hand& hand){
         for (auto card : hand.cards) { // Suppose que Deck est itérable
           os <<"  " <<card->getName() << " | "; // Écriture directe dans le flux
         }
         return os;
    }
    //avoir une carte à partir d'un nom
    Card* getCardByName(string nameCard){
        for(Card* card:cards)if(card->getName()==nameCard)return card;
        return nullptr;//si nous ne trouvons pas 
    }
    //supprime une carte par le nom
    void removeCardByName(string nameCard){
         for(int index=0;index<cards.size();index++){
            if(cards[index]->getName()==nameCard) cards.erase(cards.begin()+index);
         }  
    }

    
};
