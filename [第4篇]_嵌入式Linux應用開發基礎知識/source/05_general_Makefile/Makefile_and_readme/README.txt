本程序的Makefile分為3類:
1. 頂層目錄的Makefile
2. 頂層目錄的Makefile.build
3. 各級子目錄的Makefile

一、各級子目錄的Makefile：
   它最簡單，形式如下：

EXTRA_CFLAGS  := 
CFLAGS_file.o := 

obj-y += file.o
obj-y += subdir/
   
   "obj-y += file.o"  表示把當前目錄下的file.c編進程序裡，
   "obj-y += subdir/" 表示要進入subdir這個子目錄下去尋找文件來編進程序裡，是哪些文件由subdir目錄下的Makefile決定。
   "EXTRA_CFLAGS",    它給當前目錄下的所有文件(不含其下的子目錄)設置額外的編譯選項, 可以不設置
   "CFLAGS_xxx.o",    它給當前目錄下的xxx.c設置它自己的編譯選項, 可以不設置

注意: 
1. "subdir/"中的斜杠"/"不可省略
2. 頂層Makefile中的CFLAGS在編譯任意一個.c文件時都會使用
3. CFLAGS  EXTRA_CFLAGS  CFLAGS_xxx.o 三者組成xxx.c的編譯選項

二、頂層目錄的Makefile：
   它除了定義obj-y來指定根目錄下要編進程序去的文件、子目錄外，
   主要是定義工具鏈前綴CROSS_COMPILE,
   定義編譯參數CFLAGS,
   定義鏈接參數LDFLAGS,
   這些參數就是文件中用export導出的各變量。

三、頂層目錄的Makefile.build：
   這是最複雜的部分，它的功能就是把某個目錄及它的所有子目錄中、需要編進程序去的文件都編譯出來，打包為built-in.o
   詳細的講解請看視頻。

四、怎麼使用這套Makefile：
1．把頂層Makefile, Makefile.build放入程序的頂層目錄
   在各自子目錄創建一個空白的Makefile

2．確定編譯哪些源文件
   修改頂層目錄和各自子目錄Makefile的obj-y : 
    obj-y += xxx.o
	obj-y += yyy/
	這表示要編譯當前目錄下的xxx.c, 要編譯當前目錄下的yyy子目錄	

3. 確定編譯選項、鏈接選項
   修改頂層目錄Makefile的CFLAGS，這是編譯所有.c文件時都要用的編譯選項;
   修改頂層目錄Makefile的LDFLAGS，這是鏈接最後的應用程序時的鏈接選項;
   
   修改各自子目錄下的Makefile：
   "EXTRA_CFLAGS",    它給當前目錄下的所有文件(不含其下的子目錄)設置額外的編譯選項, 可以不設置
   "CFLAGS_xxx.o",    它給當前目錄下的xxx.c設置它自己的編譯選項, 可以不設置
   
4. 使用哪個編譯器？
   修改頂層目錄Makefile的CROSS_COMPILE, 用來指定工具鏈的前綴(比如arm-linux-)
   
5. 確定應用程序的名字：
   修改頂層目錄Makefile的TARGET, 這是用來指定編譯出來的程序的名字

6. 執行"make"來編譯，執行"make clean"來清除，執行"make distclean"來徹底清除