#include <iostream>
#include <vector>
#include <cassert>
class Hand;
class CardFactory;
class Card;
using namespace std;
//quand on veut acheter une chaine 
class NotEnoughCoins : public exception {
    const char* what() const noexcept override {
        return "Desolé vous avez pas accès de coins il faut au moins 2 coins pour acheter un nouveu chaine";
    }
};
template<class T>
class Player {
private:
    string name;                // Nom du joueur
    int coins;                       // Nombre de pièces
    vector<T> chains;       // Chaînes du joueur
    Hand hand;                       // Main du joueur

public:
    //constructeur avec un nom
    Player(string& nameP):name(nameP),coins(0){
         Chain<Card*> firstChain;
         Chain<Card*> secondChain;
         chains.push_back(firstChain);//on a initialement 2 chaines  vides
         chains.push_back(secondChain);
    }               // Constructeur avec nom
    Player(istream&, const CardFactory*);     // Constructeur avec flux

    string getName(){return name;}                   // Obtenir le nom du joueur
    int getNumCoins(){return coins;};                       // Obtenir le nombre de pièces
    Player& operator+=(int coinsN){
        coins+=coinsN;
        return *this;
    }                       // Ajouter des pièces

    int getMaxNumChains(){return 3;}                 // Obtenir le nombre max de chaînes
    int getNumChains(){return chains.size();}             // Obtenir le nombre actuel de chaînes
    
    Chain<Card*>& operator[](int index){
        assert(index>=0 && index<chains.size());
        return chains[index];
    }                       // Accès à une chaîne par index
    // Acheter une troisième chaîne
    void buyThirdChain(){
       try{
          if(getNumChains()<getMaxNumChains()){
            if(coins>2){
                Chain<Card*> newChaine;
                chains.push_back(newChaine);
                cout <<"Une 3 eme chaine a ete cree "<<endl;
            }
            else throw NotEnoughCoins();
          }
          else cout <<"Vous avez atteint le nombre maximum de coins "<<endl;

       }catch(const NotEnoughCoins& e){
          cout << e.what()<<endl;//erreur
       }
    }                         
    //si true on affiche la main si nom on affiche la premiere carte 
    void printHand(ostream& os , bool ch){
       if(ch) os<<hand;
       else os<<hand.top()->getName();
    }     
    // Insere des cartes à dans la main du joueur
    void addCardInHand(Card* card){hand+=card;}
    //afficher toute les informations du joueur
    friend ostream& operator<<(ostream& os, const Player& ply){
        os<<ply.name<<" : "<<ply.coins<<" coins "<<endl;
        for (int index=0;index<ply.chains.size();index++){
            if(ply.chains[index].getNameChain()!="VIDE")os<<ply.chains[index]<<endl;
            else {
                os<<"Chain [" <<index<<"] : VIDE"<<endl;
            }
        }
        return os;
    }
    //pour avoir  la premier card de la main du joeur
    Card* showTopCard(){
        cout <<" Votre premiere carte est : | "<<hand.top()->getName()<<" |"<<endl;
        return hand.top();
    }
    //pour jouer la premier carte
    Card* playFirstCard(){
        cout <<" Votre premiere carte est : | "<<hand.top()->getName()<<" |"<<endl;
        return hand.play();
    }
    //pour avoir une carte à partir d'un nom
    Card* getCard(string name){return hand.getCardByName(name);}
    //pour supprimer une carte à partir d'un nom
    void deletCard(string name){hand.removeCardByName(name);}
};
