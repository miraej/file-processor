#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_C2S "/tmp/fifo_c2s"
#define FIFO_S2C "/tmp/fifo_s2c"
#define BUF_SIZE 1024

void reverse_str(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

int count_words(char *str) {
    int words = 0;
    int in_word = 0;

    for (int i = 0; str[i]; i++) {
        if (isspace(str[i])) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            words++;
        }
    }
    return words;
}

void process_line(char *line, char *mode, char *result, int line_num) {
    if (strcmp(mode, "count") == 0) {
        int chars = strlen(line);
        int words = count_words(line);
        sprintf(result, "Line %d: %d chars, %d words", line_num, chars, words);
    }
    else if (strcmp(mode, "upper") == 0) {
        strcpy(result, line);
        for (int i = 0; result[i]; i++) {
            result[i] = toupper(result[i]);
        }
    }
    else if (strcmp(mode, "lower") == 0) {
        strcpy(result, line);
        for (int i = 0; result[i]; i++) {
            result[i] = tolower(result[i]);
        }
    }
    else if (strcmp(mode, "reverse") == 0) {
        strcpy(result, line);
        reverse_str(result);
    }
    else {
        sprintf(result, "Unknown mode: %s", mode);
    }
}

int main() {
    int fd_c2s, fd_s2c;
    char buf[BUF_SIZE];
    char mode[20];
    int line_num = 0;

    unlink(FIFO_C2S);
    unlink(FIFO_S2C);
    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    printf("서버 대기 중...\n");

    fd_c2s = open(FIFO_C2S, O_RDONLY);
    fd_s2c = open(FIFO_S2C, O_WRONLY);

    read(fd_c2s, mode, sizeof(mode));
    printf("처리 모드: %s\n", mode);

    while (1) {
        int n = read(fd_c2s, buf, sizeof(buf));
        if (n <= 0) continue;
        buf[n] = '\0';

        if (strcmp(buf, "END") == 0) {
            break;
        }

        line_num++;
        printf("%d번째 줄 처리 중...\n", line_num);

        char result[BUF_SIZE];
        process_line(buf, mode, result, line_num);
        write(fd_s2c, result, strlen(result));
    }

    printf("서버 종료.\n");

    close(fd_c2s);
    close(fd_s2c);
    unlink(FIFO_C2S);
    unlink(FIFO_S2C);

    return 0;
}