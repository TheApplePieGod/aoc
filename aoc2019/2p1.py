while (True):
    data = input('puzzle input \n')
    ints = list(map(int, data.split(',')))

    # replace positions
    ints[1] = 12
    ints[2] = 2

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

    print (ints[0])
