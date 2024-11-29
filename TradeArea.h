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
       return false;//cad ne se trouve pas dans le trade
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
    int numCards() const{return this->size();}
    // Opérateur d'insertion pour afficher l'échange
    friend ostream& operator<<(ostream& os, const TradeArea<Card*>& trade){
        if(trade.numCards()>0){
            os<<" ## Trade : | ";
            for(Card* card:trade)os<<card->getName()<<" | ";
            os<<" ##"<<endl;
        }
        else os<<"Le trade est vide "<<endl;
        return os;
    }
    //retourner  une carte à une position donnée
    Card* getElementAt(int index){
        if(numCards()>0){
            auto it=this->begin();
            advance(it,index);
            return *it;
        }
        else{
            cout <<"Le Trade est vide "<<endl;
            return nullptr;
        }
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
