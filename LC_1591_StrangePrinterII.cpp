// done 09 Oct 2020
// solves Leet Code problem 1591, Strange Printer II
// https://leetcode.com/problems/strange-printer-ii/
// difficulty: Hard

// A printer can print only a rectangle of a color at a time,
// and each color only once. Can the given pattern have been printed?

// I used a couple of maps to see if there are cycles of one color
// having to be both before and after another. Speed-wise it was ok,
// though in the lower half, but it also took a lot of space. However,
// conceptually it was straightforward.

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        // Central idea: for each color that exists, it must
        // have been printed as a single rectangle. Can find the
        // top, bottom, left, and right bounds of that rectangle.
        // Any other color that exists in that rectangle must have
        // been printed later. 
        // Go through and check for any cycles where color A must have
        // been after color B but also color B must have been after color A,
        // or for cycles involving more colors.
        

        // Go through and set rectangle bounds for each color determined
        // by extremes of where that color shows up.
        map<int , vector<int> > bounds;
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        for (int rr=0; rr<m; rr++) {
            for (int cc=0; cc<n; cc++) {
                if (bounds.find(targetGrid[rr][cc])!=bounds.end()){
                    if (rr>bounds[targetGrid[rr][cc]][1]) {bounds[targetGrid[rr][cc]][1]=rr;}
                    if (cc<bounds[targetGrid[rr][cc]][2]) {bounds[targetGrid[rr][cc]][2]=cc;}
                    if (cc>bounds[targetGrid[rr][cc]][3]) {bounds[targetGrid[rr][cc]][3]=cc;}
                } 
                if (bounds.find(targetGrid[rr][cc])==bounds.end()) {
                    int junk = targetGrid[rr][cc];
                    bounds[junk]={rr,rr,cc,cc};
                }
            }
        }

        /*
        // print bounds for debugging
        map<int, vector<int> >::iterator bb;
        for (bb=bounds.begin(); bb!=bounds.end(); bb++) {
            cout<<bb->first<<": ";
            for (int ii=0; ii<bb->second.size(); ii++) {
                cout<<bb->second[ii]<<" ";
            }
            cout<<endl;
        }
        */
        
        // For each color, afters holds all the colors that must have come after it.
        // Check for cycles.
        map<int, set<int> > afters;
        for (int rr=0; rr<m; rr++) {
            for (int cc=0; cc<n; cc++) {
                map<int, vector<int> >::iterator bit;
                for (bit=bounds.begin(); bit!=bounds.end(); bit++) {
                    if (targetGrid[rr][cc]!=bit->first&&rr>=bit->second[0]&&rr<=bit->second[1]&&cc>=bit->second[2]&&cc<=bit->second[3]) {
                        // check for 2-cycle
                        afters[bit->first].insert(targetGrid[rr][cc]);
                        if ( afters[targetGrid[rr][cc]].find(bit->first)!=afters[targetGrid[rr][cc]].end()) {  return false; }
                        // check for longer cycle
                        set<int>::iterator aa;
                        for (aa=afters[targetGrid[rr][cc]].begin(); aa!=afters[targetGrid[rr][cc]].end(); aa++) {
                            afters[bit->first].insert(*aa);
                            if ( afters[*aa].find(bit->first)!=afters[*aa].end()) {  return false; }
                        }
                            
                    }
                }
            }
        }

        // If no cycles found, return true.
        return true;
    }
};

