#include "Deck.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <random>

class Card;

using namespace std;

class CardFactory {
  private:
    vector<Card *> cards;
    static CardFactory *instance; // contient la seul instance du CardFactory
  public:
    CardFactory() {
        // Blue (20)
        for (int i = 0; i < 20; i++) {
            cards.push_back(new Blue());
        }

        // Chili (18)
        for (int i = 0; i < 18; i++) {
            cards.push_back(new Chili());
        }

        // Stink (16)
        for (int i = 0; i < 16; i++) {
            cards.push_back(new Stink());
        }

        // Green (14)
        for (int i = 0; i < 14; i++) {
            cards.push_back(new Green());
        }

        // Soy (12)
        for (int i = 0; i < 12; i++) {
            cards.push_back(new Soy());
        }

        // Black (10)
        for (int i = 0; i < 10; i++) {
            cards.push_back(new Black());
        }

        // Red (8)
        for (int i = 0; i < 8; i++) {
            cards.push_back(new Red());
        }

        // Garden (6)
        for (int i = 0; i < 6; i++) {
            cards.push_back(new Garden());
        }
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