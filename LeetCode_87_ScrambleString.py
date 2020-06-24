#A Hard problem with 33.4% acceptance rate as of 23 Jun 2020.
#Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
#I looked to see if every substring in s1 could be found as a possibly scrambled
#but contiguous substring in s2.
class Solution(object):
    def isScramble(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        def ssmatch(s1, s2):
            lens=len(s1)
            #check to see if they have the same characters
            if sorted(s1)!=sorted(s2):
                return False
            #check single length strings
            if lens==1 and s1[0]!=s2[0]: return False
            if lens==1 and s1[0]==s2[0]: return True
            # go through and check to see that can always split
            #print("in ssmatch", s1, s2)
            for ii in range(1,lens):
                #opposite directions
                print(s1[0:ii],s2[lens-ii:lens], s1[ii:], s2[0:lens-ii] )
                if sorted(s1[0:ii])==sorted(s2[lens-ii:lens]) and sorted(s1[ii:])==sorted(s2[0:lens-ii]):
                    if ssmatch(s1[0:ii],s2[lens-ii:lens]) and ssmatch(s1[ii:],s2[0:lens-ii]): 
                        #print("returning true")
                        return True
                    #return True
                #same directions
                print(s1[0:ii],s2[0:ii], s1[ii:], s2[ii:] )
                if sorted(s1[0:ii])==sorted(s2[0:ii]) and sorted(s1[ii:])==sorted(s2[ii:]):
                    if ssmatch(s1[0:ii],s2[0:ii]) and ssmatch(s1[ii:],s2[ii:]): 
                        #print("returning true")
                        return True
                    #return True
            print("returning false")
            return False
            
        lens=len(s1)
        #check to see if they have the same characters
        if sorted(s1)!=sorted(s2):
            return False
        #check single length strings
        if lens==1 and s1[0]!=s2[0]: return False
        if lens==1 and s1[0]==s2[0]: return True
        # go through and check to see that can always split
        return ssmatch(s1,s2)    
            

        '''    
        for ii in range(1,lens):
            #opposite directions
            print(s1[0:ii],s2[lens-ii:lens], s1[ii:], s2[0:lens-ii] )
            if sorted(s1[0:ii])==sorted(s2[lens-ii:lens]) and sorted(s1[ii:])==sorted(s2[0:lens-ii]):
                return True
            #same directions
            print(s1[0:ii],s2[0:ii], s1[ii:], s2[ii:] )
            if sorted(s1[0:ii])==sorted(s2[0:ii]) and sorted(s1[ii:])==sorted(s2[ii:]):
                return True
        #return False    
        #'''
        #check for two-letter switches
        for ii in range(lens):
            if s1[ii]!=s2[ii]:
                nma = 0 #no match ahead
                nmb = 0 #no match behind
                at0 = 0 #at beginning
                at1 = 0 #at end
                if (ii<lens-1) and (s1[ii+1]!=s2[ii] or s1[ii]!=s2[ii+1]): nma=1
                if (ii>0) and (s1[ii-1]!=s2[ii] or s1[ii]!=s2[ii-1]):nmb=1
                if ii==0: at0 = 1
                if ii==lens-1: at1 = 1
                if nma == 1 and nmb == 1: return False
                if nma == 1 and at0 == 1: return False
                if nmb == 1 and at1 == 1: return False
        #'''
        return True
        

