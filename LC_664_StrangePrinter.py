# done sep 25 2020
# solves Leet Code 664, Strange Printer
# https://leetcode.com/problems/strange-printer/
# Difficulty Hard


# Problem stipulates a printer that wants to print a string
# of lowercase chars, but on each pass can only print a continuous
# substring of a single char.

# This is a standard dp table. When adding a new char to the
# subproblem, want to see if want to print that char on the same
# pass as previous appearances of that char.


class Solution(object):
    def strangePrinter(self, s):
        """
        :type s: str
        :rtype: int
        """
        if (len(s)==0): return 0

        # s might contain repeating adjacent characters. But a printer
        # will always print those on the same pass, so no need to take
        # them into account. Hence work with a, which is a copy of s
        # but with all adjacent repeats represented by just one character.
        curchar=s[0]
        a=""
        a+=curchar
        for ii in range(1, len(s)):
            if (s[ii]!=s[ii-1]):
                a+=s[ii]
        a=str(a)
        
        dp = [[0 for i in xrange(len(a))] for j in xrange(len(a))]

        # This is where the work happens.
        # dp table imagine as square, where row rr indicates beginning
        # of substring and column cc indicates end of substring. Only
        # work in upper right half of table (cc>=rr). Work columns left
        # to right, and within those columns work up from rr=cc to rr=0.
        # Idea is that for each new char (new cc), want to see how many
        # passes for the substring of just that char and the char before it,
        # then how many passes for that char and the two before it, ... all
        # the way until include the first char.

        for cc in range(0, len(a)):
            for rr in range(cc, -1,-1):
                # To print just this last char, always need one pass.
	        if rr==cc:
                    dp[cc][rr]=1
                # If new char doesn't match beginning of substring, cycle
                # over all possibilities for cutting the substring from
                # rr to cc to see how best to add new char.
                elif a[rr]!=a[cc]:
                    curmin = float('inf')
                    for ii in range(rr,cc):
                        curmin = min(curmin,dp[rr][ii]+dp[ii+1][cc])
                    dp[rr][cc]=curmin
                # Here is the real center of the algorithm. If the chars
                # at rr and cc match, want to consider all possibilities of
                # writing the new char on the same pass as a previous instance
                # of the same char. Cycle through like above, just in case
                # also have an instance between rr and cc that is also the
                # same char, consider writing that instance (at ii) and the
                # instance at cc in the same pass. Only need to consider the
                # possibility of passes which include rr and instances adjacent
                # to rr and cc, while might skip an instance of the char closer
                # to cc.
                else:
                    curmin = float('inf')
                    for ii in range(rr,cc):
                        if (a[ii]!=a[rr]):
                            curmin=min(curmin,dp[rr][ii]+dp[ii+1][cc])
                        else:
                            curmin=min(curmin,dp[rr][ii]+dp[ii+1][cc-1])
                    dp[rr][cc]=curmin
                    
        return dp[0][len(a)-1]  


