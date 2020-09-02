// September 1 2020
// Solves Leet Code 84, Largest Rectangle in Histogram
// 

// A standard problem. I had to modify it in order to be
// fast enough for Leet Code to accept it: process after a new
// height is lower than previous heights, not on every new height.

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
};

