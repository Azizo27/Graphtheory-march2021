#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <queue>
#include "Sommet.h"
#include "arete.h"
#include <windows.h>
#include "header.h"

class Sommet;

class Arete;

class Graphe
{
private :
    ///liste des sommets (vecteur de pointeurs sur Sommet)
    std::vector <Sommet*> m_sommets;
    std::vector <Arete*> m_arete;
    std::vector <std::pair <std::string,bool> > m_filtres;
    std::vector <std::pair <std::string,int> > m_debits;
    int m_ordre;

public :
    Graphe(std::string nomFichier);
    Graphe();

    /*destructeur*/
    ~Graphe();


    void sauvegarde(std::string nomFichier);

    void changement_arete(std::string nomFichier);

    void changement_capacite(std::string nomFichier);

    /*méthode d'affichage*/
    void afficher() const;

    std::vector<Sommet*> get_sommets()const;

    Sommet* getSommet();

    void choix_trajet();

    void choix_sommet();

    void reinitialisation();

    void affichage_filtre(std::string nomFichier);

    void BFS(Sommet* s_dep,Sommet* s_arr);


    void BFS_Ford(Sommet* s_dep,Sommet* s_arr, bool &fin);

    //version=1 si on fait un dijkstra classsique
    //version=2 si on retire un type de chemin
    void Dijkstra(Sommet* s_dep, Sommet* s_arr, int version,int j,std::string nomFichier);

    void Ford_Fulkerson(Sommet* s_dep, Sommet* s_arr);


    void affichage_PQ(std::priority_queue < std::pair < float, Sommet*>,  std::vector < std::pair < float, Sommet*> >, std::greater <std::pair < float, Sommet*> > > m_pq);

};


#endif // GRAPHE_H_INCLUDED
