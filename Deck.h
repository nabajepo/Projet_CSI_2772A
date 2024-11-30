#include <iostream>
#include <vector>
using namespace std;
class CardFactory;
class Card;
class Deck : public vector<Card*> {
public:
    //Constructeur
    Deck(){}
    // Constructeur qui accepte un istream et un CardFactory pour construire un deck à partir d'un fichier
    Deck(istream&, const CardFactory*);

    // Méthode pour tirer et supprimer la carte supérieure du deck
    Card* draw(){
        Card* topCard=this->back();
        this->pop_back();
        return topCard;
    }

    // Opérateur d'insertion pour afficher le deck dans un std::ostream
    friend ostream& operator<<(ostream& os, const Deck& deck){
        for (Card* card : deck) { // Suppose que Deck est itérable
               os << card->getName() << "\n"; // Écriture directe dans le flux
        }
        return os; 
    }
    
};

