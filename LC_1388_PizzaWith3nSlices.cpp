// Done August 8 2020
// Solves LeetCode 1388, Pizza With 3n Slices
// https://leetcode.com/problems/pizza-with-3n-slices/
// Difficulty: Hard, success rate: 44.7%

// I found this one tough, but ended up solving it three different ways.
// However, my first two ways, while correct, weren't fast enough.
// First way (at the bottom): treat it like a minimium distance problem,
// where the "cities" are the states of the problem, with certain values
// used and certain values not yet used, and "distance" is total of 
// numbers chosen so far.
// Second way (in the middle below): recursive, where with each new
// "layer" of three values I maximize using the max's of the subvectors
// having removed the appropriate numbers. Again, it works but takes too
// long. I don't think memoization helps, as I don't think I recompute
// any numbers.
// Third way (on top here): this is a simple dynamic programming table.
// I had to read some other users' comments in order to get the idea,
// but the code is mine. As it happens, it is very efficient, in the 
// top 10% in both time and memory.

class Solution {
public:
    // Function to return max of three numbers.
    int max3 (int a, int b, int c) {
        int maxofthree=max(a,b);
        return max(maxofthree,c);
    }
    
public:
    int maxSizeSlices(vector<int>& slices) {
        
        int slen = slices.size();
        int rows = slen/3+1;
        int cols = slen-1;
        // left considers all but the furthest right entry
        // right considers all but the furthest left entry
        int left[rows][cols];
        int right[rows][cols];
        
        // Take care of some base cases quickly.
        if (slen==0) {return 0;}
        if (slen==3) {return max3(slices[0],slices[1],slices[2]);}
        
        // Process left. We know we are using at most rows number of
        // numbers. The DP table basically says:
        // rows: number of numbers chosen so far
        // cols: how far along the vector we are
        // If want to make current col's number be the first, then
        // the best is the max of all the numbers so far.
        // If want to make current col's number be something after the first,
        // then it is the max of (using current col plus best of two cols earlier)
        // or (use the current number of choices by the previous col).
        for (int rr=0; rr<rows; rr++) {
            if (rr==0) { left[rr][0]=0; left[rr][1]=0; }
            else { left[rr][0]=slices[0]; left[rr][1]=max(slices[0],slices[1]); }
        }
        for (int cc=2; cc<cols; cc++){
            left[0][cc]=0;
            for (int rr=1; rr<rows; rr++) {
                left[rr][cc]=max(left[rr][cc-1],slices[cc]+left[rr-1][cc-2]);
            }
        }
        
        // Process right the same way as processed left.
        for (int rr=0; rr<rows; rr++) {
            if (rr==0) { right[rr][0]=0; right[rr][1]=0; }
            else { right[rr][0]=slices[1]; right[rr][1]=max(slices[1],slices[2]); }
        }
        for (int cc=2; cc<cols; cc++){
            right[0][cc]=0;
            for (int rr=1; rr<rows; rr++) {
                right[rr][cc]=max(right[rr][cc-1],slices[cc+1]+right[rr-1][cc-2]);
            }
        }
        
        // Since can't use both ends of vector, just choose the option
        // the yields the max.
        int retval = max(left[rows-1][cols-1], right[rows-1][cols-1]);
        return retval;
    }
};

//////////////////////////////////////////////////////////////////////////////

class Solution {
public:
    std::map<vector<int>, int> memo;
public:
    int max3 (int a, int b, int c) {
        int maxofthree=max(a,b);
        return max(maxofthree,c);
    }
public:
    int slicemax (vector<int> pie) {
        if (memo.find(pie)!=memo.end()) {return memo[pie];}
        if (pie.size()==3) {
            memo[pie]=max3(pie[0],pie[1],pie[2]);
            return max3(pie[0],pie[1],pie[2]);
        }
        else {
            int ii;
            int maxsum=INT_MIN;
            for (int kk=0; kk<pie.size(); kk++) { 
                vector<int> subvec=pie;
                if (kk>0&&kk<pie.size()-1) { subvec.erase(subvec.begin()+kk-1,subvec.begin()+kk+2);}
                else if (kk==0) {
                    subvec.erase(subvec.begin(), subvec.begin()+2);
                    subvec.erase(subvec.end()-1, subvec.end());
                } else if (kk=pie.size()-1) {
                    subvec.erase(subvec.begin(), subvec.begin()+1);
                    subvec.erase(subvec.end()-2, subvec.end());
                }
                maxsum=max(maxsum,pie[kk]+slicemax(subvec));
            }
            memo[pie]=maxsum;
            return maxsum;
        }
    }
public:
    int maxSizeSlices(vector<int>& slices) {
        int slen = slices.size();
        int retval = slicemax(slices);
        return retval;
    }
};

//////////////////////////////////////////////////////////////////////////////////

class Solution {
public:
    int maxSizeSlices(vector<int>& slices) {
        const int ssize = slices.size();
        const int ssize2 = ssize;
        int retval=INT_MIN;
        int steps = ssize/3;
        std::map<vector<int>,int> states;
        vector<int> tempvec;
        vector<int> finalvector;
        std::map<vector<int>,int>:: iterator states_it;
        int statelength=ssize;

        
        for (int ii=0; ii<ssize; ii++) { tempvec.push_back(ii);finalvector.push_back(0); }
        states[tempvec]=0;
        
        for (int step=0; step<steps; step++) {
        std::map<vector<int>,int> tempstates;
        for (states_it=states.begin(); states_it!=states.end(); states_it++) {
        if (states_it->first.size()==statelength){
            for (int cc=0; cc<states_it->first.size(); cc++) {
                    vector<int> modvec;
                    copy (states_it->first.begin(), states_it->first.end(),  back_inserter(modvec));
                    if (cc>0&&cc<states_it->first.size()-1) {
                        modvec.erase(modvec.begin()+cc-1, modvec.begin()+cc+2);
                    } else if (cc==0) {
                        modvec.erase(modvec.begin(), modvec.begin()+2);
                        modvec.erase(modvec.end()-1);
                    } else if (cc=states_it->first.size()-1) {
                        modvec.erase(modvec.end()-2, modvec.end());
                        modvec.erase(modvec.begin());
                    }
                
                    if (tempstates.find(modvec)==tempstates.end()) {
                        tempstates[modvec]=states_it->second+slices[states_it->first[cc]];
                    }
                    else {
                        if (states_it->second+slices[states_it->first[cc]]>tempstates[modvec]) {
                            tempstates[modvec]=states_it->second+slices[states_it->first[cc]];
                        }
                    }
            }
        }
        }
        states.insert(tempstates.begin(), tempstates.end());
        statelength-=3;
        }
        
        states_it=states.begin();
        return states_it->second;
    }
};


