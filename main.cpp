/* This is the console executable, that makes use of the FStarUfoGame class
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic see the
FStarUfoGame class.
*/
#include <iostream>
#include <string>
#include "FStarUfoGame.h"

using FText = std::string;
using int32 = int;

void printIntro();
void playGame();
FText getValidGuess();
bool askToPlayAgain();

FStarUfoGame SUGame; //create an instance the FStarUfoGame calles SUGame

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

//PURPOSE: introduce the game
void printIntro(){
    
    std::cout << "Welcome to Stars and UFO's\n";
    std::cout << "Can you guess the " << SUGame.getRandomWordLength() << " letter isogram I'm thinking of?\n";
    return;
}

//PURPOSE: go through steps to play a game of starsUFOsut 
void playGame(){
    SUGame.reset(); 
    int32 maxTries = SUGame.getMaxTries();

    //loop asking for guesses while game is not won
    //and there are still tries remaining
    while(!SUGame.isGameWon() == false && SUGame.getCurrentTry() <= maxTries){
        FText Guess = getValidGuess(); 

        //submit valid guess to the game and receive counts
        FStarUfoCount starUFOCount = SUGame.submitValidGuess(Guess);

        std::cout << "Stars = " << starUFOCount.stars;
        std::cout << " UFO's = " << starUFOCount.UFOs << "\n\n";
    }
    //TODO summarise game
    return;
}

//PURPOSE: Get a guess from the player, loop continually unitl user gives valid guess
FText getValidGuess(){

    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = ""; //initialized to nothing
    do {
        //get a guess from the player
        int32 currentTry = SUGame.getCurrentTry();
        std::cout << "\nTry " << currentTry << ". Enter your guess: ";
        getline(std::cin , Guess);

        Status = SUGame.checkGuessValidity(Guess);
        switch(Status){
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << SUGame.getRandomWordLength() << " letter word.\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter word in lowercase.\n";
            break;
        case EGuessStatus::OK: 
            std::cout << "OK.\n";
            break;
        default:
            //assume the guess is valid
            break;
        }
        std::cout << std::endl;
    } while(Status != EGuessStatus::OK); //keep looping until we get no errors
    return Guess;
}

//PURPOSE: Ask the user if they want to play again
bool askToPlayAgain(){
    std::cout <<"\nDo you want to play again? (y to play again, any other key to exit) ";
    FText Response = "";
    getline(std::cin, Response);

    return (Response[0] == 'y' || Response[0] == 'Y');
}
