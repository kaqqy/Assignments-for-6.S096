#include <stdio.h>

union float_bits {
    float f;
    unsigned int bits;
};

void print_hex(float f) {
    union float_bits t;

    t.f = f;
    printf("The float looks like 0x%x in hex.\n", t.bits);
}

void print_repr(float f) {
    union float_bits t;

    t.f = f;
    if (t.bits & 1U << 31)
        printf("-");
    printf("1.");
    for (int shift = 22; shift >= 0; shift--)
        printf("%d", !!(t.bits & 1U << shift));
    printf(" * 2^");
    int exponent = (int)(t.bits << 1 >> 24);
    printf("%d\n", exponent - 127);
}

int main() {
    int n;

    scanf("%d", &n);
    while (n--) {
        float f;
        scanf("%f", &f);
        print_repr(f);
    }
    return 0;
}
