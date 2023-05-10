#ifndef PLAYER
#define PLAYER

#include<vector>
#include"Card.hpp"
#include"PokerHand.hpp"

/*
 * File Name Player.hpp
 *
 * Description: Representing a player
 *
 * Author: Quan Nguyen
 *
 */
class Player {
private:
    std::vector<Card> hand;
    std::vector<PokerHand> allCombination;
    std::vector<Card> data;

public:
    double money;

    Player() {
        money = 100;
    }

    void addCard(Card card) {
        hand.push_back(card);
    }

    void clear() {
        data.clear();
        allCombination.clear();
        hand.clear();
    }

    std::vector<PokerHand> getAllPossibleHands() {
        if (allCombination.size() == 21) {
            sort(allCombination.begin(), allCombination.end());
            return allCombination;
        }
        Card temp[hand.size()];
        getPossibleUtil(0, hand.size() - 1, 0);
        sort(allCombination.begin(), allCombination.end());
        return allCombination;
    }

    PokerHand getLargestHand() {
        getAllPossibleHands();
        return allCombination[allCombination.size() - 1];
    }

    void getPossibleUtil(int start, int end, int index) {
        if (index == 5) {
            PokerHand a(data[0], data[1], data[2], data[3], data[4]);
            allCombination.push_back(a);
            return;
        }
        for (int i = start; i <= end &&
                            end - i + 1 >= 5 - index; i++) {
            if (index >= data.size()) {
                data.push_back(hand[i]);
            }
            data[index] = hand[i];
            getPossibleUtil(i + 1, end, index + 1);
        }
    }
};

#endif