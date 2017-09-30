'''
这份代码加了测试代码，输出的结果的规则测试和正确结果的f1score
重点：这些函数只返回 True 或 False

总共有5种情况：
末音节、倒数第二音节、倒数第三音节、第一音节、第二音节
所以有五个函数，这五个函数，从上到下，优先级下降
所以，前面一个函数判断Ture，后面就不用判断了
但是，具体这些规则判断效果怎么样，还要去试验一下
毕竟这些规则，还是大多数情况下正确，具体正确率到多少，还是不清楚的
'''

from matplotlib import pyplot as plt
import numpy as np
import helper
import extract_changed
import vectorizer
from sklearn.metrics import f1_score


TAILS = ['ADE', 'EER', 'ESE', 'ESQUE', 'AIN', 'EE', 'ETTE', 'IQUE', 'INE', 'OON',
    'ADE', 'ETTE', 'EE', 'ESE', 'QUE', 'AAR', 'EER', 'ZEE', 'ROO',
    'IC', 'ION', 'ANA', 'ESCENCE', 'ESCENT', 'I', 'ICS', 'ITIS', 'ID',
    'EOUS', 'IAL', 'IAN', 'IENT', 'IOUS', 'ISH', 'IT',
    'LIAR', 'SIVE', 'TAL', 'UOUS', 'AL', 'TARIAN', 'SIS', 'ENCE', 'ENT',
    'IC','ION','ANA','ESCENT','ESCENCE','I','ICS','SIS','ID','INTREPID','INSIPID',
    'OUS', 'ITY', 'IAN', 'ANCE', 'ANCY', 'ENCE',
    'ENCY', 'ANT', 'ENT', 'LOGY', 'NOMY', 'ICAL',
    'IA', 'ARIUM', 'CRACY', 'CRAT', 'GRAPHY', 'ILE', 'TUDE', 'MENT',
    'AL', 'IAL', 'ICAL', 'IA', 'IUM', 'OUS', 'IAN', 'ITY',
    'ARY', 'ERY', 'ORY', 'ISM', 'IST', 'MONY',
    'AIM', 'AIN', 'CUR', 'EEM', 'DUCE', 'ERE', 'FIRM',
    'GN', 'OIN', 'OKE', 'OSE', 'PT', 'RCE', 'SELF', 'UME']
TAILS = list(set(TAILS))
print(len(TAILS))
print(TAILS)

def hasTail(tail, str):
    if (len(tail) <= len(str)):
        if (str[-len(tail):] == tail):
            return True
    return False

# 分离出每个data里的单词，用以规则判断
def depart(data):
    l = []
    for d in data:
        word_list = d.split(' ')
        pos = word_list[0].find(':')
        w = word_list[0][:pos]
        l.append(w)
    return l

# 用规则判断预测位置
def predict(x, true_y, data):
    predict_y = {}
    predict_count = {}
    i = 0
    for tail in TAILS:
        y = {1:0, 2:0, -1:0, -2:0, -3:0}
        pc = {1:0, 2:0, -1:0, -2:0, -3:0}
        for w in data:
            if (hasTail(tail, w) == True):

                pc[1] += 1
                pc[-1] += 1
                if (x[i]['vol_number'] > 1):
                    pc[2] += 1
                    pc[-2] += 1
                if (x[i]['vol_number'] > 2):
                    pc[-3] += 1

                if (true_y[i] == 1):
                    y[1] += 1
                if (true_y[i] == 2):
                    y[2] += 1
                if (x[i]['vol_number'] == true_y[i]):
                    y[-1] += 1
                if (x[i]['vol_number'] - 1 == true_y[i]):
                    y[-2] += 1
                if (x[i]['vol_number'] - 2 == true_y[i]):
                    y[-3] += 1

            i += 1
        i = 0
        predict_y[tail] = y
        predict_count[tail] = pc

    return predict_y, predict_count


if __name__ == '__main__':
    data = helper.read_data('../asset/training_data.txt')
    word_list = depart(data)
    mid = list(map(extract_changed.extract_train, data))
    feature, true_y = vectorizer.departit(mid)

    predict_y, predict_count = predict(feature, true_y, word_list)

    count = 0
    l = []
    wantTails = {1:[], 2:[], -1:[], -2:[], -3:[]}
    unWantTails = list(TAILS)
    for tail in TAILS:
        ifPass = False
        y = predict_y[tail]
        pc = predict_count[tail]
        print("后缀：", tail)
        biggest = 0
        way = 0
        for key in pc:
            if (pc[key] > 0):
                pro = y[key] / pc[key]
                if (pro > 0.7):
                    if (pro > biggest):
                        biggest = pro
                        way = key
                    ifPass = True
                    l.append(pro)
                    print(key, " 个数：", pc[key], end=" ")
                    print("正确率：", pro)
        if(ifPass):
            count += 1
            wantTails[way].append(tail)
            del unWantTails[unWantTails.index(tail)]

    print("总共", len(TAILS), "个后缀测试", ", 可以采用的后缀有：", count, " 个")
    print(np.mean(l))
    print(unWantTails)
    for key in wantTails:
        print(key, " Tails: ", wantTails[key])
    '''
    print("第一音节个数：", pc[1], end=" ")
    print("第一音节正确率：", y[1] / (pc[1]+1))
    print("第二音节个数：", pc[2], end=" ")
    print("第二音节正确率：", y[2] / (pc[2]+1))
    print("末音节个数：", pc[-1], end=" ")
    print("末音节正确率：", y[-1] / (pc[-1]+1))
    print("倒数第二音节个数：", pc[-1], end=" ")
    print("倒数第二音节正确率：", y[-2] / (pc[-1]+1))
    print("倒数第三音节个数：", pc[-1], end=" ")
    print("倒数第三音节正确率：", y[-3] / (pc[-1]+1))
    '''