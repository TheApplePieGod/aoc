inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lineData = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

def find_all_indexes(search_str):
    indexes = []
    index = 0
    for line in lineData:
        if search_str in line:
            indexes.append(index)
        index += 1
    return indexes

def runData(lines):
    acc = 0
    usedInstructions = []
    instructionPointer = 0

    while instructionPointer < len(lines):
        if (instructionPointer in usedInstructions):
            return
        usedInstructions.append(instructionPointer)
        instruction = lines[instructionPointer].split(' ')[0]
        number = lines[instructionPointer].split(' ')[1]
        sign = 1
        if number[0] == '-':
            sign = -1
        if instruction == 'acc':
            acc += int(number[1:]) * sign
            instructionPointer += 1
        elif instruction == 'nop':
            instructionPointer += 1
        elif instruction == 'jmp':
            instructionPointer += int(number[1:]) * sign
            
    print(acc)

noopIndexes = find_all_indexes("nop")
jmpIndexes = find_all_indexes("jmp")

for index in noopIndexes:
    newData = lineData.copy()
    newData[index] = "jmp" + newData[index][3:]
    runData(newData)

for index in jmpIndexes:
    newData = lineData.copy()
    newData[index] = "nop" + newData[index][3:]
    runData(newData)