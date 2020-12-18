inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

operators = ['*', '+']

def evaluate(lineIndex):
    terms = []
    lowestDepth = 0
    currentDepth = 0
    for c in lines[lineIndex].split(' '):
        modifiedC = c.replace('(', '').replace(')', '')
        if '(' in c:
            currentDepth += c.count('(')
        if modifiedC.isnumeric():
            terms.append([currentDepth, int(modifiedC)])
        elif c in operators:
            terms.append([currentDepth, c])
        if ')' in c:
            currentDepth -= c.count(')')
        if currentDepth > lowestDepth:
            lowestDepth = currentDepth

    while lowestDepth >= 0:
        newTerms = []
        evaluating = False
        currentValue = None
        lastOperator = None
        for i, term in enumerate(terms):
            evaluated = False
            if term[0] == lowestDepth:
                evaluated = True
                evaluating = True
                if type(term[1]) == int:
                    if currentValue == None:
                        currentValue = term[1]
                    elif lastOperator == '*':
                        currentValue *= term[1]
                    elif lastOperator == '+':
                        currentValue += term[1]
                else:
                    lastOperator = term[1] 

            if (not evaluated or i == len(terms) - 1) and evaluating:
                evaluating = False
                newTerms.append([lowestDepth - 1, currentValue])
                currentValue = None
                lastOperator = None
            if (not evaluated):
                newTerms.append(term)
        terms = newTerms
        lowestDepth -= 1

    return newTerms[0][1]

totalVal = 0
for i in range(0, len(lines)):
    totalVal += evaluate(i)
print(totalVal)