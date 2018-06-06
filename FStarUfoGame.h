/*THE GAME LOGIC (no view code or direct user interaction) 
The game is a simple word game based on Mastermind*/
//#pragma once
#include <string>
#include <iostream>
using namespace std;

//to make the syntax unreal friendly
using fString = std::string;
using int32 = int;

struct FStarUfoCount {
    int32 stars = 0;
    int32 UFOs = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FStarUfoGame {
    public:
        FStarUfoGame(); //CONSTRUCTOR
        int32 getMaxTries() const; //these getters cannot change any of the objects member variables
        int32 getCurrentTry() const;
        int32 getRandomWordLength() const;
        bool isGameWon() const;
        EGuessStatus checkGuessValidity(fString) const; 

        void reset();  
        FStarUfoCount submitValidGuess(fString);//counts stars and UFO's and increases try number, assuming valid guess

//Please  try ignore this and focus on the interface above ^^
    private:
        //see constructor for initialization
        int32 myCurrentTry;
        fString RandomWord;
        bool bGameIsWon;

        bool isIsogram(fString) const;
        bool isLowercase(fString) const;
};