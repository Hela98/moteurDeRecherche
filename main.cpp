
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
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include<string.h>

using namespace std;

int main()
{     int nbrFiles=0;
      char choix,sousChoix;
     // Bibliotheque bib;
      Lecteur* monLecteur;
      Lecteur1 lecture;//lecteur par défaut mais l'utilisateur peut le changer dans la configuration
      monLecteur=&lecture;
      AnalyseurVector analyseur;//Analyseur par défaut mais l'utilisateur peut le changer dans la configuration
      IndexVector index;//Index par défaut mais l'utilisateur peut le changer dans la configuration
      OrdonnanceurNbrOcc ordonnanceur;//Ordonanceur par défaut mais l'utilisateur peut le changer dans la configuration
      MoteurDeRecherche moteur(&analyseur,&index,&ordonnanceur,10);//le nbr des maximal des résultats à afficher aprés la recherche est 10, l'utilisateur peut changer ce paramétre dans la configuration

      cout<<"*********************MOTEUR DE RECHERCHE*********************"<<endl;
      cout<<endl;
      cout<<endl;
    while(1)
        {
       cout<<"***************Main menu***************"<<endl;
       cout<<"1-If you want to index a file type 1"<<endl;//le fichier va etre indexé , si le fichier est indexé déjà il va etre réindexé , car il peut etre modifié
       cout<<"2-If you want to index  multiple files  type 2"<<endl;
       cout<<"3-If you want to show index type 3"<<endl;
       cout<<"4-If you want to remove index type 4"<<endl;//choose file or remove all the index
       cout<<"*****************************************"<<endl;
       cout<<"5-If you want to view files type 5"<<endl;//affichage de repertoire (tous les fichiers qui sont déjà indexés)
       cout<<"*****************************************"<<endl;
       cout<<"6-If you want to make a research type 6"<<endl;
       cout<<"*****************************************"<<endl;
       cout<<"7-If you want to change the configuration type 7"<<endl;//configuration de : l'Analyseur,l'Index,l'Ordonnanceur,le nombre max des résultats affichés
       cout<<"*****************************************"<<endl;
       cout<<"If you want to close the application type 0"<<endl;
       cout<<"*****************************************"<<endl;
       cin>>choix;
        switch(choix)
        {
        case '1':
              {
                    string filePath;
                    cout<<"type the file path"<<endl;
                    fflush(stdin);
                    getline(cin,filePath);
                    while( filePath.size()<5 || strcmp((filePath.substr(filePath.size()-4)).c_str(),".txt" )!=0)
                    {
                           cout << "wrong path!" << endl;
                          cin.clear();
                          cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                          filePath.clear();
                           cin >> filePath;
                    }
                    vector <string> texte =monLecteur->extraireMots(filePath);
                    vector<pair<string,int> > statistics=moteur.indexerUnFichier(filePath,texte);
                    cout<<"Do you want to show the new index ? "<<endl;
                    fflush(stdin);
                    cout<<"type 1 if yes , type 2 if no "<<endl;
                    fflush(stdin);
                    cin>>sousChoix;
                    switch(sousChoix)
                     {
                         case '1':
                                 {
                                      cout<<"file index :"<<endl;
                                      for(unsigned int i(0);i<statistics.size();++i)
                                        {
                                              cout<<"<"<<statistics[i].first<<";"<<statistics[i].second<<">"<<endl;
                                         }
                                     break;
                                 }
                        case '2':
                                {
                                     break;
                                }
                       default:

                                    cout<<"invalid choice"<<endl;
                                    fflush(stdin);

                     }

              break;
              }
         case '2':
              {     char choix2;
                     map<string,vector<string> > filesContent;
                    cout<<"if you want to index the files of a directory type 1"<<endl;
                    fflush(stdin);
                    cout<<"if you want to enter the file paths one by one type 2"<<endl;
                    fflush(stdin);
                    cin>>choix2;
                     switch(choix2)
                     {

                         case '1':
                                 {
                                       string path;
                                      cout<<"Enter the directory path"<<endl;
                                       fflush(stdin);
                                       getline(cin,path,'\n');
                                       vector <string> fichiersAIndexer=moteur.filesDirectory(path);
                                       if(!fichiersAIndexer.empty())
                                       {
                                            for(unsigned int i(0);i<fichiersAIndexer.size();++i)
                                                {
                                                   filesContent[fichiersAIndexer[i]]=monLecteur->extraireMots(fichiersAIndexer[i]);
                                                  }
                                       }
                                     break;
                                 }
                        case '2':
                                {
                                      string filePath;
                                      vector<string> fichiersAIndexer;
                                      cout<<"Enter the number of files to index"<<endl;
                                      fflush(stdin);
                                      cin>>nbrFiles;
                                      while(cin.fail() || nbrFiles<=1)
                                       {
                                            cout << "Error" << endl;
                                            cin.clear();
                                            cin.ignore(256,'\n');
                                            cin >> nbrFiles;
                                         }

                                        for(int i(0);i<nbrFiles;++i)
                                         {
                                          cout<<"Enter the file path "<<i+1<<endl;
                                          fflush(stdin);
                                          getline(cin,filePath);
                                          while( filePath.size()<5 || strcmp((filePath.substr(filePath.size()-4)).c_str(),".txt" )!=0)
                                           {
                                                cout << "wrong path!" << endl;
                                                 //cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                                                cin.clear();
                                                filePath.clear();
                                                cin >> filePath;
                                            }
                                        if(find(fichiersAIndexer.begin(), fichiersAIndexer.end(), filePath)==fichiersAIndexer.end())
                                         {
                                              fichiersAIndexer.push_back(filePath);
                                          }
                                         }
                                           if(!fichiersAIndexer.empty())
                                                {
                                                      for(unsigned int i(0);i<fichiersAIndexer.size();++i)
                                                            {
                                                                filesContent[fichiersAIndexer[i]]=monLecteur->extraireMots(fichiersAIndexer[i]);
                                                                }
                                                    }


                                     break;
                                }
                       default:

                                    cout<<"invalid choice"<<endl;
                                    fflush(stdin);

                     }
                      if(!filesContent.empty())
                      {
                            map<string ,vector<pair<string,int> > > IndexRangee=moteur.indexerDesFichiers(filesContent);
                           cout<<"Do you want to show the new index ? "<<endl;
                            cout<<"type 1 if yes , type 2 if no "<<endl;
                            cin>>sousChoix;
                             switch(sousChoix)
                             {
                                   case '1':
                                 {
                                      cout<<"new index :"<<endl;
                                      for(map<string, vector<pair<string , int > > >::const_iterator it=IndexRangee.begin();it!=IndexRangee.end();++it)
                                       {

                                            cout<<'<'<<it->first<<';';
                                            for(unsigned int k(0) ;k<IndexRangee[it->first].size();k++){

                                               cout<< '<'<<IndexRangee[it->first][k].first<<";"<<IndexRangee[it->first][k].second<<'>';
                                          }
                                             cout <<'>'<<endl;

                                          }
                              break;
                                 }
                        case '2':
                                {
                                     break;
                                }
                       default:
                                {
                                    cout<<"invalid choice"<<endl;
                                    fflush(stdin);
                                }
                     }
                      }
                      else
                      {
                            cout<<"no file found"<<endl;
                      }

              break;

              }

        case '3':
            {
                  moteur.afficherToutLesIndex();
                  break;
            }
        case '4':
            {
                    string filePath;
                    cout<<"type the file path"<<endl;
                    fflush(stdin);
                    getline(cin,filePath);



                          moteur.supprimerIndex(filePath);

            break;
            }
        case '5':
            {
               cout<<moteur.bib;
            break;
            }
        case '6':
            {
                    string motsRecherches;
                   cout<<"Donnez svp votre requete de recherche"<<endl;
                  fflush(stdin);
                  getline(cin,motsRecherches);
                  moteur.rechercher(motsRecherches);

            break;
            }
        case '7':
            {
              moteur.configurer();
            break;
            }

        case '0':

                  {
                         moteur.bib.saveDirectory();

                      exit(0);

            break;
                  }
              default:
                  cout<<"invalid choice"<<endl;
                  fflush(stdin);

                  }
        }





    return 0;

}
