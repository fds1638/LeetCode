// Done 3 sep 2020
// Solves Leet Code 1092, Shortest Common Supersequence
// https://leetcode.com/problems/shortest-common-supersequence/

// Difficulty: Hard

// After finding the shortest common subsequence, just print out
// all the letters in both strings before the first match, print out
// the matching letter, then repeat.

// This is pretty fast, in the top 3 percent speedwise. Upper half
// in memory usage (ie less memory usage than half the entries).

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        string s1=str1, s2=str2;
        vector<stack<tuple<char,int,int>>> woah;
        vector<char> longestsub;
        vector<vector<int>> idx;
        if (s1.size()==0||s2.size()==0) { return 0; }
        
        // find max subsequence using dp
        // dp gives number of letters, then use reverse to back
        // up and get the actual letters (or one possible set of letters)
        int dp[s1.size()+1][s2.size()+1];
        for (int ii=0; ii<s1.size()+1; ii++) { dp[ii][0]=0; }
        for (int jj=0; jj<s2.size()+1; jj++) { dp[0][jj]=0; }
        for (int ii=0; ii<s1.size(); ii++) { 
            for (int jj=0; jj<s2.size(); jj++) {
                if (s1[ii]==s2[jj]){
                    //dp[ii][jj]=1+min(dp[ii-1][jj], dp[ii][jj-1]);
                    dp[ii+1][jj+1]=1+dp[ii][jj];
                } else {
                    dp[ii+1][jj+1]=max(dp[ii][jj+1], dp[ii+1][jj]);
                }
            }
        }
        
        //print dp
        /*
        for (int ii=0; ii<s1.size()+1; ii++) {
            for (int jj=0; jj<s2.size()+1; jj++) {
                std::cout<<dp[ii][jj]<<" ";
            }
            std::cout<<endl;
        }    
        */
        
        // reverse finds the letters of a maximal subsequence by backtracking
        // through the "corners" in the values of dp
        stack<pair<int,int>> reverse;
        int revi = s1.size(), revj = s2.size();
        while ((revi>0||revj>0)&&dp[revi][revj]>0) {
            if (dp[revi-1][revj]==dp[revi][revj-1]
                &&dp[revi-1][revj-1]==dp[revi][revj]-1
                &&dp[revi-1][revj]==dp[revi][revj]-1) { 
                reverse.push({revi-1,revj-1}); revi--; revj--;}
            else {
                if ( dp[revi-1][revj]>dp[revi][revj-1] ) { revi--; }
                else { revj--; }
            }
        }
        
        // now print out minimum superstring
        // print out all values of s1 before first shared letter, 
        // and all values of s2 before first shared letter,
        // then print out first shared letter. Etc.
        // At end print out remaining letters in s1 and s2 after last matching letter.
        string retval="";
        int iidx = 0;
        int jjdx = 0;
        while (reverse.size()>0) {
            int nexti = reverse.top().first;
            int nextj = reverse.top().second;
            while (iidx<nexti) {
                retval += s1[iidx];
                iidx++;
            }
            while (jjdx<nextj) {
                retval += s2[jjdx];
                jjdx++;
            }
            retval += s1[nexti];
            iidx++;
            jjdx++;
            reverse.pop();
        }
            while (iidx<s1.size()) {
                retval += s1[iidx];
                iidx++;
            }
            while (jjdx<s2.size()) {
                retval += s2[jjdx];
                jjdx++;
            }
            
        //std::cout<<"retval "<<retval<<endl;
        return retval;
    }
};


