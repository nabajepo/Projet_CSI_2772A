#include  <iostream>
using namespace std;

template <class T,class C>
class Table {
  private:
       Player<T> player1;
       Player<T> player2;
       Deck deck;
      

  public:
    Table(Player<T>& ply1,Player<T>& ply2,
          Deck& deck):
          player1(ply1),
          player2(ply2),
          deck(deck){}
    Table(istream&, const CardFactory*);      // Constructeur avec flux
    bool win(string& winnername){
        if (deck.size()==0) { // Si le Deck est vide
          if (player1.getCoins() > player2.getCoins()) {
            return winnername==player1.getName();
          } else if (player2.getCoins() > player1.getCoins()) {
            return winnername==player2.getName();// Le joueur 2 gagne
          } else {
            winnername = "Egalite";
            return false;//aucun gagnant 
          }  
          
        }
        return false; // Personne ne gagne tant que le Deck n'est pas vide
    }                       // Vérifier si un joueur a gagné
    void printHand(bool choice){
        cout << "Pour joueur 1" <<endl;
        player1.printHand(cout,choice);
        cout << "Pour joueur 2" <<endl;
        player2.printHand(cout,choice);
    }                          // Afficher la main du joueur
    friend ostream& operator<<(ostream& os, const Table& table){
        os << "Player 1: " << table.player1 << endl; // Affiche le joueur 1
        os << "Player 2: " << table.player2 << endl; // Affiche le joueur 2
        os << "Discard Pile: " << table.trash << endl; // Affiche la pile de défausse
        os << "Trade Area: " << table.trade << endl;     // Affiche la zone commerciale
        return os;
    } // Afficher la table
};
