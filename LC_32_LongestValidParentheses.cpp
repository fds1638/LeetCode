// Done July 24 2020
// Solves LeetCode problem 32, Longest Valid Parentheses
// https://leetcode.com/problems/longest-valid-parentheses/
// Hard problem, with 28.3% success rate.
// Given a string of ( and ) characters, what is longest streak of well-formed pairs of parentheses?

// I first solved this my own way, which is pretty inefficient. That is first below.
// Then, looking at other solutions, it dawned on me it was fair game to use the C++ stack class, so I used 
// a solution on there as inspiration for writing my own version from memory, which comes second.

// First, my own solution.
// The idea is to go through the string multiple times, first substituting any strings like '()' with the number 2,
// and substituting -1 for a ( and 0 for a ) so that I have all integers (easier to work with).
// Then I keep going through and anytime I have a sequence of the form -1,number,0 I replace that with number+2.
// When I can make no more substitutions, I return the largest number (i.e. longest streak).
 
class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size()==0) { return 0; }
        //int idx=0; // index 
        int curlen=0; // length of current valid parens
        int maxlen=0; // length of max valid parens
        int opens=0;
        int inparens=0;
        vector<int> snew;
        int ii=0;
        while (ii<s.size()) {
            if (ii<s.size()-1) {
                if (s.at(ii)=='(' && s.at(ii+1)==')') { snew.push_back(2); ii++;}   
                else { if (s.at(ii)=='(') snew.push_back(-1); else snew.push_back(0);}
            }
            else {
                if (s.at(ii)=='(') snew.push_back(-1); 
                else if (s.at(ii)==')') snew.push_back(0);                
            }
            ii++;
        }
        for (int jj=0; jj<snew.size(); jj++) {
            std::cout << snew.at(jj) << " ";
        }
        std::cout << endl;
        //std::cout << "inparens " << inparens << " opens " << opens << " curlen " << curlen << " maxlen " << maxlen << endl;   
        int madechange=1;
        vector<int> smod;
        while (madechange==1){
          madechange=0;
          smod.erase(smod.begin(),smod.end());
          int kk=0;
          int snewsize=snew.size();
          while ( kk < snewsize ){
              //std::cout << "kk " << kk << " snew.size() " << snew.size() << endl;
              if (snew.at(kk)>0 && kk<snewsize-1 && snew.at(kk+1)>0) {
                  smod.push_back(snew.at(kk)+snew.at(kk+1));
                  madechange=1;
                  kk++;
              } 
              else if (kk< snewsize-2 && snew.at(kk)==-1 && snew.at(kk+1)>0 && snew.at(kk+2)==0) {
                    smod.push_back(snew.at(kk+1)+2);
                    madechange=1;
                    kk+=2;
                  
              }
              else { 
                  smod.push_back(snew.at(kk)); 
              }
                kk++;
            }
            snew.erase(snew.begin(),snew.end());
            copy(smod.begin(), smod.end(), back_inserter(snew));
        }
        for (int jj=0; jj<snew.size(); jj++) {
            std::cout << snew.at(jj) << " ";
        }
        std:cout << endl;
        maxlen = *max_element(snew.begin(), snew.end());
        if (maxlen>0) { return maxlen; } else { return 0;}
        //return 0;
    }
};


// Here is my other solution, which basically cheated by realizing others used a stack.

class Solution {
public:
    int longestValidParentheses(string s) {
        int ssize = s.size();
        if (ssize==0) { return 0; }
        vector<int> streaks(ssize,0); // vectors of 0s, some of which change to 1s
        stack<int> opens; // stack of indices with opened parens waiting for a closing match
        
        for (int ii=0; ii<streaks.size(); ii++) {
            if (s.at(ii)=='(') { opens.push(ii) ;}  //put open parens on stack
            else {                                  // at a closing bracket
                if ( !opens.empty() ) {             // if have opener to match with
                    streaks[opens.top()]=1;         // streaks of both open and close go...
                    streaks[ii]=1;                  // ... from 0 to 1
                    opens.pop();                    // remove matched open from stack
                }
            }
        
        }
        
        // Now streaks has 0s and 1s, where 1s are matched parentheses.
        // Find the largest streak of 1s.
        int maxstreak=0;   
        int curstreak=0;
        for (int ii=0; ii<streaks.size(); ii++) {
            if ( streaks[ii]==0 ) { curstreak=0; }
            else {
                curstreak++;
                if ( curstreak > maxstreak ) { maxstreak=curstreak; }
            }
        }
        
        return maxstreak;
    }
};

