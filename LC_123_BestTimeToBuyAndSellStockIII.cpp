// Done August 14 2020
// Solves LeetCode 123, Best Time To Buy And Sell Stock III
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
// Difficulty: Hard, success rate 37.5%

// This is a more complicated version of the usual best time to buy and sell
// stock question. This time you can buy and sell twice, but have to sell first
// position before buy second position.

// Basically use the same idea as in the usual simpler problem, but have one
// optimization run forward in time and the other backwards in time. Store the
// values in an array, which you can do with only one dimension if you keep track
// of when you're halfway and so can add to existing stored value that was 
// computed "going the other way."

// This solution is pretty efficient, at about the 98th percentile in speed (only
// pass through array once) and top quartile in optimizing for space.

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.size()<=1) {return 0;}
        int plen = prices.size();
        // variables for processing optima from the left
        int minsofar = prices[0];
        int lretval = 0;
        // variables for processing optima from the right
        int maxsofar = prices[plen-1];
        int rretval = 0;
        // array for storing subvector optima
        int dp[plen];
        // return value
        int maxprof = 0;
        
        for (int pp=0; pp<plen; pp++) {
            // Get best buy/sell for subvector starting at left end.
            if (lretval<prices[pp]-minsofar) {lretval=prices[pp]-minsofar;}
            if (prices[pp]<minsofar) { minsofar=prices[pp]; }
            // Get best buy/sell for subvector starting at right end.
            if (rretval<maxsofar-prices[plen-1-pp]) {rretval=maxsofar-prices[plen-1-pp];}
            if (prices[plen-1-pp]>maxsofar) { maxsofar=prices[plen-1-pp]; }
            // Store the two values so can add them later.
            // If pp is before halfway, store the value.
            if (pp<=plen/2-1) {
                dp[pp] = lretval;
                dp[plen-1-pp] = rretval;
            }
            // If odd number of days and exactly halfway, add the two values.
            else if (plen%2!=0&&pp==(plen-1)/2) { 
                dp[pp]=lretval+rretval;  
                maxprof = max(maxprof,dp[pp]);
            } 
            // If pp is more than halfway, can add to already stored values
            // and compute max as you go.
            else {
                dp[pp] += lretval;
                dp[plen-1-pp] += rretval;
                maxprof = max ( max(maxprof, dp[pp]), dp[plen-1-pp]);
            }
        }
        return maxprof;
    }
};


