#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Hangman {
protected:
    string word;
    vector<char> guessed;
    int attempts;

public:
    Hangman(const vector<string>& words, int maxAttempts) {
        srand(time(0));
        word = words[rand() % words.size()];
        attempts = maxAttempts;
    }

    void displayWord() const {
        for (size_t i = 0; i < word.length(); ++i) {
            char c = word[i];
            if (find(guessed.begin(), guessed.end(), c) != guessed.end()) {
                cout << c << ' ';
            } else {
                cout << "_ ";
            }
        }
        cout << endl;
    }

    bool isWordGuessed() const {
        for (size_t i = 0; i < word.length(); ++i) {
            if (find(guessed.begin(), guessed.end(), word[i]) == guessed.end()) {
                return false;
            }
        }
        return true;
    }

    void guessLetter(char guess) {
        guess = tolower(guess);
        if (find(guessed.begin(), guessed.end(), guess) != guessed.end()) {
            cout << "You already guessed that letter.\n";
            return;
        }

        guessed.push_back(guess);

        if (word.find(guess) != string::npos) {
            cout << "Correct guess!\n";
        } else {
            cout << "Wrong guess.\n";
            attempts--;
        }
    }

    bool isGameOver() const {
        return attempts == 0 || isWordGuessed();
    }

    void displayStatus() const {
        displayWord();
        cout << "Attempts remaining: " << attempts << endl;
    }

    string getWord() const {
        return word;
    }
};

class Game : public Hangman {
public:
    Game(const vector<string>& words, int maxAttempts) : Hangman(words, maxAttempts) {}

    void play() {
        cout << "Welcome to Hangman!\n";

        while (!isGameOver()) {
            displayStatus();
            cout << "Guess a letter: ";
            char guess;
            cin >> guess;
            guessLetter(guess);

            if (isWordGuessed()) {
                cout << "Congratulations! You guessed the word: " << word << endl;
                return;
            }
        }

        cout << "Game Over! The word was: " << word << endl;
    }
};

int main() {
    vector<string> words = {"programming", "computer", "hangman", "cplusplus", "developer"};
    Game game(words, 6);
    game.play();
    return 0;
}
