class Deck;
class Card;
class CardFactory {
  private:
    Deck cards;
  public:
    CardFactory(){
      Card* card[]={new Blue(),new Chili(),
                   new Stink(),new Green(),
                   new Soy(),new Black(),
                   new Red(),new Garden()};
      for(int i=0;i<8;i++){
        for(int j=0;j<card[i]->getTotalOfCards();j++){
              cards.push_back(card[i]);
        }
    }  
    }
    static CardFactory* getFactory(){return new CardFactory();} // Renvoie l'unique instance de CardFactory
    Deck getDeck(){
      random_device rd;
      mt19937 gen(rd());
      shuffle(cards.begin(),cards.end(),gen);
      return cards;
    }                // Renvoie un Deck contenant toutes les cartes, mélangées
    CardFactory(const CardFactory&) = delete; // Interdire la copie
    CardFactory& operator=(const CardFactory&) = delete; // Interdire l'affectation
    
};

