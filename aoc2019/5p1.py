while (True):
    progInput = int(input('program input\n'))
    data = input('puzzle input\n')
    ints = list(map(int, data.split(',')))

    index = 0
    nextInstruction = 0
    while (index + nextInstruction < len(ints)):
        header = str(ints[index])
        headerLen = len(header)
        opcode = 0
        if (headerLen < 3): # we can assume it is just an opcode
            opcode = int(header)
        else: # last two digits are opcode
                opcode = int(header[2:])

        if (opcode == 1): # add, 3 params
            nextInstruction = 4
            numParams = 3
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            param2Val = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            #param3Val = ints[ints[index + 3]] if params[numParams - 3] == '0' else ints[index + 3]
            if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                ints[ints[index + 3]] = param1Val + param2Val
        elif (opcode == 2): # mul
            nextInstruction = 4
            numParams = 3
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            param2Val = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            #param3Val = ints[ints[index + 3]] if params[numParams - 3] == '0' else ints[index + 3]
            if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                ints[ints[index + 3]] = param1Val * param2Val
        elif (opcode == 3): # input + save
            nextInstruction = 2
            ints[ints[index + 1]] = progInput
        elif (opcode == 4): # read + output
            nextInstruction = 2
            value = ints[ints[index + 1]]
            if (value != 0): # prog failed
                print('failed with val: ' + str(value))
        elif (opcode == 99):
            break;
        
        index += nextInstruction

    #print (ints)
