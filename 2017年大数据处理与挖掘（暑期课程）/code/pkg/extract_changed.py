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
    vol_number = len(vol_list)

    head_tails = []
    for x in range(len(word_list[0])):
        if word_list[0][x] == ':':
            head_tails = head_and_tails(word_list[0][:x])


    feature = {'vol_number':vol_number}
    for x in allvol:
        if vol_list.count(x) == 0:
            feature[x] = -1
        else:
            feature[x] = vol_list.index(x)

    for i in range(6):
        if head_tails[i]==1:
            feature['ht'+str(i)]=True
        else:
            feature['ht'+str(i)]=False

    return feature

#function below returns a array that contain infomation about prefix and postfix of word
def head_and_tails(word):
    #第二音节
    head = ['A','AB','AC','AD','AL','BE','CON','DE','DIS','IM','IN','EM','EN','FOR','PRE',
    'PRO','TO','TRANS','MIS','RE','TANS','UN']
    #第二音节
    tail1 = ['AIM','AIN','CUR', 'EEM', 'DUCE','ERE','FIRM','GN','OIN','OKE','OSE','PT','RCE','SELF','UME']
    #重音位置和原词重音位置一样
    tail2 = ['AL','ACY','AGE','ER','OR','FUL','ISM','IST','IVE','IZE','LESS','ISE','LY','NESS','SHIP','ING','RY','TY']
    #重音落到末音节
    tail3 = ['ADE','ETTE','EE','ESE','QUE','AAR','EER','ZEE','ROO']
    #倒数第二音节
    tail4 = ['IC','ION','ANA','ESCENT','ESCENCE','I','ICS','SIS','ID','INTREPID','INSIPID']
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
