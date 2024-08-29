#include <stdio.h>

// a = 1100'1111
// b = 1111'1100
// c = 0101'0101
// d = 0011'0111
//
// d | c<<8 | b<<16 | a<<24
//
// 1100'1111 0000'0000 0000'0000 0000'0000 |
// 0000'0000 1111'1100 0000'0000 0000'0000 |
// 0000'0000 0000'0000 0101'0101 0000'0000 |
// 0000'0000 0000'0000 0000'0000 0011'0111
//
// 1100'1111 1111'1100 0101'0101 0011'0111 (Form 1)


// algorithm:
// 1) считать и записать 4 числа, проверить на EOF и 4 пустых
// 2) перевести их в инт формата Form 1
// 3) перевести полученный инт в 5 интов как коды перевода в 85 ичную систему
// 4) закодировать каждое число в +33
// 5) вывести эту хуйню как чары в файл
static int QuartetToInt(const int* quartet);

static int IntToFiveBytes(int bytes4, int* bytes5);

int main() {
    int a = 0b110001;
    int b = 0b110001;
    int c = 0b110001;
    int d = 0b110001;
    int quartet[4] = {};
    int bytes5[5] = {};
    quartet[0] = a;
    quartet[1] = b;
    quartet[2] = c;
    quartet[3] = d;
    //int sum_expected = 0b11001111111111000101010100110111;

    printf("a = %d b = %d c = %d d = %d \n", a, b, c, d);

    int sum = QuartetToInt(quartet);
    int symb = IntToFiveBytes(sum, bytes5);

    printf("real = %d %d \n", sum, symb);
}

static int QuartetToInt(const int* quartet) {
    return quartet[3] | quartet[2]<<8 | quartet[1]<<16 | quartet[0]<<24;
}

static int IntToFiveBytes(int bytes4, int* bytes5) {
    int null_symbol_amount = 0;

    for (int i = 0; i < 5; i++) {
        bytes5[4-i] = bytes4 % 85;
        bytes4 = bytes4 / 85;
        if (!bytes5[i]) {
            null_symbol_amount++;
        }
    }

    return null_symbol_amount;
}
