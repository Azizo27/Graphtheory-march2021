#include "header.h"


int main()
{
    std::string nomFichier = "graphe_data_arc.txt";
    std::vector <Sommet*> sommets;
    Sommet* s_dep;
    Sommet* s_arr;
    int choix;
    int j=0;
    Graphe g{nomFichier};

    Sleep(3000);
    Color(15,0);
    display_station();
    g=login(nomFichier);

    do
    {
        choix=menu(nomFichier);
        if (choix==1)
        {
            g.choix_sommet();
            test();
        }

        if (choix==2)
        {
            g.choix_trajet();
            test();

        }
        if (choix==3)
        {
            s_dep=g.getSommet();
            for(auto elem : g.get_sommets())
            {
                g.BFS(s_dep,elem);
            }
            test();


        }

        if(choix==4)
        {
            s_dep=g.getSommet();
            for(auto elem : g.get_sommets())
            {
                g.Dijkstra(s_dep,elem, 1,j,nomFichier);
            }
            test();
        }

        if (choix==5)
        {
            s_dep=g.getSommet();
            s_arr=g.getSommet();
            g.BFS(s_dep,s_arr);
            test();


        }

        if(choix==6)
        {
            s_dep=g.getSommet();
            s_arr=g.getSommet();
            g.Dijkstra(s_dep,s_arr, 1,j,nomFichier);
            test();
        }

        if(choix==7)
        {
            s_dep=g.getSommet();
            for(auto elem : g.get_sommets())
            {
                g.Dijkstra(s_dep,elem, 2,j,nomFichier);
                j++;
            }
            test();
            j=0;
        }
        if (choix==8)
        {
            s_dep=g.getSommet();
            s_arr=g.getSommet();
            g.Dijkstra(s_dep,s_arr, 2,j,nomFichier);
            test();

        }

        if (choix==9)
        {
            g.changement_arete(nomFichier);
            test();
        }

        if (choix==10)
        {
            g.changement_capacite(nomFichier);
            test();
        }

        if (choix==11)
        {
            s_dep=g.getSommet();
            s_arr=g.getSommet();

            g.Ford_Fulkerson(s_dep,s_arr);

            test();

        }
    }
    while (choix!=0);


    return 0;
}
