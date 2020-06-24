#Only a Medium difficulty. One of my earlier LeetCode efforts.
class Solution(object):
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        if len(s)==0: return 0
        if len(s)==1: return 1
        curlon=0
        maxlon=1
        dict=""
        for i in range (0, len(s)):
            curlon=1
            dict=s[i]
            j=i+1
            while j<len(s) and s[j] not in dict:
                #print(s[j])
                dict=dict+s[j]
                j=j+1
                curlon=curlon+1
                if curlon>maxlon: maxlon=curlon

        return maxlon            

