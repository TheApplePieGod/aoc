while(True):        
    print('puzzle input:')
    orbits = [] # y orbits x
    directOrbits = 0
    indirectOrbits = 0
    indirectOrbitMap = [] # x: orbit name y: num indirect

    def calcIndirects(orbit):
        found = False
        numindirect = 0
        if orbit[0] != 'COM':
            for omap in indirectOrbitMap:
                if (omap[0] == orbit[1]):
                    numindirect += omap[1]
                    found = True
                    break
            if (found == False):
                for orbit2 in orbits:
                    if (orbit2[1] == orbit[0]):
                        numindirect += calcIndirects(orbit2) + 1
                        indirectOrbitMap.append([orbit[1], numindirect])
                        break
            
        return numindirect
    
    while (True):
        line = input()
        if line:
            orbits.append(line.split(')'))
            directOrbits += 1
        else:
            break

    for orbit in orbits:
        indirectOrbits += calcIndirects(orbit)

    print('total orbits: ' + str(indirectOrbits + directOrbits))
