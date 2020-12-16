inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval.replace('\n', ' ') for interval in inputs[selectedInput].split("\n\n") if interval != '']
fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]

valid = 0
for passport in lines:
    pairs = passport.split(' ')
    found = 0
    for pair in pairs:
        field = pair.split(':')[0]
        if field in fields:
            found += 1
    if found == len(fields):
        valid += 1
print(valid)