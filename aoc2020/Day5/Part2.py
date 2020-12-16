import math

inputFile = open("Input.txt", "r")
inputs = inputFile.read().split(';\n')
selectedInput = int(input("Which input to use? (0 - " + str(len(inputs) - 1) + ") "))

rows = [interval for interval in inputs[selectedInput].split("\n") if interval != '']

seats = []
for row in rows:
    currentRow = 0
    rowHigh = 127
    currentCol = 0
    colHigh = 7
    for operation in row:
        if operation == 'F':
            rowHigh = math.ceil((rowHigh - currentRow) / 2.0 + currentRow)
        elif operation == 'B':
            currentRow = math.ceil((rowHigh - currentRow) / 2.0 + currentRow)
        elif operation == 'L':
            colHigh = math.ceil((colHigh - currentCol) / 2.0 + currentCol)
        elif operation == 'R':
            currentCol = math.ceil((colHigh - currentCol) / 2.0 + currentCol)
    seatId = currentRow * 8 + currentCol
    seats.append(seatId)

seats.sort()
lastSeat = seats[0]
for i in range(1, len(seats)):
    if seats[i] - 1 != lastSeat:
        print(seats[i] - 1)
        break
    lastSeat = seats[i]

