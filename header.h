#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <unistd.h>
#include <algorithm>
#include <queue>
#include "Sommet.h"
#include "arete.h"
#include "Graphe.h"
#include <windows.h>

void Color(int couleurDuTexte,int couleurDeFond);
void conversion_affichage(float resultat);
void gotoligcol( int lig, int col );
void display_station();
void display_menu();
int menu(std::string nomFichier);
void test();
Graphe login(std::string &nomFichier);
void affichage_file(std::queue <Sommet*> file);
float calcultemps(std::string  type, Sommet* s1, Sommet* s2);



#endif // HEADER_H_INCLUDED
