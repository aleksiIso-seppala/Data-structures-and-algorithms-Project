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

int Datastructures::calculate_distance(int x1, int y1, int x2, int y2){

    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
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
    for( std::map<TownID, Town>::iterator
         iter = towns_.begin();
         iter != towns_.end();
         ++iter )
    {
        towns_.erase(iter);
    }
}

bool Datastructures::add_town(TownID id, const Name &name, Coord coord, int tax)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("add_town()");
    if (towns_.find(id) != towns_.end()){
        return false;
    }

    Town new_town;
    new_town.name_ = name;
    new_town.coordinates_ = coord;
    new_town.taxes_ = tax;
    new_town.dist_to_center_ = calculate_distance(coord.x,coord.y,0,0);

    towns_.insert({id, new_town});


    return true;


}

Name Datastructures::get_town_name(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_name()");

    return towns_.at(id).name_;
}

Coord Datastructures::get_town_coordinates(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_coordinates()");

    return towns_.at(id).coordinates_;
}

int Datastructures::get_town_tax(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_tax()");

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

    if (towns_.find(id) == towns_.end()){
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

    std::vector<TownID> towns_distance;
    towns_distance = all_towns();

    std::sort(towns_distance.begin(), towns_distance.end(),
              [this](auto l,auto r)
    {return towns_.at(l).dist_to_center_ < towns_.at(r).dist_to_center_;});
    return towns_distance;

}

TownID Datastructures::min_distance()
{
    // Replace the line below with your implementation
    // throw NotImplemented("min_distance()");

    auto result = min_element(towns_.begin(), towns_.end(),[](auto l, auto r){
        return l.second.dist_to_center_ < r.second.dist_to_center_;});
    return result->first;

}

TownID Datastructures::max_distance()
{
    // Replace the line below with your implementation
    // throw NotImplemented("max_distance()");

    auto result = min_element(towns_.begin(), towns_.end(),[](auto l, auto r){
        return l.second.dist_to_center_ > r.second.dist_to_center_;});
    return result->first;

}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("add_vassalship()");

    if (towns_.find(masterid) == towns_.end()){
        return false;
    }
    if (towns_.find(vassalid) == towns_.end()){
        return false;
    }
    if (towns_.at(vassalid).master_ != NO_TOWNID){
        return false;
    }

    Town master = towns_.at(masterid);
    Town vassal = towns_.at(vassalid);
    master.vassals_.push_back(vassalid);
    vassal.master_ = masterid;
    return true;

}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("get_town_vassals()");

    return towns_.at(id).vassals_;

}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("taxer_path()");

    std::vector<TownID> taxers;

    if (towns_.at(id).master_ == NO_TOWNID){
        return taxers;
    }
    else{
        auto master = towns_.at(id).master_;
        taxers.push_back(master);
        taxers = taxer_path(master);
        return taxers;
    }


}

bool Datastructures::remove_town(TownID id)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    // throw NotImplemented("remove_town()");

    //check if town exists
    if(towns_.find(id) == towns_.end()){
        return false;
    }

    //check if town has vassals or a master
    if(towns_.at(id).vassals_.size() != 0){
        if(towns_.at(id).master_ != NO_TOWNID){

            // remove master_ from vassals so a new master
            // can be added for them.
            for(auto& vassal : towns_.at(id).vassals_){
                towns_.at(vassal).master_ = NO_TOWNID;
            }

            // go trought the vassals and add them under their new master
            for(auto& vassal : towns_.at(id).vassals_){
                add_vassalship(vassal, towns_.at(id).master_);
            }
        }
    }


    towns_.erase(id);
    return true;
}

std::vector<TownID> Datastructures::towns_nearest(Coord /*coord*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("towns_nearest()");

    // std::vector<TownID> towns_nearest = all_towns();

}

std::vector<TownID> Datastructures::longest_vassal_path(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("longest_vassal_path()");
}

int Datastructures::total_net_tax(TownID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("total_net_tax()");
}
