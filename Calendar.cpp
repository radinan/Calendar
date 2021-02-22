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
	case 0: return 7; //Sun
	case 1: return 1; //Mon
	case 2: return 2; //Tue
	case 3: return 3; //Wed
	case 4: return 4; //Thu
	case 5: return 5; //Fri
	case 6: return 6; //Sat
	default: assert(false);
	}
}

int main()
{
	std::string weekDay;
	switch (findDay(1, 1, 2015))
	{
	case 7: weekDay = "Sun"; break;
	case 1: weekDay = "Mon"; break;
	case 2: weekDay = "Tue"; break;
	case 3: weekDay = "Wed"; break;
	case 4: weekDay = "Thurs"; break;
	case 5: weekDay = "Fri"; break;
	case 6: weekDay = "Sat"; break;
	}
	std::cout << weekDay << std::endl;

	return 0;
}
