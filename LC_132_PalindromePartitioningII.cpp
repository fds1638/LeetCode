// Done August 10 2020
// Solves Leet Code 132, Palindrome Partitioning II
// https://leetcode.com/problems/palindrome-partitioning-ii/
// Difficulty: Hard, success rate 30.2%
// Problem asks you to partition string into substrings which are palindromes,
// using smallest number of cuts. Return only the number of cuts.

// I used a similar idea to the mailbox problem, in that when processing a new
// letter, I only needed to check palindromes ending in that letter. This time
// I wasn't too efficient, in the lower quartile in both speed and memory.

class Solution {
public:
    int minCut(string s) {
        int slen = s.size();
        if (slen==0) {return 0;}
        if (slen==1) {return 0;}
        // Idea of dynamic programming table is that as you go one letter
        // to the right, only need to check possibilities where a palindrome
        // ending on that new letter gives you an optimal breakdown to that point.
        // For all previous letters, that optimization has been done already.
        int dp[slen]; // dynamic programming table has only one row
        dp[0]=0; //first letter is a palindrome on its own, no cut needed
        for (int ii=1; ii<slen; ii++) {
            // The "default" could be considered to be the number of cuts
            // needed at the previous letter, plus one for the new letter.
            int curmin = 1 + dp[ii-1];  
            // For each new letter processed, get strings forwards and backwards
            // to compare for palindrome.
            string cursub = s.substr(0,ii+1);
            string revsub = cursub;
            reverse(revsub.begin(), revsub.end());
            // Check if whole substring so far is a palindrome; if so zero cuts.
            if (cursub.compare(revsub)==0) { curmin = 0; }
            // Use jj to lop off letters at beginning and check for palindromes in 
            // middle of word ending at new letter ii currently being processed.
            int jj=1;
            while (curmin>1&&jj<ii){ // If have curmin=1, no point in trying to do better.
                cursub = cursub.substr(1,cursub.size()-1);
                revsub = revsub.substr(0,revsub.size()-1);
                if (cursub.compare(revsub)==0) { if (1+dp[jj-1]<curmin) curmin=1+dp[jj-1]; }
                jj++;
            }
            dp[ii]=curmin;
        }
        return dp[slen-1];
    }
};


