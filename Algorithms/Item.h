#ifndef ITEM_H
#define ITEM_H

#include<string>
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::vector;
using std::unique;
using std::map;



// TODO: your code goes here

class Item {

public:
    Item(double const &lattitude, double const &longit, string const &idstring, int const &t)
            : lat(lattitude), longitude(longit), id(idstring), time(t) {


    }

    void write(ostringstream &o) {


        o << "{" << lat << "," << " " << longitude << "," << " " << "\"" << id << "\"" << "," << " " << time << "}";

    }


    const int getTime() const {

        return time;

    }


    double distanceTo(Item const &itemA) const {

        int const R = 6373000;
        double const rate = 0.0174533;

        double lon2 = itemA.longitude * rate;
        double lat2 = itemA.lat * rate;

        double lon1 = this->longitude * rate;
        double lat1 = this->lat * rate;


        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = pow((sin(dlat / 2)), 2) + cos(lat1) * cos(lat2) * pow((sin(dlon / 2)), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        double distance = R * c;


        return distance;


    }


private:
    double lat;
    double longitude;
    string id;
    int time;


};


/*

In, Item.h, make another class `MapOfItems`.  You need to define this *after the Item* class.  It needs to have:

- a private member variable that stores a vector of `Item's
- a public function 'addItem' for adding an item to the end of this vector
- a public function 'size()' for returning the size of this vector

        Note that where relevant, these should use `const`.


*/





class MapOfItems {


public:
    void addItem(Item t) {

        items.push_back(t);

    }

    int size() const {
        return items.size();
    }


/*
    for this part of the assignment, you will implement a greedy algorithm that finds an order in which to visit the Items, allowing for a walking speed between them,
    and during the times at which they are available (i.e. from a given number of seconds past the hour, until 15 minutes after).

    It should be in a class function called `getTour`, implemented within the MapOfItems class.  It should take a walking speed as an argument.
    The tour should take no longer than 3600 seconds; that is, the last item you visit, must be visited before 3600.  It should return the tour as a `vector` of `Item`s.

    The algorithm specification is as follows:

            - The tour must finish before time 3600.
    - The tour must start at the Item that is available first, at the time it becomes available.
    For instance, if there are five items on the map, available from times 3,10,14,16,18, the item at time 3 would be visited first, at time 3.
    (That is, the current time is 3.)
    - Then, repeatedly:
    - For each Item *I* that hasn't been visited yet,
    - Calculate the time that it would take to walk from the previous Item visited, to *I* (using the distance between them, and the walking speed).  This
            time, plus the current time, is the time that *I* would be visited -- if we went there next.  This time is denoted *visit(I)*.
    - If *visit(I)* is too late (more than fifteen minutes after the item appears), we can't visit that Item
    - If it's too early (before the time at which the item appears), we would need to wait at *I* until it appeared.
    This is okay. but we would set *visit(I)* to the time at which *I* appears.
    - The next item to visit is then the one with the smallest *visit(I)*: add this to the tour, and set the current time to *visit(I)*..
    - Or, if we are too late for all the remaining Items, the tour has finished.  (Yes, it might not be able to visit all the items.)
    - The function then returns the tour

*/

    vector<Item> getTour(const double walkingSpeed) {


        vector<Item> local = items;

        double smallest = 100000000;
        double smallIndex = 0;

        double visitI = 0;

        double currentTime = local[0].getTime();


        int index = 0;


        vector<Item> tour;


        tour.push_back(local[0]);


        while (currentTime < 3600) {


            smallest = 100000;

            for (int i = 1; i < local.size(); ++i) {


                visitI = (tour.back().distanceTo(local[i]) / walkingSpeed) + currentTime;


                if (currentTime > 3600) { break; }


                if (visitI > local[i].getTime() + 900) {

                    //cant visit that Item
                } else {

                    if (visitI < local[i].getTime()) { visitI = local[i].getTime(); }


                    if (visitI < smallest) {


                        smallest = visitI;
                        smallIndex = i;

                    }

                }

            }


            currentTime = smallest;


            if (smallest < 3600) {
                tour.push_back(local[smallIndex]);


                if (local.size() > 0) {
                    local.erase(local.begin() + smallIndex);
                }
            }


        }


        return tour;

    }


private:
    vector<Item> items;
};


ostringstream &operator<<(ostringstream &o, Item &a) {

    a.write(o);
    return o;
}



// don't write any code below this line

#endif

