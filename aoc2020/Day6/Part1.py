inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

groups = [interval for interval in inputs[selectedInput].split("\n\n") if interval != '']

counts = 0
for answers in groups:
    questions = []
    for letter in answers:
        if letter != '\n' and letter not in questions:
            questions.append(letter)
    counts += len(questions)

print(counts)
