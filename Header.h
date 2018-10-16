
//
//  Header.h
//  project1b
//
//  Created by Darin Hunt on 9/27/18.
//  Copyright © 2018 Darin Hunt. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <time.h>
#include <algorithm>


using namespace std;


///////////////////////////////////////

class Code
{
public:
    Code(); //n is the number of digits and m is the range, constructor
    void randomVector(vector<int> &vRand, int &n, int &m); //takes in initialized vector filled with zeros and sets values to random integers
    int checkCorrect(const vector <int> &Guess, const vector <int> &vRand, int n); //guess parameter is passed and returns number of correct digit in correct location
    int checkIncorrect(const vector <int> &vGuess, const vector <int> &vRand, int n); //guess parameter is passed and returns number of incorrect digit in correct location
    void makeHumanGuess(vector <int> &vGuess, int n);
    void eraseVector();
private:
    vector <int> listofUsed; //cleared
    int digits; //n
    int range; //m
    vector <int> numberSetRand;
    vector <int> numberSetGuess;
};

Code::Code() //constructor
{
	
}

void Code::randomVector(vector<int> &vRand, int &n, int &m) //placed before constructor so constructor can use this function
{
	digits=n;
	range=m;
    int i;
    int value;
    for (i = 0; i < digits; i++) //for loop iterizes until it reaches max value of n
    {
		
        value = rand() % range;
        //cout << value<< " ";
        
        vRand.push_back(value);//random integer form 0-value of  m //second way to do it
   		numberSetRand.push_back(value);
   		
    }
    
cout << endl;
}

void Code::makeHumanGuess(vector <int> &vGuess, int m)
{
    vGuess.push_back(m);
    numberSetGuess.push_back(m);
}



int Code::checkCorrect(const vector <int> &vGuess, const vector <int> &vRand, int n) //takes in both the random vector, the users guess as well as the number of digits
{
	
    int value = 0;
    
    for (int i = 0; i < 5; i++)
    {
    	
        int A = vGuess[i];
        int B = vRand[i];
        if (A == B) //can go head to head because they are in the same spot in each vector
            
            
            value++;
        else //if (vGuess.at(i)!=vRand.at(i))
            
            
            continue;
    }
    //    have it return a number if that number is equal to digits make it end
    
    
    return value;
}

int Code::checkIncorrect(const vector <int> &vGuess, const vector <int> &vRand, int n) //takes in both the random vector, the users guess as well as the number of digits and returns nunmber of solo digits found
{
    int value = 0;
    listofUsed.clear();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (vRand[i] != vGuess[i] && vRand[j] != vGuess[j] && vRand[i] == vGuess[j]) //double for loop so that we can just see if they contain the same numbers, no value is added if they are the same location
            {
                if (find(listofUsed.begin(), listofUsed.end(), vGuess[i]) == listofUsed.end())
                {
                    listofUsed.push_back(vGuess[i]);
                    value++;
                }
                else
                    continue;
                
            }
            
            
        }
    }
    
    
    return value;
}

void Code::eraseVector()
{
	numberSetGuess.clear();
}


class response //response class
{
public:
    response();
    int getcorrectNumber() const;
    int getincorrectNumber() const;
    void setNumber(const vector <int> &vGuess, const vector <int> &vRand, int n, int m);
    friend bool operator == (const response &lhs, const response &rhs);
    friend ostream& operator << (ostream& ostr, const response &lhs);
    void clean();
private:
    int correct;
    int incorrect;
};

response::response() //constructor initializes with two zeros
{
    correct = 0;
    incorrect = 0;
}

void response::setNumber(const vector <int> &vGuess, const vector <int> &vRand, int n, int m) //sets the correct and incorrect numbers by calling the fucntions to be run
{
    Code code2;
    correct = code2.checkCorrect(vGuess, vRand, n); //calls correct fucntion and sends two vectors and the number of digits
    incorrect = code2.checkIncorrect(vGuess, vRand, n); //calls incorrect fucntion and sends the same as the previous fucntion
}

int response::getcorrectNumber() const //returns correct number from response
{
    return correct;
}

int response::getincorrectNumber() const //returns incorrect umber from response
{
    return incorrect;
}

bool operator == (const response &lhs, const response& rhs) //defines how to compare two responses
{
    if ((lhs.getcorrectNumber() == rhs.getcorrectNumber()) && (lhs.getincorrectNumber()== rhs.getincorrectNumber()))
        return 1;
    else
        return 0;
}

ostream& operator << (ostream& ostr, const response &lhs) //defines how to output a response
{
    ostr << "( " << lhs.correct << " , " << lhs.incorrect << " )" << endl;
    return ostr;
}

class mastermind //class mastermind
{
public:
    mastermind(int n, int m);
    mastermind();
    void printSecretCode(vector <int> &Random);
    Code code1; //object
    Code human; //object
    Code humanGuess(); //function with return type code
    response getResponse(const Code &guess, const vector <int> &vGuess, const vector <int> &vRand);
    bool isSolved(const response &lhs);
    void playGame();
    int returnDigits();
    int returnRange();
    vector <int> humanGuessVector; //defines vector that will hold guess
    vector <response> holder;
    friend ostream& operator << (ostream& ostr, const response &lhs); //friend operator needed to print response
private:
    int digits;
    int range;
};
///////////////////////////////////////

mastermind::mastermind(int n, int m) //constructor
{
    digits = n;
    range = m;
}

mastermind::mastermind() //defualt constructor
{
    digits = 5;
    range = 10;
}

int mastermind::returnDigits() //returns digits 
{
	return digits;
}

int mastermind::returnRange() //returns range
{
	return range;
}

void mastermind::printSecretCode(vector <int> &Random) //prints the code at the end of program
{
    cout << "Secret Code : " << endl;
    for (int i = 0; i < digits; i++)
        cout << Random[i]<< " "<< endl;
}

Code mastermind::humanGuess() //fucntion that gets human guess
{
    humanGuessVector.clear(); //makes sure it is empty
    int value; //
    if (humanGuessVector.empty()==true) //only runs if vector is empty
    {
    for (int i = 0; i < digits; i++)
    {
    	
        cout << "Please enter a number" << endl; 
        cin >> value;
        human.makeHumanGuess(humanGuessVector, value); //calls function explained in Code class
    }
    return human; //returns the object
}
	else 
		cout << "vector not empty"<<endl;
}

response mastermind::getResponse(const Code &guess, const vector <int> &vGuess, const vector <int> &vRand) //get response asks for a code object and two vectors full of numbers
{
    response response1; //initilizes object
    response1.setNumber(vGuess, vRand, digits, range); //calls set
    cout << response1; //outputs s response, defined in operator
    return response1; //returns the object
}

bool mastermind::isSolved(const response &lhs) //takes in response object and checks correct number
{
    if (lhs.getcorrectNumber() == digits)
        return 1;
    else
        return 0;
}

void mastermind::playGame() //inititates game
{
    int count = 1; 
    vector <int> emp; //empty vector will become randomized 
    code1.randomVector(emp, digits, range); //calls for vector to be randomized
    
    while (count != 11) //iterizes for 10 turns
    {    
        Code guess = humanGuess(); //initializes code object
        response final = getResponse(guess, humanGuessVector, emp); //function gets a response by sending an object, and two vectors 
        holder.push_back(final);
		if (isSolved(final) == 1) //ifSolved returns 1 if the game is won
        {
            cout << "You Win" << endl;
            cout << "It took you " << count << " guesses! Well Done!" << endl;
            exit(0);
        }
        else
        {
            cout << "You are at " << count << " Guesses, " << "You have " << 10 - count << " left" << endl;
            count++; //value gets added so user can only do 10 turns
        }   
    }
    printSecretCode(emp); //prints
    
}


#endif /* Header_h */
