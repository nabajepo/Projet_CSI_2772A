#include <iostream>
#include <vector>
using namespace std;
class Card;
template<class T>
class DiscardPile : public vector<Card*> {
public:
    // Constructeur
    DiscardPile(){}
    // Constructeur qui accepte un istream et un CardFactory pour construire une pile de cartes à partir d'un fichier
    DiscardPile(istream& , const CardFactory*);

    // Ajoute une carte à la pile de déchet
    DiscardPile& operator+=(Card* card){
        this->push_back(card);
        return *this;
    }

    // Renvoie et supprime la carte supérieure de la pile
    Card* pickUp(){
        Card* topC=this->back();
        this->pop_back();
        return topC;
    }

    // Renvoie mais ne supprime pas la carte supérieure de la pile
    Card* top(){return this->back();}

    // Insère toutes les cartes de la pile dans un ostream
    void print(ostream& os){
        string cards="";
        for(Card* card:*this){
            cards=cards+card->getName()+"\n";  
        }
        os<<cards;
    }
    // Insère seulement la carte supérieure dans un ostream
    friend ostream& operator<<(ostream& os, const DiscardPile& dsc){
           os << dsc.top()->getName()<<endl;
    }
};


