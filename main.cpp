/* This is the console executable, that makes use of the FStarUfoGame class
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the
FStarUfoGame class.
*/
//#pragma once 
#include <iostream>
#include <string>
#include "FStarUfoGame.h"

//to make syntax unreal friendly
using FText = std::string;
using int32 = int;

//prototypes
void printIntro();
void playGame();
FText getValidGuess();
bool askToPlayAgain();
void printGameSummary();

FStarUfoGame SUGame; //create an instance the FStarUfoGame calles SUGame, reused across plays

//The entry point for our application
int main(){
    bool bPlayAgain = false; //assume they dont want to play again
    do{
        printIntro();
        playGame();
        bPlayAgain = askToPlayAgain();
    } while(bPlayAgain);

    return 0; //exit the applicatoin
}

void printIntro(){
    
    std::cout << "                Welcome to Stars and UFO's\n";
    std::cout << "  *  .     ,  *  o     .    '    .    *        o      ."       << std::endl;
    std::cout << "     *     ,               .     |        .       *"           << std::endl;
    std::cout << " o     \\  :  /       *       .-,^,-.   .    '        "        << std::endl;
    std::cout << "    `. __/ \\__ .'   .       /_....._\\    .   *       o"      << std::endl;
    std::cout << " *  _ _\\     /_ _       .-,,`       `,,-.         .       ."  << std::endl;
    std::cout << "  .    /_   _\\     .   (  ooo  ooo  ooo  )   . o   "          << std::endl;
    std::cout << "     .'  \\ /  `.     *  '-.,_________,.-'              ."     << std::endl;
    std::cout << "  o    /  :  \\   *   .      /   *   \\     *       .    o  "   << std::endl;
    std::cout << "  .       '               _/     o   \\_       .        ."     << std::endl;
    std::cout << "     *    '  .    o      `,,`  .      `,,`  .   o         "     << std::endl;
    std::cout << "Can you guess the " << SUGame.getRandomWordLength() << " letter isogram I'm thinking of?\n";
    return;
}

//PURPOSE: plays a single game with one random word
void playGame(){
    SUGame.reset(); 
    int32 maxTries = SUGame.getMaxTries();

    //loop asking for guesses while game is not won
    //and there are still tries remaining
    while(!SUGame.isGameWon() && SUGame.getCurrentTry() <= maxTries){
        FText Guess = getValidGuess(); 

        //submit valid guess to the game and receive counts
        FStarUfoCount starUFOCount = SUGame.submitValidGuess(Guess);

        std::cout << "Stars = " << starUFOCount.stars;
        std::cout << " UFO's = " << starUFOCount.UFOs << "\n";
    }
    printGameSummary();
    return;
}

//PURPOSE: Get a guess from the player, loop continually unitl user gives valid guess
FText getValidGuess(){

    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = ""; //initialized to nothing
    do {
        //get a guess from the player
        int32 currentTry = SUGame.getCurrentTry();
        std::cout << "\nTry " << currentTry << " of " << SUGame.getMaxTries() << ". Enter your guess: ";
        getline(std::cin , Guess);

        //check status and give feedback
        Status = SUGame.checkGuessValidity(Guess);
        switch(Status){
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << SUGame.getRandomWordLength() << " letter word.\n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter word in lowercase.\n\n";
            break;
        default:
            //assume the guess is valid
            break;
        }
    } while(Status != EGuessStatus::OK); //keep looping until we get no errors
    return Guess;
}

//PURPOSE: Ask the user if they want to play again
bool askToPlayAgain(){
    std::cout <<"\nDo you want to play again with the same word? (y to play again, any other key to exit) ";
    FText Response = "";
    getline(std::cin, Response);

    return (Response[0] == 'y' || Response[0] == 'Y');
}

//PURPOSE: Tell the user if they won or lost
void printGameSummary(){
    if(SUGame.isGameWon()){
        std::cout << "Winner winner chicken dinner!\n";
    } else {
        std::cout << "Sorry, try again!\n";
    }
}
