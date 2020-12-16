inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

totalNorth = 0
totalEast = 0
waypointNorth = 1
waypointEast = 10

for line in lines:
    instruction = line[0]
    value = int(line[1:])
    if instruction == 'N':
        waypointNorth += value
    elif instruction == 'S':
        waypointNorth -= value
    elif instruction == 'E':
        waypointEast += value
    elif instruction == 'W':
        waypointEast -= value
    elif instruction == 'F':
        totalEast += value * waypointEast
        totalNorth += value * waypointNorth
    elif instruction == 'L':
        turns = int(value / 90)
        for i in range(0, turns):
            temp = waypointNorth
            waypointNorth = waypointEast
            waypointEast = -1 * temp
    elif instruction == 'R':
        turns = int(value / 90)
        for i in range(0, turns):
            temp = waypointEast
            waypointEast = waypointNorth
            waypointNorth = -1 * temp

print(abs(totalNorth) + abs(totalEast))