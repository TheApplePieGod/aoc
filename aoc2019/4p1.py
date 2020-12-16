while (True):
    data = input('puzzle input\n')
    passRange = data.split('-')

    numValid = 0

    for test in range(int(passRange[0]), int(passRange[1]) + 1): # end is non inclusive
        val = str(test)
        prevChar = val[0]
        foundAdj = False
        valid = True
        for i in range(1, len(val)):
            if (val[i] == prevChar):
                foundAdj = True
            elif (int(val[i]) < int(prevChar)):
                valid = False
                break
            prevChar = val[i]
        if (valid and foundAdj):
            numValid += 1
    print('num valid: ' + str(numValid))
