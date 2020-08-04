// Done August 4 2020
// Solves LeetCode 126, Word Ladder II
// https://leetcode.com/problems/word-ladder-ii/
// Difficulty: Hard, success rate 22.1%
// Given a list of words all of the same length, find the shortest path (ladder)
// from the beginning word to the end word, changing one letter at a time.
// This is a BFS problem, with the difficulty that you must return all of the shortest
// ladders, not just the length of the shortest ladder.
// The difficulty is probably in making it fast enough, the BFS part wasn't too hard.
// I got it working, but not fast enough, so I had to see what others did. 
// The final trick I needed was in setting up the adjacency lists: 
// it is quicker to check all the neighbors of a word (for a five letter word, that is 5*26=130 neighbors)
// than it is to go through possibly thousands of words checking to see if it's a neighbor.

class Solution {
private: int numDiffs (string word1, string word2) {
    //assume word1 and word2 have the same length
    //return number of characters where they differ
    int retval=0;
    for (int ii=0; ii<word1.size(); ii++) { if (word1[ii]!=word2[ii]) retval++;}
    return retval;
}    
    
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        // use s to set up adjacency list
        // got this idea from another user
        unordered_set<string> s(wordList.begin(),wordList.end());
        int numwords = wordList.size();
        vector<vector<string>> retval;  //this holds candidate ladders
        vector<vector<string>> ans;     //gets ladders that are part of answer
        std::unordered_map<string, int> themap; //holds words that have been visited
        std::unordered_map<string, vector<string>> trythis; //holds adjacency lists
                

        int endWordpresent=0; // if endWord not in wordList, return {}
        for (int ii=0; ii<numwords; ii++) {
            if (wordList[ii]==endWord) { endWordpresent=1;}
            themap[wordList[ii]]=3;  // 3 used as default; change to 1 when used
            trythis[wordList[ii]]={};// empty adjacency list
            for (int jj=0; jj<wordList[ii].size(); jj++) {
                // for each word, change each character to one of 26 other possibitilies
                // and see if the result is in s
                // for a five-letter words, you could have thousands of words in the list
                // it's faster to check 5*26=130 possible words for presence in the list
                // rather than to check thousands of words one-by-one and see if they
                // only differ in one character
                for (char kk='a'; kk<='z'; kk++) {
                    string teststring = wordList[ii].substr(0,jj)+kk+wordList[ii].substr(jj+1);
                    if (s.find(teststring)!=s.end() && teststring!=wordList[ii]) {trythis[wordList[ii]].push_back(teststring);}
                }
            }
        }
        // if endWord is in wordList, start the bfs, else return {}
        if (endWordpresent==1) {retval.push_back({beginWord});}
        else {return {};}
        // in case beginWord is not in wordList, create its adjacency list
        if (trythis.count(beginWord)==0) {
            trythis[beginWord]={};
            for (int jj=0; jj<beginWord.size(); jj++) {
                for (char kk='a'; kk<='z'; kk++) {
                    string teststring = beginWord.substr(0,jj)+kk+beginWord.substr(jj+1);
                    if (s.find(teststring)!=s.end() ) {trythis[beginWord].push_back(teststring);}
                }
            }
        }
        themap[beginWord]=1;  //beginWord has been visited
        
        // I shouldn't need both of these, but it's a decent safeguard.
        // newstepmade means that the ladders were extended (i.e. I haven't hit a dead end)
        // stepcount just makes sure I haven't taken more steps than there are numbers
        // on the list. 
        int newstepmade=1;
        int stepcount=0;
        while (newstepmade==1 && themap[endWord]==3 && stepcount < numwords) {
            stepcount++;
            newstepmade=0; //reset to zero for a new step
            int rsize = retval.size();
            vector<vector<string>> stepped={}; //list new ladders created at this distance
            vector<string> used={};    //store newly visited words
            for (int ii=0; ii<rsize; ii++) {
                string lastword = retval[ii][retval[ii].size()-1]; // for each ladder
                // of this length, get the last word to see what next steps might exist
                // and for that last word, cycle through its adjacent words
                for (int jj=0; jj<trythis[lastword].size(); jj++) {
                    if ( themap[trythis[lastword][jj]]>1) { // if adjacent word not visited
                        stepped.push_back(retval[ii]); //put the new ladder in stepped
                        stepped.back().push_back({trythis[lastword][jj]});
                        used.push_back(trythis[lastword][jj]); //note to mark it visited
                        // if have found a ladder that got to endWord, store it to return it
                        if (trythis[lastword][jj]==endWord) {ans.push_back(stepped.back());}
                        newstepmade=1; //mark that we have extended the ladder
                    }
                }
            }
            retval.swap(stepped); //swap is fast, and only new ladders need to be kept
            // note the words that have been newly used
            // must do that here, because two ladders might want to use the same
            // word, and as long as they are of equal length (which they should be in
            // this code), that is ok.
            for (int uu=0; uu<used.size(); uu++) { themap[used[uu]]=1;}
        }    
        return ans;
    }
};

