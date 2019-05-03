import time
import numpy as np

DATA_PATH = '../data/all.csv'

def masked(val):
    return 1 if val > 0 else 0

def simpleSearch():

    file = open(DATA_PATH, 'r')
    
    file.readline()
    latitude_column = 1
    relevant_columns = list(range(6, 491, 5))
    line_count = 1

    times_and_associated_stations = {}
    

    while True:
        line = file.readline()
        line_count += 1
        if line_count % 10000 == 0:
            print('{:.2f}'.format(line_count * 100 / 4950328))
        if line[:3] == '==>':
            continue
        
        if not line:
            break 
        
        
        lineSplit = line.split(',')
        
        if len(lineSplit) <= latitude_column:
            continue
        
        
        # Don't consider lines from stations above below (or on) the 45th parallel
        if float(lineSplit[latitude_column]) >= 45.0:
            continue
        
        station = lineSplit[0]
        station_numeric = int(station[3:])
        
        rainfall = [int(lineSplit[x]) for x in relevant_columns ]
        rainfall_mask = [masked(x) for x in rainfall]
        time_with_rain = sum(rainfall_mask)
        
        if time_with_rain not in times_and_associated_stations.keys():
            times_and_associated_stations[time_with_rain] = []
        
        times_and_associated_stations[time_with_rain].append(station_numeric)
        
    # print(times_and_associated_stations)
    matching_stations = max(list(times_and_associated_stations.keys()))
    print('Max time raining ' + str(matching_stations))
    # print(times_and_associated_stations[matching_stations])
    total = sum(np.unique(times_and_associated_stations[matching_stations]))

    file.close()
    
    return total


if __name__ == '__main__':
    
    start = int(round(time.time() * 1000))
    result = simpleSearch()
    end = int(round(time.time() * 1000))
    time = end - start
    print('{}, {}, {}, {}, {}'.format('dnesbitt03qub', 'python', result, time, 'nasty and slow'))
