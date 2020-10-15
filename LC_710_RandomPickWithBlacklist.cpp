// done 15 Oct 2020
// solves Leet Code 710, Random Pick With Blacklist
// https://leetcode.com/problems/random-pick-with-blacklist/
// difficulty: Hard

// The difficulty with this problem is finding a way that is fast enough to pass
// all the testcases. The program below is in the top 10%. I had to get inspired by
// looking at some comments and hints, but the work below is my own (particularly
// applying the upper_bound to a map, which was the final key I needed).


class Solution {
private:
    map<int,int> oks;
    int count;
public:
    Solution(int N, vector<int>& blacklist) {
        // We know how many values pick() can return,
        // namely count = N - blacklist.size().
        // The idea is to make a map, called oks, which says that:
        // if the number is less that key, add the value to get the return value of pick.
        // For example, if N=4 and the blacklist is [2], then we have three possible
        // return values. The randomizer will give three values, 0, 1, or 2.
        // If it returns a 0, pick returns a 0 (i.e. adds nothing).
        // If it returns a 1 or a 2, pick returns a 2 or a 3, respectively,
        // i.e. adding 1.
        srand (time(NULL));
        sort(blacklist.begin(), blacklist.end());   // sort blacklist
        count=N-blacklist.size();                   // calculate count
        int prev = -1;                              // prev helps tell when we have consecutive blacklisted numbers
        int placed = 0;                             // keeps track of how many numbers we already have oks for
        for (int jj=0; jj<blacklist.size(); jj++) {
            if (blacklist[jj]==prev+1) {
                prev = blacklist[jj];
                continue;
            }
            oks[ blacklist[jj]-prev-1+placed ]=jj;  // if multiple numbers is row are ok, all of them add the same num
            placed += blacklist[jj]-prev-1;
            prev = blacklist[jj];                   // update prev
        }
        // Need to update oks to account for possible numbers after the last blacklisted number.
        if (blacklist.size()>0&&oks.find(count)==oks.end()) {oks[count]=blacklist.size();}
        else if (blacklist.size()==0){oks[count]=0;}
        else if (blacklist[blacklist.size()-1]!=N-1) {oks[count]=count-blacklist.size();}
    }
    
    int pick() {
        if (oks.size()==0) {return 0;}  // if all numbers are blacklisted
        int t = rand()%count;           // we have count possible return values
        map<int,int>::iterator it=oks.upper_bound (t);  // find the map key that is greater than t
        return t+it->second;                            // and add the appropriate amount
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */


