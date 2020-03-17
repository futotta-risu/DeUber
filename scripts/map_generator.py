from enum import Enum
from random import randint
from argparse import ArgumentParser


Path_generated_data = "data/generated/"
Folder_map = "maps/"
Suffix_map = ".map"
Support_file_name = "file_info"

Default_map_name = "def"

class GeneratorAlgorithms(Enum):
    RANDOM = 1


class Map:

    def __init__(self, map_dims = (5,5) ):
        self.width = int(map_dims[0])
        self.height = int(map_dims[1])
        self.map = [ [0 for i in range(self.width)] for j in range(self.height)]

    def randomMap(self):
        self.map = [[randint(0, 1) for i in range(self.width)] for j in range(self.height)]

    def printMap(self):
        return "\n".join(["".join([str(x) for x in self.map[j]]) for j in range(self.height)])


class MapGenerator:

    def __init__(self, map_dims = (5,5)):
        self.map = Map(map_dims)
        pass

    def save_map(self, map_name):
        file_info_map = dict()
        with open(Path_generated_data +  Support_file_name, "r") as fR:
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

    def generateMap(self, genAlg):
        if genAlg == GeneratorAlgorithms.RANDOM:
            self.map.randomMap()


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