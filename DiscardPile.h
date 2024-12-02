#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
class Card;
template<class T>
class DiscardPile : public vector<T> {
public:
    // Constructeur
    DiscardPile(){}
    // Constructeur qui accepte un istream et un CardFactory pour construire une pile de cartes à partir d'un fichier
    DiscardPile(istream& file, const CardFactory* factory){
          vector<string> ds=split(getInfoDiscard(file),'.');
          vector<string> taille=split(ds[0],':');
          int tailleD=stoi(taille[1]);
          if(tailleD!=0){
              vector<string> cards=split(split(ds[1],':')[1],'|');
              for(string card:cards)
                 this->push_back(createCard(card));//on insere les cards dans le discard
          }
         
    }
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
    //pour sauvegarder le deck
    void saveDiscard(string file,int index){
         ofstream outFile(file,ios::app);
         if(outFile.is_open()){
             outFile<<index<<endl;
             outFile<<"Taille:"<<this->size()<<endl;
             outFile<<"Cartes:";
             print(outFile);
             outFile.close();
             cout<<"Le discard a ete sauvegarde avec succes "<<endl;
         }
         else cout<<"Erreur de sauvegarde du discard "<<endl;   
    }
    //pour stocker les informations du discard dans un string
    string getInfoDiscard(istream& file){
        string info="";
        string line;
        bool save=false;
        while(getline(file,line)){
            if(line=="4")save=true;//on commence à enregistrer si on arrive à l'index
            else if(line=="5")break;//on stop quand on arrive à l'index 5
            else if(save)info=info+line+"."; 
        }
        return info;
    }
     //pour split un string 
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        istringstream stream(str);
        string token;
        while (getline(stream, token, delimiter)) {
               tokens.push_back(token);
        }
        return tokens;
    }
     //creer une classe à l'aide d'un nom 
    Card* createCard(string nameCard){
        Card* card[]={new Blue(),new Chili(),
                   new Stink(),new Green(),
                   new Soy(),new Black(),
                   new Red(),new Garden()};
        for(int index=0;index<8;index++)
            if(card[index]->getName()==nameCard) return card[index];
        return nullptr;    
    }
};


