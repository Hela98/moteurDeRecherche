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
#include "moteurDeRecherche.h"
using namespace std;

const string Index::fileSave="statistics.txt";
///************methode sauvegarderStat***************
void Index::sauvegarderStat (vector <pair< string,pair<string,int> > > tripletStat)
{
       ofstream ecrire(fileSave.c_str());
        if (ecrire)
        {
              for (unsigned int i(0);i<tripletStat.size();i++)
              ecrire<<tripletStat[i].first<<" "<<tripletStat[i].second.first<<" "<<tripletStat[i].second.second<<endl;
        }
}
///************methode rangerLesIndex****************
map<string ,vector<pair<string,int> > > Index::rangerLesIndex(vector <pair< string,pair<string,int> > > tripletStat)
{
      map<string ,vector<pair<string,int> > > IndexRangee;
      for( unsigned int i(0);i<tripletStat.size(); ++i)
      {
            IndexRangee[tripletStat[i].first].push_back(make_pair(tripletStat[i].second.first,tripletStat[i].second.second));
      }
        return IndexRangee;
}
///************methode indexer**************

vector <pair <string, pair<string , int > > >  Index::indexer (vector <pair <string,int> > stat ,string cheminFichier)
{
      vector <pair <string, pair<string , int > > > triplets;//  triplets le vector qui contient <mot,<nom de fichier,nbr d'occ> >
      for(unsigned int i(0);i<stat.size();i++)
      {
            triplets.push_back(make_pair(stat[i].first,make_pair(cheminFichier,stat[i].second)));
      }
      return triplets;
}
///************methode lecteurIndex**************
//**********class IndexVector*************
vector <pair <string,pair<string , int > > >  IndexVector:: lecteurIndex ()
{

    vector<pair<string, pair<string , int > > >savedIndex;
    vector <string> texteIndex;

    ifstream lire(Index::fileSave.c_str());
    if(lire)
      {
    istream_iterator<string> it(lire); //Un itérateur sur le fichier

    istream_iterator<string> fin;
           //Le signal de fin
    back_insert_iterator<vector<string> > it2(texteIndex);

     copy(it, fin, it2); //copier le contenu de fichier dans un vector

      int nbrOcc;
      unsigned int i(0);

     while(i<texteIndex.size()-2) //chaque ligne de fichier contient mot nomFichier nbrd'occ
     {
            istringstream iss;
            iss.str(texteIndex[i+2].c_str()); //convertir le nbr d'occ lu de fichier de string vers un entier
            iss>>nbrOcc;
           // savedIndex[texteIndex[i]].push_back (make_pair(texteIndex[i+1],nbrOcc));
              savedIndex.push_back (make_pair(texteIndex[i],make_pair(texteIndex[i+1],nbrOcc)));
             fichiersDejaIndexes.insert(texteIndex[i+1]);//on ajoute les fichiers qui ont déjà indexés dans un set
           i+=3;
     }
    }

    return savedIndex;//retour d'un vector contenant les statistiques lues à partir de fichier de sauvegarde
}

///************methode lecteurIndex**************
//**********class IndexMultimap*************
vector<pair<string, pair<string , int > > > IndexMultimap:: lecteurIndex ()
{
      vector<pair<string, pair<string , int > > > savedIndex;
       ifstream lire (fileSave.c_str());
      if(lire)
      {
            string ligne,mot,nomFichier;
            int nbrOcc;
            istringstream iss;
            while(getline(lire,ligne))
            {
                        iss.clear();
                        iss.str(ligne);
                        iss>> mot>>nomFichier>>nbrOcc;
                         savedIndex.push_back (make_pair(mot,make_pair(nomFichier,nbrOcc)));
                        fichiersDejaIndexes.insert(nomFichier);
                        mot.erase();
                        nomFichier.erase();
            }

}
      return savedIndex;
}





