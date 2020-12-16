inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [int(interval) for interval in inputs[selectedInput].split("\n") if interval != '']

totalArrangements = 1
currentJoltage = 0
failed = False
arrangements = {}

def getArrangements(joltage, remaining):
    global arrangements
    if joltage in arrangements.keys():
        return arrangements[joltage]
    else:
        localArrangements = 0
        found = []
        for line in remaining:
            if line - 3 <= joltage and line > joltage:
                found.append(line)
        if len(found) > 0:
            localArrangements += len(found) - 1
        for line in found:
            left = remaining.copy()
            left.remove(line)
            localArrangements += getArrangements(line, left)
        arrangements[joltage] = localArrangements
        return localArrangements

totalArrangements += getArrangements(0, lines)

print(totalArrangements)