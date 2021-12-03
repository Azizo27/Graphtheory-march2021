#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <windows.h>
#include "header.h"


class Sommet
{
private :
    int m_num;
    std::string m_lieu;
    int m_altitude;
    float m_distance;
    Sommet* m_pred_BFS;
    std::vector <std::pair < float, Sommet*> > m_successeurs;  /// vector de paires contenant toutes les combinaisons poids-sommets
    std::vector <std::pair < float, Sommet*> > m_predecesseur;
    bool m_marqueur;              /// booleen pour marquer les sommets lors du parcours de Dijkstra
    bool m_passage;

public :
    /*constructeur*/
    Sommet(int number, std::string place, int hauteur):m_num{number}, m_lieu{place}, m_altitude{hauteur}
    {
        m_marqueur=false;
        m_passage=false;
        m_distance=0;
    };

    Sommet()
    {

    }

    /*getter*/
    int getNum()const
    {
        return m_num;
    }

    std::string getlieu() const
    {
        return m_lieu;
    }

    int getaltitude() const
    {
        return m_altitude;
    }

    int getdistance()const
    {
        return m_distance;
    }

    void setdistance(float distance)
    {
        m_distance=distance;
    }

    bool getMarqueur()
    {
        return m_marqueur;
    }

    bool getPassage()
    {
        return m_passage;
    }

    Sommet* get_pred_BFS()
    {
        return m_pred_BFS;
    }

    void set_pred_BFS(Sommet* s)
    {
        m_pred_BFS=s;
    }

    std::vector <std::pair < float, Sommet*> > getPred()
    {
        return m_predecesseur;
    }

    void clear_pred()
    {
        m_predecesseur.clear();
    }

    void set_pred(std::vector <std::pair < float, Sommet*> > pred)
    {
        m_predecesseur=pred;
    }

    ///accesseur : pour la liste des successeurs
    std::vector<std::pair < float, Sommet*> > getSuccesseurs()
    {
        return m_successeurs;
    }

    void clear_succ()
    {
        m_successeurs.clear();
    }

    void set_succ(std::vector <std::pair < float, Sommet*> > succ)
    {
        m_successeurs=succ;
    }

    /*setter*/
    void setMarqueur()
    {
        m_marqueur=true;
    }

    void setMarqueur_faux()
    {
        m_marqueur=false;
    }

    void setPassage()
    {
        m_passage=true;
    }

    void setPassage_faux()
    {
        m_passage=false;
    }

    void ajouterSucc(float poids, Sommet* s)
    {
        m_successeurs.push_back({poids, s});
    }

    void ajouterPred(float poids, Sommet* s)
    {
        m_predecesseur.push_back({poids,s});
    }

    void afficher() const;

};

#endif // SOMMET_H_INCLUDED
