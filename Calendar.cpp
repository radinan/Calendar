#include <iostream>
#include <string>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <vector>

int findDay(int dayOfMonth, int monthNumber, int year) //using Zeller's algorithm
{
	//validation
	assert(monthNumber > 0 && monthNumber < 13);
	assert(year >= 1582); //Gregorian calendar was introduced in October 1582
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

	int monthZellerNumber = 0, yearZeller = year; //March = 1, April = 2 ... January = 11, February = 12; 
	if (monthNumber > 2 && monthNumber < 13)
		monthZellerNumber = monthNumber - 2;
	else
	{
		monthZellerNumber = monthNumber + 10;
		--yearZeller;
	}

	int lastTwoDigitsOfYear = yearZeller % 100, firstTwoDigitsOfYear = yearZeller;
	while (firstTwoDigitsOfYear > 99)
		firstTwoDigitsOfYear /= 10;
	
	int funcZeller = dayOfMonth + (13 * monthZellerNumber - 1) / 5 + lastTwoDigitsOfYear + (lastTwoDigitsOfYear / 4)
								   - 2 * firstTwoDigitsOfYear + (firstTwoDigitsOfYear / 4);
	int remainder = funcZeller % 7;
	while (remainder < 0)
		remainder += 7;
	

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
	default: assert(false);
	}
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
std::vector<std::pair<int, std::string>> createCalendar(int year) //28 symbs width -> 14th, 15th - in the middle
{
	std::vector<std::pair<int, std::string>> allMonths; // int -> num of rows(with days), string -> whole month

	for (int i = 1; i <= 12; ++i)
	{
		std::stringstream s;

		//Name of the month - centrally aligned
		std::string nameOfMonth = monthName(i);
		int spacesBeforeName = 0, spacesAfterName = 0, nameLength = nameOfMonth.size();
		if (nameLength % 2 == 0)
		{
			spacesBeforeName = 14 - (nameLength - 2) / 2;
			spacesAfterName = spacesBeforeName;
		}
		else
		{
			spacesBeforeName = 14 - (nameLength - 1) / 2;
			spacesAfterName = spacesBeforeName + 1;
		}
		for (int j = 1; j < spacesBeforeName; ++j)
			s << " ";
		s << nameOfMonth;
		for (int j = 1; j < spacesAfterName; ++j)
			s << " ";
		s << "\n";

		//Names of the weekdays
		s << "Sun" << " " << "Mon" << " " << "Tue" << " " << "Wed" << " " << "Thu" << " " << "Fri" << " " << "Sat" << " " << "\n";

		//Days of the month
		int day = findDay(1, i, year), lastDay = daysOfMonth(i, year), counter = 0, daysRows = 1;
		for (int k = 1; k < day; ++k)
		{
			s << "   "; //3 spaces
			s << " ";
			++counter;
		}
		for (int n = 1; n <= lastDay; ++n)
		{
			if (counter == 7)
			{
				s << "\n";
				counter = 0;
				daysRows++;
			}
			if (n > 0 && n < 10)
				s << " " << n << " "; //3 chars
			else
				s << n << " ";
			s << " ";
			counter++;
		}
		for (int k = counter; k < 7; ++k)
		{
			s << "   ";
			s << " ";
			++counter;
		}
		s << "\n";

		allMonths.push_back(std::make_pair(daysRows, s.str()));
	}

	return allMonths;
}

std::string nSpaces(int n)
{
	std::string spaces;
	for (int i = 0; i < n; ++i)
		spaces += " ";
	return spaces;
}
std::pair<int, std::string> merge(const std::pair<int, std::string>& lhs, const std::pair<int, std::string>& rhs)
{
	std::stringstream s1(lhs.second), s2(rhs.second);
	std::pair<int, std::string> merged;
	std::string lhs2, rhs2, spaces = nSpaces(31); //28 spaces + 3 for separation
	bool flag = false; //whether lhs contains 2 merged months (both shorter than rhs)

	if (lhs.first > rhs.first)
	{
		while (std::getline(s1, lhs2))
		{
			if (std::getline(s2, rhs2))
				merged.second += lhs2 + "   " + rhs2 + "\n"; 
			else
				merged.second += lhs2 + spaces + "\n"; 
		}
		merged.first = lhs.first;
	}
	else if(lhs.first < rhs.first)
	{
		while (std::getline(s2, rhs2))
		{
			if (std::getline(s1, lhs2))
			{
				merged.second += lhs2 + "   " + rhs2 + "\n";
				if (lhs2.size() > rhs2.size())
					flag = true;
			}
			else
			{
				if(flag)
					merged.second += spaces + spaces + rhs2 + "\n"; //5 rows, 5 rows, 6 rows => needs double spaces
				else
					merged.second += spaces + rhs2 + "\n";
			}
		}
		merged.first = rhs.first;
	}
	else
	{
		while (std::getline(s1, lhs2) && std::getline(s2, rhs2))
				merged.second += lhs2 + "   " + rhs2 + "\n"; 

		merged.first = lhs.first;
	}

	return merged;
}

void printCalendar(int year, std::ostream& out) //3 x 4
{
	//89 width
	std::vector<std::pair<int, std::string>> vec(createCalendar(year));
	out << std::setw(47) << "Year" << "\n";
	out << std::setw(47) << year << "\n" << "\n";

	for (int i = 0; i < 12; i += 3)
	{
		out << merge(merge(vec[i], vec[i + 1]), vec[i + 2]).second;
		out << std::endl;
	}
}

int main()
{
	printCalendar(2020, std::cout);

	return 0;
}
