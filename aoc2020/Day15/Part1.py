inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [int(interval) for interval in inputs[selectedInput].split(",") if interval != '']

currentAge = 1
lastSpoken = lines[-1]
memory = {}

# insert inital values
for i in range(0, len(lines) - 1):
    memory[lines[i]] = currentAge
    currentAge += 1


while currentAge < 2020:
    newSpoken = lastSpoken
    if lastSpoken in memory:
        newSpoken = currentAge - memory[lastSpoken]
    else:
        newSpoken = 0
    memory[lastSpoken] = currentAge
    lastSpoken = newSpoken
    currentAge += 1

print("Age: " + str(currentAge) + " LastSpoken: " + str(lastSpoken))