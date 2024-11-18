#include <iostream>
#include <vector>
#include <cassert>
class Hand;
class CardFactory;
class Card;


using namespace std;
template<class T>
class Player {
private:
    string name;                // Nom du joueur
    int coins;                       // Nombre de pièces
    vector<T> chains;       // Chaînes du joueur
    Hand hand;                       // Main du joueur

public:
    Player(string&);               // Constructeur avec nom
    Player(istream&, const CardFactory*);     // Constructeur avec flux

    string getName(){return name;}                   // Obtenir le nom du joueur
    int getNumCoins(){return coins;};                       // Obtenir le nombre de pièces
    Player& operator+=(int coinsN){
        coins+=coinsN;
        return *this;
    }                       // Ajouter des pièces

    int getMaxNumChains(){return 3;}                 // Obtenir le nombre max de chaînes
    int getNumChains();                 // Obtenir le nombre actuel de chaînes
    
    Chain& operator[](int index){
        assert(index>=0 && index<chains.size());
        return chains[index];
    }                       // Accès à une chaîne par index
    void buyThirdChain();                          // Acheter une troisième chaîne

    void printHand(ostream&, bool);     // Afficher la main
    void addCardInHand(Card*);
};
