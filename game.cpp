/*
    Author: Jared Thomas
    Date:   Thursday, February 2, 2023

    This module contains the core game loop
*/

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <cassert>

#include "Tower.h"
#include "TowerDrawer.h"
#include "screen.h"
#include "game.h"
#include "game_parser.h"
#include "parse.h"
#include "help.h"

struct GameState {
    GameState(unsigned initialDisks);

    ~GameState();

    std::vector<std::string> tokens;
    bool requestQuit;
    bool gameOver;
    std::vector<Tower> towers;
    TowerDrawer towerDrawer;
    unsigned numDisks;                  // Total number of game disks
    unsigned moves;                     // Number of valid moves that the player has made
    std::string status;                 // Message that prints every frame
    std::string question;
};

GameState::GameState(unsigned initialDisks):
    tokens(),
    requestQuit(false),
    gameOver(false),
    towers(),
    towerDrawer(initialDisks + 3),
    numDisks(initialDisks),
    moves(0),
    status(),
    question()
{

}

GameState::~GameState()
{

}

static unsigned inputState(GameState& gameState);

static void moveState(GameState& gameState);

const unsigned GOAL_TOWER_VECTOR_INDEX = 2;

/*
    Returns the least possible number of moves required to win a game (perfect game).
    This is (2^d - 1), where d is the number of disks.
*/
unsigned leastPossible(unsigned numDisks)
{
    return (1U << numDisks) - 1;
}

/*
    Calculates and returns the game score as the number of moves the player made
    out of the minimum moves required to win
*/
unsigned getScore(unsigned numDisks, unsigned moves)
{
    return (unsigned)(round(100.0 * leastPossible(numDisks) / moves));
}

/*
    Prints the player's game statistics after the game has been won.
    The statistics are the number of moves made, minimum moves required,
    and the final score
*/
void printResults(unsigned numDisks, unsigned moves)
{
    std::cout << "You finished in " << moves << " moves\n";

    std::cout << "Best possible is "\
        << leastPossible(numDisks) << " moves\n";

    std::cout << "Your score: " << getScore(numDisks, moves) << "%";
}

/*
    Clears the screen and draws the towers vector using a tower drawer
*/
void drawTowers(const std::vector<Tower>& towers, const TowerDrawer& towerDrawer)
{
    clearScreen();
    towerDrawer.draw(towers);
}

/*
    Prints the status message after drawing the towers
*/
void printStatus(const std::string& statusMessage)
{
    std::cout << "\n";
    std::cout << statusMessage << "\n";
    std::cout << "\n";
}


void askQuestion(const std::string& question)
{
    std::cout << question;
}

/*
    Returns true if the winning condition has been reached, returns false
    otherwise
*/
bool checkForGameWon(const Tower& goalTower, unsigned totalDisks)
{
    return goalTower.num_disks() == totalDisks;
}

/*
    Puts the towers back in their initial state
*/
void resetTowers(std::vector<Tower>& towers, unsigned totalDisks)
{
    towers.clear();
    towers.push_back(Tower(totalDisks));
    towers.push_back(Tower());
    towers.push_back(Tower());
}

/*
    Puts the entire game back in its initial state; this includes resetting the
    towers and all state variables
*/
void resetGame(GameState& gameState)
{
    resetTowers(gameState.towers, gameState.numDisks);
    gameState.moves = 0;
    gameState.status = "Type \"help\" at any time for instructions. Good luck!";
    gameState.question = "What's your first move? ";
}

/*
    Asks the player if they want to play again. Blocks program flow until the
    player enters valid input.

    Returns true if the player requests to play again, returns false if they
    don't.
*/
bool askPlayAgain()
{
    std::string input;
    do {
        std::cout << "Do you want to play again? (y/n): ";
        input = getRawInput();
    } while(!(input == "y" || input == "n"));
    return input == "y";
}

/*
    Asks the player for the number of disks they want to play with.

    Blocks program flow until the player enters valid input, where valid input
    is a number between 1 and 8 inclusive.

    Returns the number of disks the player entered.
*/
unsigned askNumDisks()
{
    std::string input;
    long numDisks;
    do {
        input.clear();
        numDisks = 0;
        do {
            std::cout << "How many disks do you want to play with? (1=Easiest, 8=Hardest): ";
            input = getRawInput();
        } while(parseLong(input.c_str(), &numDisks) != SUCCESS);
    } while((numDisks < 1) || (numDisks > 8));
    return (unsigned)numDisks;
}

void game(unsigned initialDisks)
{
    GameState gameState(initialDisks);
    resetTowers(gameState.towers, gameState.numDisks);
    std::string rawInput;
    gameState.status = "Type \"help\" at any time for instructions. Good luck!";
    gameState.question = "What's your first move? ";
    while(!(gameState.requestQuit || gameState.gameOver)) {
        drawTowers(gameState.towers, gameState.towerDrawer);
        printStatus(gameState.status);
        askQuestion(gameState.question);
        std::string rawInput = getRawInput();
        gameState.tokens = tokenize(rawInput);
        if(inputState(gameState)) continue;
        moveState(gameState);
    }
}

/*
    Performs input processing and command handling of tokens.

    Returns 0 if the input is a tower move and should be passed on to the move
    parser.

    Returns 1 if the flow should return to the beginning of the game loop.
*/
static unsigned inputState(GameState& gameState)
{
    const unsigned NUM_TUTORIAL_DISKS = 3;
    const unsigned TUTORIAL_ROD_HEIGHT = NUM_TUTORIAL_DISKS + 2;

    std::vector<Tower> tutorialTowers;  // Appears on the help text
    TowerDrawer tutorialTowerDrawer(TUTORIAL_ROD_HEIGHT);
    resetTowers(tutorialTowers, NUM_TUTORIAL_DISKS);

    switch(parseInput(gameState.tokens)) {
    case MOVE: return 0;
    case EMPTY_INPUT: return 1;
    case COMMAND:
        {
            switch(parseCommand(gameState.tokens.front())) {
            case REQUEST_QUIT:
                {
                    gameState.requestQuit = true;
                    return 1;
                }
            case REQUEST_RESET:
                {
                    gameState.numDisks = askNumDisks();
                    gameState.towerDrawer.set_pole_height(gameState.numDisks + 3);
                    resetGame(gameState);
                    return 1;
                }
            case REQUEST_HELP:
                {
                    showHelpText(tutorialTowers, tutorialTowerDrawer);
                    return 1;
                }
            case INVALID_COMMAND:
                {
                    gameState.status = "No such command...";
                    return 1;
                }
            }
            break;  // This only pacifies the compiler; it cannot really be reached.
        }
    case INVALID_INPUT:
        {
            gameState.status = "Huh?";
            return 1;
        }
    }
    assert(0);  // Impossible to get here
    return 0;
}

/*
    Takes in tokens from the input stage and attempts to process them as tower
    moves.
*/
static void moveState(GameState& gameState)
{
    TOWER_MOVE towerMove = parseMove(gameState.tokens, gameState.towers);
    switch(towerMove.moveType) {
    case VALID_MOVE:
        {
            doMove(towerMove, gameState.towers);
            gameState.moves++;
            if(checkForGameWon(gameState.towers.at(GOAL_TOWER_VECTOR_INDEX), gameState.numDisks)) {
                drawTowers(gameState.towers, gameState.towerDrawer);
                printStatus("You win!");
                printResults(gameState.numDisks, gameState.moves);
                std::cout << "\n\n";
                gameState.gameOver = !askPlayAgain();
                if(!gameState.gameOver) {
                    gameState.numDisks = askNumDisks();
                    gameState.towerDrawer.set_pole_height(gameState.numDisks + 3);
                    resetGame(gameState);
                }
                return;
            }
            gameState.status = "";
            gameState.question = "What's your next move? ";
            return;
        }
    case DISKLESS_TOWER:
        {
            gameState.status = "Nothing on that tower...";
            return;
        }
    case LARGER_ON_SMALLER:
        {
            gameState.status = "Can't place a larger disk on a smaller disk...";
            return;
        }
    case INVALID_MOVE_SYNTAX:
        {
            gameState.status = "Can't do that...";
        }
    }
}
