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

///*************Ordonnanceur***********

///************* convertirMotCles*********
vector <string> Ordonnanceur::convertirMotCles (string requeteRecherche)
{
 vector <string> motCles;
    string mot;

 istringstream extraire(requeteRecherche);

 while(extraire>>mot)
 {
 motCles.push_back(mot);
 }
 return motCles;
}

///*************Ordonnanceur***********

///************* trier****************
vector<string> Ordonnanceur:: trier (map<string,int> resultatRechercher)
{

      vector<string> fichiersTries;
      vector<int> scores;
      for(map<string, int>::const_iterator it=resultatRechercher.begin();it!=resultatRechercher.end();++it)
      {
            scores.push_back(it->second);
      }
       sort(scores.begin(), scores.end(), greater<int>());//trier  les scores
       scores.erase(std::unique(scores.begin(), scores.end()), scores.end());//éliminer les scores doubles
       for(unsigned int i(0);i< scores.size();++i)
       {
       for(map<string, int>::const_iterator it=resultatRechercher.begin();it!=resultatRechercher.end();++it )
       {
             if(it->second==scores[i])
             {
                   fichiersTries.push_back(it->first);//ajout des fichiers triés selon le score dans le vector fichiersTries;
                }
             }
       }
  return fichiersTries;
}

///*************OrdonnanceurNbrOcc************

///************afficherResultat*********
void OrdonnanceurNbrOcc::afficherResultat(vector <string>fichiersTries,unsigned int nbrResultat)
{
       if(fichiersTries.empty())
      {
            cout<<"no file found"<<endl;
      }
      else{
      if(nbrResultat>=fichiersTries.size())
      {
      for_each(fichiersTries.begin(), fichiersTries.end(), Afficher());   //Et on affiche les éléments
      }
      else {
            for_each(fichiersTries.begin(), fichiersTries.begin()+nbrResultat, Afficher());
      }
      }

}
///*************pour l'affichage des resultats*********
 void Afficher::operator()(string nomFichier) const
    {
        cout << nomFichier << endl;
    }

///*************OrdonnanceurNbrOcc************

///************rechercher*********
map<string,int > OrdonnanceurNbrOcc::rechercher(vector<string> motCles , map<string, vector<pair<string,int> > > resultatFinalIndex )
{
    map<string, int>  resultatRecherche;//map , clé :fichier et valeur: score de fichier
    for(unsigned int i(0);i<motCles.size();++i)
    {
          if(resultatFinalIndex.find(motCles[i])!=resultatFinalIndex.end())//si le mot clé existe dans le map des resultas de l'index final
          {
                for (unsigned int j(0);j<resultatFinalIndex[motCles[i]].size();++j)//parcour de vector<pair<string,int> > clé de map  resultatFinalIndex
                {
                      resultatRecherche[resultatFinalIndex[motCles[i]][j].first]+=resultatFinalIndex[motCles[i]][j].second;//ajout de nbr d'occ au valeur
                }
          }
    }
    return resultatRecherche;
}

///*************OrdonnanceurBinaire************

///************afficherResultat*********
void OrdonnanceurBinaire::afficherResultat(vector <string>fichiersTries,unsigned int nbrResultat)
{
       if(fichiersTries.empty())
      {
            cout<<"no file found"<<endl;
      }
      else{
      if(nbrResultat>=fichiersTries.size())

      {
            for(unsigned int i(0);i<fichiersTries.size();++i)
      {
            cout<<fichiersTries[i]<<endl;
      }
      }
      else{
            for(unsigned int i(0);i<nbrResultat;++i)
      {
            cout<<fichiersTries[i]<<endl;
      }
      }
      }

}
///*************OrdonnanceurBinaire************
///*************rechercher**************
map<string,int > OrdonnanceurBinaire::rechercher(vector<string> motCles , map<string, vector<pair<string,int> > > resultatFinalIndex )
{

    map<string, int>  resultatRecherche;//map , clé :fichier et valeur: score de fichier
    for(unsigned int i(0);i<motCles.size();++i)
    {
          if(resultatFinalIndex.find(motCles[i])!=resultatFinalIndex.end())
          {
                for (unsigned int j(0);j<resultatFinalIndex[motCles[i]].size();++j)
                {
                      ++resultatRecherche[resultatFinalIndex[motCles[i]][j].first];
                }
          }
    }
    return resultatRecherche;
}





