from cv2 import *
import numpy as np
import os
from edgel_algorithm import *
from loadin import *


if  __name__ == "__main__":

    # main function serve for modular testing
    # test load in
    file1 = open('edgel_dic.txt', 'r')
    file2 = open('edgel_ctr.txt', 'r')
    edgel_dic = loadEdgelDic(file1)
    edgel_ctr = loadEdgelCtr(file2)

    print edgel_dic
    print edgel_ctr

    # test  ranking
    skch = imread('skch.png', CV_LOAD_IMAGE_GRAYSCALE)
    rank, rankScore = getRanking(skch, edgel_dic, edgel_ctr)

    print skch
    print rank
    print rankScore

