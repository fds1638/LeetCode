// Done 3 Sep 2020
// Solves Leet Code 135, Candy
// https://leetcode.com/problems/candy/
// Difficulty: Hard

// The main idea is that as you are going through the
// array:
// if greater than previous rating then need to give one more
// if less than or equal to previous rating then want to give 1

// The issue is that if you have a streak of decreasing numbers,
// you always have to give less than before, but you quickly will
// give negative candies. To avoid this, you have to work back and
// give more candies to previous kids. But how far back do you have 
// to go? This is where leeway comes in: it tells you by how many
// you can increase the candies and how far back you have to go.

// Every time you had a step up, you have infinite leeway -- you could
// always have added one more, and no need to add to any previous kids.
// Same when ratings are equal. Only when you dropped down to 1 on a 
// rating decrease do you have limited leeway.

// This is middle of the road in speed, but very memory efficient. Also
// only pass through the array once.

class Solution {
public:
    int candy(vector<int>& ratings) {
    if (ratings.size()==0) { return 0; }
    if (ratings.size()==1) { return 1; }
    long cursum = 1;
    int last = 1;
    vector<pair<int,int>> leeway;
    leeway.push_back({0,INT_MAX});
    //std::cout<<cursum<<" ";
    for (int ii=1; ii<ratings.size(); ii++) {
        if ( ratings[ii]>ratings[ii-1] ) { last++; cursum+=last; leeway.clear(); leeway.push_back({ii,INT_MAX});}
        else if ( ratings[ii]==ratings[ii-1] ) { leeway.clear(); leeway.push_back({ii,INT_MAX}); last=1; cursum+=last; }
        else {
            if ( last>1 ) { leeway.push_back({ii,last-1-1}); last=1; cursum+=last; }
            else { 
                while (leeway.back().second==0) { leeway.pop_back();}
                int backto = leeway.back().first;
                leeway.back().second--;
                //std::cout<<"leeway "<<leeway.back().first<<" "<<leeway.back().second<<endl;
                last=1; 
                cursum+=last+ii-backto; 
            }
        }
        //std::cout<<cursum<<" ";
    }
    std::cout<<endl;
    return cursum;    
    }
};



