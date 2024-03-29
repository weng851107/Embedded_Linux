# 目錄

- [Note](#0)
- [01_Hello程序](#1)
  - [1-1_NFS應用](#1.1)
  - [1-2_配置交叉編譯工具鏈](#1.2)
- [02_GCC](#2)
  - [2-1_GCC編譯過程](#2.1)
  - [2-2_GCC常用選項](#2.2)
- [03_Makefile](#3)
- [04_文件IO](#4)
  - [4-1_文件IO_讀寫文件](#4.1)
  - [4-2_文件IO_內核接口](#4.2)
- [05_Framebuffer](#5)
  - [5-1_Framebuffer應用編程](#5.1)
- [06_字符應用](#6)
  - [6-1_字符的編碼方式](#6.1)
  - [6-2_ASCII字符的點陣顯示](#6.2)
  - [6-3_中文字符的點陣顯示](#6.3)
  - [6-4_手動交叉編譯程序_以freetype為例](#6.4)
  - [6-5_使用freetype顯示單個文字](#6.5)
  - [6-6_使用freetype顯示一行文字](#6.6)
- [07_輸入系統](#7)
  - [7-1_輸入系統框架及調試](#7.1)
  - [7-2_現場編程讀取獲取輸入設備信息](#7.2)
  - [7-3_查詢與休眠喚醒的方式讀取輸入數據](#7.3)
  - [7-4_POLL或SELECT的方式讀取輸入數據](#7.4)
  - [7-5_異步通知的方式讀取輸入數據](#7.5)
  - [7-6_電阻屏與電容屏](#7.6)
  - [7-7_tslib框架分析](#7.7)
  - [7-8_tslib交叉編譯與測試](#7.8)
  - [7-9_編寫基於tslib的測試程序](#7.9)
- [08_網路相關簡介](#8)
  - [8-1_網路編程概念](#8.1)
  - [8-2_TCP編程範例](#8.2)
  - [8-3_UDP編程範例](#8.3)
- [09_多線程編程](#9)
- [10_UART串口介紹](#10)
  - [10-1_串口應用程序編程介紹](#10.1)
  - [10-2_UART硬件介紹](#10.2)
  - [10-3_TTY體系中設備節點的差別](#10.3)
  - [10-4_TTY驅動程序框架](#10.4)
  - [10-5_串口(UART)應用編程](#10.5)
- [11_I2C介紹](#11)
  - [11-1_I2C應用程序編程介紹](#11.1)
  - [11-2_I2C協議](#11.2)
  - [11-3_SMBus協議](#11.3)
  - [11-4_I2C系統的重要結構體](#11.4)
  - [11-5_無須編寫驅動直接訪問設備_I2C-tool](#11.5)
  - [11-6_編寫APP直接訪問EEPROM](#11.6)


<h1 id="0">Note</h1>

[[第4篇]_嵌入式Linux應用開發基礎知識](https://www.bilibili.com/video/BV1kk4y117Tu?vd_source=790c8244dbe879457094c8374beb04d3)

<h1 id="1">01_Hello程序</h1>

```C
#include <stdio.h>

/* 执行命令: ./hello weidongshan 
 * argc = 2
 * argv[0] = ./hello
 * argv[1] = weidongshan
 */

int main(int argc, char **argv)
{
    if (argc >= 2)
        printf("Hello, %s!\n", argv[1]);
    else
        printf("Hello, world!\n");
    return 0;
}
```

- argc：argument conut 參數個數
- argv：argument value 代表參數值

- header file (.h)： 作為聲明(declare)
- source file (.c)： 作為定義(define)與實現(implement)

- 函式庫目錄定義分為兩種：
  - 系統目錄
  - 指定目錄

<h2 id="1.1">1-1_NFS應用</h2>

- 利用 NFS 來使 Ubuntu 與 開發版 之間傳輸檔案

- 將Ubuntu中的某目錄下掛載到開發版的某個路徑下，在同一個網域下時

    ```Shell
    mount -t nfs -o nolock,vers=3 192.168.1.137:/home/book/nfs_rootfs /mnt
    ```

    ![img00](./[第4篇]_嵌入式Linux應用開發基礎知識/img00.PNG)

- 但注意要在開發版執行的執行檔要用arm-gcc工具鏈去編譯

    ```Shell
    # PC機編譯器時用的命令是：
    gcc  -o  hello  hello.c

    # 開發板編譯器時用的命令類似下述命令(不同的開發板gcc的首碼可能不同)：
    arm-buildroot-linux-gnueabihf-gcc  -o  hello  hello.c
    ```

- 可以使用 `file` 來查看執行檔

```Shell
chicony@ubuntu:/mnt/disk2/SF/tmp/source/01_hello$ file hello
hello: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=d5e79a0a04b6cadd3272cd37627d4d7147b89f96, not stripped
```

<h2 id="1.1">1-2_配置交叉編譯工具鏈</h2>

- 交叉編譯工具鏈用來在Ubuntu主機上編譯應用程式，而這些應用程式是在ARM等其他平臺上運行。

- 設置交叉編譯工具主要是設置PATH， ARCH和CROSS_COMPILE三個環境變數

**永久生效**

- 修改使用者設定檔

    ```Shell
    book@100ask:~$ vim  ~/.bashrc

    # 在行尾添加或修改，加上下面幾行：
    export ARCH=arm
    export CROSS_COMPILE=arm-buildroot-linux-gnueabihf-
    export PATH=$PATH:/home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin

    # 載入這些設置的環境變數
    book@100ask:~$ source  ~/.bashrc
    ```

**臨時生效**

- 手工執行 `export` 命令設置環境變數，該設置只對當前終端有效(另開一個終端需要再次設置)

    ```Shell
    book@100ask:~$ export ARCH=arm
    book@100ask:~$ export CROSS_COMPILE=arm-buildroot-linux-gnueabihf-
    book@100ask:~$ export PATH=$PATH:/home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin
    ```

**手動指定**

- 先設置**PATH環境變數**，
  
- 在make編譯時指定**ARCH架構**與**CROSS_COMPILE交叉編譯工具鏈**(執行make命令時指定的參數，只對當前命令有效；下次執行make時仍需要再次指定那些參數)。

    ```Shell
    book@100ask:~$ export PATH=$PATH:/home/book/100ask_stm32mp157_pro-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin
    book@100ask:~$ make ARCH=arm CROSS_COMPILE=arm-buildroot-linux-gnueabihf-
    ```

---

![img13](./[第4篇]_嵌入式Linux應用開發基礎知識/img13.PNG)

怎麼確定交叉編譯器中標頭檔的預設路徑?

- 進入交叉編譯器的目錄裡，執行：`find . -name "stdio.h"`，它位於一個 `include` 目錄下的根目錄裡。

怎麼自己指定標頭檔目錄?

- 編譯時，加上 `-I <標頭檔目錄>` 這樣的選項。

怎麼確定交叉編譯器中庫檔的預設路徑?

- 進入交叉編譯器的目錄裡，執行：`find . -name lib`，可以得到xxxx/lib、xxxx/usr/lib，一般來說這2個目錄就是要找的路徑。
- 如果有很多類似的lib，進去看看，有很多so檔的目錄一般就是要找的路徑。

怎麼自己指定庫檔目錄、指定要用的庫檔?

- 編譯時，加上 `-L <庫檔目錄>` 這樣的選項，用來指定庫目錄
- 編譯時，加上 `-labc` 這樣的選項，用來指定庫檔libabc.so。

<h1 id="2">02_GCC</h1>

<h2 id="2.1">2-1_GCC編譯過程</h2>

機器只能讀取機器碼(即二進制的程式，非0即1)

程式的成長流程

![img01](./[第4篇]_嵌入式Linux應用開發基礎知識/img01.PNG)

`gcc -o hello hello.c` 所完成的動作

- 可透過加`-v`來查看流程跑了什麼，`gcc -o hello hello.c -v`

    ![img02](./[第4篇]_嵌入式Linux應用開發基礎知識/img02.PNG)

GCC編譯過程

![img03](./[第4篇]_嵌入式Linux應用開發基礎知識/img03.PNG)

日常說法會把 `編譯` 代表成 `預處理 -> 編譯 -> 匯編`，接著再鏈結

1. 預處理

    C/C++原始檔案中，以 `#` 開頭的命令被稱為預處理命令，如包含命令`#include`、巨集定義命令`#define`、條件編譯命令`#if`、`#ifdef`等。預處理就是將要包含(include)的檔插入原文件中、將巨集定義展開、根據條件編譯命令選擇要使用的代碼，最後將這些東西輸出到一個`.i`檔中等待進一步處理。

2. 編譯

    編譯就是把C/C++代碼(比如上述的`.i`文件)翻譯成彙編代碼，所用到的工具為cc1(它的名字就是cc1，x86有自己的cc1命令，ARM板也有自己的cc1命令)。

3. 彙編

    彙編就是將第二步輸出的彙編代碼翻譯成符合一定格式的機器代碼，在Linux系統上一般表現為ELF目的檔案(OBJ檔)，用到的工具為as。x86有自己的as命令，ARM版也有自己的as命令，也可能是xxxx-as（比如arm-linux-as）。

4. 連結

    連結就是將上步生成的OBJ檔和系統庫的OBJ檔、庫檔連結起來，最終生成了可以在特定平臺運行的可執行檔，用到的工具為ld或collect2。

<h2 id="2.2">2-2_GCC常用選項</h2>

multi-files 進行編譯：各自匯編成.o檔後，鏈結成一個執行檔

```Shell
gcc -o test main.c sub.c
```

![img04](./[第4篇]_嵌入式Linux應用開發基礎知識/img04.PNG)

當今天有999個文件時，使用這種方式，只要修改一個檔案後，每次重新編譯都會重新編譯999個文件，因此會太消耗資源，所以要先編譯在鏈結，就可以避免掉沒有修改的程式要再重新編譯，較為高效

![img05](./[第4篇]_嵌入式Linux應用開發基礎知識/img05.PNG)

**GCC常用選項**

![img06](./[第4篇]_嵌入式Linux應用開發基礎知識/img06.PNG)

1. `-c`

    預處理、編譯和彙編原始檔案，但是不作連結，編譯器根據原始檔案生成OBJ檔。缺省情況下，GCC通過用`.o替換原始檔案名的尾碼.c，.i，.s`等，產生OBJ檔案名。可以使用-o選項選擇其他名字。GCC忽略-c選項後面任何無法識別的輸入檔。

2. `-S`

    編譯後即停止，不進行彙編。對於每個輸入的非組合語言檔，輸出結果是組合語言檔。缺省情況下，GCC通過用`.s替換原始檔案名尾碼.c, .i`等等，產生彙編檔案名。可以使用-o選項選擇其他名字。GCC忽略任何不需要彙編的輸入檔。

3. `-E`

    預處理後即停止，不進行編譯。預處理後的代碼送往標準輸出。

4. `-o file`

    指定輸出檔為file。無論是預處理、編譯、彙編還是連結，這個選項都可以使用。如果沒有使用`-o`選項，預設的輸出結果是：可執行檔為`a.out`；修改輸入檔的名稱是`source.suffix`，則它的OBJ文件是`source.o`，彙編文件是 `source.s`，而預處理後的C原始程式碼送往標準輸出。

5. `-v`

    顯示製作GCC工具自身時的配置命令；同時顯示編譯器驅動程式、前置處理器、編譯器的版本號。

**指定 C標準(C Standard) 的版本：**

```bash
$ gcc -Wall -g -std=c11 -o program source.c
```

GCC 中常見的C 語言標準：

- c89 或c90 或-ansi
- c99
- c11
- c17 或c18

除此之外，還可以加上GNU 特有的extension：

- gnu89 或gnu90：c89 加上GNU C extension
- gnu99：c99 加上GNU C extension
- gnu11：c11 加上GNU C extension
- gnu17：c17 加上GNU C extension

**警告選項(Warning Option)：**

[Options to Request or Suppress Warnings](https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html#index-Wunused-variable-Werror=unused-variable%1B]8)

`-Wall`

這個選項基本打開了所有需要注意的警告資訊，比如沒有指定類型的聲明、在聲明之前就使用的函數、區域變數除了聲明就沒再使用等。

```bash
gcc -Wall -c main.c
```

`-w`: Inhibit all warning messages

`-Werror`: Make all warnings into errors

**調試選項(Debugging Option)：**

`-g` 選項加入只有GDB才使用的額外調試資訊。

**優化選項(Optimization Option)：**

1. `-O或-O1`

    不使用`-O`或`-O1`選項時，只有聲明了register的變數才分配使用寄存器。
    使用了`-O`或`-O1`選項，編譯器會試圖減少目的碼的大小和執行時間。

2. `-O2`

    多優化一些。除了涉及空間和速度交換的優化選項，執行幾乎所有的優化工作。

3. `-O3`

    優化的更多。除了打開-O2所做的一切，它還打開了`-finline-functions`選項。

4. `-O0`

    不優化。

**連結器選項(Linker Option)：**

下面的選項用於連結OBJ檔，輸出可執行檔或庫檔。

1. `-nostartfiles`

    不連結系統標準開機檔案，而標準庫檔仍然正常使用：

    ```bash
    $ gcc -v -nostartfiles -o test main.o sub.o

    /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/collect2 --eh-frame-hdr -m elf_i386 -dynamic-linker 
    /lib/ld-linux.so.2 
    -o test 
    -L/usr/lib/gcc-lib/i386-redhat-linux/3.2.2 
    -L/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/../../.. 
    main.o 
    sub.o 
    -lgcc -lgcc_eh -lc -lgcc -lgcc_eh
    /usr/bin/ld: warning: cannot find entry symbol _start; defaulting to 08048184
    ```

    對於一般應用程式，這些開機檔案是必需的，這裡僅是作為例子(這樣編譯出來的test檔無法執行)。在編譯**bootloader**、**內核**時，將用到這個選項。

2. `-nostdlib`

    不連結系統標準開機檔案和標準庫檔，只把指定的檔傳遞給連結器。這個選項常用於**編譯內核、bootloader**等程式，它們不需要開機

    ```bash
    $ gcc -v -nostdlib -o test main.o sub.o

    /usr/lib/gcc-lib/i386-redhat-linux/3.2.2/collect2 --eh-frame-hdr -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 
    -o test 
    -L/usr/lib/gcc-lib/i386-redhat-linux/3.2.2 
    -L/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/../../.. 
    main.o 
    sub.o
    /usr/bin/ld: warning: cannot find entry symbol _start; defaulting to 08048074
    main.o(.text+0x19): In function `main':
    : undefined reference to `printf'
    sub.o(.text+0xf): In function `sub_fun':
    : undefined reference to `printf'
    collect2: ld returned 1 exit status
    ```

    出現了一大堆錯誤，因為printf等函數是在庫檔中實現的。

3. `-static`

    在支援動態連結(dynamic linking)的系統上，阻止連結共用庫。

    仍以options程式為例，是否使用-static選項編譯出來的可執行程式大小相差巨大：

    ```bash
    $ gcc -c -o main.c
    $ gcc -c -o sub.c
    $ gcc -o test main.o sub.o
    $ gcc -o test_static main.o sub.o –static
    $ ls -l test test_static
    -rwxr-xr-x 1 book book   6591 Jan 16 23:51 test
    -rwxr-xr-x 1 book book 546479 Jan 16 23:51 test_static
    ```

    其中test檔為6591位元組，test_static檔為546479位元組。當不使用-static編譯檔時，程式執行前要連結共用庫檔，所以還需要將共用庫檔放入檔案系統中。

4. `-shared`

    生成一個共用OBJ檔，它可以和其他OBJ檔連結產生可執行檔。只有部分系統支援該選項。

    當不想以原始程式碼發佈程式時，可以使用-shared選項生成庫檔，比如對於options程式，可以如下製作庫檔：

    ```bash
    $ gcc -c -o sub.o sub.c
    $ gcc -shared -o libsub.so sub.o
    ```

    以後要使用sub.c中的函數sub_fun時，在連結程式時，指定引腳libsub.so即可，比如：

    ```bash
    $ gcc -o test main.o  -lsub  -L /libsub.so/所在的目錄/
    ```

    可以將多個檔製作為一個庫檔，比如：

    ```bash
    gcc -shared  -o libsub.so  sub.o  sub2.o  sub3.o
    ```

**加入額外的函式庫：**

除了少數內建的函式庫以外，編譯時要加入相關的參數

- -lm：連結math.h
- -lstdc++：混合編譯C 和C++ 程式碼時需連結的函式庫
- -lpthread：連結GNU/Linux 的多執行緒函式庫
- -lrt：連結POSIX 運行期函式庫
- -ldl：連結動態函式函式庫

```bash
$ gcc -Wall -g -o program source.c -lm
```

**目錄選項(Directory Option)：**

下列選項指定搜索路徑，用於查找標頭檔，庫檔，或編譯器的某些成員。

1. `-Idir`

    在標頭檔的搜索路徑清單中添加dir 目錄。

    如果以 `#include < >` 包含檔，則只在標準庫目錄開始搜索(包括使用-Idir選項定義的目錄)

    如果以 `#include " "` 包含檔，則先從使用者的工作目錄開始搜索，再搜索標準庫目錄

2. `-Ldir`

    在 `-l` 選項的搜索路徑清單中添加dir目錄。

    仍使用options程式進行說明，先製作庫檔libsub.a：

    ```bash
    $ gcc -c -o sub.o sub.c
    $ gcc -shared -o libsub.a sub.o
    ```

    編譯main.c：

    ```bash
    $ gcc  -c -o  main.o  main.c
    ```

    連結程式，下面的指令將出錯，提示找不到庫檔：

    ```bash
    $ gcc  -o  test  main.o  -lsub
    /usr/bin/ld: cannot find -lsub
    collect2: ld returned 1 exit status
    ```

    可以使用-Ldir選項將目前的目錄加入搜索路徑，如下則連結成功：

    ```bash
    $ gcc -L. -o test main.o -lsub
    ```

**ld/objdump/objcopy選項：**

我們在開發APP時，一般不需要直接調用這3個命令；在開發裸機、bootloader時，或是調試APP時會涉及，到時再講。

**靜態庫：**

![img128](./[第4篇]_嵌入式Linux應用開發基礎知識/img128.PNG)

![img07](./[第4篇]_嵌入式Linux應用開發基礎知識/img07.PNG)

**動態庫：**

![img129](./[第4篇]_嵌入式Linux應用開發基礎知識/img129.PNG)

![img08](./[第4篇]_嵌入式Linux應用開發基礎知識/img08.PNG)

總結

![img09](./[第4篇]_嵌入式Linux應用開發基礎知識/img09.PNG)
 
![img10](./[第4篇]_嵌入式Linux應用開發基礎知識/img10.PNG)

<h1 id="3">03_Makefile</h1>

https://github.com/weng851107/Makefile

<h1 id="4">04_文件IO</h1>

在Linux系統中，一切都是 `文件`：普通文件、驅動程序、網絡通信等等。所有的操作，都是通過 `文件IO` 來操作的。所以，很有必要掌握文件操作的常用接口。

應用程序透過接口來訪問普通文件或硬件

![img15](./[第4篇]_嵌入式Linux應用開發基礎知識/img15.PNG)

文件從哪裡來?

- 真實硬件文件
- 內核虛擬文件
- 特殊文件(字符設備、塊設備與網路設備)

![img14](./[第4篇]_嵌入式Linux應用開發基礎知識/img14.PNG)

主設備號代表驅動，次設備號代表設備

![img16](./[第4篇]_嵌入式Linux應用開發基礎知識/img16.PNG)

如何知道這些函數的用法?

- `help` 只能用於查看某個命令的用法
- `man手冊` 既可以查看命令的用法，還可以查看函數的詳細介紹等等。它含有9大分類，如下：

    ```
    1   Executable programs or shell commands                       // 命令
    2   System calls (functions provided by the kernel)             // 系统调用，比如 man 2 open
    3   Library calls (functions within program libraries)          // 函数库调用
    4   Special files (usually found in /dev)                       // 特殊文件, 比如 man 4 tty 
    5   File formats and conventions eg /etc/passwd                 // 文件格式和约定, 比如man 5 passwd
    6   Games                                                       // 游戏
    7   Miscellaneous (including macro packages and conventions), e.g. man(7), groff(7) //杂项
    8   System administration commands (usually only for root)      // 系统管理命令
    9   Kernel routines [Non standard]                              // 内核例程
    ```

<h2 id="4.1">4-1_文件IO_讀寫文件</h2>

標準Read/Write IO讀寫文件

[copy.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/06_fileio/copy.c)

透過系統調用mmap映射來讀寫文件

[copy_mmap.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/06_fileio/copy_mmap.c)

Note: 可以使用 `man 2 open` 來查看open的使用方式

<h2 id="4.2">4-2_文件IO_內核接口</h2>

應用程序透過系統調用接口來調用內核

![img17](./[第4篇]_嵌入式Linux應用開發基礎知識/img17.PNG)

APP透過系統調用函數執行swi, svc指令，來觸發CPU異常，進而導致CPU跳到某地址執行某函數，如此達成調用內核函數

![img18](./[第4篇]_嵌入式Linux應用開發基礎知識/img18.PNG)

系統調用函數怎麼進入內核?

- swi指令(ABI, Application Binary Interface)
- svc指令(ARM64)

![img19](./[第4篇]_嵌入式Linux應用開發基礎知識/img19.PNG)

內核的`sys_open`、`sys_read`會做什麼?

- 首先要分辨文件類型
- 普通文件會以FAT32/EXT4/...保存在塊設備上
- 字符設備

![img20](./[第4篇]_嵌入式Linux應用開發基礎知識/img20.PNG)

<h1 id="5">05_Framebuffer</h1>

<h2 id="5.1">5-1_Framebuffer應用編程</h2>

### LCD 簡介

在Linux系統中通過Framebuffer驅動程序來控制LCD。

Frame是幀的意思，buffer是緩衝的意思，這意味Framebuffer是一塊內存，裡面保存著一幀影像的每一個像素的顏色值

假設LCD的解析度是1024x768，每一個像素的顏色用32位來表示，那麼Framebuffer的大小就是(1024x768x32/8=3145728字節)

簡單LCD的操作原理
1. 驅動程式設置好LCD控制器
   - LCD控制器的時序、訊號極性
   - LCD解析度、BPP(bits per pixel, 每個像素點用多少個bits來表示)
2. 應用程式使用ioctl獲取LCD解析度、BPP
3. 應用程式通過mmap映射Framebuffer，在Framebuffer中寫入數據

![img21](./[第4篇]_嵌入式Linux應用開發基礎知識/img21.PNG)

計算某像素點座標所對應的Framebuffer地址

$$
pixel\_address = fb\_base\_addresss + (\frac {xres*y*bpp} {8} + \frac {x*bpp} {8})
$$

像素的顏色在不同BPP格式中，用不同位數的RGB三原色來表示的

![img23](./[第4篇]_嵌入式Linux應用開發基礎知識/img23.PNG)

![img22](./[第4篇]_嵌入式Linux應用開發基礎知識/img22.PNG)

### 代碼介紹

[show_pixel.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/07_framebuffer/show_pixel.c)

**打開設備**

```C
static int fd_fb;

/*開啟設備*/
fd_fb = open("/dev/fb0", O_RDWR);
if (fd_fb < 0)
{
    printf("can't open /dev/fb0\n");
    return -1;
}

/*關閉設備*/
close(fd_fb);
```

**獲取LCD參數, 編寫應用程序時主要關心可變參數**

1. 可變的參數 fb_var_screeninfo
2. 固定的參數 fb_fix_screeninfo

[fb.h](./[第4篇]_嵌入式Linux應用開發基礎知識/doc/fb.h)

```C
#include <linux/fb.h>
```

```C
struct fb_var_screeninfo {
    __u32 xres;                 /* visible resolution 解析度*/
    __u32 yres;

    /*........................*/

    __u32 bits_per_pixel;       /* BPP*/
    __u32 grayscale;            /* 0 = color, 1 = grayscale,*//* >1 = FOURCC*/
    struct fb_bitfield red;     /* bitfield in fb mem if true color, */
    struct fb_bitfield green;   /* else only length is significant */
    struct fb_bitfield blue;    /* RGB分別用多少位來表示，從哪位開始*/

    /*........................*/
};
```

```C
static struct fb_var_screeninfo var;	/* Current var */

static int screen_size;
static unsigned int line_width;
static unsigned int pixel_width;

if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
{
    printf("can't get var\n");
    return -1;
}
line_width  = var.xres * var.bits_per_pixel / 8;
pixel_width = var.bits_per_pixel / 8;
screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
```

**映射Framebuffer**

- 要映射一塊內存，需要知道它的地址 --- 由驅動程序來設置
- 需要知道它的大小 --- 由應用程式決定

```C
static unsigned char *fb_base;

/*映射*/
fb_base = (unsigned char *)mmap(NULL , screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
if (fb_base == (unsigned char *)-1)
{
    printf("can't mmap\n");
    return -1;
}

/*取消映射*/
munmap(fb_base , screen_size);
```

**描點函數**

![img24](./[第4篇]_嵌入式Linux應用開發基礎知識/img24.PNG)

```C
/**********************************************************************
 * 函數名稱： lcd_put_pixel
 * 功能描述： 在LCD指定位置上輸出指定顏色（描點）
 * 輸入參數： x坐標，y坐標，顏色
 * 輸出參數： 無
 * 返 回 值： 會
 * 修改日期        版本號     修改人          修改內容
 * -----------------------------------------------
 * 2020/05/12     V1.0       zh(angenao)     創建
 ***********************************************************************/
void lcd_put_pixel(int x, int y, unsigned int color)
{
    unsigned char *pen_8 = fb_base+y*line_width+x*pixel_width;
    unsigned short *pen_16;
    unsigned int *pen_32;

    unsigned int red, green, blue;

    pen_16 = (unsigned short *)pen_8;
    pen_32 = (unsigned int *)pen_8;

    switch (var.bits_per_pixel)
    {
        case 8:
        {
            *pen_8 = color;
            break;
        }
        case 16:
        {
            /* 565 */
            red   = (color >> 16) & 0xff;
            green = (color >> 8) & 0xff;
            blue  = (color >> 0) & 0xff;
            color = ((red >> 3) << 11) | ((green >> 2) << 5) | (blue >> 3);
            *pen_16 = color;
            break;
        }
        case 32:
        {
            *pen_32 = color;
            break;
        }
        default:
        {
            printf("can't surport %dbpp\n", var.bits_per_pixel);
            break;
        }
    }
}

/* 清屏: 全部设为白色 */
memset(fb_base, 0xff, screen_size);

/* 随便设置出100个为红色 */
for (i = 0; i < 100; i++)
    lcd_put_pixel(var.xres/2+i, var.yres/2, 0xFF0000);
```

<h1 id="6">06_字符應用</h1>

<h2 id="6.1">6-1_字符的編碼方式</h2>

什麼叫作編碼?

- 就是一個字符用什麼數字來表示
- 在計算機裡的一切都是用數字來表示，比如字符A用0x01或0x02或0x41來表示

編碼方式

1. ASCII

   - American Standard Code for Information Interchange，美國標準資訊交換碼
   - 每個字符用一個字節來表示，一個字節的7位可以表示128個數值，在ASCII碼中最高位永遠是0

![img25](./[第4篇]_嵌入式Linux應用開發基礎知識/img25.PNG)

2. ANSI

   - ASNI是ASCII的擴展，向下包含ASCII，對於ASCII的字符仍可以一個字節來表示，對於非ASCII字符則用兩個字節來表示
   - 第一個字節的第7位為1表示為ASNI編碼，以兩個字節來表示一個字符;反之為0則表示ASCII編碼，以一個字節表示一個字符
   - 由Windows提出
   - 使用ANSI編碼方式時，還需選擇要解析數值的字符集，才能正確地顯示出字符

![img26](./[第4篇]_嵌入式Linux應用開發基礎知識/img26.PNG)

3. UNICODE

   - 統一編碼，避免ANSI在同一個數值下對應不同的字符集會有不同的字符的問題，有著一對一的關係
   - 對於地球上任意一個字符，都給它一個唯一的數值
   - 數值範圍由 0x0000 至 0x10FFFF，有1,114,111個數值可以使用
   - 如何辨識數值 (0x41 0x4e 0x2d) 是代表 A中(0x41, 0x4e 0x2d) 還是 A-N(0x41, 0x4e, 0x2d)，因此涉及**編碼實現**

編碼實現

- ASCII & ANSI 根據地一個字節的第7位來判別是一個字符是由一個字節或是兩個字節來表示

- UNICODE
  1. 用3個字節表示一個UNICODE --> 過度浪費空間
  2. UCS-2 Little endian/UTF-16 LE 小字節序
       - 數值中權重低的放在前面
       - a 以 0x61 0x00 表示, b 以 0x62 0x00 表示, 中 以 0x2d 0x4e 表示
       - 文件開頭為 0xff 0xfe 表示 UTF-16 LE
       - 容錯率較低，只要有一個字節漏掉，整個字符都會偏掉
       - 3字節的字符無法表示
  3. UCS-2 Big endian/UTF-16 BE 大字節序
       - 數值中權重高的放在前面
       - a 以 0x00 0x41 表示 中 以 0x4e 0x2d 表示
       - 文件開頭為 0xff 0xff 表示 UTF-16 BE
       - 容錯率較低，只要有一個字節漏掉，整個字符都會偏掉
       - 3字節的字符無法表示
  4. UTF8: 為了改善上方的問題，是一種變長的編碼方式，分為帶有頭部與不帶頭部的2種UTF8格式文件
     - ASCII字符直接用ASCII碼來表示，一個字節
     - 非ASCII字符使用變長的編碼，每一個字節的高位都自帶長度信息，因此容錯率較高，只會在掉字節處發生亂碼

        ![img27](./[第4篇]_嵌入式Linux應用開發基礎知識/img27.PNG)

        ![img28](./[第4篇]_嵌入式Linux應用開發基礎知識/img28.PNG)

<h2 id="6.2">6-2_ASCII字符的點陣顯示</h2>

LCD中要顯示一個ASCII字符，首先要找到字符對應的點陣，在Linux內核中`kernel/linux-5.4/lib/fonts/`路徑下有以結構font_data的形式保存各個字符的點陣

- 常用的為font_8x16.c --> 橫方向8bits, 縱方向16bits
- 每一個bit為一個像素

    ![img29](./[第4篇]_嵌入式Linux應用開發基礎知識/img29.PNG)

- 在LCD顯示ASCII字符的函數 [show_ascii.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/08_show_ascii/show_ascii.c)

    ```C
    #define FONTDATAMAX 4096

    static const unsigned char fontdata_8x16[FONTDATAMAX] = {
        /*..........................*/
    }
    /**********************************************************************
     * 函數名稱： lcd_put_ascii
     * 功能描述： 在LCD指定位置上顯示一個8*16的字符
     * 輸入參數： x坐標，y坐標，ascii碼
     * 輸出參數： 無
     * 返 回 值： 無
     * 修改日期        版本號     修改人      修改內容
     * -----------------------------------------------
     * 2020/05/12     V1.0      zh(angenao)      創建
     ***********************************************************************/
    void lcd_put_ascii(int x, int y, unsigned char c)
    {
        unsigned char *dots = (unsigned char *)&fontdata_8x16[c*16];
        int i, b;
        unsigned char byte;

        for (i = 0; i < 16; i++)
        {
            byte = dots[i];
            for (b = 7; b >= 0; b--)
            {
                if (byte & (1<<b))
                {
                    /* show */
                    lcd_put_pixel(x+7-b, y+i, 0xffffff);    /* 白 */
                }
                else
                {
                    /* hide */
                    lcd_put_pixel(x+7-b, y+i, 0);           /* 黑 */
                }
            }
        }
    }
    ```

<h2 id="6.3">6-3_中文字符的點陣顯示</h2>

使用點陣字符時，中文字符的顯示跟ASCII字符是一樣的，要注意的地方為中文的編碼(GB2312 or UTF-8)

編寫C程序時，可以使用ANSI編碼或是UTF-8編碼，可透過下面選項告訴編譯器，若沒指定的話，GCC會默認編碼方式為UTF-8編碼

```bash
-finput-charset=GB2312
-finput-charset=UTF-8
```

將test_charset_ansi.c中的編碼內容轉換成UTF-8

```bash
gcc -finput-charset=GB2312 -fexec-charset=UTF-8 -o test_charset_ansi test_charset_ansi.c
```

將test_charset_utf8.c中的編碼內容轉換成ANSI

```bash
gcc -finput-charset=UTF-8 -fexec-charset=GB2312 -o test_charset_utf8 test_charset_utf8.c
```

常用漢字16*16點陣字庫 [HZK16](./[第4篇]_嵌入式Linux應用開發基礎知識/source/09_show_chinese/HZK16)，每個漢字使用32字節來描述

![img30](./[第4篇]_嵌入式Linux應用開發基礎知識/img30.PNG)

HZJ16以GB2312編碼值來查找點陣
- 以 `中` 為例，它的編碼值是 `0xd6 0xd0`
- 其中 `0xd6` 表示區碼，表示在哪一區：第 `0xd6 - 0xa1` 區
- 其中 `0xd0` 表示位碼，表示它是這個區的哪一個字符：第 `0xd0 - 0xa1` 個
- 一區有 `94` 個漢字，且區位碼從 `0xa1` 開始
- LCD中文字符的點陣顯示代碼

    ```C
    /**********************************************************************
     * 函數名稱： lcd_put_chinese
     * 功能描述： 在LCD指定位置上顯示一個16*16的漢字
     * 輸入參數： x坐標，y坐標，ascii碼
     * 輸出參數： 無
     * 返 回 值： 無
     * 修改日期        版本號     修改人      修改內容
     * -----------------------------------------------
     * 2020/05/12     V1.0  zh(angenao)      創建
     ***********************************************************************/
    void lcd_put_chinese(int x, int y, unsigned char *str)
    {
        unsigned int area  = str[0] - 0xA1;
        unsigned int where = str[1] - 0xA1;
        unsigned char *dots = hzkmem + (area * 94 + where)*32;
        unsigned char byte;

        int i, j, b;
        for (i = 0; i < 16; i++)
            for (j = 0; j < 2; j++)
            {
                byte = dots[i*2 + j];
                for (b = 7; b >=0; b--)
                {
                    if (byte & (1<<b))
                    {
                        /* show */
                        lcd_put_pixel(x+j*8+7-b, y+i, 0xffffff); /* 白 */
                    }
                    else
                    {
                        /* hide */
                        lcd_put_pixel(x+j*8+7-b, y+i, 0); /* 黑 */
                    }
                }
            }
    }

    int main(int argc, char **argv)
    {
        unsigned char str[] = "中";

        fd_fb = open("/dev/fb0", O_RDWR);
        if (fd_fb < 0)
        {
            printf("can't open /dev/fb0\n");
            return -1;
        }

        if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
        {
            printf("can't get var\n");
            return -1;
        }

        line_width  = var.xres * var.bits_per_pixel / 8;
        pixel_width = var.bits_per_pixel / 8;
        screen_size = var.xres * var.yres * var.bits_per_pixel / 8;
        fbmem = (unsigned char *)mmap(NULL , screen_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_fb, 0);
        if (fbmem == (unsigned char *)-1)
        {
            printf("can't mmap\n");
            return -1;
        }

        fd_hzk16 = open("HZK16", O_RDONLY);
        if (fd_hzk16 < 0)
        {
            printf("can't open HZK16\n");
            return -1;
        }
        if(fstat(fd_hzk16, &hzk_stat))
        {
            printf("can't get fstat\n");
            return -1;
        }
        hzkmem = (unsigned char *)mmap(NULL , hzk_stat.st_size, PROT_READ, MAP_SHARED, fd_hzk16, 0);
        if (hzkmem == (unsigned char *)-1)
        {
            printf("can't mmap for hzk16\n");
            return -1;
        }

        /* 清屏: 全部设为黑色 */
        memset(fbmem, 0, screen_size);

        lcd_put_ascii(var.xres/2, var.yres/2, 'A'); /*在屏幕中间显示8*16的字母A*/

        printf("chinese code: %02x %02x\n", str[0], str[1]);
        lcd_put_chinese(var.xres/2 + 8,  var.yres/2, str);

        munmap(fbmem , screen_size);
        close(fd_fb);

        return 0;
    }
    ```


<h2 id="6.4">6-4_手動交叉編譯程序_以freetype為例</h2>

FreeType是一個用C語言實現的一個字型光柵化函式庫。它可以用來將字元柵格化並對映成點陣圖以及提供其他字體相關業務的支援。

### 程序運行的一些基礎知識

1. 編譯程序時去哪裡找頭文件
    系統目錄: 交叉編譯工具鏈裡面的某個 include 目錄
    自己指定: 編譯時用 `-I dir` 選項指定
2. 鏈接時去哪找庫文件
    系統目錄: 交叉編譯工具鏈裡面的某個 lib 目錄
    自己指定: 編譯時用 `-L dir` 選項指定
3. 運行時去哪找庫文件
    系統目錄: 開發版上的 `/lib`, `/usr/lib` 目錄
    自己指定: 運行程序時用環境變量 `LD_LIBRARY_PATH` 指定
5. 運行時不需要頭文件，所以頭文件不須放到板子上

### 常見錯誤

頭文件問題 --> 編譯時找不到頭文件

- 在程序中包含頭文件 `#include <xxx.h>`，對於尖括號的頭文件要去哪裡找它
  - 系統目錄: 交叉編譯工具鏈裡面的某個 include 目錄
  - 自己指定: 編譯時用 `-I dir` 選項指定

- 透過下方指令可以得知**系統目錄**下的頭文件目錄與庫目錄(LIBRARY_PATH)

    ```bash
    echo 'main() {}' | arm-linux-gcc -E -v -
    echo 'main() {}' | gcc -E -v -
    ```

- 找不到頭文件時，需要確認頭文件目錄有沒有這個文件，或是自己指定頭文件目錄

庫文件問題

- `undefined reference tp 'xxx'`：表示xxx函數未定義
  - 函數真的未定義，實作它
  - 未連結使用到函數的函數庫

- 怎麼指定某函式庫，想鏈結 `libabc.so`，在鏈結時加上：`-labc`

- 函式庫在哪裡?
  - 系統目錄：交叉編譯工具鏈裡面的某個 lib 目錄
  - 自己指定：鏈結時用 `-L dir` 選項指定

- 透過下方指令可以得知**系統目錄**下的頭文件目錄與庫目錄(LIBRARY_PATH)

    ```bash
    echo 'main() {}' | arm-linux-gcc -E -v -
    echo 'main() {}' | gcc -E -v -
    ```

運行問題

- 運行程序時找不到函式庫

    ```
    error while loading shared libraries: libxxx.so: cannot open shared object file: No such file or directory
    ```

    系統目錄: 開發版上的 `/lib`, `/usr/lib` 目錄
    自己指定: 運行程序時用環境變量 `LD_LIBRARY_PATH` 指定，執行下方命令

    ```bash
    ## method_1
    export LD_LIBRARY_PATH=/xxx_dir; ./test

    ## method_2
    LD_LIBRARY_PATH=/xxx_dir  ./test
    ```

### 交叉編譯程序的萬能命令

交叉編譯開源軟件時，如果裡面有 `configure` 的話，可以使用下方命令：

```bash
## 分析開源軟件，生成一個Makefile
$ ./configure --host=arm-linux --prefix=$PWD/tmp
$ make
$ make install
```

- --host寫編譯工具鏈的前綴，如arm-buildroot-linux-gnueabihf-gcc的前綴是arm-buildroot-linux-gnueabihf-

- 就可以在當前目錄的 tmp 目錄下看見 bin, lib, include 等目錄，裡面存有可執行程序, 函式庫, 頭文件

把頭文件、庫文件放到工具鏈目錄裡

- 編譯一個函式庫後，把得到的頭文件與庫文件放入工具鏈的 `include`, `lib` 目錄，別個應用程序要使用這些函數時，會比較方便
- 工具鏈裡有多個 `include`, `lib` 目錄，透過下方指令可以確定系統目錄下的頭文件目錄與庫目錄(LIBRARY_PATH)

    ```bash
    echo 'main() {}' | arm-linux-gcc -E -v -
    echo 'main() {}' | gcc -E -v -
    ```

把庫文件放到開發版上的`lib`或`/usr/lib`目錄裡

- 程序在開發版上運行時，需要用到板子上/lib或/usr/lib下的庫文件，不需要頭文件

<h2 id="6.5">6-5_使用freetype顯示單個文字</h2>




<h2 id="6.6">6-6_使用freetype顯示一行文字</h2>


<h1 id="7">07_輸入系統</h1>

什麼是輸入設備
- 常見的輸入設備有 `鍵盤`、`滑鼠`、`遙控桿`、`書寫板` 與 `觸碰屏幕`，用戶通過這些輸入設備與Linux系統進行數據交換

什麼是輸入系統
- 輸入設備種類繁多，能否統一他們的接口
- Linux系統實現一套兼容所有輸入設備的框架來統一管理這些設備，驅動人員基於這套框架開發驅動程序，應用開發人員就可以使用統一的API去使用設備

<h2 id="7.1">7-1_輸入系統框架及調試</h2>

### 框架概述

用戶程序直接訪問 `/dev/input/event0` 節點設備，或者使用 `tslib` 訪問設備節點，數據的流程如下：
1. APP發起讀操作，若無數據則休眠
2. 用戶操作設備，硬件上產生中斷
3. 輸入系統驅動層對應的驅動程序處理中斷
    讀取到數據，轉換成標準的輸入事件，向核心層匯報
    所謂輸入事件就是一個 `struct input_event` 結構體
4. 核心層可以決定把輸入事件轉發給上面哪個handler來處理
    比如 `evdev_handler`, `kbd_handler`, `joydev_handler` 等等
    最常用的是 `evdev_handler` 它能夠接收任意類型的事件，任意id的設備都可以和它匹配連接
5. APP對輸入事件的處理
    APP獲取數據的方式有兩種：
   - 直接訪問 `/dev/input/event0` 節點設備

        ```bash
        ## 查詢目前使用event的相關資訊
        cat /proc/bus/input/devices

        ## 直接訪問節點設備
        hexdump /dev/input/event0
        ```

        ![img34](./[第4篇]_嵌入式Linux應用開發基礎知識/img34.PNG)

   - 使用 `tslib`、`libinput` 函式庫來間接訪問設備節點

![img31](./[第4篇]_嵌入式Linux應用開發基礎知識/img31.PNG)

### 編寫APP需要掌握的知識

內核中如何表示一個輸入設備

- 使用 `input_dev` 結構體來表示輸入設備

    ```C
    struct input_dev {
        const char *name;
        const char *phys;
        const char *uniq;
        struct input_id id;

        unsigned long propbit[BITS_TO_LONGS(INPUT_PROP_CNT)];

        unsigned long evbit[BITS_TO_LONGS(EV_CNT)];
        unsigned long keybit[BITS_TO_LONGS(KEY_CNT)];
        unsigned long relbit[BITS_TO_LONGS(REL_CNT)];
        unsigned long absbit[BITS_TO_LONGS(ABS_CNT)];
        unsigned long mscbit[BITS_TO_LONGS(MSC_CNT)];
        unsigned long ledbit[BITS_TO_LONGS(LED_CNT)];
        unsigned long sndbit[BITS_TO_LONGS(SND_CNT)];
        unsigned long ffbit[BITS_TO_LONGS(FF_CNT)];
        unsigned long swbit[BITS_TO_LONGS(SW_CNT)];

        /*.............................*/
    }
    ```

驅動程序上報的數據函義三項重要內容：

![img32](./[第4篇]_嵌入式Linux應用開發基礎知識/img32.PNG)

![img33](./[第4篇]_嵌入式Linux應用開發基礎知識/img33.PNG)

APP可以得到什麼數據

- 可以得到一系列的輸入事件，就是一個一個 `struct input_event` 結構體
- 每個結構體都有發生時間，`struct timeval` 表示自系統啟動以來過多少時間，含有 `tv_sec`(秒), `tv_usec`(微秒)

    ```C
    struct input_event {
    #if (__BITS_PER_LONG != 32 || !defined(__USE_TIME_BITS64)) && !defined(__KERNEL__)
        struct timeval time;
    #define input_event_sec time.tv_sec
    #define input_event_usec time.tv_usec
    #else
        __kernel_ulong_t __sec;
    #if defined(__sparc__) && defined(__arch64__)
        unsigned int __usec;
        unsigned int __pad;
    #else
        __kernel_ulong_t __usec;
    #endif
    #define input_event_sec  __sec
    #define input_event_usec __usec
    #endif
        __u16 type;
        __u16 code;
        __s32 value;
    };
    ```

設置同步事件作為事件的分界，表示上報事件已經完成，(type, code, value) = (0000, 0000, 0000 0000)

![img34](./[第4篇]_嵌入式Linux應用開發基礎知識/img34.PNG)

如何得知設備節點對應的硬件，取得與event對應的相關設備訊息

```bash
$ cat /proc/bus/input/devices
```

![img35](./[第4篇]_嵌入式Linux應用開發基礎知識/img35.PNG)

- B: EV=b 用來表示該設備支持哪類輸入事件
  - b=1011，bit0, 1, 3為high，表示支持三類事件(EV_SYN, EV_KEY, EV_ABS)
  - B: ABS=2658000 3，表示設備支持EV_ABS事件中的哪些事件，是2個32位的數字(0x02658000, 0x00000003)，高位在前，低位在後，組成一個64位數字，為high的bit有0, 1, 47, 48, 50, 53, 54 (即0x00, 0x01, 0x2f, 0x30, 0x32, 0x35, 0x36)

![img33](./[第4篇]_嵌入式Linux應用開發基礎知識/img33.PNG)

![img36](./[第4篇]_嵌入式Linux應用開發基礎知識/img36.PNG)

<h2 id="7.2">7-2_現場編程讀取獲取輸入設備信息</h2>

輸入系統支持完整的API操作：阻塞、非阻塞、POLL/SELECT、異步通知

APP訪問硬件的4種方式，以媽媽怎麼知道孩子醒了為例

1. 時不時進房間看一下：`查詢方式`
    簡單，但是累

2. 進去房間陪小孩一起睡覺，小孩醒會吵醒她：`休眠-喚醒`
    不累，但是媽媽沒辦法做其他事

3. 媽媽要做很多事，但可以陪小孩睡一陣子，訂個鬧鐘：`poll方式`
    要浪費點時間，但是可以繼續做其他事
    媽媽要是被小孩吵醒，不然被鬧鐘吵醒

4. 媽媽在客廳做事情，小孩醒了他會自己走出房門告訴媽媽：`異步通知`

獲取設備信息

- 通過ioctl獲取設備信息，ioctl的參數如下

    ```C
    int ioctl(int fd, unsigned long request, ...);
    ```

    ![img37](./[第4篇]_嵌入式Linux應用開發基礎知識/img37.PNG)

- 範例 [01_get_input_info.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/11_input/01_app_demo/01_get_input_info.c)

    ```C
    int err;
    int len;
    struct input_id id;
    unsigned int evbit[2];

    err = ioctl(fd, EVIOCGID, &id);

    len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
    ```

<h2 id="7.3">7-3_查詢與休眠喚醒的方式讀取輸入數據</h2>

查詢方式

- APP調用open函數時，傳入 `O_NONBLOCK` 表示 `非阻塞`
- APP調用read函數讀取數據時，如果驅動程序中有數據，則APP的read函數會返回數據，否則會立刻返回錯誤

    ```C
    int fd;
    int len;
    struct input_event event;

    fd = open(argv[1], O_RDWR | O_NONBLOCK);

    while (1)
    {
        len = read(fd, &event, sizeof(event));
        if (len == sizeof(event))
        {
            printf("get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
        }
        else
        {
            printf("read err %d\n", len);
        }
    }
    ```

休眠-喚醒

- APP調用open函數時，不要傳入 `O_NONBLOCK`，代表 `阻塞`
- APP調用read函數讀取數據時，如果驅動程序中有數據，則APP的read函數會返回數據，否則APP會在內核態休眠，當有數據時驅動程序會把APP喚醒，read函數恢復執行並返回數據給APP

    ```C
    int fd;
    int len;
    struct input_event event;

    fd = open(argv[1], O_RDWR);

    while (1)
    {
        len = read(fd, &event, sizeof(event));

        printf("get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
    }
    ```

範例: [02_input_read.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/11_input/01_app_demo/02_input_read.c)

<h2 id="7.4">7-4_POLL或SELECT的方式讀取輸入數據</h2>

POLL/SELECT介紹

- POLL機制與SELECT機制是完全一樣的，只是APP接口函數不一樣

- 簡單來說就是**定個時鐘**，在調用poll、select函數時，可以傳入 `超時時間`，在時間內，若有數據可讀且有空間可寫就會立刻返回，否則等到 `超時時間` 結束時返回錯誤

用法如下

- APP先調用open函數
- APP不是直接調用read函數，而是先調用poll或select函數，這2個函數中可以傳入 `超時時間`。
- 作用是如果驅動程序中有數據，則立刻返回，否則進入休眠。在休眠期間，若有人操作硬件使驅動程序獲得數據後，就會把APP喚醒，導致poll或select立刻返回。
- 如果在 `超時時間` 內無人操作硬件的話，時間到時poll或select函數也會返回，可以根據返回值判斷是哪一種返回

POLL/SELECT函數可以監測多個文件, 多個事件

- 函數介紹

    ```C
    #include <poll.h>

    struct pollfd {
        int   fd;         /* file descriptor */
        short events;     /* requested events */
        short revents;    /* returned events */
    };

    /*The caller should specify the number of items in the fds array in nfds.*/
    /*The timeout argument specifies the number of milliseconds*/
    /*On success, a positive number is returned; this is the number of structures which have nonzero revents fields (in other words, those descriptors with events or errors reported).  A value of 0
       indicates that the call timed out and no file descriptors were ready.  On error, -1 is returned, and errno is set appropriately.
    */
    int poll(struct pollfd *fds, nfds_t nfds, int timeout);
    ```

- 事件類型介紹

    ![img38](./[第4篇]_嵌入式Linux應用開發基礎知識/img38.PNG)

- 先從poll的返回值知道它不是超時返回，再去判斷fds數組中的revents

- 範例: [03_input_read_poll.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/11_input/01_app_demo/03_input_read_poll.c)

    ```C
    #include <poll.h>

    struct input_event event;
    struct pollfd fds[1];
    nfds_t nfds = 1;

    fd = open(argv[1], O_RDWR | O_NONBLOCK);

    while (1)
    {
        fds[0].fd = fd;
        fds[0].events  = POLLIN;
        fds[0].revents = 0;
        ret = poll(fds, nfds, 5000);
        if (ret > 0)
        {
            if (fds[0].revents == POLLIN)
            {
                while (read(fd, &event, sizeof(event)) == sizeof(event))
                {
                    printf("get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
                }
            }
        }
        else if (ret == 0)
        {
            printf("time out\n");
        }
        else
        {
            printf("poll err\n");
        }
    }
    ```

- SELECT範例: [04_input_read_select.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/11_input/01_app_demo/04_input_read_select.c)

<h2 id="7.5">7-5_異步通知的方式讀取輸入數據</h2>

### 功能介紹

同步：你慢我等你 
異步：你慢那你自己玩，我做自己的事情去，有情況再通知我

異步通知：APP可以忙自己的事，當驅動程序用數據時會主動給APP發信號，導致APP執行信號處理函數

發信號所引發的議題
1. 誰發： 驅動程序發
2. 發什麼： 信號
3. 發什麼信號： SIGIO(驅動程序要通知應用程序所發的信號)
4. 怎麼發： 內核裡提供函數
5. 發給誰： APP，APP要把自己的進程號告訴驅動
6. APP收到後做什麼： 執行信號處理函數
7. 信號處理函數和信號之間怎麼掛鉤起來： APP註冊信號處理函數

小孩通知媽媽的事情有很多： 壞了, 渴了, 想找人玩
Linux系統中也有很多信號，在Linux內核源文件 `include/uapi/asm-generic/signal.h` 中，有很多信號的宏定義

![img39](./[第4篇]_嵌入式Linux應用開發基礎知識/img39.PNG)

驅動程序通知APP時，它會發出 `SIGIO` 這個信號，表示有 `IO事件` 要處理
就APP而言，想要處理SIGIO信號，就需要提供信號處理函數，並請要跟SIGIO掛鉤。可以透過 `signal函數` 來給某個信號註冊處理函數

![img40](./[第4篇]_嵌入式Linux應用開發基礎知識/img40.PNG)

除了註冊SIGIO的處理函數，APP還要做什麼呢?
1. 內核裡有很多驅動，你想讓哪一個驅動給你發SIGIO信號?
    APP要打開驅動程序的設備節點
2. 驅動程序怎麼知道要發信號給哪個APP
    APP要把自己的進程ID告訴驅動程序
3. APP有時候想收到信號，有時候又不想收到信號
    把APP的意圖告訴驅動，設置Flag裡面的FASYNC位為high，使能**異步通知**

### 應用編程

範例: [05_input_read_fasync.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/11_input/01_app_demo/05_input_read_fasync.c)

```C
#include <signal.h>

int fd;     /*global variable*/
```

1. 編寫信號處理函數

    ```C
    void my_sig_handler(int sig)
    {
        struct input_event event;
        while (read(fd, &event, sizeof(event)) == sizeof(event))
        {
            printf("get event: type = 0x%x, code = 0x%x, value = 0x%x\n", event.type, event.code, event.value);
        }
    }
    ```

2. 註冊信號處理函數

    ```C
    signal(SIGIO, my_sig_handler);
    ```

3. 打開驅動

    ```C
    fd = open(argv[1], O_RDWR | O_NONBLOCK);
    ```

4. 把進程ID告訴驅動

    ```C
    fcntl(fd, F_SETOWN, getpid());
    ```

5. 使能驅動的FASYNC功能

    ```C
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | FASYNC);
    ```

<h2 id="7.6">7-6_電阻屏與電容屏</h2>

觸摸屏分為電阻屏與電容屏

- 電阻屏結構簡單，在以前很流行
- 電容屏支持多點觸摸，現在手機基本上都是使用電容屏

LCD與觸摸屏並不是同一種東西，LCD和觸摸屏都是輸入設備，只是常常把觸摸屏製作的與LCD的尺寸一樣，並把它覆蓋在LCD上，就變成觸摸屏幕

### 電阻屏

歐姆定律

- 假設電阻是均勻的，長度會和電阻成正比關係

    ![img41](./[第4篇]_嵌入式Linux應用開發基礎知識/img41.PNG)

電阻屏原理

- 基於歐姆定理來實現的，它有上下兩個薄膜(電阻)

    ![img42](./[第4篇]_嵌入式Linux應用開發基礎知識/img42.PNG)

- 平時上下兩層薄膜無接觸，當點擊觸摸屏時，上下兩層薄膜接觸，這時候就可以測量觸點電壓
  1. 測量 X 座標
    在xp、xm兩端施加3.3V電壓，yp和ym不能加電壓(yp就相當於探針)，測量yp電壓值，該電壓值就跟 X 座標成正比關係

    $$X = 3.3*V_{yp}/X_{max}$$


- 透過在觸摸屏取得觸點的電壓值，並轉換成LCD可以辨識位置的座標值，便可達到觸摸屏幕的效果

  - 但在實際使用時，電阻屏的$X_{max}$, $Y_{max}$無從得知，所以使用之前要先校準，依次點擊觸摸屏的四個角與中心點，推算出X, Y座標的公式

    $$
    X=func(V_{yp}) \\
    Y=func(V_{xp})
    $$

  - 根據LCD的解析度大小與電壓之間的比例關係來建立起關係

    ![img43](./[第4篇]_嵌入式Linux應用開發基礎知識/img43.PNG)

電阻屏數據

- Linux驅動程序中會上報觸點的X, Y數據，需要APP再次處理才能轉換為LCD座標值

    ![img44](./[第4篇]_嵌入式Linux應用開發基礎知識/img44.PNG)

### 電容屏

![img45](./[第4篇]_嵌入式Linux應用開發基礎知識/img45.PNG)

電容屏中有一個控制晶片，它會週期性產生驅動信號，接收電極接收到信號，並可測量電荷大小。

當電容屏被按下時，相當引入了新的電容，進而影響接收電極接收到的電荷大小，主控晶片根據電荷大小即可計算出觸點位置

控制晶片一般是使用I2C接口，只須編寫程序，通過I2C讀取晶片暫存器即可以得到這些數據

電容屏數據

- 支持多點觸摸(Multi-touch)
- TypeB類型能分辨是哪一個觸點，上報數據時會先上報觸點ID，在上報它的數據
- 範例：

    ![img46](./[第4篇]_嵌入式Linux應用開發基礎知識/img46.PNG)

    ![img47](./[第4篇]_嵌入式Linux應用開發基礎知識/img47.PNG)

    ![img48](./[第4篇]_嵌入式Linux應用開發基礎知識/img48.PNG)

電容屏實驗數據

![img49](./[第4篇]_嵌入式Linux應用開發基礎知識/img49.PNG)

![img50](./[第4篇]_嵌入式Linux應用開發基礎知識/img50.PNG)

- TOUCH_MAJOR & WIFTH_MAJOR: 橢圓形狀的長軸

    ![img51](./[第4篇]_嵌入式Linux應用開發基礎知識/img51.PNG)

<h2 id="7.7">7-7_tslib框架分析</h2>

https://www.bilibili.com/video/BV1kk4y117Tu?p=27&vd_source=790c8244dbe879457094c8374beb04d3

主要代碼如下

![img52](./[第4篇]_嵌入式Linux應用開發基礎知識/img52.PNG)

![img53](./[第4篇]_嵌入式Linux應用開發基礎知識/img53.PNG)

![img54](./[第4篇]_嵌入式Linux應用開發基礎知識/img54.PNG)

<h2 id="7.8">7-8_tslib交叉編譯與測試</h2>

https://www.bilibili.com/video/BV1kk4y117Tu?p=28&vd_source=790c8244dbe879457094c8374beb04d3

![img55](./[第4篇]_嵌入式Linux應用開發基礎知識/img55.PNG)

<h2 id="7.9">7-9_編寫基於tslib的測試程序</h2>

手指觸碰屏幕時，驅動系統會上報事件

![img56](./[第4篇]_嵌入式Linux應用開發基礎知識/img56.PNG)

使用tslib的話，可以使用ts_read_mt()來完成讀取數據的動作

```C
/*
 * Return a scaled touchscreen multitouch sample.
 */
/*slots: 幾個觸碰點, nr: 讀幾次數據*/
TSAPI int ts_read_mt(struct tsdev *, struct ts_sample_mt **, int slots, int nr);

struct ts_sample_mt {
    /* ABS_MT_* event codes. linux/include/uapi/linux/input-event-codes.h
        * has the definitions.
        */
    int		x;
    int		y;
    unsigned int	pressure;
    int		slot;
    int		tracking_id;

    int		tool_type;
    int		tool_x;
    int		tool_y;
    unsigned int	touch_major;
    unsigned int	width_major;
    unsigned int	touch_minor;
    unsigned int	width_minor;
    int		orientation;
    int		distance;
    int		blob_id;

    struct timeval	tv;

    /* BTN_TOUCH state */
    short		pen_down;

    /* valid is set != 0 if this sample
        * contains new data; see below for the
        * bits that get set.
        * valid is set to 0 otherwise
        */
    short		valid;
};
```

範例程序:
- 目的 - 不斷印出2個觸點的距離
- 思路 - 假設是5點觸摸屏，調用一次ts_read_mt可以得到5個新數據，使用新舊數據判斷，如果有2個觸點，就印出距離

    [mt_cal_distance.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/11_input/02_tslib/mt_cal_distance.c)

<h1 id="8">08_網路相關簡介</h1>

<h2 id="8.1">8-1_網路編程概念</h2>

在編程程序時，通常會用UART加上有print log的設置，但當數量變多時，不可能使用這麼多UART線，加上過多的print log，會導致程序速度變慢，非實際使用情況，故通常會透過網路把多台的log資訊傳回到某一台電腦(server?)

數據傳輸三要素：源、目的、長度

分為服務器與客戶端
- 服務器
  - 被動響應請求
- 客戶端
  - 主動發起請求

![img60](./[第4篇]_嵌入式Linux應用開發基礎知識/img60.PNG)

數據傳輸有兩種方式
- TCP
  - 可靠傳輸，有重傳機制，確保資料有傳遞成功
  - 流量控制
  - 當數據是不可丟失時使用這種方式，如控制器或是傳遞文件
- UDP
  - 不可靠的，資料丟出去，接收者未必一定有收到
  - 不需要唯一識別碼和序號
  - 當掉了丟出數據中的某一個並不會影響到其呈獻的效果時，使用這種方式，如視訊時，掉了幾幀並不會影響太多，但避免重傳，可提升速度

![img57](./[第4篇]_嵌入式Linux應用開發基礎知識/img57.PNG)

文件的讀寫

- 透過open, read, write

    ![img58](./[第4篇]_嵌入式Linux應用開發基礎知識/img58.PNG)

IP與端口：用來表示網路傳輸中的源或目的

![img59](./[第4篇]_嵌入式Linux應用開發基礎知識/img59.PNG)

網路協議被分為 5 層

![img61](./[第4篇]_嵌入式Linux應用開發基礎知識/img61.PNG)

- 應用層：系統結構中的最高層，直接為用戶的應用進程(如 電子郵件, 文件傳輸和終端仿真)提供服務
  - 全球廣域網路(www)的HTTP協議
  - 電子郵件的SMTP協議
  - 文件傳送的FTP協議
  - DNS
  - Telnet
  - ....
- 傳輸層：負責向兩個主機中進程之間的通信提供服務
  - 傳輸控制協議(Transmission Control Protocol, TCP)
  - 使用者資料包協定(User Datagram Protocol, UDP)
- 網路層：將資料從源網路傳輸到目的網路
- 資料連結層：封包從一個裝置的網路層傳輸到另外一個裝置的網路層的方法
- 實體(物理)層：物理層確保原始的數據可在各種物理媒體上傳輸

以初學者來說，我們需要使用**傳輸層**編寫應用程序，而應用程序位於**應用層**

- TCP

    ![img62](./[第4篇]_嵌入式Linux應用開發基礎知識/img62.PNG)

    ![img64](./[第4篇]_嵌入式Linux應用開發基礎知識/img64.PNG)

- UDP

    ![img63](./[第4篇]_嵌入式Linux應用開發基礎知識/img63.PNG)

    ![img65](./[第4篇]_嵌入式Linux應用開發基礎知識/img65.PNG)

<h2 id="8.2">8-2_TCP編程範例</h2>

[Linux网络编程入门 (转载)](https://www.cnblogs.com/duzouzhe/archive/2009/06/19/1506699.html)

C 語言中的 fork 函數可以將目前的程式行程（process）複製一份，建立出新的子行程（child process），而原本的行程就稱為父行程（parent process）

fork 在執行之後，會傳回一個整數的傳回值，以下是各種數值所代表的意義：

- 負值（小於零）：建立子行程失敗。
- 零：代表這個程式處於新建立的子行程中。
- 正值（大於零）：代表這個程式處於原本的父行程中，這個整數值則是子行程的 ID。

在程序一開始時，執行`signal(SIGCHLD, SIG_IGN);`，可以避免子進程退出時產生殭屍進程

```C
socket(AF_INET, SOCK_STREAM, 0);
```

[Server範例](./[第4篇]_嵌入式Linux應用開發基礎知識/source/12_socket/tcp/server.c)

```C
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

/* socket
 * bind
 * listen
 * accept
 * send/recv
 */

#define SERVER_PORT 8888
#define BACKLOG     10

int main(int argc, char **argv)
{
    int iSocketServer;
    int iSocketClient;
    struct sockaddr_in tSocketServerAddr;
    struct sockaddr_in tSocketClientAddr;
    int iRet;
    int iAddrLen;

    int iRecvLen;
    unsigned char ucRecvBuf[1024];

    int iClientNum = -1;

    signal(SIGCHLD, SIG_IGN);   /*避免子進程退出時產生殭屍進程*/

    iSocketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == iSocketServer)
    {
        printf("socket error!\n");
        return -1;
    }

    tSocketServerAddr.sin_family      = AF_INET;
    tSocketServerAddr.sin_port        = htons(SERVER_PORT);  /* host to net, short */
    tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;  /*htonl(IP); INADDR_ANY表示可以和任何的主機通信*/
    memset(tSocketServerAddr.sin_zero, 0, 8);

    iRet = bind(iSocketServer, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr));
    if (-1 == iRet)
    {
        printf("bind error!\n");
        return -1;
    }

    iRet = listen(iSocketServer, BACKLOG);	/*BACKLOG 代表最多可以連接的client端數量*/
    if (-1 == iRet)
    {
        printf("listen error!\n");
        return -1;
    }

    while (1)
    {
        iAddrLen = sizeof(struct sockaddr);
        iSocketClient = accept(iSocketServer, (struct sockaddr *)&tSocketClientAddr, &iAddrLen);
        if (-1 != iSocketClient)
        {
            iClientNum++;
            printf("Get connect from client %d : %s\n",  iClientNum, inet_ntoa(tSocketClientAddr.sin_addr));	/*inet_ntoa: 把IP轉換成一般字符串形式*/
            if (!fork())
            {
                /* 子進程的源碼 */
                while (1)
                {
                    /* 接收客戶端發來的數據並顯示出來 */
                    iRecvLen = recv(iSocketClient, ucRecvBuf, 1023, 0);
                    if (iRecvLen <= 0)
                    {
                        close(iSocketClient);
                        return -1;
                    }
                    else
                    {
                        ucRecvBuf[iRecvLen] = '\0';
                        printf("Get Msg From Client %d: %s\n", iClientNum, ucRecvBuf);
                    }
                }
            }
        }
    }

    close(iSocketServer);
    return 0;
}
```

[Client範例](./[第4篇]_嵌入式Linux應用開發基礎知識/source/12_socket/tcp/client.c)

```C
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

/* socket
 * connect
 * send/recv
 */

#define SERVER_PORT 8888

int main(int argc, char **argv)
{
    int iSocketClient;
    struct sockaddr_in tSocketServerAddr;

    int iRet;
    unsigned char ucSendBuf[1024];
    int iSendLen;

    if (argc != 2)
    {
        printf("Usage:\n");
        printf("%s <server_ip>\n", argv[0]);
        return -1;
    }

    iSocketClient = socket(AF_INET, SOCK_STREAM, 0);

    tSocketServerAddr.sin_family      = AF_INET;
    tSocketServerAddr.sin_port        = htons(SERVER_PORT);  /* host to net, short */
    //tSocketServerAddr.sin_addr.s_addr = INADDR_ANY;
    if (0 == inet_aton(argv[1], &tSocketServerAddr.sin_addr))	/*inet_aton: 把字符串轉換成inet address*/
    {
        printf("invalid server_ip\n");
        return -1;
    }
    memset(tSocketServerAddr.sin_zero, 0, 8);


    iRet = connect(iSocketClient, (const struct sockaddr *)&tSocketServerAddr, sizeof(struct sockaddr));
    if (-1 == iRet)
    {
        printf("connect error!\n");
        return -1;
    }

    while (1)
    {
        if (fgets(ucSendBuf, 1023, stdin))
        {
            iSendLen = send(iSocketClient, ucSendBuf, strlen(ucSendBuf), 0);
            if (iSendLen <= 0)
            {
                close(iSocketClient);
                return -1;
            }
        }
    }

    return 0;
}
```

<h2 id="8.3">8-3_UDP編程範例</h2>

```C
socket(AF_INET, SOCK_DGRAM, 0);
```

[Server範例](./[第4篇]_嵌入式Linux應用開發基礎知識/source/12_socket/udp/server.c)

使用connect + send

- [Client範例1](./[第4篇]_嵌入式Linux應用開發基礎知識/source/12_socket/udp/client.c)

不使用connect + sendto(含有目的)

- [Client範例2](./[第4篇]_嵌入式Linux應用開發基礎知識/source/12_socket/udp2/client.c)

<h1 id="9">09_多線程編程</h1>

[參考資料]

### 為什麼要使用多線程

使用多線程的話，可以獨立地處理不同事件，使代碼更加簡潔

假設要做 2 件事，一件需要阻塞等待，另一件需要實時進行，如播放器一邊在屏幕播放視頻，一邊在等待用戶的按鍵操作。如果使用單線程必須一會查詢有無按鍵，一會播放視頻，查詢案件太久就會導致視頻卡頓，視頻播放太久就無法及時響應用戶的操作，透過多線程即可解決此問題

### 線程的概念

線程：作業系統所能調度的最小單位

普通的進程：只有一個線程在執行對應的程序

多線程編程：使一個進程可以去執行多個不同的任務

相比多進程編程而言，線程享有共享資源，即在進程中出現的全局變量，每個線程都可以去訪問它，與進程共享 4G 內存空間，使得系統資源消耗減少

調度的最小單位為線程，分配內存的最小單位為進程

`ps`：查看進程

`ps -T`：查看線程

`ps -T -p <pid>`： 查看某進程的線程

### 編程演示

創建線程

![img66](./[第4篇]_嵌入式Linux應用開發基礎知識/img66.PNG)

- [pthread1.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/13_thread/pthread1.c)

主線程讀取標準輸入, 發給**接收線程**

- [pthread2.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/13_thread/pthread2.c)

同步操作，透過信號量修改while (g_hasData == 0);死循環占用大量CPU資源

```C
// 初始化
#include <semaphore.h>
int sem_init(sem_t *sem,int pshared,unsigned int value);

等待/释放：
#include <pthread.h>
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
```

- [pthread3.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/13_thread/pthread3.c)

互斥訪問，避免同時訪問導致獲得的變量不一致

```C
static pthread_mutex_t g_tMutex  = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&g_tMutex);

pthread_mutex_unlock(&g_tMutex);
```

- [pthread4.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/13_thread/pthread4.c)

同步操作，條件變量

```C
static pthread_cond_t  g_tConVar = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t g_tMutex  = PTHREAD_MUTEX_INITIALIZER;

/*線程A: 等待條件成立*/
pthread_mutex_lock(&g_tMutex);
pthread_cond_wait(&g_tConVar, &g_tMutex);   /*等待條件成立，並釋放互斥變量，條件成立時，獲取互斥變量*/
/* 操作臨界資源 */
pthread_mutex_unlock(&g_tMutex);

/*線程B: 喚醒等待g_tConVar的線程*/
pthread_cond_signal(&g_tConVar);
```

- [pthread5.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/13_thread/pthread5.c)

<h1 id="10">10_UART串口介紹</h1>

<h2 id="10.1">10-1_串口應用程序編程介紹</h2>

UART：通用異步收發傳輸器（Universal Asynchronous Receiver/Transmitter)，簡稱串口。

- 調試：移植u-boot、內核、應用程序時，主要使用串口查看打印信息
- 外接各種模塊：GPS、藍芽......等等

    ![img67](./[第4篇]_嵌入式Linux應用開發基礎知識/img67.PNG)

<h2 id="10.2">10-2_UART硬件介紹</h2>

### 1. 串口的硬件介紹

UART的全稱是**Universal Asynchronous Receiver and Transmitter**，即異步發送和接收。
串口在嵌入式中用途非常的廣泛，主要的用途有：

* **打印調試信息**；
* **外接各種模塊**：GPS、藍牙、Radar；

串口因為結構簡單、穩定可靠，廣受歡迎。

通過三根線即可，發送、接收、地線。

<img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_001.jpg">

通過TxD->RxD把ARM開發板要發送的信息發送給PC機。
通過RxD->TxD線把PC機要發送的信息發送給ARM開發板。
最下面的地線統一參考地。

### 2. 串口的參數

- 波特率：一般選波特率都會有9600,19200,115200等選項。其實意思就是每秒傳輸這麼多個比特位數(bit)。
- 起始位:先發出一個邏輯”0”的信號，表示傳輸數據的開始。
- 數據位：可以是5~8位邏輯”0”或”1”。如ASCII碼（7位），擴展BCD碼（8位）。小端傳輸。
- 校驗位：數據位加上這一位後，使得“1”的位數應為偶數(偶校驗)或奇數(奇校驗)，以此來校驗數據傳送的正確性。
- 停止位：它是一個字符數據的結束標誌。

    ![img02](./[第4篇]_嵌入式Linux應用開發基礎知識/img69.PNG)

- 縮寫: 115200, 8n1 ---> baudrate=115200, 8bits Data, n 沒有校驗位, 1 停止位為high

**怎麼發送一字節數據，比如‘A‘?**

‘A’的ASCII值是**0x41**,二進制就是**01000001**，怎樣把這8位數據發送給PC機呢？

* 雙方約定好波特率（每一位(bit)佔據的時間）；

* 規定傳輸協議

  *  **原來是高電平，ARM拉低電平，保持1bit時間**；
  *  PC在低電平開始處計時；
  *  ARM根據數據依次驅動TxD的電平，同時PC依次讀取RxD引腳電平，獲得數據；

  <img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_002.jpg">

前面圖中提及到了邏輯電平，也就是說代表信號1的引腳電平是人為規定的。
如圖是**TTL/CMOS邏輯電平**下，傳輸‘A’時的波形：

<img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_003.jpg">

* 在xV至5V之間，就認為是邏輯1
* 在0V至yV之間就為邏輯0

如圖是**RS-232邏輯電平**下，傳輸‘A’時的波形：

<img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_004.jpg">

* 在-12V至-3V之間，就認為是邏輯1
* 在+3V至+12V之間就為邏輯0

**RS-232的電平比TTL/CMOS高，能傳輸更遠的距離，在工業上用得比較多。**

市面上大多數ARM芯片都不止一個串口，一般使用串口0來調試，其它串口來外接模塊。

### 3. 串口電平

ARM芯片上得串口都是TTL電平的，通過板子上或者外接的**電平轉換芯片**，轉成RS232接口，連接到電腦的RS232串口上，實現兩者的數據傳輸。

<img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_005.jpg">

現在的電腦越來越少有RS232串口的接口，當USB是幾乎都有的。因此使用**USB串口芯片**將ARM芯片上的TTL電平轉換成USB串口協議，即可通過USB與電腦數據傳輸。

<img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_006.jpg">

上面的兩種方式，對ARM芯片的編程操作都是一樣的。

### 4. 串口內部結構

ARM芯片是如何發送/接收數據？
如圖所示串口結構圖：

<img src="./[第4篇]_嵌入式Linux應用開發基礎知識/lesson1_007.bmp">

* 要發送數據時
  * CPU控制內存要發送的數據通過FIFO傳給UART單位，
  * UART裡面的移位器，依次將數據發送出去，
  * 在發送完成後產生中斷提醒CPU傳輸完成。

* 接收數據時
  * 獲取接收引腳的電平，逐位放進接收移位器，
  * 再放入FIFO，寫入內存。
  * 在接收完成後產生中斷提醒CPU傳輸完成。

<h2 id="10.3">10-3_TTY體系中設備節點的差別</h2>

TTY的歷史來源

- TELETYPE

    ![img70](./[第4篇]_嵌入式Linux應用開發基礎知識/img70.PNG)

- 以前電腦不普及，因此會多個終端共用一台電腦

    ![img71](./[第4篇]_嵌入式Linux應用開發基礎知識/img71.PNG)

    ![img72](./[第4篇]_嵌入式Linux應用開發基礎知識/img72.PNG)

- 終端升級，不再透過串口(UART)，但其驅動仍在TTY體系

    ![img73](./[第4篇]_嵌入式Linux應用開發基礎知識/img73.PNG)

- 個人電腦與虛擬終端

    ![img74](./[第4篇]_嵌入式Linux應用開發基礎知識/img74.PNG)

下圖中兩條紅線之內的代碼被稱為TTY子系統

![img75](./[第4篇]_嵌入式Linux應用開發基礎知識/img75.PNG)

- 會有多個虛擬終端可以共同使用同一個display, keyboard終端

- /dev/tty：代表當前終端

- UART串口不會使用虛擬終端

Console

![img76](./[第4篇]_嵌入式Linux應用開發基礎知識/img76.PNG)

![img77](./[第4篇]_嵌入式Linux應用開發基礎知識/img77.PNG)

- 可利用 `cat /proc/cmdline` 來取得目前的 cmdline 是什麼

    ```bash
    32bits-Arm $ cat /proc/cmdline
    console=ttyS0 noinitrd root=/dev/mmcblk0p7 rw rootfstype=ext4 init=/linuxrc rootwait

    chicony@ubuntu:~$ cat /proc/cmdline 
    BOOT_IMAGE=/boot/vmlinuz-4.4.0-142-generic root=UUID=696523e2-dd6d-43d8-8c1e-f0c45f05e24f ro splash quiet
    ```

<h2 id="10.4">10-4_TTY驅動程序框架</h2>

什麼是行規程(line discipline)

- 當我們在一個終端上按下按鍵 `l` 的時候，終端只是把字母 `l` 回顯了回來，緊接著按下按鍵 `s`，依然是回顯字母 `s`，隨後我們按下回車鍵，回顯的不再是回車鍵(請問怎麼回顯)，而是列出並顯示了當前目錄下的所有文件，這些規則是如何定義的？

- 當我們按下組合鍵 `Ctrl-C` 的時候，當前的進程就終止了，這個又是如何規定的？為什麼不是組合鍵 `Shift-B` 來完成同樣的事？

- 所有這些問題都可以用行規程來回答，行規程是一套約定俗成的協議。約定雙方可以是計算機和終端(包括輸出設備和人體輸入設備)。

- 行規程規定了鍵盤，串口，打印機，顯示器等輸入輸出設備和用戶態Shell等程序之間的行為規範，鍵盤上的按鍵事件被行規程解釋成了Shell可以理解的輸入並給出相應的輸出。人們要想操作計算機，這套規程是必不可少的，它事實上規定了信息從外部進入計算機的規範。

使用場景

![img78](./[第4篇]_嵌入式Linux應用開發基礎知識/img78.PNG)

TTY驅動程序框架

![img79](./[第4篇]_嵌入式Linux應用開發基礎知識/img79.PNG)

<h2 id="10.5">10-5_串口(UART)應用編程</h2>

[Serial Programming Guide for POSIX Operating Systems](https://digilander.libero.it/robang/rubrica/serial.htm#CONTENTS)

### 串口API

![img78](./[第4篇]_嵌入式Linux應用開發基礎知識/img78.PNG)

在Linux系統中，操作設備的統一接口就是：open/ioctl/read/write

對於UART，又在ioctl之上封裝了很多函數，主要是用來設置行規程(line sidcipline)

所以對於UART編程的套路如下：

- open
- 設置行規程，如波特率, 數據位, 停止位, 檢驗位, RAW模式, 一有數據就返回
- read/write

行規程的參數用 `結構體termios` 來表示，[Linux串口—struct termios结构体](https://blog.csdn.net/yemingzhu163/article/details/5897156)

```C
typedef unsigned char	cc_t;
typedef unsigned int	speed_t;
typedef unsigned int	tcflag_t;

#define NCCS 32
struct termios
{
    tcflag_t c_iflag;		/* input mode flags */
    tcflag_t c_oflag;		/* output mode flags */
    tcflag_t c_cflag;		/* control mode flags */
    tcflag_t c_lflag;		/* local mode flags */
    cc_t c_line;		/* line discipline */
    cc_t c_cc[NCCS];		/* control characters */
    speed_t c_ispeed;		/* input speed */
    speed_t c_ospeed;		/* output speed */
#define _HAVE_STRUCT_TERMIOS_C_ISPEED 1
#define _HAVE_STRUCT_TERMIOS_C_OSPEED 1
};
```

![img80](./[第4篇]_嵌入式Linux應用開發基礎知識/img80.PNG)

### 串口回環範例

[serial_send_recv.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/14_UART/01_app_send_recv/serial_send_recv.c)

開啟串口

```C
int open_port(char *com)
{
    int fd;
    //fd = open(com, O_RDWR|O_NOCTTY|O_NDELAY);
    fd = open(com, O_RDWR|O_NOCTTY);
    if (-1 == fd){
        return(-1);
    }

        if(fcntl(fd, F_SETFL, 0)<0) /* 设置串口为阻塞状态*/
        {
            printf("fcntl failed!\n");
            return -1;
        }

        return fd;
}
```

- O_NOCTTYl：設置其不作為控制終端，即不會把`ctrl+C`視為控制命令，而是當作raw data

- fcntl

    ![img81](./[第4篇]_嵌入式Linux應用開發基礎知識/img81.PNG)

- 設置 波特率, 數據位, 停止位, 檢驗位, 讀多少數據或多久返回

    ```C
    /* set_opt(fd,115200,8,'N',1) */
    int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
    {
        struct termios newtio,oldtio;

        if ( tcgetattr( fd,&oldtio) != 0) { 
            perror("SetupSerial 1");
            return -1;
        }

        bzero( &newtio, sizeof( newtio ) );
        newtio.c_cflag |= CLOCAL | CREAD; 
        newtio.c_cflag &= ~CSIZE; 

        newtio.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
        newtio.c_oflag  &= ~OPOST;   /*Output*/

        switch( nBits )
        {
        case 7:
            newtio.c_cflag |= CS7;
        break;
        case 8:
            newtio.c_cflag |= CS8;
        break;
        }

        switch( nEvent )
        {
        case 'O':
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
        break;
        case 'E': 
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
        break;
        case 'N': 
            newtio.c_cflag &= ~PARENB;
        break;
        }

        switch( nSpeed )
        {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
        break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
        break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
        break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
        break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
        break;
        }

        if( nStop == 1 )
            newtio.c_cflag &= ~CSTOPB;
        else if ( nStop == 2 )
            newtio.c_cflag |= CSTOPB;

        newtio.c_cc[VMIN]  = 1;  /* 读数据时的最小字节数: 没读到这些数据我就不返回! */
        newtio.c_cc[VTIME] = 0; /* 等待第1个数据的时间: 
                                    * 0: 代表永遠等待
                                    * 比如VMIN设为10表示至少读到10个数据才返回,
                                    * 但是没有数据总不能一直等吧? 可以设置VTIME(单位是10秒)
                                    * 假设VTIME=1，表示: 
                                    *    10秒内一个数据都没有的话就返回
                                    *    如果10秒内至少读到了1个字节，那就继续等待，完全读到VMIN个数据再返回
                                    */

        tcflush(fd,TCIFLUSH);

        if((tcsetattr(fd,TCSANOW,&newtio))!=0)
        {
            perror("com set error");
            return -1;
        }
        //printf("set done!\n");
        return 0;
    }
    ```

### GPS範例

[gps_read.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/14_UART/02_gps/gps_read.c)

讀取raw data：

```C
/* eg. $GPGGA,082559.00,4005.22599,N,11632.58234,E,1,04,3.08,14.6,M,-5.6,M,,*76"<CR><LF>*/
int read_gps_raw_data(int fd, char *buf)
{
    int i = 0;
    int iRet;
    char c;
    int start = 0;

    while (1)
    {
        iRet = read(fd, &c, 1);
        if (iRet == 1)
        {
            if (c == '$')
                start = 1;
            if (start)
            {
                buf[i++] = c;
            }
            if (c == '\n' || c == '\r')
                return 0;
        }
        else
        {
            return -1;
        }
    }
}
```

解析數據

```C
/* eg. $GPGGA,082559.00,4005.22599,N,11632.58234,E,1,04,3.08,14.6,M,-5.6,M,,*76"<CR><LF> */
int parse_gps_raw_data(char *buf, char *time, char *lat, char *ns, char *lng, char *ew)
{
    char tmp[10];

    if (buf[0] != '$')
        return -1;
    else if (strncmp(buf+3, "GGA", 3) != 0)
        return -1;
    else if (strstr(buf, ",,,,,"))
    {
        printf("Place the GPS to open area\n");
        return -1;
    }
    else {
        //printf("raw data: %s\n", buf);
        sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", tmp, time, lat, ns, lng, ew);
        return 0;
    }
}
```

<h1 id="11">11_I2C介紹</h1>

<h2 id="11.1">11-1_I2C應用程序編程介紹</h2>

硬件架構

![img82](./[第4篇]_嵌入式Linux應用開發基礎知識/img82.PNG)

軟件架構

![img83](./[第4篇]_嵌入式Linux應用開發基礎知識/img83.PNG)

<h2 id="11.2">11-2_I2C協議</h2>

[i2c_spec.pdf](./[第4篇]_嵌入式Linux應用開發基礎知識/doc/i2c_spec.pdf)

### 硬件連接

![img84](./[第4篇]_嵌入式Linux應用開發基礎知識/img84.PNG)

### 傳輸數據類比

![img85](./[第4篇]_嵌入式Linux應用開發基礎知識/img85.PNG)

![img86](./[第4篇]_嵌入式Linux應用開發基礎知識/img86.PNG)

### IIC傳輸數據的格式

![img87](./[第4篇]_嵌入式Linux應用開發基礎知識/img87.PNG)

![img88](./[第4篇]_嵌入式Linux應用開發基礎知識/img88.PNG)

![img89](./[第4篇]_嵌入式Linux應用開發基礎知識/img89.PNG)

![img92](./[第4篇]_嵌入式Linux應用開發基礎知識/img92.PNG)

![img90](./[第4篇]_嵌入式Linux應用開發基礎知識/img90.PNG)

![img91](./[第4篇]_嵌入式Linux應用開發基礎知識/img91.PNG)

<h2 id="11.3">11-3_SMBus協議</h2>

參考資料：

- Linux內核文檔： Documentation\i2c\smbus-protocol.rst
- SMBus協議： http://www.smbus.org/specs/
- [SMBus_3_0_20141220.pdf](./[第4篇]_嵌入式Linux應用開發基礎知識/doc/SMBus_3_0_20141220.pdf)
- I2CTools: https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/

### SMBus是I2C協議的一個子集

![img93](./[第4篇]_嵌入式Linux應用開發基礎知識/img93.PNG)

![img94](./[第4篇]_嵌入式Linux應用開發基礎知識/img94.PNG)

### SMBus協議分析

對於I2C協議，它只定義了怎麼傳輸數據，但是並沒有定義數據的格式，這完全由設備來定義。

對於SMBus協議，它定義了幾種數據格式。

下面文檔中的 `Functionality flag` 是Linux的某個I2C控制器驅動所支持的功能。
比如 `Functionality flag: I2C_FUNC_SMBUS_QUICK`，表示需要I2C控制器支持 `SMBus Quick Command`

![img95](./[第4篇]_嵌入式Linux應用開發基礎知識/img95.PNG)

![img96](./[第4篇]_嵌入式Linux應用開發基礎知識/img96.PNG)

![img97](./[第4篇]_嵌入式Linux應用開發基礎知識/img97.PNG)

![img98](./[第4篇]_嵌入式Linux應用開發基礎知識/img98.PNG)

![img99](./[第4篇]_嵌入式Linux應用開發基礎知識/img99.PNG)

![img100](./[第4篇]_嵌入式Linux應用開發基礎知識/img100.PNG)

![img101](./[第4篇]_嵌入式Linux應用開發基礎知識/img101.PNG)

![img102](./[第4篇]_嵌入式Linux應用開發基礎知識/img102.PNG)

### SMBus和I2C的建議

因為很多設備都實現了SMBus，而不是更寬泛的I2C協議，所以優先使用SMBus。

即使I2C控制器沒有實現SMBus，軟件方面也是可以使用I2C協議來模擬SMBus。

所以：Linux建議優先使用SMBus。

<h2 id="11.4">11-4_I2C系統的重要結構體</h2>

參考資料：

- Linux驅動程序: drivers/i2c/i2c-dev.c

- I2CTools: https://mirrors.edge.kernel.org/pub/software/utils/i2c-tools/

### I2C硬件框架

![img103](./[第4篇]_嵌入式Linux應用開發基礎知識/img103.PNG)

### I2C傳輸協議

![img104](./[第4篇]_嵌入式Linux應用開發基礎知識/img104.PNG)

### Linux軟件框架

![img105](./[第4篇]_嵌入式Linux應用開發基礎知識/img105.PNG)

### 重要結構體

使用一句話概括I2C傳輸：APP通過I2C Controller與I2C Device傳輸數據。

在Linux中：

- 怎麼表示I2C Controller
  - 一個芯片裡可能有多個I2C Controller，比如第0個、第1個、……
  - 對於使用者，只要確定是第幾個I2C Controller即可
  - 使用i2c_adapter表示一個I2C BUS，或稱為I2C Controller
  - 裡面有2個重要的成員：
    - nr：第幾個I2C BUS(I2C Controller)
    - i2c_algorithm，裡面有該I2C BUS的傳輸函數，用來收發I2C數據
  - i2c_adapter

    ![img106](./[第4篇]_嵌入式Linux應用開發基礎知識/img106.PNG)

  - i2c_algorithm

    ![img107](./[第4篇]_嵌入式Linux應用開發基礎知識/img107.PNG)

- 怎麼表示I2C Device
  - 一個I2C Device，一定有設備地址
  - 它連接在哪個I2C Controller上，即對應的i2c_adapter是什麼
  - 使用i2c_client來表示一個I2C Device

    ![img108](./[第4篇]_嵌入式Linux應用開發基礎知識/img108.PNG)

  - 怎麼表示要傳輸的數據
    - 在上面的i2c_algorithm結構體中可以看到要傳輸的數據被稱為：i2c_msg
    - i2c_msg

        ![img109](./[第4篇]_嵌入式Linux應用開發基礎知識/img109.PNG)

  - i2c_msg中的flags用來表示傳輸方向：bit 0等於I2C_M_RD表示讀，bit 0等於0表示寫
  - 一個i2c_msg要麼是讀，要麼是寫
  - 舉例：設備地址為0x50的EEPROM，要讀取它裡面存儲地址為0x10的一個字節，應該構造幾個i2c_msg？
    - 要構造2個i2c_msg
    - 第一個i2c_msg表示寫操作，把要訪問的存儲地址0x10發給設備
    - 第二個i2c_msg表示讀操作
    - 代碼如下

        ![img110](./[第4篇]_嵌入式Linux應用開發基礎知識/img110.PNG)

### 內核裡怎麼傳輸數據

使用一句話概括I2C傳輸：

- APP通過I2C Controller與I2C Device傳輸數據
- APP通過i2c_adapter與i2c_client傳輸i2c_msg
- 內核函數i2c_transfer
  - i2c_msg裡含有addr，所以這個函數里不需要i2c_client

    ![img111](./[第4篇]_嵌入式Linux應用開發基礎知識/img111.PNG)

<h2 id="11.5">11-5_無須編寫驅動直接訪問設備_I2C-tool</h2>

### 無需編寫驅動程序即可訪問I2C設備

APP訪問硬件肯定是需要驅動程序的

對於I2C設備，內核提供了驅動程序drivers/i2c/i2c-dev.c ，通過它可以直接使用下面的I2C控制器
驅動程序來訪問I2C設備。

框架如下：

![img112](./[第4篇]_嵌入式Linux應用開發基礎知識/img112.PNG)

i2c-tools是一套好用的工具，也是一套示例代碼。

### 體驗I2C-Tools

使用一句話概括I2C傳輸：APP通過I2C Controller與I2C Device傳輸數據。

所以使用I2C-Tools時也需要指定：

- 哪個I2C控制器(或稱為I2C BUS、I2C Adapter)
- 哪個I2C設備(設備地址)
- 數據：讀還是寫、數據本身

![img113](./[第4篇]_嵌入式Linux應用開發基礎知識/img113.PNG)

![img114](./[第4篇]_嵌入式Linux應用開發基礎知識/img114.PNG)

`i2cdetect`：I2C檢測

![img115](./[第4篇]_嵌入式Linux應用開發基礎知識/img115.PNG)

![img116](./[第4篇]_嵌入式Linux應用開發基礎知識/img116.PNG)

`i2cget`：I2C讀

![img117](./[第4篇]_嵌入式Linux應用開發基礎知識/img117.PNG)

`i2cset`：I2C寫

![img118](./[第4篇]_嵌入式Linux應用開發基礎知識/img118.PNG)

![img119](./[第4篇]_嵌入式Linux應用開發基礎知識/img119.PNG)

`i2ctransfer`：I2C傳輸(不是基於SMBus)

![img120](./[第4篇]_嵌入式Linux應用開發基礎知識/img120.PNG)

使用I2C-Tools操作傳感器AP3216C

![img121](./[第4篇]_嵌入式Linux應用開發基礎知識/img121.PNG)

### I2C-Tools的訪問I2C設備的2種方式

I2C-Tools可以通過SMBus來訪問I2C設備，也可以使用一般的I2C協議來訪問I2C設備。

使用一句話概括I2C傳輸：APP通過I2C Controller與I2C Device傳輸數據。

在APP裡，有這幾個問題：

- 怎麼指定I2C控制器？
  - i2c-dev.c提供為每個I2C控制器(I2C Bus、I2C Adapter)都生成一個設備節點：`/dev/i2c-0`、`/dev/i2c-1`等待
  - open某個`/dev/i2c-X`節點，就是去訪問該I2C控制器下的設備

- 怎麼指定I2C設備？
  - 通過ioctl指定I2C設備的地址
  - `ioctl(file, I2C_SLAVE, address)`
    - 如果該設備已經有了對應的設備驅動程序，則返回失敗
  - `ioctl(file, I2C_SLAVE_FORCE, address)`
    - 如果該設備已經有了對應的設備驅動程序，但是還是想通過i2c-dev驅動來訪問它，則使用這個ioctl來指定I2C設備地址
  - 怎麼傳輸數據？兩種方式
    - 一般的I2C方式：`ioctl(file, I2C_RDWR, &rdwr)`
    - SMBus方式：`ioctl(file, I2C_SMBUS, &args)`

### 源碼分析

使用I2C的方式: `i2ctransfer.c`

[i2cbusses.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/15_I2C/01_at24c02_test/i2cbusses.c)

![img122](./[第4篇]_嵌入式Linux應用開發基礎知識/img122.PNG)

使用SMBus的方式: `i2cget.c`、`i2cset.c`

[smbus.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/15_I2C/01_at24c02_test/smbus.c)

![img123](./[第4篇]_嵌入式Linux應用開發基礎知識/img123.PNG)

<h2 id="11.6">11-6_編寫APP直接訪問EEPROM</h2>

### 硬件連接

![img124](./[第4篇]_嵌入式Linux應用開發基礎知識/img124.PNG)

### AT24C02訪問方法

![img125](./[第4篇]_嵌入式Linux應用開發基礎知識/img125.PNG)

![img126](./[第4篇]_嵌入式Linux應用開發基礎知識/img126.PNG)

![img127](./[第4篇]_嵌入式Linux應用開發基礎知識/img127.PNG)

根據 [i2cbusses.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/15_I2C/01_at24c02_test/i2cbusses.c) 與 [smbus.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/15_I2C/01_at24c02_test/smbus.c) 撰寫AT24C02訪問範例 [at24c02_test.c](./[第4篇]_嵌入式Linux應用開發基礎知識/source/15_I2C/01_at24c02_test/at24c02_test.c)

```C
int open_i2c_dev(int i2cbus, char *filename, size_t size, int quiet)
{
    int file, len;

    len = snprintf(filename, size, "/dev/i2c/%d", i2cbus);
    if (len >= (int)size) {
        fprintf(stderr, "%s: path truncated\n", filename);
        return -EOVERFLOW;
    }
    file = open(filename, O_RDWR);

    if (file < 0 && (errno == ENOENT || errno == ENOTDIR)) {
        len = snprintf(filename, size, "/dev/i2c-%d", i2cbus);
        if (len >= (int)size) {
            fprintf(stderr, "%s: path truncated\n", filename);
            return -EOVERFLOW;
        }
        file = open(filename, O_RDWR);
    }

    if (file < 0 && !quiet) {
        if (errno == ENOENT) {
            fprintf(stderr, "Error: Could not open file "
                "`/dev/i2c-%d' or `/dev/i2c/%d': %s\n",
                i2cbus, i2cbus, strerror(ENOENT));
        } else {
            fprintf(stderr, "Error: Could not open file "
                "`%s': %s\n", filename, strerror(errno));
            if (errno == EACCES)
                fprintf(stderr, "Run as root?\n");
        }
    }

    return file;
}
```

```C
int set_slave_addr(int file, int address, int force)
{
    /* With force, let the user read from/write to the registers
        even when a driver is also running */
    if (ioctl(file, force ? I2C_SLAVE_FORCE : I2C_SLAVE, address) < 0) {
        fprintf(stderr,
            "Error: Could not set address to 0x%02x: %s\n",
            address, strerror(errno));
        return -errno;
    }

    return 0;
}
```

```C
__s32 i2c_smbus_write_byte_data(int file, __u8 command, __u8 value)
{
    union i2c_smbus_data data;
    data.byte = value;
    return i2c_smbus_access(file, I2C_SMBUS_WRITE, command, I2C_SMBUS_BYTE_DATA, &data);
}
```

```C
__s32 i2c_smbus_read_i2c_block_data(int file, __u8 command, __u8 length, __u8 *values)
{
    union i2c_smbus_data data;
    int i, err;

    if (length > I2C_SMBUS_BLOCK_MAX)
        length = I2C_SMBUS_BLOCK_MAX;
    data.block[0] = length;

    err = i2c_smbus_access(file, I2C_SMBUS_READ, command,
                    length == 32 ? I2C_SMBUS_I2C_BLOCK_BROKEN :
                I2C_SMBUS_I2C_BLOCK_DATA, &data);
    if (err < 0)
        return err;

    for (i = 1; i <= data.block[0]; i++)
        values[i-1] = data.block[i];
    return data.block[0];
}
```
