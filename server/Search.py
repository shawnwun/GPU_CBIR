

def load_model():

    #TODO: loading function for indexed image features
    # return the loaded model
    return None


def process_img(filename):

    #TODO: preprocess for submitted image
    # return the processed image feature
    return None

def rank(image_feature,indexing):

    #TODO: main ranking function
    # return a list of image paths
    return None
    

if  __name__ == "__main__":

    # main function serve for modular testing
    # test model loading
    indexing = load_model()
    print indexing

    # test preprocessing
    feature = process_img('PATH_TO_IMAGE')
    print feature

    # test ranking
    rank_list = rank(feature,indexing)
    print rank_list

