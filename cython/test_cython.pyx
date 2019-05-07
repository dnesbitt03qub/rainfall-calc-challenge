import time as ti

DATA_PATH = '../data/all.csv'

def simpleSearch():

    #start_all = int(round(ti.time() * 1000))
    #start = int(round(ti.time() * 1000))
    file = open(DATA_PATH, 'r')
    
    header = file.readline()
    file.readline()
    latitude_column = 1
    relevant_columns = list(range(6, 486, 5))
    # header_split = header.split(',')
    # header_columns = [header_split[x] for x in relevant_columns]
    #line_count = 1

    times_for_stations = {}
    
    #end = int(round(ti.time() * 1000))
    #setup = end - start
    #start = int(round(ti.time() * 1000))
    #reading = 0
    #actual_processing = 0

    while True:
        #start_loop = int(round(ti.time() * 1000))
        line = file.readline()
        #end_loop = int(round(ti.time() * 1000))
        #reading += end_loop - start_loop
        #start_loop = int(round(ti.time() * 1000))
        
        
        #line_count += 1
        #if line_count % 50000 == 0:
        #    print('{:.2f}'.format(line_count * 100 / 4950328))
        
        if line[:3] == '==>':
            continue
        
        if not line:
            break 
        
        # Get the latitude
        line_length = len(line)
        pos_pre_lat_comma = 0
        
        while pos_pre_lat_comma < line_length:
            if line[pos_pre_lat_comma] == ',':
                break
            pos_pre_lat_comma += 1
                
        pos_lat_decimal_point = pos_pre_lat_comma
        while pos_lat_decimal_point < line_length:
            if line[pos_lat_decimal_point] == '.':
                break
            pos_lat_decimal_point += 1
            
        lat_characteristic = line[pos_pre_lat_comma+1:pos_lat_decimal_point]
        
        if not lat_characteristic:
            continue
        
        int_lat = int(lat_characteristic)
        
        if int_lat < 45:
            continue
        
        lineSplit = line.split(',')
        
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
                
        #end_loop = int(round(ti.time() * 1000))
        #actual_processing += end_loop - start_loop
                
    
    #end = int(round(ti.time() * 1000))
    #main_loop = end - start
    #start = int(round(ti.time() * 1000))
    
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
    
    #end = int(round(ti.time() * 1000))
    #dictionary_work = end - start
    #end_all = int(round(ti.time() * 1000))
    #all_time = end_all - start_all
    #print('All {}\n\tSetup {}\n\tMain loop {}\n\t\tReading {}\n\t\tActual Processing {}\n\t\tNot captured {}\n\tDictionary Work {}'.format(all_time, setup, main_loop, reading, actual_processing, main_loop - reading - actual_processing, dictionary_work))
    
    return total

start = int(round(ti.time() * 1000))
result = simpleSearch()
end = int(round(ti.time() * 1000))
time = end - start
print('{}, {}, {}, {}, {}'.format('dnesbitt03qub', 'python', result, time, 'nasty and slow'))
