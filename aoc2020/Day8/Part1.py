inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

acc = 0
usedInstructions = []
instructionPointer = 0

while instructionPointer < len(lines) and instructionPointer not in usedInstructions:
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