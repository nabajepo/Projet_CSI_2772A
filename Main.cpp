#include "Card.h"
#include "CardFactory.h"
#include "Chain.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

#define LOG(x) cout << x << endl;

int main() {
    // Game
    Game game;

    string playerOneName, playerTwoName;
    playerOneName = game.inputPlayerName();
    playerTwoName = game.inputPlayerName();

    // Table
    Table table(playerOneName, playerTwoName);

    cout << "Bienvenue au jeu bohnanza" << endl;

    /// Pour jouer
    while (table.getDeckSize() > 0) {
        Player &currentPlayer = table.getCurrentPlayer();
        cout << "[INFO] " << currentPlayer.getName() << " is playing!" << endl;
        // game.showMenu(currentPlayer.getName());
        // on affiche la table
        table.printHand(1);

        // Player draws top card from Deck
        currentPlayer.addCardInHand(table.drawCardFromDeck());

        // If TradeArea is not empty
        //      Add bean cards from the TradeArea to chains or discard them.
        if (table.getTradeArea().cards.size()) {
            cout << "there are " << table.getTradeArea().cards.size()
                 << " cards in trade area!" << endl;
            for (Card *card : table.getTradeArea().cards) {
                cout << "Do you want to add " << card->getName()
                     << " to your chains? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    try {
                        currentPlayer.addCardToChain(1, card);
                    } catch (const IllegalType &) {
                        try {
                            currentPlayer.addCardToChain(2, card);
                        } catch (const IllegalType &e) {
                            cout << e.what()
                                 << "Card cannot be added to either chain."
                                 << endl;
                            //@TODO: is this right?
                            table.getDiscardPile().operator+=(card);
                        }
                    }

                } else {
                    table.getDiscardPile().operator+=(card);
                }
            }
            // discard cards
            table.getTradeArea().cards.clear();
        }

        // Play topmost card from Hand.
        cout << "Playing top card and adding it to chain ..." << endl;
        Card *card = currentPlayer.playFirstCard();

        try {
            currentPlayer.addCardToChain(1, card);
        } catch (const IllegalType &) {
            try {
                currentPlayer.addCardToChain(2, card);
            } catch (const IllegalType &e) {
                cout << e.what() << "Card cannot be added to either chain."
                     << endl;
                //@TODO: is this right?
                table.getDiscardPile().operator+=(card);
            }
        }

        // If chain is ended, cards for chain are removed and player receives
        // coin(s).
        // Sell chain 1
        try {
            int coins = currentPlayer.getChain(1).sell();
            if (coins) {
                currentPlayer.operator+=(coins);
                currentPlayer.getChain(1).destroyChain();
            }

            // sell chain 2
            coins = currentPlayer.getChain(2).sell();
            if (coins) {
                currentPlayer.operator+=(coins);
                currentPlayer.getChain(2).destroyChain();
            }
        } catch (const out_of_range &) {
            cout << "[ERROR] Chain index out of range!" << endl;
        }

        // If player decides to Show the player's full hand and player
        // selects an arbitrary card Discard the arbitrary card from the
        // player's hand and place it on the discard pile.

        // Draw three cards from the deck and place cards in the trade area
        for (int i = 0; i < 3; i++) {
            table.getTradeArea().cards.push_back(table.drawCardFromDeck());
        }

        // while top card of discard pile matches an existing card in the trade
        // area
        //      draw the top-most card from the discard pile and place it in the
        //      trade area end

        // for all cards in the trade area
        //      if player wants to chain the card chain the card.
        //      else card remains in trade area for the next player.
        // end

        // Draw two cards from Deck and add the cards to the player's hand (at
        // the back).
        for (int i = 0; i < 2; i++) {
            currentPlayer.addCardInHand(table.drawCardFromDeck());
        }

        // on continue à jouer
        cout << "Il reste dans le deck que " << table.getDeckSize()
             << " cartes " << endl;

        table.switchPlayer();
    }
}
