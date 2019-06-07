import os
from collections import defaultdict
from time import time

file_location = os.path.join('..', '..', 'data', 'all.csv')

def assume_single_max():
    stations = defaultdict(int)
    start = time()

    with open(file_location, 'r') as file:
        line = file.readline()
        # Ignore the headers
        line = file.readline()
        while line:
            # Ensure line isn't empty and station is north of the 45th parallel
            if line is not '\n' and (
                # At least the 50th parallel
                ord(line[12]) > 52 or (
                    # 40-49.9999 latitude
                    ord(line[12]) == 52 and (
                        # At least the 46th parallel
                        ord(line[13]) > 53 or (
                            # 45-45.9999
                            ord(line[13]) == 53 and (
                                # Not exactly the 45th parallel
                                line[15] is not '0' or line[16] is not '0' or line[17] is not '0' or line[18] is not '0'))))):
                
                values = line.split(',')
                stations[values[0]] += len([1 for val in values[6::5] if val[0] not in ('-', '0')])


            line = file.readline()

    max_station = max(stations, key=stations.get)[3:]
    end = time()
    return max_station, int((end - start) * 1000)

def possible_multiple_max():
    stations = defaultdict(int)
    max_value = 0
    max_stations = []
    start = time()

    with open(file_location, 'r') as file:
        line = file.readline()
        # Ignore the headers
        line = file.readline()
        while line:
            # Ensure line isn't empty and station is north of the 45th parallel
            if line is not '\n' and (
                # At least the 50th parallel
                ord(line[12]) > 52 or (
                    # 40-49.9999 latitude
                    ord(line[12]) == 52 and (
                        # At least the 46th parallel
                        ord(line[13]) > 53 or (
                            # 45-45.9999
                            ord(line[13]) == 53 and (
                                # Not exactly the 45th parallel
                                line[15] is not '0' or line[16] is not '0' or line[17] is not '0' or line[18] is not '0'))))):
                
                values = line.split(',')
                
                curr_station = values[0]

                # 96 is the number of 15-minute segments in a day
                for i in range(96):
                    start_char = values[6 + i*5][0]
                    if start_char is not '-' and start_char is not '0':
                        stations[curr_station] += 1
                        
                        curr_val = stations[curr_station]
                        
                        if curr_val > max_value:
                            max_value = curr_val
                            max_stations = [curr_station]
                        elif curr_val == max_value:
                            max_stations.append(curr_station)


            line = file.readline()

    max_station = sum([int(station[3:]) for station in max_stations])
    end = time()
    return max_station, int((end - start) * 1000)

# Convert to ms
station, total_time = assume_single_max()
print(f"Ben Green, Python, {station}, {total_time}ms, Assuming only one max station in data")
station, total_time = possible_multiple_max()
print(f"Ben Green, Python, {station}, {total_time}ms, Somewhat optimized")
