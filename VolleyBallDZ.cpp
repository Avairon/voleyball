﻿#include <iostream>
#include <string>
#include <fstream>

int teamA[6]; 
int teamB[6]; // массивы для хранения сторон команд

int partScoreA = 0;
int partScoreB = 0; //счет партии

int scoreA = 3;
int scoreB = 0; //счет (в общем)

int lastGoal = 0;

//std::ofstream log;

void reverse(int arra1[6]) //функция для перехода
{
        int buffer1 = arra1[5];
        arra1[5] = arra1[4];
        arra1[4] = arra1[3];
        arra1[3] = arra1[2];
        arra1[2] = arra1[1];
        arra1[1] = arra1[0];
        arra1[0] = buffer1;
    
}

void graphic(int arra1[6], int arra2[6]) //функция для отображения поля
{
    std::cout << "\n\nScore A: " << scoreA << "(" << partScoreA << ")" << "  Score A: " << scoreB << "(" << partScoreB << ")\n\n";
    std::cout << "      " << arra1[2] << "  " << arra1[3] << "  |  " << arra2[5] << "  " << arra2[0] << "(P)\n";
    std::cout << "      " << arra1[1] << "  " << arra1[4] << "  |  " << arra2[4] << "  " << arra2[1] << "\n";
    std::cout << "   (P)" << arra1[0] << "  " << arra1[5] << "  |  " << arra2[3] << "  " << arra2[2] << "\n\n";
}

void startGame(int arra1[6], int arra2[6]) //функция для ввода команд
{
    //log.open("D:\log.txt");
    //log << "Game was started!";

    std::cout << "Enter command A" << "\n";

    for (int i = 0; i < 6; i++)
    {
        std::cout << "Player " << i + 1 << ": ";
        std::cin >> arra1[i];
    }

    std::cout << "Enter command B" << "\n";

    for (int i = 0; i < 6; i++)
    {
        std::cout << "Player " << i + 1 << ": ";
        std::cin >> arra2[i];
    }
}

void action(int* lastGoal, int* partScoreA, int* partScoreB) //функция действия
{
    std::string teamAction;
    int playerAction;
    std::string whatAction;


    std::cout << "which team performed the action?(a or b)\n";
    std::cin >> teamAction;

    if (teamAction != "a" && teamAction != "b")
    {
        std::cout << "You choose wrong team, please retry\n";
        return;
    }

    std::cout << "\nwhat action was performed?\n";
    std::cout << "a - Attack; b - Block, p - Supply, o - Error (P.S. Please, don't write anything except a, b, p, or o) \n";
    std::cin >> whatAction;                      

    if(whatAction != "o")
    { 
        std::cout << "which player performed the action?(player's position number)\n";
        std::cin >> playerAction;

        if (playerAction <= 0 && playerAction >= 7)
        {
            std::cout << "You choose wrong player place number, please retry\n";
            return;
        }

        if (teamAction == "a")
        {
            if (*lastGoal == 2) reverse(teamA);
            *lastGoal = 1;
            *partScoreA += 1;
        }

        if (teamAction == "b")
        {
            if (*lastGoal == 1) reverse(teamB);
            *lastGoal = 2;
            *partScoreB += 1;
        }
    }

    if (whatAction != "a" && whatAction != "b" && whatAction != "p" && whatAction != "o")
    {
        std::cout << "You choose wrong action, please retry\n";
        return;
    }
    else
    {
        //log.write("");
    }
}

void scorePlus(int* partScoreA, int* partScoreB, int* scoreA, int* scoreB) //функция меняющая очки партий
{
    if (*partScoreA == 25) { *partScoreA = 0; *scoreA += 1; }
    if (*partScoreB == 25) { *partScoreB = 0; *scoreB += 1; }
}

void playerReplace(int arra1[6], int arra2[6]) //функция замены
{
    std::string team;
    int playerPlace;
    int playerNum;

    std::cout << "which team?\n";
    std::cin >> team;

    if (team != "a" && team != "b")
    {
        std::cout << "You choose wrong team, please retry\n";
        return;
    }

    std::cout << "which player?(player's position number)\n";
    std::cin >> playerPlace;

    if (playerPlace <= 0 && playerPlace >= 7)
    {
        std::cout << "You choose wrong player place number, please retry\n";
        return;
    }

    std::cout << "which player to replace?(player number\n";
    std::cin >> playerNum;

    if (team == "a") arra1[playerPlace - 1] = playerNum;
    if (team == "b") arra2[playerPlace - 1] = playerNum;
    
}

int main()
{
    

    startGame(teamA, teamB);

    while (true)
    {
        graphic(teamA, teamB);
        int choose;
        std::cout << "what do you want to do?\n";
        std::cout << "1 - Replace Player, 2 - Action\n";
        std::cin >> choose;

        switch (choose)
        {
        case(1):
            playerReplace(teamA, teamB);
            break;
        case(2):
            action(&lastGoal, &partScoreA, &partScoreB);
            break;
        }

        scorePlus(&partScoreA, &partScoreB, &scoreA, &scoreB);

        if (scoreA == 3) { std::cout << "Team A win!\n"; break; }
        if (scoreB == 3) { std::cout << "Team B win!\n"; break; }
    }
}


