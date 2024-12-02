#include <iostream>
#include <algorithm>
#include <random>
#include <fstream>
#include <string>
#include "Card.h"
#include "Chain.h"
#include "Deck.h"
#include "CardFactory.h"
#include "DiscardPile.h"
#include "Hand.h"
#include "Player.h"
#include "Table.h"
#include "TradeArea.h"
#define LOG(x)cout<<x<<endl;
int main(){
    //Game
    Game game;
    //Deck
    Deck deckOfCard;
    //DiscardPile
    DiscardPile<Card*> trash;
    //TradeArea
    TradeArea<Card*> trade;
    //Player1
    Player player1;
    //Player2
    Player player2;
    //Player (celui qui joue )
    Player player;
    //Player (celui qui attend son tour)
    Player playerW;
    //Table 
    Table<Card*> table(player1,player2,player,deckOfCard,trash,trade);
    player1.printHand(cout,true);
    player2.printHand(cout,true);
    //Pour savoir qui jouer 
    if(player.getName()==player1.getName())playerW=player2;
    else playerW=player1;
    ///Pour jouer
    while(deckOfCard.size()>0){
        //on veut faire une pause 
        int pause=game.pause(player.getName());
        if(pause==2){table.saveTable();break;}
        //update la table
        table.updateTable(player,player1,player2,trash,trade,deckOfCard);
        //on affiche la table
        LOG(table)
        //Cartes
        player.printHand(cout,true);
        //joue et pioche et fini sont tour 
        table.playTurn(player,playerW,deckOfCard);//reste à developper ca 
        //on continue à jouer
        cout<<"Il reste dans le desk que "<<deckOfCard.size()<<" cartes "<<endl;
        //on swap
        Player stockPlayer=playerW;
        playerW=player;
        player=stockPlayer;
    }
    //On recherche le gagnant
    //table.showWinner(player,playerW);
}

