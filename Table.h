#include "Game.h"
#include "TradeArea.h"
#include <filesystem>
#include <iostream>
#include <vector>

class DiscardPile;

using namespace std;

class Table {
  public:
    Player player1;  // joueur 1
    Player player2;  // joueur 2
    bool playerTurn; // FALSE: jouer 1, TRUE: joueur 2

    Deck deck;         // toutes les cartes melanagées
    DiscardPile trash; // contenant les cartes jéteé
    TradeArea trade;   // emplacement des cartes à echanger

    CardFactory factory; // pour factoty
    string checkPointFilename =
        "game.txt"; // pour l'emplacement du  fichier en question

    Game game;
    Table(const string playerOneName, const string playerTwoName)
        : player1(playerOneName), player2(playerTwoName), trade(), factory() {
        // start with player one
        playerTurn = false;

        // get deck
        deck = factory.getDeck();

        // draw 5 cards for the hand of each player
        for (int i = 0; i < 5; i++) {
            player1.addCardInHand(deck.draw());
        }

        for (int i = 0; i < 5; i++) {
            player2.addCardInHand(deck.draw());
        }
    };

    // get the player whose turn it is
    Player &getCurrentPlayer() {
        if (playerTurn == false) {
            return player1;
        }

        return player2;
    }

    // Toggle/change player turn
    void switchPlayer() { playerTurn = !playerTurn; }

    // @TODO: use factory class
    Table(istream &file, const CardFactory *factory)
        : player1(""), player2("") {}

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

    // on affiche toute les mains des joue  true toute les mains et false
    // une carte
    void printHand(bool choice) {
        cout << "Main du joueur 1:" << endl;
        player1.printHand(cout, choice);
        cout << "\n\n";

        cout << "Main du joueur 2:" << endl;
        player2.printHand(cout, choice);
        cout << "\n\n";
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
                save = true; // on commence à enregistrer si on arrive à
                             // l'index
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

    int getDeckSize() const { return deck.size(); }

    Card *drawCardFromDeck() { return deck.draw(); }

    TradeArea &getTradeArea() { return trade; }

    DiscardPile &getDiscardPile() { return trash; }
};
