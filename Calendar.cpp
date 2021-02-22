#include <iostream>
#include <string>
#include <cassert>

//using Zeller's algorithm
int findDay(int dayOfMonth, int monthNumber, int year)
{
	assert(monthNumber > 0 && monthNumber < 13);
	assert(year > 0);
	switch (monthNumber)
	{
	case 2:		
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //leap year
			assert(dayOfMonth > 0 && dayOfMonth < 30);
		else
			assert(dayOfMonth > 0 && dayOfMonth < 29);
		break;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		assert(dayOfMonth > 0 && dayOfMonth < 32);
		break;
	case 4: case 6: case 9: case 11:
		assert(dayOfMonth > 0 && dayOfMonth < 31);
		break;
	default: assert(false);
	}


	int monthZellerNumber = monthNumber, yearZeller = year; //March = 1, April = 2 ... January = 11, February = 12; 
	if (monthNumber > 2 && monthNumber < 13)
		monthZellerNumber = monthNumber - 2;
	else
	{
		monthZellerNumber = monthNumber + 10;
		yearZeller--;
	}

	int lastTwoDigitsOfYear = yearZeller % 100,
		firstTwoDigitsOfYear = yearZeller;
	while (firstTwoDigitsOfYear > 99)
		firstTwoDigitsOfYear /= 10;
	
	int funcZeller = dayOfMonth + ((13 * monthZellerNumber - 1) / 5) + lastTwoDigitsOfYear + (lastTwoDigitsOfYear / 4)
		- 2 * firstTwoDigitsOfYear + (firstTwoDigitsOfYear / 4);

	int remainder = funcZeller % 7;
	while (remainder < 0)
	{
		remainder += 7;
	}

	switch (remainder)
	{
	case 0: return 1; //Sun
	case 1: return 2; //Mon
	case 2: return 3; //Tue
	case 3: return 4; //Wed
	case 4: return 5; //Thu
	case 5: return 6; //Fri
	case 6: return 7; //Sat
	default: assert(false);
	}
}
std::string monthName(int monthNumber)
{
	switch (monthNumber)
	{
	case 1: return "January";
	case 2: return "February";
	case 3: return "March";
	case 4: return "April";
	case 5: return "May";
	case 6: return "June";
	case 7: return "July";
	case 8: return "August";
	case 9: return "September";
	case 10: return "October";
	case 11: return "November";
	case 12: return "December";
	//default: assert(false);
	}
}
void printDaysNames()
{
	std::cout << "Sun" << " " << "Mon" << " " << "Tue" << " " << "Wed" << " " << "Thu" << " " << "Fri" << " " << "Sat" << std::endl;
}
int daysOfMonth(int monthNumber, int year)
{
	switch (monthNumber)
	{
	case 2:
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //leap year
			return 29;
		else
			return 28;
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	default: assert(false);
	}
}
void printCalendar(int year)
{
	for (int i = 1; i <= 12; ++i) //month
	{
		std::cout << monthName(i) << std::endl;
		printDaysNames();

		int date = 1, day = findDay(1, i, year), lastDay = daysOfMonth(i, year), counter = 0;
		
		for (int k = 1; k < day; ++k)
		{
			std::cout << "   ";
			std::cout << " ";
			++counter;
		}
		for (int n = 1; n <= lastDay; ++n)
		{
			if (counter == 7)
			{
				std::cout << std::endl;
				counter = 0;
			}
			if (n > 0 && n < 10)
				std::cout << " " << n << " ";
			else
				std::cout << n << " ";
			std::cout << " ";
			counter++;
		}

		std::cout << std::endl << std::endl;

	}
}
int main()
{
	printCalendar(2020);

	return 0;
}
