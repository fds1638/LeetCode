// Done July 31 2020
// Solves LeetCode problem 336, Palindrome Pairs
// https://leetcode.com/problems/palindrome-pairs/
// Difficulty: Hard, success rate 33.6%

// I had to look up the idea of how to solve this. But the code below is mine.
// Once I realized that the big idea was to only loop over the words once but 
// to loop within the word twice, it was straightforward. That change means
// going from O( n^2 * k ) to O( n * k^2 ) where n is the number of words
// (on the order of 10,000) and k is the average length of a word (on the
// order of 20). Previously, I had gotten something that worked, but that
// couldn't finish in the time LeetCode demanded. This still isn't too fast,
// I could re-do many of the things I tried in order to make my code faster
// when I was on the wrong track, but at this point I'll move on to a new problem.

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        std::unordered_map<string, int> themap;
        int wlen = words.size();
        vector<vector<int>> retval;
        
        // Create a map that takes every word in words and maps it to its index.
        for (int ii=0; ii<wlen; ii++ ) {
            themap[words[ii]]=ii;
        }

        // For every word, consider every substring that starts/ends at the beginning
        // or end of the word. E.g. if word is "abcde" consider "a", "ab", etc. as well
        // as "e", "de", etc.
        // For strings starting at beginning of word, if that string is a palindrome, then
        // look for reverse of suffix among other words. Because if prepend reverse of suffix
        // to this word, the combined word will be a palindrome.
        // Do the same thing, mutatis mutandis, for strings starting at the end of the word.
        for (int ii=0; ii<wlen; ii++ ) {
            // Check suffices of strings that start at beginning of word.
            for (int jj=0; jj<=words[ii].size(); jj++) {
                string curword = words[ii].substr(0,jj);
                string suffix = words[ii].substr(jj);
                string revcurword = curword;
                reverse(revcurword.begin(), revcurword.end());
                reverse(suffix.begin(), suffix.end());
                if (curword.compare(revcurword)==0) {
                    if (themap.count(suffix)==1 && themap[suffix]!=ii) { retval.push_back({themap[suffix],ii }); }
                }
            }
            // Check prefices of strings that end at end of word.
            for (int jj=words[ii].size()-1; jj>=0; jj--) {
                string curword = words[ii].substr(jj);
                string prefix = words[ii].substr(0,jj);
                string revcurword = curword;
                reverse(revcurword.begin(), revcurword.end());
                reverse(prefix.begin(), prefix.end());
                if (curword.compare(revcurword)==0) {
                    if (themap.count(prefix)==1 && themap[prefix]!=ii) { retval.push_back({ii,themap[prefix] }); }
                }
            }
        }
        return retval;
    }
};

