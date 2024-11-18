#include <iostream>
#include <list>//liste doublement chainée 
using namespace std;
template <class T>
class TradeArea : public list<Card*> {
public:
    // Constructeur qui initialise la TradeArea à partir d'un flux istream
    TradeArea(istream&, const CardFactory*);

    // Opérateur d'ajout d'une carte à l'échange
    TradeArea& operator+=(const Card*);

    // Vérifie si une carte peut être ajoutée à l'échange
    bool legal(const Card*);

    // Échange une carte avec un nom donné
    Card* trade(string);

    // Retourne le nombre de cartes dans l'échange
    int numCards();

    // Opérateur d'insertion pour afficher l'échange
    friend ostream& operator<<(ostream&, const TradeArea<Card*>&);
};
