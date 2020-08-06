// Done August 6 2020
// Solves LeetCode 363, Max Sum of Rectangle No Larger Than K
// https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
// Difficulty: Hard, success rate 37.3%
// This one was efficient, coming in at less space usage than 100% of solutions,
// and time in the upper half of solutions (time seems to vary).

// Basically, a brute force approach, calculate sums of rectangles and 
// then seeing if any subrectangles within it are optimal.

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int curmax = INT_MIN;
        int rows = matrix.size();
        int cols = matrix[0].size();
        int cs[rows][cols];   //cumulative sum matrix, sum from top left corner to here
        // first set up first entry and first row of cumulative sum matrix
        cs[0][0]=matrix[0][0];
        if (cs[0][0]<=k) { curmax = cs[0][0]; }
        // first row
        for (int cc=1; cc<cols; cc++) {
            cs[0][cc]=cs[0][cc-1]+matrix[0][cc]; 
            if (cs[0][cc]<=k && cs[0][cc]>curmax) { curmax = cs[0][cc]; }
            for (int jj=0; jj<cc; jj++) {
                int rectsum = cs[0][cc]-cs[0][jj];
                if (rectsum<=k && rectsum>curmax) { curmax = rectsum;}
            }    
        }
        
        // Now add the rest of the rows, minimizing as we go.
        for (int rr=1; rr<rows; rr++) {
            
            // Set up the cs cumulative sum matrix for this row.
            for (int cc=0; cc<cols; cc++) {
                if (cc==0) {cs[rr][cc]=cs[rr-1][cc]+matrix[rr][cc];}
                else {cs[rr][cc]=cs[rr-1][cc]+cs[rr][cc-1]-cs[rr-1][cc-1]+matrix[rr][cc];}
                // Check if submatrix all the way from top left corner is optimal.
                if (cs[rr][cc]<=k && cs[rr][cc]>curmax) { curmax = cs[rr][cc]; }

            // Now see if there is a submatrix that is optimal.
            // First see if an optimal matrix borders the top of the whole matrix.
            for (int ii=0; ii<rr; ii++) { 
                int rectsum = cs[rr][cc]-cs[ii][cc];
                if (rectsum<=k && rectsum>curmax) { curmax = rectsum;}
            }
            // Then see if an optimal matrix borders the left of the whole matrix.
            for (int jj=0; jj<cc; jj++) {
                int rectsum = cs[rr][cc]-cs[rr][jj];
                if (rectsum<=k && rectsum>curmax) { curmax = rectsum;}
            }
            // Then see if an optimal matrix is in the middle somewhere,
            // with a lower right corner of (rr,cc), having eliminated
            // everything above or to the left of (ii,jj) inclusive.
            for (int ii=0; ii<=rr; ii++) {
            for (int jj=0; jj<=cc; jj++) {
                if (ii<rr||jj<cc){
                    int rectsum = cs[rr][cc]-cs[ii][cc]-cs[rr][jj]+cs[ii][jj];
                    if (rectsum<=k && rectsum>curmax) { curmax = rectsum;}
                }
            }
            }

            }

        }
        return curmax;
    }
};

