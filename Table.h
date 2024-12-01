#include  <iostream>
using namespace std;
class Player;
class Deck;
class Card;
template <typename C>
class TradeArea;
template <typename C>
class Table {
  private:
       Player player;//celui qui est entrain de jouer 
       Player player1;//joueur 1
       Player player2;//joueur 2
       Deck deck;//toutes les cartes melanagées
       DiscardPile<C> trash;//contenant les cartes jéteé
       TradeArea<C> trade;//emplacement des cartes à echanger 
       
  public:
    Table(Player& ply1,
          Player& ply2,
          Deck& deck,
          DiscardPile<C>& trashT,
          TradeArea<C>& tradeT):
          player1(ply1),
          player2(ply2),
          deck(deck),
          trash(trashT),
          trade(tradeT){}
    Table(istream& file, const CardFactory* factory);
    bool win(string& winnername){
        if (deck.size()==0) { // Si le Deck est vide
          if (player1.getNumCoins()> player2.getNumCoins()) return winnername==player1.getName();//Le joueur 1 à gagner 
          else if (player2.getNumCoins() > player1.getNumCoins()) return winnername==player2.getName();// Le joueur 2 à gagner
          else return false;//aucun gagnant 
        }
        return false; // Personne ne gagne tant que le Deck n'est pas vide
    }
    //on affiche toute les mains des joue  true toute les mains et false une carte                     
    void printHand(bool choice){
        cout << "Pour joueur 1 " <<endl;
        player1.printHand(cout,choice);
        cout<<endl;
        cout << "Pour joueur 2 " <<endl;
        cout<<endl;
        player2.printHand(cout,choice);
    }                          // Afficher la main du joueur
    // Afficher la table
    friend ostream& operator<<(ostream& os, const Table& table){
        os << "Player 1: " <<endl<<table.player1 << endl; // Affiche le joueur 1
        os << "Player 2: " <<endl<< table.player2 << endl; // Affiche le joueur 2
        os << "Discard Pile: "<<table.trash<< endl; // Affiche la pile de défausse
        os << "Trade Area: " << table.trade << endl;     // Affiche la zone commerciale*/
        return os;
    } 
    //affiche les joueurs 
    void showPlayers() const{ 
      cout<<"------------INFO-PLAYERS---------------"<<endl;
      cout <<"Pour joueur 1 : "<<endl;
      cout<<player1;
      cout<<"Pour joueur 2 : "<<endl;
      cout <<player2;
      cout<<"---------------------------------------"<<endl;
    }
    
};
