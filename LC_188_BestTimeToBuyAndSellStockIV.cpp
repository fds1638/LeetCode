// Done August 16 2020
// Solves Leet Code 188, Best Time To Buy And Sell Stock IV
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
// Difficulty: Hard, success rate 28.0%

// I quasi-cheated on this one, because when finishing problem 123,
// Best Time To Buy And Sell Stock III, I looked at others' solutions,
// and found one that would obviously generalize better than mine. So
// the generalization below is my code generalizing that idea to k>=3,
// with the explanation of why it works. It is relatively slow (bottom
// quartile) and right in the middle on memory usage.

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int plen = prices.size();
        if (plen<=1||k==0) {return 0;} // quick check
        if (k>plen/2) { k=plen/2; } // don't need more buy/sell opportunities than this
        // dp[ii][0] is money you have after buy number ii
        // dp[ii][1] is money you have after sale number ii
        int dp[k][2];    
        // initialize
        for (int kk=0; kk<k; kk++) {
            dp[kk][0]=INT_MIN;
            dp[kk][1]=0;
        }
        // At each step ii, the dp entries have the following meanings:
        // dp[0][0]: money you have if you had executed first buy by now
        // dp[0][1]: money you have if you had executed first sale by now
        // dp[1][0]: money you have if you had executed second buy by now
        // dp[1][1]: money you have if you had executed second sale by now
        // etc.
        // The trick is that dp[1][1] won't update unless it's actually beneficial
        // to buy and sell twice; otherwise dp[1][1] will be the same as dp[0][1].
        // Similarly, dp[2][1] won't update unless it's actually beneficieal
        // to buy and sell three times, otherwise dp[2][1] will be the same as
        // dp[1][1] and possible dp[0][1]. Etc.
        for(int ii=0;ii<plen;ii++) {
            for (int kk=0; kk<k; kk++) {
                if (kk==0) { dp[kk][0]=max(dp[kk][0],-prices[ii]); }
                else { dp[kk][0]=max(dp[kk][0],dp[kk-1][1]-prices[ii]); }
                dp[kk][1]=max(dp[kk][1],dp[kk][0]+prices[ii]);
            }
        }
        return dp[k-1][1];
    }
};


