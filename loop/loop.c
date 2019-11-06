#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 100000

ssize_t read(int fd, void *buf, size_t count);

size_t getstr(char **str) {
    size_t chars_to_read = BLOCK_SIZE;
    size_t length = 0;
    size_t alloc_len = chars_to_read + 1;
    size_t chars = 0;

    *str = (char*)malloc(alloc_len * sizeof(**str)); 
    while ((chars = read(0, *str + length, chars_to_read))) {
        length += chars;
        if (length + chars_to_read + 1 > alloc_len) {
            alloc_len = 2 * alloc_len + 1;
            *str = (char*)realloc(*str, alloc_len);
        }
    }
    // string doesn't include newline at the end of the file
    (*str)[length - 1] = '\0';
    return length - 1;
}

void reverse(char *str, size_t len) {
    char temp;

    for (size_t i = 0; 2 * i < len; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void encrypt(char *str, size_t len) {
    if (len <= 2)
        return;
    reverse(str, len / 2);
    reverse(str + len / 2, (len + 1) / 2);
    encrypt(str, len / 2);
    encrypt(str + len / 2, (len + 1) / 2);
}

int main() {
    char *input;
    size_t input_len;

    input_len = getstr(&input);
    encrypt(input, input_len);
    printf("%u\n", input_len);
    printf("%s\n", input);
    return 0;
}
