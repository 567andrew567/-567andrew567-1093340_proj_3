# 567andrew567-1093340_proj_3

## 編譯及執行方式
將cpp檔及test_data資料夾放在同個資料夾底下
### 測試環境
    電腦環境:windows11
    編譯器:g++ (MinGW.org GCC-6.3.0-1) 6.3.0
### 編譯
g++ -g 1093340_proj_3.cpp -o 1093340_proj_3
### 執行

###執行結果

```
ADDI R1 R0 2
ADDI R2 R0 4
MUL R4 R1 R2
SUB R3 R2 R1
DIV R5 R3 R1
MUL R3 R4 R1
cycle 1
RF:
R0: 0
R1: 0
R2: 0
R3: 0
R4: 0
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: RS1
R2: -
R3: -
R4: -
R5: -
R6: -
R7: -
R8: -
R9: -

RS:
RS1: + 0 2
RS2: empty
RS3: empty

buffer: empty

RS4: empty
RS5: empty

buffer: empty

-----------------------------------------------------
cycle 2
RF:
R0: 0
R1: 0
R2: 0
R3: 0
R4: 0
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: RS1
R2: RS2
R3: -
R4: -
R5: -
R6: -
R7: -
R8: -
R9: -

RS:
RS1: + 0 2
RS2: + 0 4
RS3: empty

buffer: RS1 0 + 2

RS4: empty
RS5: empty

buffer: empty

-----------------------------------------------------
cycle 3
RF:
R0: 0
R1: 2
R2: 0
R3: 0
R4: 0
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: RS2
R3: -
R4: RS4
R5: -
R6: -
R7: -
R8: -
R9: -

RS:
RS1: empty
RS2: + 0 4
RS3: empty

buffer: RS2 0 + 4

RS4: * 2 RS2
RS5: empty

buffer: empty

-----------------------------------------------------
cycle 4
RF:
R0: 0
R1: 2
R2: 4
R3: 0
R4: 0
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: -
R3: RS1
R4: RS4
R5: -
R6: -
R7: -
R8: -
R9: -

RS:
RS1: - 4 2
RS2: empty
RS3: empty

buffer: empty

RS4: * 2 4
RS5: empty

buffer: RS4 2 * 4

-----------------------------------------------------
cycle 5
RF:
R0: 0
R1: 2
R2: 4
R3: 0
R4: 0
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: -
R3: RS1
R4: RS4
R5: RS5
R6: -
R7: -
R8: -
R9: -

RS:
RS1: - 4 2
RS2: empty
RS3: empty

buffer: RS1 4 - 2

RS4: * 2 4
RS5: / RS1 2

buffer: RS4 2 * 4

-----------------------------------------------------
cycle 7
RF:
R0: 0
R1: 2
R2: 4
R3: 2
R4: 0
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: -
R3: -
R4: RS4
R5: RS5
R6: -
R7: -
R8: -
R9: -

RS:
RS1: empty
RS2: empty
RS3: empty

buffer: empty

RS4: * 2 4
RS5: / 2 2

buffer: RS4 2 * 4

-----------------------------------------------------
cycle 14
RF:
R0: 0
R1: 2
R2: 4
R3: 2
R4: 8
R5: 0
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: -
R3: RS4
R4: -
R5: RS5
R6: -
R7: -
R8: -
R9: -

RS:
RS1: empty
RS2: empty
RS3: empty

buffer: empty

RS4: * 8 2
RS5: / 2 2

buffer: RS5 2 / 2

-----------------------------------------------------
cycle 34
RF:
R0: 0
R1: 2
R2: 4
R3: 2
R4: 8
R5: 1
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: -
R3: RS4
R4: -
R5: -
R6: -
R7: -
R8: -
R9: -

RS:
RS1: empty
RS2: empty
RS3: empty

buffer: empty

RS4: * 8 2
RS5: empty

buffer: RS4 8 * 2

-----------------------------------------------------
cycle 44
RF:
R0: 0
R1: 2
R2: 4
R3: 16
R4: 8
R5: 1
R6: 0
R7: 0
R8: 0
R9: 0

RAT:
R0: -
R1: -
R2: -
R3: -
R4: -
R5: -
R6: -
R7: -
R8: -
R9: -

RS:
RS1: empty
RS2: empty
RS3: empty

buffer: empty

RS4: empty
RS5: empty

buffer: empty

-----------------------------------------------------
```
