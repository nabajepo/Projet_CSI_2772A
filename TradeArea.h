#ifndef TRADE_AREA_H
#define TRADE_AREA_H

#include <algorithm>
#include <iostream>
#include <list> //liste doublement chainée

string getSectionInfo(istream &file, int sectionID);

using namespace std;

class CardFactory;

class TradeArea {
  public:
    list<Card *> cards;
    // constructeur
    TradeArea() {}

    // Constructeur qui initialise la TradeArea à partir d'un flux istream
    TradeArea(istream &file, const CardFactory *factory) {
        vector<string> tr = split(getSectionInfo(file, 5), '.');
        if (tr.empty())
            return;

        vector<string> taille = split(tr[0], ':');
        int tailleT = stoi(taille[1]);
        if (tailleT != 0) {
            vector<string> cartes = split(split(tr[1], ':')[1], '|');
            for (string card : cartes)
                cards.push_back(
                    createCard(card)); // on insere le card dans le trade
        }
    }

    // Opérateur d'ajout d'une carte à l'échange
    TradeArea &operator+=(Card *newCard) {
        cards.push_back(newCard);
        return *this;
    }

    // Vérifie si une carte peut être ajoutée à l'échange
    bool legal(Card *card) {
        if (cards.size() == 0)
            return true;

        if (cards.front()->getName() == card->getName())
            return true;

        cout << "La carte " << card->getName() << " n'est pas valide " << endl;
        return false; // cad ne se trouve pas dans le trade
    }

    // Retourne le nombre de cartes dans l'échange
    int numCards() const { return cards.size(); }

    // Opérateur d'insertion pour afficher l'échange
    friend ostream &operator<<(ostream &os, const TradeArea &trade) {
        if (trade.numCards() > 0) {
            for (Card *card : trade.cards)
                os << card->getName() << "|";
            os << endl;
        } else
            os << "[INFO] Le trade est vide#" << endl;
        return os;
    }

    // detruit toute les cartes du trade
    void destroyTrade() { cards.clear(); }

    // pour sauvegarder le trade
    void saveTrade(string file, int index) {
        ofstream outFile(file, ios::app);
        if (outFile.is_open()) {
            outFile << index << endl;
            outFile << "Taille:" << cards.size() << endl;
            outFile << "Cartes:" << *this;
            outFile.close();
            cout << "[Sauvegarde] Le Trade a ete sauvegarde avec succes "
                 << endl;
        } else
            cout << "[ERREUR] Erreur de sauvegarde du Trade" << endl;
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
};

#endif