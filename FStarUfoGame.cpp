#include <iostream>
#include <string>
#include "FStarUfoGame.h"
#include <map>

//to make syntax unreal friendly
#define TMap std::map
using int32 = int;

//CONSTRUCTOR
FStarUfoGame::FStarUfoGame(){reset();}

//getters
int32 FStarUfoGame::getCurrentTry() const {return myCurrentTry;}
int32 FStarUfoGame::getRandomWordLength() const {return RandomWord.length();}
bool FStarUfoGame::isGameWon() const {return bGameIsWon;}

int32 FStarUfoGame::getMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7, 20} };
    return WordLengthToMaxTries[RandomWord.length()];
}

void FStarUfoGame::reset(){ 
    const int32 MAX_TRIES = {3};
    const fString RANDOM_WORD = "planet";   //this must be an isogram

    RandomWord = RANDOM_WORD;
    myCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FStarUfoGame::checkGuessValidity(fString Guess) const{

    if(!isIsogram(Guess)){ //IF THE GUESS isnt an isogram
        return EGuessStatus::Not_Isogram;   //return an error 
    } else if (!isLowercase(Guess)){  //if the guess isnt all lowercase 
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

bool FStarUfoGame::isIsogram(fString Word) const {

    //treat 0 or 1 letter words as isograms
    if(Word.length() <= 1) { return true; } 

    TMap<char, bool> LetterSeen; //set up TMap
    for (auto Letter : Word){    //for all letters of the word

        Letter = tolower(Letter);   //to store and remember only lower case letters
        if(LetterSeen[Letter]) {//if the letter is in the map twice 
            return false;   //no isogram at this stage
            } else { //start adding letters to map
                LetterSeen[Letter] = true; //add the letter to the map as seen
            }
    }
    return true; //for example in cases where /0 is entered
}

bool FStarUfoGame::isLowercase(fString Word) const {

    for(auto Letter : Word){ //for all letters of the word
        if(!islower(Letter))//if not a lowercase letter
            return false;
        
        }
    return true;
}