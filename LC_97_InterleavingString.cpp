// Done August 13 2020
// Solves Leet Code problem 97, Interleaving String
// https://leetcode.com/problems/interleaving-string/
// Difficulty: Hard, success rate 31.5%

// This solution is relatively inefficient, in bottom
// quartile in both time and space. But it was accepted.
// The dp table is a map this time, which is slow. I used
// a map in order to store all the possibilities. In contrast
// to many dp's where you only need to keep a max or a min,
// here needed to know if progress was possible. So dp is of
// the form 
// dp(ii,jj,kk) = ( s3[kk]==s1[ii] && dp(ii+1,jj,kk+1) )  || ( s3[kk]==s2[jj] && dp(ii,jj+1,kk+1) )
// Note that ii, jj, kk in the above don't exactly correspond to those
// variables in the code; the above is just a general idea.

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        std::map<vector<int>, int> themap;
        int s1len = s1.size();
        int s2len = s2.size();
        int s3len = s3.size();
        // Preliminary check.
        if (s1len+s2len!=s3len) {return false;}
        // Process first letter to set up map.
        // themap key (kk,ii,jj) means that after processing char kk from s3,
        // have used up ii-1 chars from s1 and jj-1 chars from s2. In other words,
        // ii and jj are the next characters to be used from respective strings.
        if (s3[0]==s1[0]) {themap[{0,1,0}]=1;}
        if (s3[0]==s2[0]) {themap[{0,0,1}]=1;}
        if (s3[0]!=s1[0]&&s3[0]!=s2[0]) { return false; }
        
        // Process the rest of the letters.
        for (int kk=1; kk<s3len; kk++) {
            //If can't match current letter, progress flag will stop and return false.
            int progress=0;
            // For each new letter in s3, see how many ways can add it onto
            // already existing possibilities in themap. 
            for (int pp=0; pp<=kk; pp++) {
                int ii, jj;
                // If are at letter kk now, then at kk-1 must have used
                // pp from s1 and kk-pp from s2.
                if (themap.find({kk-1,pp,kk-pp})!=themap.end()){
                    ii = pp;
                    jj = kk-pp;
                } else { // go to next pp
                    continue;
                }
                // Check if can use next letter in s1.
                if (ii<s1len&&s3[kk]==s1[ii]) {
                    progress=1;
                    themap[{kk,ii+1,jj}]=1;
                }
                // Check if can use next letter in s2.
                if (jj<s2len&&s3[kk]==s2[jj]) {
                    progress=1;
                    themap[{kk,ii,jj+1}]=1;
                }
            }
            if (progress==0) { return false;}
        }
        
        return true;
    }
};


