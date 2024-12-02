#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
class CardFactory;
class Card;

// Error exception
class IllegalType : public exception {
  public:
    const char *what() const noexcept override {
        return "Erreur de type de carte : ";
    }
};

// Interface abstraite de base pour les chaînes
class Chain_base {
  public:
    virtual string getNameChain() const = 0;
    virtual void destroyChain() = 0;
    virtual int sell() = 0;
    virtual int getSizeChain() const = 0;
    virtual ~Chain_base() = default;
};
template <class T>
// Classe Chain template pour les cartes
class Chain : public Chain_base {
  private:
    vector<T> cards; // Conteneur pour stocker les cartes
    T cardType;

  public:
    // constructeur
    Chain() : cardType(nullptr) {}
    
    // Constructeur qui accepte un istream et un CardFactory (pour la création
    // de cartes)
    Chain(istream &, const CardFactory *);
    // Opérateur += pour ajouter une carte à la chaîne
    Chain<T> &operator+=(T newCard) {
        try {
            if (cardType == nullptr) {
                cardType = newCard;
                cards.push_back(newCard);
                return *this;
            } else if (newCard->getName() == cardType->getName()) {
                cards.push_back(newCard);
                return *this;
            } else
                throw IllegalType();
        } catch (const IllegalType &e) {
            cout << e.what() << newCard->getName() << endl;
            return *this;
        }
    }
    // Méthode pour calculer le nombre de pièces en fonction des cartes dans la
    // chaîne
    int sell() override {
        if (cardType == nullptr)
            return 0;
        if ((cardType->getCardsPerCoin(1) == cards.size()) ||
            ((cardType->getCardsPerCoin(1) != 0) &&
             (cardType->getCardsPerCoin(1) < cards.size()) &&
             (cardType->getCardsPerCoin(2) > cards.size())))
            return 1;
        if ((cardType->getCardsPerCoin(2) == cards.size()) ||
            ((cardType->getCardsPerCoin(2) < cards.size()) &&
             (cardType->getCardsPerCoin(3) > cards.size())))
            return 2;
        if ((cardType->getCardsPerCoin(3) == cards.size()) ||
            ((cardType->getCardsPerCoin(3) < cards.size()) &&
             (cardType->getCardsPerCoin(4) > cards.size())) ||
            (cardType->getCardsPerCoin(4) == 0))
            return 3;
        if ((cardType->getCardsPerCoin(4) == cards.size()) ||
            ((cardType->getCardsPerCoin(4) < cards.size())))
            return 4;
        return 0;
    }

    // Methode pour savoir le nombre de cartes dans la chain
    int getSizeChain() const override { return cards.size(); }

    // Opérateur d'insertion pour afficher la chaîne
    friend ostream &operator<<(ostream &os, const Chain<T> &chain) {
        os << chain.cardType->getName() << " : ";
        for (auto card : chain.cards) {
            os << card->getName().at(0) << " ";
        }
        return os;
    }

    // return le nom de la chain
    string getNameChain() const override {
        if (cardType == nullptr)
            return "VIDE";
        else
            return cardType->getName();
    }

    // on supprime toute les cartes sur la chaine
    void destroyChain() override {
        vector<T> card;
        cards = card;
        cardType = nullptr;
        cout << "La chaine a ete detruit avec succes " << endl;
    }
    // on
};
