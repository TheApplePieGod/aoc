inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

data = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

bagData = {}
for line in data:
    color = line.split(" contain ")[0]
    contains = line.split(" contain ")[1].split(',')
    bagDataLine = []
    for contain in contains:
        contain = contain.strip()
        amount = contain[0]
        containColor = contain[2:]
        containColor = containColor.replace('.','')
        if containColor[-1] != 's':
            containColor += 's'
        bagDataLine.append([containColor, amount])
    bagData[color] = bagDataLine

amount = 0
def getBagCount(bag):
    total = 0
    if bag in bagData.keys():
        for line in bagData[bag]:
            bagCount = getBagCount(line[0])
            try:
                total += bagCount * int(line[1]) + int(line[1])
            except ValueError:
                total += 0
    return total

amount += getBagCount('shiny gold bags')

print(amount)