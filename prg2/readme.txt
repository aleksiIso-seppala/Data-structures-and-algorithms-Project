Readme file for the second phase of the project

The roads are stored in two places, first of them is the all_roads_ vector. This
vector is updated everytime a new road is added or a road is deleted. The roads
are stored in the vector as they are returned in the all_roads() function, so
the function becomes O(1). The vector is only used for this function.

The second place where the roads are stored is inside the Town struct. The stuct
has a few added parameters to accommodate for the roads:

vector<Town*> adjacent_towns_:
used to store pointers to all the towns that the town
has access to via roads. Vector was chosen because, it is fast to 
go through the towns and they rarely need to be accessed otherwise,
the exception being when the adjacent town needs to be deleted.

Color color_:
Color is std::string, where the color of the town is stored. The color is used to
determine whether the town has been accessed in an algorithm.

Town* pi_:
this is a pointer to the town where this town was accessed from. This is also
used in the algorithms.

Distance dist_:
Distance is int, which stores distances from starting town to destination. This
is used by the Dijsktra algorithm.

With these parameters, the roads can be accessed and various algorithms can be
performed to them.
