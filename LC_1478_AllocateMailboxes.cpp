// Done August 9 2020
// Solves Leet Code 1478, Allocate Mailboxes
// https://leetcode.com/problems/allocate-mailboxes/
// Difficulty: Hard, success rate 54.9%

// Given houses on a number line and a number of mailboxes,
// arrange the mailboxes so that the total distance from a
// house to its nearest mailbox is minimized.

// Essentially, the idea is to break down the vector of house
// locations into k subvectors, where the mailbox for each subvector
// is the median of that subvector. Find the subvector breakdown
// that minimizes the total distance.

// My solution was pretty slow ( right around bottom quartile),
// but top ten percent when it comes to memory usage.

class Solution {
public:
    int minDistance(vector<int>& houses, int k) {
        int hlen = houses.size();
        int dp[k][hlen];
        // Sort the locations of the houses and find gaps between them.
        sort(houses.begin(), houses.end());
        // gaps is just a helper vector to speed calculation.
        // Intuition behind use of gaps:
        // if you have a set of houses for which you have 1 mailbox, and you
        // know the total of the distances to that mailbox, and now you add a new
        // house to the end of the row of houses: you can easily find the new total
        // of distances by basically adding half of the gaps.
        vector<int> gaps;
        for (int ii=0; ii<hlen-1; ii++) {gaps.push_back(houses[ii+1]-houses[ii]);}
        
        // First column of dynamic programming table.
        for (int kk=0; kk<k; kk++) { dp[kk][0]=0; }

        // Second column and onward.
        for (int hh=1; hh<hlen; hh++) {
            for (int kk=0; kk<k; kk++) { 
                // If have as many houses as mailboxes, total distance is zero.
                if (kk+1>=hh+1) { dp[kk][hh]=0; }
                // Else, if have 1 house
                else if (kk==0) {
                    int cursum=0;
                    // Could have used gaps here but wrote this before writing gaps vector.
                    for (int cc=0; cc<=(hh-1)/2; cc++) {cursum+=houses[hh-cc]-houses[cc];}
                    dp[kk][hh]=cursum;
                }
                else {
                    int curmin = INT_MAX;
                    int curlast = 0;
                    for (int stepback=0; stepback<hh-kk+1; stepback++) {
                        // Key insight that makes dp work:
                        // when calculating a new column for adding a new house, only need
                        // to consider that new house having its mailbox to itself, sharing
                        // with one other house, sharing with two others, etc. All other
                        // optimizations will have been already done. So are just looking
                        // in the row above of the dp matrix, and moving to the left.
                        curlast += accumulate(gaps.begin()+hh-stepback, gaps.begin()+hh-stepback/2, 0);
                        if (dp[kk-1][hh-1-stepback]+curlast<curmin) {curmin=dp[kk-1][hh-1-stepback]+curlast;}
                    }
                    dp[kk][hh]=curmin;
                }
            }
        }

        return dp[k-1][hlen-1];
    }
};


