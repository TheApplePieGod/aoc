inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

treeCount = 0
slopeX = 3
slopeY = 1
currentX = 0
currentY = 0
while currentY < len(lines):
    currentX = currentX % len(lines[0])
    if lines[currentY][currentX] == '#':
        treeCount += 1
    currentX += slopeX
    currentY += slopeY
print(treeCount)