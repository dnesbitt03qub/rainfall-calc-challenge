#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#include "timer.h"

#define TIMING 0

using namespace std;

constexpr char PATH[] = "../data/all.csv";

int superSimple();
int partiallyOptimizedSolution();
int optimizedSolution();

int main(int argc, char * argv[]) {
    auto id = Timer::timerBegin();
    auto resultOptimized = optimizedSolution();
    auto timeOptimized = Timer::timerEnd(id) / 1000;
    cout << "dnesbitt03qub,C++," << resultOptimized << "," << timeOptimized << ",optimized\n";
    /*
    id = Timer::timerBegin();
    auto resultPartiallyOptimized = partiallyOptimizedSolution();
    auto timePartiallyOptimized = Timer::timerEnd(id) / 1000;
    cout << "dnesbitt03qub,C++," << resultPartiallyOptimized << "," << timePartiallyOptimized << ",partially optimized\n";
    */
    id = Timer::timerBegin();
    auto resultSimple = superSimple();
    auto timeSimple = Timer::timerEnd(id) / 1000;
    cout << "dnesbitt03qub,C++," << resultSimple << "," << timeSimple << ",simple" << endl;
    
    return 0;
}

int optimizedSolution() {
#if TIMING
    auto id = Timer::timerBegin();
#endif
    ifstream file(PATH);

    if (!file.is_open()) {
	cout << "No file at " << PATH << endl;
	exit(-1);
    }
    
    string line, value;
    
    // Skip the header line
    getline(file, line);

    map<string,int> timesForStations;

    // Relevant columns
    vector<int> relevantColumns;
    for (int i = 6 ; i < 486 ; i += 5) {
	relevantColumns.push_back(i);
    }

#if TIMING
    auto preLoop = Timer::timerEnd(id);
    id = Timer::timerBegin();
    long completeLinesTime = 0, toLatTest = 0;
#endif
    
    // For each line in the file
    while (getline(file, line)) {
	//auto id_loop = Timer::timerBegin();
	
	// Continue
	if (line[0] == '=') continue;
	if (line.empty()) {
	    continue;
	}

#if TIMING
	toLatTest += Timer::timerEnd(id_loop);
	id_loop = Timer::timerBegin();
#endif
	
	int digit = (int)line[12];
	if (digit < 52) continue; // ASCII 52 = '4' (if <40)
	if (digit == 52) { // if 40 - 49.9999
	    digit = (int)line[13]; // set digit to the second digit of the lat
	    if (digit < 53) continue; // ASCII 53 = '5' (if <45)
	    for (int i = 15 ; i < 19 ; i++) {
		bool mantissaEqualsZero = true;
		if (line[i] != '0') {
		    mantissaEqualsZero = false;
		    break;
		}
		if (mantissaEqualsZero) continue;
	    }
	}
	// if execution gets here lat is >45

	auto lineLength = line.size();
	int pos = 0, column = 0, posAfter = 0;
	long timeWithRain = 0;
	while (++pos < lineLength) {
	    if (line[pos] == ',') {
		column++;
		if ((column - 6) % 5 == 0) {
		    if (column != 1) {
			posAfter = pos + 1;
			while (line[posAfter++] != ',');

			for (int p = pos + 1 ; p < posAfter - 1 ; p++) {
			    int digit = (int)line[p];
			    if (digit == 45) break; // test for '-'
			    if (digit > 48) {
				timeWithRain++;
				break;
			    }
			}

		    } // END if not column 1
		}
	    }
	}
	
	if (timeWithRain > 0) {
	    string station = line.substr(3,8);
	    timesForStations[station] += timeWithRain;
	}

#if TIMING
	completeLinesTime += Timer::timerEnd(id_loop);
#endif
    }

#if TIMING
    auto loop = Timer::timerEnd(id);
    id = Timer::timerBegin();
#endif
    
    // do dict stuff
    map<int,vector<string>> stationsForEachTime;
    for (const auto& stationTimes : timesForStations) {
	stationsForEachTime[stationTimes.second].push_back(stationTimes.first);
    }

    int longestTime = (*(stationsForEachTime.rbegin())).first;
    int total = 0;
    for (const auto& stationID : stationsForEachTime[longestTime]) {
	int stationNumeric = stoi(stationID);
	total += stationNumeric;
    }
    
    file.close();

#if TIMING
    auto postLoop = Timer::timerEnd(id);

    cout << "Preloop " << preLoop / 1000
	 << "\nLoop " << loop / 1000
	 << "\n\tTo Lat Test " << toLatTest / 1000
	 << "\n\tComplete Lines " << completeLinesTime / 1000
	 << "\n\t(Other) " << ( loop - completeLinesTime - toLatTest ) / 1000
	 << "\nPostloop " << postLoop / 1000
	 << endl;
#endif
    
    return total;
}

int partiallyOptimizedSolution() {
#if TIMING
    auto id = Timer::timerBegin();
#endif
    ifstream file(PATH);

    if (!file.is_open()) {
	cout << "No file at " << PATH << endl;
	exit(-1);
    }
    
    string line, value;
    
    // Skip the header line
    getline(file, line);

    map<string,int> timesForStations;

    // Relevant columns
    vector<int> relevantColumns;
    for (int i = 6 ; i < 486 ; i += 5) {
	relevantColumns.push_back(i);
    }

#if TIMING
    auto preLoop = Timer::timerEnd(id);
    id = Timer::timerBegin();
    long completeLinesTime = 0, toLatTest = 0;
#endif
    
    // For each line in the file
    while (getline(file, line)) {
	//auto id_loop = Timer::timerBegin();
	
	// Continue
	if (line[0] == '=') continue;
	if (line.empty()) {
	    continue;
	}

#if TIMING
	toLatTest += Timer::timerEnd(id_loop);
	id_loop = Timer::timerBegin();
#endif

	const string lat = line.substr(12,7);
	const float lat_float = stof(lat);
	if (lat_float < 45.) continue;
	
	auto lineLength = line.size();
	int pos = 0, column = 0, posAfter = 0;
	long timeWithRain = 0;
	while (++pos < lineLength) {
	    if (line[pos] == ',') {
		column++;
		if ((column - 6) % 5 == 0) {
		    if (column != 1) {
			posAfter = pos + 1;
			while (line[posAfter++] != ',');

			for (int p = pos + 1 ; p < posAfter - 1 ; p++) {
			    int digit = (int)line[p];
			    if (digit == 45) break; // test for '-'
			    if (digit > 48) {
				timeWithRain++;
				break;
			    }
			}

		    } // END if not column 1
		}
	    }
	}
	
	if (timeWithRain > 0) {
	    string station = line.substr(3,8);
	    timesForStations[station] += timeWithRain;
	}

#if TIMING
	completeLinesTime += Timer::timerEnd(id_loop);
#endif
    }

#if TIMING
    auto loop = Timer::timerEnd(id);
    id = Timer::timerBegin();
#endif
    
    // do dict stuff
    map<int,vector<string>> stationsForEachTime;
    for (const auto& stationTimes : timesForStations) {
	stationsForEachTime[stationTimes.second].push_back(stationTimes.first);
    }

    int longestTime = (*(stationsForEachTime.rbegin())).first;
    int total = 0;
    for (const auto& stationID : stationsForEachTime[longestTime]) {
	int stationNumeric = stoi(stationID);
	total += stationNumeric;
    }
    
    file.close();

#if TIMING
    auto postLoop = Timer::timerEnd(id);

    cout << "Preloop " << preLoop / 1000
	 << "\nLoop " << loop / 1000
	 << "\n\tTo Lat Test " << toLatTest / 1000
	 << "\n\tComplete Lines " << completeLinesTime / 1000
	 << "\n\t(Other) " << ( loop - completeLinesTime - toLatTest ) / 1000
	 << "\nPostloop " << postLoop / 1000
	 << endl;
#endif
    
    return total;
}


int superSimple() {
    ifstream file(PATH);

    if (!file.is_open()) {
	cout << "No file at " << PATH << endl;
	exit(-1);
    }

    string line, value;

    // Skip the header line
    getline(file, line);

    map<string,int> timesForStations;

    // Relevant columns
    vector<int> relevantColumns;
    for (int i = 6 ; i < 486 ; i += 5) {
	relevantColumns.push_back(i);
    }

    // For each line in the file
    while (getline(file, line)) {

	// Continue
	if (line[0] == '=') continue;
	if (line.empty()) {
	    continue;
	}

	const string lat = line.substr(12,7);

	const float lat_float = stof(lat);

	if (lat_float < 45.) continue;


	stringstream lineStream(line);
	vector<string> columns;
	int timeWithRain = 0;

	// For each column in the file
	while (getline(lineStream, value, ',')) {
	    columns.push_back(value);
	}

	for (const auto& colIndex : relevantColumns) {
	    string valueAtColIndex = columns[colIndex];
	    if (stof(valueAtColIndex) > 0) {
		timeWithRain++;
	    }
	}

	timesForStations[columns[0]] += timeWithRain;
    }

    // do dict stuff
    map<int,vector<string>> stationsForEachTime;
    for (const auto& stationTimes : timesForStations) {
	stationsForEachTime[stationTimes.second].push_back(stationTimes.first);
    }

    int longestTime = (*(stationsForEachTime.rbegin())).first;
    int total = 0;
    for (const auto& stationID : stationsForEachTime[longestTime]) {
	int stationNumeric = stoi(stationID.substr(3));
	total += stationNumeric;
    }

    file.close();

    return total;
}
