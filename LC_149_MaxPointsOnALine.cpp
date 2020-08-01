// Done Aug 1 2020
// Solves LeetCode 149, Max Point On a Line
// https://leetcode.com/problems/max-points-on-a-line/
// Difficulty: Hard, success rate 16.9%
// Given a list of points (a,b) on the plane,
// consider all the possible lines that run through two of those points,
// and for the line which runs through the greatest number of points,
// return the number of points on that line.

// This one wasn't really hard, other than my solution isn't too efficient.

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        // Unfortunately pretty inefficient, since it makes multiple loops.
        int plen=points.size();
        if (plen==0) { return 0; }
        if (plen==1) { return 1; }
        // Use a tuple to represent the equation of a line in standard form,
        // a*x + b*y = c.
        // This form can represent any line, and a, b, and c can be stored
        // as long rather than float or double, which avoids any rounding issues.
        std::map<tuple<long,long,long>, int> themap2;
        
        // For each pair of points put a, b, and c of equation of standard line
        // into a tuple in the map. 
        for (int ii=0; ii<plen; ii++) {
            vector<int> p1 = points[ii];
            for (int jj=ii+1; jj<plen; jj++) {
                vector<int> p2 = points[jj];
                // These variables actually mean a different thing.
                // Take the two points to be (a,b) and (c,d). So not same
                // as a, b, and c from the equation a*x+b*y=c.
                long a = p1[0];
                long b = p1[1];
                long c = p2[0];
                long d = p2[1];
                // If the two points aren't the same, don't put any 
                // equation into the map.
                // Put the value of each key to be zero.
                if (b-d!=0||c-a!=0||b*c-a*d!=0) {  
                    themap2[{b-d,c-a,b*c-a*d}]=0;
                }
            }
        }

        // Special case: if all points are the same, return number of points.
        if ( themap2.begin()==themap2.end() ) { return plen; }

        // Loop through the map and all points. If the point
        // satisfies the equation of the map, add one to the
        // value associated with that tuple.
        std::map<tuple<long,long,long>, int>::iterator it2;
        for (int ii=0; ii<plen; ii++) {
            vector<int> p = points[ii];
            it2 = themap2.begin();
            while (it2 != themap2.end()) {
                long a = std::get<0>(it2->first);
                long b = std::get<1>(it2->first);
                long c = std::get<2>(it2->first);
                if (a*p[0]+b*p[1]==c && (a!=0||b!=0||c!=0)) {it2->second+=1;}
                it2++;
            }
        }    

        // Loop through map and find and return the max number.
        int maxline2=-1;
        it2 = themap2.begin();
        while (it2 != themap2.end()) {
            if (it2->second > maxline2) { 
                maxline2 = it2->second;
            }
            it2++;
        }
        return maxline2;
    }
};


