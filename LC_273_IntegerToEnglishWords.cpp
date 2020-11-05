// done 5 Nov 2020
// solves Leet Code 273, Integer To English Words
// https://leetcode.com/problems/integer-to-english-words/
// difficulty: Hard

// This really wasn't that hard, even though the problem says there are a lot of 
// edge cases. This solution is about in the middle of the range speed-wise.

class Solution {
public:
    string numberToWords(int num) {
        // This is pretty straightforward. Most of my debugging involved duplicate
        // whitespace values or dealing with a situation like 20000 where you need
        // to add the "Thousand" even though the thousands digit is zero.
        if (num==0) {return "Zero";}
        map<int,string> singles;
        singles.insert({1,"One"});
        singles.insert({2,"Two"});
        singles.insert({3,"Three"});
        singles.insert({4,"Four"});
        singles.insert({5,"Five"});
        singles.insert({6,"Six"});
        singles.insert({7,"Seven"});
        singles.insert({8,"Eight"});
        singles.insert({9,"Nine"});
        map<int,string> teens;
        teens.insert({10,"Ten"});
        teens.insert({11,"Eleven"});
        teens.insert({12,"Twelve"});
        teens.insert({13,"Thirteen"});
        teens.insert({14,"Fourteen"});
        teens.insert({15,"Fifteen"});
        teens.insert({16,"Sixteen"});
        teens.insert({17,"Seventeen"});
        teens.insert({18,"Eighteen"});
        teens.insert({19,"Nineteen"});
        map<int,string> tens;
        tens.insert({2,"Twenty"});
        tens.insert({3,"Thirty"});
        tens.insert({4,"Forty"});
        tens.insert({5,"Fifty"});
        tens.insert({6,"Sixty"});
        tens.insert({7,"Seventy"});
        tens.insert({8,"Eighty"});
        tens.insert({9,"Ninety"});
        string retval = "";
        int curdig;
        int lastdig;
        int place = 0;
        while (num>0) {
            int curdig = num%10;
            num=num/10;
            place++;
            //cout<<"curdig "<<curdig<<" place "<<place<<endl;
            if (place==1) {
                retval = singles[curdig] + retval;
            } else if (place%3==1) {
                //cout<<"curdig "<<curdig<<" num "<<num<<endl;
                if (curdig!=0||(curdig==0&&num>0&&num%100>0)) {
                    if (retval[0]==' ') { retval = retval.substr(1);}
                    if (place == 4) {
                        retval = singles[curdig] + " Thousand " + retval;
                    } else if (place == 7) {
                        retval = singles[curdig] + " Million " + retval;
                    } else if (place == 10) {
                        retval = singles[curdig] + " Billion " + retval;
                    } else {
                        return "Error 4";
                    }
                }
            } else if (place%3==2) {
                if (curdig==1) {
                    int firstspace = retval.find_first_of(" ");
                    //cout<<"firstspace "<<firstspace<<endl;
                    if (firstspace==-1) {
                        retval = "";
                        retval = teens[curdig*10+lastdig];
                    } else {
                        retval = retval.substr(firstspace+1);
                        retval = teens[curdig*10+lastdig]+" "+retval;
                    }
                } else {
                    if (retval[0]==' ') { retval = retval.substr(1);}
                    if (retval.size()>0) {
                        retval = tens[curdig]+" "+retval;
                    } else {
                        retval = tens[curdig];
                    }
                }
            } else if (place%3==0) {
                if (curdig!=0) {
                    if (retval[0]!=' ') {
                        retval = singles[curdig]+" Hundred "+retval;
                    } else {
                        retval = singles[curdig]+" Hundred"+retval;
                    }
                }
            } else {
                //cout<<"Error"<<endl;
                return "Error";
            }
            //cout<<retval<<endl;
            lastdig = curdig;
        }
        int lastidx = retval.size()-1;
        if (retval[lastidx]==' ') {
            retval = retval.substr(0,lastidx);
        }
        return retval;
    }
};


