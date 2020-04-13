/* *****************************************************************************

CS 142 - Winter 2015
Midterm 1 - Yahtzee

Student Name (First and Last): Hunter Boody
Student NetID: 93-850-5166
Section and Instructor: Section 4 - Ryan Farrell
Development Platform (e.g. Visual Studio Express 2013" or "XCode"): Visual Studio Express 2013

***************************************************************************** */



#include <iostream>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "YahtC++.h"

using namespace std;


// Some constants that you may find useful
const int Char_n = 'n';
const int Char_y = 'y';
//Made these two a constant char so I can use them for the GETYN function
const char CHAR_YES = 'Y';
const char CHAR_NO = 'N';
const int  TURNS_PER_GAME = 13;
const int  SIDES_PER_DIE = 6;






/* *****-***********************************************************************
GETYN()-

DESCRIPTION - This function prompts the user for input in the form of either a
              'Y' or an 'N'.  Your program should accept either upper- or
			  lower-case Y and N.  Any other character that's given as input is
			  invalid and your program should continue to prompt the user until
			  a valid input character (a Y or an N) is received.

PARAMETERS/INPUTS:
    @PROMPT - This string parameter is used as the display prompt for the user.
	          For example, if prompt has the value "Do you want to quit?", then
			  the program will display "Do you want to quit? [Y/N]: " and wait
			  for user input.

RETURNS - Either an upper-case 'Y' or an 'N'

***************************************************************************** */

char getYN(string prompt)
{
	int i = 0;
	//in the while loop until it doesn't equal 0
	while (i==0)
	{
		cout << endl << prompt << endl;
		char userinput;
		cin >> userinput;
			
			//if its uppercase or lowercase y it will accept both
		if (userinput == CHAR_YES || userinput == Char_y)
			{
			char upper = userinput;
			upper = toupper(userinput);
				cout << "" << upper << endl;
				return CHAR_YES;
				i++;
				//adds one to get out of the while loop
			}

			//if its uppercase or lowercase n it will accept both
		else if (userinput == CHAR_NO || userinput == Char_n)
			{
			char upper = userinput;
			upper = toupper(userinput);
				cout << "" << upper << endl;
				return CHAR_NO;
				i++;
				//adds one to get out of the while loop
			}

			else
			{
				cout << "Invalid Selection" << endl;
			}
	}
	return CHAR_NO;    
}







/* *****************************************************************************
GETCHARINRANGE()

DESCRIPTION - This function prompts the user for input in the form of a single
              character in a specified range.  Your program should accept either
			  upper- or lower-case characers, but always return upper case.  If
			  the character that's given by the user is in the specified range
			  (you may assume that the input characters are upper-case),
			  then it should return it (return the upper-case version if a
			  lower-case character was entered).  If the input is not in the
			  valid range, then your program should continue to prompt the user
			  until a valid input character (in the correct range) is received.

PARAMETERS/INPUTS:
    @MIN -    An upper-case character that begins the valid range.
	@MAX -    An upper-case character that ends the valid range.

RETURNS -     An upper-case character in the specified range.


***************************************************************************** */

char getCharInRange(char min, char max)
{
	bool inRange = false;
	//while loop as long as its true
	while (!inRange)
	{
		char letter;
		cin >> letter;

		//if its greater or equal to min or less than or equal to the max character
		if (letter >= min || letter <= max)
		{
			char upper;
			upper = toupper(letter);
			cout << upper << endl;
			return upper;
		}

		//if its anything else it is an invalid selction and will reprompt them
		else if (letter < min || letter > max)
		{
			cout << "Invalid Selection. Enter a choice between [" << min << " and " << max << endl;
			return 'Z';
		}
	}
}







/* *****************************************************************************
ISVALIDOPTION_YAHTZEE()

DESCRIPTION - This function determines whether the values on the five dice
              passed in as parameters constitute a YAHTZEE (all five dice have
			  an identical value).  For example, the values 2 2 2 2 2 represent
			  a YAHTZEE.

PARAMETERS/INPUTS:
    @DIE1 -   This int parameter indicates the current value of the first die.
	          The range for this value is from 1 up to SIDES_PER_DIE.
    @DIE2 -   This int parameter has the value of the second die.  Same range.
	@DIE3 -   This int parameter has the value of the third die.  Same range.
	@DIE4 -   This int parameter has the value of the fourth die.  Same range.
	@DIE5 -   This int parameter has the value of the fifth die.  Same range.

RETURNS - Either TRUE (if the values are all identical) or FALSE (otherwise).

***************************************************************************** */

bool isValidOption_YAHTZEE(int die1, int die2, int die3, int die4, int die5)
{	
	//if they all equal the same number
	if (die1 == die2 && die3 == die4 && die5==die1 && die2 == die3)
	{
		return true;
	}

	else

	{
		return false;
	}
}





/* *****************************************************************************
ISVALIDOPTION_SMSTRAIGHT()

DESCRIPTION - This function determines whether there is a small straight.  For
              example if the dice values were 2 5 4 3 4, there is a small
			  straight 2-3-4-5 present.  Any sequence of four consecutive
			  values (each in the range 1-6) is a small straight.

PARAMETERS/INPUTS:
    @DIE1 -   This int parameter indicates the current value of the first die.
	          The range for this value is from 1 up to SIDES_PER_DIE.
    @DIE2 -   This int parameter has the value of the second die.  Same range.
	@DIE3 -   This int parameter has the value of the third die.  Same range.
	@DIE4 -   This int parameter has the value of the fourth die.  Same range.
	@DIE5 -   This int parameter has the value of the fifth die.  Same range.

RETURNS -     Either TRUE (if a small straight is present in the dice) or
              FALSE (otherwise).

***************************************************************************** */

bool isValidOption_SmStraight(int die1, int die2, int die3, int die4, int die5)
{
	//setting up the array here
	int die[5] = { die1, die2, die3, die4, die5 };
	sort(die, die + 4);
	int lastDie = die[0];
	int a = 1;

	//if the lowest number is a 4, or the highest number is a 3 there will not be a straight
	if (die[0] >= 4 || die[4] <= 3)
	{
		return false;
	}

	//iterate through the dice
	for (int i = 0; i < 5; i++)
	{
		//current die is one greater than the last one..the numbers are in sequence
		if (die[i] == lastDie + 1)
		{
			a++;
		}
		//if the dice are not in order it should get it ex. 1,3,4,5,6
		else
		{
			a = 1;
		}

		//small straight is true when the sequence is 4 or larger
		if (a >= 4)
		{
			return true;
			lastDie = die[i];
		}


	}
	return false;

}







/* *****************************************************************************
ISVALIDOPTION_3OFAKIND()

DESCRIPTION - This function determines whether there are 3 (or more) dice that
              have the same value.  For example if the dice values were
			  2 5 5 1 5, there is a 3-of-a-kind, the fives.

PARAMETERS/INPUTS:
    @DIE1 -   This int parameter indicates the current value of the first die.
	          The range for this value is from 1 up to SIDES_PER_DIE.
    @DIE2 -   This int parameter has the value of the second die.  Same range.
	@DIE3 -   This int parameter has the value of the third die.  Same range.
	@DIE4 -   This int parameter has the value of the fourth die.  Same range.
	@DIE5 -   This int parameter has the value of the fifth die.  Same range.

RETURNS -     Either TRUE (if 3 or more dice have the same value) or
              FALSE (otherwise).

***************************************************************************** */

bool isValidOption_3OfAKind(int die1, int die2, int die3, int die4, int die5)
{
	int die[5] = { die1, die2, die3, die4, die5};

	// This is the 5 die that it will look at
	for (int a = 0; a < 5; a++) 
	{
		//my counter
		int three_of_a_kind = 0;

		// Compare die against each other
		for (int i = 0; i < 5; i++) 
		{
			//if they are three of a kind
			if (die[a] == die[i])
			{
				three_of_a_kind += 1; 
			}

			//if not
			else if (three_of_a_kind == 3)
			{
				return true;
			}
		}
	}
}








/* *****************************************************************************
POINTSFOR_SIXES()

DESCRIPTION - This function computes the number of points for sixes.  If two
              dice show sixes, then this would return 12, if four dice show
			  sixes, then this function would return 24, and so forth.

PARAMETERS/INPUTS:
    @DIE1 -   This int parameter indicates the current value of the first die.
	          The range for this value is from 1 up to SIDES_PER_DIE.
    @DIE2 -   This int parameter has the value of the second die.  Same range.
	@DIE3 -   This int parameter has the value of the third die.  Same range.
	@DIE4 -   This int parameter has the value of the fourth die.  Same range.
	@DIE5 -   This int parameter has the value of the fifth die.  Same range.

RETURNS -     The total of all dice showing a six (an int).

***************************************************************************** */

int pointsFor_Sixes(int die1, int die2, int die3, int die4, int die5)
{
	//array of all die
	int die[5] = { die1, die2, die3, die4, die5 };
	int six_counter = 0;

	//look at all the die
	for (int j = 0; j < 5; j++)
	{
		//see if one of them is 6
		if (die[j] == 6)
		{
			six_counter = six_counter + 6;
		}
	}
	return six_counter;
}




