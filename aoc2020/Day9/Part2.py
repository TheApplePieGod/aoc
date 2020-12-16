inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [int(interval) for interval in inputs[selectedInput].split("\n") if interval != '']

brokenNum = 1492208709

def checkContiguous(startIndex):
    if startIndex < len(lines):
        nums = []
        currentSum = 0
        smallest = 999999999
        largest = 0
        for i in range(startIndex, len(lines)):
            currentSum += lines[i]
            nums.append(lines[i])
            if lines[i] < smallest:
                smallest = lines[i]
            elif lines[i] > largest:
                largest = lines[i]
            if currentSum >= brokenNum:
                break
        if currentSum == brokenNum:
            print(smallest + largest)
            return True
    return False

currentIndex = 0
while (not checkContiguous(currentIndex)):
    currentIndex += 1