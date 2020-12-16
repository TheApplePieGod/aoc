inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

goalTime = int(lines[0])
busData = [data for data in lines[1].split(',')]
busses = {}
lastStreak = 0
currentStreak = 0
timestampIncrement = 0
for bus in busData:
    if bus != 'x':
        if timestampIncrement == 0:
            timestampIncrement = int(bus)
        busses[int(bus)] = currentStreak
        lastStreak = currentStreak
        currentStreak = 0
    else:
        currentStreak += 1

currentTimestamp = 0
while True:
    localTimestamp = currentTimestamp
    validBusses = 0
    for bus in busses.keys():
        localTimestamp += busses[bus]
        if localTimestamp % bus != 0:
            break
        else:
            validBusses += 1
        localTimestamp += 1
    if validBusses == len(busses.keys()):
        break
    currentTimestamp += timestampIncrement


print(currentTimestamp + len(busData) - 1)