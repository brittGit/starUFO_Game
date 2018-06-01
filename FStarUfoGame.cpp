#include <iostream>
#include <string>
#include "FStarUfoGame.h"

using fString = std::string;
using int32 = int;

//CONSTRUCTOR
FStarUfoGame::FStarUfoGame(){reset();}

//getters
int32 FStarUfoGame::getMaxTries() const {return myMaxTries;}
int32 FStarUfoGame::getCurrentTry() const {return myCurrentTry;}
int32 FStarUfoGame::getRandomWordLength() const {return RandomWord.length();}
bool FStarUfoGame::isGameWon() const {return bGameIsWon;}

void FStarUfoGame::reset(){  //TODO make a more rich return value
    const int32 MAX_TRIES = 8;
     const fString RANDOM_WORD = "planet";

    myMaxTries = MAX_TRIES;
    RandomWord = RANDOM_WORD;
    myCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FStarUfoGame::checkGuessValidity(fString Guess) const{

    if(false){ //IF THE GUESS isnt an isogram
        return EGuessStatus::Not_Isogram;   //return an error
    } else if (false){  //if the guess isnt all lowercase
        return EGuessStatus::Not_Lowercase; //return error  
    } else if(Guess.length() != getRandomWordLength()){    //if the guess length is wrong
        return EGuessStatus::Wrong_Length; //return error
    } else {//otherwise
        return EGuessStatus::OK;//return OK
    }
} 

//PURPOSE: receives a VALID guess, increments turn, and returns count
FStarUfoCount FStarUfoGame::submitValidGuess(fString Guess){
    myCurrentTry++;   

    //setup a return variable (type then name of variable)
    FStarUfoCount starUFOCount;

   //putting length of the hiddenword into WordLength
    int32 WordLength = RandomWord.length(); //assuming the same length as guess

    //loop througth all letters in the random word
    for (int32 RandomWordChar = 0; RandomWordChar < WordLength; RandomWordChar++){
        //compare letters against guessed word
        for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++){   //compare letters against the hidden word characters
            if (Guess[GuessChar] == RandomWord[RandomWordChar]){   //if letters in hiddenword and guess match
                if(RandomWordChar == GuessChar){                 //if they are in the same place
                    starUFOCount.stars++;   //increment stars 
                } else {
                    starUFOCount.UFOs++;    //must be a UFO so increment UFOS 
                }   
            }
        }
    }
    if(starUFOCount.stars == WordLength) {
        bGameIsWon = true;
    } else {
        bGameIsWon = false;
    }
    return starUFOCount;
}