while (True):
    data = input('puzzle input \n')
    compOutput = int(input('output equals\n'))
    initData = list(map(int, data.split(',')))
    ints = []
    currentNoun = -1
    currentVerb = -1
    output = 0

    while (output != compOutput):
        currentNoun += 1
        if (currentNoun > 99):
            currentNoun = 0
            currentVerb += 1
            
        ints = initData.copy()
        ints[1] = currentNoun
        ints[2] = currentVerb
        
        index = 0
        while (index + 3 < len(ints)):
            opcode = int(ints[index])

            if (opcode == 1): # add
                ints[ints[index + 3]] = ints[ints[index + 1]] + ints[ints[index + 2]]
            elif (opcode == 2): # mul
                ints[ints[index + 3]] = ints[ints[index + 1]] * ints[ints[index + 2]]
            elif (opcode == 99):
                break;
            
            index += 4
        output = ints[0]

    print('100 * noun + verb = ' + str(100 * currentNoun + currentVerb))
