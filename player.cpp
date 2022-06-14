 /* Ohjelman kirjoittaja
 * Nimi: Niko Korhonen
 * Opiskelijanumero: K443740
 * Käyttäjätunnus: sfniko
 * E-Mail: niko.korhonen@tuni.fi
 */

#include "player.hh"
#include <iostream>


Player::Player(const std::string& name):
    name_(name)
{

}

std::string Player::get_name() const
{
    return name_;
}

unsigned int Player::number_of_pairs() const
{
    return pairs_;
}

void Player::add_card()
{
    pairs_ += 1;

}

void Player::print() const
{
    std::cout << "*** " << name_ << " has " << pairs_ << std::endl;
}
