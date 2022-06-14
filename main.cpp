#include "mainwindow.hh"
#include <QApplication>

/* Muistipeli
 *
 * Kuvaus:
 * Ohjelma toteuttaa graafisen muistipelin. Pelissä on vaihteleva määrä kortteja.
 * Korttien lukumäärää voi vaihdella muuttamalla const NUMBER_OF_CARDS:ia.
 * pelaajia. Pelin alussa käyttäjältä pelaajien nimet. Pelaajia on oltava
 * vähintään 2 kappaletta.
 * Kunnes vähintään kahden pelaajan nimi on annettu pelin voi
 * aloittaa joko painamalla start nappia tai kääntämällä korttia.
 *
 * Joka kierroksella vuorossa oleva pelaaja napauttaa hiirellä kahta korttia.
 *
 * Mikäli pari löytyy, lisätään pisteet pelaajalle, kortit katoaa ja
 * vuoro vaihtuu. Jos pareja ei löydy vuoro siirtyy seuraavalle.
 *
 * Rivin tai sarakkeen tyhjetessä korteista kortteja asetellaan lähemmäksi
 * toisiaan sekä keskemmälle pelilauttaa.
 *
 * Peli päättyy, kun kaikki parit on löydetty, ja pelilauta on tyhjä.
 * Tällöin pelin lopputilannetta voi tarkastella hetken ennenkuin ohjelma
 * sammuu.
 *
 * LISÄOMINAISUUKSIA
 * 1. Pelissä on vaihteleva määrä pelaajia.(10p)
 * 2. Pelaaja voi antaa pelaajille nimet (5p)
 * 5. Pelin aikana kerrotaan siihen käytetty aika(10p.)
 *
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Niko Korhonen
 * Opiskelijanumero: K443740
 * Käyttäjätunnus: sfniko
 * E-Mail: niko.korhonen@tuni.fi
 *
 *
 *
 * */

#include <player.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}