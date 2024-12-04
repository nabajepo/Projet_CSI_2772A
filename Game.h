#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Table.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

class Game {
  public:
    Game() {}

    // pour faire une pause
    bool shouldPause() {
        int choice;
        cout << "[Pause] Voulez-vous arreter et sauvegarder le jeu (game.txt)? "
             << endl
             << "1. Oui " << endl
             << "2. Non" << endl
             << "Entrez votre choix : ";
        cin >> choice;

        return choice == 1;
    }

    // pour le choix du joueur à propos des cartes
    int choicePlayer() {
        int choice;
        cout << "Que voulez-vous faire ? " << endl
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
            cout << "SVP entrez un choix valid " << endl;
            return choicePlayer();
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

    // pour obtenir le nom des cartes qu'on veut tdu trade
    string getCardFromTrade() {
        string choice;
        cout << "Entrez le nom de la carte que vous vous voulez : ";
        cin >> choice;
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

    // Si on a deja un jeu en attente
    bool shouldLoadGame() {
        int choice;
        cout << "[Sauvegarde] Un jeu est deja enregistrer. Voulez-vous : "
             << endl
             << "1. Continue le meme jeu " << endl
             << "2. Commencez un nouveau jeu " << endl
             << "Entrez votre choix : ";
        cin >> choice;

        return choice == 1;
    }

    Table *loadGame() {
        ifstream file(Table::CHECKPOINTFILENAME);

        if (file.is_open()) {       // si le fichier existe
            if (shouldLoadGame()) { // on veut continue le jeu
                file.seekg(0, ios::beg);
                return new Table(file, new CardFactory());
            }
            file.close();
        }

        // Input player names or load game from file
        string playerOneName, playerTwoName;
        playerOneName = inputPlayerName();
        playerTwoName = inputPlayerName();
        return new Table(playerOneName, playerTwoName);
    }
};

#endif