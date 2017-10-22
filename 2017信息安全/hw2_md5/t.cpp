#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

const uint32_t T[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

const int S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
    5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

// 不同生成函数的字符串定位
#define F_WORDS_ORDER(i) i
#define G_WORDS_ORDER(i) (1+5*i)%16
#define H_WORDS_ORDER(i) (5+3*i)%16
#define I_WORDS_ORDER(i) (7*i)%16

typedef uint32_t generate_func(uint32_t, uint32_t, uint32_t);

uint32_t F(uint32_t b, uint32_t c, uint32_t d) {
    return (b & c) | ((~b) & d);
}

uint32_t G(uint32_t b, uint32_t c, uint32_t d) {
    return (b & d) | (c & (~d));
}

uint32_t H(uint32_t b, uint32_t c, uint32_t d) {
    return b ^ c ^ d;
}

uint32_t I(uint32_t b, uint32_t c, uint32_t d) {
    return c ^ (b | (~d));
}

uint32_t left_rotate(const uint32_t val, const int shift) {
    return ((val << shift) | (val >> (32 - shift)));    
}

uint32_t generate_function(generate_func gf, const uint32_t *CV) {
    return CV[0] + gf(CV[1], CV[2], CV[3]);
}

void display_CV(const uint32_t *t_CV) {
    for (int j = 0; j < 4; j++) {
        printf("%u", t_CV[j]);
    }
    putchar('\n');
}

void swap_CV(uint32_t *CV, const uint32_t a) {
    CV[0] = CV[3];
    CV[3] = CV[2];
    CV[2] = CV[1];
    CV[1] = a;
}

uint32_t generate_CV_first_one(generate_func gf, const uint32_t *CV, const uint32_t word, const int loop) {  
    return CV[1] + left_rotate(generate_function(gf, CV) + word + T[loop], S[loop]);
}

uint32_t F_loop(uint32_t *CV, const uint32_t* words) {
    for (int i = 0; i < 16; i++) {
        uint32_t a = generate_CV_first_one(F, CV, words[F_WORDS_ORDER(i)], i);
        swap_CV(CV, a);
    }
}

uint32_t G_loop(uint32_t *CV, const uint32_t* words) {
    for (int i = 16; i < 32; i++) {
        uint32_t a = generate_CV_first_one(G, CV, words[G_WORDS_ORDER(i)], i);
        swap_CV(CV, a);
    }
}

uint32_t H_loop(uint32_t *CV, const uint32_t* words) {
    for (int i = 32; i < 48; i++) {
        uint32_t a = generate_CV_first_one(H, CV, words[H_WORDS_ORDER(i)], i);
        swap_CV(CV, a);
    }
}

uint32_t I_loop(uint32_t *CV, const uint32_t* words) {
    for (int i = 48; i < 64; i++) {
        uint32_t a = generate_CV_first_one(I, CV, words[I_WORDS_ORDER(i)], i);
        swap_CV(CV, a);
    }
}
// 获得填充后新字符串长度
int get_padding_size(const int plaintext_size) {
    int plaintext_bit_size = plaintext_size * 8;
    for (int i = 0; ; i++) {
        if ((448 + 512 * i - plaintext_bit_size) > 0) {
            return (448 + 512 * i) / 8 + 8;
        }
    }
}

void uint_to_bytes(const uint32_t val, uint8_t *bytes) {
    bytes[3] = (uint8_t)(val >> 24);
    bytes[2] = (uint8_t)(val >> 16);
    bytes[1] = (uint8_t)(val >> 8);
    bytes[0] = (uint8_t)val;
}

uint32_t bytes_to_uint(uint8_t *bytes) {
    return (uint32_t) bytes[0]
    | ((uint32_t) bytes[1] << 8)
    | ((uint32_t) bytes[2] << 16)
    | ((uint32_t) bytes[3] << 24);
}

void copy_text(const uint8_t *text, uint8_t *new_text, const uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
        new_text[i] = text[i];
    }
}

void copy_CV(uint32_t *t_CV, const uint32_t *CV) {
    for (int i = 0; i < 4; i++) {
        t_CV[i] = CV[i];
    }
}

void add_CV(uint32_t *CV, const uint32_t *t_CV) {
    for (int i = 0; i < 4; i++) {
        CV[i] += t_CV[i];
    }
}

void md5(const uint8_t *text, const uint64_t size, uint32_t *result) {
    // --------------填充------------
    uint64_t new_size = get_padding_size(size);
    uint8_t *new_text = new uint8_t[new_size]();            // 初始化全为0
    copy_text(text, new_text, size);                        // 复制字符串
    new_text[size] = uint8_t(1 << 7);                       // 填充1
    uint_to_bytes(size * 8, new_text + new_size - 8);       // 填充原字符串长度低位
    uint_to_bytes((size * 8) >> 32, new_text + new_size);   // 填充原字符串长度高位
    // ------------------------------
    // CV初始值
    uint32_t CV[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    // 每512位一组
    for (int i = 0; (i * 512 / 8) < new_size; i++) {
        uint32_t t_CV[4];
        copy_CV(t_CV, CV);
        // 每512位可以分成16个32位的字
        uint32_t words[16];
        for (int j = 0; j < 16; j++) {
            words[j] = bytes_to_uint(new_text + (i * 512 / 8) + j * 4);
        }
        // 4个不同循环
        F_loop(t_CV, words);
        G_loop(t_CV, words);
        H_loop(t_CV, words);
        I_loop(t_CV, words);
        add_CV(CV, t_CV);
    }
    delete [] new_text;
    copy_CV(result, CV);
}
 


int main() {
    string text;
    cin >> text;
    uint32_t CV[4];    
    md5((uint8_t *)text.c_str(), text.size(), CV);
    // 输出结果
    uint8_t result[4][4];
    for (int i = 0; i < 4; i++) {
        uint_to_bytes(CV[i], result[i]);
        for (int j = 0; j < 4; j++)
            printf("%02x", result[i][j]);
    }
    putchar('\n');
    
}