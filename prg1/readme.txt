Readme file for the first phase of the project

Datastructure for a single town used is a struct "Town". This structure was chosen because the town has multiple parameters
of information and struct is the single best option to keep them in order. The struct has the following parameters:
name_ (stores the name of the town)
coord_ (stores the coordinates of the town in a single Coord struct.
taxes_ (stores the amount of taxes the town gets from its citizens.
master_ (stores the TownID of the town if it has one, otherwise NO_TOWNID.
vassals_ (stores the TownID's of the towns vassals, set<TownID> was chosen instead of a vector so the deletion of a
          specific vassal would be easier).

The Towns are stored in an unordered_map<TownID, Town>. Unordered_map was the clear choice to store all the towns since
the towns didn't need to be in order, but they needed to be accessible easily through their TownID.

Additionally there is a multimap<Distance, TownID> "distances_from_origo". This map stores information with the key being
the distance from origo and the payload being the corresponding town. This structure wasn't necessary to complete the
project, but it significantly speedied up multiple functions, because they regularly need information about the towns 
distance from origo. By using a multimap, multiple same distance with different TownIDs could be added to the map.
The map is keeping all the distances in order all the time, so functions like mindist, maxdist and towns_distance_increasing
became much faster, and was the reason I included the datastructure in the first place.