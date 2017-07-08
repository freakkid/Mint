# Exercise 1:
# https://www.zhihu.com/question/35122102

def nsqrt(n):
    a, i = 3, 1
    while i + a <= n:
        i += a
        a += 2
    return (a - 1) / 2

# Exercise 2:

def fprime(x):
    return 1.0 + math.log(x)
def f(x):
    return x * math.log(x) - 16.0

"""
x_0: initial guess
EPSILON: stop when abs(x - x_new) < EPSILON
MAX_ITER: maximum number of iteration
"""

def find_root(f, fprime, x_0=1.0, EPSILON=1E-7, MAX_ITER=1000):
    for i in range(MAX_ITER):
        x_0 = x_0 - f(x_0) / fprime(x_0)
    return x_0

x = find_root(f, fprime)
print(x)
print(f(x))

# Exercise 3:
# 从小到大排列，每行num个数字，最大的数字为max
# num个元素 来自 {1,2,3,...,n}

path = []
def comb(n, k):
    if (k == 1):
        return [[i] for i in range(n, 0, -1)]
    else:
        r_list = []
        for i in comb(n, k-1):
            if len(i) == k-1:
                for j in range(1, i[0]):
                    r_list.append([j]+i)
        return r_list
