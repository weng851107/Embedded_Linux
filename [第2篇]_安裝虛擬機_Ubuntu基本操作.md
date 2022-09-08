# 目錄

- [Note](#0)
- [01_安装VMware运行Ubuntu](#1)
- [02_Ubuntu和Windows的简单比较与使用](#2)
- [03_shell命令解析与PATH环境变量](#3)
- [04_目录与文件操作命令](#4)
- [05_权限与属性命令](#5)
- [06_find和grep命令](#6)
- [07_压缩和解压缩命令](#7)
- [08_网络命令](#8)
- [09_VI编辑器_新建_保存_浏览](#9)
- [10_VI编辑器_编辑](#10)
- [11_VI编辑器_复制粘贴查找替换](#11)

<h1 id="0">Note</h1>

[第2篇：安装虚拟机/Ubuntu基本操作](https://www.100ask.net/detail/p_63018801e4b050af23abff16/6?product_id=p_63018801e4b050af23abff16)

<h1 id="1">01_安装VMware运行Ubuntu</h1>

![img00](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img00.PNG)

<h1 id="2">02_Ubuntu和Windows的简单比较与使用</h1>

![img01](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img01.PNG)

- sd代表硬碟，a代表第一個，1代表第一個分區(partition)

    ![img02](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img02.PNG)

    ![img03](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img03.PNG)

- Linux各種文件介紹

    ![img04](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img04.PNG)

    ![img05](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img05.PNG)

<h1 id="3">03_shell命令解析与PATH环境变量</h1>

- Shell

    ![img06](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img06.PNG)

    ![img08](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img08.PNG)

- Linux命令格式

    ![img07](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img07.PNG)

- 透過 `env` 可以查詢Linux目前的環境變量有什麼

- 一般執行應用程序時，會有三種情況可以執行
  - 直接輸入執行檔名稱: `hello`
  - 透過相對路徑來執行: `./hello`
  - 透過絕對路徑來執行: `/home/hello`

    ![img09](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img09.PNG)

- 設置PATH的方式

    ![img10](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img10.PNG)

    ![img11](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img11.PNG)

    ![img12](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img12.PNG)

<h1 id="4">04_目录与文件操作命令</h1>

![img13](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img13.PNG)

![img14](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img14.PNG)

![img31](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img31.PNG)

<h1 id="5">05_权限与属性命令</h1>

![img15](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img15.PNG)

- chmod

    ![img18](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img18.PNG)

- chowm

    ![img16](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img16.PNG)

    ![img17](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img17.PNG)

<h1 id="6">06_find和grep命令</h1>

![img19](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img19.PNG)

![img20](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img20.PNG)

<h1 id="7">07_压缩和解压缩命令</h1>

- 比較沒在使用的 `gzip` & `bzip2`

    ![img21](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img21.PNG)

- 常用的 `tar`

    ```Shell
    -c(create)：表示創建用來生成檔包 。
    -x：表示提取，從檔包中提取檔。
    -t：可以查看壓縮的檔。
    -z：使用gzip方式進行處理，它與”c“結合就表示壓縮，與”x“結合就表示解壓縮。
    -j：使用bzip2方式進行處理，它與”c“結合就表示壓縮，與”x“結合就表示解壓縮。 
    -v(verbose)：詳細報告tar處理的資訊。
    -f(file)：表示檔，後面接著一個檔案名。 -C <指定目錄> 解壓到指定目錄。
    ```

- 用 `tar` 壓縮(解壓)文件(目錄)

    ![img22](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img22.PNG)

    ![img23](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img23.PNG)

    ![img24](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img24.PNG)

<h1 id="8">08_网络命令</h1>

- `ifconfig`

    ![img25](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img25.PNG)

- `route`

    ![img25_1](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img25_1.PNG)

    ![img25_2](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img25_2.PNG)

<h1 id="9">09_VI编辑器_新建_保存_浏览</h1>

![img26](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img26.PNG)

![img27](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img27.PNG)

- nG或ngg：光标移动到第 n行首。

- 屏幕翻滚
  - Ctrl + f	屏幕向下翻一页，相当于下一页。
  - Ctrl + b	屏幕向上翻一页，相当于上一页。


<h1 id="10">10_VI编辑器_编辑</h1>

![img28](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img28.PNG)

<h1 id="11">11_VI编辑器_复制粘贴查找替换</h1>

![img29](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img29.PNG)

![img30](./[第2篇]_安裝虛擬機_Ubuntu基本操作/img30.PNG)
