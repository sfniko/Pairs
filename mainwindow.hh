 /*
 * Ohjelman kirjoittaja
 * Nimi: Niko Korhonen
 * Opiskelijanumero: K443740
 * Käyttäjätunnus: sfniko
 * E-Mail: niko.korhonen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>
#include <player.hh>

using Players_type = std::vector<Player>;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer* timer;

private slots:
    void cardClick();
    void pair_not_found();
    void hide_pair();
    void timer_timeout();
    void end_game();

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;


    // Korttien lukumäärä. On oltava parillinen luku.
    // Maksimimäärä 50.
    const int NUMBER_OF_CARDS = 8;


    // Korttien koko
    const int DISPLAY_WIDTH = 50;
    const int DISPLAY_HEIGTH = 70;

    // Kortit
    std::vector<QPushButton*> cards_;

    // Vuorossa olevan pelaajan indeksi
    unsigned int in_turn_ = 0;

    // Pelaajien oliot vektorissa
    Players_type players;

    // Pointterit painettuun ja edeltävään korttiin.
    QPushButton* last_pressed_ = nullptr;
    QPushButton* pressed_button_ = nullptr;

    // Luo kortit gridiin
    void make_card_table();
    // Muuttaa pelaajan indexiä
    void in_turn();
    // Asettaa kortit käyttökelvottomiksi
    void disable_all();
    // Aktivoi kortit
    void enable_all();
    // Tulostaa pelaajat ja parien määrän.
    void print();
    // Aloittaa pelin ja ajastimen
    void start_game();
    // Laskee annettujen korttien mukaan rivit ja sarakkeet
    void calculate_factors();
    // Tarkastaa onko peli jo loppu
    void is_game_over();
    // Tieto siitä onko ensimmäinen kierros
    int count_ = 0;
    // Kaikkien pelaajien pisteet yhteensä
    int total_points_ = 0;

    int rows_;
    int columns_;





};
#endif // MAINWINDOW_HH
