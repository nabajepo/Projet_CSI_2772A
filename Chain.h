#include <iostream>
#include <stdexcept>
#include <vector>
class Card;
class CardFactory;
using namespace std;
// Exception à lancer pour les types incorrects
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
     T cardType;
public:
    Chain():cardType(nullptr){}
    Chain(T value):cardType(value){}
    // Constructeur qui accepte un istream et un CardFactory (pour la création de cartes)
    Chain(istream&, const CardFactory*);

    // Opérateur += pour ajouter une carte à la chaîne
    Chain<T>& operator+=(Card* newCard) {
        if(newCard->getName()==cardType->getName()){
            cards.push_back(newCard);
            return *this;}
        else throw IllegalType() ;  
        
    }
    // Méthode pour calculer le nombre de pièces en fonction des cartes dans la chaîne
    int sell(){
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
    int getLength(){return cards.size();}
    
    // Opérateur d'insertion pour afficher la chaîne
    friend std::ostream& operator<<(std::ostream& os, const Chain<T*>& chain){
        os<<chain.cardType->getName()<< "  : "<<chain.cards.size();///A changer 
        return os;
    }
};
// Déclaration de la classe CardFactory


