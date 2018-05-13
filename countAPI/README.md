The problme: Given a vector with a list of strings representing directories. Return another vector
in a specific format that indicate which folder is under another folder, with number representing how 
many items in that folder.

Complication: 

1) three layer directory, storing the data as map inside another map would work...
BUT hard for the top layer map to count how many items inside its nested map.
Because we would read the data structure from outer folder to inner folders, outer folder cannot look ahead before
accessing the inner folders.

2) the result need to be in the extra same order as they are read, and map order automatically

Solution: 

1) Instead of storing them as maps inside map, store them as a struct inside map,
with each struct acting as a folder, containing a map , a number counting the items. 
Basically all the information are generated and stored in the struct as we append the data.

2) Instead of iterating through the map, store another vector indicating the order of files.
Iterate that vector and use it as key to access value in map. 
