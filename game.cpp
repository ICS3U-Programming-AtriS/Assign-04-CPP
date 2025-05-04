// Copyright (c) 2025 Atri Sarker All rights reserved.
// .
// Created By: Atri S
// Date: MAY 3, 2025
// King of the Ants

#include <unistd.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

// Colors
const char BLACK[] = "\033[0;30m";  // BLACK
const char RED[] = "\033[0;31m";  // RED
const char GREEN[] = "\033[0;32m";  // GREEN
const char YELLOW[] = "\033[0;33m";  // YELLOW
const char BLUE[] = "\033[0;34m";   // BLUE
const char PURPLE[] = "\033[0;35m";  // PURPLE
const char CYAN[] = "\033[0;36m";    // CYAN
const char WHITE[] = "\033[0;37m";   // WHITE
const char GREY[] = "\033[38;5;240m";  // GREY
const char ORANGE[] = "\033[38;5;208m";  // ORANGE

// COLOR PRINT FUNCTIONS
void Black(std::string msg = "") {
    // APPLY COLOR
    std::cout << BLACK;
    // PRINT MESSAGE
    std::cout << msg;
}

void Red(std::string msg = "") {
    // APPLY COLOR
    std::cout << RED;
    // PRINT MESSAGE
    std::cout << msg;
}

void Green(std::string msg = "") {
    // APPLY COLOR
    std::cout << GREEN;
    // PRINT MESSAGE
    std::cout << msg;
}

void Yellow(std::string msg = "") {
    // APPLY COLOR
    std::cout << YELLOW;
    // PRINT MESSAGE
    std::cout << msg;
}

void Blue(std::string msg = "") {
    // APPLY COLOR
    std::cout << BLUE;
    // PRINT MESSAGE
    std::cout << msg;
}

void Purple(std::string msg = "") {
    // APPLY COLOR
    std::cout << PURPLE;
    // PRINT MESSAGE
    std::cout << msg;
}

void Cyan(std::string msg = "") {
    // APPLY COLOR
    std::cout << CYAN;
    // PRINT MESSAGE
    std::cout << msg;
}

void White(std::string msg = "") {
    // APPLY COLOR
    std::cout << WHITE;
    // PRINT MESSAGE
    std::cout << msg;
}

void Grey(std::string msg = "") {
    // APPLY COLOR
    std::cout << GREY;
    // PRINT MESSAGE
    // With a flush, since I am using it in Pause()
    std::cout << msg << std::flush;
}

void Orange(std::string msg = "") {
    // APPLY COLOR
    std::cout << ORANGE;
    // PRINT MESSAGE
    std::cout << msg;
}

// Function thats check whether an element is in a list or not.
// I was originally planning to use a loop that checks over
// every element inside the list.
// but std::find() is way easier [I searched up how to do this].
bool IsElementInList(std::string element, std::list<std::string> list) {
    // list.end() does not represent the last element of a list
    // it represents 1 after the last element of the list
    // std::find() will return list.end() if it doesn't find element
    return std::find(list.begin(), list.end(), element) != list.end();
}

// Function that gets the player's decision
std::string GetDecision(std::string question,
    std::list<std::string> decisions) {
    while (true) {
        // Display question
        Cyan(question);
        // Get user input [WHITE]
        White();
        std::string choice;
        std::getline(std::cin, choice);
        // Transform input for case insensitivity
        std::transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        //  Check if the choice is in the list of possible decisions
        if (IsElementInList(choice, decisions)) {
            // Return the selected choice
            return choice;
        } else {
            // Invalid Input
            Red("Invalid decision, try again.\n");
        }
    }
}

// Function that clears the Terminal
void ClearTerminal() {
    // Clears the Terminal
    std::system("clear");
}

// Function for pausing the terminal
// Used for allowing the read to read the effects
// Also acts as a downtime between events
void Pause() {
    Grey("Continue in [");
    // 2 seconds long[1.5 + 0.5]
    for (int halfSecond = 0; halfSecond < 3; halfSecond++) {
        // Halt the program for half a second
        // usleep uses microseconds
        usleep(500000);  // 500,000 microseconds = 0.5 seconds
        Grey("#");
    }
    usleep(500000);
    // Close off progress bar
    Grey("]\n");
    // Give user a signal to continue
    Yellow("Press enter to continue >>>");
    // Pause will end once user presses enter
    // Using std::cin and ::getline()
    // Useless variable, I just needed it to activate std::cin
    std::string catalyst;
    std::getline(std::cin, catalyst);
}

// Function that displays the title
void DisplayTitle() {
    Yellow("##################################\n");
    Yellow("######## KING OF THE ANTS ########\n");
    Yellow("##################################\n");
}

// INITIALIZE STATS
// I was originally using [long int] but cpplint didn't like that
int64_t gold = 100;
int64_t population = 0;
int64_t power = 100;

// Initalize a list to hold the flags for the user
std::list<std::string> userFlags = {};

// EVENT EVENT
class Event {
    // Every property is going to be public
    // Wierd indentation is for cpplint
 public:
        // Function that checks whether an event is available or not
        bool Available() {
            // Check if the user has the prerequisite flags
            for (std::string flag : inclusionFlags) {
                if (!IsElementInList(flag, userFlags)) {
                    return false;
                }
            }

            // Check if the user does not have the blacklisted flags
            for (std::string flag : exclusionFlags) {
                if (IsElementInList(flag, userFlags)) {
                    return false;
                }
            }

            // Check if the user meets the minimum stat criteria
            if (population < minPopulation) {
                return false;
            }
            if (gold < minGold) {
                return false;
            }
            if (power < minPower) {
                return false;
            }

            // Check if the user meets the maximum stat criteria
            if ((maxPopulation != -1) && (population > maxPopulation)) {
                return false;
            }
            if ((maxGold != -1) && (gold > maxGold)) {
                return false;
            }
            if ((maxPower != -1) && (power > maxPower)) {
                return false;
            }

            // Once all checks are passed, return true
            return true;
        }

        // Function that displays the synopsis of the event
        void synopsis() {
            std::cout << "This is an event!" << std::endl;
        }

        // The event question that is asked to the user after the synopsis
        std::string question = "Do you understand? (yes/no): ";

        // List of possible decisions for the player to make
        std::list<std::string> decisions = {"YES", "NO"};

        // Function that displays the aftermath based on decision
        void Effect(std::string decision) {
            std::cout << "You picked " << decision << std::endl;
        }

        // Flag Lists
        std::list<std::string> inclusionFlags;  // List of prerequisite flags
        std::list<std::string> exclusionFlags;  // List of blacklisted flags

        // Minimums and Maximums
        // -1 will represent infinity
        // These values are used to check the availability of the event
        int minPopulation = 0;
        int maxPopulation = -1;
        int minGold = 0;
        int maxGold = -1;
        int minPower = 0;
        int maxPower = -1;

        // Event Name
        std::string name = "Event Name";

        // Weight determines the likelihood of an event
        int weight = 0;
};

int main() {
    // Code Goes Here
    Pause();
}
