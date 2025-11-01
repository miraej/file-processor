#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>

#define FIFO_C2S "/tmp/fifo_c2s"
#define FIFO_S2C "/tmp/fifo_s2c"
#define BUF_SIZE 1024

void remove_newline(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len-1] == '\n' || str[len-1] == '\r')) {
        str[--len] = '\0';
    }
}

double get_elapsed_time(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) +
           (end.tv_usec - start.tv_usec) / 1000000.0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("사용법: %s <파일명> <모드>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *mode = argv[2];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("파일을 열 수 없습니다: %s\n", filename);
        return 1;
    }

    mkfifo(FIFO_C2S, 0666);
    mkfifo(FIFO_S2C, 0666);

    printf("서버 연결 중...\n");
    int fd_c2s = open(FIFO_C2S, O_WRONLY);
    int fd_s2c = open(FIFO_S2C, O_RDONLY);
    printf("서버 연결 완료!\n");

    write(fd_c2s, mode, strlen(mode));
    usleep(10000);

    char buf[BUF_SIZE];
    char result[BUF_SIZE];
    int line_count = 0;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    while (fgets(buf, sizeof(buf), fp)) {
        remove_newline(buf);

        if (strlen(buf) == 0) continue;

        line_count++;
        printf("%d번째 줄 전송...\n", line_count);

        write(fd_c2s, buf, strlen(buf) + 1);

        int n = read(fd_s2c, result, sizeof(result) - 1);
        result[n] = '\0';

        printf("결과: %s\n", result);
    }

    write(fd_c2s, "END", 4);

    gettimeofday(&end, NULL);
    double elapsed = get_elapsed_time(start, end);

    printf("\n=== 처리 통계 ===\n");
    printf("처리 모드: %s\n", mode);
    printf("처리한 줄 수: %d줄\n", line_count);
    printf("소요 시간: %.6f초\n", elapsed);

    fclose(fp);
    close(fd_c2s);
    close(fd_s2c);

    return 0;
}