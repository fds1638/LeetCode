// done 15 sep 2020
// solves leet code 197 Dungeon Game
// https://leetcode.com/problems/dungeon-game/
// difficulty: hard

// Key: work backwards. You know how many points knight will lose when
// arrives on the princess's spot. So you know how many points knight
// will need on the previous step. Work backwards from there.

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int dp[dungeon.size()][dungeon[0].size()];
        int fd = dungeon[dungeon.size()-1][dungeon[0].size()-1];
        if (fd<0) {dp[dungeon.size()-1][dungeon[0].size()-1]=-fd+1; }
        else {dp[dungeon.size()-1][dungeon[0].size()-1]=1; }
        
        for (int rr=dungeon.size()-2;rr>=0;rr--) {
            dp[rr][dungeon[0].size()-1]=max(1,dp[rr+1][dungeon[0].size()-1]-dungeon[rr][dungeon[0].size()-1]);
        }
        for (int cc=dungeon[0].size()-2;cc>=0;cc--) {
            dp[dungeon.size()-1][cc]=max(1,dp[dungeon.size()-1][cc+1]-dungeon[dungeon.size()-1][cc]);
        }
        for (int rr=dungeon.size()-2;rr>=0;rr--) {
        for (int cc=dungeon[0].size()-2;cc>=0;cc--) {
            int lowerpath = min(dp[rr+1][cc],dp[rr][cc+1]);
            dp[rr][cc]=max(1,lowerpath-dungeon[rr][cc]);
        }
        }
            
        int retval = dp[0][0];
        return max(retval,1);
    }
};


