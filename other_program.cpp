#include "header.h"

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void gotoligcol( int lig, int col )
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

void conversion_affichage(float resultat)
{
    int heure=0;
    int minute=0;

    resultat=resultat/3600.0;  // 1.055
    heure=resultat;  // mH = 1;
    resultat=resultat-heure; // 1.055 - 1 = 0.055
    resultat=resultat*60; // 0.055*60 = 3,3

    if(resultat < 1)
    {
        resultat=resultat*60;
    }

    else
    {
        minute=resultat; // min = 3  sec = 18
    }

    Color(11,0);
    if(heure==0)

        if(minute==0)
        {
        }
        else
        {
            std::cout <<  " (environ "<<minute << " min)" << std::endl;
        }

    else
    {
        std::cout << " (environ " << heure << " h " << minute << " min)" << std::endl;
    }
    Color(15,0);

}


void display_station()
{
    int x=3, y=55, a_x=1;
    Color(12,0);
    gotoligcol(x,y);
    std::cout << "  ____ _____  _  _____ ___ ___  _   _           _     _____ ____       _    ____   ____ ____  " << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout << " / ___|_   _|/ \\|_   _|_ _/ _ \\| \\ | |         | |   | ____/ ___|     / \\  |  _ \\ / ___/ ___| " << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout << " \\___ \\ | | / _ \\ | |  | | | | |  \\| |  _____  | |   |  _| \\___ \\    / _ \\ | |_) | |   \\___ \\ " << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout << "  ___) || |/ ___ \\| |  | | |_| | |\\  | |_____| | |___| |___ ___) |  / ___ \\|  _ <| |___ ___) |" << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout << " |____/ |_/_/   \\_\\_| |___\\___/|_| \\_|         |_____|_____|____/  /_/   \\_\\_| \\_\\\\____|____/ " << std::endl;
    Color(15,0);
}


void display_menu()
{
    int x=8, y=0, a_x=1;
    Color(11,0);
    gotoligcol(x,y);
    std::cout << "  /\\/\\   ___ _ __  _   _   _ " << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout <<  " /    \\ / _ \\ '_ \\| | | | (_)" << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout << "/ /\\/\\ \\  __/ | | | |_| |  _ " << std::endl;
    x=x+a_x;
    gotoligcol(x,y);
    std::cout << "\\/    \\/\\___|_| |_|\\__,_| (_)" << std::endl;
    Color(15,0);
}


int menu(std::string nomFichier)
{
    int choix;
    system("cls");
    display_station();
    display_menu();

    if(nomFichier=="touchousse_graphe_data_arc.txt")
    {
        std::cout  << std::endl << std::endl << std::endl;
        std::cout <<"1.Departs et arrivees d'un point" << std::endl << std::endl;
        std::cout <<"2.Depart et arrivee d'un trajet " << std::endl << std::endl;
        std::cout <<"3.Plus court chemin EN NOMBRE D'ARCS entre un point de depart et les autres points (BFS)" << std::endl  << std::endl;
        std::cout <<"4.Plus court chemin EN TEMPS entre un point de depart et les autres points (Dijkstra)" << std::endl << std::endl;
        std::cout <<"5.Plus court chemin EN NOMBRE D'ARCS entre deux points (BFS)" << std::endl << std::endl;
        std::cout <<"6.Plus court chemin EN TEMPS entre deux points (Dijkstra)" << std::endl << std::endl;
        std::cout <<"7.Optimisation du trajet EN TEMPS entre un point de depart et les autres points" << std::endl << std::endl;
        std::cout <<"8.Optimisation du trajet EN TEMPS entre deux points" << std::endl << std::endl ;
        std::cout <<"9.Modifier le temps d'un trajet" << std::endl << std::endl;
        std::cout <<"10.Modifier la capacite d'une installation " << std::endl << std::endl;
        std::cout <<"11.Optimisation des flux de skieurs dans la station" << std::endl << std::endl << std::endl << std::endl;
        std::cout <<"0.Quitter le logiciel" << std::endl << std::endl;

        do
        {
            std::cin >> choix;
        }
        while (choix<0 || choix>11);

    }

    else
    {
        std::cout  << std::endl << std::endl << std::endl;
        std::cout <<"1.Departs et arrivees d'un point" << std::endl << std::endl;
        std::cout <<"2.Depart et arrivee d'un trajet " << std::endl << std::endl;
        std::cout <<"3.Plus court chemin EN NOMBRE D'ARCS entre un point de depart et les autres points (BFS)" << std::endl  << std::endl;
        std::cout <<"4.Plus court chemin EN TEMPS entre un point de depart et les autres points (Dijkstra)" << std::endl << std::endl;
        std::cout <<"5.Plus court chemin EN NOMBRE D'ARCS entre deux points (BFS)" << std::endl << std::endl;
        std::cout <<"6.Plus court chemin EN TEMPS entre deux points (Dijkstra)" << std::endl << std::endl;
        std::cout <<"7.Optimisation du trajet EN TEMPS entre un point de depart et les autres points" << std::endl << std::endl;
        std::cout <<"8.Optimisation du trajet EN TEMPS entre deux points" << std::endl << std::endl ;
        std::cout <<"0.Quitter le logiciel" << std::endl << std::endl;

        do
        {
            std::cin >> choix;
        }
        while (choix<0 || choix>8);
    }

    system("cls");
    display_station();
    return choix;

}


void test()
{
    std::cout << std::endl << std::endl <<std::endl<< "0. Appuyez sur 0 pour revenir au menu principal" << std::endl;
    int fin=0;
    do
    {
        std::cin >> fin;

    }
    while(fin!=0);
}



Graphe login(std::string &nomFichier)
{
    std::string pseudo;
    gotoligcol(25, 75);
    std::cout << "Nom d'utilisateur : " ;
    std::cin >> pseudo;

    std::ifstream flux {pseudo+"_graphe_data_arc.txt"};

    if(flux.is_open())
    {
        Graphe utilisateur{pseudo+"_graphe_data_arc.txt"};
        nomFichier=pseudo+"_graphe_data_arc.txt";
        std::cout << nomFichier << std::endl;
        flux.close();
        return utilisateur;
    }
    else
    {
        std::ifstream read {"graphe_data_arc_original.txt"};
        std::ofstream write {pseudo+"_graphe_data_arc.txt"};
        std::string ligne;

        while(getline(read,ligne))
        {
            if(write)
            {
                write << ligne << std::endl;
            }
            else
            {
                std::cout << "fichier ecriture impossible a ouvrir" << std::endl;
            }
        }

        Graphe utilisateur {pseudo+"_graphe_data_arc.txt"};
        nomFichier=pseudo+"_graphe_data_arc.txt";
        write.close();
        return utilisateur;
    }

}


void affichage_file(std::queue <Sommet*> file) // permet d'afficher l'etat de la file pour le BFS
{
    std::queue <Sommet*> temp;
    temp=file;
    while (!temp.empty())
    {

        std::cout << temp.front()->getNum();
        temp.pop();

        if (!temp.empty())
            std::cout << " --> " ;
    }
    std::cout << std::endl << std::endl;
}


float calcultemps(std::string  type, Sommet* s1, Sommet* s2)
{
    float x;
    float ajout;
    float temps_seconde;

    float altitude_une=s1->getaltitude();
    float altitude_deux=s2->getaltitude();


    if (type=="V" || type=="B" ||type=="R" ||type=="N" ||type=="KL" ||type=="SURF")
        ajout=0;

    if (type=="TK" || type=="TS" || type=="TSD")
        ajout=1*60;

    if (type=="TC")
        ajout=2*60;

    if (type=="TPH")
        ajout=4*60;

    if (type=="V")
        temps_seconde=5*60;

    if (type=="B")
        temps_seconde=4*60;

    if (type=="R")
        temps_seconde=3*60;

    if (type=="N")
        temps_seconde=2*60;

    if (type=="KL")
        temps_seconde=10;

    if (type=="SURF")
        temps_seconde=10*60;

    if (type=="TK" || type=="TS")
        temps_seconde=4*60;

    if (type=="TSD" || type=="TC")
        temps_seconde=3*60;

    if (type=="TPH")
        temps_seconde=2*60;



    if (altitude_deux>=altitude_une)
        x= ajout+((temps_seconde/100)*(altitude_deux-altitude_une));

    if (altitude_une>altitude_deux)
        x= ajout+((temps_seconde/100)*(altitude_une-altitude_deux));

    return x;
}






