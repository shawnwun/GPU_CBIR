import os

def loadEdgelDic(file1):
    edgel_dic = dict()
    for columns in ( row.strip().split() for row in file1 ):  
        key = int(columns[0])
        docList = list()
        for docID in columns[1:]:
            docList.append(int(docID))
        edgel_dic[key] = docList
    return edgel_dic

def loadEdgelCtr(file2):
    edgel_counter = list()
    for columns in ( row.strip().split() for row in file2 ):  
        key = int(columns[0])
        count = int(columns[1])
        edgel_counter.append(count)
    return edgel_counter


def loadImgMap(file3):
    img_map = dict()
    for columns in ( row.strip().split() for row in file3 ):
        key = int(columns[0])
        edglist = list()
        for edgID in columns[1:]:
            edglist.append(int(edgID))
        img_map[key] = edglist
    return img_map
