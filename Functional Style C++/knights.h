#ifndef KNIGHTS_H
#define KNIGHTS_H

#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>


using std::pair;
using std::make_pair;
using std::vector;
using std::endl;
using std::cout;
using std::set;

typedef vector<pair<int,int> > Path;

/** Helper function: adds two pairs of ints */
pair<int,int> operator+(const pair<int,int> & a, const pair<int,int> & b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

// TODO - your code goes here

Path moves(const pair<int,int> & pos) {

	vector<pair<int,int> > a{{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

	 auto t = std::transform(a.begin(),a.end(),a.begin(),[pos](pair<int,int> p) {
		return p + pos;

	});

	return a;


}


Path legal_moves(const int & size, const Path & path, const pair<int,int> & pos) {

	if(size < 3) {

		return {};
	}

	Path allMoves = moves(pos);

	Path other;

	copy_if(allMoves.begin(),allMoves.end(),back_inserter(other), [path,size] (const pair<int,int> p) {

		if(p.first >= size || p.first < 0 || p.second >= size || p.second < 0)  {

		} else if (path.begin() == path.end()) {

			return true;

		} else if(std::find(path.begin(), path.end(), p) != path.end()){

		} else {
			return true;
		}

		return false;

	});



	return other;


}




pair<Path,bool> first_tour(const int & size, const Path & path) {

	Path nextPossibleMoves = legal_moves(size, path, path.back());
	Path localPath = path;		

		if(path.size() == size * size) {
				
				return pair<Path,bool>(path, true);
			}

		for(int i = 0; i < nextPossibleMoves.size(); ++i) {

			localPath.push_back(nextPossibleMoves[i]);

			pair<Path,bool> local = first_tour(size,localPath);

			if(local.second == false) {

				localPath.erase(localPath.begin() + localPath.size()-1);

			} else {

				return local;
			}

		}

	return pair<Path,bool>({},false);


}




// Do not edit below this line

#endif
