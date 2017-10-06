#！usr/bin/env python
# -*- coding:utf-8 -*-
"""
DES算法
"""
import random

# 初始置换IP
IP = [58, 50, 42, 34, 26, 18, 10, 2, 
      60, 52, 44, 36, 28, 20, 12, 4, 
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7]

# 逆置换IP-1
IP_1 = [40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25]
        
# 8个S盒
S1 = [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
      0, 15, 7, 4, 15, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
      4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
      15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13]

S2 = [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
      3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
      13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9]

S3 = [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
      13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
      13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
      1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12]

S4 = [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
      12, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
      10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
      3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14]

S5 = [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
      14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
      4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
      11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3]

S6 = [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
      10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
      9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
      4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13]

S7 = [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
      13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
      1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
      6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12]

S8 = [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
      1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
      7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
      2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11]

PC1 = [57, 49, 41, 33, 25, 17, 9,
       1, 58, 50, 42, 34, 26, 18,
       10, 2, 59, 51, 43, 35, 27,
       19, 11, 3, 60, 52, 44, 36,
       63, 55, 47, 39, 31, 23, 15,
       7, 62, 54, 46, 38, 30, 22,
       14, 6, 61, 53, 45, 37, 29,
       21, 13, 5, 28, 20, 12, 4]

PC2 = [14, 17, 11, 24, 1, 5,
       3, 28, 15, 6, 21, 10,
       23, 19, 12, 4, 26, 8,
       16, 7, 27, 20, 13, 2,
       41, 52, 31, 37, 47, 55,
       30, 40, 51, 45, 33, 48,
       44, 49, 39, 56, 34, 53,
       46, 42, 50, 36, 29, 32]

EXTENDED_RULE_TABLE = [[32, 5], [4, 9], [8, 13], [12, 17], [16, 21], [20, 25], [24, 29], [28, 1]]

P = [16, 7, 20, 21,
     29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2, 8, 24, 14,
     32, 27, 3, 9,
     19, 13, 30, 6,
     22, 11, 4, 25]

S_BOXS = [S1, S2, S3, S4, S5, S6, S7, S8]   # S盒的集合
IPSIZE = len(IP)                            # 明文块长度
HALFSIZE = IPSIZE / 2                       # 一半数组长度
ITERATION_COUNTERS = 16                     # 迭代次数
S_BOX_NUM = len(S_BOXS)                     # S-盒数量
S_BOX_COLS = 16                             # S-盒列数

def permutate_plain_text_by_IP(plain_text):
    """
    通过IP重排明文块
    """
    return [plain_text[ip_index - 1] for ip_index in IP]

def inverse_permutate_by_IP_1(R_L):
    """
    逆置换IP-1
    """
    return [R_L[i - 1] for i in IP_1]

def permutate_by_P(thiry_two_bit_R):
    """
    32位R逆置换
    """
    return [thiry_two_bit_R[i - 1] for i in P]

def exclsive_or(A, B):
    """
    将A、B两个二进制list按位异或
    """
    return [A[index] ^ B[index] for index in range(len(A))]

def E_extended(R):
    """
    E扩展
    """
    extended_R = []
    for i in range(len(EXTENDED_RULE_TABLE)):
        extended_R.append(R[EXTENDED_RULE_TABLE[i][0] - 1])
        for j in range(4):
            extended_R.append(R[4 * i + j])
        extended_R.append(R[EXTENDED_RULE_TABLE[i][1] - 1])

    return extended_R

def get_PC1_subkey(K):
    """
    对64位的k进行压缩置换得到56位
    """
    return [K[i-1] for i in PC1]

def get_PC2_subkey(K):
    """
    对56位的k进行压缩置换得到48位
    """
    return [K[i-1] for i in PC2]

def move_onebit_subkey(K):
    """
    i = 1,2,9,16 左移一位
    """
    return K[1:] + K[:1]

def move_twobit_subkey(K):
    """
    i ≠ 1,2,9,16 左移两位
    """
    return K[2:] + K[:2]

SUBKEYS = []        # 子密钥集合
def general_subkeys(K):
    """
    生成子密钥
    """
    HALF_SUBKEY_LENGTH = 28
    # 64位K通过PC-2表压缩成56位
    subkey = get_PC1_subkey(K)
    # 获得 C0，D0
    C, D = subkey[:HALF_SUBKEY_LENGTH], subkey[HALF_SUBKEY_LENGTH:]
    # 获得 C1，D1
    for i in range(1, 17):
        if i == 1 or i == 2 or i == 9 or i == 16:
            C, D = move_onebit_subkey(C), move_onebit_subkey(D) # 循环左移一位
        else:
            C, D = move_twobit_subkey(C), move_twobit_subkey(D) # 循环左移两位
        SUBKEYS.append(get_PC2_subkey(C + D))   # 56位K通过PC-2表压缩成48位

def get_subkey(i):
    """
    返回子密钥Ki
    """
    return SUBKEYS[i-1]

def S_box_substitution(R_group, S_BOX):
    """
    S盒替换 R_group6位输入
    """
    row = (R_group[0] << 1) + R_group[5]
    col = 0
    for i in range(3, 6):
        col = (col << 1) + R_group[i]

    demical_output = S_BOX[row * S_BOX_COLS + col]
    binary_output = []
    BINARY_OUTPUT_LEN = 4
    # 10进制转成4位二进制
    for i in range(BINARY_OUTPUT_LEN - 1, -1, -1):
        if demical_output - 2 ** BINARY_OUTPUT_LEN >= 0:
            binary_output.append(1)
            demical_output -= 2 ** BINARY_OUTPUT_LEN
        else:
            binary_output.append(0)
    
    return binary_output

# Ri-1, Ki
def feistel(R, i):
    """
    feistel轮函数，R为长度为32位的Ri-1，i为迭代第i次
    """
    # 1 - 长度为32位的Ri-1作E-扩展，作为48位的串E(Ri-1)
    # 2 - 将E(Ri-1)和长度为48位的子密钥Ki作48位二进制串按位异或运算
    
    t_R = exclsive_or(E_extended(R), get_subkey(i))
    # 3 - 将2得到的结果分成8个长度为6的分组，经过8个不同的S-盒
    #     进行6-4转换，得到8个长度分别为4位的分组
    # 4 - 将分组结果合并成长度为32位的串
    GROUP_LEN = 6
    thiry_two_bit_R = []
    # print("t_R", t_R)
    for i in range(S_BOX_NUM):
        thiry_two_bit_R += S_box_substitution(t_R[GROUP_LEN * i : GROUP_LEN * (i + 1)], S_BOXS[i])
        # print(thiry_two_bit_R)
    
    # 5 - 把32位的串进行P-置换
    return permutate_by_P(thiry_two_bit_R)


def DES_encryption_or_decryption(text, secret_key, is_decrypt):
    """
    对text进行加密或解密，secret_key是密钥，is_decrypt不为0则加密，否则解密
    """
    # IP置换
    deal_text = permutate_plain_text_by_IP(text)
    L, R = deal_text[:int(HALFSIZE)], deal_text[int(HALFSIZE):]

    # 产生子密钥
    general_subkeys(secret_key)

    # 16次迭代
    start, end, interval = 0, ITERATION_COUNTERS, 1
    # 若为解密，反序调用子密钥
    if is_decrypt:
        start, end, interval = ITERATION_COUNTERS - 1, -1, -1
    for i in range(start, end, interval):
        t_L = R
        R = exclsive_or(L, feistel(R, i))
        L = t_L
    # 逆置换IP-1
    return inverse_permutate_by_IP_1(R + L)

def random_generated_key():
    """
    随机产生0~1大小的随机数四舍五入获得0和1，得到密钥list
    """
    return [round(random.random()) for i in range(64)]

# 测试加密
def encrypt_test():
    '''
    读取要加密的明文，随机生成密钥，加密获得密文，默认"utf-8"编码
    plain_text.txt ： 明文
    secret_key.txt ： 密钥
    '''
    # --------------------------读取将加密的明文-------------------------------
    with open("plain_text.txt", "r", encoding="utf-8") as fin:
        read_data = fin.read()
    # 获得密文的16进制的list
    hex_list = list(bytearray(read_data, encoding="utf-8"))
    # 判断密文是不是8字节的倍数，不是则补上缺的位数
    # 假如缺4个字节，则补上4个4；假如缺5，则补上5个5
    # 解密的时候再对应去掉
    hex_list_len = len(hex_list)
    if (hex_list_len % 8):
        lack_num = 8 - hex_list_len % 8
        for i in range(lack_num):
            hex_list.append(lack_num)
    # ---------------------------------------------------------------------------

    # 16进制list--->二进制字符串list--->合并成二进制字符串-->二进制list
    bin_str_list = list(map(lambda x: bin(x)[2:], hex_list))
    for i in range(len(bin_str_list)):
        if len(bin_str_list[i]) < 8:
            bin_str_list[i] = (8 - len(bin_str_list[i])) * '0' + bin_str_list[i]

    bin_list = list(map(lambda x: int(x), list(''.join(bin_str_list))))
    #-------------------------------------------------------------
    
    # ---------------随机生成64位密钥并保存在文件中-------------------
    secret_key = random_generated_key()
    print("secret_key = ", ''.join(list(map(lambda x: str(x), secret_key))))
    with open("secret_key.txt", "w") as fout:
        fout.write(''.join(list(map(lambda x: str(x), secret_key))))
    #-------------------------------------------------------------

    # ---------------对二进制list进行每次分64位进行加密------------------
    ciphertext = []
    for i in range(int(len(bin_list) / 64)):        
        t = DES_encryption_or_decryption(bin_list[i * 64 : (i + 1) * 64], secret_key, 0)
        ciphertext += t
    # 将密文保存进文件中
    with open("ciphertext.txt", "w") as fout:
        for i in ciphertext:
            fout.write(str(i))
    # ----------------------------------------------------------------

# 测试解密
def decrypt_test():
    """"
    根据密文和密钥获得明文，并把结果输出到文件中，默认"utf-8"编码
    secret_key.txt : 密钥
    ciphertext.txt ：密文
    result.txt ：解密结果
    """
    # ------------------------读取密文和对应的密钥------------------------
    with open("secret_key.txt", "r") as fin:
        secret_key = list(map(lambda x: int(x), list(fin.read())))
    
    with open("ciphertext.txt", "r") as fin:
        ciphertext = list(map(lambda x: int(x), list(fin.read())))
    # ----------------------------------------------------------------

    # ------------------每次分64位进行解密获得二进制list--------------------
    bin_list = []
    for i in range(int(len(ciphertext) / 64)):
        t = DES_encryption_or_decryption(ciphertext[i * 64 : (i + 1) * 64], secret_key, 1)
        for i in range(int(len(t) / 8)):
            t = list(map(lambda x: str(x), t))
            bin_list.append(''.join(t[i * 8 : (i + 1) * 8]))
    # ----------------------------------------------------------------
    
    # ------------------将二进制list转成16进制list转成明文--------------------
    hex_list = list(map(lambda x: int(hex(int(x, 2)), 16), bin_list))
    # 获取最后一位数字，判断是否是由于不足8字节而填补上的
    end_num = hex_list[len(hex_list) - 1]
    if end_num < 8:
        for i in range(-end_num, 0, 1):
            if hex_list[i] != end_num:
                break
        else:
            hex_list = hex_list[:-end_num]
    
    # print(bytearray(hex_list).decode("utf-8"))
    with open("result.txt", "w", encoding="utf-8") as fout:
        fout.write(bytearray(hex_list).decode("utf-8"))
    # ----------------------------------------------------------------
    

def test1():
    a = "你好"
    b = list(bytearray(a, encoding="utf-8")) # [228, 189, 160, 229, 165, 189]
    c = bytearray(b).decode("utf-8") # 你好
    d = list(map(lambda x: bin(x)[2:], b))
    # ['11100100', '10111101', '10100000', '11100101', '10100101', '10111101']
    e = list(map(lambda x: int(hex(int(x, 2)), 16), d))
    # [228, 189, 160, 229, 165, 189]

if __name__ == "__main__":
    encrypt_test()
    decrypt_test()