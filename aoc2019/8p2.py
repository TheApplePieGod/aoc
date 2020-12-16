while (True):
    width = int(input('width\n'))
    height = int(input('height\n'))
    data = input('puzzle input\n')
    pixels = list(map(int, list(data)))
    finalPixels = []
    layerSize = width * height
    numLayers = int(len(pixels) / layerSize)

    for p in range(layerSize):
        for l in range(numLayers):
            if (pixels[(l * layerSize) + p] == 0):
                finalPixels.append(0)
                break
            elif (pixels[(l * layerSize) + p] == 1):
                finalPixels.append(1)
                break

    st = ''
    print('final image = ')
    index = 0
    for y in range(height):
        for x in range(width):
            if (finalPixels[index] == 1):
                st += '#'
            else:
                st += ' '
            index += 1
        st += '\n'
    print(st)
    
