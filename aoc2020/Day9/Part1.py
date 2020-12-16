inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [int(interval) for interval in inputs[selectedInput].split("\n") if interval != '']

plen = 25

def checkValid(startIndex):
    if startIndex < len(lines):
        check = lines[startIndex]
        for i in range(startIndex - plen, startIndex):
            for j in range(startIndex - plen, startIndex):
                if lines[i] + lines[j] == check:
                    return True
        print(check)
    return False

currentIndex = plen
while (checkValid(currentIndex)):
    currentIndex += 1


