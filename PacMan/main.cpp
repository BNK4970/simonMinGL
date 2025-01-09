/*!
 * \file   main.cpp
 * \authors Alain Casali, Marc Laporte
 * \date december 8 2016
 * \brief   Terminal's color management
 *          beginning of the project titled "catch me if you can"
 */

#define FPS_LIMIT 25

#include <iostream>
#include <vector>
#include <thread>
#include "mingl/mingl.h"
#include "mingl/shape/rectangle.h"

using namespace std;
nsGraphics::Vec2D rectPos1;
nsGraphics::Vec2D rectPos2;
/**
 * @brief main
 * @return return 0 iff everything is OK, 1 if we have an exception, 2 if we can't load the params' file
 */




void clavier1(MinGL &window, nsGraphics::Vec2D &joueur)
{
    // On vérifie si ZQSD est pressé, et met a jour la position
    if (window.isPressed({'z', false}))
        joueur.setY(joueur.getY() - 2);
    if (window.isPressed({'s', false}))
        joueur.setY(joueur.getY() + 2);
    if (window.isPressed({'q', false}))
        joueur.setX(joueur.getX() - 2);
    if (window.isPressed({'d', false}))
        joueur.setX(joueur.getX() + 2);
}

void clavier2(MinGL &window, nsGraphics::Vec2D &joueur)
{
    // On vérifie si IJKL est pressé, et met a jour la position
    if (window.isPressed({'i', false}))
        joueur.setY(joueur.getY() - 3);
    if (window.isPressed({'k', false}))
        joueur.setY(joueur.getY() + 3);
    if (window.isPressed({'j', false}))
        joueur.setX(joueur.getX() - 3);
    if (window.isPressed({'l', false}))
        joueur.setX(joueur.getX() + 3);
}

void dessiner(MinGL &window)
{
    // On dessine le rectangle
    window << nsShape::Rectangle(rectPos1, rectPos1 + nsGraphics::Vec2D(20, 20), nsGraphics::KCyan);
    window << nsShape::Rectangle(rectPos2, rectPos2 + nsGraphics::Vec2D(20, 20), nsGraphics::KRed);
}

void affichageMap(MinGL &window, vector<vector<int>> &Map) {
    for(size_t i (0); i<Map.size(); ++i) {
        for(size_t j (0); j<Map[i].size(); ++j) {
            switch(Map[i][j]) {
            case 0 :
                //On dessine les espaces vide
                window << nsShape::Rectangle(nsGraphics::Vec2D(i*20, j*20), nsGraphics::Vec2D((i*20)+20, (j*20)+20), nsGraphics::KBlack);
                break;
            case 1:
                //On dessine les murs
                window << nsShape::Rectangle(nsGraphics::Vec2D(i*20, j*20), nsGraphics::Vec2D((i*20)+20, (j*20)+20), nsGraphics::KGreen);
                break;
            }
        }
    }
}


int main()
{
    MinGL window("03 - Clavier", nsGraphics::Vec2D(640, 640), nsGraphics::Vec2D(128, 128), nsGraphics::KBlack);
    window.initGlut();
    window.initGraphic();

    // Variable qui tient le temps de frame
    chrono::microseconds frameTime = chrono::microseconds::zero();

    //On initialise la map

    vector<vector<int>> Map = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,1,1,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };

    // On fait tourner la boucle tant que la fenêtre est ouverte
    while (window.isOpen())
    {
        // Récupère l'heure actuelle
        chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();

        // On efface la fenêtre
        window.clearScreen();

        //On affiche la map
        affichageMap(window,Map);

        // On fait tourner les procédures
        clavier1(window,rectPos1);
        clavier2(window,rectPos2);
        dessiner(window);

        // On finit la frame en cours
        window.finishFrame();

        // On vide la queue d'évènements
        window.getEventManager().clearEvents();

        // On attend un peu pour limiter le framerate et soulager le CPU
        this_thread::sleep_for(chrono::milliseconds(1000 / FPS_LIMIT) - chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start));

        // On récupère le temps de frame
        frameTime = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    }

    return 0;
}



