
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

Graphe::Graphe()
{

}

Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;
    ifs >> ordre;
    m_ordre=ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");


    int chiffre;
    std::string lieu;
    int hauteur;
    for (int i=1; i<=ordre; ++i)
    {

        ifs >> chiffre >> lieu >> hauteur ;
        m_sommets.push_back( new Sommet{chiffre, lieu, hauteur} );
    }

    bool etat;
    int debit;
    std::string type_arete;

    for(int i=0; i<12; i++)
    {
        ifs >> type_arete >>  etat >> debit;
        m_filtres.push_back({type_arete,etat});
        m_debits.push_back({type_arete,debit});
    }


    int taille;
    ifs >> taille;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");


    int num1,num2,num3; //num3 le numero de trajet, num1 le numero du sommet 1 et num2 le numero du sommet 2
    std::string name;
    std::string type;
    float num4;

    for (int i=0; i<taille; ++i)
    {
        Sommet* s1;
        Sommet* s2;
        ifs >> num3 >> name >> type >> num1 >> num2 >> num4;

        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture arc");


        for (auto elem : m_sommets)
        {
            if (elem->getNum()==num1)
                s1=elem;
            if (elem->getNum()==num2)
                s2=elem;
        }

        for(auto elem : m_filtres)
        {
            if(elem.first==type)
            {
                etat=elem.second;
            }
        }

        for(auto elem : m_debits)
        {
            if(elem.first==type)
            {
                debit=elem.second;
            }
        }

        m_arete.push_back( new Arete{num3, name, type, s1, s2,etat,debit,num4,nomFichier} );
    }

    sauvegarde(nomFichier);
}


Graphe::~Graphe()
{
    for (auto s : m_sommets)
        delete s;


    for(auto ar : m_arete)
        delete ar;
}

void Graphe::sauvegarde(std::string nomFichier)
{
    std::ofstream flux {nomFichier};

    for (auto elem : m_sommets)
    {
        elem->clear_pred();
        elem->clear_succ();

        for (auto ar : m_arete)
        {
            if (elem==ar->get_s1())
                elem->ajouterSucc(ar->get_poids(), ar->get_s2());

            if (elem==ar->get_s2())
                elem->ajouterPred(ar->get_poids(), ar->get_s1());
        }
    }

    flux << m_ordre << std::endl;

    for(auto elem : m_sommets)
    {
        flux << elem->getNum() << "  " << elem->getlieu() << "  " << elem->getaltitude() << std::endl;
    }

    int i=0;

    for(auto elem : m_filtres)
    {
        flux << elem.first << " " <<  elem.second << " " << m_debits[i].second << std::endl;
        i++;
    }

    flux << m_arete.size() << std::endl;

    for(auto elem : m_arete)
    {
        flux << elem->get_num_trajet() << "  " << elem->get_nom_trajet() << "  " << elem->get_type()
             << "  " << elem->get_s1()->getNum() << "  " << elem->get_s2()->getNum() << "  " << elem->get_poids() << std::endl;
    }
}


void Graphe::changement_arete(std::string nomFichier)
{
    int num=0;
    float new_poids=0;

    std::cout << "Quelle arete voulez vous modifier (entre 1 et 95):";
    do
    {
        std::cin >> num;

    }
    while(num<1 || num>95);

    std::cout << "Valeur du nouveau temps :";
    do
    {
        std::cin >> new_poids;

    }
    while(new_poids<=0);

    for(auto elem : m_arete)
    {
        if(elem->get_num_trajet()==num)
        {
            elem->set_poids(new_poids);
        }
    }

    sauvegarde(nomFichier);
}


void Graphe::changement_capacite(std::string nomFichier)
    {
        std::string type="";
        int new_capacite=0;

        std::cout << "Quel type d'installation voulez vous modifier :";
        do
        {
            std::cin >> type;

        }
        while(type!="V" && type!="B" && type!="R" &&type!="N" && type!="KL" && type!="SURF" && type!="TK" && type!="TS" && type!="TSD" && type!="TC" && type!="TPH" && type!="BUS");

        std::cout << std::endl << "Valeur de la nouvelle capacite de l'installation :";
        do
        {
            std::cin >> new_capacite;

        }
        while(new_capacite<=0);

        for(auto elem : m_arete)
        {
            if(elem->get_type()==type)
            {
                elem->set_capacite(new_capacite);
            }
        }

        int i=0;
        for(auto elem : m_debits)
        {
            if(elem.first==type)
            {
                m_debits[i].second=new_capacite;
            }
            i++;
        }
        sauvegarde(nomFichier);
    }


void Graphe::afficher() const
{
    for (auto elem : m_arete)
    {
        elem->affichage_arete();
        std::cout << std::endl;
    }

}

std::vector<Sommet*> Graphe::get_sommets()const
    {
        return m_sommets;
    }

Sommet* Graphe:: getSommet()   /// Retourne le sommet demande
{
    int choix=0;
    std::cout << "Numero du point la station (entre 1 et 37): ";
    do
    {
        std::cin >> choix;
    }
    while (choix<1 || choix>37);

    for(auto elem : m_sommets )
    {
        if(elem->getNum()== choix)
        {
            return elem;
        }
    }
    return NULL;
}


void Graphe::choix_trajet()
{
    int choix=0;
    std::cout << std::endl << "Saisissez le numero de trajet que vous voulez connaitre (entre 1 et 95): ";
    do
    {
        std::cin >> choix;

    }
    while(choix < 1 || choix > 95);

    for(auto elem :m_arete)
    {
        if(choix==elem->get_num_trajet())
        {
            elem->affichage_arete();
        }
    }
}

void Graphe::choix_sommet()
{
    int choix=0;
    std::cout << "Saisissez la station de depart (entre 1 et 37): ";
    do
    {
        std::cin >> choix;

    }
    while(choix < 1 || choix > 37);

    m_sommets[choix-1]->afficher();
}

void Graphe::reinitialisation()
{
    for(auto elem : m_sommets)
    {
        elem->setdistance(0);
        elem->setPassage_faux();
        elem->setMarqueur_faux();
    }
}

void Graphe::affichage_filtre(std::string nomFichier)
{
    std::cout << std::endl << "Parametres sauvegardes :" << std::endl << std::endl;
    int i=1;
    int choix=0;
    bool ver;

    do
    {
        gotoligcol(14,0);

        for(auto elem : m_filtres)
        {
            std::cout << i << ". " << elem.first << "  : " ;
            if(elem.second==true)
            {
                Color(10,0);
                std::cout << " ACTIF     " << std::endl;
            }
            if(elem.second==false)
            {
                Color(12,0);
                std::cout << " NON-ACTIF   " << std::endl;
            }
            Color(15,0);

            i++;
        }

        i=1;

        std::cout << std::endl << std::endl <<  "0. Fin choix filtres" << std::endl;

        do
        {
            gotoligcol(29,0);
            std::cout << "      ";
            gotoligcol(29,0);
            std::cin >> choix;


        }
        while(choix <0 || choix >12);

        if(choix==0)
        {

        }

        else
        {
            for(int i=0; i<12; i++)
            {
                if(choix==i+1)
                {
                    if(m_filtres[i].second==true)
                    {
                        ver=true;
                        m_filtres[i].second=false;

                        for(auto ar : m_arete)
                        {
                            if(ar->get_type()==m_filtres[i].first)
                            {
                                ar->set_active(false);
                            }
                        }
                    }


                    if(m_filtres[i].second==false && ver==false)
                    {
                        m_filtres[i].second=true;

                        for(auto ar : m_arete)
                        {
                            if(ar->get_type()==m_filtres[i].first)
                            {
                                ar->set_active(true);
                            }
                        }
                    }

                }

                ver=false;
            }
        }

    }
    while(choix!=0);

    sauvegarde(nomFichier);

}


void Graphe::BFS(Sommet* s_dep,Sommet* s_arr)
{
    std::queue <Sommet*> file;
    std::vector <int> chemin;
    std::vector <int> tri;
    Sommet* init;

    if(s_dep==s_arr)
    {
        Color(12,0);
        std::cout << std::endl << "C'est le meme point de la station" << std::endl;
        Color(15,0);
    }

    else
    {
        file.push(s_dep);       // On met le sommet de départ dans la file
        s_dep->setMarqueur();   // on marque ce sommet
        init=s_dep;             // stocke temporairement le sommet de départ dans une autre variable

        while(!file.empty() && s_arr->getMarqueur()==false)
        {
            for(auto elem : init->getSuccesseurs())
            {
                if(elem.second->getMarqueur()== false ) //on parcout les successeurs du sommet, s'ils ne sont pas deja marqués on les marque puis ajoute dans la file
                {
                    elem.second->setMarqueur();
                    tri.push_back(elem.second->getNum());
                }

            }
            std::sort (tri.begin(),tri.end());
            for(auto elem : tri)
            {
                for(auto succ : init->getSuccesseurs())
                {
                    if(elem==succ.second->getNum())
                    {
                        file.push(succ.second);
                        succ.second->set_pred_BFS(init);
                    }
                }
            }
            tri.clear();
            file.pop(); /// enlever le sommet initial de la file
            init=file.front();

        }

        if(s_arr->getMarqueur()==false)
        {
            Color(12,0);
            std::cout << "Il n'est pas possible de rejoindre ces deux points de la station dans ce sens" << std::endl;
            Color(15,0);
        }

        else
        {
            init=s_arr;

            while(init!=s_dep)
            {
                chemin.push_back(init->get_pred_BFS()->getNum());
                init=init->get_pred_BFS();
            }

            std::cout << std::endl << std::endl << "Le chemin le plus court en nombre d'aretes en partant de " << s_dep->getNum() << " a " << s_arr->getNum() << " est : " << std::endl;

            Color(10,0);
            for(std::vector<int>::reverse_iterator it=chemin.rbegin(); it!=chemin.rend(); it++)
            {
                std::cout <<  *it << " -> ";
            }
            std::cout << s_arr->getNum() << std::endl;
            Color(15,0);
        }
    }

    reinitialisation();

}


void Graphe::BFS_Ford(Sommet* s_dep,Sommet* s_arr, bool &fin)
{
    std::queue <Sommet*> file;
    std::vector <int> chemin;
    std::vector <int> tri;
    Sommet* init;

    if(s_dep==s_arr)
    {
        Color(12,0);
        std::cout << "C'est le meme point de la station" << std::endl;
        Color(15,0);
    }

    else
    {
        file.push(s_dep);       // On met le sommet de départ dans la file
        s_dep->setMarqueur();   // on marque ce sommet
        init=s_dep;             // stocke temporairement le sommet de départ dans une autre variable

        while(!file.empty() && s_arr->getMarqueur()==false)
        {
            for(auto elem : init->getSuccesseurs())
            {
                for(auto ar : m_arete)
                {
                    if(elem.second==ar->get_s2() && elem.first==ar->get_poids())
                    {
                        if(elem.second->getMarqueur()== false && (ar->get_flot() < ar->get_capacite())) //on parcout les successeurs du sommet, s'ils ne sont pas deja marqués on les marque puis ajoute dans la file
                        {
                            elem.second->setMarqueur();
                            tri.push_back(elem.second->getNum());
                        }
                    }
                }
            }
            std::sort (tri.begin(),tri.end());
            for(auto elem : tri)
            {
                for(auto succ : init->getSuccesseurs())
                {
                    if(elem==succ.second->getNum())
                    {
                        file.push(succ.second);
                        succ.second->set_pred_BFS(init);
                    }
                }
            }
            tri.clear();
            file.pop(); /// enlever le sommet initial de la file
            init=file.front();

        }

        if(s_arr->getMarqueur()==false)
        {
            Color(12,0);
            std::cout << std::endl << "Il n'est pas possible de rejoindre ces deux points de la station dans ce sens" << std::endl;
            Color(15,0);
            fin=true;

        }

        else
        {
            init=s_arr;

            while(init!=s_dep)
            {
                chemin.push_back(init->get_pred_BFS()->getNum());
                init=init->get_pred_BFS();
            }

            std::cout << std::endl << std::endl << "Le chemin le plus court en nombre d'aretes en partant de " << s_dep->getNum() << " a " << s_arr->getNum() << " est : " << std::endl;

            Color(10,0);
            for(std::vector<int>::reverse_iterator it=chemin.rbegin(); it!=chemin.rend(); it++)
            {
                std::cout <<  *it << " -> ";
            }
            std::cout << s_arr->getNum() << std::endl;
            Color(15,0);


        }

    }
    reinitialisation();

}


/*void BFS_inverse(Sommet* s_dep,Sommet* s_arr)
{
    std::queue <Sommet*> file;
    std::vector <int> chemin;
    std::vector <int> tri;
    Sommet* init;

    if(s_dep==s_arr)
    {
        std::cout << "C'est le meme point de la station" << std::endl;
    }

    else
    {
        file.push(s_dep);       // On met le sommet de départ dans la file
        s_dep->setMarqueur();   // on marque ce sommet
        init=s_dep;             // stocke temporairement le sommet de départ dans une autre variable

        while(!file.empty() && s_arr->getMarqueur()==false)
        {
            for(auto ar : m_arete)
            {
                if(ar->get_s1()==init)
                {
                    if(ar->get_s2()->getMarqueur()== false && (ar->get_flot() < ar->get_capacite())) //on parcout les successeurs du sommet, s'ils ne sont pas deja marqués on les marque puis ajoute dans la file
                    {
                        ar->get_s2()->setMarqueur();
                        tri.push_back(ar->get_s2()->getNum());
                    }
                }
            }

            std::sort (tri.begin(),tri.end());

            for(auto elem : tri)
            {
                for(auto ar : m_arete)
                {
                    if(elem==ar->get_s2()->getNum())
                    {
                        file.push(ar->get_s2());
                        ar->get_s2()->set_pred_BFS(init);
                    }
                }
            }
            tri.clear();
            file.pop(); /// enlever le sommet initial de la file
            init=file.front();

        }

        if(s_arr->getMarqueur()==false)
        {
            std::cout << "Il n'est pas possible de rejoindre ces deux points de la station dans ce sens" << std::endl;
        }

        else
        {
            init=s_arr;

            while(init!=s_dep)
            {
                chemin.push_back(init->get_pred_BFS()->getNum());
                init=init->get_pred_BFS();
            }

            std::cout << std::endl << std::endl << "Le chemin le plus court en nombre d'aretes en partant de " << s_dep->getNum() << " a " << s_arr->getNum() << " est : " << std::endl << std::endl ;

            for(std::vector<int>::reverse_iterator it=chemin.rbegin(); it!=chemin.rend(); it++)
            {
                std::cout <<  *it << " -> ";
            }
            std::cout << s_arr->getNum() << std::endl;


        }

    }
    reinitialisation();

}
*/


//version=1 si on fait un dijkstra classsique
//version=2 si on retire un type de chemin
void Graphe::Dijkstra(Sommet* s_dep, Sommet* s_arr, int version,int j,std::string nomFichier)
{
    float distance_finale=0.0;  // on initialise toutes les variables necessaire au deroulement de l'algo
    std::vector < std::pair <float,Sommet*> > news;
    std::priority_queue < std::pair < float, Sommet*>,  std::vector < std::pair < float, Sommet*> >, std::greater <std::pair < float, Sommet*> > > m_pq;
    Sommet* temp;
    bool fin=false;

    //Variable utile uniquement pour dijkstra 2
    bool active;

    if(version==2 && j==0)
        affichage_filtre(nomFichier);

    s_dep->setMarqueur();
    temp=s_dep;

    if(s_dep->getNum()==s_arr->getNum())
    {
        Color(12,0);
        std::cout << std::endl <<  "C'est le meme sommet, la distance vaut donc 0." << std::endl;
        Color(15,0);
    }

    else
    {

        for(auto elem : s_dep->getSuccesseurs()) // initialisation du premier sommet
        {
            if (version==2)
            {
                for(auto ar : m_arete)
                {
                    if(elem.second->getNum()==ar->get_s2()->getNum() && elem.first == ar->get_poids())
                    {
                        active=ar->get_active();
                    }
                }
            }

            if(elem.second->getMarqueur()==false)
            {
                if (  (version==1)  ||   (version==2 && active==true) )
                    m_pq.push(elem);

            }

        }

        do
        {
            if(m_pq.size()>0)
            {
                m_pq.top().second->setMarqueur();
                temp=m_pq.top().second;

                for(auto elem : temp->getSuccesseurs())  // on parcout les successeurs du sommet actuel
                {
                    if (version==2)
                    {
                        for(auto ar : m_arete)

                        {
                            if(elem.second->getNum()==ar->get_s2()->getNum() && elem.first == ar->get_poids())
                            {
                                active=ar->get_active();
                            }
                        }
                    }

                    if(elem.second->getMarqueur()==false)
                    {
                        if (  (version==1)  ||   (version==2 && active==true) )
                        {
                            float distance=0;
                            Sommet* s;
                            distance=m_pq.top().first + elem.first;  // on calcule sa distance au sommet de depart
                            s=elem.second;
                            news.push_back({distance,s});    // on cree une nouvelle pair contenant les nouvelles/bonnes informations
                        }
                    }


                }

                distance_finale = m_pq.top().first;  // on recupere la distance finale entre les deux sommets
                m_pq.top().second->setdistance(m_pq.top().first);

                m_pq.pop(); // on oublie pas d'enlever le sommet decouvert de la priority queue


                for(auto elem : news) // les nouvelles paires des successeurs sont push dans la priority queue
                {
                    if(elem.second->getMarqueur()==false)
                    {
                        m_pq.push(elem);
                    }
                }
                news.clear(); // on vide � chaque tour de boucle le vector de nouvelles paires sinon on a des doublons

            }
            else
            {
                fin=true;
            }


        }
        while(s_arr->getMarqueur()== false && fin==false);  // on arrete le parcours du graphe lorsque le sommet d'arriv�e a �t� marqu�

        if(s_arr->getMarqueur()==false)
        {
            Color(12,0);
            std::cout << std::endl << "Il n'est pas possible d'atteindre le sommet " << s_arr->getNum() << " a partir du sommet "<< s_dep->getNum() << std::endl;
            Color(15,0);
        }

        else
        {
            std::cout << std::endl << std::endl <<  "Le chemin le plus court du sommet " << s_dep->getNum() << " au sommet " << s_arr->getNum()  << " dure : " << distance_finale << " secondes.";
            conversion_affichage(distance_finale);

            //AFFICHAGE CHEMIN

            std::vector <int> chemin;
            std::vector <float> distances;
            float petite=0;
            Sommet* s;

            s_arr->setPassage();
            chemin.push_back(s_arr->getNum());

            for(auto elem : s_arr->getPred() )
            {
                if (version==2)
                {
                    for(auto ar : m_arete)
                    {
                        if(elem.second->getNum()==ar->get_s1()->getNum() && elem.first == ar->get_poids())
                        {
                            active=ar->get_active();
                        }
                    }
                }


                if(elem.second->getMarqueur()==true)
                {
                    if (  (version==1)  ||   (version==2 && active==true) )
                        distances.push_back(elem.second->getdistance());
                }

            }

            std::sort (distances.begin(),distances.end());


            do
            {
                petite=distances[0];

                for(auto elem :m_sommets)
                {
                    if(elem->getdistance()==petite)
                    {
                        s=elem;
                    }
                }

                s->setPassage();
                chemin.push_back(s->getNum());
                distances.clear();

                for(auto elem : s->getPred())
                {
                    if (version==2)
                    {
                        for(auto ar : m_arete)
                        {
                            if(elem.second->getNum()==ar->get_s1()->getNum() && elem.first == ar->get_poids())
                            {
                                active=ar->get_active();
                            }
                        }
                    }


                    if(elem.second->getMarqueur()==true && elem.second->getPassage()==false)
                    {
                        if (  (version==1)  ||   (version==2 && active==true) )
                            distances.push_back(elem.second->getdistance());
                    }
                }

                std::sort (distances.begin(),distances.end());

            }
            while(petite!=0);

            Color(10,0);
            std::cout << s_dep->getNum() << " -> ";
            for(std::vector<int>::reverse_iterator it=chemin.rbegin()+1; it!=chemin.rend()-1; it++)
            {
                std::cout <<  *it << " -> ";
            }
            std::cout << s_arr->getNum() << std::endl;
            Color(15,0);

        }

    }
    reinitialisation();

}


void Graphe::Ford_Fulkerson(Sommet* s_dep, Sommet* s_arr)
{
    std::vector <std::pair < float, Sommet*> > temp_succ;
    std::vector <std::pair < float, Sommet*> > temp_pred;
    std::vector <Sommet*> chemin;
    std::vector <int> capacites;
    int flot=1;
    Sommet* init;
    bool fin=false;

    for(auto elem : m_sommets)
    {
        if(elem==s_dep)
        {
            temp_pred=elem->getPred();
            elem->clear_pred();
        }

        if(elem==s_arr)
        {
            temp_succ=elem->getSuccesseurs();
            elem->clear_succ();
        }
    }

    while(fin==false && flot!=0)
    {
        BFS_Ford(s_dep,s_arr,fin);

        if(fin==true)
        {
        }
        else
        {
            init=s_arr;
            chemin.push_back(s_arr);

            while(init!=s_dep)
            {
                chemin.push_back(init->get_pred_BFS());
                init=init->get_pred_BFS();
            }

            for(auto ar : m_arete)
            {
                for(auto elem : chemin)
                {
                    if((ar->get_s1()==elem->get_pred_BFS() && ar->get_s2()==elem && (ar->get_flot() < ar->get_capacite())))
                    {
                        capacites.push_back(ar->get_capacite()- ar->get_flot());
                        ar->set_direction(true);
                    }

                    if((ar->get_s2()==elem->get_pred_BFS() && ar->get_s1()==elem && (ar->get_flot() < ar->get_capacite())))
                    {
                        capacites.push_back(ar->get_capacite() - ar->get_flot());
                        ar->set_direction(false);
                    }
                }

            }

            std::sort (capacites.begin(),capacites.end());

            int i=0;
            for(auto elem : capacites)
            {
                for(auto ar : m_arete)
                {
                    if(ar->get_direction()==true)
                    {
                        if(elem==ar->get_capacite()-ar->get_flot() && i==0)
                        {
                            flot=elem;
                            i++;
                        }
                    }
                }
            }

            std::cout << "le flot est " << flot << std::endl;

            for(auto ar : m_arete)
            {
                for(auto elem : chemin)
                {
                    if((ar->get_s1()==elem->get_pred_BFS() && ar->get_s2()==elem && ar->get_s1()->getMarqueur()==false && (ar->get_flot() < ar->get_capacite())))
                    {
                        ar->set_flot(ar->get_flot()+flot);
                        ar->get_s1()->setMarqueur();
                    }
                }
            }

            reinitialisation();
            capacites.clear();
            chemin.clear();
        }
    }

    int flot_max=0;

    for(auto elem : s_dep->getSuccesseurs())
    {
        for(auto ar : m_arete)
        {
            if(ar->get_s2()==elem.second && ar->get_s1()==s_dep) //s1
            {
                flot_max=flot_max + ar->get_flot();
            }
        }
    }

    Color(10,0);
    std::cout << std::endl << std::endl <<"LE FLOT MAXIMUM VAUT DONC : " << flot_max << std::endl;
    Color(15,0);

    ///DEUXIEME ETAPE

    /*chemin.clear();
    capacites.clear();
    BFS_inverse(s_dep,s_arr);
    //BFS_Ford(s_dep,s_arr,fin);

    init=s_arr;
    chemin.push_back(s_arr);

    while(init!=s_dep)
    {
        chemin.push_back(init->get_pred_BFS());
        init=init->get_pred_BFS();
    }

    for(auto ar : m_arete)
    {
        for(auto elem : chemin)
        {
            if((ar->get_s1()==elem->get_pred_BFS() && ar->get_s2()==elem))
            {
                ar->set_direction(true);
                capacites.push_back(ar->get_capacite()- ar->get_flot());
                std::cout << ar->get_direction() << " " << ar->get_num_trajet() << " " << ar->get_marqueur_arete() <<  std::endl;
            }

            if((ar->get_s2()==elem->get_pred_BFS() && ar->get_s1()==elem))
            {
                ar->set_direction(false);
                capacites.push_back(ar->get_flot() - ar->get_capacite());
                std::cout << ar->get_direction() << " " << ar->get_num_trajet() << " " << ar->get_marqueur_arete() <<  std::endl;
            }
        }

    }


    std::cout << "CAPACITES" << std::endl;

    for(auto elem : capacites)
    {
        std::cout << elem << std::endl;
    }

    std::sort (capacites.begin(),capacites.end());
    flot=capacites[capacites.size()-1];

    std::cout << "le flot est :" << flot ;
    */

    /// Reinitialisation des flots
    for(auto ar : m_arete)
    {
        ar->set_flot(0);
    }

    /// Reinitialisation des successeurs et predecesseurs de la source et du puit
    for(auto elem : m_sommets)
    {
        if(elem==s_dep)
        {
            elem->set_pred(temp_pred);
        }

        if(elem==s_arr)
        {
            elem->set_succ(temp_succ);
        }
    }
}


void Graphe::affichage_PQ(std::priority_queue < std::pair < float, Sommet*>,  std::vector < std::pair < float, Sommet*> >, std::greater <std::pair < float, Sommet*> > > m_pq)
{
    while (!m_pq.empty()) // fonction permettant d'afficher le contenu de la priority queue
    {
        std::pair < float, Sommet*> temp;
        temp=m_pq.top();
        std::cout << temp.first << " "  << temp.second->getNum() << std::endl;
        m_pq.pop();
    }
    std::cout << std::endl << std::endl ;
}
