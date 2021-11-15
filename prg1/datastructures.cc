// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

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

int Datastructures::calculate_distance(Coord coord1, Coord coord2){

    int x1 = coord1.x;
    int x2 = coord2.x;
    int y1 = coord1.y;
    int y2 = coord2.y;

    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

bool Datastructures::does_town_exist(TownID id){

    if (towns_.find(id) != towns_.end()){
        return true;
    }
    return false;

}

unsigned int Datastructures::town_count()
{
    // Replace the line below with your implementation
    //throw NotImplemented("town_count()");

    return towns_.size();
}

void Datastructures::clear_all()
{
    // Replace the line below with your implementation
    // throw NotImplemented("clear_all()");

    // deleting all  towns
    towns_.clear();

}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("add_town()");
    if (does_town_exist(id)){
        return false;
    }

    Town new_town;
    new_town.name_ = name;
    new_town.coord_ = coord;
    new_town.taxes_ = tax;

    // new_town.dist_to_center_ = calculate_distance(coord,(0,0));

    towns_.insert({id, new_town});


    return true;


}

Name Datastructures::get_town_name(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_name()");
    if (!does_town_exist(id)){
            return NO_NAME;
    }
    return towns_.at(id).name_;
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_coordinates()");

    if (!does_town_exist(id)){
            return NO_COORD;
    }

    return towns_.at(id).coord_;
}

int Datastructures::get_town_tax(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_tax()");

    if (!does_town_exist(id)){
            return NO_VALUE;
    }

    return towns_.at(id).taxes_;

}

std::vector<TownID> Datastructures::all_towns()
{
    // Replace the line below with your implementation
    // throw NotImplemented("all_towns()");
    std::vector<TownID> towns;

    for (auto &town : towns_){
        towns.push_back(town.first);
    }
    return towns;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("find_towns()");

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
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("change_town_name()");

    if (!does_town_exist(id)){
        return false;
    }
    towns_.at(id).name_ = newname;
    return true;

}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Replace the line below with your implementation
    // throw NotImplemented("towns_alphabetically()");

    std::vector<TownID> towns_alphabet;
    towns_alphabet = all_towns();

    std::sort(towns_alphabet.begin(), towns_alphabet.end(),
              [this](auto l,auto r)
    {return towns_.at(l).name_ < towns_.at(r).name_;});
    return towns_alphabet;

}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Replace the line below with your implementation
    // throw NotImplemented("towns_distance_increasing()");

    Coord origo;
    origo.x = 0;
    origo.y = 0;

    std::vector<TownID> towns_distance;
    towns_distance = all_towns();

    std::sort(towns_distance.begin(), towns_distance.end(),
        [&](auto l,auto r){
        return calculate_distance(towns_.at(l).coord_,origo) <
        calculate_distance(towns_.at(r).coord_,origo);});
    return towns_distance;

}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation
    // throw NotImplemented("min_distance()");

    Coord origo;
    origo.x = 0;
    origo.y = 0;

    auto result = min_element(towns_.begin(), towns_.end(),[&](auto l, auto r){
        return calculate_distance(l.second.coord_,origo) <
               calculate_distance(r.second.coord_,origo);});
    return result->first;

}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation
    // throw NotImplemented("max_distance()");

    Coord origo;
    origo.x = 0;
    origo.y = 0;

    auto result = min_element(towns_.begin(), towns_.end(),[&](auto l, auto r){
        return calculate_distance(l.second.coord_,origo) >
               calculate_distance(r.second.coord_,origo);});
    return result->first;

}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("add_vassalship()");

    if (!does_town_exist(vassalid)){
        return false;
    }
    if (!does_town_exist(masterid)){
        return false;
    }

    towns_.at(masterid).vassals_.insert(vassalid);
    towns_.at(vassalid).master_ = masterid;
    return true;

}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_vassals()");
    std::vector<TownID> vassals;
    for (auto& town : towns_.at(id).vassals_){
        vassals.push_back(town);
    }
    return vassals;

}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("taxer_path()");

    std::vector<TownID> taxers;
    taxers.push_back(id);
    TownID tmp = id;
    while(towns_.at(tmp).master_ != NO_TOWNID){
        taxers.push_back(towns_.at(tmp).master_);
        TownID current = towns_.at(tmp).master_;
        tmp = current;
    }
    return taxers;

}

bool Datastructures::remove_town(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("remove_town()");

    //check if town exists
    if(!does_town_exist(id)){
        return false;
    }
    if(towns_.at(id).master_ == NO_TOWNID){

        // If town had vassals, remove master_ from them so a new master
        // can be added for them.
        for(auto& vassal : towns_.at(id).vassals_){
            towns_.at(vassal).master_ = NO_TOWNID;
        }
        towns_.erase(id);
        return true;
    }

    std::cout << "test1" << std::endl;

    towns_.at(towns_.at(id).master_).vassals_.erase(id);

    // go trought the vassals and add them under their new master
    for(auto& vassal : towns_.at(id).vassals_){
        std::cout << "test3b" << std::endl;
        add_vassalship(vassal, towns_.at(id).master_);
    }


    std::cout << "test5" << std::endl;
    towns_.erase(id);
    std::cout << "test6" << std::endl;
    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    //throw NotImplemented("towns_nearest()");

    auto towns_nearest = all_towns();
    sort(towns_nearest.begin(), towns_nearest.end(),[&](auto l, auto r){
        return calculate_distance(towns_.at(l).coord_,coord) <
                calculate_distance(towns_.at(r).coord_,coord);});

    return towns_nearest;

}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("longest_vassal_path()");



}

int Datastructures::total_net_tax(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("total_net_tax()");

    if (!does_town_exist(id)){
        return NO_VALUE;
    }

    int taxes = towns_.at(id).taxes_;

    if (towns_.at(id).master_ == NO_TOWNID &&
        towns_.at(id).vassals_.size() == 0){
        return taxes;
    }

    if (towns_.at(id).master_ != NO_TOWNID &&
        towns_.at(id).vassals_.size() == 0){
        return taxes * 0.9;
    }

    for(auto& vassal : towns_.at(id).vassals_){
        if(towns_.at(vassal).vassals_.size() == 0){
            taxes = taxes + 0.1*towns_.at(vassal).taxes_;
            continue;
        }
        int tax = total_net_tax(vassal)/0.9;
        taxes = taxes + 0.1*tax;
    }


    if (towns_.at(id).master_ != NO_TOWNID){
        return taxes * 0.9;
    }
    return taxes;
}
