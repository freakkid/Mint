

def extract_con(strs):
    word_list = strs.split(' ')
    consonant = ['P', 'B', 'CH', 'DH', 'F', 'G', 'HH', 'JH', 'K', 'L', 'M', 'N', 'NG', 'R', 'S', 'SH', 'T', 'TH', 'V', 'W', 'Y', 'Z', 'ZH']
    vol_list=[]       #in case you wanna use it,not sure it's useful or not,
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

