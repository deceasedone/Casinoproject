/*==============================================================
        ==>>>BACCARAT - Casino Number Game<<<==
Baccarat is a popular casino card game that is played between
two hands: the player and the banker. The goal of the game is
to predict which hand will have a higher value: the player's
hand, the banker's hand, or a tie. The values of the cards are
calculated by adding up their face values, with the Ace being
worth 1, and face cards and tens worth 0. The hand closest to
a total of 9 wins. Baccarat is known for its simplicity and
fast-paced gameplay, making it a favorite among both beginners
                and experienced gamblers.
================================================================*/
#include <iostream>
#include <ctime>
#include <string>
#include <limits>
using namespace std;

class Card {
private:
    int num1;
    int num2;
    int extraCard;
    int sum;

public:
    Card() {
        num1 = 0;
        num2 = 0;
        extraCard = 0;
        sum = 0;
    }

    void setcard(int n1, int n2, int extra) {
        num1 = n1;
        num2 = n2;
        extraCard = extra;
        sum = (num1 + num2 + extraCard) % 10;
    }

    int getSum() {
        return sum;
    }

    void printCard1() {
        cout << "=======\n";
        cout << "|     |\n";
        cout << "|  " << sum << "  |\n";
        cout << "|     |\n";
        cout << "=======\n";

        cout << "First Card: " << num1 << "\n";
        cout << "Second Card: " << num2 << "\n";
        cout << "Extra Card: " << extraCard << "\n";
    }

    void printCard2() {
        cout << "=======\n";
        cout << "|     |\n";
        cout << "|  " << sum << "  |\n";
        cout << "|     |\n";
        cout << "=======\n";

        cout << "This is a natural win 8/9 \n";
        cout << "First Card: " << num1 << "\n";
        cout << "Second Card: " << num2 << "\n";
    }
};

class Baccarat {
private:
    string name;
    int bet;
    int decision;
    int winner;
    int prize;
    char play;
    bool logic;
    int money;

public:
    Baccarat() {
        name = "";
        bet = 0;
        decision = 0;
        winner = 0;
        prize = 0;
        play = ' ';
        logic = true;
        money = 10000;
    }

    void startGame() {
        system("Color 4F");
        srand(time(NULL));

        cout << "==============================" << endl;
        cout << "Welcome, Please enter your name" << endl;

        cout << "Enter your name: ";
        getline(cin, name);

        cout << "\nGood evening, " << name << endl;
        cout << "==============================\n\n";
        cout << "WELCOME TO VIRTUAL BACCARAT TABLE" << endl;
        cout << "=================================" << endl;

        do {
            cout << "Current balance, INR " << money << endl;
            cout << "1 - BANKER\n2 - PLAYER\n";
            cout << "Choose your bet: ";

            while (!(cin >> decision) || (decision < 1 || decision > 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Choose your bet: ";
                cout << "\n1 - BANKER\n2 - PLAYER\n";
            }

            do {
                cout << "Place your bet, INR: ";
                cin >> bet;
            } while (bet > money);

            playGame();

            cout << "Current Money, INR " << money << "\n\n";

            cout << "Play Again? Y/N ";
            cin >> play;
            logic = playAgain(play, money);

        } while (logic);
    }

    void playGame() {
        Card bankcard;
        Card playcard;

        cout << "\n==============================\n";
        cout << "      = BANKER'S CARD  =\n";
        cout << "==============================\n";

        bankcard.setcard(rand() % 10 + 1, rand() % 10 + 1, 0);
        if (bankcard.getSum() != 9 && bankcard.getSum() != 8) {
            bankcard.setcard(bankcard.getSum(), bankcard.getSum(), rand() % 10 + 1);
            bankcard.printCard1();
        } else {
            bankcard.printCard2();
        }

        cout << "\n==============================\n";
        cout << "      = PLAYER'S CARD =\n";
        cout << "==============================\n";

        playcard.setcard(rand() % 10 + 1, rand() % 10 + 1, 0);
        if (playcard.getSum() != 9 && playcard.getSum() != 8) {
            playcard.setcard(playcard.getSum(), playcard.getSum(), rand() % 10 + 1);
            playcard.printCard1();
        } else {
            playcard.printCard2();
        }

        winner = winnerFunction(bankcard.getSum(), playcard.getSum());
        prize = declareWinner(winner, decision, bet);
        cout << "INR " << prize << endl;
        money += prize;
    }

    bool playAgain(char x, int money) {
        if (money > 0) {
            if (x == 'Y' || x == 'y') {
                return true;
            } else if (x == 'N' || x == 'n') {
                cout << "THANK YOU FOR PLAYING!";
                return false;
            }
        } else {
            cout << "Insufficient fund!";
            return false;
        }
    }

    int winnerFunction(int bankcard, int playcard) {
        cout << "\n==================================\n";
        if (bankcard > playcard) {
            cout << "\nBANKER WIN, ";
            return 1;
        } else if (bankcard < playcard) {
            cout << "\nPLAYER WIN, ";
            return 2;
        } else if (bankcard == playcard) {
            cout << "\nDRAW, ";
            return 3;
        }
    }

    int declareWinner(int winner, int decision, int bet) {
        if (winner == decision) {
            cout << "YOU WIN!\n";
            return bet;
        } if (winner == 3) {
            cout << "Tie Game!" << endl;
            return 0;
        } else {
            cout << "YOU LOSE!\n";
            bet *= -1;
            return bet;
        }
    }
};

int main() {
    Baccarat game;
    game.startGame();

    return 0;
}
