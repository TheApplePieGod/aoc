while (True):
    progInput = int(input('program input\n'))
    data = input('puzzle input\n')
    initialInts = list(map(int, data.split(',')))
    ints = []
    lenInts = len(initialInts)
    outputSignals = []
    settings = [0, 1, 2, 3, 4]

    def updateSettings():
        settings[4] += 1
        if (settings[4] == 5):
            settings[4] = 0
            settings[3] += 1
        if (settings[3] == 5):
            settings[3] = 0
            settings[2] += 1
        if (settings[2] == 5):
            settings[2] = 0
            settings[1] += 1
        if (settings[1] == 5):
            settings[1] = 0
            settings[0] += 1  

    def checkSettings():
        invalidSettings = False # settings cannot have repeated digits
        if (settings[0] == 5):
            return True
        for i in range(5):
            for c in range(5):
                if (i != c and settings[i] == settings[c]):
                    invalidSettings = True
                    break
        return invalidSettings

    def runIntComputer(module, inputValue):
        index = 0
        inputInstruction = 0
        ints = initialInts.copy()
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
                if (inputInstruction == 0): # phase setting
                    ints[ints[index + 1]] = settings[module]
                    inputInstruction += 1
                else: # input value
                    ints[ints[index + 1]] = inputValue
                index += 2
            elif (opcode == 4 and index + 1 < lenInts): # read + output
                value = ints[ints[index + 1]]
                if (module == 4): # save val of final module
                    outputSignals.append([value, settings.copy()])
                    #break;
                else: # otherwise startup next module
                    runIntComputer(module + 1, value)
                    #break;
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
                break
            else:
                print('invalid opcode, stopping')

    enabled = True
    while (enabled):
        invalidSettings = checkSettings()
        while (invalidSettings == True):
            updateSettings()
            if (settings[0] == 5):
                enabled = False
                break
            invalidSettings = checkSettings()
            
        if (enabled == True):
            runIntComputer(0, progInput)
            updateSettings()

    maxVal = [0, []]
    for signal in outputSignals:
        if (signal[0] > maxVal[0]):
            maxVal = signal

    print ('max val of ' + str(maxVal[0]) + ' with settings ' + str(maxVal[1][0]) + str(maxVal[1][1]) + str(maxVal[1][2]) + str(maxVal[1][3]) + str(maxVal[1][4]))
