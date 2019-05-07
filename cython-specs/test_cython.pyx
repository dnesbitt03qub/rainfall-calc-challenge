import os
import time

USER = 'specs'
LANG = 'cython'
NOTES = 'ugly. needs cleanup.'
PATH = '/data/all.csv'


def print_results(result, runtime):
    print('{}, {}, {}, {} ms, {}'.format(USER, LANG, result, runtime, NOTES))


start = int(round(time.time() * 1000))
data = {}
with open(PATH) as f:
    temp = f.readlines()

for row in temp[1:]:
    if ',' in row:
        x = row.split(',')
        if x[1] == 'Lat' or float(x[1]) > 45.0:
            if x[0] not in data:
                data[x[0]] = 0
            data[x[0]] += sum(1 for t in x[6::5] if float(t) > 0.0)

data = sorted(
    [
        {
            'station': k,
            'total': v
        }
        for k, v in data.items()
    ],
    key=lambda k: k['total'],
    reverse=True
)

end = int(round(time.time() * 1000)) - start
print_results(data[0]['station'][3:], end)
