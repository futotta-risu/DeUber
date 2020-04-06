from random import randint


class Car:
    def __init__(self, coords):
        self.pos = coords


class Map:
    n_car = 0
    cars = dict()

    def __init__(self, map_dims = (5,5) ):
        self.width = int(map_dims[0])
        self.height = int(map_dims[1])
        self.map = [[0 for i in range(self.width)] for j in range(self.height)]

    def add_car(self, coords):
        self.cars[self.n_car] = Car(coords)
        self.n_car += 1

    def read_map(self, file_path):
        with open(file_path,"r") as f:
            self.map = [[int(c) for c in line] for line in f]

    def printMap(self):
        return "\n".join(["".join([str(x) for x in self.map[j]]) for j in range(self.height)])

