// Done 24 August 2020
// Solves LeetCode 140, Word Break II
// https://leetcode.com/problems/word-break-ii/
// Difficulty Hard, success rate 32.7%

// Given a string and a list of words in a dictionary,
// return all the ways the string can be made by concatenating
// words in the dictionary.

// I initially solved this using a BFS and a DFS, but while both
// solved everything correctly they weren't fast enough. This solution is
// in the top half of speed and top 5% in avoiding memory usage.

class Solution {
public:
    std::map<string, vector<string>> themap;
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        // The strategy is to take the words in wordDict and find all the places that
        // a word matches a substring of s, putting beginning and ending indices in 
        // wordarray, a two-dim array of integers (row=beginning, col=end of substring
        // match). Then use wordarray to do essentially backtracking (but going forward)
        // because you have a list of all the places a substring match can end if you 
        // are given a substring beginning index.
        vector<string> retval; // return value
        int wlen = wordDict.size();
        int slen = s.size();
        // Initialize wordarray to all zeroes; ones will then be used to indicate
        // that that row and col are the beginning and end indices of a substring match.
        int wordarray[slen][slen];
        for (int ii=0; ii<slen; ii++) {
            for (int jj=0; jj<slen; jj++) { 
                wordarray[ii][jj]=0;
            }
        }
        
        // A time-saver is using begins and covered, which are arrays that slightly duplicate
        // what wordarray does, but allow us to quickly check if it is even feasible for an
        // answer to occur. Basically, if at the end any index is not covered by some substring
        // which matches a dictionary word, no solution is possible.
        int begins[slen];
        int covered[slen];
        vector<pair<int,int>> bes;  // Stores pairs of indices, duplicates wordarray in a sense.
        for (int ii=0; ii<slen; ii++) { begins[ii]=0; covered[ii]=1; }
        for (int ww=0; ww<wlen; ww++) {
            if (wordDict[ww].size()<=slen){
            for (int ii=0; ii<slen-wordDict[ww].size()+1; ii++) {
                if (s.substr(ii,wordDict[ww].size()).compare(wordDict[ww])==0) {
                    wordarray[ii][ii+wordDict[ww].size()-1]=1;
                    if (ii>0) { bes.push_back({ii,ii+wordDict[ww].size()-1});}
                    else { bes.push_back({0,ii+wordDict[ww].size()-1});}
                }
            }
            }
        }
        // Use bes, begins, and covered to check for possibility of a solution.
        sort(bes.begin(), bes.end()); 
        for (int ii=0; ii<bes.size(); ii++) {
            int curbeg = std::get<0>(bes[ii]);
            int curend = std::get<1>(bes[ii]);
            for (int jj=curbeg; jj<=curend; jj++) {covered[jj]=0;} 
            if (curbeg>0) {begins[curbeg-1]=1;}
        }
        // If any index not covered, coveredsum will be greater than zero.
        int coveredsum = 0;
        for (int ii=0; ii<slen; ii++) { 
            coveredsum+=covered[ii];}
        if ( coveredsum>0) { return {}; }
        
        // Now we know a solution exists, so use wordarray to build all possible solutions.
        // As we work through the index jj, we have a list of all strings which end at the current
        // index and are made up of wordDict substrings.
        vector<vector<string>> searches;
        for (int jj=0; jj<slen; jj++) {
            searches.push_back({});
            for (int ii=0; ii<=jj; ii++) { 
                if (wordarray[ii][jj]==1) {
                    if (ii==0) {searches[jj].push_back(s.substr(ii,jj-ii+1));}
                    else {
                        for (int ss=0; ss<searches[ii-1].size(); ss++) {
                            searches[jj].push_back(searches[ii-1][ss]+" "+s.substr(ii,jj-ii+1));
                        }
                    }
                }
            }
        }
        // Return the last entry.
        return searches[slen-1];
    }
};


