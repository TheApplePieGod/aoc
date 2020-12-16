while (True):
    progInput = int(input('program input\n'))
    data = input('puzzle input\n')
    ints = list(map(int, data.split(',')))
    lenInts = len(ints)

    index = 0
    while (index < lenInts):
        header = str(ints[index])
        headerLen = len(header)
        opcode = 0
        if (headerLen < 3): # we can assume it is just an opcode
            opcode = int(header)
        else: # last two digits are opcode
            opcode = int(header[2:])

        if (opcode == 1 and index + 3 < lenInts): # add, 3 params
            numParams = 3
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            param2Val = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                ints[ints[index + 3]] = param1Val + param2Val
            index += 4
        elif (opcode == 2 and index + 3 < lenInts): # mul
            numParams = 3
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            param2Val = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                ints[ints[index + 3]] = param1Val * param2Val
            index += 4
        elif (opcode == 3 and index + 1 < lenInts): # input + save
            ints[ints[index + 1]] = progInput
            index += 2
        elif (opcode == 4 and index + 1 < lenInts): # read + output
            value = ints[ints[index + 1]]
            if (value != 0): # prog failed
                print('non-zero output: ' + str(value))
            index += 2
        elif (opcode == 5 and index + 2 < lenInts): # jump if true
            numParams = 2
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            if (param1Val != 0):
                index = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            else:
                index += 3
        elif (opcode == 6 and index + 2 < lenInts): # jump if false
            numParams = 2
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            if (param1Val == 0):
                index = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            else:
                index += 3
        elif (opcode == 7 and index + 3 < lenInts): # less than
            numParams = 3
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            param2Val = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                ints[ints[index + 3]] = 1 if param1Val < param2Val else 0
            index += 4
        elif (opcode == 8 and index + 3 < lenInts): # equals
            numParams = 3
            params = ''
            for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
            params += header[:headerLen - 2]
            param1Val = ints[ints[index + 1]] if params[numParams - 1] == '0' else ints[index + 1]
            param2Val = ints[ints[index + 2]] if params[numParams - 2] == '0' else ints[index + 2]
            if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                ints[ints[index + 3]] = 1 if param1Val == param2Val else 0
            index += 4
        elif (opcode == 99):
            break;

    #print (ints)
