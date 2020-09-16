// done 16 Sep 2020
// solves Leet Code 980, Unique Paths III
// https://leetcode.com/problems/unique-paths-iii/
// Difficulty: hard

// Count number of unique paths through a 2-d grid,
// given a starting point, an ending point, and some
// grid locations that are obstacles.

// DFS does the trick.

class Solution {
public:
    int numsolns = 0;
    int needlen = 0;
public:
    void dfs (int loc, set<int>& used, vector<vector<int>>& grid) {
        int rr,cc;
        if (loc%grid[0].size()!=0){rr = loc/grid[0].size();} else {rr = loc/grid[0].size()-1;}
        if (loc%grid[0].size()!=0){cc = loc%grid[0].size()-1;} else {cc = grid[0].size()-1;}
        used.insert(loc);
        //cout<<loc<<" ";
        //cout<<loc<<" "<<rr<<" "<<cc<<" "<<grid[0].size()<<endl;
        if (used.size()==needlen) {numsolns++;}
        //check the four directions
        // up
        if (rr>0&&grid[rr-1][cc]!=-1&&(grid[rr-1][cc]!=2||used.size()==needlen-1)&&used.find(loc-grid[0].size())==used.end()) {
        //if (loc==8) cout<<"to here"<<endl;
            dfs(loc-grid[0].size(), used, grid);
        }
        // down
        if (rr<grid.size()-1&&grid[rr+1][cc]!=-1&&(grid[rr+1][cc]!=2||used.size()==needlen-1)&&used.find(loc+grid[0].size())==used.end()) {
            dfs(loc+grid[0].size(), used, grid);
        }
        // left
        if (cc>0&&grid[rr][cc-1]!=-1&&(grid[rr][cc-1]!=2||used.size()==needlen-1)&&used.find(loc-1)==used.end()) {
            dfs(loc-1, used, grid);
        }
        // right
        if (cc<grid[0].size()-1&&grid[rr][cc+1]!=-1&&(grid[rr][cc+1]!=2||used.size()==needlen-1)&&(used.find(loc+1)==used.end())) {
            dfs(loc+1, used, grid);
        }
        //cout<<"* ";
        used.erase(loc);
        return;
    }
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        set<int> used;

        int currow, curcol, start;
        for (int rr=0; rr<grid.size(); rr++) {
            for (int cc=0; cc<grid[0].size(); cc++) {
                if (grid[rr][cc]==1) {
                    currow = rr;
                    curcol = cc;
                    start = cc+1+grid[0].size()*rr;
                }
                if (grid[rr][cc]>=0) { needlen++;}
                //cout<<cc+1+grid[0].size()*rr<<"\t";
            }
            //cout<<endl;
        }
        //cout<<endl;
        
        dfs(start, used, grid);
        
        
        return numsolns;
    }
};

