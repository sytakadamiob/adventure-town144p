#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <cstdlib>   // rand, srand// rand, srand
#include <cctype>    // tolower
#include <ctime>     // time
#include <thread>    // sleep helper
#include <chrono>    // sleep helper

using namespace std;

// Function Prototypes
void clearScreen();
void sleepSeconds(int);
void loading(const string&, int);
void welcomeMessage();
void printMenu();
void aboutGame();
void aboutUs();
void briefIntro();
void journeyStart();
bool validInput(const int);
string toLowerCase(string&);
string repromptDir();
string repromptElement();
bool lvl1n2(const string, const string, const string, const string, const string, const string, const string, const string, const string);
bool lvl3();

int main() {
    int userChoice;

    // Prompt user input
    do {
        welcomeMessage();
        printMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;

        // Clear the newline
        cin.clear();
        cin.ignore(1000, '\n');

        while (!validInput(userChoice)) {
            cout << "\nInvalid Input. Try again.\nEnter your choice: ";
            cin >> userChoice;
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch(userChoice) {
            case 1:
                journeyStart();
                break;
            case 2:
                aboutGame();
                break;
            case 3:
                aboutUs();
                break;
            case 4:
                cout << "Game terminated." << endl;
                return 0;
                break;
        }
    } while (userChoice != 4);

    return 0;
}

// Cross-platform clear & sleep
inline void clearScreen() {
    #if defined(_WIN32)
        cout << "\x1B[2J\x1B[H" << std::flush;
        // std::system("cls"); // optional fallback
    #else
        cout << "\x1B[2J\x1B[H" << std::flush;
        // std::system("clear"); // optional fallback
    #endif
}  
inline void sleepSeconds(int s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
}

void loading(const string& message, int count) {
    clearScreen();
        cout << message << endl;

    for (int i = 0; i < count; i++) {
        sleepSeconds(1);
        clearScreen();
        cout << message;

        for (int j = 0; j <= i; j++) {
            cout << ".";
        }
        cout << endl;
    }
    sleepSeconds(1);
    clearScreen();
}

void welcomeMessage() {
    cout << "\nWelcome to Adventure Town!" << endl;
    cout << setfill('=') << setw(32) << "" << endl;
}

void printMenu() {
    cout << "1) Start the journey." << endl;
    cout << "2) About the game." << endl;
    cout << "3) About us." << endl;
    cout << "4) Quit." << endl;
}

void aboutGame() {
    string returnKey;

    cout << "\nWise choice!" << endl;
    cout << "It's always the best to learn before you start." << endl;
    cout << "Here is how the game works:" << endl;
    cout << "• You'll play as a hero with 3 elements: fire, water, and earth." << endl;
    cout << "• Using those, you are to fight the monsters you'll encounter on your way along the journey." << endl;
    cout << "• [Tip] Attack with their weakness by guessing their type by their names." << endl;
    cout << "   - Fire beats Earth (burns plants)" << endl;
    cout << "   - Water beats Fire (extinguishes flames)" << endl;
    cout << "   - Earth beats Water (absorbs moisture)" << endl;
    cout << "But that won't apply to the final boss!" << endl;
    cout << "It doesn't have certain weakness so whoever is on the luck will win." << endl;
    cout << "Remember to also choose your path wisely - different routes lead to different monsters" << endl;
    cout << "Good luck!" << endl;
    cout << "\nHope you now have a solid understanding of the game logic." << endl;
    cout << "    Press Enter to return to menu: ";
    getline(cin, returnKey);
    loading("Returning back to the menu", 3);

}

void aboutUs() {
    cout << "\nAbout the Dev:" << endl;
    cout << "This game was fully developed by me:)" << endl;
    cout << "Thanks for playing this game and I hope you enjoy the game!" << endl;
    cout << "I genuinely appreciate your support!" << endl;
}

void briefIntro() {
    string startKey;
    clearScreen();

    cout << "The Story Begins:" << endl;
    cout << "\n- On May 31st, 1875..." << endl;
    cout << "      \"The weather is calm with the sun shining brightly." << endl;
    cout << "   But something feels odd about the town today. Suddenly "<< endl;
    cout << "   flustered residents bring you urgent news that monsters" << endl;
    cout << "   have been spotted uprising not far from the town.\"" << endl;
    cout << "\nYou have decided to embark on a journey to eliminate these threats!" << endl;
    cout << "     Press any key to continue: ";
    getline(cin, startKey);
}

void journeyStart() {
    string restartKey;
    bool isTerminating = false;
    briefIntro();

    while (!isTerminating) {
        if (!lvl1n2("Level 1", "You take the left path toward the volcano range\nWandering around", "Phoenix", "fire", "water", 
            "You take the right path toward the misty shoreline\nApproaching" , "Hydrofin", "water", "earth")) {
            cout << "<Game Over>" << endl;
            cout << "    Press any key to restart or \'s\' to stop: ";
            getline(cin, restartKey);
            if (restartKey == "s") {
                isTerminating = true;
                loading("Returning back to the menu", 3);
            } else {
                loading("Restarting over", 3);
            }
        } else {
            cout << "Congrats! You advance to next level!" << endl;
            if (!lvl1n2("Level 2", "You veer left towards a crystal-clear lake\nApproaching the lake", "Aqua Drake", "water", "earth", 
                "You veer right into an ominous cave\nVenturing inside" , "Boulderbeast", "earth", "fire")) {
                cout << "<Game Over>" << endl;
                cout << "    Press any key to restart or \'s\' to stop: ";
                getline(cin, restartKey);
                if (restartKey == "s") {
                    isTerminating = true;
                    loading("Returning back to the menu", 3);
                } else {
                    loading("Restarting over", 3);
                }
                
            } else {
                cout << "Congrats! You advance to next level!" << endl;
                if (!lvl3()) {
                    cout << "<Game Over>" << endl;
                    cout << "    Press any key to restart or \'s\' to stop: ";
                    getline(cin, restartKey);
                    if (restartKey == "s") {
                        isTerminating = true;
                        loading("Returning back to the menu", 3);
                    } else {
                        loading("Restarting over", 3);
                    }
                } else {
                    cout << "You've beaten up the final boss! Victory is yours." << endl;
                    isTerminating = true;
                }
            }
        }
    }
}

bool validInput(const int input) {
    if (input > 0 && input < 5) {
        return true;
    } else {
        return false;
    }
}

string toLowerCase(string& input) {
    string updatedStr = input;
    for (int i = 0; i < input.length(); i++) {
        updatedStr[i] = tolower(updatedStr[i]);
    }
    return updatedStr;
}

string repromptDir() {
    string userInput;

    do {
        cout << "Invalid Input. Try (left/right): ";
        getline(cin, userInput);
        userInput = toLowerCase(userInput);
    } while (userInput != "left" && userInput != "right");

    return userInput;
}

string repromptElement() {
    string yourChoice;

    do {
        cout << "Invalid Input. Try Again: ";
        getline(cin, yourChoice);
        yourChoice = toLowerCase(yourChoice);
    } while (yourChoice != "fire" && yourChoice != "water" && yourChoice != "earth");

    return yourChoice;
}

// ------------------- Level 1 + 2 -------------------
bool lvl1n2(const string level, const string message1, const string monster1, const string power1, const string weakness1, 
    const string message2, const string monster2, const string power2, const string weakness2) {
    string dir;
    bool nextLvl = false;

    cout << endl;
    cout << setfill('-') << setw(20) << "";
    cout << "   " << level << "   ";
    cout << setfill('-') << setw(20) << "" << endl;
    cout << setfill(' '); // reset
    if (level == "Level 1") {
        cout << "Your journey begins!" << endl;
    }
    cout << "Which path would you like to take? (left/right): ";

    getline(cin, dir);
    dir = toLowerCase(dir);

    while (dir != "left" && dir != "right") {
        dir = repromptDir();
    }

    if (dir == "left") {
        string yourChoice;
        loading(message1, 5);

        do {
            cout << "\nYou met a " << monster1 << "!" << endl;
            cout << "You've got altogether 3 elements(fire, water, and earth)." << endl;
            cout << "Choose your element: ";
            getline(cin, yourChoice);
            yourChoice = toLowerCase(yourChoice);

            while (yourChoice != "fire" && yourChoice != "water" && yourChoice != "earth") {
                yourChoice = repromptElement();
                yourChoice = toLowerCase(yourChoice);
            }

            cout << monster1 << " attacks with \"" << power1 << "\"." << endl;

            if (yourChoice == power1) {
                cout << "It's a tie!" << endl;

            }
            else if (yourChoice == weakness1) {
                cout << "You win!" << endl;
                nextLvl = true;
            } else {
                cout << "You lose." << endl;
                return false;
            }
        } while (yourChoice == power1);
    }

    else if (dir == "right") {
        string yourChoice;
        loading(message2, 5);

        do {
            cout << "\nYou met a " << monster2 << "!" << endl;
            cout << "You've got altogether 3 elements(fire, water, and earth)." << endl;
            cout << "Choose your element: ";
            getline(cin, yourChoice);
            yourChoice = toLowerCase(yourChoice);

            while (yourChoice != "fire" && yourChoice != "water" && yourChoice != "earth") {
                yourChoice = repromptElement();
            }

            cout << monster2 << " attacks with \"" << power2 << "\"." << endl;

            if (yourChoice == power2) {
                cout << "It's a tie!" << endl;
            }
            else if (yourChoice == weakness2) {
                cout << "You win!" << endl;
                nextLvl = true;
            } else {
                cout << "You lose." << endl;
                return false;
            }
        } while (yourChoice == power2);
    } 

    return nextLvl;
}

// ------------------- Level 3 -------------------
bool lvl3() {
    string yourChoice;
    string MonsterAttk;
    string continueKey;
    bool nextLvl = false;
    bool tie = false;
    srand(time(NULL));

    cout << endl;
    cout << setfill('-') << setw(20) << ' ';
    cout << "   Level 3   ";
    cout << setfill('-') << setw(20) << ' ' << endl;
    cout << "You've come to the edge of the thick forest!" << endl;
    cout << "You've got no choice but to continue." << endl;
    cout << "Ready to continue your last journey?" << endl;
    cout << "    Press any key to continue: ";
    getline(cin, continueKey);

    loading("You enter right into the thick forest\nMarching", 5);

    do {
        cout << "\nYou met an Elementalbeast! (Final Boss)" << endl;
        cout << "You've got altogether 3 elements(fire, water, and earth)." << endl;
        cout << "Choose your element: ";
        getline(cin, yourChoice);
        yourChoice = toLowerCase(yourChoice);

        while (yourChoice != "fire" && yourChoice != "water" && yourChoice != "earth") {
            yourChoice = repromptElement();
        }

        int randNum = (rand() % 3) + 1;
        switch(randNum) {
            case 1:
                MonsterAttk = "fire";
                break;
            case 2:
                MonsterAttk = "water";
                break;
            case 3:
                MonsterAttk = "earth";
                break;
            default:
                cout << "Error" << endl;
                break;
        }

        cout << "Elementalbeast attacks with \""<< MonsterAttk << "\"." << endl;

        if (yourChoice == MonsterAttk) {
            cout << "It's a tie!" << endl;
            tie = true;
        }
        else if (yourChoice == "fire" && MonsterAttk == "earth") {
            cout << "You won!" << endl;
            nextLvl = true;
            tie = false;
        }
        else if (yourChoice == "water" && MonsterAttk == "fire") {
            cout << "You won!" << endl;
            nextLvl = true;
            tie = false;
        }
        else if (yourChoice == "earth" && MonsterAttk == "water") {
            cout << "You won!" << endl;
            nextLvl = true;
            tie = false;
        } else {
            tie = false;
            cout << "You lose." << endl;
        }
    } while (tie);

    return nextLvl;
}