// Done July 20 2020
// Solves LeetCode 741 Cherry Pickup, Hard problem
// https://leetcode.com/problems/cherry-pickup/
// Another dynamic programming problem. I needed some help on this but after getting the concept I wrote the code myself.
// I can use more dp practice.

// It boils down to two "players" (for lack of a better word) moving down and left though a checkerboard.
// Some square have cherries (1), otherse don't (0), and others are impassable (-1).
// If it were just one player, finding max path would be easy. But second player made it harder.
// Need 3-dim dp, considering all ways that two players could have arrived at current state after steps numbers of steps.

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        if ( grid.size()==1 ) { return grid[0][0];}
        
        int gridsize=grid.size();
        int step = 0;
        int r1 = 0;
        int r2 = 0;
        int T[2*gridsize-1][gridsize][gridsize];
        T[0][0][0]=grid[0][0];                     //initialize
        for (int step=1; step<=2*gridsize-2; step++) {
            int gridlo = ((step-(gridsize-1))<0)?0:step-(gridsize-1); // implement geometry of board
            int gridlim = (step<=gridsize-1)?step:gridsize-1;         // implement geometry of board
            for (int r1=gridlo; r1<=gridlim; r1++){     // if steps is how many steps have been taken, where can p1 be?
                for (int r2=gridlo; r2<=gridlim; r2++){ // same for p2
                    if ( grid[r1][step-r1]==-1 or grid[r2][step-r2]==-1) { T[step][r1][r2]=-1;}
                    else {
                        int num1, num2, num3, num4;
                        // There's four ways the two paths get to the places they are now.
                        // Last move horizontal for both, vertical for both, or one vert one horiz.
                        if ( r1>0 and r2>0) { num1 = T[step-1][r1-1][r2-1]; } else { num1 = -1; }
                        if ( r1<step and r2>0 ) { num2 = T[step-1][r1][r2-1];} else { num2 = -1;}
                        if ( r2<step and r1>0 ) { num3 = T[step-1][r1-1][r2]; } else { num3 = -1; }
                        if ( r1<step and r2<step) { num4 = T[step-1][r1][r2];} else { num4 = -1;}
                        if ( num1==-1 && num2==-1 && num3==-1 && num4==-1 ) { T[step][r1][r2]=-1;}
                        else { // just like dynamic programming, find max
                            if ( r1==r2 ){
                                T[step][r1][r2]=grid[r1][step-r1]+std::max({num1, num2, num3, num4});
                            }
                            else {
                                T[step][r1][r2]=grid[r1][step-r1]+grid[r2][step-r2]+std::max({num1, num2, num3, num4});
                            }
                        }
                    }
                }
            }
        }
        // if -1 block way then return 0 as problem requires 
        if ( T[2*gridsize-1-1][gridsize-1][gridsize-1]==-1 ) { return 0;}
        
        return T[2*gridsize-1-1][gridsize-1][gridsize-1];
        
    }
};

