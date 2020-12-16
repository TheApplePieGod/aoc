inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [int(interval) for interval in inputs[selectedInput].split("\n") if interval != '']

oneJolt = 0
threeJolt = 1
currentJoltage = 0
failed = False
used = []

while (not failed):
    found = []
    for line in lines:
        if line not in used and line - 3 <= currentJoltage:
            found.append(line)
    
    if len(found) == 0:
        failed = True
    else:
        found.sort()
        line = found[0]
        if line - 3 == currentJoltage:
            threeJolt += 1
        elif line - 1 == currentJoltage:
            oneJolt += 1
        used.append(line)
        currentJoltage = line
        
print(oneJolt * threeJolt)