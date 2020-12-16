import os
clear = lambda: os.system('cls')

while (True):
    progInput = int(input('program input\n'))
    data = input('puzzle input\n')
    initialInts = list(map(int, data.split(',')))
    modules = []
    moduleData = []
    lenInts = len(initialInts)
    outputSignals = []
    settings = [5, 6, 7, 8, 9]
    complete = False

    def updateSettings():
        settings[4] += 1
        if (settings[4] == 10):
            settings[4] = 5
            settings[3] += 1
        if (settings[3] == 10):
            settings[3] = 5
            settings[2] += 1
        if (settings[2] == 10):
            settings[2] = 5
            settings[1] += 1
        if (settings[1] == 10):
            settings[1] = 5
            settings[0] += 1  

    def checkSettings():
        invalidSettings = False # settings cannot have repeated digits
        if (settings[0] == 10):
            return True
        for i in range(5):
            for c in range(5):
                if (i != c and settings[i] == settings[c]):
                    invalidSettings = True
                    break
        return invalidSettings

    def runIntComputer(module, inputValue):
        global complete
        index = moduleData[module][1]
        outputVal = 0
        while (index < lenInts):
            if (complete == True):
                break
            #clear()
            #print(outputSignals)
            #print('0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28')
            header = str(modules[module][index])
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
                param1Val = modules[module][modules[module][index + 1]] if params[numParams - 1] == '0' else modules[module][index + 1]
                param2Val = modules[module][modules[module][index + 2]] if params[numParams - 2] == '0' else modules[module][index + 2]
                if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                    modules[module][modules[module][index + 3]] = param1Val + param2Val
                    #print('added ' + str(param1Val + param2Val) + ' at pos ' + str(index + 3))
                index += 4
            elif (opcode == 2 and index + 3 < lenInts): # mul
                numParams = 3
                params = ''
                for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
                params += header[:headerLen - 2]
                param1Val = modules[module][modules[module][index + 1]] if params[numParams - 1] == '0' else modules[module][index + 1]
                param2Val = modules[module][modules[module][index + 2]] if params[numParams - 2] == '0' else modules[module][index + 2]
                if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                    modules[module][modules[module][index + 3]] = param1Val * param2Val
                index += 4
            elif (opcode == 3 and index + 1 < lenInts): # input + save
                if (moduleData[module][0] == False): # phase setting
                    modules[module][modules[module][index + 1]] = settings[module]
                    moduleData[module][0] = True
                else: # input value
                    modules[module][modules[module][index + 1]] = inputValue
                index += 2
            elif (opcode == 4 and index + 1 < lenInts): # read + output
                moduleData[module][1] = index + 2 # keep track of pos
                outputVal = modules[module][modules[module][index + 1]]
                if (module == 4): # save val of final module
                    outputSignals.append([outputVal, settings.copy()])
                    runIntComputer(0, outputVal)
                else: # otherwise startup next module w/ looping
                    if (len(modules[module+1]) == 0): # not initialized yet
                        modules[module+1] = initialInts.copy()
                    runIntComputer(module + 1, outputVal)
                index += 2
            elif (opcode == 5 and index + 2 < lenInts): # jump if true
                numParams = 2
                params = ''
                for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
                params += header[:headerLen - 2]
                param1Val = modules[module][modules[module][index + 1]] if params[numParams - 1] == '0' else modules[module][index + 1]
                if (param1Val != 0):
                    index = modules[module][modules[module][index + 2]] if params[numParams - 2] == '0' else modules[module][index + 2]
                else:
                    index += 3
            elif (opcode == 6 and index + 2 < lenInts): # jump if false
                numParams = 2
                params = ''
                for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
                params += header[:headerLen - 2]
                param1Val = modules[module][modules[module][index + 1]] if params[numParams - 1] == '0' else modules[module][index + 1]
                if (param1Val == 0):
                    index = modules[module][modules[module][index + 2]] if params[numParams - 2] == '0' else modules[module][index + 2]
                else:
                    index += 3
            elif (opcode == 7 and index + 3 < lenInts): # less than
                numParams = 3
                params = ''
                for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
                params += header[:headerLen - 2]
                param1Val = modules[module][modules[module][index + 1]] if params[numParams - 1] == '0' else modules[module][index + 1]
                param2Val = modules[module][modules[module][index + 2]] if params[numParams - 2] == '0' else modules[module][index + 2]
                if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                    modules[module][modules[module][index + 3]] = 1 if param1Val < param2Val else 0
                index += 4
            elif (opcode == 8 and index + 3 < lenInts): # equals
                numParams = 3
                params = ''
                for i in range((numParams - (headerLen - 2))): params += '0' # append 0 for missing parameter modes
                params += header[:headerLen - 2]
                param1Val = modules[module][modules[module][index + 1]] if params[numParams - 1] == '0' else modules[module][index + 1]
                param2Val = modules[module][modules[module][index + 2]] if params[numParams - 2] == '0' else modules[module][index + 2]
                if (params[numParams - 3] == '0'): # dont do anything if output is in immediate mode
                    modules[module][modules[module][index + 3]] = 1 if param1Val == param2Val else 0
                index += 4
            elif (opcode == 99):
                if (module == 4):
                    complete = True
                return
            else:
                print('invalid opcode: ' + str(opcode))
            moduleData[module][1] = index
            #print(modules[0])
            #print(modules[1])
            #print(modules[2])
            #print(modules[3])
            #print(modules[4])

    enabled = True
    while (enabled):
        invalidSettings = checkSettings()
        while (invalidSettings == True):
            updateSettings()
            if (settings[0] == 10):
                enabled = False
                break
            invalidSettings = checkSettings()
                
        if (enabled == True):
            complete = False
            modules = [[], [], [], [], []]
            moduleData = [[False, 0], [False, 0], [False, 0], [False, 0], [False, 0]]
            modules[0] = initialInts.copy()
            runIntComputer(0, progInput)
            updateSettings()
    #modules[0] = initialInts.copy()
    #settings = [9, 8, 7, 6, 5]
    #runIntComputer(0, progInput)

    maxVal = [0, []]
    for signal in outputSignals:
        if (signal[0] > maxVal[0]):
            maxVal = signal

    print ('max val of ' + str(maxVal[0]) + ' with settings ' + str(maxVal[1][0]) + str(maxVal[1][1]) + str(maxVal[1][2]) + str(maxVal[1][3]) + str(maxVal[1][4]))

