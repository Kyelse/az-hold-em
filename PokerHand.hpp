#ifndef POKER_HAND
#define POKER_HAND

#include <set>
#include <algorithm>
#include<vector>
#include"Card.hpp"

/*
 * File Name PokerHand.hpp
 *
 * Description: The Poker which represent a hand
 *
 * Author: Quan Nguyen
 *
 */


enum class HandRank {
    HIGH = 1,
    PAIR = 2,
    TWO_PAIR = 3,
    THREE_KIND = 4,
    STRAIGHT = 5,
    FLUSH = 6,
    FULL = 7,
    FOUR = 8,
    STRAIGHT_FLUSH = 9,
    ROYAL = 10
};
enum class Compare {
    LESS = 1,
    EQUAL = 2,
    MORE = 3
};

class PokerHand {
private:
    std::vector<Card> hands;


public:
    struct greater {
        template<class T>
        bool operator()(T const &a, T const &b) const { return a > b; }
    };

    PokerHand(Card c1, Card c2, Card c3, Card c4, Card c5) {
        hands.push_back(c1);
        hands.push_back(c2);
        hands.push_back(c3);
        hands.push_back(c4);
        hands.push_back(c5);
        sort(hands.begin(), hands.end(), greater());
    }


    bool operator<(const PokerHand &lhs) const {
        if (this->getHand() < lhs.getHand()) {
            return true;
        }
        if (this->getHand() > lhs.getHand()) {
            return false;
        }
        // equal hand case, separate
        Compare result;
        if (this->getHand() == HandRank::ROYAL) {
            result = royal_compare(*this, lhs);
        } else if (this->getHand() == HandRank::STRAIGHT_FLUSH) {
            result = straight_flush_compare(*this, lhs);
        } else if (this->getHand() == HandRank::FOUR) {
            result = four_compare(*this, lhs);
        } else if (this->getHand() == HandRank::FULL) {
            result = full_compare(*this, lhs);
        } else if (this->getHand() == HandRank::FLUSH) {
            result = flush_hand_compare(*this, lhs);
        } else if (this->getHand() == HandRank::STRAIGHT) {
            result = straight_hand_compare(*this, lhs);
        } else if (this->getHand() == HandRank::THREE_KIND) {
            result = three_kind_compare(*this, lhs);
        } else if (this->getHand() == HandRank::TWO_PAIR) {
            result = two_pair_compare(*this, lhs);
        } else if (this->getHand() == HandRank::PAIR) {
            result = one_pair_compare(*this, lhs);
        } else {
            result = high_compare(*this, lhs);
        }
        return result == Compare::LESS;
    }

    std::string toString() const {
        std::string toPrint;
        for (int i = 0; i < 5; i++) {
            toPrint += hands[i].toString() + " ";
        }
        return toPrint;
    }

    bool royal() const {
        if (straight_flush()) {
            if (hands[0].getRank() == Rank::ACE && hands[1].getRank() == Rank::KING) {
                return true;
            }
        }
        return false;
    }

    bool straight_flush() const {
        if (this->flush_hand() && this->straight_hand()) {
            return true;
        }
        return false;
    }

    bool four() const {
        int matches = 0;
        std::set<int> allFound;
        for (int i = 0; i < 5; i++) {
            int currentCardRank = hands[i].getValue();
            if (countCard(currentCardRank) == 4) {
                return true;
            }
        }
        return false;
    }

    bool full() const {
        // x-x-x-y-y
        if (hands[0].getValue() == hands[1].getValue() && hands[1].getValue() == hands[2].getValue()) {
            if (hands[3].getValue() == hands[4].getValue()) {
                return true;
            }
        }
        //x-x-y-y-y
        if (hands[0].getValue() == hands[1].getValue()) {
            if (hands[2].getValue() == hands[3].getValue() && hands[3].getValue() == hands[4].getValue()) {
                return true;
            }
        }
        return false;
    }

    bool flush_hand() const {
        Suit suit = hands[0].getSuit();
        for (int i = 0; i < 5; i++) {
            if (hands[i].getSuit() != suit) {
                return false;
            }
        }
        return true;
    }

    bool straight_hand() const {
        if (hands[0].getRank() == Rank::ACE) {
            if (hands[4].getRank() == Rank::DEUCE && hands[3].getRank() == Rank::THREE &&
                hands[2].getRank() == Rank::FOUR && hands[1].getRank() == Rank::FIVE) {
                return true;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (hands[i].getValue() - hands[i + 1].getValue() != 1) {
                return false;
            }
        }
        return true;
    }

    bool three_kind() const {
        int matches = 0;
        std::set<int> allFound;
        for (int i = 0; i < 5; i++) {
            int currentCardRank = hands[i].getValue();
            if (countCard(currentCardRank) == 3 && allFound.count(currentCardRank) == 0) {
                matches++;
                allFound.insert(currentCardRank);
            }
        }
        if (matches == 1) { // one three kinds
            return true;
        }
        return false;
    }

    bool two_pair() const {
        int matches = 0;
        std::set<int> allFound;
        for (int i = 0; i < 5; i++) {
            int currentCardRank = hands[i].getValue();
            if (countCard(currentCardRank) == 2 && allFound.count(currentCardRank) == 0) {
                matches++;
                allFound.insert(currentCardRank);
            }
        }
        if (matches == 2) { // two pair in the card
            return true;
        }
        return false;
    }

    bool one_pair() const {
        int matches = 0;
        std::set<int> allFound;
        for (int i = 0; i < 5; i++) {
            int currentCardRank = hands[i].getValue();
            if (countCard(currentCardRank) == 2 && allFound.count(currentCardRank) == 0) {
                matches++;
                allFound.insert(currentCardRank);
            }
        }
        if (matches == 1) { // one pair in the card
            return true;
        }
        return false;
    }

    HandRank getHand() const {
        if (royal()) {
            return HandRank::ROYAL;
        } else if (straight_flush()) {
            return HandRank::STRAIGHT_FLUSH;
        } else if (four()) {
            return HandRank::FOUR;
        } else if (full()) {
            return HandRank::FULL;
        } else if (flush_hand()) {
            return HandRank::FLUSH;
        } else if (straight_hand()) {
            return HandRank::STRAIGHT;
        } else if (three_kind()) {
            return HandRank::THREE_KIND;
        } else if (two_pair()) {
            return HandRank::TWO_PAIR;
        } else if (one_pair()) {
            return HandRank::PAIR;
        } else return HandRank::HIGH;
    }

    Compare high_compare(const PokerHand &pHand, const PokerHand &hand) const {
        for (int i = 0; i < 5; i++) {
            if (pHand.getCard(i).getValue() < hand.getCard(i).getValue()) {
                return Compare::LESS;
            } else if (pHand.getCard(i).getValue() > hand.getCard(i).getValue()) {
                return Compare::MORE;
            }
        }
        return Compare::EQUAL;
    }

    int countCard(int rankVal) const {
        int matches = 0;
        for (int i = 0; i < 5; i++) {
            if (hands[i].getValue() == rankVal) {
                matches++;
            }
        }
        return matches;
    }

    Compare one_pair_compare(const PokerHand &pHand, const PokerHand &hand) const {
        // here, we know that we do have one pair only
        Rank pHandPair;
        Rank handPair;
        for (int i = 0; i < 5; i++) {
            int pHandNow = pHand.getCard(i).getValue();
            int handNow = hand.getCard(i).getValue();
            if (pHand.countCard(pHandNow) == 2) {
                pHandPair = pHand.getCard(i).getRank();
            }
            if (hand.countCard(handNow) == 2) {
                handPair = hand.getCard(i).getRank();
            }
        }
        if (pHandPair < handPair) {
            return Compare::LESS;
        } else if (pHandPair > handPair) {
            return Compare::MORE;
        }
        // same rank

        for (int i = 0; i < 5; i++) {
            if (pHand.getCard(i).getRank() == pHandPair) {
                continue;
            }
            if (pHand.getCard(i).getRank() < hand.getCard(i).getRank()) {
                return Compare::LESS;
            } else if (pHand.getCard(i).getRank() > hand.getCard(i).getRank()) {
                return Compare::MORE;
            }
        }
        return Compare::EQUAL;
    }

    Compare two_pair_compare(const PokerHand &pHand, const PokerHand &hand) const {
        Card pHandPair1;
        Card handPair1;
        for (int i = 0; i < 5; i++) {
            Card pHandNow = pHand.getCard(i);
            if (pHand.countCard(pHandNow.getValue()) == 2) {
                pHandPair1 = pHand.getCard(i);
                break;
            }
        }
        for (int i = 0; i < 5; i++) {
            Card handNow = hand.getCard(i);
            if (hand.countCard(handNow.getValue()) == 2) {
                handPair1 = hand.getCard(i);
                break;
            }
        }
        Card pHandPair2;
        Card handPair2;
        for (int i = 0; i < 5; i++) {
            Card pHandNow = pHand.getCard(i);
            Card handNow = hand.getCard(i);
            if (pHand.countCard(pHandNow.getValue()) == 2 && pHandPair1 != pHandNow) {
                pHandPair2 = pHand.getCard(i);
            }
            if (hand.countCard(handNow.getValue()) == 2 && handPair1 != handNow) {
                handPair2 = hand.getCard(i);
            }
        }
        Compare handCom = compareTwo(std::vector<Card>{pHandPair1, pHandPair2},
                                     std::vector<Card>{handPair1, handPair2});
        if (handCom != Compare::EQUAL) {
            return handCom;
        }
        Card pHandPairLeft;
        Card handPairLeft;
        for (int i = 0; i < 5; i++) {
            Card pHandNow = pHand.getCard(i);
            Card handNow = hand.getCard(i);
            if (pHand.countCard(pHandNow.getValue()) == 1) {
                pHandPairLeft = pHand.getCard(i);
            }
            if (hand.countCard(handNow.getValue()) == 1) {
                handPairLeft = hand.getCard(i);
            }
        }
        if (pHandPairLeft < handPairLeft) {
            return Compare::LESS;
        } else if (pHandPairLeft > handPairLeft) {
            return Compare::MORE;
        }
        return Compare::EQUAL;
    }

    Compare three_kind_compare(const PokerHand &pHand, const PokerHand &hand) const {
        Card pHandTrip;
        Card handTrip;
        for (int i = 0; i < 5; i++) {
            Card pHandNow = pHand.getCard(i);
            if (pHand.countCard(pHandNow.getValue()) == 3) {
                pHandTrip = pHand.getCard(i);
                break;
            }
        }
        for (int i = 0; i < 5; i++) {
            Card handNow = hand.getCard(i);
            if (hand.countCard(handNow.getValue()) == 3) {
                handTrip = hand.getCard(i);
                break;
            }
        }
        if (pHandTrip < handTrip) {
            return Compare::LESS;
        } else if (pHandTrip > handTrip) {
            return Compare::MORE;
        }
        std::vector<Card> pHandLeft = pHand.removeAll(std::vector<Card>{pHandTrip});
        std::vector<Card> handLeft = hand.removeAll(std::vector<Card>{handTrip});

        return compareTwo(pHandLeft, handLeft);
    }

    std::vector<Card> removeAll(std::vector<Card> val) const {
        std::vector<Card> result;
        for (int i = 0; i < 5; i++) {
            for (Card card: val) {
                if (hands[i].getValue() != card.getValue()) {
                    result.push_back(hands[i]);
                }
            }
        }

        return result;
    }

    Compare compareTwo(const std::vector<Card> &pHand, const std::vector<Card> &hand) const {
        for (int i = 0; i < pHand.size(); i++) {
            if (pHand[i] < hand[i]) {
                return Compare::LESS;
            } else if (pHand[i] > hand[i]) {
                return Compare::MORE;
            }
        }

        return Compare::EQUAL;
    }

    Compare straight_hand_compare(const PokerHand &pHand, const PokerHand &hand) const {
        Card pHandHigh = pHand.getCard(0);
        Card handHigh = hand.getCard(0);
        if (pHandHigh.getRank() == Rank::ACE) {
            if (pHand.getCard(1).getRank() == Rank::FIVE) {
                if (hand.getCard(1).getRank() == Rank::FIVE && pHandHigh == handHigh) {
                    return Compare::EQUAL;
                } else { // since this is the lowest
                    return Compare::LESS;
                }
            }
        }
        if (pHandHigh < handHigh) {
            if (handHigh.getRank() == Rank::ACE) {
                if (hand.getCard(1).getRank() == Rank::FIVE) {
                    if (pHand.getCard(1).getRank() == Rank::FIVE && pHandHigh == handHigh) {
                        return Compare::EQUAL;
                    } else { // since this is the lowest
                        return Compare::MORE;
                    }
                }
            }
            return Compare::LESS;
        } else if (pHandHigh > handHigh) {
            return Compare::MORE;
        }
        return Compare::EQUAL;
    }

    Compare flush_hand_compare(const PokerHand &pHand, const PokerHand &hand) const {
        return high_compare(pHand, hand);
    }

    Compare full_compare(const PokerHand &pHand, const PokerHand &hand) const {
        return three_kind_compare(pHand, hand);
    }

    Compare four_compare(const PokerHand &pHand, const PokerHand &hand) const {
        Card pHandFour;
        Card handFour;
        for (int i = 0; i < 5; i++) {
            Card pHandNow = pHand.getCard(i);
            if (pHand.countCard(pHandNow.getValue()) == 4) {
                pHandFour = pHand.getCard(i);
                break;
            }
        }
        for (int i = 0; i < 5; i++) {
            Card handNow = hand.getCard(i);
            if (hand.countCard(handNow.getValue()) == 4) {
                handFour = hand.getCard(i);
                break;
            }
        }
        if (pHandFour < handFour) {
            return Compare::LESS;
        } else if (pHandFour > handFour) {
            return Compare::MORE;
        }
        std::vector<Card> pHandLeft = pHand.removeAll(std::vector<Card>{pHandFour});
        std::vector<Card> handLeft = hand.removeAll(std::vector<Card>{handFour});

        return compareTwo(pHandLeft, handLeft);
    }

    Compare straight_flush_compare(const PokerHand &pHand, const PokerHand &hand) const {
        return straight_hand_compare(pHand, hand);
    }

    Compare royal_compare(const PokerHand &pHand, const PokerHand &hand) const {
        return Compare::MORE;
    }

    Card getCard(int i) const {
        return hands[i];
    }

    bool operator==(const PokerHand &lhs) const {
        if (this->getHand() < lhs.getHand()) {
            return false;
        }
        if (this->getHand() > lhs.getHand()) {
            return false;
        }
        // equal hand case, separate
        Compare result;
        if (this->getHand() == HandRank::ROYAL) {
            result = royal_compare(*this, lhs);
        } else if (this->getHand() == HandRank::STRAIGHT_FLUSH) {
            result = straight_flush_compare(*this, lhs);
        } else if (this->getHand() == HandRank::FOUR) {
            result = four_compare(*this, lhs);
        } else if (this->getHand() == HandRank::FULL) {
            result = full_compare(*this, lhs);
        } else if (this->getHand() == HandRank::FLUSH) {
            result = flush_hand_compare(*this, lhs);
        } else if (this->getHand() == HandRank::STRAIGHT) {
            result = straight_hand_compare(*this, lhs);
        } else if (this->getHand() == HandRank::THREE_KIND) {
            result = three_kind_compare(*this, lhs);
        } else if (this->getHand() == HandRank::TWO_PAIR) {
            result = two_pair_compare(*this, lhs);
        } else if (this->getHand() == HandRank::PAIR) {
            result = one_pair_compare(*this, lhs);
        } else {
            result = high_compare(*this, lhs);
        }
        return result == Compare::EQUAL;
    }

};

#endif