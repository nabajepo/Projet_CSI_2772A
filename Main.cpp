#include "Card.h"
#include "CardFactory.h"
#include "Chain.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Player.h"
#include "TradeArea.h"
#include "Table.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#define LOG(x) cout << x << endl;

void changeTurn(Player *cPlayer, Player *player1, Player *player2) {
    if (cPlayer == player1) {
        cPlayer = player2;
    } else {
        cPlayer = player1;
    }
}

int main() {
    // Game
    Game game;
    // Deck
    Deck deckOfCard;
    // DiscardPile
    DiscardPile trash;
    // TradeArea
    TradeArea trade;

    // Player1
    Player *player1;
    // Player2
    Player *player2;

    // Player (celui qui joue )
    Player *currentPlayer;

    string playerOneName, playerTwoName;
    cout << "Enter name for player 1: ";
    getline(cin, playerOneName);
    cout << "Enter name for player 2: ";
    getline(cin, playerTwoName);

    player1 = new Player(playerOneName);
    player2 = new Player(playerTwoName);
    currentPlayer = player1;

    // Table
    Table table(*player1, *player2, deckOfCard, trash, trade);

    /// Pour jouer
    while (deckOfCard.size() > 0) {
        // on veut faire une pause
        int pause = game.pause(currentPlayer->getName());
        if (pause == 2) {
            table.saveTable();
            break;
        }

        // on affiche la table
        table.printHand(1);

        // Cartes
        currentPlayer->printHand(cout, true);

        // on continue à jouer
        cout << "Il reste dans le desk que " << deckOfCard.size() << " cartes "
             << endl;

        // change turn
        changeTurn(currentPlayer, player1, player2);
    }
}
