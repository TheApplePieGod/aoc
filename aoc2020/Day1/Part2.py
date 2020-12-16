inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

numbers = [int(interval) for interval in inputs[selectedInput].split("\n") if interval != '']

answer = 0
for num in numbers:
    for num2 in numbers:
        for num3 in numbers:
            if num + num2 + num3 == 2020:
                answer = num * num2 * num3
                break
    if answer != 0:
        break
print("Answer: " + str(answer))