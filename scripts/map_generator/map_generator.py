from enum import Enum
from argparse import ArgumentParser
from scripts import map_simulator as MS

from random import randint, uniform

Path_generated_data = "../data/generated/"
Folder_map = "maps/"
Suffix_map = ".map"
Support_file_name = "file_info"

Default_map_name = "def"


class GeneratorAlgorithms(Enum):
    RANDOM = 1
    LSYSTEM = 2


class MapGenerator:

    def __init__(self, map_dims = (5,5)):
        self.map = MS.Map(map_dims)
        pass

    def save_map(self, map_name):
        file_info_map = dict()
        with open(Path_generated_data + Support_file_name, "r") as fR:
            for line in fR:
                key, value = [part.strip() for part in line.split(":")]
                file_info_map[key] = value
        with open(Path_generated_data + Folder_map + map_name + value + Suffix_map, "w+") as f:
            f.write(f"{self.map.width} {self.map.height}\n")
            f.write(self.map.printMap())
        file_info_map["map_file_id"] = str(int(file_info_map["map_file_id"])+1)

        with open(Path_generated_data +  Support_file_name, "w+") as fR:
            for key, value in file_info_map.items():
                fR.write(str(key) + ":" + str(value) + "\n")

    def lsystem(self, n_iter = 10, alpha = 0.8, ran_val = 2):

        l = [[self.map.width, self.map.width, 0, 0]]
        l2 = []

        for i in range(n_iter):
            for j in l:
                if j[0]<=2 or j[1]<=2:
                    l2+=[j]
                    continue
                if uniform(0, 1) < alpha:
                    if uniform(0, 1) < 0.5*(j[0]**ran_val/(j[0]**ran_val+j[1]**ran_val)):
                        n_width = randint(1, j[0]-2)
                        l2 += [[n_width, j[1], j[2], j[3]], [j[0]-n_width-1, j[1], j[2]+n_width+1, j[3]]]
                    else:
                        n_height = randint(1, j[1]-2)
                        l2 += [[j[0], n_height, j[2], j[3]], [j[0], j[1]-n_height-1, j[2], j[3]+n_height+1]]
                    continue
                l2 += [j]
                l = l2.copy()
                l2 = []
        mapa = [[0 for j in range(self.map.width)] for j in range(self.map.height)]

        for j in l:
            for a1 in range(j[2], j[2]+j[0]):
                for a2 in range(j[3], j[3]+j[1]):
                    mapa[a2][a1] = 1
        self.map.map = mapa.copy()

    def generateMap(self, genAlg):
        if genAlg == GeneratorAlgorithms.RANDOM:
            self.map.randomMap()
        elif genAlg == GeneratorAlgorithms.LSYSTEM:
            self.lsystem()

if __name__ == "__main__":

    parser = ArgumentParser()
    parser.add_argument("-f", "--file", dest="filename",
                        help="Name of the file to save the map", metavar="FILE")
    parser.add_argument("-md", "--map_dims", dest="map_dims", nargs=2,
                        help="Dimensions of the map", metavar=("WIDTH","HEIGHT"))
    args = parser.parse_args()

    file_name = Default_map_name
    if args.filename is not None:
        file_name = args.filename

    map_dims = (5,5)
    if args.map_dims is not None:
        map_dims = args.map_dims

    mG = MapGenerator(map_dims)
    mG.generateMap(GeneratorAlgorithms.RANDOM)
    mG.save_map(file_name)