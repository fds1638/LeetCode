// done 07 Oct 2020
// solves Leet Code problem 1293, Shortest Path In A Grid With Obstacles Elimination
// https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
// Difficulty: Hard

// Task is to go from top left to bottom right in a grid with obstacles, given the max
// number of obstacles you can eliminate.
// There is a hint to use BFS while keeping track of how many obstacles you had to eliminate up
// to that point, and this is pretty much a straighforward implementation of that.

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        // This is a standard BFS, with the addition that we note how many eliminations
        // we have made in the prior visit to this grid point, and visit if now we are
        // visiting with fewer eliminations.
        // I initially wrote this keeping track of the steps to this grid point as well,
        // but that ended up not being used. I didn't bother to delete steps from the map.
        stack<vector<int> > bfs;
        map<pair<int,int>, pair<int,int> > visited;
        bfs.push({0,0,0,0}); // row, column, eliminated, steps
        visited.insert({{0,0},{0,0}});
        while (!bfs.empty()){
            stack<vector<int> > curlevel;
            curlevel.swap(bfs);
            while (!curlevel.empty()) {
                int rr = curlevel.top()[0]; //row
                int cc = curlevel.top()[1]; //column
                int kk = curlevel.top()[2]; //eliminated
                int ss = curlevel.top()[3]; //steps
                curlevel.pop();
                if ( rr==grid.size()-1 && cc==grid[0].size()-1 ) {return ss;}
                // up
                if (rr>0) {
                    map<pair<int,int>, pair<int,int>>::iterator vischeck = visited.find({rr-1,cc});
                    if (grid[rr-1][cc]==0 && kk<=k && (vischeck==visited.end()||vischeck->second.second>kk )) { 
                        bfs.push({rr-1,cc,kk,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr-1,cc},{ss+1,kk}});
                    }
                    else if (grid[rr-1][cc]==1 && kk<k && (vischeck==visited.end()||vischeck->second.second>kk )) { 
                        bfs.push({rr-1,cc,kk+1,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr-1,cc},{ss+1,kk+1}});
                    }
                }
                // down
                if (rr<grid.size()-1) {
                    map<pair<int,int>, pair<int,int>>::iterator vischeck = visited.find({rr+1,cc});
                    if (grid[rr+1][cc]==0 && kk<=k && (vischeck==visited.end()||vischeck->second.second>kk )) { 
                        bfs.push({rr+1,cc,kk,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr+1,cc},{ss+1,kk}});
                    }
                    else if (grid[rr+1][cc]==1 && kk<k && (vischeck==visited.end()||vischeck->second.second>kk )){ 
                        bfs.push({rr+1,cc,kk+1,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr+1,cc},{ss+1,kk+1}});
                    }
                }
                // left
                if (cc>0) {
                    map<pair<int,int>, pair<int,int>>::iterator vischeck = visited.find({rr,cc-1});
                    if (grid[rr][cc-1]==0 && kk<=k && (vischeck==visited.end()||vischeck->second.second>kk )) { 
                        bfs.push({rr,cc-1,kk,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr,cc-1},{ss+1,kk}});
                    }
                    else if (grid[rr][cc-1]==1 && kk<k && (vischeck==visited.end()||vischeck->second.second>kk )) { 
                        bfs.push({rr,cc-1,kk+1,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr,cc-1},{ss+1,kk+1}});
                    }
                }
                // right
                if (cc<grid[0].size()-1) {
                    map<pair<int,int>, pair<int,int>>::iterator vischeck = visited.find({rr,cc+1});
                    if (grid[rr][cc+1]==0 && kk<=k && (vischeck==visited.end()||vischeck->second.second>kk )) { 
                        bfs.push({rr,cc+1,kk,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr,cc+1},{ss+1,kk}});
                    }
                    else if (grid[rr][cc+1]==1 && kk<k && (vischeck==visited.end()||vischeck->second.second>kk )){ 
                        bfs.push({rr,cc+1,kk+1,ss+1}); 
                        if (vischeck!=visited.end()) {visited.erase(vischeck);}
                        visited.insert({{rr,cc+1},{ss+1,kk+1}});
                    }
                }
            }
        }
        return -1;
    }
};


