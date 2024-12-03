#include <algorithm>
#include <iostream>
#include <list> //liste doublement chainée

using namespace std;

class CardFactory;

class TradeArea {
  public:
    list<Card *> cards;
    // constructeur
    TradeArea() {}

    // Constructeur qui initialise la TradeArea à partir d'un flux istream
    TradeArea(istream &file, const CardFactory *factory) {
        vector<string> tr = split(getInfoTrade(file), '.');
        vector<string> taille = split(tr[0], ':');
        int tailleT = stoi(taille[1]);
        if (tailleT != 0) {
            vector<string> cards = split(split(tr[1], ':')[1], '|');
            // @TODO: use factory
            // for (string card : cards)
            // cards.push_back(
            //     createCard(card));
            // on insere le card dans le trade
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

    // // supprime une carte donnée et la retourne
    // Card *trade(string nameCard) {
    //     auto it = std::find_if(cards.begin(), cards.end(), [&](Card &card) {
    //         return card.name() == nameCard;
    //     });

    //     if (it != cards.end()) {
    //         Card *cardN = *it;
    //         cards.erase(it); // Supprime la carte trouvée
    //         return cardN;    // Retourne la carte trouvée
    //     }
    //     return nullptr; // Retourne nullptr si aucune carte ne correspond
    // }

    // Retourne le nombre de cartes dans l'échange
    int numCards() const { return cards.size(); }

    // Opérateur d'insertion pour afficher l'échange
    friend ostream &operator<<(ostream &os, const TradeArea &trade) {
        if (trade.numCards() > 0) {
            for (Card *card : trade.cards)
                os << card->getName() << "|";
            os << endl;
        } else
            os << "#Le trade est vide#" << endl;
        return os;
    }

    // retourner  une carte à une position donnée
    Card *getElementAt(int index) {
        if (numCards() > 0) {
            auto it = cards.begin();
            advance(it, index);
            return *it;
        } else {
            cout << "#Le trade est vide# " << endl;
            return nullptr;
        }
    }

    // retourne une carte par le nom
    Card *getCardByName(string nameCard) {
        for (Card *card : cards)
            if (nameCard == card->getName())
                return card;
        return nullptr; // si on ne trouve rien
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
            cout << "Le Trade a ete sauvegarde avec succes " << endl;
        } else
            cout << "Erreur de sauvegarde du Trade " << endl;
    }

    // pour stocker les informations du Trade dans un string
    string getInfoTrade(istream &file) {
        string info = "";
        string line;
        bool save = false;
        while (getline(file, line)) {
            if (line == "5")
                save = true; // on commence à enregistrer si on arrive à l'index
            else if (line == "6")
                break; // on stop quand on arrive à l'index 5
            else if (save)
                info = info + line + ".";
        }
        return info;
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
