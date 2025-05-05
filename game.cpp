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
#include <functional>

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
        // This if statement allows ctrl+d to actually exit the program
        if (!std::getline(std::cin, choice)) {
            // EXIT PROGRAM
            std::exit(0);
        }
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
int64_t population = 100;
int64_t gold = 0;
int64_t power = 100;

// Initalize a list to hold the flags for the user
std::list<std::string> userFlags = {};

// EVENT CLASS
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
        // std::function allows me to change the function easily
        // when making new events
        std::function<void()> Synopsis = []() {
            std::cout << "This is an event!" << std::endl;
        };

        // The event question that is asked to the user after the synopsis
        std::string question = "Do you understand? (yes/no): ";

        // LIST OF POSSIBLE DECISIONS FOR THE PLAYER TO MAKE
        // ALL DECISIONS MUST BE UPPERCASE
        std::list<std::string> decisions = {"YES", "NO"};

        // Function that displays the aftermath
        std::function<void(std::string)> Effect = [](std::string decision) {
            std::cout << "You picked " << decision << std::endl;
        };

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

// Function for adding a flag
void AddFlag(std::string flagName) {
    // Check if flag is not inside user_flags [Not really needed]
    if (!IsElementInList(flagName, userFlags)) {
        // Append it to the flag list
        userFlags.push_back(flagName);
    }
}

// Initialize list to hold all the events
std::list<Event> eventList = {};

// Function for adding event to event_list
void AddEvent(Event event) {
    // Append event to the event list
    eventList.push_back(event);
}

/* MAKE EVENTS */
Event Intro() {
    Event event;
    event.name = "Introduction";
    event.Synopsis = []() {
        Blue("[ROYAL ADVISOR] Vexel\n");
        Blue("Your Majesty, you have awakened at last.\n");
        Blue("Forgive my intrusion, but time is of the essence.\n");
        Blue("The colony awaits your command, ");
        Blue("and your wisdom is needed now more than ever.\n");
    };

    event.question = "Do you understand your role, my liege? (yes/no): ";
    event.decisions = {"YES", "NO"};

    event.Effect = [](std::string decision) {
        Blue("[ROYAL ADVISOR] Vexel\n");
        if (decision == "YES") {
            Blue("Excellent, Your Majesty.\n");
            Blue("Let's continue.\n");
        } else if (decision == "NO") {
            Blue("Ah, a jest, perhaps?\n");
            Blue("No matter--your instincts shall guide you,");
            Blue(" as they always have.\n");
        }
        AddFlag("INTRO_COMPLETE");
    };

    event.inclusionFlags = {};
    event.exclusionFlags = {"INTRO_COMPLETE"};
    event.weight = -1;

    return event;
}

Event Tutorial() {
    Event event;
    event.name = "The Three Pillars [Tutorial]";

    event.Synopsis = []() {
        Blue("[ROYAL ADVISOR] Vexel\n");
        Blue("Before you proceed, Your Majesty, ");
        Blue("allow me to speak of the three pillars that uphold your rule.\n");
        Blue("\n");
        Blue("First: *");
        Purple("POPULATION");
        Blue("*. Our strength in numbers. It is our greatest strength.\n");
        Blue("This is the most important pillar ");
        Blue("and must be upheld at all times\n");
        Blue("Without it, our goal, is nothing but a lofty dream.\n");
        Blue("\n");
        Blue("Second: *");
        Yellow("GOLD");
        Blue("*. The foundation of our economy. ");
        Blue("It funds our expansion, our armies,");
        Blue(" and the future of the colony.\n");
        Blue("\n");
        Blue("Third: *");
        Red("POWER");
        Blue("*. The measure of your might. When battle comes,");
        Blue(" it is this that determines victory or defeat.\n");
        Blue("\n");
        Blue("Every decision you make shall shape these forces. ");
        Blue("Balance them wisely, ");
        Blue("for the fate of the empire lies in your hands.\n");
    };

    event.question = "Shall we proceed, Your Majesty? (yes): ";
    event.decisions = {"YES"};

    event.Effect = [](std::string decision) {
        Blue("[ROYAL ADVISOR] Vexel\n");
        Blue("Very well. The colony awaits your wisdom.\n");
        Blue("Here's a sum of gold to get you started. ");
        Green("[+500 GOLD]\n");
        gold += 500;
        AddFlag("TUTORIAL_COMPLETE");
    };

    event.inclusionFlags = {"INTRO_COMPLETE"};
    event.exclusionFlags = {"TUTORIAL_COMPLETE"};
    event.weight = -1;

    return event;
}

Event Encounter1() {
    Event event;
    event.name = "Overpowered Cloning Machine";
    event.Synopsis = []() {
        Purple("[Mad Scientist] Sinko\n");
        Purple("Your Majesty, I invented a cloning machine.\n");
        Purple("Would you like to use it? \n");
        Purple("It only costs 10 gold to activate. \n");
    };

    event.question = "Would you like to use the cloning machine? (yes/no): ";
    event.decisions = {"YES", "NO"};

    event.Effect = [](std::string decision) {
        if (decision == "YES") {
            Grey("You insert a gold coin into the coin-shaped slot. ");
            Red("[-10 GOLD] \n");
            gold -= 10;
            Grey("You enter the cloning machine. ");
            Green("[+500000000 POPULATION] \n");
            population += 500000000;
        } else if (decision == "NO") {
            Purple("[Mad Scientist] Sinko\n");
            Purple("... \n");
        }
    };

    event.inclusionFlags = {"TUTORIAL_COMPLETE"};
    event.exclusionFlags = {};
    event.weight = 3;
    event.minGold = 10;
    return event;
}

Event Encounter2() {
    Event event;
    event.name = "Uh-Oh";
    event.Synopsis = []() {
        Cyan("[King of the North] Great Ice Dragon\n");
        Cyan("I am here to destroy your colony.\n");
    };

    event.question = "... (continue): ";
    event.decisions = {"CONTINUE"};

    event.Effect = [](std::string decision) {
        Grey("The dragon submerges your entire colony in a sea of ice. ");
        Red();
        printf("[-%i POPULATION] \n", population);
        population -= population;
    };

    event.inclusionFlags = {"TUTORIAL_COMPLETE"};
    event.exclusionFlags = {};
    event.weight = 1;
    return event;
}

// Function that will only be called once
// ################################################
// Creates all the events
// ################################################
void MakeEvents() {
    AddEvent(Intro());
    AddEvent(Tutorial());
    AddEvent(Encounter1());
    AddEvent(Encounter2());
}

// Initialize variable for the current event
Event currentEvent;

std::list<Event> GetUnlockedEvents() {
    // Initialize a list to hold the unlocked events
    std::list<Event> unlockedEvents;
    // Go through every event in event list
    for (Event event : eventList) {
        // Check if it is available
        if (event.Available()) {
            // If it is, append it to the list
            unlockedEvents.push_back(event);
        }
    }
    // Return the completed list
    return unlockedEvents;
}

// Function that gets a random unlocked event
Event RandomEvent() {
    // Get list of available events
    std::list<Event> unlockedEvents = GetUnlockedEvents();
    // Initialize variable to hold the total sum of weights
    int sumOfWeights = 0;
    // Loop through every unlocked event
    // And add up all the weights
    for (Event event : unlockedEvents) {
        // A weight of -1 is a priority event
        if (event.weight == -1) {
            // Return it immediately
            return event;
        } else {
            // Increment sum of weights by event's weight
            sumOfWeights += event.weight;
        }
    }

    /* Generate a random float between 0 and sum of weights */
    // Used rand_r() instead of rand() due to cpplint
    // Generate seed
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    // Originally used (float) to cast but cpplint wanted me to use static_cast
    // Cast is needed, otherwise the division would evaluate to an integer
    float randNum = (static_cast<float>(rand_r(&seed)) / RAND_MAX);
    randNum *= sumOfWeights;
    // Initialize a variable that accounts for the weight of previous events
    int weightHeap = 0;
    // Loop through every unlocked event
    for (Event event : unlockedEvents) {
        // minimum boundary
        int minBound = weightHeap;
        // maximum boundary
        int maxBound = weightHeap + event.weight;
        // Check if the random number falls within the boundary
        if ((minBound <= randNum) && (randNum <= maxBound)) {
            // If it does, return the event
            return event;
        } else {
            // Otherwise, increment weight heap by the event's weight
            weightHeap += event.weight;
        }
    }
    // Purely for linter purposes
    return Event();
}

// Function that displays every stat
void DisplayStats() {
    Purple();
    printf("POPULATION: %i, ", population);
    Yellow();
    printf("GOLD: %i, ", gold);
    Red();
    printf("POWER: %i \n", power);
}

// Function that manages the event
void ProcessEvent() {
    // Clear Terminal
    ClearTerminal();
    // Display title at top
    DisplayTitle();
    // Display stats
    DisplayStats();
    // Display event name
    Orange();
    printf("~~~ < %s > ~~~\n", currentEvent.name.c_str());
    // Display event synopsis
    currentEvent.Synopsis();
    // Get player's decision
    std::string decision = GetDecision(currentEvent.question,
                            currentEvent.decisions);
    /* Aftermath */
    // Clear Terminal
    ClearTerminal();
    // Display title at top
    DisplayTitle();
    // Display stats
    DisplayStats();
    // Display event name
    Orange();
    printf("~~~ < %s > ~~~\n", currentEvent.name.c_str());
    // Display effect
    currentEvent.Effect(decision);
    // Pause
    Pause();
}

// GAME LOOP
void GameLoop() {
    // Set current event to a random unlocked event
    currentEvent = RandomEvent();
    // Process event + decision
    ProcessEvent();
}

int main() {
    // Make all events
    MakeEvents();
    // Keep on looping indefinitely
    // Until user wins or loses
    while (true) {
        // GAME LOOP
        GameLoop();
        /* At the end of every game loop */
        // Check if population is less than or equal to 0
        if (population <= 0) {
            // population <= 0 results in a loss
            // LOSS
            Red("Your population has been eradicated.\n");
            Red("Your kingdom has fallen. The colony is no more.\n");
            Red("This is all your fault.\n");
            Red("You lost. \n");
            // BREAK
            break;
        } else if (population >= 1000000000) {
            // population >= 1_000_000_000 results in a win
            // WIN
            Green("The kindom is thriving.\n");
            Green("No one dares to challenge you anymore.\n");
            Green("The colony shall never fall as long as you rule.\n");
            Green("You win. \n");
            // BREAK
            break;
        }
    }
    // [ END ]
    White("Thanks for Playing!\n");
}
