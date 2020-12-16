while (True):
    data = input('puzzle input\n')
    passRange = data.split('-')

    numValid = 0

    for test in range(int(passRange[0]), int(passRange[1]) + 1): # end is non inclusive
        val = str(test)
        prevChar = val[0]
        foundAdj = False
        sameValCount = 1
        valid = True
        for i in range(1, len(val)):
            if (foundAdj == False):
                checkCount = False
                if (val[i] == prevChar):
                    sameValCount += 1
                else:
                    checkCount = True
                    
                if (checkCount == True or i == len(val) - 1):
                    if (sameValCount == 2):
                        foundAdj = True
                    sameValCount = 1

            if (int(val[i]) < int(prevChar)):
                valid = False
                break
            
            prevChar = val[i]
            
        if (valid and foundAdj):
            numValid += 1
    print('num valid: ' + str(numValid))
