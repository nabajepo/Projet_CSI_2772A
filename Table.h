#ifndef TABLE_H
#define TABLE_H

#include "CardFactory.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include <iostream>
#include <vector>

using namespace std;

class Table {
    Player player1;    // joueur 1
    Player player2;    // joueur 2
    bool playerTurn;   // FALSE: jouer 1, TRUE: joueur 2
    Deck deck;         // toutes les cartes melanagées
    DiscardPile trash; // contenant les cartes jéteé
    TradeArea trade;   // emplacement des cartes à echanger

    CardFactory factory; // pour factoty

  public:
    // pour l'emplacement du  fichier en question
    static const string CHECKPOINTFILENAME;

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

    Table(istream &file, const CardFactory *factory)
        : player1(file, factory, 2), player2(file, factory, 3),
          trade(file, factory), trash(file, factory), deck(file, factory),
          factory() {
        playerTurn = getTurnPlayer(file);
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

    // on affiche toute les mains des joue  true toute les mains et false
    // une carte
    void printHand(bool choice) {
        cout << "Main de " << player1.getName() << endl;
        player1.printHand(cout, choice);
        cout << "\n\n";

        cout << "Main de " << player2.getName() << endl;
        player2.printHand(cout, choice);
        cout << "\n\n";
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
        cout << player1.getName();
        cout << "Pour joueur 2 : " << endl;
        cout << player2.getName();
        cout << "---------------------------------------" << endl;
    }

    // pour enregistrer le jeu
    void saveTable() {
        ofstream outFile(CHECKPOINTFILENAME);
        if (outFile.is_open()) {
            outFile << 1 << endl;
            outFile << "Tour:" << playerTurn << endl;
            outFile.close();

            player1.savePlayer(CHECKPOINTFILENAME, 2);
            player2.savePlayer(CHECKPOINTFILENAME, 3);
            trash.saveDiscard(CHECKPOINTFILENAME, 4);
            trade.saveTrade(CHECKPOINTFILENAME, 5);
            deck.saveDeck(CHECKPOINTFILENAME, 6);

            cout << "[Sauvegarde] Le jeu a ete enregistre avec succes " << endl;
        } else {
            cout << "[ERROR] Erreur dans la sauvergarde du jeu " << endl;
        }
    }

    void deleteGame() { remove(CHECKPOINTFILENAME.c_str()); }

    // pour stocker les informations du jouer qui jouer
    bool getTurnPlayer(istream &file) {
        file.clear();
        file.seekg(0, ios::beg);
        string line;
        while (getline(file, line)) {
            if (line.find("Tour:") != string::npos)
                return line.find("1") != string::npos;
        }
        return false;
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

const string Table::CHECKPOINTFILENAME = "game.txt";

#endif