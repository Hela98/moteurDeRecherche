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
#include <dirent.h>
#include <sys/types.h>
#include<string.h>
#include "moteurDeRecherche.h"
using namespace std;
///************constructeur**********
 MoteurDeRecherche::MoteurDeRecherche(Analyseur* a,Index* i,Ordonnanceur* o,unsigned int n)
 {
   monAnalyseur=a;
   monIndex=i;
   monOrd=o;
   nbrMaxResultats=n;
 }


///**************indexerUnFichier*************
 vector<pair<string,int> > MoteurDeRecherche::indexerUnFichier(string cheminFichier, vector<string> texte)
{
    bool existe;
    existe=bib.ajouterFichiers(cheminFichier);//si le fichier n'existe pas elle va etre ajouté

    vector <pair <string, pair<string , int > > >  resultats;//va contenir les anciens index enregistrés et le nouveau index
    vector<pair<string, pair<string , int > > >  savedIndex=monIndex->lecteurIndex();//les index enregistrés dans le fichier de persistence

    if(existe==true)//si le fichier existe déjà dans la bibliothéque càd qu'il est indexé déjà alors on va le réindexer et mettre à jour l'indexation, et sauvegarder l'index
    {
        cout<<"file reindexing..."<<endl;
        vector<pair<string, pair<string , int > > > ::iterator it =savedIndex.begin();
         while(it!=savedIndex.end())
         {
               if((*it).second.first==cheminFichier)    //suppression de l'ancien index
               {
                     it=savedIndex.erase(it);
               }
               else{
                  ++it;
               }
         }

    }
    else{
         cout<<"file indexing..."<<endl;
    }
        vector<pair<string,int> > statistics =monAnalyseur->analyser(texte);
        vector <pair <string, pair<string , int > > > resultatsIndex=monIndex->indexer( statistics ,cheminFichier);//nouveau index de fichier
         for (unsigned int j(0);j<resultatsIndex.size();j++)
             {
                   resultats.push_back(resultatsIndex[j]);//ajout de nouveaux index dans le vector resultats

             }
              for (unsigned int i(0);i<savedIndex.size();++i)
       {
             resultats.push_back(savedIndex[i]);//les anciens index
       }

   monIndex->sauvegarderStat(resultats);//sauvegarde les resultats de l'index aprés la mise à jour dans le fichier de persistence
   return statistics;
    }

///************indexerDesFichiers********
map<string ,vector<pair<string,int> > > MoteurDeRecherche::indexerDesFichiers(map<string,vector<string> > filesContent)
{
    bool existe;

    vector <pair <string, pair<string , int > > >  resultats;//va contenir les anciens index enregistrés et les nouveaux index
    vector<pair<string, pair<string , int > > >  savedIndex=monIndex->lecteurIndex();//les index enregistrés dans le fichier de persistence
     for(map<string, vector<string> >::const_iterator it=filesContent.begin();it!=filesContent.end();++it)
     {
           existe=bib.ajouterFichiers(it->first);//si le fichier n'existe pas elle va etre ajouté
            if(existe==true)//si le fichier existe déjà dans la bibliothéque càd qu'il est indexé déjà alors on va le réindexer et mettre à jour l'indexation, et sauvegarder l'index
         {
             cout<<"file reindexing..."<<endl;
             vector<pair<string, pair<string , int > > > ::iterator it1 =savedIndex.begin();
             while(it1!=savedIndex.end())
             {
               if((*it1).second.first==it->first)    //suppression de l'ancien index
               {
                     it1=savedIndex.erase(it1);
               }
               else{
                  ++it1;
               }
              }
         }

             vector<pair<string,int> > statistics =monAnalyseur->analyser(it->second);
             vector <pair <string, pair<string , int > > > resultatsIndex=monIndex->indexer( statistics ,it->first);
             for (unsigned int j(0);j<resultatsIndex.size();j++)
             {
                   resultats.push_back(resultatsIndex[j]);

             }

    }
    map<string ,vector<pair<string,int> > > Rangee=monIndex->rangerLesIndex(resultats);

   for (unsigned int i(0);i<savedIndex.size();++i)
       {
             resultats.push_back(savedIndex[i]);
       }

      monIndex->sauvegarderStat(resultats);//sauvegarde des resultats de l'index dans le fichier de persistence
      return Rangee;
}
///************ filesDirectory *************
vector<string>  MoteurDeRecherche::filesDirectory (std::string pathDirectory)
{
       vector<string> fichiersAIndexer;

      struct dirent *entry;
      DIR *dir = opendir(pathDirectory.c_str());

      if (dir == NULL) {
      cout<<"can't open directory"<<endl;
          }
      while ((entry = readdir(dir)) != NULL)
       {
         string path(entry->d_name);

         if(path.size()>=5 && strcmp((path.substr(path.size()-4)).c_str(),".txt")==0)
            {
                  cout<<path<<endl;
                  fichiersAIndexer.push_back(pathDirectory+'\\'+path);

             }
       path.clear();
   }
   closedir(dir);

     return fichiersAIndexer;
}


///**************supprimerIndex********
void MoteurDeRecherche::supprimerIndex(string cheminFichier)
{
      bool existe;
      existe=bib.supprimerFichier(cheminFichier);
   vector<pair<string, pair<string , int > > >  savedIndex=monIndex->lecteurIndex();
   vector<pair<string, pair<string , int > > > ::iterator it =savedIndex.begin();
   if(existe==true)

         {
               while(it!=savedIndex.end())
         {
               if((*it).second.first==cheminFichier)    //suppression de l'ancien index
               {
                     it=savedIndex.erase(it);
               }
               else{
                  ++it;
               }
         }
         }
         monIndex->sauvegarderStat(savedIndex);

}
///********************affcherToutLesIndex*********
void MoteurDeRecherche::afficherToutLesIndex()
{
   vector<pair<string, pair<string , int > > >  savedIndex=monIndex->lecteurIndex();
   map<string ,vector<pair<string,int> > > Rangee=monIndex->rangerLesIndex(savedIndex);
   for(map<string, vector<pair<string , int > > >::const_iterator it=Rangee.begin();it!=Rangee.end();++it)
      {

            cout<<'<'<<it->first<<';';
            for(unsigned int k(0) ;k<Rangee[it->first].size();k++){

                        cout<< '<'<<Rangee[it->first][k].first<<";"<<Rangee[it->first][k].second<<'>';
            }
            cout <<'>'<<endl;

      }

}
///*************recherche***********
void MoteurDeRecherche::rechercher(string motsRecherches)
{
        vector<pair<string, pair<string , int > > >  savedIndex=monIndex->lecteurIndex();//les indexes lues de fichier de persistance
        vector<string> requeteRecherche=monOrd->convertirMotCles(motsRecherches);
       map<string ,vector<pair<string,int> > > Rangee=monIndex->rangerLesIndex(savedIndex);//les resultats  de l'index transformés en map le clé un mot et la valeur :tous les fichiers dans lequels ce mot existe et le nbr d'occ dans chaque fichier
       //la methode rangerLesIndex pour faciliter le role de l'ordonnaceur
        map<string,int> fichiersETscores=monOrd->rechercher(requeteRecherche ,Rangee );
        vector <string> ResultatsFinals=monOrd->trier (fichiersETscores);
        monOrd->afficherResultat(ResultatsFinals,nbrMaxResultats);// c'est le resultat de recherche
}

///********************methode configuration**********
void MoteurDeRecherche::configurer()
{
    char choix1,choix2;
     unsigned int nbr=0;
      cout<< "To change Analyseur type 1 "<<endl;
      cout<< "To change Index type 2"<<endl;
      cout<< "To change Ordonnanceur type 3"<<endl;
      cout<<"To change the maximum number of search results type 4  "<<endl;
      cin>>choix1;
        switch(choix1)
         {
        case '1':
              {
                   cout<<"choose Analyseur"<<endl;
                   fflush(stdin);
                   cout<<"to choose AnalyseurVector type 1"<<endl;
                   fflush(stdin);
                   cout<<"to choose AnalyseurMap type 2"<<endl;
                   fflush(stdin);
                  cin>>choix2;
                  switch(choix2)
                  {
                  case '1':
                        {
                              delete monAnalyseur;
                              monAnalyseur=0;
                              monAnalyseur= new AnalyseurVector;
                              //AnalyseurVector newAnalyseur;
                             // configuerAnalyseur(&newAnalyseur);
                              break;
                        }
                  case '2':
                        {
                              delete monAnalyseur;
                              monAnalyseur=0;
                              monAnalyseur= new AnalyseurMap;
                              //AnalyseurMap newAnalyseur;
                             // configuerAnalyseur(&newAnalyseur);
                              break;
                        }
                         default:
                        {

                      cout<<"invalid choice"<<endl;
                      fflush(stdin);
                               }
                  }

         break;
              }

   case '2':
              {

                   cout<<"choose Index"<<endl;
                   fflush(stdin);
                   cout<<"to choose IndexVector type 1"<<endl;
                   fflush(stdin);
                   cout<<"to choose IndexMultimap type 2"<<endl;
                   fflush(stdin);
                  cin>>choix2;
                  switch(choix2)
                  {
                  case '1':
                        {
                              delete monIndex;
                              monIndex=0;
                              monIndex=new IndexVector;
                              //IndexVector newIndex;
                              //configurerIndex(&newIndex);
                              break;
                        }
                  case '2':
                        {
                              delete monIndex;
                              monIndex=0;
                              monIndex=new IndexMultimap;
                              break;
                        }
                         default:
                        {

                      cout<<"invalid choice"<<endl;
                      fflush(stdin);
                               }
                  }
                  break;
              }


case '3':
             {
                   cout<<"choose Ordonnanceur"<<endl;
                   fflush(stdin);
                   cout<<"to choose OrdonnanceurBinaire type 1"<<endl;
                   fflush(stdin);
                   cout<<"to choose  OrdonnaceurNbrOcc type 2"<<endl;
                   fflush(stdin);
                  cin>>choix2;
                  switch(choix2)
                  {
                  case '1':
                        {      delete monOrd;
                               monOrd=0;
                               monOrd=new OrdonnanceurBinaire;
                              //OrdonnanceurBinaire newOrdonnanceur;
                              //configurerOrdonnanceur(&newOrdonnanceur);
                              break;
                        }
                  case '2':
                        {
                              delete monOrd;
                              monOrd=0;
                              monOrd=new OrdonnanceurNbrOcc;
                             // OrdonnanceurNbrOcc newOrdonnanceur;
                              //configurerOrdonnanceur(&newOrdonnanceur);
                              break;
                        }
                         default:
                        {

                      cout<<"invalid choice"<<endl;
                      fflush(stdin);
                               }
                  }
                  break;
             }
  case '4':
            {
                  while(nbr<=0)
                  {
                  cout<<"enter the maximum number of search results"<<endl;
                  cin>> nbr;
                  }
                   nbrMaxResultats=nbr;
                   break;

                  }
  default:


                         cout<<"invalid choice"<<endl;
                      fflush(stdin);

         }

}
