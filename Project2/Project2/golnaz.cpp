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

using namespace std;

// Declare functions:

// Function for printing the errors into the logfile and terminal

void print_message(ofstream & logfile, ostream & stream, string statement) {
	logfile << statement << "\n";
	stream << statement << "\n";
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

int ReadDateNumbers( const string & date, vector <int> & v) {
	istringstream is (date);
	int n;
	while ( is >> n ) {
		v.push_back(n);
	}
	return v.size();
}

int ReadTimeNumbers( const string & time, vector <int> & w) {
	istringstream is (time);
	int n;
	while ( is >> n ) {
		w.push_back(n);
	}
	return w.size();
}

bool is_valid_date (string date, int mm, int & dd, int & yyyy) {
	if ( mm < 1 || mm > 12) return false;
	if ( dd < 1 || dd > 31) return false;
	if ( yyyy < 1850 || yyyy > 2015 ) return false;
}

bool is_valid_time (string time, int hr, int min, int sec, int sec_frac) {
	if ( hr < 1 || hr > 24 ) return false;
	if ( min < 0 || min > 59 ) return false;
	if ( sec < 0 || sec > 59 ) return false;
	if ( sec_frac < 1000 || sec_frac > 999 ) return false;
}

enum mag_type {                                     // case insensitive
	ML,
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

	// Calling the open functions:
	// Generating output and log files

	open_output(outputfile, logfile, cout, "golnaz.out");
	open_logfile(logfile, "golnaz.log");

	// Declare variable types:

	int day = 0, year = 0, mm = 0, size = 0, i = 0;
	int hr = 0, min = 0, sec_frac = 0, sec = 0;

	string date, time;                                              //("mm/dd/yyyy or mm-dd-yyyy hh:mm:ss.fff time_zone");
	months month;
	string readline3; ("Earthquake name");
	string Earthquake_name;
	char time_zone[3];
	int number = 0;

	double longitude = 0, latitude = 0, depth = 0;
	string magnitude_type;
	mag_type mt[4];
	float magnitude_size;                   // greater than 0 ( > 0) 
	char station_code_1[3];
	int station_code_2[5];
	const int Maxsize = 12;
	const char Maxchar = 3;


	// Starting the enumeration
	// Inorder to facilitate printing starts at 1



	// Reading the input Header and check for the data correctness
	// First line for event ID

	inputfile >> event_ID;
	print_message ( logfile, cout, "Event ID is read." );

	// Reading second line for Datetime and time zone information

	inputfile >> date;

	// if ( ! format("%mm/%dd/%yyyy || "%mm-%dd-%yyyy) {

	vector <int> v;
	ReadDateNumbers ( date, v);
	for (int i = 0; i < (int)v.size(); i++) {
		v[i=1] = mm;
		v[i=2] = day;
		v[i=3] = year;
	}

	if ( ! is_valid_date(date, mm, day, year) ) {
		print_message ( logfile, cout, "date of earthquake is not valid" );
	}

	// if ( ! sizeof(date) < 11 ) {
	//	print_message ( logfile, cout, "date of earthquake is not valid" );
	//}
	
	// if ( ! format("%hr:%min:%sec.%sec_frac ) {

	inputfile >> time;

	vector <int> w;
	ReadTimeNumbers ( time, w);
	for (int i = 0; i < (int)w.size(); i++) {
		w[i=1] = hr;
		w[i=2] = min;
		w[i=3] = sec;
		w[i=4] = sec_frac;
	}

	if ( ! is_valid_time) {
		print_message ( logfile, cout, "time is not valid" );
	}

	// if ( ! sizeof(time) < 12 ) {
	//	print_message ( logfile, cout, "time of earthquake is not valid" );
	//}

	inputfile >> time_zone;
	
	// if (sizeof(char) > 3 || sizeof(char) < 3 ) {
		// print_message ( logfile, cout, "time_zone is not valid" );
	//}
	// cout << time_zone;
	
	print_message ( logfile, cout, "Second line is read." );

	inputfile >> longitude;
	inputfile >> latitude;
	inputfile >> depth;
	inputfile >> magnitude_type;

	inputfile >> magnitude_size;

	// magnitude_type = (string)readline4[4];
	// if (lengthof() > 3 || sizeof(char) < 3 ) {
	//	print_message ( logfile, cout, "time_zone is not valid" );
	// }
		
	getchar();
	return 0;
}