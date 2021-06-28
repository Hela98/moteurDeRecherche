#ifndef MOTEURDERECHERCHE_H_INCLUDED
#define MOTEURDERECHERCHE_H_INCLUDED
#include<string>
#include<vector>
#include<utility>
#include <set>
#include <map>
#include <iostream>
using std::string;
using std::vector;
using std::set;
using std::map;
using std::iostream;

///************Afficher******************
class Afficher
{
public:
    void operator()(std::string nomFichier) const;

};


///*************class Lecteur(class mere)**********
class Lecteur
{
public:
      virtual ~Lecteur(){};
      virtual vector <std::string>  extraireMots(std::string cheminFichier)=0;
};

///****************Class Lecteur1******************
class Lecteur1:public Lecteur
{
public:
        virtual ~Lecteur1(){};
      virtual vector <string>  extraireMots(string cheminFichier);

};

///*****************Class Lecteur2**************

class Lecteur2:public Lecteur
{
public:
      virtual ~Lecteur2(){};
      virtual vector <string>  extraireMots(string cheminFichier);

};

///*******************Lecteur3***************************
class Lecteur3:public Lecteur
{
public:
      virtual ~Lecteur3(){};
     virtual  vector <string>  extraireMots(string cheminFichier);

};

///***********class Analyseur (class mere)***********
class Analyseur
      {
      public:
      virtual ~Analyseur(){};
     virtual  vector<std::pair<string,int> > analyser (vector <string> texteAAnalyser) =0;
      };
///*************AnalyseurVector******

class AnalyseurVector:public Analyseur //Analyseur de fichier
      {
      public:
      virtual ~ AnalyseurVector(){};
       virtual vector<std::pair<string,int> > analyser (vector <string> texteAAnalyser);
      };
///**********AnalyseurMap************
 class AnalyseurMap:public Analyseur //Analyseur de fichier
      {
      public:
      virtual ~AnalyseurMap(){};
      virtual  vector<std::pair<string,int> > analyser (vector <string> texteAAnalyser);
      };

///*********class Index (class mere)*********
class Index
      {
protected:
     static const string  fileSave;//="statistics.txt";
      std::set<string> fichiersDejaIndexes;
public:
       virtual ~Index(){};
      void sauvegarderStat (vector <std::pair< string,std::pair<string,int> > > tripletStat);
     std:: map<string ,vector<std::pair<string,int> > > rangerLesIndex(vector <std::pair< string,std::pair<string,int> > > tripletStat);
      virtual vector<std::pair<string, std::pair<string , int > > >  lecteurIndex () =0;
       vector <std::pair <string,std::pair<string , int > > > indexer (vector <std::pair <string,int> > stat ,string cheminFichier) ;
      };

//const string fileSave="statistics.txt";

///******************Class IndexVector*********************

      class IndexVector:public Index
{
public:
  virtual ~IndexVector(){};
   virtual vector<std::pair<string, std::pair<string , int > > >  lecteurIndex ();


};
///******************Class IndexMultimap*********************
 class IndexMultimap:public Index
{
public:
   virtual ~IndexMultimap(){};
    virtual vector<std::pair<string,std:: pair<string , int > > >  lecteurIndex ();
};

///*******************Class Bibliotheque*****************************
class Bibliotheque //la classe Bibliotheque va retourner un vector qui contient les noms des fichiers qu'on va les analyser
{
public:
      Bibliotheque();
      bool ajouterFichiers(string cheminFichier);
      bool supprimerFichier(string cheminFichier);
      void affichageFichiers(std::ostream& flux)const;
      void saveDirectory();
      friend std::ostream& operator<<(std::ostream& flux,Bibliotheque const& bib);
      vector <string> fichiers;
      static const string  files;//"repertoire.txt";


};

///******************class Ordonnanceur (class mere)***************
class Ordonnanceur
{
      public:
     virtual ~Ordonnanceur(){};
      vector <string> convertirMotCles (string requeteRecherche);
      vector <string> trier (map<string,int> resultatRechercher);
      virtual std::map<string,int> rechercher(std::vector<string> motCles , std::map<string, vector<std::pair<string,int> > > resultatFinalIndex ) =0;
      virtual void afficherResultat(vector <string>fichiersTries,unsigned int nbrResultat)=0; //ordonnaceurNbrOcc a un affichage avec le score
};

///*******************class OrdonnanceurBinaire ******************
class OrdonnanceurBinaire:public Ordonnanceur
{
public:
      virtual ~OrdonnanceurBinaire(){};
     virtual  map<string,int> rechercher(vector<string> motCles , map<string, vector<std::pair<string,int> > > resultatFinalIndex );
     virtual void afficherResultat(vector <string>fichiersTries,unsigned int nbrResultat);

};
///*****************Class OrdonnanceurNbrOcc*****************
class OrdonnanceurNbrOcc:public Ordonnanceur
{
      public:
    virtual ~OrdonnanceurNbrOcc(){};
     virtual  std::map<string,int> rechercher(vector<string> motCles , std::map<string, vector<std::pair<string,int> > > resultatFinalIndex );
     virtual void afficherResultat(vector <string>fichiersTries,unsigned int nbrResultat);
};

///****************Class MoteurDeRecherche **********
class MoteurDeRecherche
{
public:
      ~MoteurDeRecherche()
      {
            delete monAnalyseur;
            delete monIndex;
            delete monOrd;
      }
      unsigned int nbrMaxResultats;
      Analyseur* monAnalyseur=0;
      Index* monIndex=0;
      Ordonnanceur* monOrd=0;
      Bibliotheque bib;
      MoteurDeRecherche(Analyseur* a,Index* i,Ordonnanceur* o,unsigned int n);
       vector<std::pair<string,int> > indexerUnFichier(string fichierAIndexer,vector<string> texte);
       map<string ,vector<std::pair<string,int> > > indexerDesFichiers(map<string,vector<string> > filesContent);
       vector<string>   filesDirectory (string pathDirectory);
       void supprimerIndex(string cheminFichier);
       void afficherToutLesIndex();
       void rechercher(string motsRecherches);
       void configurer();
       void configurerOrdonnanceur (Ordonnanceur* newOrdonnanceur);


      // n'oublier pas de configurer le lecteur dans le main
};
#endif // MOTEURDERECHERCHE_H_INCLUDED
