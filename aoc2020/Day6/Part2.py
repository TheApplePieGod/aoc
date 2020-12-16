inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

groups = [interval for interval in inputs[selectedInput].split("\n\n") if interval != '']

counts = 0
for answers in groups:
    questions = []
    people = answers.split('\n')
    for answer in people:
        for letter in answer:
            if letter not in questions:
                found = True
                for answer2 in people:
                    if letter not in answer2:
                        found = False
                if found:
                    questions.append(letter)
    counts += len(questions)

print(counts)