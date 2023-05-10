#include "Player.hpp"
#include "52Cards.hpp"
#include "PokerHand.hpp"
#include "Deck.hpp"
#include <map>
#include <iostream>
#include <iomanip>
// A simulator for the poker game.
// author: Quan Nguyen
using namespace std;

string printType(const PokerHand &pHand);

int countCard(set<Card> aSet, Card card);

int main() {
    cout << "How many Players?" << endl;
    string prompt;
    cin >> prompt;
    int playerCount = stoi(prompt);
    vector<Player> player;
    for (int i = 0; i < playerCount; i++) {
        Player a;
        player.push_back(a);
    }
    string continuePlay = "y";
    srand((int) time(nullptr));
    while (continuePlay == "y") {
        Deck aDeck;
        vector<Card> deck = aDeck.deck;
        set<Card> cardChosen;
        vector<Card> community;
        cout << "Community Cards: ";
        int comCount = 0;
        while (comCount < 5) {
            int index = rand() % (deck.size());
            if (countCard(cardChosen, deck[index]) == 0) {
                community.push_back(deck[index]);
                cardChosen.insert(deck[index]);
                cout << deck[index].toString() << " ";
                comCount++;
            }
        }
        for (int i = 0; i < playerCount; i++) {
            for (int j = 0; j < 5; j++) {
                player[i].addCard(community[j]);
            }
        }
        cout << endl;
        map<PokerHand const, vector<int>> largestEach;
        cout << "++++++++++++++++++++++++++++++++++++" << endl;
        cout << setprecision(2) << fixed;
        for (int i = 0; i < playerCount; i++) {
            int countCardNum = 0;
            cout << "Player " << i + 1 << ": $" << player[i].money - 2 << " - ";
            while (countCardNum < 2) {
                int index = rand() % (deck.size());
                if (countCard(cardChosen, deck[index]) == 0) {
                    player[i].addCard(deck[index]);
                    cardChosen.insert(deck[index]);
                    cout << deck[index].toString() << " ";
                    countCardNum++;
                }
            }
            cout << endl;
            PokerHand largest = player[i].getLargestHand();
            cout << "   Best Hand: " << largest.toString() << printType(largest) << endl;
            if (largestEach.count(largest) == 0) {
                vector<int> equal;
                largestEach.insert({largest, equal});
            }
            largestEach[largest].push_back(i);
            cout << endl;
        }
        map<int, PokerHand> winnerList;
        PokerHand winner = largestEach.rbegin()->first;
        for (auto i = largestEach.begin(); i != largestEach.end(); i++) {
            if (i->first == winner) {
                for (int winPlayer: i->second) {
                    winnerList.insert({winPlayer, i->first});
                }
            }
        }
        double moneyWin = 0;
        for (int j = 0; j < playerCount; j++) {
            if (winnerList.count(j) == 0) {
                player[j].money -= 2;
                moneyWin += 2;
            }
        }
        moneyWin = moneyWin / winnerList.size();
        for (auto i = winnerList.begin(); i != winnerList.end(); i++) {
            player[i->first].money += moneyWin;
        }
        if (winnerList.size() == 1) {
            cout << "Winner: Player " << winnerList.begin()->first + 1 << " $"
                 << player[winnerList.begin()->first].money << endl;
        } else {
            cout << "Winning Hand (tie) " << endl;
        }


        cout << "++++++++++++++++++++++++++++++++++++" << endl;
        if (winnerList.size() == 1) {
            cout << " " << winnerList.begin()->second.toString() << "   " << printType(winnerList.begin()->second)
                 << endl;
        } else {
            for (auto i = winnerList.begin(); i != winnerList.end(); i++) {
                cout << i->second.toString() << " " << printType(i->second) << " Player " << i->first + 1 << " $"
                     << player[i->first].money << endl;
            }
        }
        cout << "Play another game? <y or n> ";
        cin >> continuePlay;
        for (int i = 0; i < playerCount; i++) {
            player[i].clear();
        }

    }

}

int countCard(set<Card> aSet, Card card) {
    int count = 0;
    for (auto i = aSet.begin(); i != aSet.end(); i++) {
        if (card.getSuit() == i->getSuit() && card.getRank() == i->getRank()) {
            count++;
        }
    }
    return count;
}

string printType(const PokerHand &pHand) {
    string result;
    if (pHand.getHand() == HandRank::ROYAL) {
        result = "Royal";
    } else if (pHand.getHand() == HandRank::STRAIGHT_FLUSH) {
        result = "Straight Flush";
    } else if (pHand.getHand() == HandRank::FOUR) {
        result = "Four of a Kind";
    } else if (pHand.getHand() == HandRank::FULL) {
        result = "Full House";
    } else if (pHand.getHand() == HandRank::FLUSH) {
        result = "Flush";
    } else if (pHand.getHand() == HandRank::STRAIGHT) {
        result = "Straight";
    } else if (pHand.getHand() == HandRank::THREE_KIND) {
        result = "Three of a Kind";
    } else if (pHand.getHand() == HandRank::TWO_PAIR) {
        result = "Two Pair";
    } else if (pHand.getHand() == HandRank::PAIR) {
        result = "One Pair";
    } else {
        result = "High Card";
    }
    return result;
}

