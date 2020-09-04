// Done 4 Sep 2020
// Solves LeetCode 85, Maximal Rectangle
// https://leetcode.com/problems/maximal-rectangle/
// Difficulty: Hard

// Given a matrix of 1's and 0's, find the largest rectangle
// that consists of all 1's.

// I treated this like the rectangle in the histogram problem,
// where I computed rectangles for each row of the matrix.
// This is pretty fast, top 20%, but pretty memory-intenstive,
// bottom 20%.

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if ( heights.size() == 0 ) { return 0; }
        
        stack<pair<int, int>> pastheights;
        long maxarea = heights[0];
        pastheights.push({0,heights[0]});
        
        // whenever a new number is lower than the previous,
        // process all the rectangles corresponding to heights
        // it is knocking off the stack
        for (int ii=1; ii<heights.size(); ii++) {
            int curcoord = ii+1;
            int backto = ii;
            while ( pastheights.size()>0 && heights[ii] < pastheights.top().second ) { 
                backto = pastheights.top().first; 
                int backhi = pastheights.top().second;
                long curarea = (ii-backto)*backhi;
                maxarea = max(maxarea, curarea);
                pastheights.pop(); 
                
            }
            
            pastheights.push({backto, heights[ii]});
        }
        // at end, drop down to zero height (end of array), so
        // process all remaining numbers
        while ( pastheights.size()>0 ) { 
            int backto = pastheights.top().first; 
            int backhi = pastheights.top().second;
            long curarea = (heights.size()-backto)*backhi;
            maxarea = max(maxarea, curarea);
            pastheights.pop(); 
        }
            
        
        return maxarea;
    }

public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        vector<vector<int>> histos;
        int retval = 0;
        for (int ii=0; ii<matrix.size(); ii++) {
            histos.push_back({});
            for (int jj=0; jj<matrix[0].size(); jj++) {
                if (ii==0) { histos[ii].push_back(matrix[ii][jj]-48);}
                else {
                    if ( matrix[ii][jj]=='0') {histos[ii].push_back(0);}
                    else { histos[ii].push_back(histos[ii-1][jj]+1); } 
                }
            }
            int currowmax = largestRectangleArea(histos[ii]);
            retval = max(retval, currowmax);
        }
        //for (int ii=0; ii<matrix.size(); ii++) {
        //for (int jj=0; jj<matrix[0].size(); jj++) {
        //    std::cout<<histos[ii][jj]<<" ";
        //}
        //std::cout<<endl;
        //}
        return retval;
    }
};


