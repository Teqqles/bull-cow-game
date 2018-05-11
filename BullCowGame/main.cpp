#include <iostream>
#include <string>
#include "FBullCowGame.h"

void PrintWelcomeIntroduction();
void PrintGuess(FString Guess, FBullCowScore Score);
void PlayGame();
void PrintReplayQuestion();
bool IsReplaying();
void PrintGameOverMessage(bool IsGameWon);

FBullCowGame BCGame = FBullCowGame();

int main(int argc, const char * argv[])
{
    do
    {
        PrintWelcomeIntroduction();
        PlayGame();
        PrintReplayQuestion();
        BCGame.Reset();
    } while (IsReplaying());
    
    return 0;
}

void PlayGame()
{
    FString PlayerGuess = "";
    int32 i = 0;
    FBullCowScore BullCowScore;
    bool IsGameWon = false;
    do
    {
        PlayerGuess = BCGame.GetValidGuess();
        BullCowScore = BCGame.SubmitValidGuess(PlayerGuess);
        PrintGuess(PlayerGuess, BullCowScore);
        IsGameWon = BCGame.IsWinner(BullCowScore);
    } while (++i < BCGame.GetMaxTries() && !IsGameWon);
    
    PrintGameOverMessage(IsGameWon);
    
    return;
}

void PrintWelcomeIntroduction()
{
    std::cout << "                /)  (\\" << std::endl;
    std::cout << "           .-._((,~~.))_.-,             .-.___,~~.___.-," << std::endl;
    std::cout << "  BULLS     `=.   ^^   ,='               `=.   69   ,='" << std::endl;
    std::cout << "              / ,o~~o. \\                   / ,o~~o. \\" << std::endl;
    std::cout << "             { { .__. } }                 { { ____ } }" << std::endl;
    std::cout << "              ) `~~~\\' (                   ) `~~~~' (" << std::endl;
    std::cout << "             /`-._  _\\.-\\                 /`-._  _.-`\\" << std::endl;
    std::cout << "            /         )  \\      AND      /            \\" << std::endl;
    std::cout << "          ,-X        #   X-.           ,-X            X-." << std::endl;
    std::cout << "         /   \\          /   \\         /   \\          /   \\" << std::endl;
    std::cout << "        (     )| |  | |(     )       (     )| |  | |(     )" << std::endl;
    std::cout << "         \\   / | |  | | \\   /         \\   / | |  | | \\   /" << std::endl;
    std::cout << "          \\_(.-( )--( )-.)_/           \\_(.-( )--( )-.)_/" << std::endl;
    std::cout << "          /_,\\ ) /  \\ ( /._\\           /_,\\ ) /  \\ ( /._\\    COWS" << std::endl;
    std::cout << "              /_,\\  /._\\                   /_,\\  /._\\" << std::endl << std::endl;
    std::cout << "_-_-_-_-_-_-_-_-_-_| Welcome to Bulls and Cows |_-_-_-_-_-_-_-_-_-_" << std::endl << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " character isogram word I am thinking of?" << std::endl;
    return;
}

void PrintGuess(FString Guess, FBullCowScore Score)
{
    std::cout << "Your guess was: " << Guess << std::endl;
    std::cout << "This guess contained " << Score.Bulls << " Bulls";
    std::cout << " and " << Score.Cows << " Cows" << std::endl;
    return;
}

void PrintGameOverMessage(bool IsGameWon)
{
    std::cout << std::endl << std::endl;
    if (IsGameWon)
    {
        std::cout << "Congratulations, you guessed the word correctly!" << std::endl;
    } else
    {
        std::cout << "Sorry, you lose, better luck next time." << std::endl;
    }
}

void PrintReplayQuestion()
{
    std::cout << std::endl << "Would you like to play again using the same word? (y/n)" << std::endl;
    return;
}

bool IsReplaying()
{
    FString QuestionResponse = "";
    std::getline(std::cin, QuestionResponse);
    if (QuestionResponse.length() > 0 && tolower(QuestionResponse[0]) == 'y')
    {
        return true;
    }
    return false;
}
