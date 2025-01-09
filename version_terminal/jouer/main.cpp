#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
void clearScreen() {
    cout << "\033[H\033[2J";
}
const unsigned KReset   (0);// on définit une constante dont la valeur est nulle
const unsigned KPlayer1   (31); // code de couleur pour joueur1
const unsigned KPlayer2    (34); // code de couleur pour joueur2
typedef vector <char> CVLine; // type représentant une ligne de matrice
typedef vector <CVLine> CMatrix; // type représentant la matrice
typedef pair <unsigned, unsigned> CPosition; // type représentant une coordonnée dans la matrice
const char kTokenPlayer1 = 'X'; // joueur1
const char kTokenPlayer2 = 'O'; // joueur2
const char kEmpty        = '_'; // le sol
const char kMur = '#'; // obstacle
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}
void initMur(CMatrix & Mat) {// Fonction pour initialiser les obstacles dans la version difficile
    Mat[3][2]=kMur;// on va avoir un mur dans la 3 ème ligne et 2ème ligne
    Mat[0][7]=kMur;
    Mat[1][7]=kMur;
    Mat[2][5]=kMur;
    Mat[2][6]=kMur;
    Mat[2][7]=kMur;
    Mat[3][9]=kMur;
    Mat[4][9]=kMur;
    Mat[4][1]=kMur;
    Mat[4][2]=kMur;
    Mat[5][1]=kMur;
    Mat[5][2]=kMur;
    Mat[5][3]=kMur;
    Mat[5][6]=kMur;
    Mat[5][7]=kMur;
    Mat[5][9]=kMur;
    Mat[6][4]=kMur;
    Mat[7][2]=kMur;
    Mat[7][5]=kMur;
    Mat[7][8]=kMur;
    Mat[7][9]=kMur;
    Mat[8][2]=kMur;
    Mat[8][8]=kMur;
    Mat[8][9]=kMur;
    Mat[9][2]=kMur;
}
void initMat(CMatrix & Mat, unsigned nbLine, unsigned nbColumn, CPosition & posPlayer1, CPosition & posPlayer2, bool difficult) {// Fonction pour initialiser la matrice
    Mat.assign(nbLine, CVLine(nbColumn, kEmpty));
    posPlayer1 = {0, 0}; // position initiale du joueur 1
    posPlayer2 = {nbLine - 1, nbColumn - 1}; // position initiale du joueur 2
    Mat[0][0] = kTokenPlayer1; // placement du joueur1
    Mat[nbLine - 1][nbColumn - 1] = kTokenPlayer2; // placement du joueur2
    if (difficult) {//si c'est la version difficile
        initMur(Mat); // Ajouter les obstacles
    }
}
void showMatrix(const CMatrix & Mat) {//procedure qui nous permet d'afficher la matrice
    clearScreen();
    for (size_t i = 0; i < Mat.size(); i++) {
        cout << "|";// on affiche un mur au debut de la ligne
        for (size_t j = 0; j < Mat.size(); j++) {
            couleur(KReset);//rénisialiser la couleur
            if (Mat[i][j] == kTokenPlayer1) {// si c'est le joueur 1
                couleur(KPlayer1); //changer la couleur du joueur 1 en rouge
                cout << kTokenPlayer1;//afficher le joueur 1 sur le terminal
                couleur(KReset);
            } else if (Mat[i][j] == kTokenPlayer2) {//meme chose si c'est le joueur 2
                couleur(KPlayer2);
                cout << kTokenPlayer2;
                couleur(KReset);
            } else if (Mat[i][j] == kMur) {//si l'élément est un obstacle
                cout << kMur;// afficher l'obstacle
            } else {
                cout << kEmpty;//sinon afficher le sol
            }
        }
        cout << "|" << endl;// on affiche un mur à la fin de la ligne de la matrice
    }
}
bool isTrap(CPosition & pos) {// fonction pour vérifier le joueur est tombé dans un piege ou pas
    return (pos.first == 2 && pos.second == 2) || (pos.first == 7 && pos.second == 7); // pièges aux positions (2, 2) et (7, 7)
}
CPosition movetokentorandom(CPosition & pos) {// Fonction de téléportation aléatoire
    pos.first = rand() % 10;
    pos.second = rand() % 10;
    return pos;
}
bool moveToken(CMatrix & Mat, char move, CPosition & pos, bool difficult) {//fonction pour deplacer les joueurs
    char joueur = Mat[pos.first][pos.second];
    Mat[pos.first][pos.second] = kEmpty;
    if (difficult && ((pos.first == 0 && pos.second == 1) ||// si c'est la version difficile et le joueur atteint un de ces cases
                      (pos.first == 4 && pos.second == 4) ||
                      (pos.first == 4 && pos.second == 7) ||
                      (pos.first == 9 && pos.second == 7))) {
        pos = movetokentorandom(pos); // Téléportation aléatoire
    } else {// Sinon deplacement normal
        switch (tolower(move)) {
        case 'z'://deplacement vers le haut
            if (pos.first > 0 && Mat[pos.first - 1][pos.second] != '#') pos.first--;
            break;
        case 's'://deplacement vers le bas
            if ((pos.first < Mat.size() - 1) && (Mat[pos.first + 1][pos.second] != '#')) pos.first++;
            break;
        case 'q':// deplacement vers la guauche
            if ((pos.second > 0) && (Mat[pos.first][pos.second - 1] != '#')) pos.second--;
            break;
        case 'd':// deplacement vers la droite
            if ((pos.second < Mat[0].size() - 1) && (Mat[pos.first][pos.second + 1] != '#')) pos.second++;
            break;
        }
    }
    if (difficult && isTrap(pos)) {// si c'est la version difficile et un des joueur est tombé dans le piège faire
        if (joueur == 'X') {
            cout << "Le joueur X est tombé dans un piège ! Le joueur O est le vainqueur !" << endl;
            return false; // Fin du jeu
        }
        if (joueur == 'O') {
            cout << "Le joueur O est tombé dans un piège ! Le joueur X est le vainqueur !" << endl;
            return false; // Fin du jeu
        }
    }
    Mat[pos.first][pos.second] = joueur; // Placer le joueur à la nouvelle position
    return true; // Le jeu continue
}
int ppal(bool difficult) {// Fonction principale
    srand(time(NULL));//generateur de nombres aléatoires
    CMatrix tableauDeJeu;//La matrice
    CPosition posPlayer1, posPlayer2;
    int nbColumn = 10;// nombre de colonnes
    int nbLine = 10;//nombre de lignes
    int nbToursMax = 100;//nombres de trours maximum
    initMat(tableauDeJeu, nbLine, nbColumn, posPlayer1, posPlayer2, difficult);//appel de la fonction qui nous permet d'initialiser la matrice
    showMatrix(tableauDeJeu);//appel de la fonction qui affiche la matrice
    int nbTours = 0;// initialisation des nombres des tours à 0
    bool gameRunning = true;// variable qui montre l'etat du jeux
    string mouvement;//variable pour stocker le mouvement du joueur
    while (nbTours != nbToursMax && posPlayer1 != posPlayer2 && gameRunning) {//tant que le nb de tours < nb de tous max et la positions des 2 joueurs est differentes et le jeu marche
        if (nbTours % 2 == 0) {
            couleur(KPlayer1);//changer la couleur du joueur 1 en rouge
            cout << "X C'EST A TOI!! : " << endl;// afficher que c'est le tour du joueur 1
            couleur(KReset);
            getline(cin, mouvement);// on prend le mouvement que l'utilisateur a fait entrer
            if (mouvement.size() == 1 && (mouvement == "z" || mouvement == "s" || mouvement == "q" || mouvement == "d")) {//il faut entrer que q ,s,z ou d
                gameRunning = moveToken(tableauDeJeu, mouvement[0], posPlayer1, difficult);//la variable gamerunning prend le resultat de la fonction movetoken
                if (!gameRunning) break;// le jeu s'arrete dans ce cas
            } else {
                cout << "Entrée invalide ! Utilise uniquement les touches Z, S, Q, D." << endl;// si l'utilisateur se trompe on affiche ce message
                continue;
            }
        } else {//meme chose pour le joueur 2
            couleur(KPlayer2);
            cout << "O C'EST A TOI!! : " << endl;
            couleur(KReset);
            getline(cin, mouvement);
            if (mouvement.size() == 1 && (mouvement == "z" || mouvement == "s" || mouvement == "q" || mouvement == "d")) {
                gameRunning = moveToken(tableauDeJeu, mouvement[0], posPlayer2, difficult);
                if (!gameRunning) break;
            } else {
                cout << "Entrée invalide ! Utilise uniquement les touches Z, S, Q, D." << endl;
                continue;
            }
        }
        nbTours++;// incrementation du nb de tours
        showMatrix(tableauDeJeu);//on affiche la matrice
    }
    if (posPlayer1 == posPlayer2) {//si les joueurs se croisent
        if (nbTours % 2 == 0) {
            cout << "O a gagné !" << endl;
        }
    else {
            cout << "X a gagné !" << endl;
        }
    }
    if (nbTours == 100) {
        cout << "Nombre de tours dépassé !, Vous avez perdu tous les deux HAHAHA (:" << endl;
    }
    return 0;
}
int main() {//programme principal
    int choix;// variable qui va contenir le choix de l'utilisateur
    cout << "Bienvenue dans le jeu! Choisissez la version:" << endl;
    cout << "1. Version Simple: sans pièges et téléportation" << endl;
    cout << "2. Version Difficile: avec pièges et téléportation" << endl;
    cout << "Entrez votre choix (1 ou 2): ";
    cin >> choix;
    cin.ignore();  // Pour ignorer le caractère de nouvelle ligne
    if (choix == 1) {
        ppal(false);// version simple
    } else if (choix == 2) {
        ppal(true);// version difficile
    } else {
        cout << "Choix invalide! Veuillez entrer 1 ou 2 SVP." << endl;
    }

    return 0;
}
