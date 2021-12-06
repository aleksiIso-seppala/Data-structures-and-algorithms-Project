// Datastructures.cc
//
// Student name: Aleksi Iso-Seppälä
// Student email: aleksi.iso-seppala@tuni.fi
// Student number: H292168

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <iostream>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

// helper function made to calculate the distance between two coordinates.
int Datastructures::calculate_distance(Coord coord1, Coord coord2){

    int x1 = coord1.x;
    int x2 = coord2.x;
    int y1 = coord1.y;
    int y2 = coord2.y;

    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

bool Datastructures::does_town_exist(TownID id){

    //if town is found, return true.
    if (towns_.find(id) != towns_.end()){
        return true;
    }
    return false;

}

unsigned int Datastructures::town_count()
{
    // return the size of the map
    return towns_.size();
}

void Datastructures::clear_all()
{

    // deleting all  towns
    towns_.clear();
    // deleting all roads
    clear_roads();
    // clearing distances from origo
    distances_from_origo_.clear();

}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{

    if (does_town_exist(id)){
        return false;
    }

    // create a new town with the given parameters.
    Town new_town;
    new_town.name_ = name;
    new_town.coord_ = coord;
    new_town.taxes_ = tax;
    new_town.ID_ = id;
    new_town.dist_to_origo_ = sqrt((coord.x)*(coord.x)+(coord.y)*(coord.y));
    Distance dist = sqrt((coord.x)*(coord.x)+(coord.y)*(coord.y));
    // add town to unordered_map
    towns_.insert({id, new_town});

    // add the distance from origo and town id to multimap.
    distances_from_origo_.insert({dist, id});

    return true;


}

Name Datastructures::get_town_name(TownID id)
{

    if (!does_town_exist(id)){
            return NO_NAME;
    }
    return towns_.at(id).name_;
}

Coord Datastructures::get_town_coordinates(TownID id)
{

    if (!does_town_exist(id)){
            return NO_COORD;
    }

    return towns_.at(id).coord_;
}

int Datastructures::get_town_tax(TownID id)
{

    if (!does_town_exist(id)){
            return NO_VALUE;
    }

    return towns_.at(id).taxes_;

}

std::vector<TownID> Datastructures::all_towns()
{

    std::vector<TownID> towns;

    for (auto &town : towns_){
        towns.push_back(town.first);
    }
    return towns;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{

    std::vector<TownID> towns;

    for (auto &town : towns_){
        if (town.second.name_ == name){
            towns.push_back(town.first);
        }
    }
    return towns;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{

    if (!does_town_exist(id)){
        return false;
    }

    //changing the towns name
    towns_.at(id).name_ = newname;
    return true;

}

std::vector<TownID> Datastructures::towns_alphabetically()
{

    // create a new vector with all the towns in it.
    std::vector<TownID> towns_alphabet;
    towns_alphabet = all_towns();

    // sort the vector with a lambda function that compares
    // the names of the towns.
    std::sort(towns_alphabet.begin(), towns_alphabet.end(),
              [&](auto l,auto r)
    {return towns_.at(l).name_ < towns_.at(r).name_;});
    return towns_alphabet;

}

std::vector<TownID> Datastructures::towns_distance_increasing()
{

    // create a new vector.
    std::vector<TownID> towns_distance;
    std::map<Distance, TownID>::iterator it;
    // go through the towns in distances_from_origo_ multimap and
    // add them to the vector
    for (it=distances_from_origo_.begin();
         it != distances_from_origo_.end();
         it++){
        towns_distance.push_back(it->second);
    }
    return towns_distance;
}

TownID Datastructures::min_distance()
{

    // the minimun distance from origo is found by accessing the first
    // element in the distances_from_origo multimap.
    return distances_from_origo_.begin()->second;
}

TownID Datastructures::max_distance()
{

    // the maximun distance from origo is found by accessing the last
    // element in the distances_from_origo multimap.
    auto iter = distances_from_origo_.end();
    iter--;
    return iter->second;

}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{

    if (!does_town_exist(vassalid)){
        return false;
    }
    if (!does_town_exist(masterid)){
        return false;
    }

    //adds a new master for the vassal and adds the vassal
    // to the masters vector of vassals.
    towns_.at(masterid).vassals_.insert(vassalid);
    towns_.at(vassalid).master_ = masterid;
    return true;

}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{

    std::vector<TownID> vassals;

    if(!does_town_exist(id)){
        vassals.push_back(NO_TOWNID);
        return vassals;
    }



    // goes through the vector of vassals and
    // adds them to the vector
    for (auto& town : towns_.at(id).vassals_){
        vassals.push_back(town);
    }
    return vassals;

}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{

    std::vector<TownID> taxers;
    taxers.push_back(id);
    TownID tmp = id;

    // loop goes through the each vassal and accesses their
    // master adding them to the vector until the current
    // id does not have a master.
    while(towns_.at(tmp).master_ != NO_TOWNID){
        taxers.push_back(towns_.at(tmp).master_);
        TownID current = towns_.at(tmp).master_;
        tmp = current;
    }
    return taxers;

}

bool Datastructures::remove_town(TownID id)
{

    //check if town exists
    if(!does_town_exist(id)){
        return false;
    }

    // remove town from the distances from origo multimap
    for(auto& town : distances_from_origo_){
        if (town.second == id){
            distances_from_origo_.erase(town.first);
            break;
        }
    }


    if(towns_.at(id).master_ == NO_TOWNID){

        // If town had vassals, remove master_ from them.
        for(auto& vassal : towns_.at(id).vassals_){
            towns_.at(vassal).master_ = NO_TOWNID;
        }
        towns_.erase(id);
        return true;
    }

    // remove the current town from its masters vassals;
    towns_.at(towns_.at(id).master_).vassals_.erase(id);

    // go through the vassals and add them under their new master
    for(auto& vassal : towns_.at(id).vassals_){
        add_vassalship(vassal, towns_.at(id).master_);
    }

    towns_.erase(id);
    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{

    // create vecctor off all towns
    auto towns_nearest = all_towns();

    // sort vector with the lambda function using calculate_distance
    // helper function that compares distances.
    sort(towns_nearest.begin(), towns_nearest.end(),[&](auto l, auto r){
        return calculate_distance(towns_.at(l).coord_,coord) <
                calculate_distance(towns_.at(r).coord_,coord);});

    return towns_nearest;

}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{

    std::vector<TownID> longest_path;

    auto town = towns_.find(id);

    // if town doesnt exist, returns a vector with NO_TOWNID in it
    if (town == towns_.end()){
        longest_path.push_back(NO_TOWNID);
        return longest_path;
    }

    // if the town didnt have vassals, add the town to the vector
    // and return it
    if(town->second.vassals_.size() == 0){
       longest_path.push_back(town->first);
       return longest_path;
    }
    else{
        // goes through the towns vassals, and calls longest_vassal_path
        // function.
        for(auto& vassal : town->second.vassals_){
            std::vector path = longest_vassal_path(vassal);

            // comparison between the returned vector and the current
            // longest vector. keeps the longer vector.
            if (longest_path.size() < path.size()){
                longest_path = path;
            }
        }
        // add the current town to the beginning of the vector
        longest_path.insert(longest_path.begin(),id);
        return longest_path;
    }



}

int Datastructures::total_net_tax(TownID id)
{

    if (!does_town_exist(id)){
        return NO_VALUE;
    }

    int taxes = towns_.at(id).taxes_;

    if(towns_.at(id).vassals_.size() != 0){

        //if town had vassals, go through them
        for(auto& vassal : towns_.at(id).vassals_){
            // if the vassal didnt have their own vassals,
            // add a portion of their tax to taxes.
            if(towns_.at(vassal).vassals_.size() == 0){
                int tax_to_pay = 0.1*towns_.at(vassal).taxes_;
                taxes += tax_to_pay;
                continue;
            }
            // if the vassal had vassals of their own, call
            // function total_net_tax on them to get their tax amount.
            // the function returns 90% of their total income, so we
            // need to convert that back, and add a portion of that
            // to taxes.
            int tax = total_net_tax(vassal)/0.9;
            int tax_to_pay = 0.1*tax;
            taxes = taxes + tax_to_pay;
        }
    }
    // return either 90% or 100% of the collected taxes according to
    // whether the town had a master.
    if (towns_.at(id).master_ != NO_TOWNID){
        int tax_to_pay = taxes*0.1;
        return taxes - tax_to_pay;
    }
    return taxes;
}

//
// Phase 2 operations
//


void Datastructures::clear_roads()
{
    // Replace the line below with your implementation

    all_roads_.clear();
    for(auto &town : towns_){
        town.second.adjacent_towns_.clear();
    }
    return;
}

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    // Replace the line below with your implementation
    return all_roads_;
}

bool Datastructures::add_road(TownID town1, TownID town2)
{

    TownID id_small;
    TownID id_large;

    //check for if the town already exists
    if(!does_town_exist(town2) ||
       !does_town_exist(town1)){
        return false;
    }

    //assigning the variables so the smaller goes to id_small and vice versa
    if(town1 < town2){
        id_small = town1;
        id_large = town2;
    }
    else{
        id_small = town2;
        id_large = town1;
    }

    // check for if the road already exist
    std::pair<TownID,TownID> item = {id_small,id_large};
    if(std::find(all_roads_.begin(), all_roads_.end(), item)!=all_roads_.end()){
          return false;
    }


    Town* smaller_town = &towns_.find(id_small)->second;
    Town* larger_town = &towns_.find(id_large)->second;

    // adding the towns to each others neighboring towns
    smaller_town->adjacent_towns_.push_back(larger_town);
    larger_town->adjacent_towns_.push_back(smaller_town);

    // adding the road to all_roads_ vector
    all_roads_.push_back({id_small,id_large});

    return true;
}

std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )

    std::vector<TownID> roads_from;
    auto town = towns_.find(id);
    if(town == towns_.end()){
        roads_from.push_back(NO_TOWNID);
        return roads_from;
    }

    // the adjacent towns are stored with pointers so
    // we need to fetch the ID_'s for a new vector
    for(auto town : town->second.adjacent_towns_){
        roads_from.push_back(town->ID_);
    }
    return roads_from;
}

// uses the breadth_first_search algorithm, after the algorithm goes through the pointers
// to gather the route from the destination to the beginning
std::vector<TownID> Datastructures::breadth_first_search(Town* fromtown, Town* totown){

    std::deque<Town*> Q;
    std::vector<TownID> short_route;
    bool route_found = false;

    fromtown->color_ = "gray";
    Q.push_back(fromtown);

    while(Q.size() != 0){
        auto u = Q.at(0);
        Q.pop_front();
        for(auto v : u->adjacent_towns_){

            if(v == totown){
                route_found = true;
            }

            if(v->color_ == "white"){
                v->color_ = "gray";
                v->pi_ = u;
                Q.push_back(v);
            }
        }
        u->color_ = "black";
    }

    if(!route_found){
        return short_route;
    }

    // after the algorithm has found the optimal route, we can
    // trace the route from the destination to the beginning
    Town* current_town = totown;
    while(current_town != fromtown){

        short_route.insert(short_route.begin(),current_town->ID_);
        Town* tmp = current_town->pi_;

        current_town = tmp;
    }

    // the starting town isn't added in the loop so we need to add it after
    if(short_route.size() != 0){
        short_route.insert(short_route.begin(),current_town->ID_);
    }

    return short_route;
}

std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )

    std::vector<TownID> any_route;

    //checking if towns exist
    if(!does_town_exist(fromid) ||
       !does_town_exist(toid)){
        any_route.push_back(NO_TOWNID);
        return any_route;
    }

    // assinging towns to pointers
    auto fromtown = &towns_.find(fromid)->second;
    auto totown = &towns_.find(toid)->second;

    // Resetting all town "colors" and route pointers.
    for (auto &town : towns_){
        town.second.color_ = "white";
        town.second.pi_ = nullptr;
    }
    // calling the algorithm and returning the result
    any_route = breadth_first_search(fromtown, totown);
    return any_route;
}

bool Datastructures::remove_road(TownID town1, TownID town2)
{

    // check for if the town exists
    if(!does_town_exist(town1) ||
       !does_town_exist(town2)){
        return false;
    }

    // assigning the towns to pointers (Town*)
    auto town1p = &towns_.find(town1)->second;
    auto town2p = &towns_.find(town2)->second;

    // erasing the connection for the first town.
    for(unsigned long int i=0; i<town1p->adjacent_towns_.size();i++){
        if(town1p->adjacent_towns_.at(i)->ID_ == town2){
            town1p->adjacent_towns_.erase(town1p->adjacent_towns_.begin() + i);
            break;
        }
    }
    // erasing the connection for the other town
    for(unsigned long int i=0; i<town2p->adjacent_towns_.size();i++){
        if(town2p->adjacent_towns_.at(i)->ID_ == town1){
            town2p->adjacent_towns_.erase(town2p->adjacent_towns_.begin() + i);
            break;
        }
    }

    // going through the vector with all roads in it, and deleting
    // the one with both towns connecting them. The if check is
    // made so the towns can be inserted in either order.
    for(unsigned long int i=0; i<all_roads_.size();i++){
        if((all_roads_.at(i).first == town1 &&
            all_roads_.at(i).second == town2) ||
           (all_roads_.at(i).first == town2 &&
            all_roads_.at(i).second == town1)){

            // removing the road from the vector
            all_roads_.erase(all_roads_.begin() + i);
            break;
        }
    }

    return true;
}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{

    std::vector<TownID> short_route;

    //checking if towns exist
    if(!does_town_exist(fromid) ||
       !does_town_exist(toid)){
        short_route.push_back(NO_TOWNID);
        return short_route;
    }

    // assigning towns to pointers (Town*)
    auto fromtown = &towns_.find(fromid)->second;
    auto totown = &towns_.find(toid)->second;

    // going through towns and resetting their "color" and route pointer
    for (auto &town : towns_){
        town.second.color_ = "white";
        town.second.pi_ = nullptr;
    }
    short_route = breadth_first_search(fromtown, totown);
    return short_route;
}

// uses a modified version of breadth_first_search algorithm, after the algorithm
// goes through the towns from the loop point back to the starting town.
std::vector<TownID> Datastructures::depth_first_search(Town* fromtown){

    std::vector<Town*> Q;
    std::vector<TownID> route;
    bool cycle_found = false;
    Q.push_back(fromtown);
    Town* previous_town = fromtown;
    Town* last_town = nullptr;

    while(Q.size() != 0){
        auto u = Q.at(Q.size()-1);
        previous_town = u;
        Q.pop_back();
        for(auto v : u->adjacent_towns_){
            if(v->color_ == "white"){
                v->color_ = "gray";
                v->pi_ = u;
                Q.push_back(v);
            }
            else{
                if(previous_town == v->pi_){
                    continue;
                }
                if(v->color_ == "gray"){
                    cycle_found = true;
                    last_town = v;
                    v->pi_ = u;
                    for(auto last : v->adjacent_towns_){
                        if(last->color_ == "black"){
                            route.insert(route.begin(),last->ID_);
                            break;
                        }
                    }
                    Q.clear();
                    break;
                }
            }
        }
        u->color_ = "black";
    }

    if(cycle_found){
        auto current_town = last_town;
        while(current_town->pi_ != nullptr){

            route.insert(route.begin(),current_town->ID_);
            Town* tmp = current_town->pi_;

            current_town = tmp;
        }
        route.insert(route.begin(),fromtown->ID_);
    }
    return route;

}

void  Datastructures::Relax(Town* u, Town* v){

    Distance cost = calculate_distance(u->coord_,v->coord_);
    if(v->dist_ > u->dist_ + cost){
        v->dist_ = (u->dist_ + cost);
        v->pi_ = u;
    }

    return;
}

// uses the Dijkstra algorithm to route the shortest route to the town.
// After that it goes through the route and adds it to a vector that
// gets returned.
std::vector<TownID> Datastructures::dijkstra(Town* fromtown, Town* totown){

    // necessary things for the algorithm
    std::priority_queue<std::pair<int,Town*>> Q;
    std::vector<TownID> route;
    bool route_found = false;
    fromtown->color_ = "gray";
    Distance current_dist = 0;
    fromtown->dist_ = current_dist;
    Q.push({current_dist,fromtown});

    // the Dijkstra algorithm
    while(Q.size() != 0){
        Town* u = Q.top().second;
        Q.pop();
        std::cout << u->ID_ << std::endl;

        for(auto v : u->adjacent_towns_){
            Relax(u,v);
            if(v == totown){
                route_found = true;
                Q = std::priority_queue<std::pair<int,Town*>>();
                break;
            }
            if(v->color_ == "white"){
                v->color_ = "gray";
                Q.push({v->dist_*(-1),v});
            }
            else{
                if(u->pi_ != v){
                    Q.push({v->dist_*(-1),v});
                }

            }
        }
        u->color_ = "black";
    }

    // if route wasnt found, returns empty vector
    if(!route_found){
        return route;
    }

    // goes through the route in reverse order and adds the towns to a vector
    Town* current_town = totown;
    while(current_town != fromtown){
        std::cout << current_town->ID_ << std::endl;
        route.insert(route.begin(),current_town->ID_);
        Town* tmp = current_town->pi_;

        current_town = tmp;
    }

    // the starting town need to be added separately since the loop
    // stops before getting to it
    if(route.size() != 0){
        route.insert(route.begin(),current_town->ID_);
    }
    return route;
}

std::vector<TownID> Datastructures::road_cycle_route(TownID startid)
{

    std::vector<TownID> cycle_route;

    // checks if a town can be found
    auto fromtown = &towns_.find(startid)->second;

    // returns a vector with NO_TOWNID if town wasnt found
    if(!does_town_exist(startid)){
        cycle_route.push_back(NO_TOWNID);
        return cycle_route;
    }

    // goes through all the towns and resets their "color" and route pointer
    for (auto &town : towns_){
        town.second.color_ = "white";
        town.second.pi_ = nullptr;
    }

    // calls the algorithm which is actually a modified breadth_first search to
    // find loops. If loop is found returns the route in a vector.
    cycle_route = depth_first_search(fromtown);
    return cycle_route;
}

std::vector<TownID> Datastructures::shortest_route(TownID fromid, TownID toid)
{

    std::vector<TownID> short_route;

    // check if the town exists
    if(!does_town_exist(fromid) ||
       !does_town_exist(toid)){
        short_route.push_back(NO_TOWNID);
        return short_route;
    }

    // assign the towns to pointers
    auto fromtown = &towns_.find(fromid)->second;
    auto totown = &towns_.find(toid)->second;

    // Resets the town values needed for the algorithm to work right
    for (auto &town : towns_){
        town.second.color_ = "white";
        town.second.pi_ = nullptr;
        town.second.dist_ = INFINITY;
    }

    //calls the algorithm that returns a vector for the shortest route
    short_route = dijkstra(fromtown, totown);
    return short_route;
}

Distance Datastructures::trim_road_network()
{
    // Replace the line below with your implementation
    throw NotImplemented("trim_road_network()");
}
