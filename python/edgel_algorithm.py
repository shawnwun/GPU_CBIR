from edgel_helper_func import *



def computeDocScore(skch, edgel_dic, edgel_ctr):
    score = list()
    for i in range(0, len(edgel_ctr)):
        score.append(0)
    
    ornt_skch = cvtToOrntImg(skch)

    rows, cols = ornt_skch.shape
    TOL = 2
    
    for x in range(0, rows):
        for y in range(0, cols):
            val = ornt_skch[x, y]
            if(val != 0.0):
                for rx in range(maxOf(0, x - TOL), minOf(rows, x + TOL + 1)):
                    for ry in range(maxOf(0, y - TOL), minOf(cols, y + TOL + 1)):
                        key = int(rx * 10000 + ry * 10 + quantifiedAngle(val))
                        if(edgel_dic.has_key(key)):
                            for doc in edgel_dic.get(key):
                                score[doc] = score[doc] + 1
                        
    for i in range(0, len(score)):
        if(edgel_ctr[i] != 0):
            score[i] = score[i] / float(edgel_ctr[i])
        else:
            score[i] = 0

    return score



def getTop100(skch, edgel_dic, edgel_ctr):
    
    score = computeDocScore(skch, edgel_dic, edgel_ctr)
    
    top100 = list()
    buff = list(score)
    temp = list(score)
    buff.sort()
    top = len(buff)-1

    ptr = 0
    for i in range(0, 100):
        top100.append(ptr + score[ptr:].index(buff[top - i]))
        if(buff[top - i] == buff[top - i - 1]):
            ptr = top100[len(top100)-1] + 1
        else:
            ptr = 0
    ret = top100[:100]
    return ret



