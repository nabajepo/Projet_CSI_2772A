#include <cassert>
#include <iostream>
#include <vector>
using namespace std;
class Card;
class CardFactory;
class Hand {
  private:
    vector<Card *> cards; // Conteneur pour stocker les cartes de la main

  public:
    // constructeur
    Hand() {}
    // Constructeur pour construire la main à partir d'un flux istream
    Hand(istream &, const CardFactory *);
    // Ajoute une carte derrière la dernière carte de la main
    Hand &operator+=(Card *newCard) {
        cards.push_back(newCard);
        return *this;
    }
    // Renvoie et supprime la première carte de la main
    Card *play() {
        if (getSizeHand() > 0) {
            Card *topCard = cards[0];
            cout << " Votre premiere carte est : | " << topCard->getName()
                 << " |" << endl;
            cards.erase(cards.begin());
            return topCard;
        } else {
            cout << "Votre main est vide " << endl;
            return nullptr;
        }
    }

    // pour avoir le nombre de carte sur la main
    int getSizeHand() const { return cards.size(); }

    // Renvoie mais ne supprime pas la première carte de la main
    Card *top() {
        if (getSizeHand() > 0) {
            cout << " Votre premiere carte est : | " << cards[0]->getName()
                 << " |" << endl;
            return cards[0];
        } else {
            cout << "Votre main est vide " << endl;
            return nullptr;
        }
    }

    // Renvoie et supprime une carte à une position donnée
    Card *operator[](int index) {
        Card *card = cards[index];
        cards.erase(cards.begin() + index);
        return card;
    }

    // Affiche toutes les cartes dans la main
    friend ostream &operator<<(ostream &os, const Hand &hand) {
        if (hand.getSizeHand() > 0) {
            for (Card *card : hand.cards) {   // Suppose que Deck est itérable
                os << card->getName() << "|"; // Écriture directe dans le flux
            }
            os << endl;
        } else
            os << "#Votre main est vide#" << endl;
        return os;
    }

    // avoir une carte à partir d'un nom
    Card *getCardByName(string nameCard) {
        for (Card *card : cards)
            if (card->getName() == nameCard)
                return card;
        return nullptr; // si nous ne trouvons pas
    }

    // supprime une carte par le nom
    void removeCardByName(string nameCard) {
        for (int index = 0; index < cards.size(); index++)
            if (cards[index]->getName() == nameCard)
                cards.erase(cards.begin() + index);
    }
};
