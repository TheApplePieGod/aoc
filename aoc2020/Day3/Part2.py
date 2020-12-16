inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

def calcAmount(slopeX, slopeY):
    treeCount = 0
    currentX = 0
    currentY = 0
    while currentY < len(lines):
        currentX = currentX % len(lines[0])
        if lines[currentY][currentX] == '#':
            treeCount += 1
        currentX += slopeX
        currentY += slopeY
    return treeCount

final = 1
final = final * calcAmount(1, 1)
final = final * calcAmount(3, 1)
final = final * calcAmount(5, 1)
final = final * calcAmount(7, 1)
final = final * calcAmount(1, 2)
print(final)