#ifndef CHAIN_H
#define CHAIN_H

#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <vector>

using namespace std;
class CardFactory;
class Card;

// Error exception
class IllegalType : public exception {
  public:
    const char *what() const noexcept override {
        return "Erreur de type de carte: ";
    }
};

// Interface abstraite de base pour les chaînes
class Chain_Base {
  public:
    virtual string getNameChain() const = 0;
    virtual void destroyChain() = 0;
    virtual int sell() = 0;
    virtual int getSizeChain() const = 0;
    virtual ~Chain_Base() = default;
};

template <class T>
// Classe Chain template pour les cartes
class Chain : public Chain_Base {
  private:
    vector<T> cards; // Conteneur pour stocker les cartes

  public:
    Chain() {}
    // Constructeur qui accepte un istream et un CardFactory (pour la création
    // de cartes). TODO: implement this function
    Chain(istream &, const CardFactory *);

    // Opérateur += pour ajouter une carte à la chaîne
    Chain<T> &operator+=(Card *newCard) {
        if (typeid(T) != typeid(newCard))
            throw IllegalType();

        cards.push_back(newCard);
        return *this;
    }

    // Méthode pour calculer le nombre de pièces en fonction des cartes dans
    // la chaîne
    int sell() override {
        if (cards.size() == 0)
            return 0;

        int size = cards.size();
        T card = cards.front();
        int coins = 0;

        for (int i = 1; i <= 4; ++i) {
            if (card->getCardsPerCoin(i) == size) {
                coins = i;
                break;
            } else if (card->getCardsPerCoin(i) < size &&
                       (i == 4 || card->getCardsPerCoin(i + 1) > size ||
                        card->getCardsPerCoin(i + 1) == 0)) {
                coins = i;
                break;
            }
        }

        return coins;
    }

    // Methode pour savoir le nombre de cartes dans la chain
    int getSizeChain() const override { return cards.size(); }

    // Opérateur d'insertion pour afficher la chaîne
    friend ostream &operator<<(ostream &os, const Chain<T> &chain) {
        os << chain.cardType->getName() << "\t";
        for (auto card : chain.cards) {
            os << card->getName().at(0) << " ";
        }
        os << endl;

        return os;
    }

    // return le nom de la chain
    string getNameChain() const override {
        if (cards.size() == 0)
            return "VIDE";
        else
            return cards.front()->getName();
    }

    // on supprime toute les cartes sur la chaine
    void destroyChain() override {
        cards.clear();
        cout << "[INFO] La chaine a ete detruit avec succes " << endl;
    }

    Card *getCard(int index) const { return cards[index]; }
};

#endif