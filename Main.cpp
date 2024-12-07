#include "Card.h"
#include "Chain.h"
#include "Game.h"
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
    string winner;

    Table *table = game.loadGame();

    cout << "\nBienvenue au jeu Bohnanza\n" << endl;

    /// Pour jouer
    while (!table->win(winner)) {
        Player &currentPlayer = table->getCurrentPlayer();
        cout << "[INFO] C'est le tour de " << currentPlayer.getName() << endl;

        if (game.shouldPause()) {
            table->saveTable();
            exit(0);
        }

        // on affiche la table
        table->printHand(1);

        // Player draws top card from Deck
        currentPlayer.addCardInHand(table->drawCardFromDeck());

        // If TradeArea is not empty
        //      Add bean cards from the TradeArea to chains or discard them.
        if (table->getTradeArea().cards.size()) {
            cout << "Il y a " << table->getTradeArea().cards.size()
                 << " cartes dans trade area!" << endl;
            for (Card *card : table->getTradeArea().cards) {
                cout << "[TradeArea] Voulez-vous rajoute " << card->getName()
                     << " a vos chaines? (y/n): ";
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
                                 << "La carte ne peut pas etre rajouter a "
                                    "aucune chaine!"
                                 << endl;
                            table->getDiscardPile().operator+=(card);
                        }
                    }

                } else {
                    table->getDiscardPile().operator+=(card);
                }
            }
            // discard cards
            table->getTradeArea().cards.clear();
        }

        // Play topmost card from Hand.
        cout << "On joue la carte au dessus de la main du joeur ..." << endl;
        Card *card = currentPlayer.playFirstCard();

        try {
            currentPlayer.addCardToChain(1, card);
        } catch (const IllegalType &) {
            try {
                currentPlayer.addCardToChain(2, card);
            } catch (const IllegalType &e) {
                cout << e.what()
                     << "La carte ne peut pas etre rajouter a aucune chaine!"
                     << endl;
                table->getDiscardPile().operator+=(card);
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
            cout << "[ERREUR] Chain index out of range!" << endl;
        }

        // If player decides to Show the player's full hand and player
        // selects an arbitrary card Discard the arbitrary card from the
        // player's hand and place it on the discard pile.

        // Draw three cards from the deck and place cards in the trade area
        for (int i = 0; i < 3; i++) {
            table->getTradeArea().cards.push_back(table->drawCardFromDeck());
        }

        // while top card of discard pile matches an existing card in the trade
        // area
        //      draw the top-most card from the discard pile and place it in the
        //      trade area end
        Card *topCard = table->getDiscardPile().top();
        if (topCard != nullptr) {
            bool matchFound = false;

            for (Card *tradeCard : table->getTradeArea().cards) {
                if (tradeCard->getName() == topCard->getName()) {
                    matchFound = true;
                    break;
                }
            }

            if (matchFound) {
                table->getTradeArea().cards.push_back(
                    table->getDiscardPile().pickUp());
            }
        }

        // for all cards in the trade area
        //      if player wants to chain the card chain the card.
        //      else card remains in trade area for the next player.
        // end

        // copy cards to prevent removing elements while removing them
        auto tradeAreaCards = table->getTradeArea().cards;
        for (Card *card : tradeAreaCards) {
            cout << "[TradeArea] Voulez-vous rajoute " << card->getName()
                 << " a vos chaines? (y/n): ";
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
                             << "La carte ne peut pas etre rajouter a aucune "
                                "chaine!"
                             << endl;
                        // Leave card in trade area
                        continue;
                    }
                }

                // Remove card from trade area if successfully added to chain
                auto it = find(table->getTradeArea().cards.begin(),
                               table->getTradeArea().cards.end(), card);
                if (it != table->getTradeArea().cards.end()) {
                    table->getTradeArea().cards.erase(it);
                }
            }
        }

        // Draw two cards from Deck and add the cards to the player's hand (at
        // the back).
        for (int i = 0; i < 2; i++) {
            currentPlayer.addCardInHand(table->drawCardFromDeck());
        }

        // on continue à jouer
        cout << "Il reste dans le deck que " << table->getDeckSize()
             << " cartes\n\n";

        table->switchPlayer();
    }

    cout << "Le gagnant est: " << winner << endl;
    cout << "FIN" << endl;

    return 0;
}

string getSectionInfo(istream &file, int sectionID) {
    file.clear();
    file.seekg(0, ios::beg);

    string info, line;
    bool saving = false;
    while (getline(file, line)) {
        if (line == to_string(sectionID)) {
            saving = true;
            continue;
        }
        // Stop saving once we reach the next position
        if (line == to_string(sectionID + 1)) {
            break;
        }
        // Collect lines if in saving mode
        if (saving) {
            if (!info.empty()) {
                info += "."; // Add a delimiter between lines
            }
            info += line;
        }
    }
    return info;
}