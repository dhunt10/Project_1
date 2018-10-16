

//
//  main.cpp
//  project1b
//
//  Created by Darin Hunt on 9/27/18.
//  Copyright © 2018 Darin Hunt. All rights reserved.
//
#include "Header.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <vector>

using namespace std;

int main()
{
	srand(time(NULL));
    int range, digits;
    char answer;
    cout << "Please enter a digits" << endl;
    cin >> digits;
    cout << "Please enter a range" << endl;
    cin >> range;
    mastermind game1(digits, range);
    game1.playGame();
    
    cout << "Do You want to play again? (y/n)" << endl;
    cin >> answer;
    
    if (answer == 'y')
    {
        system("CLS");
        system("CLC");
        system("pause");
        main();
    }
    
return 0;
}

