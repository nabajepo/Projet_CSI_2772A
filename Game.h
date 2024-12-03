#include <filesystem>
#include <fstream>
#include <iostream>
using namespace std;

class Game {
  public:
    Game() {}

    // pour faire une pause
    int showMenu(string nameP) {
        int choice;
        cout << nameP << " voulez-vous continuer ? " << endl
             << "1.Oui " << endl
             << "2.Non" << endl
             << "Entrez votre choix : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez un nombre valide " << endl;
            return showMenu(nameP);
        } else
            return choice;
    }

    // pour le choix du joueur à propos des cartes
    int choicePlayer(string nameP) {
        int choice;
        cout << nameP << "que voulez-vous faire ? " << endl
             << " 1.Trade la premiere carte ou plusieurs cartes " << endl
             << " 2.Chainer la premiere carte de la main " << endl
             << "3.Jeter la premiere  carte de la main" << endl
             << " 4.Vendre les cartes d'une chaine specifique " << endl
             << " 5. Acheter une troisieme chaine  " << endl
             << " 6.Jeter une  chaine specifique " << endl
             << " Entrez votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4 &&
            choice != 5 && choice != 6) {
            cout << "SVP " << nameP << " entrez un choix valid " << endl;
            return choicePlayer(nameP);
        } else
            return choice;
    }

    // pour obtenir un index d'une chaine valide
    int getChainIndex(Player &player) {
        int choice;
        cout << "--------------------CHAINPART--------------------" << endl;
        cout << player;
        player.printHand(cout, true);
        cout << "--------------------ENDCHAINPART--------------------" << endl;
        cout << player.getName() << " vous avez " << player.getNumChains()
             << endl;
        cout << " Entrez l'index de la chaine que vous voulez ? : ";
        cin >> choice;
        if (choice < 0 && choice >= player.getNumChains()) {
            cout << "SVP entre un index valid " << endl;
            return getChainIndex(player);
        } else
            return choice;
    }

    // pour rompre une action
    int getChoice() {
        int choice;
        cout << "Voulez-vous " << endl
             << "1.Essayez encore " << endl
             << "2.Rompre l'action " << endl
             << "Entrez votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez un choix valide ";
            return getChoice();
        } else
            return choice;
    }

    // pour avoir un choix d'un discard
    int getDiscardChoice(string diff) {
        int choice;
        cout << "Voulez-vous " << endl
             << "1." << diff << endl
             << "2.Discard une chaine  " << endl
             << "Entrez votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez un choix valide ";
            return getDiscardChoice(diff);
        } else
            return choice;
    }

    // pour obtenir le nombre de carte à trade
    int getTradeLength(Player &player) {
        int choice;
        cout << "Combien de carte voulez-vous trade? : ";
        cin >> choice;
        if (choice > player.getSizePlayer() && choice <= 0) {
            cout << "SVP entrez un nombre valide >0 et <"
                 << player.getSizePlayer() << endl;
            return getTradeLength(player);
        } else
            return choice;
    }

    // pour obtenir le nom des cartes qu'on veut trade
    string getCardPlayer(Player &player) {
        string choice;
        cout << "Entrez le nom de la carte que vous vous voulez : ";
        cin >> choice;
        if (player.getCardByName(choice) == nullptr) {
            cout << "SVP entre une carte qui se trouve dans votre main "
                 << endl;
            return getCardPlayer(player);
        } else
            return choice;
    }

    // pour pour accepter un trade
    int getTradeAggreement() {
        int choice;
        cout << "Voulez-vous accepter le trade  ? : " << endl
             << "1.oui" << endl
             << "2.non" << endl
             << "Entrez-votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez une reponse valide  " << endl;
            return getTradeAggreement();
        } else
            return choice;
    }

    // pour les cartes qu'on doit jouer
    int getPlacement() {
        int choice;
        cout << "Que voulez vous faire de la carte ? : " << endl
             << "1.Ajouter la carte au trade" << endl
             << "2.jette la carte " << endl
             << "3.jette une chaine specifique " << endl
             << "Entrez-votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3) {
            cout << "SVP entrez une reponse valide  " << endl;
            return getPlacement();
        } else
            return choice;
    }

    // pour une carte qu'on doit jouer
    int getPlacementD() {
        int choice;
        cout << "Que voulez vous faire de la carte ? : " << endl
             << "1.Ajouter la carte au chain " << endl
             << "2.jette la carte " << endl
             << "Entrez-votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez une reponse valide  " << endl;
            return getPlacementD();
        } else
            return choice;
    }

    // pour lr pioche
    int getPiocheChoice() {
        int choice;
        cout << "Que voulez vous faire ? : " << endl
             << "1.Recuperer toute les cartes piocher" << endl
             << "2.Supprimer toute les cartes piocher " << endl
             << "3.Recuperer une carte d'un trade " << endl
             << "4.Trade toutes les cartes du trade" << endl
             << "Entrez-votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2 & choice != 3) {
            cout << "SVP entrez une reponse valide  " << endl;
            return getPiocheChoice();
        } else
            return choice;
    }

    // pour obtenir le nom des cartes qu'on veut tdu trade
    string getCardFromTrade() {
        string choice;
        cout << "Entrez le nom de la carte que vous vous voulez : ";
        cin >> choice;
        return choice;
    }

    // pour une carte restant du trade
    int getPiocheR() {
        int choice;
        cout << "Que voulez vous faire de la carte ? : " << endl
             << "1.Trade la carte qui reste  " << endl
             << "2.jette la carte " << endl
             << "Entrez-votre choix ici : ";
        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "SVP entrez une reponse valide  " << endl;
            return getPlacementD();
        } else
            return choice;
    }

    // pour avoir le nom d'un joueur
    string inputPlayerName() {
        string playerName;
        cout << "Entrez le nom du joueur: ";
        getline(cin >> ws, playerName);
        if (playerName.empty()) {
            cout << "SVP entrez un nom valide " << endl;
            return inputPlayerName();
        } else
            return playerName;
    }
};