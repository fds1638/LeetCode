// Done August 2 2020
// Solves LeetCode problem 1531, String Compression II
// https://leetcode.com/problems/string-compression-ii/
// Difficulty: Hard, success rate 27.7%
// Given a string and a number of possible deletions, find
// the minimum number of characters needed to encode the string,
// where encoding is like aaabb becomes 3a2b.
// The difficulty is when dropping the characters means that you
// can eliminate a letter and combine two separate groups of the
// same letter. For example, if you have aaabbaa and you can 
// drop 2, the best is to drop the two b's and combine the
// five a's into 5a for a length of 2. I ended up doing this one pretty
// efficiently, about the 60th percentile in speed and memory. I keep the
// whole dynamic programming table, which is inefficient.

class Solution {
public:
    int getLengthOfOptimalCompression(string s, int k) {
        std::unordered_map<char, int> themap;
        int slen=s.length();
        
        // break string up into tokens, like 3 a's, 2 b's, etc.
        vector<int> s_num;
        vector<char> s_let;
        char cur_char=s.at(0);
        int cur_count=1;
        int sidx = 0;
        s_let.push_back(cur_char);
        for (int ii=1; ii<slen; ii++){
            if ( s.at(ii)==cur_char ) { cur_count++; }
            else { s_num.push_back(cur_count); cur_count=1; cur_char=s.at(ii); s_let.push_back(cur_char);
                 }
        }
        s_num.push_back(cur_count);        
        int num_tokens = s_let.size();
        
        // dt is the table for doing the dynamic programming
        int dt[k+1][num_tokens];  //distance table for holding results
        // fill in first column of distance table
        // ii here is an index for rows
        for (int ii=0; ii<=k; ii++) {
            dt[ii][0]=max(s_num.at(0)-ii,0);
            if (dt[ii][0]>=100) {dt[ii][0]=4;}
            else if (dt[ii][0]>=10) {dt[ii][0]=3;}
            else if (dt[ii][0]>=2) {dt[ii][0]=2;}
            else if (dt[ii][0]>=1) {dt[ii][0]=1;}
        }

        // fill in the rest of the distance table dt
        // jj is index of columns
        for (int jj=1; jj<num_tokens; jj++) {
            // will loop over ii rows
            int nct = s_num.at(jj);
            // Need to set up gaptoprevs to use for calculating
            // if a gap to a previous occurrence of the same letter
            // can be eliminated.
            // Get numbers needed to clear out until
            // previous occurrence of said letter.
            // Beginning is universal letter.
            // First is column, second is num letters.
            vector<vector<int>> gaptoprevs;
            int runtotal=0;
            for (int gg=jj-1; gg>=0; gg--) {
                if ( s_let.at(gg)!=s_let.at(jj)) {runtotal+=s_num.at(gg);}
                else {
                    gaptoprevs.push_back({gg,runtotal});
                }
            }
            if (s_let.at(0)!=s_let.at(jj)) {
                gaptoprevs.push_back({-1,runtotal}); //universal, beginning
            }
            
            // This is the meat of the dynamic programming.
            for (int ii=0; ii<=k; ii++) {
                int mindist = 100000;
                int minrow = max(0, ii-nct);
                // Look at previous column for dynamic programming.
                for (int r=minrow; r<=ii; r++) {
                    int newomits = ii-r; // additional chars to omit
                    int newchars; // num new chars to add
                    if (nct-newomits>=10) {newchars=3;}
                    else if (nct-newomits>=2) {newchars=2;}
                    else if (nct-newomits==1) {newchars=1;}
                    else if (nct-newomits==0) {newchars=0;}
                    else {std::cout << "Error "<<ii<<" "<<r<<endl;}
                    int forthisr = newchars+dt[r][jj-1];
                    if (forthisr<mindist) {mindist=forthisr;}
                }
                // Look at the gaps for dynamic programming.
                for (int gg=0; gg<gaptoprevs.size(); gg++){
                    if (ii>=gaptoprevs[gg][1]) {
                        int sumcurlet=0;
                        int forthisr;
                        if (gaptoprevs[gg][0]>-1) { // if gap does not extend to beginning
                            for (int cc=gaptoprevs[gg][0]; cc<=jj; cc++) {
                                if (s_let.at(cc)==s_let.at(jj)) { sumcurlet+=s_num.at(cc);}
                            }
                            if (sumcurlet>=100) {sumcurlet=4;}
                            else if (sumcurlet>=10) {sumcurlet=3;}
                            else if (sumcurlet>=2) {sumcurlet=2;}
                            else if (sumcurlet>=1) {sumcurlet=1;}
                            else {std::cout << "Error sumcurlet ii " << ii << " gg " << gg << endl;}
                            if (gaptoprevs[gg][0]==0) {
                                forthisr = sumcurlet;
                            } else {
                                forthisr = dt[max(0,ii-gaptoprevs[gg][1])][gaptoprevs[gg][0]-1]+sumcurlet;
                            }
                        } else { //gap extends to the beginning
                            for (int cc=0; cc<=jj; cc++) {
                                if (s_let.at(cc)==s_let.at(jj)) { sumcurlet+=s_num.at(cc);}
                            }
                            if (sumcurlet>=100) {sumcurlet=4;}
                            else if (sumcurlet>=10) {sumcurlet=3;}
                            else if (sumcurlet>=2) {sumcurlet=2;}
                            else if (sumcurlet>=1) {sumcurlet=1;}
                            else {std::cout << "Error sumcurlet ii " << ii << " gg " << gg << endl;}
                            forthisr = sumcurlet;
                        }
                        // Record minimum distance (i.e. num of chars)
                        // from beginning to this column.
                        if (forthisr<mindist) {mindist=forthisr;}
                    }
                }            
                // Put mindist in the table.
                dt[ii][jj]=mindist;
            }    
        }
        return dt[k][num_tokens-1];
    }
};

