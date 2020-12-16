inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

memory = {}
currentMask = ""
for line in lines:
    if line.startswith('mask'):
        currentMask = line.split(' ')[2]
    else:
        memIndex = int(line.split('[')[1].split(']')[0])
        settingValue = int(line.split(' ')[2])
        settingValueBinaryString = "{0:b}".format(settingValue)
        maskOffset = len(currentMask) - len(settingValueBinaryString)
        finalValue = ""
        for i in range(0, len(currentMask)):
            addingValue = '0'
            if i >= maskOffset:
                addingValue = settingValueBinaryString[i - maskOffset]
            if currentMask[i] == 'X':
                finalValue += addingValue
            else:
                finalValue += currentMask[i]
        memory[memIndex] = finalValue

finalSum = 0
for elem in memory:
    finalSum += int(memory[elem], 2)
print(finalSum)