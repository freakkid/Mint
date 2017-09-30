from . import extract_changed
from . import helper
from . import vectorizer
import numpy as np
def readplz():
    return helper.read_data('./asset/training_data.txt')

def get(training_data):
    mid = list(map(extract_changed.extract_train,training_data))
    feature,label = vectorizer.departit(mid)
    feature = vectorizer.vectorize(feature)
    #label = vectorizer.label(label)
    label = np.array(label)
    return feature.toarray(),label


def cut_train_file(training_data,start,end):   #cut off part of training_data
    x,y = get(training_data)
    return x[start:end],y[start:end]


def feedtest(model,x,y):
    test = model
    re = test.fit(x,y)
    print(re.score(x,y))

def result(arr):
    arr = comb_result(arr,len(arr))
    r = []
    for x in arr:
        r.append(vote(x))
    return r

#input an array ,feedback the highest freq one
def vote(arr):
    v=[0,0,0,0,0,0]
    for x in arr:
        v[x] += 1
    big = 0
    big_val = 0
    for x in range(6):
        if v[x] >big_val:
            big_val = v[x]
            big = x

    return big

#transform
def comb_result(arr,num_of_model):
    result = []
    for i in range(len(arr[0])):
        item = []
        for j in range(num_of_model):
            item.append(arr[j][i])
        result.append(item)
    return result
