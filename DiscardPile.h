#ifndef DISCARD_PILe_H
#define DISCARD_PILe_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

string getSectionInfo(istream &file, int sectionID);

using namespace std;
class Card;
class DiscardPile {
    std::vector<Card *> cards;

  public:
    // Constructeur
    DiscardPile() {}

    // Constructeur qui accepte un istream et un CardFactory pour construire une
    // pile de cartes à partir d'un fichier
    DiscardPile(istream &file, const CardFactory *factory) {
        string discardInfo = getSectionInfo(file, 4);

        vector<string> ds = split(discardInfo, '.');
        if (ds.empty())
            return;

        vector<string> taille = split(ds[0], ':');
        int tailleD = stoi(taille[1]);
        if (tailleD != 0) {
            vector<string> cartes = split(split(ds[1], ':')[1], '|');
            for (string card : cartes)
                cards.push_back(createCard(card)); // utiliser factory Object
        }
    }

    // Ajoute une carte à la pile de déchet
    DiscardPile &operator+=(Card *card) {
        cards.push_back(card);
        return *this;
    }

    // Renvoie et supprime la carte supérieure de la pile
    Card *pickUp() {
        if (cards.size() > 0) {
            Card *topC = cards.back();
            cards.pop_back();
            return topC;
        } else {
            cout << "[ERREUR] Le  discardPile est vide" << endl;
            return nullptr;
        }
    }

    // Renvoie mais ne supprime pas la carte supérieure de la pile
    Card *top() const {
        if (cards.size() > 0)
            return cards.back();
        else {
            cout << "[INFO] Le  discardPile est vide " << endl;
            return nullptr;
        }
    }

    // Insère toutes les cartes de la pile dans un ostream
    void print(ostream &os) {
        if (cards.size() > 0) {
            for (Card *card : cards)
                os << card->getName() << "|";
            os << endl;
        } else
            os << "[INFO] Le discardPile est vide!" << endl;
    }

    int size() const { return cards.size(); }

    // Insère seulement la carte supérieure dans un ostream
    friend ostream &operator<<(ostream &os, const DiscardPile &dsc) {
        if (dsc.size() > 0)
            os << "|" << dsc.top()->getName() << "|" << endl;
        else
            os << "[INFO] La pile est vide " << endl;
        return os;
    }

    // pour sauvegarder le deck
    void saveDiscard(string file, int index) {
        ofstream outFile(file, ios::app);
        if (outFile.is_open()) {
            outFile << index << endl;
            outFile << "Taille:" << cards.size() << endl;
            outFile << "Cartes:";
            print(outFile);
            outFile.close();
            cout << "[Sauvegarde] Le discard a ete sauvegarde avec succes "
                 << endl;
        } else
            cout << "[ERREUR] Erreur de sauvegarde du discard " << endl;
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

    // creer une classe à l'aide d'un nom
    Card *createCard(string nameCard) {
        Card *card[] = {new Blue(), new Chili(), new Stink(), new Green(),
                        new Soy(),  new Black(), new Red(),   new Garden()};
        for (int index = 0; index < 8; index++)
            if (card[index]->getName() == nameCard)
                return card[index];
        return nullptr;
    }
};

#endif