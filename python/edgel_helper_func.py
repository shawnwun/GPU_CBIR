from cv2 import *

def calculateOrnt(dx, dy):
    ornt = dx
    rows,cols = dx.shape
    for i in range(0, rows):
        for j in range(0, cols):
            x = dx[i,j]
            y = dy[i,j]
            ornt[i,j] = fastAtan2(x, y)
    return ornt

def cvtToOrntImg(src):
    dx = Sobel(src, CV_32F, 1, 0, 3)
    dy = Sobel(src, CV_32F, 0, 1, 3)

    ornt_src = calculateOrnt(dx, dy)
    return ornt_src

def maxOf(a, b):
    if(a > b):
        return a
    else:
        return b

def minOf(a, b):
    if(a < b):
        return a
    else:
        return b

def inRange(val, a, b):
    return ((val >= a)  and (val < b))


def quantifiedAngle(val):
    if(inRange(val, 0.0, 45.0)):
        return 0
    elif(inRange(val, 45.0, 90.0)):
        return 1
    elif(inRange(val, 90.0, 135.0)):
        return 2
    elif(inRange(val, 135.0, 180.0)):
        return 3
    elif(inRange(val, 180.0, 225.0)):
        return 4
    elif(inRange(val, 225.0, 270.0)):
        return 5
    elif(inRange(val, 270.0, 315.0)):
        return 6
    elif(inRange(val, 315.0, 360.0)):
        return 7
    else:
        print "invalid value in quantifiedAngle()"
        
    
    
