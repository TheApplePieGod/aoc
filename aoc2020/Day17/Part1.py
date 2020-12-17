import copy

inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

grid = [[]]
nextGrid = [[]]

for line in lines:
    grid[0].append(line)
    nextGrid[0].append(line)

x0 = 0
y0 = 0
z0 = 0
x20 = 0
y20 = 0
z20 = 0

def expandBounds(x, y, z):
    global x20
    global y20
    global z20
    if z == 1:
        nextGrid.append(['.' * len(nextGrid[0][0])] * len(nextGrid[0]))
    elif z == -1:
        nextGrid.insert(0, ['.' * len(nextGrid[0][0])] * len(nextGrid[0]))
        z20 += 1
    if y == 1:
        for i in range(0, len(nextGrid)):
            nextGrid[i].append('.' * len(nextGrid[0][0]))
    elif y == -1:
        for i in range(0, len(nextGrid)):
            nextGrid[i].insert(0, '.' * len(nextGrid[0][0]))
        y20 += 1
    if x == 1:
        for i in range(0, len(nextGrid)):
            for j in range(0, len(nextGrid[i])):
                nextGrid[i][j] = nextGrid[i][j] + '.'
    elif x == -1:
        for i in range(0, len(nextGrid)):
            for j in range(0, len(nextGrid[i])):
                nextGrid[i][j] = '.' + nextGrid[i][j]
        x20 += 1

# expands bounds if necessary
def isNeighborActive(x, y, z, xSlope, ySlope, zSlope):
    xIndex = 0
    yIndex = 0
    zIndex = 0
    wasOutOfBounds = False
    while True:
        xIndex = x0 + x + xSlope
        yIndex = y0 + y + ySlope
        zIndex = z0 + z + zSlope
        boundsX = x20 + x + xSlope
        boundsY = y20 + y + ySlope
        boundsZ = z20 + z + zSlope

        # we can do bounds checking at element 0 because it should expand uniformly
        expandX = 0
        expandY = 0
        expandZ = 0
        if zIndex >= len(grid): expandZ = 1
        elif zIndex < 0: expandZ = -1
        if yIndex >= len(grid[0]): expandY = 1
        elif yIndex < 0: expandY = -1
        if xIndex >= len(grid[0][0]): expandX = 1
        elif xIndex < 0: expandX = -1

        if expandX == 0 and expandY == 0 and expandZ == 0:
            break
        else:
            # return '.' if the index should be out of range but has already been expanded
            if len(nextGrid) > boundsZ >= 0 and len(nextGrid[0]) > boundsY >= 0 and len(nextGrid[0][0]) > boundsX >= 0:
                return 0
            wasOutOfBounds = True
            expandBounds(expandX, expandY, expandZ) # expands for next grid

    # if it was ever out of bounds, return '.' because that is what it would have been set to
    if wasOutOfBounds:
        return 0

    if grid[zIndex][yIndex][xIndex] == '#':
        return 1
    else:
        return 0

def finishCycle():
    global nextGrid
    global grid
    global x0
    global y0
    global z0
    expandBounds(1, 1, 1)
    expandBounds(-1, -1, -1)
    expandBounds(1, 1, 1)
    expandBounds(-1, -1, -1)
    grid = nextGrid
    x0 = x20
    y0 = y20
    z0 = z20

finishCycle()
cycle = 0
while cycle < 6:
    nextGrid = copy.deepcopy(grid)
    for z in range(1, len(grid) - 1):
        zVal = z - z0
        for y in range(1, len(grid[z]) - 1):
            yVal = y - y0
            for x in range(1, len(grid[z][y]) - 1):
                xVal = x - x0
                active = 0
                isActive = grid[z][y][x] == '#'

                for cz in range(-1, 2):
                    for cy in range(-1, 2):
                        for cx in range(-1, 2):
                            if cz != 0 or cy !=0 or cx != 0:
                                active += isNeighborActive(xVal, yVal, zVal, cx, cy, cz)

                if isActive and (active < 2 or active > 3):
                    strList = list(nextGrid[zVal + z20][yVal + y20])
                    strList[xVal + x20] = '.'
                    nextGrid[zVal + z20][yVal + y20] = "".join(strList)
                elif (not isActive) and active == 3:
                    strList = list(nextGrid[zVal + z20][yVal + y20])
                    strList[xVal + x20] = '#'
                    nextGrid[zVal + z20][yVal + y20] = "".join(strList)

    cycle += 1
    finishCycle()
    
numActive = 0
for z in range(0, len(grid)):
    for y in range(0, len(grid[0])):
        for x in range(0, len(grid[0][0])):
            if grid[z][y][x] == '#':
                numActive += 1
    
print(numActive)