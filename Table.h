#include  <iostream>
#include <filesystem>
#include <vector>
#include "Game.h"
using namespace std;
class Player;
class Deck;
class Card;
template <typename C>
class TradeArea;
template <typename C>
class Table {
  public:
       Player player;//celui qui est entrain de jouer 
       Player wtPlayer;//celui qui attend son tour 
       Player player1;//joueur 1
       Player player2;//joueur 2
       Deck deckOfC;//toutes les cartes melanagées
       DiscardPile<C> trash;//contenant les cartes jéteé
       TradeArea<C> trade;//emplacement des cartes à echanger 
       CardFactory factory;//pour factoty
       string nameFile;//pour l'emplacement du  fichier en question 
       Game game;
    Table(Player& ply1,
          Player& ply2,
          Player& ply,
          Deck& deck,
          DiscardPile<C>& trashT,
          TradeArea<C>& tradeT
          ):
          player1(ply1),
          player2(ply2),
          player(ply),
          deckOfC(deck),
          trash(trashT),
          trade(tradeT),
          nameFile("game.txt"){
            cout<<"Bienvenue au jeu bohnanza"<<endl; 
            ifstream file(nameFile);
            if(file.is_open()){//si le fichier existe 
              int choice=continueGame();
              if(choice==1){//on veut continue le jeu
                 string roundP=getTurnPlayer(file);
                 CardFactory* fact;
                 Table table(file,fact);
                 ply1=table.player1;
                 player1=ply1;
                 ply2=table.player2;
                 player2=ply2;
                 deck=table.deckOfC;
                 deckOfC=deck;
                 trashT=table.trash;
                 trash=trashT,
                 tradeT=table.trade;
                 trade=tradeT;
                 if(split(roundP,':')[1]==player1.getName())
                 {player=player1; 
                 ply=player;}
                 else {player=player2; ply=player;}
                 file.close();
                 cout<<"Le jeu a ete charge avec succes "<<endl;
              }
              else{//on veut commencer un nouveau jeu
                  file.close();
                  deleteGame();
                  startNewGame(ply,ply1,ply2,deck);
              }
            }
            else{//si le fichier n'existe 
               startNewGame(ply,ply1,ply2,deck);
            }
            
          }
    Table(istream& file, const CardFactory* factory){
          file.seekg(0, ios::beg);
          player1=Player(file,factory,2);
          file.seekg(0, ios::beg);
          player2=Player(file,factory,3);
          file.seekg(0, ios::beg);
          trade=TradeArea<C>(file,factory);
          file.seekg(0, ios::beg);
          trash=DiscardPile<C>(file,factory);
          file.seekg(0, ios::beg);
          deckOfC=Deck(file,factory);
         }
    bool win(string& winnername){
        if (deckOfC.size()==0) { // Si le Deck est vide
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
    } 
    //pour mettre à jour la table 
    void updateTable(Player& playe,Player& playe1,Player& playe2,
                  DiscardPile<Card*>& dr,TradeArea<Card*>& tr,Deck& decOfC){
         player=playe;
         player1=playe1;
         player2=playe2;
         trash=dr;
         trade=tr;
         deckOfC=decOfC;
         cout <<"La table a ete mise a jour "<<endl;
    }
    // Afficher la table
    friend ostream& operator<<(ostream& os, const Table& table){
        os<<"--------------------TABLE---------------------"<<endl;
        os << "Player 1: " <<endl<<table.player1; // Affiche le joueur 1
        os << "Player 2: " <<endl<< table.player2; // Affiche le joueur 2
        os << "Discard Pile: "<<endl<<table.trash<< endl; // Affiche la pile de défausse
        os << "Trade Area: " <<endl<<table.trade << endl;     // Affiche la zone commerciale*/
        os<<"------------------END-TABLE--------------------"<<endl;
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
    //pour enregistrer le jeu
    void saveTable(){
      ofstream outFile(nameFile);
      if(outFile.is_open()){
        outFile<< 1<<endl;
        outFile<<"Tour:"<<player.getName()<<endl;
        player1.savePlayer(nameFile,2);
        player2.savePlayer(nameFile,3);
        trash.saveDiscard(nameFile,4);
        trade.saveTrade(nameFile,5);
        deckOfC.saveDeck(nameFile,6);
        outFile.close();
        cout<<"Le jeu a ete enregistre avec succes "<<endl;
      }
      else{
        cout <<"Erreur dans la sauvergarde du jeu "<<endl;
      }
    }
    //pour commencer un nouveau jeu
    void startNewGame(Player& ply,Player& play1,Player& play2,Deck& deck){
         string np1=getNamePlayer(1);
         string np2=getNamePlayer(2);
         play1=Player(np1);
         play2=Player(np2);
         deck=factory.getDeck();
         for(int index=0;index<5;index++)play1.addCardInHand(deck.draw());
         for(int index=0;index<5;index++)play2.addCardInHand(deck.draw());
         player1=play1;
         player2=play2;
         deckOfC=deck;
         ply=play1;
         player=ply;
         cout<<"On commence un nouveau jeu "<<endl;
    }
     //Si on a deja un jeu en attente
     int continueGame(){
           int choice;
           cout<<"Un jeu est deja enregistrer : "<<endl
           <<"1.Voulez-vous continue le meme jeu "<<endl
           <<"2.Voulez-vous commencez un nouveau jeu "<<endl
           <<"Entrez votre choix : ";
           cin>>choice;
           if (choice!=1 && choice!=2){
               cout<<"SVP entrez un nombre valide "<<endl;
               return continueGame();
            }
           else return choice;
       }
       //pour avoir d'un joueur 
       string getNamePlayer(int pos){
          string playerName;
          cout<<"Entrez le nom du joueur "<<pos<<" : ";
          getline(cin>>ws,playerName);
          if(playerName.empty()){
            cout<<"SVP entrez un nom valide "<<endl;
            return getNamePlayer(pos);
          }
          else return playerName;
       }
       //pour supprimer le jeu qui etait enregistrer
       void deleteGame(){
           filesystem::remove(nameFile);
       }
       //pour stocker les informations du jouer qui jouer
       string getTurnPlayer(istream& file){
          string info="";
          string line;
          bool save=false;
          while(getline(file,line)){
            if(line=="1")save=true;//on commence à enregistrer si on arrive à l'index
            else if(line=="2")break;//on stop quand on arrive à l'index 5
            else if(save)info=info+line+"."; 
          }
          return info;
       }
     
        //pour split un string 
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        istringstream stream(str);
        string token;
        while (getline(stream, token, delimiter)) {
               tokens.push_back(token);
        }
        return tokens;
    }
    //Pour jouer un tour
    void playTurn(Player& playerG,Player& waitPlayer,Deck& dec){
     
    }
    //pour piocher 
    void pioche(){}
    //pour trade
    void trade(){}
    //pour terminer son tour en ajoutant 3 cartes au back;
    void addCardsTurn(){
      for(int index=0;index<2;index++)player.addCardInHand(deckOfC.draw());
    }
    
   
    
    
       
};
