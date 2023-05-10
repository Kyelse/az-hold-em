/*
 * Deck.hpp
 *
 *  Created on:
 *  Quan Nguyen
 */

#ifndef DECK
#define DECK

#include "52Cards.hpp"

class Deck {
public:
    std::vector<Card> deck;

    Deck() {
        deck.push_back(C2);
        deck.push_back(C3);
        deck.push_back(C4);
        deck.push_back(C5);
        deck.push_back(C6);
        deck.push_back(C7);
        deck.push_back(C8);
        deck.push_back(C9);
        deck.push_back(C10);
        deck.push_back(CJ);
        deck.push_back(CQ);
        deck.push_back(CK);
        deck.push_back(CA);

        deck.push_back(D2);
        deck.push_back(D3);
        deck.push_back(D4);
        deck.push_back(D5);
        deck.push_back(D6);
        deck.push_back(D7);
        deck.push_back(D8);
        deck.push_back(D9);
        deck.push_back(D10);
        deck.push_back(DJ);
        deck.push_back(DQ);
        deck.push_back(DK);
        deck.push_back(DA);

        deck.push_back(H2);
        deck.push_back(H3);
        deck.push_back(H4);
        deck.push_back(H5);
        deck.push_back(H6);
        deck.push_back(H7);
        deck.push_back(H8);
        deck.push_back(H9);
        deck.push_back(H10);
        deck.push_back(HJ);
        deck.push_back(HQ);
        deck.push_back(HK);
        deck.push_back(HA);

        deck.push_back(S2);
        deck.push_back(S3);
        deck.push_back(S4);
        deck.push_back(S5);
        deck.push_back(S6);
        deck.push_back(S7);
        deck.push_back(S8);
        deck.push_back(S9);
        deck.push_back(S10);
        deck.push_back(SJ);
        deck.push_back(SQ);
        deck.push_back(SK);
        deck.push_back(SA);
    }
};

#endif DECK
