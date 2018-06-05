#include <string>
#include <iostream>
using namespace std;
using fString = std::string;
using int32 = int;

//all values initialized to 0
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
        EGuessStatus checkGuessValidity(fString) const; //TODO make a more rich return value

        void reset();  //TODO make a more rich return value
        FStarUfoCount submitValidGuess(fString);//counts stars and UFO's and increases try number, assuming valid guess

//Please  try ignore this and focus on the interface above ^^
    private:
        //see constructor for initialization
        int32 myCurrentTry;
        int32 myMaxTries;
        fString RandomWord;
        bool bGameIsWon;

        bool isIsogram(fString) const;
        bool isLowercase(fString) const;
};