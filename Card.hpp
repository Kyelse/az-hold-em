/*
 * File Name Card.hpp
 *
 * Description: class Card represents an object with a suit and rank
 * The toString member function given shows a graphical representation
 * of a card. When sorted, a vector<card> has all cards sorted using getValue()
 * that returns the rank as an integer from 2 (DEUCE) through 14 (ACE).
 *
 * Author Rick Mercer and Quan Nguyen
 *
 */
#ifndef CARD
#define CARD

#include <string>
#include <vector>
#include <iostream>

// TODO: Implement scoped enum class Rank where DEUCE = 2 and ACE = 14
enum class Rank {
    DEUCE = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
};
// TODO: Implement scoped enum class Suit where CLUBS=3, DIAMONDS=2, HEARTS=1, SPADES=0
enum class Suit {
    CLUBS = 3,
    DIAMONDS = 2,
    HEARTS = 1,
    SPADES = 0
};

class Card {
private:
    Rank rank;
    Suit suit;
public:
    // TODO: Need a constructor and other methods to compile and pass the given assertions
    inline Card(Rank cardRank, Suit suitRank) {
        rank = cardRank;
        suit = suitRank;
    }

    Card() {
    }

    // TODO: Add the methods specified as a catch test.
    Rank getRank() const {
        return rank;
    }

    Suit getSuit() const {
        return suit;
    }

    int getValue() const {
        return static_cast<int>(rank);
    }

    bool operator<(const Card &lhs) const {
        if (this->getValue() < lhs.getValue()) {
            return true;
        }
        return false;
    }

    bool operator==(const Card &lhs) const {
        if (this->getValue() == lhs.getValue() && (this->getSuit() == lhs.getSuit())) {
            return true;
        }
        return false;
    }

    bool operator!=(const Card &lhs) const {
        if (this->getValue() != lhs.getValue()) {
            return true;
        }
        return false;
    }

    bool operator>(const Card &lhs) const {
        if (this->getValue() > lhs.getValue()) {
            return true;
        }
        return false;
    }


    // This Card toString() member function is provided so we don't have to explain many unnecessary concepts
    std::string toString() const {
        std::vector<std::string> suits{"\xe2\x99\xa0", "\xe2\x99\xa5", "\xe2\x99\xa6", "\xe2\x99\xa3"};
        std::vector<std::string> face{"2", "3", "4", "5", "6", "7", "8",
                                      "9", "10", "J", "Q", "K", "A"};

        return face.at(static_cast<int>(rank) - 2)
               + suits.at(static_cast<int>(suit));
    }
};

#endif