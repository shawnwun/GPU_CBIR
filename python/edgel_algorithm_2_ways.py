from edgel_helper_func import *
import operator
import math 


def checkTOL(edgel_img, skch_edgel_list):
    TOL = 2
    for xa in range(0 - TOL, TOL + 1):
        for ya in range(0 - TOL, TOL + 1):
            if(skch_edgel_list.has_key(edgel_img + xa * 10000 + ya * 10)):
                return True

    return False
    

def computeScoreRev(skch_edgel_list, img_map):
    score_rev = dict()
    for i in range(0, len(img_map)):
        score_rev[i] = 0

    print "skch_edgel_list"
    print len(skch_edgel_list)
    #print skch_edgel_list

    for docID in img_map.keys():
        #print docID
        for edgel_img in img_map[docID]:
            if(checkTOL(edgel_img, skch_edgel_list)):
                score_rev[docID] += 1
                
    return score_rev


def computeDocScoreHash_2Ways(skch, edgel_dic, edgel_ctr, img_map):
    score = dict()
    for i in range(0, len(edgel_ctr)):
        score[i] = 0
        
    
    ornt_skch = cvtToOrntImg(skch)

    rows, cols = ornt_skch.shape
    TOL = 2
    skch_edgel_list = dict()
    
    for x in range(0, rows):
        for y in range(0, cols):
            val = ornt_skch[x, y]
            if(val != 0.0):
                skch_edgel_list[int(x * 10000 + y * 10 + quantifiedAngle(val))] = True
                for rx in range(maxOf(0, x - TOL), minOf(rows, x + TOL + 1)):
                    for ry in range(maxOf(0, y - TOL), minOf(cols, y + TOL + 1)):
                        key = int(rx * 10000 + ry * 10 + quantifiedAngle(val))
                        if(edgel_dic.has_key(key)):
                            for doc in edgel_dic.get(key):
                                score[doc] = score[doc] + 1

    score_rev = computeScoreRev(skch_edgel_list, img_map)
    skch_ctr = len(skch_edgel_list)

    
    ret = dict()
    for docID in score.keys():
        if(edgel_ctr[docID] != 0):
            score[docID] = score[docID] / float(edgel_ctr[docID])
            score_rev[docID] = score_rev[docID] / float(skch_ctr)
            ret[docID] = math.sqrt(score[docID] * score_rev[docID])
        else:
            if(score_rev[docID] != 0.0):
                print "error in computing score_rev!"
                print docID
                print score_rev[docID]
            score[docID] = 0.0
            ret[docID] = 0.0


    return score, score_rev, ret





def getRanking_2Ways(skch, edgel_dic, edgel_ctr, img_map):
    
    score1, score2, score = computeDocScoreHash_2Ways(skch, edgel_dic, edgel_ctr, img_map)

    #rank = list()
    #rankScore = list()
    #for key, value in sorted(score.iteritems(),key=operator.itemgetter(1),reverse=True):
    #    rank.append(key)
    #    rankScore.append(value)

    return score1, score2, score 
