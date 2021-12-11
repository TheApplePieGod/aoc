import copy

inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

sections = [interval for interval in inputs[selectedInput].split("\n\n") if interval != '']

rules = {}
for rule in sections[0].split('\n'):
    number = int(rule.split(':')[0])
    rules[number] = []
    data = rule.split(':')[1].split(' | ')
    for option in data:
        option = option.strip()
        if '"' in option:
            rules[number].append(option.replace('"', ''))
        else:
            rules[number].append([int(i) for i in option.split(' ')])

def matches(value, rule):
    if value != '':
        for option in rules[rule]:
            if len(value) >= len(option):
                valueIndex = 0
                matched = 0
                for char in option:
                    if char == 'a':
                        if value[0] == 'a':
                            matched += 1
                    elif char == 'b':
                        if value[0] == 'b':
                            matched += 1
                    else:
                        returned = matches(value[valueIndex:], char)
                        matched += returned[0]
                        valueIndex += max(returned[1] - 1, 0)
                    valueIndex += 1
                if matched == len(option):
                    return [1, valueIndex]
    return [0, 0]

matchedResults = 0
for line in sections[1].split('\n'):
    if line != '':
        returned = matches(line, 0)
        #matchedResults += returned[0]
        if returned[0] == 1 and len(line) == returned[1]:
           print(line)
           matchedResults += 1

print(matchedResults)