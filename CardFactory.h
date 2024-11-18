class Deck;
class CardFactory {
  private:
    Deck allCards;
    static CardFactory* instance;
  public:
    CardFactory();  
    static CardFactory* getFactory(); // Renvoie l'unique instance de CardFactory
    Deck getDeck();                   // Renvoie un Deck contenant toutes les cartes, mélangées
    CardFactory(const CardFactory&) = delete; // Interdire la copie
    CardFactory& operator=(const CardFactory&) = delete; // Interdire l'affectation
    
};

