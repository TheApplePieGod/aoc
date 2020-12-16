inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

goalTime = int(lines[0])
numbers = [int(data) for data in lines[1].split(',') if data != 'x']

smallestTimeId = 99999999
smallestTime = 999999999
for number in numbers:
    currentVal = 0
    while currentVal < goalTime:
        currentVal += number
    time = currentVal - goalTime
    if time < smallestTime:
        smallestTimeId = number
        smallestTime = time

print(smallestTime * smallestTimeId)