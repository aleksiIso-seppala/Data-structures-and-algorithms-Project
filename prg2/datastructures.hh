// Datastructures.hh
//
// Student name: Aleksi Iso-Seppälä
// Student email: aleksi.iso-seppala@tuni.fi
// Student number: H292168

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <algorithm>

// Types for IDs
using TownID = std::string;
using Name = std::string;
using Color = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int town_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_town_name(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_town_coordinates(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int get_town_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> all_towns();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID min_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    TownID max_distance();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_town(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    int total_net_tax(TownID id);


    // Phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: function needs to go through all the towns to delete their connection
    // to other towns via roads.
    void clear_roads();

    // Estimate of performance: O(1)
    // Short rationale for estimate: returns the vector that has all the roads stored in it with the
    // add_road function.
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(n)
    // Short rationale for estimate: this function would be faster, but in order to find if the road already exists
    // we need to go through all the roads in the network. This is done with std::find for the vector (O(n)), in which
    // n is the amount of roads.
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function is O(n) where n is the amount of towns connected to the town searched.
    // So unless the town is connected to every other town in the network, this isn't as slow as O(n) would suggest.
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function calls breadth_first_search function (complexity) to map out the route,
    // but before that it needs to go through all the towns in order (O(n)) to set their parameters so the algorithm works
    // correctly.
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: the function needs to go through multiple vectors in order to completely delete
    // the road. First it needs to remove the connection from both towns (O(n) where n is the amount of towns
    // connected to the searched town). After that it needs to go through the
    // vector with all the roads in it (O(n), where n is the amount of roads) in order to
    // find the correct road to delete.
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: This function is exactly the same as any_route, so the complexity is O(n). This is
    // because in order for the algorithm to work correctly, we need to go through all the towns to reset certain
    // parameters.
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Uses a modified breadth-first-search to find the loops in the network
    // but first it needs to reset the parameters in all towns, so it needs to go through all the towns before
    // the algorithm.
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Uses the djikstra algorithm (complexity) to find the shortest route, but before that
    // it needs to reset the parameters in all towns.
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    Distance trim_road_network();

private:

    struct Town;

    // Add stuff needed for your class implementation here
    int calculate_distance(Coord coord1, Coord coord2);
    bool does_town_exist(TownID id);
    std::vector<TownID> breadth_first_search(Town* fromtown, Town* totown);
    std::vector<TownID> depth_first_search(Town* fromtown);
    std::vector<TownID> dijkstra(Town* fromtown, Town* totown);
    void Relax(Town* u, Town* v);


    struct Town{
      // data needed for towns
      TownID ID_;
      Name name_;
      Coord coord_;
      int taxes_;
      TownID master_ = NO_TOWNID;
      std::set<TownID> vassals_;
      Distance dist_to_origo_;

      // data needed for roads
      std::vector<Town*> adjacent_towns_;
      Color color_ = "white";
      Town* pi_ = nullptr;
      Distance dist_;

    };

    std::unordered_map<TownID, Town> towns_;
    std::multimap<Distance,TownID> distances_from_origo_;
    std::vector<std::pair<TownID,TownID>> all_roads_;

};

#endif // DATASTRUCTURES_HH
