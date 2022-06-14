/* Luokka: Player
 * --------------
 * Kuvaa yhtä pelaajaa muistipelissä.
 *
 * COMP.CS.110 K2021
 *
 * Ohjelman kirjoittaja
 * Nimi: Niko Korhonen
 * Opiskelijanumero: K443740
 * Käyttäjätunnus: sfniko
 * E-Mail: niko.korhonen@tuni.fi
 */

#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>


class Player
{
public:
    // Rakentaja: luo annetun nimisen pelaajan.
    //
    // Constructor: creates a player with the given name.
    Player(const std::string& name);

    // Palauttaa pelaajan nimen.
    //
    // Returns the name of the player.
    std::string get_name() const;

    // Palauttaa pelaajan tähän asti keräämien parien määrän.
    //
    // Returns the number of pairs collected by the player so far.
    unsigned int number_of_pairs() const;

    // Siirtää annetun kortin pelilaudalta pelaajalle,
    // eli lisää kortin pelaajan keräämiin kortteihin
    // ja poistaa sen pelilaudalta.
    //
    // Moves the given card from the game board for the player,
    // i.e. inserts it to the collected cards of the player and
    // removes it from the game board.
    void add_card();

    // Tulostaa pelaajan tilanteen: nimen ja tähän asti kerättyjen parien määrän.
    //
    // Prints the game status of the player: name and collected pairs so far.
    void print() const;

private:
    // Pelaajan nimi
    std::string name_;
    // Kerätyt parit
    unsigned int pairs_ = 0;

};

#endif // PLAYER_HH
