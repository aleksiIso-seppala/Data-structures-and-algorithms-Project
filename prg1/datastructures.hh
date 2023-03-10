// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

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

// Types for IDs
using TownID = std::string;
using Name = std::string;

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

    // Estimate of performance: O(n)
    // Short rationale for estimate: It may be even O(1), but I couldn't find
    // performances for function used in here (size()).
    // But i'm sure it can't be slower than O(n).
    unsigned int town_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: map::clear algorithm used in the function
    // is O(n)
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Function calls a helper function which is O(n) and
    // after that creates the struct and inserts it to the map and that is O(n) ??(1).
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance: O(n) and ??(1)
    // Short rationale for estimate: Helper function does_town_exist is O(n) and after that
    // insertion to unordered_map is O(n) and ??(1)
    Name get_town_name(TownID id);

    // Estimate of performance: O(n) and ??(1)
    // Short rationale for estimate: Helper function does_town_exist is O(n) and after that
    // getting the coordinates is O(n) and ??(1).
    Coord get_town_coordinates(TownID id);

    // Estimate of performance: O(n) and ??(1)
    // Short rationale for estimate: Helper function does_town_exist is O(n) and after that
    // getting the tax is O(n) and ??(1).
    int get_town_tax(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: function goes trough all towns in the unordered_map (O(n)) and
    // adds them to the back of the vector (O(1)).
    std::vector<TownID> all_towns();

    // Estimate of performance: O(n)
    // Short rationale for estimate: function goes through all towns in the unordered_map (O(n)) and
    // adds the ones with the correct name to the back of the vector (O(1)).
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Helper function does_town_exist is O(n) and the setting of the
    // new name after that is O(n) and ??(1) (the accessing of the correct town and changing the name).
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance: O(n*logn)
    // Short rationale for estimate: First uses the all_towns function (O(n)) and after that
    // uses std::sort to sort the names alphabetically (O(n*logn)).
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through a multimap O(n) and adds the TownID to vector (O(1))
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Takes the first element of the multimap O(n).
    TownID min_distance();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Takes the last element of the multimap O(n);
    TownID max_distance();

    // Estimate of performance: O(logn)
    // Short rationale for estimate: adds the vassal to set
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(n), where the n is the number of vassals the town has
    // Short rationale for estimate: function goes through the set of vassals O(n) and
    // adds them to the back of the vector.
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance: O(n), where n is the size of the vector that the function
    // returns.
    // Short rationale for estimate: goes through towns, adds their master (O(n) ??(1))
    // to the vector (O(1)) until the master is NO_TOWNID.
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: at worst needs to remove the town from the map (O(n) ??(1)),
    // and add the towns vassals to a new master (O(n)). also needs to remove the town from their
    // masters vassal set (O(n)).
    bool remove_town(TownID id);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: First gets all towns from all_towns function (O(n)),
    // then uses std::sort(O(nlogn) to calculate the distance from a set coordinate using
    // lambda function calculate_distance(O(1)) for comparisons.
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: Uses a recursive function to go through the vassals and find the
    // longest path. N is the total amount of vassals that are under the town (this counts also their
    // vassals, and their vassals and so forth). All single operations are O(1) with a few exceptions.
    // Getting information from the map is O(n), ??(1). And inserting the new town to the front of the
    // vector is O(n).
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: Uses a recursive function to go through all the vassals and get
    // their taxes. N is the total amount of vassals that are under the town (this counts alsot their
    // vassals, and their vassals and so forth. All of the operations where information is fetched
    // from the map are O(n), ??(1).
    int total_net_tax(TownID id);

private:
    // Add stuff needed for your class implementation here

    int calculate_distance(Coord coord1, Coord coord2);
    bool does_town_exist(TownID id);

    struct Town{
      Name name_;
      Coord coord_;
      int taxes_;
      TownID master_ = NO_TOWNID;
      std::set<TownID> vassals_;
      Distance dist_to_origo_;

    };

    std::unordered_map<TownID, Town> towns_;
    std::multimap<Distance,TownID> distances_from_origo_;


};

#endif // DATASTRUCTURES_HH
