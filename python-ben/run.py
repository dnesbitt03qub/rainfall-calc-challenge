import os
from collections import defaultdict
from time import time

file_location = os.path.join('..', '..', 'data', 'all.csv')

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

            # 96 is the number of 15-minute segments in a day
            stations[values[0]] += len([val for val in values[6::5] if val[0] not in ('-', '0')])

        line = file.readline()

max_value = max(stations.values())
max_station = sum([int(station[3:]) for station in stations if stations[station] == max_value])

end = time()
total_time = int((end - start) * 1000)

print(f"Ben Green, Python, {max_station}, {total_time}ms, Optimized")
