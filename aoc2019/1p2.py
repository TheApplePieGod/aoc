import math

while(True):
    print('puzzle input:')
    masses = []
    
    while (True):
        line = input()
        if line:
            masses.append(int(line))
        else:
            break

    totalFuel = 0

    for i in range(len(masses)):
        mass = int(masses[i])
        adding = math.floor(mass / 3) - 2
        while (adding > 0):
            totalFuel += adding
            adding = math.floor(adding / 3) - 2

    print('total fuel = ' + str(totalFuel))
        
