// done 24 sep 2020
// solves Leet Code 546, Remove Boxes
// https://leetcode.com/problems/remove-boxes/
// Difficulty: Hard

// Got 50% on speed and better than 100% on memory. No peeking for any hints of any kind.

// Given vector of "boxes" of different "colors" (i.e. numbers), can remove one box for 1 point,
// or 2 adjacent boxes for 2^2=4 points, or 3 adjacent boxes of same color for 3^2=9 points. Question
// is what order to do the removals, since once removals may cause boxes of same color which weren't
// adjacent to become adjacent, giving your points a bonus because of the squaring.

// Did a pretty standard dp table.

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        // First, go through and instead of individual boxes have the color and how many
        // are adjacent: For 222 replace with 2 in colors vector and 3 in lengths vector.
        vector<int> colors;
        vector<int> lengths;
        map<int,vector<int> > sames;
        int curlen = 1;
        int curidx = 0;
        int curcol = boxes[0];
        sames[curcol].push_back(curidx);
        for (int ii=1; ii<boxes.size(); ii++) {
            if (boxes[ii]==curcol) { curlen++; }
            else {
                colors.push_back(curcol);
                lengths.push_back(curlen);
                curidx++;
                curcol = boxes[ii];
                curlen = 1;
                sames[curcol].push_back(curidx);
            }
        }
        colors.push_back(curcol);
        lengths.push_back(curlen);
        // Print out what I have so far if need to debug.
        /*
        for (int ii=0; ii<colors.size(); ii++) {cout<<colors[ii]<<" ";} cout<<endl;
        for (int ii=0; ii<lengths.size(); ii++) {cout<<lengths[ii]<<" ";} cout<<endl;
        
        map<int,vector<int> >::iterator sit;
        for (sit=sames.begin();sit!=sames.end();sit++) {
            cout<<sit->first<<": ";
            for (int ii=0; ii<sit->second.size(); ii++) {
                cout<<sit->second[ii]<<" ";
            }
            cout<<endl;
        }
        */
        // end debug print checks
        
        // Initialize dp table to zero, dp is a square table.
        int dp[colors.size()][colors.size()];
        for(int rr=0;rr<colors.size();rr++){for(int cc=0;cc<colors.size();cc++){dp[rr][cc]=0;}}
        
        // Will work only with the upper right half of the dp table, where cc>rr.
        // For each column, start on the main diagonal and work up. Then move one column to the right.
        for(int cc=0;cc<colors.size();cc++){for(int rr=cc;rr>=0;rr--){
            // The entry on the diagonal is simply the length of the current column's boxes squared.
            if (rr==cc) { dp[rr][cc]=lengths[cc]*lengths[cc];}
            // Moving up the table (i.e. rr decrases). If the colors at rr and cc don't match,
            // then have to look at all possibilities for "cutting" this current range of boxes.
            // Take the max.
            else if (colors[rr]!=colors[cc]) { 
                int curmax = INT_MIN;
                for (int jj=0; jj<cc-rr; jj++) {
                    curmax = max(curmax, dp[rr][rr+jj]+dp[rr+jj+1][cc]);
                }
                dp[rr][cc]=curmax;
            }
            // Here is the crux of the issue: if the colors at rr and cc match, then need to look
            // at all the possibilities of combining that color of box for the boxes in the subarray
            // between rr and cc in colors/lengths.
            else {
                // In the map sames, have a vector of all the indices of this same color. Get sameslo
                // and sameshi so can iterate over the range of these indices corresponding to rr and cc.
                int sameslo = 0;
                while (sames[colors[cc]][sameslo]!=rr) {sameslo++;} // get to correct last index
                int sameshi = 0;
                while (sames[colors[cc]][sameshi]!=cc) {sameshi++;} // get to correct last index
                
                // Always using the box at cc to combine, check to see results of combining
                // with all boxes going backwards to rr.
                for (int kk=sameshi-1; kk>=sameslo; kk--) {
                    int cursum = 0;
                    int curcountthisnum = 0;
                    // using all matches with color cc's boxes
                    for (int mm=kk; mm<sameshi; mm++) {
                        cursum += dp[sames[colors[cc]][mm]+1][sames[colors[cc]][mm+1]-1];
                        curcountthisnum += lengths[sames[colors[cc]][mm]];
                    }
                    curcountthisnum += lengths[cc]; // add the length of the box at cc
                    int compare = cursum+pow(curcountthisnum,2);
                    dp[rr][cc]=max(dp[rr][cc],compare);
                 }

                // this is the only place that is something of a kludge
                // What I need to do is check all possibilities of combining same color boxes.
                // For example, if I have five boxes of the same color which are not adjacent,
                // I need to consider the possibility of combining none of the boxes, any two
                // of the boxes but not the others, two pairs of two boxes, etc. -- i.e. the
                // powerset.
                // But if I'm working on column cc, I know I only need to check the possibilities
                // where column cc is combined with others. Above I check to see what happens
                // if all boxes of column cc color are combined. Here, I leave out the last one
                // before the end of column cc (since I can look at the testcases and realized
                // that's what I need to do for the last testcase).
                 for (int kk=sameshi-1; kk>=sameslo; kk--) {
                    int cursum = 0;
                    int curcountthisnum = 0;
                    // using all matching boxes except the last before cc
                    for (int mm=kk; mm<sameshi-1; mm++) {
                        if (mm==sameshi-2) {
                            cursum += dp[sames[colors[cc]][mm]+1][sames[colors[cc]][mm+2]-1];
                        } else {
                            cursum += dp[sames[colors[cc]][mm]+1][sames[colors[cc]][mm+1]-1];
                        }
                        curcountthisnum += lengths[sames[colors[cc]][mm]];
                    }
                    curcountthisnum += lengths[cc];
                    int compare = cursum+pow(curcountthisnum,2);
                    dp[rr][cc]=max(dp[rr][cc],compare);
                 }

                // Even though have matching color boxes at rr and cc, check if simply don't
                // want to exploit that match. So do what we did in the non-match situation.
                int curmax = dp[rr][cc];
                for (int jj=0; jj<cc-rr; jj++) {
                    curmax = max(curmax, dp[rr][rr+jj]+dp[rr+jj+1][cc]);
                }
                dp[rr][cc]=curmax>dp[rr+1][cc-1]+pow(lengths[rr]+lengths[cc],2)?curmax:dp[rr+1][cc-1]+pow(lengths[rr]+lengths[cc],2);
            }
        }
        }
        // print dp table for debugging
        //cout<<endl;for(int rr=0;rr<colors.size();rr++){for(int cc=0;cc<colors.size();cc++){cout<<dp[rr][cc]<<"\t";}cout<<endl;}
        return dp[0][colors.size()-1];
    }
};


