#include <iostream>
#include <stdexcept>
#include <vector>
class Card;
class CardFactory;
using namespace std;
//Error exception
class IllegalType : public exception {
    const char* what() const noexcept override {
        return "Erreur de type de carte.";
    }
};

// Interface abstraite de base pour les chaînes
class Chain_base {
public:
    virtual ~Chain_base()=default;
};
template<class T>
// Classe Chain template pour les cartes
class Chain:public Chain_base{
private:
     vector<Card*> cards;  // Conteneur pour stocker les cartes
     Card* cardType;
public:
    //constructeur
    Chain():cardType(nullptr){}
    // Constructeur qui accepte un istream et un CardFactory (pour la création de cartes)
    Chain(istream&, const CardFactory*);
    // Opérateur += pour ajouter une carte à la chaîne
    Chain<Card*>& operator+=(Card* newCard) {
        try{
            if(cardType==nullptr){
               cardType=newCard;
               cards.push_back(newCard);
               return *this;
            }
            else if(newCard->getName()==cardType->getName()){
               cards.push_back(newCard);
               return *this;
            }
            else throw IllegalType() ; 

        }catch(const IllegalType& e){
            cout <<e.what()<<endl;
            return *this;
        }
    }
    // Méthode pour calculer le nombre de pièces en fonction des cartes dans la chaîne
    int sell(){
        if(cardType==nullptr) return 0;
        if((cardType->getCardsPerCoin(1)==cards.size())
           || ((cardType->getCardsPerCoin(1)!=0)&&(cardType->getCardsPerCoin(1)<cards.size())&&(cardType->getCardsPerCoin(2)>cards.size())))return 1;
        if((cardType->getCardsPerCoin(2)==cards.size())
           || ((cardType->getCardsPerCoin(2)<cards.size())&&(cardType->getCardsPerCoin(3)>cards.size())))return 2;
        if((cardType->getCardsPerCoin(3)==cards.size())
           || ((cardType->getCardsPerCoin(3)<cards.size())&&(cardType->getCardsPerCoin(4)>cards.size()))
           || (cardType->getCardsPerCoin(4)==0))return 3;
        if((cardType->getCardsPerCoin(4)==cards.size())
           || ((cardType->getCardsPerCoin(4)<cards.size())))return 4;
        return 0;
    }
    //Methode pour savoir le nombre de cartes dans la chain
    int getSizeChain(){return cards.size();}
    // Opérateur d'insertion pour afficher la chaîne
    friend ostream& operator<<(ostream& os, const Chain<T*>& chain){
        string chars="";
        for (Card* card:chain.cards){
            chars=chars+card->getName().at(0)+"  ";
        }
        os<<chain.cardType->getName()<< "  : "<<chars;
        return os;
    }
    //return le nom de la chain
    string getNameChain(){
        if(cardType==nullptr) return "VIDE";
        else return cardType->getName();
    }
    //on supprime toute les cartes sur la chaine
    void destroyChain(){
         vector<Card*> card;
         cards=card;
         cardType=nullptr;
    }
    //on
};



