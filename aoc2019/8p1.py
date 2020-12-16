while (True):
    width = int(input('width\n'))
    height = int(input('height\n'))
    data = input('puzzle input\n')
    pixels = list(map(int, list(data)))
    numLayers = int(len(pixels) / (width * height))
    fewestZeros = 99999999999
    fzLayer = 0

    currentIndex = 0
    for i in range(numLayers):
        zeros = 0
        for p in range(width * height):
            if (pixels[currentIndex] == 0):
                zeros += 1
            currentIndex += 1
        if (zeros < fewestZeros):
            fewestZeros = zeros
            fzLayer = i

    
    currentIndex = fzLayer * width * height
    num1s = 0
    num2s = 0
    for p in range(width * height):
        if (pixels[currentIndex] == 1):
            num1s += 1
        elif (pixels[currentIndex] == 2):
            num2s += 1
        currentIndex += 1
    print('num of 1s * num of 2s = ' + str(num1s * num2s))
    
