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

// Function thats check whether an element is in a list or not
// I was originally planning to use a loop that checks over every element inside the list
// but std::find() is way easier [I searched up how to do this]
bool IsElementInList(std::string element, std::list<std::string> list) {
    // list.end() does not represent the last element of a list
    // it represents 1 after the last element of the list
    // std::find() will return list.end() if it doesn't find element
    return std::find(list.begin(), list.end(), element) != list.end();
}

// Function that gets the player's decision
std::string GetDecision(std::string question, std::list<std::string> decisions) {
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

int main() {
    // Code Goes Here
    Pause();
}
