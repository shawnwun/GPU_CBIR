from cv2 import *
import numpy as np
import os
from edgel_algorithm import *

skch = imread('skch.png', CV_LOAD_IMAGE_GRAYSCALE)
score1, score2, score  = getRanking_2Ways(skch, edgel_dic, edgel_ctr, img_map)
