while(True):
    print('puzzle input:')
    wires = []
    wireHitPoints = []
    intersectionSteps = []
    
    while (True):
        line = input()
        if line:
            wires.append(line.split(','))
            wireHitPoints.append([])
        else:
            break

    for i in range(len(wires)):
        origin = [0, 0, 0]
        steps = 0
        wireHitPoints[i].append([0, 0, 0])
        for instruction in wires[i]:
            direction = instruction[0]
            amount = int(instruction[1:]) # x: inclusive, :x non inclusive

            steps += amount
            newpos = [origin[0], origin[1], steps] # right +x, up +y
            if (direction == 'U'):
                newpos[1] += amount
            elif (direction == 'D'):
                newpos[1] -= amount
            elif (direction == 'L'):
                newpos[0] -= amount
            elif (direction == 'R'):
                newpos[0] += amount

            wireHitPoints[i].append(newpos)

            if (i != 0): # check if point intersects w/ wire 0
                for h in range(len(wireHitPoints[0]) - 1):
                    hit1 = wireHitPoints[0][h]
                    hit2 = wireHitPoints[0][h + 1]

                    #p1 origin #p2 newpos #p3 hit1 #p4 hit2

                    denom = ((hit2[0] - hit1[0]) * (origin[1] - newpos[1]) - (origin[0] - newpos[0]) * (hit2[1] - hit1[1]))
                    if (denom != 0): # there may be an intersect
                        alpha1 = ( ((hit1[1] - hit2[1]) * (origin[0] - hit1[0]) + (hit2[0] - hit1[0]) * (origin[1] - hit1[1])) / denom )
                        alpha2 = ( ((origin[1] - newpos[1]) * (origin[0] - hit1[0]) + (newpos[0] - origin[0]) * (origin[1] - hit1[1])) / denom )
                        if (alpha1 <= 1 and alpha1 >= 0 and alpha2 <= 1 and alpha2 >= 0):
                            intersect = [origin[0] + alpha1 * (newpos[0] - origin[0]), origin[1] + alpha2 * (newpos[1] - origin[1])]
                            combinedSteps = (origin[2] + alpha1* (newpos[2] - origin[2])) + (hit1[2] + alpha2* (hit2[2] - hit1[2]))
                            #distance = round(abs(intersect[0])) + round(abs(intersect[1]))
                            intersectionSteps.append(combinedSteps)

            origin = newpos.copy()
            
    minSteps = 99999999999
    for steps in intersectionSteps:
        if (steps < minSteps and steps != 0):
            minSteps = steps

    print(minSteps)
            
            
        
        
