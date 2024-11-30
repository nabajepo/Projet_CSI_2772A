#include <iostream>
#include <vector>
using namespace std;
class Card;
template<class T>
class DiscardPile : public vector<T> {
public:
    // Constructeur
    DiscardPile(){}
    // Constructeur qui accepte un istream et un CardFactory pour construire une pile de cartes à partir d'un fichier
    DiscardPile(istream& , const CardFactory*);

    // Ajoute une carte à la pile de déchet
    DiscardPile& operator+=(T card){
        this->push_back(card);
        return *this;
    }

    // Renvoie et supprime la carte supérieure de la pile
    T pickUp(){
        if(this.size()>0){
            T topC=this->back();
            this->pop_back();
            return topC;
        }
        else{
             cout <<"Le  discardPile est vide "<<endl;
             return nullptr;
        }
        
    }

    // Renvoie mais ne supprime pas la carte supérieure de la pile
    T top() const{
        if(this->size()>0)return this->back();
        else{
            cout <<"Le  discardPile est vide "<<endl;
            return nullptr;
        }
    }     

    // Insère toutes les cartes de la pile dans un ostream
    void print (ostream& os){
        if (this->size()>0){
            os<<"|";
            for(T card:*this)
            os<<card->getName()<<"|";
            os<<endl;
        }
        else os<<"#Le discardPile est vide#"<<endl;
        
    }
    // Insère seulement la carte supérieure dans un ostream
    friend ostream& operator<<(ostream& os, const DiscardPile<T>& dsc){
        if(dsc.size()>0)os <<"|"<<dsc.top()->getName()<<"|"<<endl; 
        else os<<"La pile est vide "<<endl;
        return os;
    }
    //pour afficher toutes les cartes de la main par ligne
    void getDiscard(ostream& os){
         if(this->size()>0){
            for (Card* card :*this){// Suppose que Deck est itérable
                 os <<card->getName() <<endl; // Écriture directe dans le flux
            }
          }
          else os<<"#Le discard est vide#"<<endl;
    }
    //pour sauvegarder le deck
    void saveDiscard(string file,int index){
         ofstream outFile(file,ios::app);
         if(outFile.is_open()){
             outFile<<index<<endl;
             outFile<<"Taille:"<<this->size()<<endl;
             getDiscard(outFile);
             outFile.close();
             cout<<"Le discard a ete sauvegarde avec succes "<<endl;
         }
         else cout<<"Erreur de sauvegarde du discard "<<endl;   
    }
};


