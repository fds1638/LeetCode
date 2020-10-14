// done 14 Oct 2020
// solves Leet Code 1345, Jump Game IV
// https://leetcode.com/problems/jump-game-iv/
// difficutly: Hard

// Given an array, you want to go from one end to the other
// in the fewest steps, where you can take a step to either
// neighbor or to any other entry which shares the same value.

// BFS solution.

class Solution {
public:
    int minJumps(vector<int>& arr) {
        if (arr.size()==0) {return 0;}
        if (arr.size()==1) {return 0;}
        // Make a map of indices of arr that have the same value.
        // If an index points to an element of arr which has the 
        // same value on both the left and the right, ignore it.
        map<int,vector<int>> sames;
        for (int ii=0; ii<arr.size(); ii++) {
            if (ii==0) {
                sames[arr[ii]].push_back(ii);
            } else if (ii==arr.size()-1){
                sames[arr[ii]].push_back(ii);
            } else if (arr[ii]!=arr[ii-1]||arr[ii]!=arr[ii+1]) {
                sames[arr[ii]].push_back(ii);
            }
        }
        set<int> visited;       // so as not to re-visit indices
        stack<int> bfs;         // bfs stack
        int steps = 0;          // count number of steps
        bfs.push(0);            // start at zero
        while (!bfs.empty()) {
            stack<int> curlevel;    // get the current level of entries
            curlevel.swap(bfs);
            while (!curlevel.empty()) {
                int now = curlevel.top();
                visited.insert(now);
                curlevel.pop();
                if (now==arr.size()-1) {return steps;} // we have arrived!
                // If haven't arrived, put the two neighbors on the stack.
                // We could actually check to see if the neighbors are of the same value
                // and aren't bordering any indices of a different value. It would be a waste
                // of time to go to a place of the same value which doesn't border a different value.
                // But I didn't implement that because it passes all testcases as-is.
                if (now>0&&visited.find(now-1)==visited.end()) { bfs.push(now-1); }
                if (now<arr.size()-1&&visited.find(now+1)==visited.end()) { bfs.push(now+1);}
                // Go through all relevant indices of the same value.
                for (int ii=0; ii<sames[arr[now]].size(); ii++) {
                    if (sames[arr[now]][ii]!=now&&visited.find(sames[arr[now]][ii])==visited.end()){
                        bfs.push(sames[arr[now]][ii]);
                    }
                }
            }
            steps++;
        }
        return steps;
    }
};


