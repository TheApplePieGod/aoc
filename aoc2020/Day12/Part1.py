inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

directions = ['N', 'E', 'S', 'W']
currentDirection = 1
totalNorth = 0
totalEast = 0

for line in lines:
    instruction = line[0]
    value = int(line[1:])
    if instruction == 'N':
        totalNorth += value
    elif instruction == 'S':
        totalNorth -= value
    elif instruction == 'E':
        totalEast += value
    elif instruction == 'W':
        totalEast -= value
    elif instruction == 'F':
        if currentDirection == 0:
            totalNorth += value
        elif currentDirection == 2:
            totalNorth -= value
        elif currentDirection == 1:
            totalEast += value
        elif currentDirection == 3:
            totalEast -= value
    elif instruction == 'L':
        currentDirection = (currentDirection - (value / 90)) % len(directions)
    elif instruction == 'R':
        currentDirection = (currentDirection + (value / 90)) % len(directions)

print(abs(totalNorth) + abs(totalEast))