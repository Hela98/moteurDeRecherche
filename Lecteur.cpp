
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

///************lecteur1***************
vector<string> Lecteur1::extraireMots(string cheminFichier)
{
      vector <string> texte;
    ifstream fichier(cheminFichier.c_str());
    istream_iterator<string> it(fichier); //Un itérateur sur le fichier
    istream_iterator<string> end;         //Le signal de fin

    while(it != end)   //Tant qu'on a pas atteint la fin
    {
           texte.push_back(*it);
            ++it;                 // on avance
    }
                  return texte;
}
///************lecteur2***************
vector<string> Lecteur2::extraireMots(string cheminFichier)
{
      vector <string> texte;
      ifstream fichier(cheminFichier.c_str());
            string mot;
                  while (fichier >>mot)
                  {
                        texte.push_back(mot);         //lire mot par mot à partir du fichier
                  }
                  return texte;
}
///************lecteur3***************
vector<string> Lecteur3::extraireMots(string cheminFichier)
{
      vector <string> texte;
    ifstream fichier(cheminFichier.c_str());
    istream_iterator<string> it(fichier); //Un itérateur sur le fichier
    istream_iterator<string> fin;         //Le signal de fin
     back_insert_iterator<vector<string> > it2(texte);

      copy(it, fin, it2);
                  return texte;
}

