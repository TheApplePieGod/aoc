inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n\n") if interval != '']

fields = {}
for line in lines[0].split('\n'):
    data = line.split(':')
    data[1] = data[1].strip()
    ranges = data[1].split(' or ')
    range1 = [int(i) for i in ranges[0].split('-')]
    range2 = [int(i) for i in ranges[1].split('-')]
    fields[data[0]] = [range1, range2]

invalidTotal = 0
nearbyLines = lines[2].split('\n')
for i in range(1, len(nearbyLines)):
    if nearbyLines[i] != '':
        numbers = [int(i) for i in nearbyLines[i].split(',')]
        shouldBreak = False
        for number in numbers:
            found = False
            for field in fields:
                value = fields[field]
                if ((number >= value[0][0] and number <= value[0][1]) or (number >= value[1][0] and number <= value[1][1])):
                    found = True
                    break
            if not found:
                invalidTotal += number
                break

print(invalidTotal)