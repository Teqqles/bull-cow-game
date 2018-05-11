#ifndef FBullCowGame_h
#define FBullCowGame_h

#include <string>
#include <map>

using int32 = int;
using FText = std::string;
using FString = std::string;

enum class EGuessStatus
{
    OK,
    Not_Isogram,
    Not_Lowercase,
    Wrong_Length
};

struct FBullCowScore
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

class FBullCowGame
{
public:
    FBullCowGame();
    void Reset();
    int32 GetMaxTries() const;
    int32 GetCurrentAttemptCount() const;
    bool IsWinner(FBullCowScore) const;
    EGuessStatus GetGuessValidity(FText) const;
    FBullCowScore SubmitValidGuess(FText);
    FString GetValidGuess();
    int32 GetHiddenWordLength() const;
    
private:
    FString GetGuess();
    void PrintGuessErrorMessage(FText, FText);
    bool IsIsogram(FText) const;
    bool IsLowercase(FText) const;
    int32 MaxTries;
    int32 CurrentNumberOfAttempts;
    FText HiddenWord;
};

#endif /* FBullCowGame_h */
