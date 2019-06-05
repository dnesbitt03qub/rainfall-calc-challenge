import os
from time import time

file_location = os.path.join('..', '..', 'data', 'all.csv')

stations = {}
max_value = 0
max_stations = []


start = time()

with open(file_location, 'r') as file:
    line = file.readline()
    # Ignore the headers
    line = file.readline()
    while line:
        # Only check stations north of the 45th parallel
        if line is not '\n' and float(line[12:line.index(',', 13)]) > 45:
            values = line.split(',')
            curr_station = values[0]
            if curr_station not in stations:
                stations[curr_station] = 0

            # 96 is the number of 15-minute segments in a day
            for i in range(96):
                if int(values[6 + i*5]) > 0:
                    stations[curr_station] += 1
                    
                    curr_val = stations[curr_station]
                    
                    if curr_val > max_value:
                        max_value = curr_val
                        max_stations = [curr_station]
                    elif curr_val == max_value:
                        max_stations.append(curr_station)

        line = file.readline()

max_station = sum([int(station[3:]) for station in max_stations])

# Convert to ms
total_time = int((time() - start) * 1000)

print(f"Ben Green, Python, {max_station:08}, {total_time}ms, Simple")
