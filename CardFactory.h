class Deck;
class Card;
class CardFactory {
  private:
    Card** card;
    Deck cards;
  public:
    CardFactory(){
        //interface
        card=new Card*[8];
        card[0] = new Blue();
        card[1] = new Chili();
        card[2] = new Stink();
        card[3] = new Green();
        card[4] = new Soy();
        card[5] = new Black();
        card[6] = new Red();
        card[7] = new Garden();
      //insertion des cartes   
        for(int i=0;i<8;i++)
           for(int j=0;j<card[i]->getTotalOfCards();j++)
              cards.push_back(card[i]);
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
    //creer une classe à l'aide d'un nom 
    Card* createCard(string nameCard){
        for(int index=0;index<8;index++)
            if(card[index]->getName()==nameCard) return card[index];
        return nullptr;    
    }
    
};

