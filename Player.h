#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// quand on veut acheter une chaine
class NotEnoughCoins : public exception {
  public:
    const char *what() const noexcept override {
        return "Desole vous avez pas acces de coins pour une 3 eme chaine il "
               "faut au moins 2 coins";
    }
};
class Player {
  private:
    string name;                  // Nom du joueur
    int coins;                    // Nombre de pièces
    vector<Chain<Card *>> chains; // Chaînes du joueur
    Hand hand;                    // Main du joueur
    int position; // represente la position du joueur dans le fichier
  public:
    // constructeur avec un nom
    Player(const string &playerName) {
        name = playerName;
        coins = 0;

        Chain<Card *> chainOne;
        chains.push_back(chainOne); // on a initialement 2 chaines  vides

        Chain<Card *> chainTwo;

        chains.push_back(chainTwo);
    } // Constructeur avec nom

    // @TODO: use factory object to generate cards
    Player(istream &file, const CardFactory *factory,
           int pos) { // constructeur du flux
        position = pos;
        vector<string> plt = split(getInfoPlayer(file), '.');
        name = split(plt[0], ':')[1];
        coins = stoi(split(plt[1], ':')[1]);
        int lenCh = stoi(split(plt[2], ':')[1]);
        for (int index = 0; index < lenCh; index++) {
            if (index == 0)
                makeChain(plt, 3);
            else if (index == 1)
                makeChain(plt, 5);
            else
                makeChain(plt, 7);
        }
        vector<string> taille;
        vector<string> cards;
        if (lenCh == 3) {
            taille = split(plt[9], ':');
            cards = split(plt[10], ':');
        } else {
            taille = split(plt[7], ':');
            cards = split(plt[8], ':');
        }
        int tailleP = stoi(taille[1]);
        if (tailleP != 0) {
            vector<string> hand = split(cards[1], '|');
            for (string card : hand)
                addCardInHand(
                    createCard(card)); // on insere le card dans le trade
        }
    }

    string getName() { return name; } // Obtenir le nom du joueur

    int getNumCoins() { return coins; }; // Obtenir le nombre de pièces

    Player &operator+=(int coinsN) {
        coins += coinsN;
        return *this;
    } // Ajouter des pièces

    int getMaxNumChains() { return 3; } // Obtenir le nombre max de chaînes.

    int getNumChains() const {
        return chains.size();
    } // Obtenir le nombre actuel de chaînes

    Chain<Card *> &
    operator[](int index) { // obtenir une chaine à une position donnée
        return chains[index];
    } // Accès à une chaîne par index

    // Acheter une troisième chaîne
    void buyThirdChain() {
        try {
            if (getNumChains() < getMaxNumChains()) {
                if (coins >= 2) {
                    coins -= 2; // on reduit de 2 le nombre de coins
                    Chain<Card *> newChaine;
                    chains.push_back(newChaine);
                    cout << "Vous avez payez avec succes une 3 eme chaine  "
                         << endl;
                } else
                    throw NotEnoughCoins();
            } else
                cout << "Vous avez atteint le nombre maximum de coins " << endl;
        } catch (const NotEnoughCoins &e) {
            cout << e.what() << endl; // erreur
        }
    }

    // si true on affiche la main si nom on affiche la premiere carte
    void printHand(ostream &os, bool ch) {
        if (!ch) {
            os << hand.top()->getName();
            return;
        }

        for (int i = 0; i < hand.getSizeHand(); ++i) {
            os << hand[i]->getName() << " ";
        }
    }

    // Insere des cartes à dans la main du joueur
    void addCardInHand(Card *card) { hand += card; }

    // afficher toute les informations du joueur
    friend ostream &operator<<(ostream &os, const Player &ply) {
        os << ply.name << " : " << ply.coins << " coins " << endl;

        for (int index = 0; index < ply.getNumChains(); index++) {
            os << ply.chains[index].getNameChain() << "\t";
            for (int j = 0; j < ply.chains[index].getSizeChain(); j++) {
                os << ply.chains[index].getCard(j)->getName()[0] << " ";
            }
            os << endl;
        }

        return os;
    }

    // pour avoir  la premier card de la main du joeur
    Card *showTopCard() { return hand.top(); }

    // pour jouer la premier carte
    Card *playFirstCard() { return hand.play(); }

    // pour avoir une carte à partir d'un nom
    Card *getCardByName(string name) { return hand.getCardByName(name); }

    // pour supprimer une carte à partir d'un nom
    void deletCardByName(string name) { hand.removeCardByName(name); }

    // ajouter une carte sur une chaine specifique à partir d'un index
    void addCardToChain(int index, Card *card) { chains[index - 1] += card; }

    // pour sauvegarder toutes les informations du joueur
    void savePlayer(string file, int index) {
        ofstream outFile(file, ios::app);
        if (outFile.is_open()) {
            outFile << index << endl;
            outFile << "Nom:" << name << endl;
            outFile << "Coins:" << getNumCoins() << endl;
            outFile << "NC:" << getNumChains() << endl;
            outFile << "C0:" << chains[0].getNameChain() << endl;
            outFile << "C0S:" << chains[0].getSizeChain() << endl;
            outFile << "C1:" << chains[1].getNameChain() << endl;
            outFile << "C1S:" << chains[1].getSizeChain() << endl;
            if (getNumChains() > 2) {
                outFile << "C2:" << chains[2].getNameChain() << endl;
                outFile << "C2S:" << chains[2].getSizeChain() << endl;
            }
            outFile << "SH:" << hand.getSizeHand() << endl;
            outFile << "Cartes:" << hand;
            outFile.close();
            cout << "Les infos du joueur " << name
                 << " a ete sauvegarde avec succes" << endl;
        } else
            cout << "Erreur de sauvegarde des infos du  joueur " << name
                 << endl;
    }

    // pour stocker les informations du player dans un string
    string getInfoPlayer(istream &file) {
        string info = "";
        string line;
        bool save = false;
        while (getline(file, line)) {
            if (line == to_string(position))
                save = true; // on commence à enregistrer si on arrive à l'index
            else if (line == to_string(position + 1))
                break; // on arrete à l'index suivant
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

    // pour creer les chaines à partir d'un fichier
    void makeChain(vector<string> &vec, int index) {
        Chain<Card *> newCh;
        if (split(vec[index], ':')[1] != "VIDE") {
            int length = stoi(split(vec[index + 1], ':')[1]);
            Card *card = createCard(split(vec[index], ':')[1]);
            for (int index = 0; index < length; index++)
                newCh += card;
        }
        chains.push_back(newCh);
    }

    // pour obtenir le nombre de cartes à la main
    int getSizePlayer() { return hand.getSizeHand(); }

    Chain<Card *> &getChain(int index) {
        if (index >= chains.size() || index <= 0)
            throw out_of_range("Chain index out of range!");

        return chains[index - 1];
    }
};
