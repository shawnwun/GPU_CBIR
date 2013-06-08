from cv2 import *
import numpy as np
import os
from edgel_algorithm import *
from loadin import *


if  __name__ == "__main__":

    print "Start"
    
    # main function serve for modular testing
    # test load in
    edgel_dic = loadEdgelDic(open('edgel_dic.txt', 'r'))
    edgel_ctr = loadEdgelCtr(open('edgel_ctr.txt', 'r'))
    img_map   = loadImgMap  (open('img_map.txt'))

    print "load done"
    #print type(edgel_dic)
    #print type(edgel_ctr)
    #print type(img_map)
    #print "load in data done!"

    # test  ranking
    skch = imread('skch.png', CV_LOAD_IMAGE_GRAYSCALE)
    #rank, rankScore = getRanking(skch, edgel_dic, edgel_ctr)
    score1, score2, score  = getRanking_2Ways(skch, edgel_dic, edgel_ctr, img_map)
    
    #print type(skch)
    #print "rank = "
    #print rank[:20]
    #print "rankScore = "
    #print rankScore[:20]


