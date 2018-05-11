#include "FBullCowGame.h"
#include <iostream>
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
    Reset();
}

void FBullCowGame::Reset()
{
    constexpr int32 MAX_RETRIES = 5;
    MaxTries = MAX_RETRIES;
    CurrentNumberOfAttempts = 1;
    HiddenWord = "score";
    return;
}

int32 FBullCowGame::GetMaxTries() const
{
    return MaxTries;
}

int32 FBullCowGame::GetCurrentAttemptCount() const
{ 
    return CurrentNumberOfAttempts;
}

bool FBullCowGame::IsIsogram(FText Guess) const
{
    TMap<char, bool> CharacterSeen;
    for (auto Character : Guess)
    {
        if (CharacterSeen.find(Character) != CharacterSeen.end())
        {
            return false;
        }
        CharacterSeen[Character] = true;
    }
    return true;
}

bool FBullCowGame::IsLowercase(FText Guess) const
{
    for (auto Character : Guess)
    {
        if (tolower(Character) != Character)
        {
            return false;
        }
    }
    return true;
}

EGuessStatus FBullCowGame::GetGuessValidity(FText Guess) const
{
    if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    } else if (!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    return EGuessStatus::OK;
}

bool FBullCowGame::IsWinner(FBullCowScore Score) const
{
    if (Score.Bulls == GetHiddenWordLength())
    {
        return true;
    }
    return false;
}

FBullCowScore FBullCowGame::SubmitValidGuess(FText Guess)
{
    FBullCowScore BullCowScore;
    CurrentNumberOfAttempts++;
    for(int32 i=0; i< Guess.length(); i++)
    {
        size_t CharPos = HiddenWord.find(Guess[i]);
        if (CharPos != std::string::npos)
        {
            if (CharPos == i)
            {
                BullCowScore.Bulls++;
            } else {
                BullCowScore.Cows++;
            }
        }
    }
    return BullCowScore;
}

FString FBullCowGame::GetValidGuess()
{
    EGuessStatus GuessStatus;
    FString Guess;
    do
    {
        Guess = GetGuess();
        GuessStatus = GetGuessValidity(Guess);
        switch (GuessStatus)
        {
            case EGuessStatus::Not_Lowercase:
                PrintGuessErrorMessage(Guess, "is not lowercase, please only enter a lowercase word.");
                break;
            case EGuessStatus::Not_Isogram:
                PrintGuessErrorMessage(Guess, "is not an isogram (a word containing no repearing characters.");
                break;
            case EGuessStatus::Wrong_Length:
                PrintGuessErrorMessage(Guess, "is not " + std::to_string(GetHiddenWordLength()) + " characters long.");
                break;
            default:
                break;
        }
    } while (GuessStatus != EGuessStatus::OK);
    return Guess;
}

FString FBullCowGame::GetGuess()
{
    std::cout << "Try " << GetCurrentAttemptCount() << ". Enter your guess: ";
    FString Guess = "";
    std::getline(std::cin, Guess);
    return Guess;
}

void FBullCowGame::PrintGuessErrorMessage(FText Guess, FText Error) {
    std::cout << "Your word '" << Guess << "' " << Error << std::endl;
}

int32 FBullCowGame::GetHiddenWordLength() const {
    return (int32)HiddenWord.length();
}




