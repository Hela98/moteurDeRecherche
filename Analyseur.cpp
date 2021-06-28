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



///*******************AnalyseurVector**************
vector<pair<string,int> > AnalyseurVector::analyser(vector <string> texteAAnalyser)
      {

          vector <pair<string,int> > statistics;
             for(unsigned int i=0;i<texteAAnalyser.size();++i)
      {
            bool trouve(false);  //booleen pour tester si le mot existe déjà ou non
            for (unsigned int j=0;j<statistics.size();++j)
            {

                  if(statistics[j].first==texteAAnalyser[i])
                  {
                        trouve=true;// le mot existe déjà donc on va incrémenter le nombre d'occurrence
                       statistics[j].second+=1;
                        break;
                  }
            }
            if (trouve==false)  // le mot n'existe pas
            {
                statistics.push_back(make_pair(texteAAnalyser[i],1)); // ajout d'un pair dans le vector statistics
            }
      }
      return statistics;//la méthode analyser va retourner le vector statistics chaque case contient un pair contenant le mot et son occurrence
      }

  ///*******************AnalyseurMap**************
       vector<pair<string,int> > AnalyseurMap::analyser(vector <string> texteAAnalyser)
      {
            map <string,int>Occurence;
            for(unsigned int i=0;i<texteAAnalyser.size();++i)
      {
            ++Occurence[texteAAnalyser[i]];  //incrémenter le nombre d'occurrence  du mot ( texte[i])
      }
   vector <pair<string,int> > statistics;
   for(map<string,int> ::const_iterator it=Occurence.begin();it!=Occurence.end();++it)
   {
         pair<string,int> p(it->first,it->second);
         statistics.push_back(p);
   }

   return statistics;//la méthode analyser va retourner le vector statistics chaque case contient un pair contenant le mot et son occurrence
}
