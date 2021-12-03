
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include "Sommet.h"
#include "header.h"


Arete::Arete(int numero, std::string nom, std::string type, Sommet* s1, Sommet*s2,bool active,int debit,float poids,std::string nomFichier)
    {
        m_num_trajet=numero;
        m_nom_trajet=nom;
        m_type=type;
        m_s1=s1;
        m_s2=s2;
        m_flot=0;
        m_active=active;
        m_direction=false;
        m_capacite=debit;

        if (m_type=="BUS")
        {
            if (m_num_trajet==61 || m_num_trajet==60)
                m_poids=40*60;

            if (m_num_trajet==59 || m_num_trajet==58)
                m_poids=30*60;
        }

        else
            m_poids=calcultemps(type, s1, s2);


        if(nomFichier=="touchousse_graphe_data_arc.txt")
            m_poids=poids;
    }


void Arete::affichage_arete() const
    {
        std::cout << std::endl <<  std::endl;
        Color(0,15);
        std::cout <<"Numero du trajet:";
        Color(15,0);
        std::cout << " " << m_num_trajet << std::endl << std::endl;
        Color(0,15);
        std::cout <<"Nom :";
        Color(15,0);
        std::cout << " " << m_nom_trajet << std::endl << std::endl;
        Color(0,15);
        std::cout <<"Type:";
        Color(15,0);
        std::cout << " " << m_type << std::endl << std::endl;
        Color(0,15);
        std::cout <<"Temps pour le parcourir:";
        Color(15,0);
        std::cout << " " << m_poids <<" secondes";
        conversion_affichage(m_poids);
        std::cout << std::endl << std::endl;
        Color(0,15);
        std::cout << "Chemin parcouru:";
        Color(15,0);
        std::cout << " " << m_s1->getNum() << " -> " <<m_s2->getNum() << std::endl;
    }


