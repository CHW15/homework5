/*
* Program Tools Course - HW5
* by Golnaz Sarram
* February 28th, 2015
* The repository address in github is:

* This Program 
*/

// Calling external libraries

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ostream>
#include <cstdlib>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <numeric>
#include <cstring>

using namespace std;

// Declare functions:

// Function for printing the errors into the logfile and terminal

void print_message(ofstream & logfile, ostream & stream, string statement) {
	logfile << statement << "\n";
	stream << statement << "\n";
	return;
}

void print(ofstream & logfile, ostream & stream, char & charater) {
	logfile << (charater) << "\n";
	stream << (charater) << "\n";
	return;
}

// Void functions to open the input and output files

void open_input(ifstream & inputfile, ofstream & logfile, ostream & stream, string inputfilename) {
	inputfile.open(inputfilename.c_str());
	if ( !inputfile.is_open() ) {
		print_message(logfile, stream, "Cannot open input file: ");
	}
}

void open_output(ofstream & outputfile, ofstream & logfile, ostream & stream, string outputfilename) {
	outputfile.open(outputfilename.c_str());
	if ( !outputfile.is_open() ) {
		print_message(logfile, stream, "Cannot open outputfile : ");
	}
}

void open_logfile(ofstream & logfile, string logfilename) {
	logfile.open(logfilename.c_str());
}

// Function for printing the results into the outputfile and terminal


// useful function to convert a string to uppercase (in example:array+struct)



// useful function extract integers from string

enum months { 
	January=1, 
	February, 
	March, 
	April, 
	May, 
	June,
	July, 
	August, 
	September, 
	October, 
	November, 
	December
};

//int ReadDateNumbers( const string & date, vector <int> & v) {
//	istringstream is (date);
//	int n;
//	while ( is >> n ) {
//		v.push_back(n);
//	}
//	return v.size();
//}

// int ReadTimeNumbers( const string & time, vector <int> & w) {
// 	istringstream is (time);
//	int n;
//	while ( is >> n ) {
//		w.push_back(n);
//	}
//	return w.size();
//}

bool is_valid_date (int & mm, int & dd, int & yyyy) {
	if ( mm > 0 && mm < 13) return false;
	if ( dd > 0 && dd < 32) return false;
	if ( yyyy > 1850 && yyyy < 2016 ) return false;
	return true;
}

bool is_valid_time ( int hr, int min, int sec) {
	if ( hr >= 0 || hr < 24 ) return false;
	if ( min >= 0 || min < 60 ) return false;
	if ( sec > 0.0009 || sec <= 59.9999 ) return false;
	return true;
}

enum mag_type {                                     // case insensitive
	ML = 1,
	Ms,
	Mb,
	Mw
};

// Function for convertine a string to uppercase and check for validation 

string uppercase (string & s) {
    string result = s;
    for (int i=0; i < (int)result.size(); i++)
        result[i] = toupper(result[i]);
    return result;
}

bool is_valid_magnitude_type (string magnitude_type) {
	string ss = uppercase(magnitude_type);
	return( (ss == "ML") || (ss == "MS") || (ss == "MB") || (ss == "MW") );
}

enum network_code {                                 // case sensitive
	CE,
	FA,
	NP,
	WR
};

enum type_of_band {
	L,
	B,
	H
};

enum type_of_instrument {
	HG,
	LG,
	NA
};

enum orientation_1 {
	N,
	E,
	Z
};

int main() {

	// Defining the local variables

	string event_ID;
	string inputfilename = "golnaz.in", outputfilename = "golnaz.out", logfilename = "golnaz.log";
	ifstream inputfile;
	ofstream outputfile;
	ofstream logfile;


	// Prompt the user for an input file

	cout << "Enter input filename: ";
	cin >> inputfilename;
	open_input(inputfile, logfile, cout, inputfilename);

	// Generating the log files

	open_logfile(logfile, "golnaz.log");

	// Declare variable types:

	int day = 1, year = 1850, mm = 1, tzl = 0, i = 0;        //("mm/dd/yyyy or mm-dd-yyyy hh:mm:ss.fff time_zone");
	int month = 0, hr = 0, min = 0, delimi_position = 0; 
	string date, time, m, dy, d, y, minsec, Hr, Min, Sec;                  
	//months month2;
	string readline3; ("Earthquake name");
	string Earthquake_name;
	char time_zone[5];
	float sec = 0;

	double longitude = 0, latitude = 0, depth = 0;
	string magnitude_type;
	//mag_type mt[4];
	float magnitude_size;                   // greater than 0 ( > 0) 
	//char station_code_1[3];
	//int station_code_2[5];
	//const int Maxsize = 12;
	//const char Maxchar = 3;


	// Starting the enumeration
	// Inorder to facilitate printing starts at 1



	// Reading the input Header and check for the data correctness
	// First line for event ID

	inputfile >> event_ID;
	print_message ( logfile, cout, "Event ID is read." );

	// Reading second line for Datetime and time zone information

	inputfile >> date;

	// Case 1:

	delimi_position = date.find_first_of("/");
	m = date.substr(0, delimi_position);
	stringstream (m) >> mm;

	dy = date.substr(delimi_position + 1);

	delimi_position = dy.find_first_of("/");
	d = dy.substr(0, delimi_position);
	stringstream (d) >> day;

	y = dy.substr(delimi_position + 1);
	stringstream (y) >> year;

	// Check for date validation

	if ( mm != year) {
		cout << mm << "/" << day << "/" << year << "\n";
		if ( ! is_valid_date( mm, day, year) ) {
		print_message ( logfile, cout, "date of earthquake is not valid" );
		// exit(0);
		} else { 
			return 0;
		}
	}

	// Case 2 (delimiter is deferent):

	delimi_position = date.find_first_of("-");
	m = date.substr(0, delimi_position);
	stringstream (m) >> mm;

	dy = date.substr(delimi_position + 1);

	delimi_position = dy.find_first_of("-");
	d = dy.substr(0, delimi_position);
	stringstream (d) >> day;

	y = dy.substr(delimi_position + 1);
	stringstream (y) >> year;

	// Check for date validation

	if ( mm != year) {
		cout << mm << "/" << day << "/" << year << "\n";
		if ( ! is_valid_date( mm, day, year) ) {
		print_message ( logfile, cout, "date of earthquake is not valid" );
		// exit(0);
		} else { 
			return 0;
		}
	}

	inputfile >> time;

	delimi_position = time.find_first_of(":");
	Hr = time.substr(0, delimi_position);
	stringstream (Hr) >> hr;

	minsec = time.substr(delimi_position + 1);

	delimi_position = minsec.find_first_of(":");
	Min = minsec.substr(0, delimi_position);
	stringstream (Min) >> min;

	Sec = minsec.substr(delimi_position + 1);
	stringstream (Sec) >> sec;

	// Check for time validation

	cout << hr << ":" << min << ":" << sec << "\n";
	if ( ! is_valid_time( hr, min, sec) ) {
		print_message ( logfile, cout, "Time of earthquake is not valid" );
		// exit(0);
	}

	int Maxsize = 5;
	inputfile >> time_zone;
	for (i = 0; i < Maxsize; i++) {
		inputfile >> time_zone[i];
		cout << time_zone[i];
	} 
	cout << "\n";
	tzl = strlen(time_zone);
	if ( tzl != 3 ) {
		print_message ( logfile, cout, "Time_zone is not valid" );
		// exit(0);
	}

	print_message ( logfile, cout, "The second line is read." );

	// Reading the third line for event name

	getline (inputfile, readline3);
	print_message ( logfile, cout, "The third line in header is read." );

	// Reading the fourth line for orintation and magnitude data

	// Orintation entries:
	inputfile >> longitude;
	inputfile >> latitude;
	inputfile >> depth;

	// Magnitude properties:
	inputfile >> magnitude_type;
	if ( ! is_valid_magnitude_type(magnitude_type) ) {
		print_message ( logfile, cout, "The magnitude_type is not valid" );
		// exit(0);
	}

	inputfile >> magnitude_size;
	if ( magnitude_size <= 0 ) {
		print_message ( logfile, cout, "The magnitude_size is not valid" );
		//exit(0);
	}

	print_message ( logfile, cout, "The fourth line in header is read." );

	// Generating the log files

	open_output(outputfile, logfile, cout, "golnaz.out");

    // Start reading the table:

	return 0;
}