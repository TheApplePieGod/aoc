import re

inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

lines = [interval.replace('\n', ' ') for interval in inputs[selectedInput].split("\n\n") if interval != '']
fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
eyeColors = ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]

valid = 0
for passport in lines:
    pairs = passport.split(' ')
    found = 0
    for pair in pairs:
        if pair != '':
            key = pair.split(':')[0]
            value = pair.split(':')[1]
            if key == "byr" and int(value) >= 1920 and int(value) <= 2002:
                found += 1
            if key == "iyr" and int(value) >= 2010 and int(value) <= 2020:
                found += 1
            if key == "eyr" and int(value) >= 2020 and int(value) <= 2030:
                found += 1
            if key == "hgt" and ((value[-2:] == "cm" and int(value[0:-2]) >= 150 and int(value[0:-2]) <= 193) or (value[-2:] == "in" and int(value[0:-2]) >= 59 and int(value[0:-2]) <= 76)):
                found += 1
            if key == "hcl" and len(value) == 7 and re.search(r"#([0-9A-Fa-f]{6})", value):
                found += 1
            if key == "ecl" and value in eyeColors:
                found += 1
            if key == "pid" and len(value) == 9 and value.isnumeric():
                found += 1

    if found == len(fields):
        valid += 1
print(valid)
