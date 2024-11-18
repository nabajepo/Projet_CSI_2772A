#include  <iostream>
using namespace std;
class CardFactory;
class Table {
public:
    Table(istream&, const CardFactory*);      // Constructeur avec flux
    bool win(string&);                        // Vérifier si un joueur a gagné
    void printHand(bool);                          // Afficher la main du joueur
    friend ostream& operator<<(ostream&, const Table&); // Afficher la table
};
