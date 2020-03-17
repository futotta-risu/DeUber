# Project Documentation

1. [Map Files](#map-files)
    1. [Map Format](#map-format)
    2. [Map File Generation](#map-file-generation)

## Map files

###Map Format
Map files are a common text file with a specific format to import maps into the software.

The format of the map files is the following one:

The first line will contain two integers representing the map width (w) and height (h). The next **h** lines will have **w** consecutive digits in each line representing the type of cell it contains.

| Cell Name | Cell Type | Description |
| ---- | ---- | ----|
| 0 | *FLOOR*| Represents an empty cell. Cars can move through this types of cells.|
| 1 | *BUILDING* | Represents a blocked cell. A car cannot pass through this cells.|
| 2 | *CAR* | Represents a car. **This type of cell should not be in the map file**  |
| 3 | *GOAL* | Represent a goal the car should reach.**This type of cell should not be in the map file**  |

### Map File Generation

> **Attention: Python3 is required to run the script**

To generate random map files, we made a simple Python script which can be found in the scripts folder as map_generator.py. This file will handle the process of creating maps. 

|Argument| Input |Usage |
|---|---| ---| 
| -f, --file| String| Defines the name under which it will be saved |
|-md, --map_dims| Int Int| Defines the dimensions of the map we will be creating|
 
