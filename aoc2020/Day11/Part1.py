import copy

inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']
newLines = copy.deepcopy(lines)
maxX = len(lines[0])
maxY = len(lines)

lastHash = 0
currentHash = -1
while currentHash != lastHash:
    for y in range(0, maxY):
        for x in range(0, maxX):
            if lines[y][x] == 'L':
                seatCount = 0
                ymin1 = y if y - 1 < 0 else y - 1
                yplus1 = y if y + 1 >= maxY else y + 1
                xmin1 = x if x - 1 < 0 else x - 1
                xplus1 = x if x + 1 >= maxX else x + 1
                if ymin1 != y and (lines[ymin1][x] == '#' ):
                    continue
                if yplus1 != y and (lines[yplus1][x] == '#' ):
                    continue
                if xmin1 != x and (lines[y][xmin1] == '#' ):
                    continue
                if xplus1 != x and (lines[y][xplus1] == '#' ):
                    continue
                if (ymin1 != y and xmin1 != x) and (lines[ymin1][xmin1] == '#'):
                    continue
                if (ymin1 != y and xplus1 != x) and (lines[ymin1][xplus1] == '#' ):
                    continue
                if (yplus1 != y and xmin1 != x) and (lines[yplus1][xmin1] == '#'):
                    continue
                if (yplus1 != y and xplus1 != x) and (lines[yplus1][xplus1] == '#' ):
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
                if ymin1 != y and (lines[ymin1][x] == '#' ):
                    seatCount += 1
                if yplus1 != y and (lines[yplus1][x] == '#' ):
                    seatCount += 1
                if xmin1 != x and (lines[y][xmin1] == '#' ):
                    seatCount += 1
                if xplus1 != x and (lines[y][xplus1] == '#' ):
                    seatCount += 1
                if (ymin1 != y and xmin1 != x) and (lines[ymin1][xmin1] == '#'):
                    seatCount += 1
                if (ymin1 != y and xplus1 != x) and (lines[ymin1][xplus1] == '#' ):
                    seatCount += 1
                if (yplus1 != y and xmin1 != x) and (lines[yplus1][xmin1] == '#'):
                    seatCount += 1
                if (yplus1 != y and xplus1 != x) and (lines[yplus1][xplus1] == '#' ):
                    seatCount += 1
                if seatCount >= 4:
                    linelist = list(newLines[y])
                    linelist[x] = 'L'
                    newLines[y] = "".join(linelist)
    lines = copy.deepcopy(newLines)
    lastHash = currentHash
    currentHash = hash(str(lines))

numOccupied = 0
for y in range(0, maxY):
    for x in range(0, maxX):
        if lines[y][x] == '#':
            numOccupied += 1

print(numOccupied)

