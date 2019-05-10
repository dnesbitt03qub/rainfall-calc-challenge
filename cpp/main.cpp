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
    auto timeSimple = Timer::timerEnd(id) / 1000;

    cout << "dnesbitt03qub,C++," << resultSimple << "," << timeSimple << ",simple"
	 << endl;

    return 0;
}

int superSimple() {
    //auto id = Timer::timerBegin();
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

    //auto preLoop = Timer::timerEnd(id);
    //id = Timer::timerBegin();

    //long completeLinesTime = 0, toLatTest = 0;
    
    // For each line in the file
    while (getline(file, line)) {
	//auto id_loop = Timer::timerBegin();
	auto lineLength = line.size();
	
	// Continue
	if (line[0] == '=') continue;
	if (line.empty()) {
	    continue;
	}

	const string lat = line.substr(12,7);

	const float lat_float = stof(lat);

	//toLatTest += Timer::timerEnd(id_loop);
	//id_loop = Timer::timerBegin();
	
	if (lat_float < 45.) continue;

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

	//completeLinesTime += Timer::timerEnd(id_loop);
    }

    //auto loop = Timer::timerEnd(id);
    //id = Timer::timerBegin();

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

    /*
    auto postLoop = Timer::timerEnd(id);

    cout << "Preloop " << preLoop / 1000
	 << "\nLoop " << loop / 1000
	 << "\n\tTo Lat Test " << toLatTest / 1000
	 << "\n\tComplete Lines " << completeLinesTime / 1000
	 << "\n\t(Other) " << ( loop - completeLinesTime - toLatTest ) / 1000
	 << "\nPostloop " << postLoop / 1000
	 << endl;
    */
    return total;
}
