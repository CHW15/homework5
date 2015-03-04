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

void print_string(ofstream & logfile, ostream & stream, string & string) {
	logfile << (string) << "\n";
	stream << (string) << "\n";
	return;
}

// Function for printing the results into the outputfile and terminal

void print_position(ofstream & logfile, ostream & stream, int & position) {
	logfile << (position) << "\n";
	stream << (position) << "\n";
	return;
}

void print_output(ofstream & outputfile, ostream & stream, unsigned long long & Fibonacci_Table, int & position) {
	outputfile << Fibonacci_Table << "  ";
	if ( position % 10 == 0 ) {
		outputfile << "\n";
	}

	stream << Fibonacci_Table << "  ";
	if ( position % 10 == 0 ) {
		stream << "\n";
	}
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

// Define enumerator types

enum Months { 
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

enum magnitude_type {                                     // case insensitive
	ML = 1,
	Ms,
	Mb,
	Mw
};

enum Network_code {                                 // case sensitive
	CE,
	FA,
	NP,
	WR
};

enum Type_of_band {
	Longperiod,
	Shortperiod,
	Broadband
};

enum Type_of_instrument {
	HighGain,
	LowGain,
	Accelerometer
};

enum Orientation {
	N,
	E,
	Z
};

string Month_Num_to_namestring (Months aa) {
	switch (aa) {
	case January:   return "January";
	case February:  return "February";
	case March:     return "March";
	case April:     return "April";
	case May:       return "May";
	case June:      return "June";
	case July:      return "July";
	case August:    return "August";
	case September: return "September";
	case October:   return "October";
	case November:  return "November";
	case December:  return "December";
	}
	exit(EXIT_FAILURE);
}

Months number_to_months (int a){
    
    if (a == 1)  return January;
    if (a == 2)  return February;
    if (a == 3)  return March;
    if (a == 4)  return April;
    if (a == 5)  return May;
    if (a == 6)  return June;
    if (a == 7)  return July;
    if (a == 8)  return August;
    if (a == 9)  return September;
    if (a == 10) return October;
    if (a == 11) return November;
    if (a == 12) return December;
    
    // It should never get here!!
    exit(EXIT_FAILURE);
}

// Functions for input header inorder to check date and time validation 

bool is_valid_date (int & mm, int & dd, int & yyyy) {
    bool date_f=1;
    if ( mm < 0 || mm > 13) {date_f=0;}
    if ( dd < 0 || dd > 32) {date_f=0;}
    if ( yyyy < 1850 || yyyy > 2016 ) {date_f=0;}
	return date_f;
}

bool is_valid_time ( int hr, int min, int sec) {
    bool time_f=1;
    if ( hr < 0 || hr > 24 ) {time_f=0;}
    if ( min < 0 || min > 60 ) {time_f=0;}
    if ( sec < 0.0009 || sec > 59.9999 ) {time_f=0;}
	return time_f;
}

// Functions for report list for converting a string to uppercase and check for validation 

string uppercase (string & s) {
	string result = s;
	for (int i = 0; i < (int)result.size(); i++)
		result[i] = toupper(result[i]);
	return result;
}

bool is_valid_magnitude_type (string magnitude_type) {
	string ss = magnitude_type;
	return( (ss == "ML") || (ss == "MS") || (ss == "MB") || (ss == "MW") );
}

bool is_valid_Network_code (string net_code) {
	string ss = uppercase(net_code);
	return( (ss == "CE") || (ss == "CI") || (ss == "FA") || (ss == "NP") || (ss == "WR") );
}

bool is_valid_Type_of_band (string band_type) {
	string ss = band_type;
	return( (ss == "L") || (ss == "B") || (ss == "H") );
}

bool is_valid_Type_of_instrument (string inst_type) {
	string ss = inst_type;
	return( (ss == "H") || (ss == "L") || (ss == "N") );
}

bool is_valid_Orientation (string orientation) {
	string ss = uppercase(orientation);
	return( (ss == "N") || (ss == "E") || (ss == "Z") );
}

// Defining the main struct of event report propertires

struct Satation_records {
	Network_code         net_code;
	string               Station_Name;
	Type_of_band         band_type;
	Type_of_instrument   inst_type;
	Orientation          orientation;
};

const int MAXSIZE = 300;

// read the input -- pass back whether error or normal as result
// stations' name is in db (passed by reference because it is an array of strings)
// also number of cars read is also passed back...
/*
bool read_input (string & logfilename,  Satation_records db[MAXSIZE], int & code, int entry_pos  ) {

	string net_code;
	string band_type;
	string orientation;
	string inst_type;
	string orientation1;
	int    orientation2;
	ofstream outputfile;
	ofstream logfile;
	ifstream inputfile;

	code = 0;
	entry_pos = 0;

	while ( code < MAXSIZE ) {

		if ( !(inputfile >> net_code >> db[code].Station_Name >> band_type 
			>> inst_type >> orientation ) ) 
			break;

		entry_pos++;
		if ( !is_valid_Network_code (net_code) ) {
			print_message ( logfile, cout, "Invalid_Network_code at position:" );
			print_position(logfile, cout, entry_pos);
		}

		entry_pos++;
		if ( !is_valid_Type_of_band (band_type) ) {
			print_message ( logfile, cout, "Invalid_Network_code at position:" );
			print_position(logfile, cout, entry_pos);
		}

		entry_pos++;
		if ( !is_valid_Type_of_instrument (inst_type) ) {
			print_message ( logfile, cout, "Invalid_Network_code at position:" );
			print_position(logfile, cout, entry_pos);
		} 
		
		if ( !is_valid_Orientation (orientation) ) {
			print_message ( logfile, cout, "Invalid_Network_code at position:" );
			print_position(logfile, cout, entry_pos);
		} else {
            
            stringstream str1;
            
            str1 << orientation.substr(0);
            str1 >> orl;
            
			//int orl = orientation.substr(0);
			if ( orl < 10000 || orl > 99999 ) {
				print_message ( logfile, cout, "Invalid_Network_code at position:" );
				print_position(logfile, cout, entry_pos);
			}
		}

		code++;
	}
	return true;
}
*/
int main() {

	// Declare variable types:

	string   inputfilename = "golnaz.in", outputfilename = "golnaz.out", logfilename = "golnaz.log";
	ofstream outputfile;
	ofstream logfile;
	ifstream inputfile;

	string   event_ID;
	int day = 1, year = 1850, mm = 1, tzl = 0, i = 0;        // Date and Time variables in format : ("mm/dd/yyyy or mm-dd-yyyy hh:mm:ss.fff time_zone");
	int hr = 0, min = 0, delimi_position = 0; 
	string date, time, m, dy, d, y, minsec, Hr, Min, Sec;                  
	Months month;
   
	string readline3;                                        // "Earthquake name"
	string time_zone;
	float  sec = 0;
	char   tz;

	double longitude = 0, latitude = 0, depth = 0;
	string magnitude_type;
	//mag_type mt[4];
	float magnitude_size;                                   // greater than 0 ( > 0) 
	//char stati_code_ty1[3];
	//int stati_code_ty2[5];
	string station_code;
	//const int Maxsize = 12;
	//const char Maxchar = 3;

	// Prompt the user for an input file

	cout << "Enter input filename: ";
	cin >> inputfilename;
	open_input(inputfile, logfile, cout, inputfilename);

	// Generating the log files

	open_logfile(logfile, "golnaz.log");

	// Reading the input Header and check for the data correctness
	// First line for event ID

	inputfile >> event_ID;

	// Reading second line for Datetime and time zone information

	inputfile >> date;

	// Case 1:

	delimi_position = date.find_first_of("/");
	m = date.substr(0, delimi_position);
	stringstream (m) >> mm;
    
    
	month << mm;

    
	dy = date.substr(delimi_position + 1);

	delimi_position = dy.find_first_of("/");
	d = dy.substr(0, delimi_position);
	stringstream (d) >> day;

	y = dy.substr(delimi_position + 1);
	stringstream (y) >> year;

	// Check for date validation

    //cout << mm << "/" << day << "/" << year << "\n";
    
	if ( mm != year) {
		
		if (  is_valid_date( mm, day, year)==0 ) {
			print_message ( logfile, cout, "date of earthquake is not valid" );
        exit(0);
		} else { cout << mm << "/" << day << "/" << year << "\n";}
			//return 0;
		
	}

	// Case 2 (delimiter is deferent):

	if (mm == year ) {
		delimi_position = date.find_first_of("-");
		m = date.substr(0, delimi_position);
		stringstream (m) >> mm;
		month << mm;

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
				print_message ( logfile, cout, "Date of the earthquake is not valid" );
				// exit(0);
			} else { 
				
			}
		}
	}

	// Read time of the event

   cout << "line 389" << "\n";
    
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
	if ( is_valid_time( hr, min, sec)==0 ) {
		print_message ( logfile, cout, "Time of earthquake is not valid" );
		exit(0);
	}

	// Read time_zone for the event

	inputfile >> time_zone;
	cout << "\n";
	string str = time_zone;
	const char *cstr = str.c_str();
	cout << cstr;
	tzl = strlen(cstr);
	if ( tzl != 3 ) {
		print_message ( logfile, cout, "Time_zone is not valid" );
		 exit(0);
	}

	// Reading the third line for event name

    
    inputfile.ignore();
	getline (inputfile, readline3);
    
	// Reading the fourth line for orintation and magnitude data

	// Orintation entries:
	inputfile >> longitude;
	inputfile >> latitude;
	inputfile >> depth;

	cout << longitude << " " << latitude << " " << depth << "\n"; 

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

	print_message ( logfile, cout, "Header read correctly!" );

	// Generating the log files

	open_output(outputfile, logfile, cout, "golnaz.out");

	// Print the header in the outputfile:
   
    outputfile <<"# " <<  Month_Num_to_namestring (number_to_months(mm)) <<" "<< day << " " << year << " " << time << " " << time_zone << " " << magnitude_type << " " << magnitude_size
    << " " << readline3 << " " << "[" << event_ID << "]" << "(" << longitude 	<< "," << " " << latitude << "," << " " << depth << ")" << "\n";
    


	// Start reading the table:

    outputfile.close();

	return 0;
}