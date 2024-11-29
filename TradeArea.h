#include <iostream>
#include <algorithm>
#include <list>//liste doublement chainée 
using namespace std;
class CardFactory;
template <class T>
class TradeArea : public list<Card*> {
public:
    //constructeur
    TradeArea(){}
    // Constructeur qui initialise la TradeArea à partir d'un flux istream
    TradeArea(istream&, const CardFactory*);
    // Opérateur d'ajout d'une carte à l'échange
    TradeArea& operator+=(Card* newCard){
        this->push_back(newCard);
        return *this;
    }
    // Vérifie si une carte peut être ajoutée à l'échange
    bool legal(Card* exC){
        for(Card* card:*this){
           if(exC->getName()==card->getName())return true;
        }
       return false;
    }
    // Échange une carte avec un nom donné
    Card* trade(string nameCard){
        auto it = find_if(this->begin(), this->end(), [&](Card* card) {
        return card->getName() == nameCard;});

        if (it != this->end()) {
            Card* cardN = *it;
            this->erase(it); // Supprime la carte trouvée
            return cardN;    // Retourne la carte trouvée
        }
        return nullptr; // Retourne nullptr si aucune carte ne correspond
    }
    // Retourne le nombre de cartes dans l'échange
    int numCards(){return this->size();}
    // Opérateur d'insertion pour afficher l'échange
    friend ostream& operator<<(ostream& os, const TradeArea<Card*>& trade){
        string chaine="## trade : ";
        for(Card* card:trade){
            chaine=chaine+card->getName()+" ";
        }
        os<<chaine<<" ##"<<endl;
        return os;
    }
    
    //retourner  une carte à une position donnée
    Card* getElementAt(int index){
        auto it=this->begin();
        advance(it,index);
        return *it;
    }
    //retourne une carte par le nom
    Card* getCardByName(string nameCard){
        for(Card* card:*this)if(nameCard==card->getName())return card;
        return nullptr;//si on ne trouve rien
    }
    //detruit toute les cartes du trade
    void destroyTrade(){
        TradeArea<Card*> newTrade;/////ici on supprimer les cartes se trouvant dans le trade 
        *this=newTrade;
    }
};
