#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include "Sommet.h"
#include "header.h"

class Sommet;



class Arete
{
private:
    int m_num_trajet;
    std::string m_nom_trajet;
    std::string m_type; //Va servir pour connaitre le poids (On peut meme mettre en int puis convertir dans le chargement en poids)
    float m_poids;
    bool m_active;
    bool m_direction;
    int m_capacite;
    int m_flot;
    Sommet* m_s1;
    Sommet* m_s2;


public:
    Arete(int numero, std::string nom, std::string type, Sommet* s1, Sommet*s2,bool active,int debit,float poids,std::string nomFichier);


    void affichage_arete() const;

    int get_num_trajet() const
    {
        return m_num_trajet;
    }

    bool get_active()const
    {
        return m_active;
    }

    void set_active(bool active)
    {
        m_active=active;
    }

    std::string get_nom_trajet() const
    {
        return m_nom_trajet;
    }
    std::string get_type() const
    {
        return m_type;
    }
    Sommet* get_s1() const
    {
        return m_s1;
    }
    Sommet* get_s2() const
    {
        return m_s2;
    }

    float get_poids() const
    {
        return m_poids;
    }

    void set_poids(float poids)
    {
        m_poids=poids;
    }

    int get_flot() const
    {
        return m_flot;
    }
    void set_flot(int flot)
    {
        if(flot <= m_capacite)
            m_flot=flot;
    }

    void set_capacite(int capacite)
    {
        m_capacite=capacite;
    }

    int get_capacite() const
    {
        return m_capacite;
    }

    bool get_direction() const
    {
        return m_direction;
    }

    void set_direction(bool direction)
    {
        m_direction=direction;
    }

    //~Arete();

};

#endif // ARETE_H_INCLUDED
