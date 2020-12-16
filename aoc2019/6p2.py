while(True):        
    print('puzzle input:')
    orbits = [] # y orbits x
    steps = []
    start = ''
    destination = ''
        
    def calcPathToOrbit(orbit, dest):
        crossed = []
        steps = 0
        nextOrbit = orbit
        while nextOrbit != dest:
            steps += 1
            for orbit2 in orbits:
                if (orbit2[1] == nextOrbit):
                    nextOrbit = orbit2[0]
                    crossed.append(nextOrbit)
                    break
        return [crossed, steps]
    
    while (True):
        line = input()
        if line:
            vals = line.split(')')
            orbits.append(vals)
            if (vals[1] == 'YOU'):
                start = vals[0]
            elif (vals[1] == 'SAN'):
                destination = vals[0]
        else:
            break

        
    startPath = calcPathToOrbit(start, 'COM')[0]
    destPath = calcPathToOrbit(destination, 'COM')[0]
    firstIntersect = ''
    found = False
    for orbit in startPath:
        for orbit2 in destPath:
            if (orbit == orbit2):
                firstIntersect = orbit
                found = True
                break
        if (found == True):
            break

    stepsFromDest = calcPathToOrbit(destination, firstIntersect)[1]
    stepsFromStart = calcPathToOrbit(start, firstIntersect)[1]
    
    print('min steps: ' + str(stepsFromDest + stepsFromStart))

