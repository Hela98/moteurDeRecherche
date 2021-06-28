#include "moteurDeRecherche.h"
#include <iostream>
#include<string>
#include <sstream>
#include <vector>
#include <fstream>
#include<cstdlib>
#include <utility>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const string Bibliotheque::files="repertoire.txt";//fichier de persistence des fichiers indexés
///*************class Bibliotheque********
 Bibliotheque::Bibliotheque(){

      ifstream fichier(files.c_str());
            string mot;
                  while (fichier >>mot)
                  {
                        fichiers.push_back(mot);         //stocker le repertoire dans un vector
                  }
      }
//************methode ajouterFichiers*********
bool Bibliotheque::ajouterFichiers(string cheminFichier)
{
      bool existe;
      if(find(fichiers.begin(), fichiers.end(), cheminFichier)==fichiers.end()){
                  fichiers.push_back(cheminFichier);

                  existe=false;
                   saveDirectory();
}
else
{
      existe=true;
      cout<<"the file already exists"<<endl;
}
   return existe;
}

//******************************
std::ostream& operator<<(std::ostream& flux,Bibliotheque const& bib)
{
      bib.affichageFichiers(flux);
      return flux;
}
//**********methode affichageFichiers*********
void  Bibliotheque::affichageFichiers(std::ostream& flux)const{
      if(!fichiers.empty())
      {
             for(unsigned int i(0);i<fichiers.size();++i)
           {
            flux<<fichiers[i]<<endl;
             }
      }
      else {
            cout<<"no file found"<<endl;
      }


}
//*************methode saveDirectory*********
void Bibliotheque::saveDirectory()
{
      ofstream ecrire(files.c_str());

        if (ecrire)
        {
              for (unsigned int i(0);i<fichiers.size();i++)
              ecrire<<fichiers[i]<<endl;
        }
}

//*******************supprimerFichier********
bool Bibliotheque::supprimerFichier(string cheminFichier)
{     bool existe;
      vector<string>::iterator it;
      it=find(fichiers.begin(), fichiers.end(), cheminFichier);
     if(it!=fichiers.end())
     {
           fichiers.erase(it);
           existe=true;
           saveDirectory();
     }
     else {
      cout<<"file does not exist"<<endl;
      existe=false;
     }
     return existe;
}
