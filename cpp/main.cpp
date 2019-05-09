#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

#include "timer.h"

using namespace std;

constexpr char PATH[] = "../data/all.csv";

int superSimple();
string getTextFromFile() {
    ifstream file(PATH);

    if (!file.is_open()) {
	cout << "No file at " << PATH << endl;
	exit(-1);
    }
    
    stringstream buffer;
    buffer << file.rdbuf();
    string text(buffer.str());
    file.close();

    return text;
}

int main(int argc, char * argv[]) {
    auto id = Timer::timerBegin();
    auto resultSimple = superSimple();
    auto timeSimple = Timer::timerEnd(id);

    cout << "dnesbitt03qub,C++," << resultSimple << "," << timeSimple << "simple"
	 << endl;

    return 0;
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

	const string lat = line.substr(10,8);
	const float lat_float = stof(lat);

	if (lat_float < 45.) continue;

	
	stringstream lineStream(line);
	vector<string> columns;
	int timeWithRain = 0;

	// For each column in the file
	while (getline(lineStream, value, '.')) {
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
	int stationNumeric = stoi(stationID.substr(2));
	total += stationNumeric;
    }
    
    file.close();

    return total;
}
