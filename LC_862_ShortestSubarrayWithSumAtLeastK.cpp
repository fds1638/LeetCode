// done 24 Oct 2020
// solves Leet Code 862, Shortest Subarray With Sum At Least K
// https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
// difficulty: Hard

// Idea is that if have found one subarray, any shorter subarray won't have a left end to its left.
// Also, if have a negative number given, no need to check further left numbers unless they have a lower accumulation.

class Solution {
public:
    int shortestSubarray(vector<int>& A, int K) {
        // Keep track of the accumulated sum of A as you go along, in vector accum.
        // Keep a list of previous indices that need to be checked, in vector checks.
        // If find a subarray w/ sum >= K, can eliminate all checks before the beginning
        // of that subarray.
        // If new element of A is negative, can eliminate all checks before it that are
        // greater than it.
        int alen = A.size();
        if (alen==0) {return -1;}   // low-hanging fruit
        if (alen==1) {if (A[0]>=K) { return 1;} else {return -1;}}
        deque<int> checks;          // store indices that need to be checked, is left index of subarray
        std::vector<int> accum(alen+1, 0);  // accumulation of A, also right index of subarray being checked
        accum[0]=0;
        checks.push_back(0);
        int retval = INT_MAX;               // initialization
        for (int ii=0; ii<alen; ii++) {
            accum[ii+1]=accum[ii]+A[ii];    // accumulate next value
            while (checks.size()>0&&accum[ii+1]<accum[checks.back()]) {
                checks.pop_back();          // if negative value, can eliminate all checks of greater value
            }
            checks.push_back(ii+1);         // store current value
            int maxjj=-1;                   // initialization
            if (accum[ii+1]-accum[checks[0]]>=K) {  // binary search for furthest right index in checks...
                int lo = 0;                         // ...which gives subarray of sum >=K for this value of ii
                int hi = checks.size()-1;
                while (hi-lo>1) {
                    maxjj = (hi+lo)/2;
                    if (accum[ii+1]-accum[checks[maxjj]]>=K) { 
                        lo = maxjj; 
                    }
                    else {hi = maxjj;}
                }
                maxjj=lo;                           // now that have the furthest right index, see if new minimum
                if (ii-checks[maxjj]<retval) {
                    retval = ii-checks[maxjj]+1;
                    if (retval==1) {return 1;}
                }
            }

            int frontpopcount = 0;                  // eliminate all checks before the furthest right index
            while (frontpopcount<maxjj){
                checks.pop_front();
                frontpopcount++;
            }
        }
        if (retval==INT_MAX) {return -1;}           // if no subarray exists, return -1
        return retval;
    }
};

