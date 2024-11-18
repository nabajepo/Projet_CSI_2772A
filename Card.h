#include <iostream>
using namespace std;
class Card {
    protected:
           int totalCards; //nbre of cards
           int nbre_of_cards_for_oneCoin;
           int nbre_of_cards_for_twoCoins;
           int nbre_of_cards_for_threeCoins;
           int nbre_of_cards_for_fourCoins;
    public:
          Card(int total, int cardsOneCoin, int cardsTwoCoins, 
          int cardsThreeCoins, int cardsFourCoins): 
           totalCards(total), nbre_of_cards_for_oneCoin(cardsOneCoin),
           nbre_of_cards_for_twoCoins(cardsTwoCoins), nbre_of_cards_for_threeCoins(cardsThreeCoins), 
           nbre_of_cards_for_fourCoins(cardsFourCoins) {}//constructor to initialize each card
           virtual int getCardsPerCoin(int) = 0;
           virtual string getName() = 0;//to get name 
           virtual void print(ostream&) = 0;
           virtual ~Card() = default;//The destructor
           
};
class Blue : public Card {
    public :
           Blue():Card(20,4,6,8,10){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Blue";}
           void print(ostream& os) override {os << getName().at(0)<<" ";}
};
class Chili : public Card {
    public :
           Chili():Card(18,3,6,8,9){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Chili";}
           void print(ostream& os) override {os << getName().at(0)<< " ";}
};
class Stink : public Card {
    public :
           Stink():Card(16,3,5,7,8){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Stink";}
           void print(ostream& os) override {os << getName().at(0)<< " " ;}
};
class Green : public Card {
    public :
           Green():Card(14,3,5,6,7){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Green";}
           void print(ostream& os) override {os << getName().at(0) << " ";}
};
class Soy : public Card {
    public :
           Soy():Card(12,2,4,6,7){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Soy";}
           void print(ostream& os) override {os << getName().at(0)<< " ";}
};
class Black : public Card {
    public :
           Black():Card(10,2,4,5,6){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Black";}
           void print(ostream& os) override {os << getName().at(0)<< " ";}
};
class Red : public Card {
    public :
           Red():Card(8,2,3,4,5){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 1) return nbre_of_cards_for_oneCoin;
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 if (coins == 4) return nbre_of_cards_for_fourCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Red";}
           void print(ostream& os) override {os << getName().at(0)<< " ";}
};
class Garden : public Card {
    public :
           Garden():Card(6,0,2,3,0){}
           int getCardsPerCoin(int coins) override{
                 if (coins == 2) return nbre_of_cards_for_twoCoins;
                 if (coins == 3) return nbre_of_cards_for_threeCoins;
                 return 0;//we send zero for any other values
           }
           string getName() override {return "Garden";}
           void print(ostream& os) override {os << getName().at(0) << " ";}
};
