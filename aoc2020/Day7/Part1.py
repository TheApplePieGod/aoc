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
def hasGold(bag):
    global amount
    if bag in bagData.keys():
        for line in bagData[bag]:
            if "shiny gold bag" in line or "shiny gold bags" in line:
                amount += 1
                return True
        for line in bagData[bag]:
            if hasGold(line[0]):
                return True
    return False

for bag in bagData.keys():
    hasGold(bag)

print(amount)