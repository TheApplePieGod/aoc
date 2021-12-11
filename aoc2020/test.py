class Object:
    def __init__(self, initial_value):
        self.value = initial_value

    def add_value(self, val):
        self.value += val

    def print_value(self):
        print(self.value)

obj = Object(10)
obj.add_value(5)
obj.print_value()