import os
from time import time

file_location = os.path.join('..', '..', 'data', 'all.csv')

stations = {}

start = time()

with open(file_location, 'r') as file:
    line = file.readline()
    # Ignore the headers
    line = file.readline()
    while line:
        # Only check stations north of the 45th parallel
        if line is not '\n' and float(line[12:19]) > 45.0:
            values = line.split(',')
            
            curr_station = values[0]
            if curr_station not in stations:
                stations[curr_station] = 0

            stations[curr_station] += len([1 for val in values[6::5] if int(val) > 0])


        line = file.readline()

max_station = max(stations, key=stations.get)[3:]

end = time()

# Convert to ms
total_time = int((end - start) * 1000)

print(f"Ben Green, Python, {max_station}, {total_time}ms, Cleaned up")
