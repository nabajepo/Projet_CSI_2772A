#include "Deck.h"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Card;

using namespace std;

class CardFactory {
  private:
    vector<Card *> cards;
    static CardFactory *instance; // contient la seul instance du CardFactory
  public:
    CardFactory() {
        // Blue (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Blue());
        }

        // Chili (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Chili());
        }

        // Stink (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Stink());
        }

        // Green (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Green());
        }

        // Soy (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Soy());
        }

        // Black (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Black());
        }

        // Red (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Red());
        }

        // Garden (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Garden());
        }
        cout << "[INFO] # Cards in deck: " << cards.size() << endl;
    }

    static CardFactory *getFactory() {
        if (instance == nullptr) {
            instance = new CardFactory();
        }
        return instance;
    } // Renvoie un unique instance de CardFactory

    Deck getDeck() {
        std::random_device rd;
        std::mt19937 g(rd());
        shuffle(cards.begin(), cards.end(), g);

        Deck deck;
        for (Card *card : cards) {
            deck.push_back(card);
        }

        return deck;
    } // Renvoie un Deck contenant toutes les cartes, mélangées

    CardFactory(const CardFactory &) = delete; // Interdire la copie
    CardFactory &
    operator=(const CardFactory &) = delete; // Interdire l'affectation
};

CardFactory *CardFactory::instance = nullptr;