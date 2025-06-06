#include <stdio.h>
#include <stdint.h>
#include <string.h>

//全局变量
int VAR = 0;

// TEA 加密函数
void __attribute__((annotate("bcf igv ibr icall sub split"))) tea_encrypt(uint32_t* v, const uint32_t* k) {
    VAR ++;
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    const uint32_t delta = 0x9e3779b9;
    
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    
    v[0] = v0;
    v[1] = v1;
}

// TEA 解密函数
void __attribute__((annotate("fla igv ibr icall sub split"))) tea_decrypt(uint32_t* v, const uint32_t* k) {
    VAR ++;
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0xC6EF3720; // delta * 32
    const uint32_t delta = 0x9e3779b9;
    
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= delta;
    }
    
    v[0] = v0;
    v[1] = v1;
}

// 打印十六进制数据
void print_hex(const char* label, const uint8_t* data, size_t len) {
    VAR ++;
    printf("%s: ", label);
    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
    }
    printf("\n");
}

int main() {
    // 测试数据 (64位 = 8字节)
    uint8_t plaintext[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t ciphertext[8];
    uint8_t decrypted[8];
    
    // 128位密钥 (16字节)
    const uint32_t key[4] = {
        0x90ABCDEF, 0x12345678, 
        0xFEDCBA09, 0x87654321
    };

    
    // 打印原始数据
    print_hex("Original ", plaintext, sizeof(plaintext));
    
    // 加密
    tea_encrypt((uint32_t*)plaintext, key);
    memcpy(ciphertext, plaintext, sizeof(ciphertext));
    print_hex("Encrypted", ciphertext, sizeof(ciphertext));
    
    // 解密
    tea_decrypt((uint32_t*)ciphertext, key);
    memcpy(decrypted, ciphertext, sizeof(decrypted));
    print_hex("Decrypted", decrypted, sizeof(decrypted));

    printf("GlobalVar: %d\n", VAR);
    return 0;
}