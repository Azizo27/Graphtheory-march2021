
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <windows.h>
#include "Sommet.h"
#include "header.h"


void Sommet::afficher() const
    {
        std::cout << std::endl << std::endl << std::endl;
        Color(0,15);
        std::cout<<"POINT "<<m_num <<":";
        Color(15,0);
        std::cout <<" Il se situe a " <<m_lieu << ". Il a une altitude de " << m_altitude << " metres" <<  std::endl << std::endl;
        Color(12,0);
        std::cout <<"Successeurs: " << std::endl;
        Color(15,0);
        for (auto elem : m_successeurs)
        {
            std::cout <<  m_num <<" -> " << elem.second->getNum() << " en " << elem.first << " secondes";
            conversion_affichage(elem.first);
        }
        std::cout  << std::endl << std::endl;
        Color(12,0);
        std::cout <<"Predecesseurs: " << std::endl;
        Color(15,0);
        for (auto elem : m_predecesseur)
        {
            std::cout <<  elem.second->getNum() <<" -> " << m_num << " en " << elem.first << " secondes";
            conversion_affichage(elem.first);
        }
    }
