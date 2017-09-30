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

import helper
import extract_changed
import vectorizer
from sklearn.metrics import f1_score

#判断末音节重音
def ultima(word):
    TAILS = ['EER', 'FIRM', 'UME']
    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True

    return False

#判断倒数第二音节
def penult(word):
    TAILS = ['ION', 'I', 'IC', 'ICS', 'ITIS', 'ESCENT', 'ESCENCE', 'SIVE', 'ANA', 'LIAR']

    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True

    return False

#判断倒数第三音节
def antepenultimate(word):
    TAILS = ['OKE', 'IA', 'OIN', 'ICAL', 'ENCY', 'LOGY', 'ZEE', 'IAN',
    'ERY', 'IST', 'OON', 'IENT', 'AIM', 'UOUS', 'ITY', 'TUDE', 'IUM', 'CRAT']

    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
                return True

    return False

#判断第一音节
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

#判断第二音节
def secondSyll(word):
    HEADS = ['A', 'AB', 'AC', 'AD', 'AL', 'BE', 'CON', 'DE',
    'DIS', 'EM', 'EN', 'IN', 'MIS', 'RE', 'TANS', 'UN']
    TAILS = ['OKE', 'IA', 'OIN', 'ICAL', 'ENCY', 'LOGY', 'ZEE',
    'IAN', 'ERY', 'IST', 'OON', 'IENT', 'AIM', 'UOUS', 'ITY', 'TUDE', 'IUM', 'CRAT']

    for head in HEADS:
        if (len(head) <= len(word)):
            if (word[:len(head)] == head):
                return True

    for tail in TAILS:
        if (len(tail) <= len(word)):
            if (word[-len(tail):] == tail):
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
def predict(x, data, true_y):
    predict_y = []                   # 规则判断的结果
    predict_way = []                 # 记录是属于哪一种规则判断
    words = []                       # 能够用规则判断的词汇
    extract_y = []                   # 能够用规则判断的词汇的正确位置
    i = 0
    for w in data:
        if (ultima(w) == True):
            if (x[i]['vol_number'] >= 3):
                predict_y.append(x[i]['vol_number'])
                predict_way.append(-1)
                words.append(w)
                extract_y.append(true_y[i])
            i += 1
            continue

        if (penult(w) == True):
            if (x[i]['vol_number'] >= 3):
                predict_y.append(x[i]['vol_number'] - 1)
                predict_way.append(-2)
                words.append(w)
                extract_y.append(true_y[i])
            i += 1
            continue

        if (antepenultimate(w) == True):
            if (x[i]['vol_number'] >= 3):
                predict_y.append(x[i]['vol_number'] - 2)
                predict_way.append(-3)
                words.append(w)
                extract_y.append(true_y[i])
            i += 1
            continue

        if (firstSyll(w) == True):
            predict_y.append(1)
            predict_way.append(1)
            words.append(w)
            extract_y.append(true_y[i])
            i += 1
            continue

        i += 1

    return predict_y, extract_y, words, predict_way


if __name__ == '__main__':
    data = helper.read_data('../asset/training_data.txt')
    word_list = depart(data)
    mid = list(map(extract_changed.extract_train, data))
    feature, true_y = vectorizer.departit(mid)

    # predict_y 是预测的位置
    # extract_y 是正确的位置
    # words 是可以规则判断的所有单词
    # predict_way 存的是每个单词属于哪一种规则(属于末音节，倒数第二....)
    predict_y, extract_y, words, predict_way = predict(feature, word_list, true_y)

    print("f1_score =", f1_score(predict_y, extract_y, average='weighted'))

    # wrongPredictInfo 记录错误单词
    # wrongPredictInfo是一个链表，它存的单位也是链表
    wrongPredictInfo = []
    i = 0
    count = 0
    # right wrong count记录各种规则的正确判断、错误判断的个数
    # 1代表第一音节，-1代表末音节，以此类推
    right_count = {1: 0, -1: 0, -2: 0, -3: 0}
    wrong_count = {1: 0, -1: 0, -2: 0, -3: 0}
    for b in predict_y:                       #计算成功率
        if (b == extract_y[i]):
            count += 1
            right_count[predict_way[i]] += 1
        else:
            pre = "Predict: " + str(predict_y[i])
            t = "True: " + str(extract_y[i])
            wrong_count[predict_way[i]] += 1
            wrongPredictInfo.append([words[i], pre, t, predict_way[i]])
        i += 1

    print("第一音节正确率：", right_count[1] / (right_count[1] + wrong_count[1]))
    print("第一音节个数：", right_count[1] + wrong_count[1])
    print("末音节正确率：", right_count[-1] / (right_count[-1] + wrong_count[-1]))
    print("末音节个数：", right_count[-1] + wrong_count[-1])
    print("倒数第二音节正确率：", right_count[-2] / (right_count[-2] + wrong_count[-2]))
    print("倒数第二音节个数：", right_count[-2] + wrong_count[-2])
    print("倒数第三音节正确率：", right_count[-3] / (right_count[-3] + wrong_count[-3]))
    print("倒数第三音节个数：", right_count[-3] + wrong_count[-3])
    print("单词总个数:", len(predict_y))
    print("失败单词个数:", len(wrongPredictInfo))
    print("成功率:", count / len(predict_y))