# 目錄

- [Note](#0)
- [01_嵌入式Linux开发环境介绍](#1)
- [02_配置VMware使用双网卡之NAT网卡](#2)
- [03_配置VMware使用双网之桥接网卡(USB网卡)_STM32MP157_Pro](#3)
- [04_配置VMware使用双网之桥接网卡(路由器)_STM32MP157_Pro](#4)
- [05_安装软件_远程登录_传文件](#5)
- [06_下载BSP_配置工具链_STM32MP157_Pro](#6)
- [07_传输源码并创建sourceinsight工程_STM32MP157_Pro](#7)



<h1 id="0">Note</h1>

[第3篇：环境搭建与开发板操作](https://www.100ask.net/detail/p_63018b58e4b0c942648a74d0/6)

<h1 id="1">01_嵌入式Linux开发环境介绍</h1>

- 單晶片

    ![img00](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img00.PNG)

- 嵌入式Linux

    ![img01](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img01.PNG)

    ![img02](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img02.PNG)

    ![img03](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img03.PNG)

<h1 id="2">02_配置VMware使用双网卡之NAT网卡</h1>

![img04](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img04.PNG)

![img05](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img05.PNG)

![img06](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img06.PNG)

<h1 id="3">03_配置VMware使用双网之桥接网卡(USB网卡)_STM32MP157_Pro</h1>

- 設置VMware, Windows與開發版的網路配置

    ![img07](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img07.PNG)

    ![img08](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img08.PNG)

- 在VMware中新增`橋接網卡`，且以管理員身份運行虛擬網路編輯器(vmnet)，從中手動選擇要橋接的網卡為USB網卡

- 設置VMware與Windows USB IP

- 設置開發版IP
  - 進入console後，手動下指令配置IP

    ```Shell
    ifconfig eth0 192.168.5.9
    ```

    ![img09](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img09.PNG)

  - 設置IP為固定IP，每次開機都不變

    ```Shell
    vi /etc/systemd/network/50-static.network

    [Match]
        Name=eth0
    [Network]
        Address=192.168.5.9/24
        Gateway=192.168.5.1
    ```

    ![img10](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img10.PNG)

<h1 id="4">04_配置VMware使用双网之桥接网卡(路由器)_STM32MP157_Pro</h1>

- 配置橋接網卡，除了使用**USB網卡**之外，也可以使用**路由器**(透過有線或無線)

    ![img11](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img11.PNG)

- 開發版透過路由器自動配置IP
  - 若有固定IP的文件，要刪除它

    ```Shell
    rm /etc/systemd/network/50-static.network
    ```

  - 若路由器沒有自動配置的話，可以執行下方指令

    ```Shell
    udhcpc -i eth0
    ```

    ![img12](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img12.PNG)

<h1 id="5">05_安装软件_远程登录_传文件</h1>

- MobaXterm 遠程登錄串口程序

- Linux 安裝FTP

    https://codertw.com/%E7%A8%8B%E5%BC%8F%E8%AA%9E%E8%A8%80/722619/

<h1 id="6">06_下载BSP_配置工具链_STM32MP157_Pro</h1>

- BSP為開發版相關的配置檔案

- 配置編譯code的工具鏈

    ![img13](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img13.PNG)

<h1 id="7">07_传输源码并创建sourceinsight工程_STM32MP157_Pro</h1>

- Source Insight 為閱讀與編輯源碼的軟體

<h1 id="8">08_启动方式与连接串口_STM32MP157_Pro</h1>

- 選擇開發版要啟動的模式

    ![img14](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img14.PNG)

- 當開發版接USB至PC後，基本上Windows會自動安裝USB驅動程序，若沒有或是跳出警告讀不到USB驅動程序，則需要自行手動安裝

    ![img15](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img15.PNG)

    ![img16](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img16.PNG)

- 通常開發版串口的配置參數

    ![img17](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img17.PNG)


----------------------------------start

<h1 id="9">09_开发板挂载Ubuntu的NFS目录_STM32MP157_Pro</h1>

**什麼是NFS協議?**

- NFS實現了一個跨越網絡的文件訪問功能，如下圖可以簡要說明其原理。其整個架構為Client-Server架構，客戶端和服務端通過RPC協議進行通信，RPC協議可以簡單的理解為一個基於TCP的應用層協議，它簡化命令和數據的傳輸。

- NFS最大的特點是將服務端的文件系統目錄樹映射到客戶端，而在客戶端訪問該目錄樹與訪問本地文件系統沒有任何差別，客戶端並不知道這個文件系統目錄樹是本地的還是遠在另外一台服務器。

    ![img18](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img18.PNG)

- 我們為什麼要掛載ubuntu的nfs目錄？
我們有些時候需要多次調試開發板文件系統內的某個應用程序，這就需要多次進行編譯拷貝等操作，所以我們在前期進行調試時可以直接讓開發板使用ubuntu的nfs目錄下文件系統來進行遠程調試，用以提高調試效率，加快研發速度。

**在Ubuntu中安裝、配置NFS**

- Ubuntu未安裝NFS服務，那麼在確保Ubuntu可以上網的前提下，執行以下命令：

    ```Shell
    sudo apt-get install nfs-kernel-server
    ```

- 還得修改/etc/exports，添加類似以下的內容，下面的例子裡允許開發板通過NFS訪問Ubuntu的/home/book目錄：

    ```Shell
    /home/book   *(rw,nohide,insecure,no_subtree_check,async,no_root_squash)
    ```

- 重啟NFS服務，在Ubuntu上執行以下命令：

    ```Shell
    sudo /etc/init.d/nfs-kernel-server restart
    ```

- 若Ubuntu有安裝NFS服務，可以查看一下/etc/exports的內容，就知道開發板可以掛載哪一個目錄。


**确定ubuntu的网卡和IP**

- 在Ubuntu终端下使用ifconfig命令来查看桥接模式获取到的网卡 

    ![img19](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro)/img19.PNG)

**在开发板上执行mount nfs命令**

- ubuntu的IP是192.168.5.11，確保開發板能ping通ubuntu後，在開發板上執行以下命令掛載NFS：

    ```Shell
    mount -t nfs -o nolock,vers=3 192.168.５.1１:/home/book/nfs_rootfs /mnt
    ```

- mount成功之後，開發板在/mnt目錄下讀寫檔時，實際上訪問的就是Ubuntu中的/home/book/nfs_rootfs目錄，所以開發板和Ubuntu之間通過NFS可以很方便地共用檔。

- 在開發過程中，在Ubuntu中編譯好程式後放入/home/book/nfs_rootfs目錄，開發板mount nfs後就可以直接使用/mnt下的檔。

- 開發板上不一定安裝有FTP服務、SSH等服務，所以不一定能使用FTP等工具登錄開發板。

- 但是開發板的系統一般都自帶mount命令，並且支援NFS檔案系統。所以可以在開發板上執行mount命令掛載Ubuntu的某個目錄。這樣就可以在開發板和Ubuntu之間傳檔了。

<h1 id="10">10_开发板的第1个APP</h1>

- 編譯指令

    ```Shell
    # PC機編譯器時用的命令是：
    gcc  -o  hello  hello.c

    # 開發板編譯器時用的命令類似下述命令(不同的開發板gcc的首碼可能不同)：
    arm-buildroot-linux-gnueabihf-gcc  -o  hello  hello.c
    ```

## 配置交叉編譯工具鏈

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




