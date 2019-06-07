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
            if curr_station not in stations:
                stations[curr_station] = 0

            stations[curr_station] += len([1 for val in values[6::5] if int(val) > 0])


        line = file.readline()

max_station = max(stations, key=stations.get)[3:]

end = time()

# Convert to ms
total_time = int((end - start) * 1000)

print(f"Ben Green, Python, {max_station}, {total_time}ms, Cleaned up")
