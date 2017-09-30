from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction import DictVectorizer
from sklearn.ensemble import RandomForestClassifier
import numpy as np
import pickle

##############################################################
def ultima(word):
    TAILS = ['EER', 'FIRM', 'UME']
    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True
    return False

def penult(word):
    TAILS = ['ION', 'I', 'IC', 'ICS', 'ITIS', 'ESCENT', 'ESCENCE', 'SIVE', 'ANA', 'LIAR']
    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True
    return False

def antepenultimate(word):
    TAILS = ['OKE', 'IA', 'OIN', 'ICAL', 'ENCY', 'LOGY', 'ZEE', 'IAN',
    'ERY', 'IST', 'OON', 'IENT', 'AIM', 'UOUS', 'ITY', 'TUDE', 'IUM', 'CRAT']
    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True
    return False

def firstSyll(word):
    TAILS = ['ANCY', 'AAR', 'ARY', 'ILE', 'ISM', 'ORY', 'MONY', 'ISH']
    WORDS = ['ORIGINAL', 'PRISONAL', 'RESIDUAL', 'ADJECTIVAL',
    'ANECDOTAL', 'CUSTOMARY', 'SCIENTIST', 'SLAVERY', 'ADVERTISE', 'MESSAGE']
    for w in WORDS:
        if (w == word):
            return True
    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True
    return False

def departWord(data):
    l = []
    for d in data:
        word_list = d.split(' ')
        pos = word_list[0].find(':')
        w = word_list[0][:pos]
        l.append(w)
    return l

# 用规则判断预测位置
def predict(x, data):
    predict_y = []                   # 规则判断的结果
    word_index = []                  # 适用于规则判断的词汇的下标列表++++++++++++++++++++
    index = 0                        # 词汇的下标++++++++++++++++++++
    for w in data:
        if (x[index]['vol_number'] == 1):
            predict_y.append(1)
            word_index.append(index) 
        elif (ultima(w) == True):
            if (x[index]['vol_number'] >= 3):
                predict_y.append(x[index]['vol_number'])
                word_index.append(index)
        elif (penult(w) == True):
            if (x[index]['vol_number'] >= 3):
                predict_y.append(x[index]['vol_number'] - 1)
                word_index.append(index)
        elif (antepenultimate(w) == True):
            if (x[index]['vol_number'] >= 3):
                predict_y.append(x[index]['vol_number'] - 2)
                word_index.append(index)
        elif (firstSyll(w) == True):
            predict_y.append(1)
            word_index.append(index)

        index += 1

    return predict_y, word_index
############################################

def departit(original_tuple_array):
    x,y = zip(*original_tuple_array)
    return list(x),list(y)


def vectorize(feature):
    vectorizer = DictVectorizer(dtype=float, sparse=True)
    feature = vectorizer.fit_transform(feature)
    return feature


def label(target):
    encoder = LabelEncoder()
    return encoder.fit_transform(target)

def extract_train(strs):
    word_list = strs.split(' ')
    allvol = ['AA', 'AE', 'AH', 'AO', 'AW', 'AY', 'EH', 'ER', 'EY', 'IH', 'IY', 'OW', 'OY', 'UH', 'UW']
    vol_list=[]       #in case you wanna use it,not sure it's useful or not
    cons_list=[]      #in case you wanna use it,not sure it's useful or not
    vol_count = 1
    pri_stress_position = 0
    for x in word_list:
        if x[-1] =='0':
            vol_list.append(x[:-1])
            vol_count+=1
        elif x[-1] == '1':
            vol_list.append(x[:-1])
            pri_stress_position = vol_count
            vol_count+=1
        elif x[-1] ==  '2':
            vol_list.append(x[:-1])
            vol_count+=1
        else:
            cons_list.append(x)
    feature = {'vol_number':vol_count-1}
    #feature={}
    for x in range(len(vol_list[0])):
        if vol_list[0][x] == ':':
            vol_list[0] = vol_list[0][x+1:]
            break
    for x in allvol:
        if vol_list.count(x) == 0:
            feature[x] = False
        else:
            feature[x] = True

    for x in range(5):
        if x < len(vol_list):
            feature['pos'+str(x)] = allvol.index(vol_list[x])
        else:
            feature['pos'+str(x)] = 22
    # add something
    head_tails = []
    x = word_list[0].find(':')              # find the position of ':' 
    head_tails = head_and_tails(word_list[0][:x])


    for i in range(6):
        if head_tails[i]==1:
            feature['ht'+str(i)]=True
        else:
            feature['ht'+str(i)]=False

    return (feature, pri_stress_position)

def extract_test(strs):
    word_list = strs.split(' ')
    allvol = ['AA', 'AE', 'AH', 'AO', 'AW', 'AY', 'EH', 'ER', 'EY', 'IH', 'IY', 'OW', 'OY', 'UH', 'UW']

    vol_list=[]
    for x in word_list:
        if allvol.count(x) > 0:
            vol_list.append(x)
    for x in range(len(vol_list[0])):
        if vol_list[0][x] == ':':
            vol_list[0] = vol_list[0][x+1:]
            break
    vol_number = len(vol_list)

    head_tails = []
    x = word_list[0].find(':')              # find the position of ':' 
    head_tails = head_and_tails(word_list[0][:x])


    feature = {'vol_number':vol_number}
    for x in allvol:
        if vol_list.count(x) == 0:
            feature[x] = False
        else:
            feature[x] = True
    for x in range(5):
        if x < len(vol_list):
            feature['pos'+str(x)] = allvol.index(vol_list[x])
        else:
            feature['pos'+str(x)] = 22
    for i in range(6):
        if head_tails[i]==1:
            feature['ht'+str(i)]=True
        else:
            feature['ht'+str(i)]=False

    return feature

#function below returns a array that contain infomation about prefix and postfix of word
def head_and_tails(word):
    head = ['A','AB','AC','AD','AL','BE','CON','DE','DIS','IM','IN','EM','EN','FOR','PRE',
    'PRO','TO','TRANS','MIS','RE','TANS','UN']
    tail1 = ['AIM','AIN','CUR', 'EEM', 'DUCE','ERE','FIRM','GN','OIN','OKE','OSE','PT','RCE','SELF','UME']
    tail2 = ['AL','ACY','AGE','ER','OR','FUL','ISM','IST','IVE','IZE','LESS','ISE','LY','NESS','SHIP','ING','ABLE','RY','TY']
    tail3 = ['ADE','ETTE','EE','ESE','QUE','AAR','EER','ZEE','ROO']
    tail4 = ['IC','ION','ANA','ESCENT','ESCENCE','i','ICS','SIS','ID','INTREPID','INSIPID']
    tail5 = ['ABLE','IBLE','ARY','ERY','ORY']
    result = [0,0,0,0,0,0]  #result array
    for x in head:
        if len(x) <= len(word):
            if word[:len(x)] == x:
                result[0] = 1
    for x in tail1:
        if len(x) <= len(word):
            if word[-len(x):] == x:
                result[1] = 1
    for x in tail2:
        if len(x) <= len(word):
            if word[-len(x):] == x:
                result[2] = 1
    for x in tail3:
        if len(x) <= len(word):
            if word[-len(x):] == x:
                result[3] = 1
    for x in tail4:
        if len(x) <= len(word):
            if word[-len(x):] == x:
                result[4] = 1
    for x in tail5:
        if len(x) <= len(word):
            if word[-len(x):] == x:
                result[5] = 1
    return result

def get(training_data):
    mid = list(map(extract_train,training_data))
    feature,label = departit(mid)
    feature = vectorize(feature)
    #label = label(label)
    label = np.array(label)
    return feature.toarray(),label


def train(data, classifier_file):
    x,y = get(data)
    model = RandomForestClassifier()
    model.fit(x,y)
    f = open(classifier_file, 'wb')
    pickle.dump(model,f)
    f.close()

def test(data, classifier_file):
    feature = list(map(extract_test,data))
    word_list = departWord(data)
    rulePredict_y, word_index = predict(feature, word_list)
    count = 0
    feature = vectorize(feature).toarray()
    f = open(classifier_file, 'rb')
    classifier = pickle.load(f)
    y = classifier.predict(feature)
    for index in word_index:
        y[index] = rulePredict_y[count]
        count += 1
    f.close()
    predict_y = list(map(int,y))
    return predict_y

# if __name__ == '__main__':
#     from pkg.helper import read_data
#     train_data = read_data("asset/training_data.txt")
#     train(train_data, 'classifier_file')
#     test_data = read_data("asset/tiny_test.txt")
#     return_value = test(test_data, 'classifier_file')
#     print(return_value)
#     print(type(return_value))
#     print(len(return_value))

#     print("Done")

