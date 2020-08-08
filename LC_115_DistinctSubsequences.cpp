// Done August 8 2020
// Solves Leet Code 115, Distinct Subsequences
// Difficulty: Hard, success rate 38.2%
// https://leetcode.com/problems/distinct-subsequences/submissions/
// This one I found pretty easy. Given two strings,
// find how many ways the shorter can be created from
// the longer by dropping (but not rearranging) letters.
// The solution comes from a straightforward dp table.
// My solution is in the top quarter in both time and memory.

class Solution {
public:
    int numDistinct(string s, string t) {
        int slen = s.size();
        int tlen = t.size();
        // Take care of base case quickly.
        if (slen==0) {return 0;}
        // Dynamic programming table has s along top and
        // t along side. 
        long table[tlen][slen];
        
        // First column (i.e. first letter of s): 
        // if the first letter of t matches the first
        // letter of s, it gets a 1. Everything else is a zero because
        // second or later letters of t can't match first letter of s.
        if (s[0]==t[0]) { table[0][0]=1; } else {table[0][0]=0;}
        for (int tt=1; tt<tlen; tt++){table[tt][0]=0;}

        // Afterwards, go letter by letter in s, and for each letter in s
        // count how many ways it can be the corresponding letter in t.
        // Some letters in s can match more than one letter in t.
        for (int ss=1; ss<slen; ss++) {
            // If want this letter in s to be the first letter in t,
            // give it a 1 if it matches.
            if (s[ss]==t[0]) { table[0][ss]=1; } else { table[0][ss]=0; }

            // For this letter in s to be the nth letter in t, need to count
            // how many ways previous letter in s can be the previous letter
            // in t.
            for (int tt=1; tt<tlen; tt++){
                if (s[ss]==t[tt]) { 
                    int sum=0;
                    for (int ii=0; ii<ss; ii++) { sum+= table[tt-1][ii]; }
                    table[tt][ss]=sum; 
                } else {table[tt][ss]=0;}
            }
        }
        
        // Now have the full table. To find the return value, add up the 
        // last row of the table, which will give you the total number of 
        // ways a letter in s can be counted as the final letter in t.
        long retval=0;
        for (int ss=0; ss<slen; ss++) { retval+=table[tlen-1][ss]; }
        
        return retval;
    }
};


