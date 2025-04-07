import re

file = open("test.txt")

lines = [line.strip() for line in file.readlines()]

seeds = lines[0]

location = []

for num in map(int, re.findall('\d+', seeds)):
    for seg in lines[1:]:
        for conver in re.findall('(\d+) (\d+) (\d+)', seg):
            dist, source, length = map(int, conver)
            # print(dist, source, length)
            if num in range(source, source+length): # 98 => 100
                num += dist + (source - num)
                break
    print(num)
    location.append(num)

print(min(location))
