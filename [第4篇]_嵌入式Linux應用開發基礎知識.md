# 目錄

- [Note](#0)
- [01_Hello程序](#1)
  - [1-1_NFS應用](#1.1)
  - [1-2_配置交叉編譯工具鏈](#1.2)
- [02_GCC](#2)
  - [2-1_GCC編譯過程](#2.1)
  - [2-2_GCC常用選項](#2.2)
- [03_Makefile](#3)
  - [3-1_Makefile要達成的效果](#3.1)
  - [3-2_Makefile的引入與規則](#3.2)
  - [3-3_Makefile的語法](#3.3)

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

<h1 id="2">02_GCC</h1>

<h2 id="2.1">2-1_GCC編譯過程</h2>

- 機器只能讀取機器碼(即二進制的程式，非0即1)

- 程式的成長流程

    ![img01](./[第4篇]_嵌入式Linux應用開發基礎知識/img01.PNG)

- `gcc -o hello hello.c` 所完成的動作
  - 可透過加`-v`來查看流程跑了什麼，`gcc -o hello hello.c -v`

    ![img02](./[第4篇]_嵌入式Linux應用開發基礎知識/img02.PNG)

- GCC編譯過程

    ![img03](./[第4篇]_嵌入式Linux應用開發基礎知識/img03.PNG)

- 日常說法會把 `編譯` 代表成 `預處理 -> 編譯 -> 匯編`，接著再鏈結

<h2 id="2.2">2-2_GCC常用選項</h2>

- multi-files 進行編譯：各自匯編成.o檔後，鏈結成一個執行檔

    ```Shell
    gcc -o test main.c sub.c
    ```

    ![img04](./[第4篇]_嵌入式Linux應用開發基礎知識/img04.PNG)

- 當今天有999個文件時，使用這種方式，只要修改一個檔案後，每次重新編譯都會重新編譯999個文件，因此會太消耗資源，所以要先編譯在鏈結，就可以避免掉沒有修改的程式要再重新編譯，較為高效

    ![img05](./[第4篇]_嵌入式Linux應用開發基礎知識/img05.PNG)

- GCC常用選項

    ![img06](./[第4篇]_嵌入式Linux應用開發基礎知識/img06.PNG)

- 靜態庫：

    ![img07](./[第4篇]_嵌入式Linux應用開發基礎知識/img07.PNG)

- 動態庫：

    ![img08](./[第4篇]_嵌入式Linux應用開發基礎知識/img08.PNG)

- 總結

    ![img09](./[第4篇]_嵌入式Linux應用開發基礎知識/img09.PNG)
 
    ![img10](./[第4篇]_嵌入式Linux應用開發基礎知識/img10.PNG)

<h1 id="3">03_Makefile</h1>

<h2 id="3.1">3-1_Makefile要達成的效果</h2>

- 為了能夠高效地編譯程序

- 組織管理程序

- 決定要編譯哪一個文件

<h2 id="3.2">3-2_Makefile的引入與規則</h2>

**Makefile的引入**

- 我們知道.c程序 ==》 得到可執行程序它們之間要經過四個步驟：
    1. 預處理
    2. 編譯
    3. 彙編
    4. 鏈接

- 我們經常把前三個步驟統稱為編譯了。

- 我們具體分析：`gcc -o test a.c b.c`這條命令，它們要經過下面幾個步驟：
    1）對於**a.c**：執行：預處理 編譯 彙編 的過程，**a.c ==>xxx.s ==>xxx.o** 文件。
    2）對於**b.c**：執行：預處理 編譯 彙編 的過程，**b.c ==>yyy.s ==>yyy.o** 文件。
    3）最後：**xxx.o**和**yyy.o**鏈接在一起得到一個**test**應用程序。

    提示：**gcc -o test a.c b.c -v** ：加上一個**‘-v’**選項可以看到它們的處理過程，

- 第一次編譯 a.c 得到 xxx.o 文件，這是很合乎情理的， 執行完第一次之後，如果修改 a.c 又再次執行：`gcc -o test a.c b.c`，對於 a.c 應該重新生成 xxx.o，但是對於 b.c 又會重新編譯一次，這完全沒有必要，b.c 根本沒有修改，直接使用第一次生成的 yyy.o 文件就可以了。

- 因此，對於這些源文件，我們應該分別處理，執行：預處理 編譯 彙編，先分別編譯它們，最後再把它們鏈接在一次，比如：

  - 編譯：

    ```bash
    gcc -o a.o a.c
    gcc -o b.o b.c
    ```

  - 鏈接：

    ```bash
    gcc -o test a.o b.o
    ```

- 比如：上面的例子，當我們修改a.c之後,a.c會重現編譯然後再把它們鏈接在一起就可以了。 `b.c`就不需要重新編譯。

- 如何知道哪些文件被更新了/被修改了？ --> `比較時間`
  - 比較 a.o 和 a.c 的時間，如果a.c的時間比 a.o 的時間更加新的話，就表明 a.c 被修改了，同理b.o和b.c也會進行同樣的比較。
  - 比較test和 a.o,b.o 的時間，如果a.o或者b.o的時間比test更加新的話，就表明應該重新生成test。

**Makefile的規則**

- makefie最基本的語法是規則，規則：

    ```bash
    目標 : 依賴1 依賴2 ...
    [TAB]命令
    ```

- 當**依賴**比**目標**新，執行它們下面的命令。我們要把上面三個命令寫成makefile規則，如下：

    ```bash
    test ：a.o b.o  //test是目標，它依賴於a.o b.o文件，一旦a.o或者b.o比test新的時候，，就需要執行下面的命令，重新生成test可執行程序。
    gcc -o test a.o b.o

    a.o : a.c  //a.o依賴於a.c，當a.c更加新的話，執行下面的命令來生成a.o
    gcc -c -o a.o a.c

    b.o : b.c  //b.o依賴於b.c,當b.c更加新的話，執行下面的命令，來生成b.o
    gcc -c -o b.o b.c
    ```

- 範例: [001_test_app](./%5B%E7%AC%AC4%E7%AF%87%5D_%E5%B5%8C%E5%85%A5%E5%BC%8FLinux%E6%87%89%E7%94%A8%E9%96%8B%E7%99%BC%E5%9F%BA%E7%A4%8E%E7%9F%A5%E8%AD%98/source/04_2018_Makefile/001_test_app/)

<h2 id="3.3">3-3_Makefile的語法</h2>

### Patten - 通配符

- 假如一個目標文件所依賴的依賴文件很多時，我們可以使用通配符，來解決這些繁瑣問題。

    ```bash
    test ：a.o b.o c.o
    gcc -o test a.o b.o

    a.o : a.c
    gcc -c -o a.o a.c

    b.o : b.c
    gcc -c -o b.o b.c

    c.o : c.c
    gcc -c -o c.o c.c
    ```

    ```bash
    test: a.o b.o 
        gcc -o test $^
        
    %.o : %.c
        gcc -c -o $@ $<
    ```

    %.o：表示所用的.o文件
    %.c：表示所有的.c文件
    \$\@：表示目標
    \$\<：表示第1個依賴文件
    \$\^：表示所有依賴文件

- 範例：[001_patten](./%5B%E7%AC%AC4%E7%AF%87%5D_%E5%B5%8C%E5%85%A5%E5%BC%8FLinux%E6%87%89%E7%94%A8%E9%96%8B%E7%99%BC%E5%9F%BA%E7%A4%8E%E7%9F%A5%E8%AD%98/source/04_2018_Makefile/002_syntax/001_patten/)

### 假想目標 .PHONY

1. 我們想清除文件，我們在Makefile的結尾添加如下代碼就可以了：

    ```bash
    test: a.o b.o c.o
        gcc -o test $^
        
    %.o : %.c
        gcc -c -o $@ $<

    clean:
        rm *.o test
    ```

    1）執行 make ：生成第一個可執行文件。
    2）執行 make clean : 清除所有文件，即執行： rm \*.o test。

- make後面可以帶上目標名，也可以不帶，如果不帶目標名的話它就想生成第一個規則裡面的第一個目標。

時間:0713