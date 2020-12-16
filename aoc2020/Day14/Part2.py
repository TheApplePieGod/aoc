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
        memIndexBinaryString = "{0:b}".format(memIndex)
        maskOffset = len(currentMask) - len(memIndexBinaryString)
        finalMem = ""
        for i in range(0, len(currentMask)):
            addingValue = '0'
            if i >= maskOffset:
                addingValue = memIndexBinaryString[i - maskOffset]
            if currentMask[i] == '0':
                finalMem += addingValue
            else:
                finalMem += currentMask[i]

        xCount = finalMem.count('X')
        for i in range(0, pow(2, xCount)):
            xReplacer = ("{:0" + str(xCount) + "b}").format(i)
            newMem = ""
            xCountLocal = 0
            for j in range(0, len(finalMem)):
                if finalMem[j] == 'X':
                    newMem += xReplacer[xCountLocal]
                    xCountLocal += 1
                else:
                    newMem += finalMem[j]
            memory[int(newMem, 2)] = settingValue

finalSum = 0
for elem in memory:
    finalSum += memory[elem]
print(finalSum)