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


#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <player.hh>
#include <QGridLayout>
#include <QTimer>
#include<QString>
#include <algorithm>

const int TIMER_TIME = 1500;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      timer(new QTimer(this))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    calculate_factors();
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::start_game);
    make_card_table();

    connect(timer, &QTimer::timeout, this, &MainWindow::timer_timeout);

}

// Ajastimen toiminta
void MainWindow::timer_timeout()
{
    int current_mins = ui->lcdNumberMin->intValue();
    int current_secs = ui->lcdNumberSec->intValue();
    ui->lcdNumberMin->setPalette(Qt::red);
    ui->lcdNumberSec->setPalette(Qt::red);

    if (current_secs == 59)
    {
        ui->lcdNumberMin->display(current_mins + 1);
        ui->lcdNumberSec->display(0);
    }
    else
    {
        ui->lcdNumberSec->display(current_secs + 1);
    }

}

// Lopettaa ohjelman
void MainWindow::end_game()
{
    QApplication::exit();
}

// Purkaja
MainWindow::~MainWindow()
{
    for (unsigned int i = 0; i < cards_.size(); ++i)
    {
        delete cards_[i];
    }
    delete timer;
    delete ui;
}

// Toiminnallisuus kortin painamiselle. Tarkastaa tuliko pari
// ja lisää pisteet pelaajille
void MainWindow::cardClick()
{
    if (players.size() > 1)
    {
        // Jos peli aloitettiin kääntämällä kortteja
        // eikä start buttonilla.
        if (count_ == 0)
        {
            start_game();
            ++count_;
        }

        // Käännetään painettu kortti
        QPushButton* pressed_button = static_cast<QPushButton*>(sender());
        pressed_button_ = pressed_button;
        pressed_button->setStyleSheet("background-color: red");

        // Jos painettu kortti on sama kuin edellinen
        if (pressed_button == last_pressed_)
        {
            return;
        }
        // Jos yksi kortti on käännettynä.
        if (last_pressed_ != nullptr)
        {
            // Jos pari löytyi. Lisätään pisteet ja poistetaan kortit.
            if (pressed_button->text() == last_pressed_->text())
            {
                disable_all();
                players[in_turn_].add_card();
                ++total_points_;
                print();
                QTimer::singleShot(TIMER_TIME,this,SLOT(hide_pair()));
                return;

            }
            // Jos paria ei löytynyt piilotetaan kortit uudestaan
            // ja vuoro vaihtuu
            else
            {
                in_turn();
                disable_all();
                QTimer::singleShot(TIMER_TIME,this,SLOT(pair_not_found()));

                ui->in_turnO->setText(QString::fromStdString
                                      (players[in_turn_].get_name()));

            }
        }
        else
        {
            last_pressed_ = pressed_button;
        }
    }
}
// Poistetaan löydetty pari. Tarkastetaan myös onko peli loppunut.
void MainWindow::hide_pair()
{
    pressed_button_->hide();
    last_pressed_->hide();
    last_pressed_ = nullptr;
    is_game_over();
    enable_all();

}

// Vaihdetaan vuoro seuraavalle.
void MainWindow::in_turn()
{
    if (in_turn_ == players.size() - 1)
    {
        in_turn_ = 0;
    }
    else
    {
        ++in_turn_;
    }
}

// Piilotetaan kortit kun ei paria.
void MainWindow::pair_not_found()
{
    pressed_button_->setStyleSheet("background-color: black");
    last_pressed_->setStyleSheet("background-color: black");
    pressed_button_ = nullptr;
    last_pressed_ = nullptr;
    enable_all();
}

// Luodaan kortit ja asetellaan ne pelialustalle.
void MainWindow::make_card_table()
{
    // Luodaan kortit ja sekoitetaan ne.
    QString alphas = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQRRSSTTUUVVWWZZXX";
    alphas = alphas.left(NUMBER_OF_CARDS);
    std::random_shuffle(std::begin(alphas), std::end(alphas));
    int index = 0;

    // Luodaan painikkeet
    for(int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < columns_; ++j)
        {

            QPushButton* pushButton = new QPushButton(alphas.at(index), this);
            pushButton->setFixedSize(DISPLAY_WIDTH, DISPLAY_HEIGTH);
            pushButton->setStyleSheet("background-color: black;");

            cards_.push_back(pushButton);
            ui->gridLayout->addWidget(pushButton, i, j);
            ++index;

            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::cardClick);
        }
    }
}

// Poistetaan kortit käytöstä
void MainWindow::disable_all()
{
    for (unsigned int i = 0; i < cards_.size(); ++i)
    {
        if (cards_[i] != pressed_button_ && cards_[i] != last_pressed_)
        {

            cards_[i]->setEnabled(false);
            cards_[i]->setStyleSheet(
                {"background-color: black; color: black;"});
        }
        else
        {
            cards_[i]->setEnabled(false);
            cards_[i]->setStyleSheet(
                {"background-color: red; color: black;"});
        }
    }
}

// Asetetaan kortit takaisin käyttöön.
void MainWindow::enable_all()
{
    for (unsigned int i = 0; i < cards_.size(); ++i)
    {
        cards_[i]->setEnabled(true);
    }
}

// Tulostetaan pelaajat ja heidän pisteet.
void MainWindow::print()
{
    QString text = "";
    std::map<QString, int>::iterator it;
    for ( auto& it : players)
    {
        text.append(QString::fromStdString(it.get_name())
                    + ": " + QString::number(it.number_of_pairs()) + "\n");
    }
    ui->textBrowser->setText(text);

}

// Aloitetaan peli ja ajastin.
void MainWindow::start_game()
{
    if (players.size() > 1)
    {
        timer->start(1000);
        ui->startButton->setEnabled(false);
        ui->in_turnO->setText(QString::fromStdString
                              (players[in_turn_].get_name()));
        ui->lineEdit->setDisabled(true);
        ++count_;
    }
}

// Toiminnallisuus syötettävälle tekstikentälle.
void MainWindow::on_lineEdit_returnPressed()
{
    players.push_back(ui->lineEdit->text().toStdString());
    print();
    ui->lineEdit->clear();
}

// Lasketaan rivien ja sarakkeiden määrä.
void MainWindow::calculate_factors()
{

    for(int i = 1; i * i <= NUMBER_OF_CARDS; ++i)
    {
        if(NUMBER_OF_CARDS % i == 0)
        {
            rows_ = i;
        }
    }
    columns_ = NUMBER_OF_CARDS / rows_;
}

// Tarkastetaan onko peli loppunut. Jos on
// niin lopetetaan ohjelma.

void MainWindow::is_game_over()
{
    if (total_points_ == NUMBER_OF_CARDS / 2)
    {
        ui->in_turnO->setText("GAME OVER");
        timer->stop();
        QTimer::singleShot(TIMER_TIME*2,this,SLOT(end_game()));
        print();

    }
}

