inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

numValid = 0
for line in lines:
    split1 = line.split('-')
    split2 = split1[1].split(" ")
    rangeLow = int(split1[0])
    rangeHigh = int(split2[0])
    letter = split2[1][0]
    password = split2[2]
    letterCount = password.count(letter)
    if letterCount >= rangeLow and letterCount <= rangeHigh:
        numValid += 1

print("Num valid: " + str(numValid))
