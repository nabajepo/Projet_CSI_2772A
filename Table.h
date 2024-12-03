#include "Game.h"
#include <filesystem>
#include <iostream>
#include <vector>

class DiscardPile;
class TradeArea;

using namespace std;

class Table {
  public:
    Player player1; // joueur 1
    Player player2; // joueur 2

    Deck deck;         // toutes les cartes melanagées
    DiscardPile trash; // contenant les cartes jéteé
    TradeArea trade;   // emplacement des cartes à echanger

    CardFactory factory; // pour factoty
    string checkPointFilename =
        "game.txt"; // pour l'emplacement du  fichier en question

    Game game;
    Table(Player &ply1, Player &ply2, Deck &deckInit, DiscardPile &trashInit,
          TradeArea &tradeInit)
        : player1(ply1), player2(ply2) {
        deck = deckInit;
        trash = trashInit;
        trade = tradeInit;

        cout << "Bienvenue au jeu bohnanza" << endl;

        ifstream file(checkPointFilename);

        if (file.is_open()) { // si le fichier existe
            int choice = continueGame();
            if (choice == 1) { // on veut continue le jeu
                string roundP = getTurnPlayer(file);
                CardFactory *fact;
                Table table(file, fact);
                ply1 = table.player1;
                player1 = ply1;
                ply2 = table.player2;
                player2 = ply2;
                deckInit = table.deck;
                deck = deckInit;
                trashInit = table.trash;
                trash = trashInit, tradeInit = table.trade;
                trade = tradeInit;
                // if (split(roundP, ':')[1] == player1.getName()) {
                //     player = player1;
                //     ply = player;
                // } else {
                //     player = player2;
                //     ply = player;
                // }
                file.close();
                cout << "Le jeu a ete charge avec succes " << endl;
            } else { // on veut commencer un nouveau jeu
                file.close();
                deleteGame();
            }
        }
    }

    // @TODO: use factory class
    Table(istream &file, const CardFactory *factory)
        : player1(""), player2("") {
        // file.seekg(0, ios::beg);
        // player1 = Player(file, factory, 2);
        // file.seekg(0, ios::beg);
        // player2 = Player(file, factory, 3);
        // file.seekg(0, ios::beg);
        // trade = TradeArea(file, factory);
        // file.seekg(0, ios::beg);
        // trash = DiscardPile(file, factory);
        // file.seekg(0, ios::beg);
        // deck = Deck(file, factory);
    }

    bool win(string &winnerName) {
        if (deck.empty()) { // Si le Deck est vide
            int coinsPlayer1 = player1.getNumCoins();
            int coinsPlayer2 = player2.getNumCoins();

            if (coinsPlayer1 > coinsPlayer2) {
                winnerName = player1.getName(); // Le joueur 1 a gagné
                return true;
            } else if (coinsPlayer2 > coinsPlayer1) {
                winnerName = player2.getName(); // Le joueur 2 a gagné
                return true;
            } else {
                return false; // Aucun gagnant
            }
        }

        return false; // Personne ne gagne tant que le Deck n'est pas vide
    }

    // on affiche toute les mains des joue  true toute les mains et false une
    // carte
    void printHand(bool choice) {
        cout << "Main du joueur 1:" << endl;
        player1.printHand(cout, choice);
        cout << endl;

        cout << "Main du joueur 2:" << endl;
        cout << endl;
        player2.printHand(cout, choice);
    }

    // pour mettre à jour la table
    void updateTable(Player &playe, Player &playe1, Player &playe2,
                     DiscardPile &dr, TradeArea &tr, Deck &decOfC) {
        player1 = playe1;
        player2 = playe2;
        trash = dr;
        trade = tr;
        deck = decOfC;
        cout << "La table a ete mise a jour " << endl;
    }

    // Afficher la table
    friend ostream &operator<<(ostream &os, const Table &table) {
        os << "--------------------TABLE---------------------" << endl;
        os << "Player 1: " << endl << table.player1; // Affiche le joueur 1
        os << "Player 2: " << endl << table.player2; // Affiche le joueur 2
        os << "Discard Pile: " << endl
           << table.trash << endl; // Affiche la pile de défausse
        os << "Trade Area: " << endl
           << "------------------END-TABLE--------------------" << endl;
        return os;
    }

    // affiche les joueurs
    void showPlayers() const {
        cout << "------------INFO-PLAYERS---------------" << endl;
        cout << "Pour joueur 1 : " << endl;
        cout << player1;
        cout << "Pour joueur 2 : " << endl;
        cout << player2;
        cout << "---------------------------------------" << endl;
    }

    // pour enregistrer le jeu
    void saveTable() {
        ofstream outFile(checkPointFilename);
        if (outFile.is_open()) {
            outFile << 1 << endl;
            // outFile << "Tour:" << player.getName() << endl;
            player1.savePlayer(checkPointFilename, 2);
            player2.savePlayer(checkPointFilename, 3);
            trash.saveDiscard(checkPointFilename, 4);
            trade.saveTrade(checkPointFilename, 5);
            deck.saveDeck(checkPointFilename, 6);
            outFile.close();
            cout << "Le jeu a ete enregistre avec succes " << endl;
        } else {
            cout << "Erreur dans la sauvergarde du jeu " << endl;
        }
    }

    // Si on a deja un jeu en attente
    int continueGame() {
        int choice;
        cout << "Un jeu est deja enregistrer : " << endl
             << "1.Voulez-vous continue le meme jeu " << endl
             << "2.Voulez-vous commencez un nouveau jeu " << endl
             << "Entrez votre choix : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez un nombre valide " << endl;
            return continueGame();
        } else
            return choice;
    }

    // pour avoir d'un joueur
    string getNamePlayer(int pos) {
        string playerName;
        cout << "Entrez le nom du joueur " << pos << " : ";
        getline(cin >> ws, playerName);
        if (playerName.empty()) {
            cout << "SVP entrez un nom valide " << endl;
            return getNamePlayer(pos);
        } else
            return playerName;
    }

    // pour supprimer le jeu qui etait enregistrer
    void deleteGame() {
        // filesystem::remove(checkPointFilename);
    }

    // pour stocker les informations du jouer qui jouer
    string getTurnPlayer(istream &file) {
        string info = "";
        string line;
        bool save = false;
        while (getline(file, line)) {
            if (line == "1")
                save = true; // on commence à enregistrer si on arrive à l'index
            else if (line == "2")
                break; // on stop quand on arrive à l'index 5
            else if (save)
                info = info + line + ".";
        }
        return info;
    }

    // pour split un string
    vector<string> split(const string &str, char delimiter) {
        vector<string> tokens;
        istringstream stream(str);
        string token;
        while (getline(stream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};
