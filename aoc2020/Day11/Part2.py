import copy

inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']
newLines = copy.deepcopy(lines)
maxX = len(lines[0])
maxY = len(lines)

def findSeatsInDirection(x, y, slopeX, slopeY):
    currentChar = ''
    currentX = x + slopeX
    currentY = y + slopeY
    while currentChar != 'L' and currentChar != '#' and currentX < maxX and currentX >= 0 and currentY < maxY and currentY >= 0:
        currentChar = lines[currentY][currentX]
        currentX += slopeX
        currentY += slopeY
    return currentChar

lastHash = 0
currentHash = -1
iterations = 0
while currentHash != lastHash:
    iterations += 1
    for y in range(0, maxY):
        for x in range(0, maxX):
            if lines[y][x] == 'L':
                seatCount = 0
                ymin1 = y if y - 1 < 0 else y - 1
                yplus1 = y if y + 1 >= maxY else y + 1
                xmin1 = x if x - 1 < 0 else x - 1
                xplus1 = x if x + 1 >= maxX else x + 1
                if findSeatsInDirection(x, y, 0, -1) == '#':
                    continue
                if findSeatsInDirection(x, y, 0, 1) == '#':
                    continue
                if findSeatsInDirection(x, y, -1, 0) == '#':
                    continue
                if findSeatsInDirection(x, y, 1, 0) == '#':
                    continue
                if findSeatsInDirection(x, y, -1, -1) == '#':
                    continue
                if findSeatsInDirection(x, y, 1, -1) == '#':
                    continue
                if findSeatsInDirection(x, y, -1, 1) == '#':
                    continue
                if findSeatsInDirection(x, y, 1, 1) == '#':
                    continue
                linelist = list(newLines[y])
                linelist[x] = '#'
                newLines[y] = "".join(linelist)
            elif lines[y][x] == '#':
                seatCount = 0
                ymin1 = y if y - 1 < 0 else y - 1
                yplus1 = y if y + 1 >= maxY else y + 1
                xmin1 = x if x - 1 < 0 else x - 1
                xplus1 = x if x + 1 >= maxX else x + 1
                if findSeatsInDirection(x, y, 0, -1) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, 0, 1) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, -1, 0) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, 1, 0) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, -1, -1) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, 1, -1) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, -1, 1) == '#':
                    seatCount += 1
                if findSeatsInDirection(x, y, 1, 1) == '#':
                    seatCount += 1
                if seatCount >= 5:
                    linelist = list(newLines[y])
                    linelist[x] = 'L'
                    newLines[y] = "".join(linelist)
    #for line in newLines:
    #    print(line)
    lines = newLines.copy()
    lastHash = currentHash
    currentHash = hash(str(lines))

numOccupied = 0
for y in range(0, maxY):
    for x in range(0, maxX):
        if lines[y][x] == '#':
            numOccupied += 1

print("Iterations: " + str(iterations))
print(numOccupied)

