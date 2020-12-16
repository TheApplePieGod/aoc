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

nearbyLines = lines[2].split('\n')
validTickets = []
for i in range(1, len(nearbyLines)):
    if nearbyLines[i] != '':
        numbers = [int(i) for i in nearbyLines[i].split(',')]
        isValid = True
        for number in numbers:
            found = False
            for field in fields:
                value = fields[field]
                if ((number >= value[0][0] and number <= value[0][1]) or (number >= value[1][0] and number <= value[1][1])):
                    found = True
                    break
            if not found:
                isValid = False
                break
        if isValid:
            validTickets.append(numbers)

rows = {}

for field in fields:
    rows[field] = []
    value = fields[field]
    for i in range(0, len(fields)):
        valid = True
        for j in range(0, len(validTickets)):
            number = validTickets[j][i]
            if not ((number >= value[0][0] and number <= value[0][1]) or (number >= value[1][0] and number <= value[1][1])):
                valid = False
                break
        if valid:
            rows[field].append(i)

foundList = []
finalRows = ["" for i in range(0, len(fields))]
while "" in finalRows:
    for row in rows:
        rowData = rows[row]
        modifiedData = [i for i in rowData if i not in foundList]
        if len(modifiedData) == 1:
            finalRows[modifiedData[0]] = row
            foundList.append(modifiedData[0])

finalValue = 1
ticketNumbers = [int(i) for i in lines[1].split('\n')[1].split(',')]
localIndex = 0
for row in finalRows:
    if row.startswith("departure"):
        finalValue *= ticketNumbers[localIndex]
    localIndex += 1

print(finalValue)