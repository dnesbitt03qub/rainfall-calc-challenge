import time

DATA_PATH = '../data/all.csv'

def simpleSearch():

    file = open(DATA_PATH, 'r')
    
    #header = file.readline()
    file.readline()
    latitude_column = 1
    relevant_columns = list(range(6, 486, 5))
    # header_split = header.split(',')
    # header_columns = [header_split[x] for x in relevant_columns]
    #line_count = 1

    times_for_stations = {}

    while True:
        line = file.readline()
        
        #line_count += 1
        #if line_count % 50000 == 0:
        #    print('{:.2f}'.format(line_count * 100 / 4950328))
        
        if line[:3] == '==>':
            continue
        
        if not line:
            break 
        
        
        lineSplit = line.split(',')
        
        if len(lineSplit) <= latitude_column:
            continue
        
        # Don't consider lines from stations South of the 45th parallel
        if float(lineSplit[latitude_column]) < 45.0:
            continue
        
        station = lineSplit[0]
        
        rainfall = [int(lineSplit[x]) for x in relevant_columns ]
        time_with_rain = 0
        for r in rainfall:
            if r > 0:
                time_with_rain += 1
        
        if time_with_rain > 0:
            if station in times_for_stations.keys():
                times_for_stations[station] += time_with_rain
            else:   
                times_for_stations[station] = time_with_rain
    
    stations_for_each_time = {}
    for station, time in times_for_stations.items():
        if time in stations_for_each_time.keys():
            stations_for_each_time[time].append(station)
        else:
            stations_for_each_time[time] = [ station ]
        
    longest_time = max(list(stations_for_each_time.keys()))
    
    #print('Found longest time')
    #print(longest_time * 15)
    
    #print('Stations with that time')
    #print(stations_for_each_time[longest_time])
    stations_numeric = [ int(station[3:]) for station in stations_for_each_time[longest_time]]
    total = sum(stations_numeric)

    file.close()
    
    return total


if __name__ == '__main__':
    
    start = int(round(time.time() * 1000))
    result = simpleSearch()
    end = int(round(time.time() * 1000))
    time = end - start
    print('{}, {}, {}, {}, {}'.format('dnesbitt03qub', 'python', result, time, 'nasty and slow'))
