from cv2 import *
import numpy as np
import os
from edgel_algorithm import *
from loadin import *


print "Start preprocessing..."
file1 = open('edgel_dic.txt', 'r')
file2 = open('edgel_ctr.txt', 'r')
edgel_dic = loadEdgelDic(file1)
edgel_ctr = loadEdgelCtr(file2)


print "Enter online stage..."
skch = imread('skch.png', CV_LOAD_IMAGE_GRAYSCALE)
#top100 = getTop100(skch, edgel_dic, edgel_ctr)
rank, rankScore = getRanking(skch, edgel_dic, edgel_ctr)

#verification, show sketch and retrieval results
imshow('sketch', skch)
print "Press any key on the pictures to exit"
waitKey(0)
destroyAllWindows()  
