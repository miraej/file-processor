# 프로세스 협력 파일 처리기

### 개요

- 클라이언트-서버 모델을 사용하여 파일의 각 줄 처리

- 클라이언트는 파일의 각 줄을 서버에 전송

- 서버는 지정된 처리 모드에 따라 각 줄을 처리한 후 결과를 클라이언트에 반환

- 처리 모드:

  - count: 문자 수 및 단어 수 계산

  - upper: 대문자로 변환

  - lower: 소문자로 변환

  - reverse: 문자열 뒤집기

- 사용법

```

./file_processor_clnt <input_file> <mode>

```

- <input_file>: 처리할 텍스트 파일의 경로

- <mode>: count, upper, lower, reverse 중 하나

 

## 실행결과

### 클라이언트: count

```

./file_processor_clnt test.txt count

서버 연결 중...
서버 연결 완료!
1번째 줄 전송...
1번째 줄 결과 수신: Line 1: 12 chars, 2 words
2번째 줄 전송...
2번째 줄 결과 수신: Line 2: 20 chars, 5 words
3번째 줄 전송...
3번째 줄 결과 수신: Line 3: 21 chars, 4 words
4번째 줄 전송...
4번째 줄 결과 수신: Line 4: 12 chars, 3 words

=== 처리 통계 ===
처리 모드: count
처리한 줄 수: 4줄
소요 시간: 0.000759초
```

### 클라이언트: upper

```

./file_processor_clnt test.txt upper

서버 연결 중...
서버 연결 완료!
1번째 줄 전송...
1번째 줄 결과 수신: HELLO WORLD!
2번째 줄 전송...
2번째 줄 결과 수신: THIS IS A TEST FILE.
3번째 줄 전송...
3번째 줄 결과 수신: C PROGRAMMING IS FUN.
4번째 줄 전송...
4번째 줄 결과 수신: END OF LINE.

=== 처리 통계 ===
처리 모드: upper
처리한 줄 수: 4줄
소요 시간: 0.000959초
```

 

### 클라이언트: lower

```

./file_processor_clnt test.txt lower

magin@DESKTOP-P3L0JF0:~/sysprg4$ ./file_processor_clnt test.txt lower
서버 연결 중...
서버 연결 완료!
1번째 줄 전송...
1번째 줄 결과 수신: hello world!
2번째 줄 전송...
2번째 줄 결과 수신: this is a test file.
3번째 줄 전송...
3번째 줄 결과 수신: c programming is fun.
4번째 줄 전송...
4번째 줄 결과 수신: end of line.

=== 처리 통계 ===
처리 모드: lower
처리한 줄 수: 4줄
소요 시간: 0.000732초

```

 

### 클라이언트: reverse

```

./file_processor_clnt test.txt reverse
서버 연결 중...
서버 연결 완료!
1번째 줄 전송...
1번째 줄 결과 수신: !dlroW olleH
2번째 줄 전송...
2번째 줄 결과 수신: .elif tseT a si sihT
3번째 줄 전송...
3번째 줄 결과 수신: .nuF si gnimmargorP C
4번째 줄 전송...
4번째 줄 결과 수신: .eniL fo dnE

=== 처리 통계 ===
처리 모드: reverse
처리한 줄 수: 4줄
소요 시간: 0.000668초

```
 

### 서버

```
 ./file_processor_svr
서버 대기 중...
처리 모드: count
1번째 줄 처리 중...
2번째 줄 처리 중...
3번째 줄 처리 중...
4번째 줄 처리 중...
서버 종료.
```
