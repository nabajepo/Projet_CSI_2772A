#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class Card;
class CardFactory;
class Deck : public vector<Card *> {
  public:
    // Constructeur
    Deck() {}
    // Constructeur qui accepte un istream et un CardFactory pour construire un
    // deck à partir d'un fichier
    Deck(istream &file, const CardFactory *factory) {
        vector<string> cards =
            split(split(split(getInfoDeck(file), '.')[1], ':')[1], '|');
        for (string card : cards)
            this->push_back(
                createCard(card)); // on insere le card dans le trade
    }

    // Méthode pour tirer et supprimer la carte supérieure du deck
    Card *draw() {
        Card *topCard = this->back();
        this->pop_back();
        return topCard;
    }

    // Opérateur d'insertion pour afficher le deck dans un std::ostream
    friend ostream &operator<<(ostream &os, const Deck &deck) {
        for (Card *card : deck)           // Suppose que Deck est itérable
            os << card->getName() << "|"; // Écriture directe dans le flux

        return os;
    }
    // pour sauvegarder le deck
    void saveDeck(string file, int index) {
        ofstream outFile(file, ios::app);
        if (outFile.is_open()) {
            outFile << index << endl;
            outFile << "Taille:" << this->size() << endl;
            outFile << "Cartes:" << *this;
            outFile.close();
            cout << "Le deck a ete sauvegarde avec succes " << endl;
        } else
            cout << "Erreur de sauvegarde du deck " << index << endl;
    }
    
    // pour stocker les informations du deck dans un string
    string getInfoDeck(istream &file) {
        string info = "";
        string line;
        bool save = false;
        while (getline(file, line)) {
            if (line == "6")
                save = true; // on commence à enregistrer si on arrive à l'index
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
