inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

operators = ['*', '+']

def evaluate(lineIndex):
    terms = []
    lowestDepth = 0
    currentDepth = 0
    innerDepth = 0
    for c in lines[lineIndex].split(' '):
        modifiedC = c.replace('(', '').replace(')', '')
        if '(' in c:
            currentDepth += 1 * c.count('(')
            innerDepth = 0
        if modifiedC.isnumeric():
            terms.append([currentDepth, innerDepth, int(modifiedC)])
            innerDepth = 0
        elif c in operators:
            if c == '+':
                innerDepth = 1
                if terms[len(terms) - 1][0] == currentDepth:
                    terms[len(terms) - 1][1] = innerDepth
            terms.append([currentDepth, innerDepth, c])
        if ')' in c:
            currentDepth -= 1 * c.count(')')
            innerDepth = 0
        if currentDepth > lowestDepth:
            lowestDepth = currentDepth

    currentValue = None
    while len(terms) > 1:
        tempTerms = []
        newTerms = terms
        evaluating = False
        currentValue = None
        lastOperator = None
        lowestInner = 1

        while lowestInner >= 0:
            for i, term in enumerate(newTerms):
                evaluated = False
                if term[0] == lowestDepth and term[1] == lowestInner:
                    evaluated = True
                    evaluating = True
                    if type(term[2]) == int:
                        if currentValue == None:
                            currentValue = term[2]
                        elif lastOperator == '*':
                            currentValue *= term[2]
                        elif lastOperator == '+':
                            currentValue += term[2]
                    else:
                        lastOperator = term[2]
                        tempLen = len(tempTerms)
                        if lastOperator == '+' and tempLen > 0 and tempTerms[tempLen - 1][0] == currentDepth and type(tempTerms[tempLen - 1][2]) == int:
                            tempTerms[tempLen - 1][1] = 1

                if (not evaluated or i == len(newTerms) - 1) and evaluating:
                    evaluating = False
                    if lowestInner == 0:
                        frontOp = newTerms[i][2] if (newTerms[i][2] in operators and newTerms[i][0] == lowestDepth - 1) else ''
                        backOp = tempTerms[len(tempTerms) - 1][2] if len(tempTerms) > 0 and tempTerms[len(tempTerms) - 1][0] == lowestDepth - 1 else ''

                        if frontOp == '+' or backOp == '+':
                            tempTerms.append([lowestDepth - 1, 1, currentValue])
                        else:
                            tempTerms.append([lowestDepth - 1, 0, currentValue])
                    else:
                        tempTerms.append([lowestDepth, lowestInner - 1, currentValue])
                    currentValue = None
                    lastOperator = None
                if (not evaluated):
                    tempTerms.append(term)
            newTerms = tempTerms
            tempTerms = []
            lowestInner -= 1
        terms = newTerms
        lowestDepth -= 1
    return terms[0][2]

totalVal = 0
for i in range(0, len(lines)):
    totalVal += evaluate(i)
print(totalVal)