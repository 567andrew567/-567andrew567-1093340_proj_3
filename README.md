# 1093340_proj_3

## 編譯及執行方式
將cpp檔及test_data資料夾放在同個資料夾底下
### 測試環境
    電腦環境:windows11
    編譯器:g++ (MinGW.org GCC-6.3.0-1) 6.3.0
### 編譯
g++ -g 1093340_proj_3.cpp -o 1093340_proj_3
### 執行

1093340_proj_3 測資路徑\
example:1093340_proj_3 test_data/test.txt

### 執行結果
以test.txt為例
```
ADDI R1 R0 2
ADDI R2 R0 4
MUL R4 R1 R2
ADD R6 R4 R2
SUB R3 R2 R1
DIV R5 R3 R1
MUL R3 R4 R5
----------------------------------------------------
cycle: 1
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
RS2: -
RS3: -

buffer: -

RS4: -
RS5: -

buffer: -

-----------------------------------------------------
cycle: 2
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
RS3: -

buffer: RS1 0 + 2

RS4: -
RS5: -

buffer: -

-----------------------------------------------------
cycle: 3
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
RS1: -
RS2: + 0 4
RS3: -

buffer: RS2 0 + 4

RS4: * 2 RS2
RS5: -

buffer: -

-----------------------------------------------------
cycle: 4
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
R3: -
R4: RS4
R5: -
R6: RS1
R7: -
R8: -
R9: -

RS:
RS1: + RS4 4
RS2: -
RS3: -

buffer: -

RS4: * 2 4
RS5: -

buffer: RS4 2 * 4

-----------------------------------------------------
cycle: 5
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
R3: RS2
R4: RS4
R5: -
R6: RS1
R7: -
R8: -
R9: -

RS:
RS1: + RS4 4
RS2: - 4 2
RS3: -

buffer: -

RS4: * 2 4
RS5: -

buffer: RS4 2 * 4

-----------------------------------------------------
cycle: 6
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
R3: RS2
R4: RS4
R5: RS5
R6: RS1
R7: -
R8: -
R9: -

RS:
RS1: + RS4 4
RS2: - 4 2
RS3: -

buffer: RS2 4 - 2

RS4: * 2 4
RS5: / RS2 2

buffer: RS4 2 * 4

-----------------------------------------------------
cycle: 8
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
R6: RS1
R7: -
R8: -
R9: -

RS:
RS1: + RS4 4
RS2: -
RS3: -

buffer: -

RS4: * 2 4
RS5: / 2 2

buffer: RS4 2 * 4

-----------------------------------------------------
cycle: 14
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
R6: RS1
R7: -
R8: -
R9: -

RS:
RS1: + 8 4
RS2: -
RS3: -

buffer: RS1 8 + 4

RS4: * 8 RS5
RS5: / 2 2

buffer: RS5 2 / 2

-----------------------------------------------------
cycle: 15
RF:
R0: 0
R1: 2
R2: 4
R3: 2
R4: 8
R5: 0
R6: 12
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
RS1: -
RS2: -
RS3: -

buffer: -

RS4: * 8 RS5
RS5: / 2 2

buffer: RS5 2 / 2

-----------------------------------------------------
cycle: 34
RF:
R0: 0
R1: 2
R2: 4
R3: 2
R4: 8
R5: 1
R6: 12
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
RS1: -
RS2: -
RS3: -

buffer: -

RS4: * 8 1
RS5: -

buffer: RS4 8 * 1

-----------------------------------------------------
cycle: 44
RF:
R0: 0
R1: 2
R2: 4
R3: 8
R4: 8
R5: 1
R6: 12
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
RS1: -
RS2: -
RS3: -

buffer: -

RS4: -
RS5: -

buffer: -

-----------------------------------------------------
```
輸出以虛線分割，第一格為從txt讀入的instruction，接著每一格皆為有變化的cycle的情況，RF為register file，數值為register內存的值，
RAT為register allocation table，數值為對應到的RS的編號，若無對應到的RS則為 **-**，
RS前3個為add/addi/sub的暫存，後兩個為mul/div的暫存，第一個buffer為執行前3個rs的alu,第二個則為執行後兩個rs的alu。
