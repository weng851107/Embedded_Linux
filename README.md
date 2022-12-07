```Text
Author: Antony_Weng <weng851107@gmail.com>

This file is only used for the record of the learning process, only used by myself and the file has never been leaked out.
If there is related infringement or violation of related regulations, please contact me and the related files will be deleted immediately. Thank you!
```

# 目錄

- [Note](#0)
- [相關知識](#1)
  - [單片機 & 嵌入式系統](#1.1)
  - [嵌入式系統之作業系統](#1.2)
  - [簡介裸機與RTOS開發模式](#1.3)
    - [裸機開發模式](#1.3.1)
    - [RTOS的引入](#1.3.2)
  - [單片機常用調試的接口：JTAG、SWD、RDI接口與Jlink、Ulink、STlink仿真器](#1.4)
  - [AMBA(Advanced Microcontroller Bus Architecture) 總線協議](#1.5)
  - [分時多工（Time-Division Multiplexing，TDM）](#1.6)
  - [Ethernet（以太網）之 詳解 MAC、MII、PHY](#1.7)
- [快速入門](#2)
- [驅動大全](#3)


<h1 id="0">Note</h1>

[嵌入式Linux教程_韋東山手把手教你嵌入式Linux快速入門到精通](https://www.bilibili.com/video/BV1w4411B7a4?spm_id_from=333.999.0.0&vd_source=790c8244dbe879457094c8374beb04d3)

[韋東山老師, 快速入門 git repository](https://e.coding.net/weidongshan/01_all_series_quickstart.git)

[Linux 内核源码（kernel source）路径](https://blog.csdn.net/lanchunhui/article/details/72866103)

- 内核源码所在的位置：/usr/src

[Linux驱动之用man查看内核函数](https://blog.csdn.net/lang523493505/article/details/104273604)

<h1 id="1">相關知識</h1>

<h2 id="1.1">單片機 & 嵌入式系統</h2>

[Reference](https://ppfocus.com/0/te3daf8fd.html)

### 單片機(Single Chip Microomputer), 微控制器(MicroController Unit)

- 在那個年代半導體工藝還在起步階段，集成能力很差，往往是CPU一個晶片，SRAM一個晶片，Flash一個晶片，需要中斷的話又得有個專門處理中斷的晶片，所以一個完整可用的計算機系統是很多個晶片(Chip)做在一個PCB板上構成的。

- 單片機就是在一個晶片(Chip)上集成了CPU、SRAM、Flash及其他需要模塊，在一個Chip上實現一個微型計算機系統，所以就叫Single Chip Microcomputer。

- 其實從這個角度來講，單片機這個詞現在已經沒意義了，因爲現在的半導體工藝早就很厲害了，現在你買到的所有都是「單片機」，根本不存在分離式的所謂「多片機」。

- 現代的單片機不但集成了CPU、SRAM、Flash等微型計算機不可少的部件，而且大多集成了很多內部外設，如Nand控制器、LCD控制器、串口通信、定時器、RTC等等，所以現在的單片機其實應該叫SoC(System on Chip)。

- 晶片中不帶MMU(memory management unit)從而不支持虛擬地址，只能跑裸機或RTOS(典型如ucos、華爲LiteOS、RT-Thread、freertos等)的system叫單片機(典型如STM32、NXP LPC系列、新的NXP imxRT1052系列等)

- 51單片機之所以出名並活到現在，是因爲Intel後來開放了51內核的版權，所以很多公司很多人可以毫無顧忌的使用它而不擔心付費或版權風險。

- ARM這些年風頭很強，在application級別的SoC中大勝Intel，現在手機行業的晶片都被ARM吃掉了，MIPS之類的更是被壓的生不如死。在單片機領域，ARM的Cortex-M系列(M0、M3、M4、M7)也是大獲全勝，很多半導體廠商都放棄了自己原來的架構轉而做ARM內核的單片機了。

- 單片機不是裸機就是RTOS

```
computer - 指的就是電腦，你可以理解爲就是電腦，譬如筆記本、台式機這些。當然很多年前的電腦很龐大很笨重，
           所以computer就是指的這種有機箱外殼，有鍵盤滑鼠，很龐大笨重，通用性強的電腦。

microcomputer - 指的就是單片機這類東西，它也是一個獨立的電腦系統，有CPU和內存和外設這些，能跑電腦程式。
                但是他相對於computer來說體積很小，而且不是通用的而是專用的，所以叫microcomputer。

microcontroller - 現在很多單片機廠商都把自己的單片機叫microcontroller(微控制器)，microcontroller的重點在於controller，
                  也就是說他們想強調這個chip中集成的system是一個controller，擅長控制。而不是一個DSP(擅長運算)。

system - 更傾向於整個系統，也就是說system=microcomputer+各種外設。簡單理解就是，當串口、LCD控制器等模塊進入了Chip內部時，
         整個microcomputer就成爲system，其實system才是更有意義，更適合現代單片機晶片的一個名字。
         所以現在我們都把晶片叫SoC，這個名字更有價值。
```

### 嵌入式系統(Embedded system)

- 嵌入指的是我們把這個system(硬體上表現爲一個Chip)嵌入到某個設備中去。譬如冰箱的板卡上的晶片就是一個嵌入到冰箱中的system，負責控制用戶按鍵、冰箱照明燈、製冷系統等。可以看出，嵌入式系統這個名字主要是從晶片在使用時的組織形態來命名的。所以從這個角度講，只要是被嵌入到設備中的晶片都可以被叫做嵌入式系統。

- 狹義上講，嵌入式是爲了區別於單片機。我們經常把晶片中不帶MMU(memory management unit)從而不支持虛擬地址，只能跑裸機或RTOS(典型如ucos、華爲LiteOS、RT-Thread、freertos等)的system叫單片機(典型如STM32、NXP LPC系列、新的NXP imxRT1052系列等)

- 晶片自帶MMU可以支持虛擬地址，能夠跑Linux、Vxworks、WinCE、Android這樣的作業系統的system叫嵌入式。

- 嵌入式領域目前最火的就是ARM+linux和ARM+android。晶片都是基於ARM的，低端的有ARM9、ARM11，高端的有Cortex-A7、Cortex-A8、Cortex-A9、Cortex-A53、Cortex-A57等。從單核心到雙核心、四核心、八核心都有。

- 嵌入式級別的ARM因爲有MMU所以可以很好的跑複雜OS，因此雖然晶片本身也可以裸機運行，但是基本沒有人用這類晶片來跑裸機或者RTOS的。都會上作業系統。
  - 產品不需要華麗美觀的人機界面就上linux(譬如路由器、網絡攝像機)
  - 需要人機界面但是界面簡單注重功能和穩定性，那就上linux+QT(譬如工控HMI、電動車充電樁、停車場顯示)
  - 產品很注重人機互動的用戶體驗，那就上Android(譬如智慧型手機、智能電視機、遊戲機等)

<h2 id="1.2">嵌入式系統之作業系統</h2>

嵌入式系統分為軟件和硬件兩部分：

- 硬件：主要包括核心處理器芯片、內存和存儲芯片等外圍芯片；
- 軟件：主要包括有嵌入式系統運行的引導程序如uboot、操作系統（如linux）、底層設備驅動及應用軟件等。

ARM（Advanced RISC Machines）架構：

- 指精簡指令集計算機設備
- 使用ARM 技術生產的各種型號芯片稱為ARM 處理器
- ARM公司使用RISC技術設計芯片，給其他公司授權芯片IP core
  - Cortex-A：針對高端領域的處理器，在移動互聯設備、數字電視等領域使用廣泛。
  - Cortex-R：在實時性方面有巨大優勢，應用領域例如智能汽車、消費電子等。
  - Cortex-M：主要優勢為低成本和低功耗，主要應用於微控制領域，如工業控制和家用電器等

作業系統有兩種：

- 用MMU： Windows, MacOS, Linux, Android  --> 非實時作業系統
- 不用MMU： FreeRTOS, VxWorks, ucOS       --> 實時作業系統

CPU有分帶MMU的和不帶MMU的：

- 帶MMU的有Cortex-A系列ARM9 ARM11系列
- 不帶MMU的有Cortex-M系列…

非實時作業系統的運行單位是進程, 實時作業系統的運行單位是線程，而要實現進程晶片必須要有MMU(存儲管理單元)

STM32是M系列，不可能運行Linux，但可以跑實時操作系統，如ucos、 FreeRTOS、 RT-Thread

<h2 id="1.3">簡介裸機與RTOS開發模式</h2>

<h3 id="1.3.1">裸機開發模式</h3>

- 裸機開發，指的就是沒有操作系統，就是單片機開發。

- 程序的運行，完全取决於代碼的邏輯設計，硬件設備的固定設定。

- 總結來說，裸機程序難以解决的問題就是，控制每個任務的運行時間。難以消除任務與任務之間的相互影響。

**輪詢方式**

```C
void main()
{
    
   while(1){
      eat();         //喂孩子吃飯函數
      message();     //回複同事消息
   }
}
```

**事件驅動方式**

- 事件是一個寬泛的概念，什麼是事件？可以是：按下了按鍵、串口接收到了數據、模塊產生了中斷、某個全局變量被設置了。

- 當某個事件發生時，才調用對應函數，這就叫事件驅動。

```C
void crying_isr(){
   //檢測孩子是否在哭的中斷函數
   eating();//哭了就執行喂孩子吃飯的函數
}
void message_isr(){
   //檢測同事是否發消息函數.
   message();//執行回消息函數
}
void main(){
    
   while(1){
      
   }
}
```

**改進的事件驅動方式**

- 當兩個中斷同時產生的時候，同一時間只能處理一個，如果一個中斷處理時間比較長，就會影響另一個中斷的處理。

- 通過設置標志比特來改進程序

   ```C
   void crying_isr(){

      is_crying=1;         //如果哭了就將標志比特置1
   }
   void message_isr(){

      is_message=1;        //將有消息標志比特置1。
   }
   void main(){

      while(1){
         if(is_crying==1)
            eating();
         if(is_message==1)
            message();
      }
   }
   ```

**常用時間驅動方式：定時器**

- 設置一個定時器，比如每1ms產生一次中斷

   ```
   對於函數A，可以設置它的執行周期，比如每1ms執行一次
   對於函數B，可以設置它的執行周期，比如每2ms執行一次
   對於函數C，可以設置它的執行周期，比如每3ms執行一次
   ```

    ```C
    typedef struct soft_timer{
        int remain;//錶示剩餘多少時間，就需要調用下面的函數
        int period;//錶示周期
        void (*function)(void);//處理函數
    }soft_timer,*p_soft_timer;

    static soft_timer timers[]={
        {1,1,A},
        {2,2,B},
        {3,3,C}
    };//符合題目要求

    void main()
    {  
        while(1){  }
    }
    void timer_isr()
    {
        int i;      
        //是每個timers數組成員的remain都减1.
        for(i=0;i<3;i++){   
            timers[i].remain--;
        }
        //當remain减到0，就錶示要調用對應結構體中的函數了
        for(i=0;i<3;i++){
            if(timers[i].remain==0){        
                timers[i].function();                     //調用函數
                timers[i].remain=timers[i].period;        //重置remain.
            }
        }
    }
    ```

**使用狀態機進行改進**

- 當任務處理函數執行時間都很長的時候，這裏我們可以使用狀態機的思想來解决這個問題，思路就是操作系統的時間片

    ```C
    void crying_isr(void)
    {
        static int state = 0;

        switch (state)
        {

            case 0: /* 開始 */
            {

                /* 盛飯 */
                state++;
                return;
            }

            case 1: /* 盛菜 */
            {

                /* 盛菜 */
                state++;
                return;
            }

            case 2: 
            {

                /* 拿勺子 */
                state++;
                return;
            } 
        }
    }

    void mesage_isr(void)
    {
        static int state = 0;

        switch (state)
        {

            case 0: /* 開始 */
            {

                /* 打開電腦 */
                state++;
                return;
            }

            case 1: 
            {

                /* 觀看信息 */
                state++;
                return;
            }

            case 2: 
            {

                /* 打字 */
                state++;
                return;
            }
        }
    }

    void main()
    { 
        while (1)
        {

            crying_isr();
            message_isr();
            //其實就是將這個執行時間很長的函數，拆分為短時間來處理。
        }
    }
    ```

<h3 id="1.3.2">RTOS的引入</h3>

- 假設要調用兩個函數AB，AB執行的時間都很長，使用裸機程序時可以把AB函數改造為"**狀態機**"，還可以使用**RTOS**。這兩種方法的核心都是"**分時複用**"：
  - 分時：函數A運行一小段時間，函數B再運行一小段時間
  - 複用：複用誰？就是CPU

- 寶媽一會兒喂孩子飯，一會兒回消息。當這個時間足够短的時候，從宏觀上來看就是兩個事件同時發生；從微觀上來看，這依舊是兩件事情。

- 關鍵在於RTOS讓多個任務輪流運行，不再需要我們手工在任務函數去使用狀態機拆分程序。

    ```C
    // RTOS程序 
    喂飯()
    {
        while (1)
        {
        
            喂一口飯();
        }
    }

    回信息()
    {
        while (1)
        {
        
            回一個信息();
        }
    }

    void main()
    {
        
        create_task(喂飯);//創建一個任務
        create_task(回信息);//創建一個任務
        start_scheduler();//執行任務列錶
        while (1)
        {

            sleep();
        }
    }
    ```

<h2 id="1.4">單片機常用調試的接口：JTAG、SWD、RDI接口與Jlink、Ulink、STlink仿真器</h2>

### JTAG協議

- JTAG（Joint Test Action Group，聯合測試行動小組）是一種國際標準測試協議（IEEE 1149.1兼容），主要用於晶片內部測試。現在多數的高級器件都支持JTAG協議，如ARM、DSP、FPGA器件等。

- 標準的JTAG接口是4線：TMS、 TCK、TDI、TDO，分別為模式選擇、時鐘、數據輸入和數據輸出線。
  - TMS：測試模式選擇，TMS用來設置JTAG接口處於某種特定的測試模式；
  - TCK：測試時鐘輸入；
  - TDI：測試數據輸入，數據通過TDI引腳輸入JTAG接口；
  - TDO：測試數據輸出，數據通過TDO引 腳從JTAG接口輸出；

- 目前市場上已經很少看到它的身影了。取而代之的是越來越多的USB接口。

### SWD接口

- 串行調試（Serial Wire Debug），應該可以算是一種和JTAG不同的調試模式，使用的調試協議也應該不一樣，所以最直接的體現在調試接口上，與JTAG的20個引腳相比，SWD只需要4個（或者5個）引腳，結構簡單，但是使用範圍沒有JTAG廣泛，主流調試器上也是後來才加的SWD調試模式。

    ![MCU_img00](./image/MCU/MCU_img00.PNG)

- 板子的體積有限的時候推薦使用SWD模式，它需要的引腳少

### RDI接口

- 遠程調試接口（Remote Debug Interface），是ARM公司提出的標準調試接口，主要用於ARM晶片的仿真，由於各個IDE廠商使用的調試接口各自獨立，硬體無法進行跨平台的調試。

### JLink仿真器

- 基於JTAG的仿真器

- 給一個JTAG協議轉換盒，即一個小型USB到JTAG的轉換盒，其連接到計算機用的是USB接口，而到目標板內部用的還是jtag協議。它完成了一個從軟體到硬體轉換的工作。

### ULink仿真器

- ULINK是ARM/KEIL公司推出的仿真器

- ULINK/ULINK2可以配合Keil軟體實現仿真功能，並且僅可以在Keil軟體上使用，增加了串行調試（SWD）支持，返回時鐘支持和實時代理等功能。

### ST-Link仿真器

- 專門針對意法半導體STM8和STM32系列晶片的仿真器。

- 採用5V的USB2.0全速接口進行供電與數據傳輸，可以方便的對內部固件進行升級，同時支持以 **JTAG** 或 **SWD** 模式連接至 STM32 系列微控制器，或者以 **SWIM** 模式連接至 STM8 系列微控制器

<h2 id="1.5">AMBA(Advanced Microcontroller Bus Architecture) 總線協議</h2>

- AMBA (Advanced Microcontroller Bus Architecture) 高級處理器總線架構
  - AHB (Advanced High-performance Bus) 高級高性能總線
  - ASB (Advanced System Bus) 高級系統總線
  - APB (Advanced Peripheral Bus) 高級外圍總線
  - AXI (Advanced eXtensible Interface) 高級可拓展接口

   ![AMBA_img00](./image/AMBA/AMBA_img00.PNG)

<h2 id="1.6">分時多工（Time-Division Multiplexing，TDM）</h2>

- 分時多工（Time-Division Multiplexing，TDM）是一種數位或者類比（較罕見）的多工技術。

- 使用這種技術，兩個以上的訊號或資料流可以同時在一條通訊線路上傳輸，其表現為同一通訊頻道的子頻道。但在物理上來看，訊號還是輪流占用物理通道的。時間域被分成周期迴圈的一些小段，每段時間長度是固定的，每個時段用來傳輸一個子頻道。

<h2 id="1.7">Ethernet（以太網）之 詳解 MAC、MII、PHY</h2>

[Reference](https://www.twblogs.net/a/5b7a98562b7177392c9666f8)

- 從硬件的角度看，以太網接口電路主要由**MAC（Media Access Control）控制器**和**物理層接口PHY（Physical Layer，PHY）兩大部分構成**。PHY整合了大量模擬硬件，而MAC是典型的全數字器件。

    ![ethernet_img00](./image/Ethernet/ethernet_img00.PNG)

  - CPU集成MAC與PHY。目前來說並不多見

    ![ethernet_img01](./image/Ethernet/ethernet_img01.PNG)

  - CPU集成MAC，PHY採用獨立芯片。比較常見

    ![ethernet_img02](./image/Ethernet/ethernet_img02.PNG)

  - CPU不集成MAC與PHY，MAC與PHY採用集成芯片。比較常見

    ![ethernet_img03](./image/Ethernet/ethernet_img03.PNG)

  - MAC及PHY工作在OSI七層模型的數據鏈路層和物理層。具體如下

    ![ethernet_img04](./image/Ethernet/ethernet_img04.PNG)

- **MAC（Media Access Control）**即**媒體訪問控制子層協議**。該部分有兩個概念：MAC可以是一個硬件控制器 及 MAC通信以協議。該協議位於OSI七層協議中數據鏈路層的下半部分，主要負責控制與連接物理層的物理介質。

    ![ethernet_img05](./image/Ethernet/ethernet_img05.PNG)

- **MII（Media Independent Interface）**即**媒體獨立接口**，MII接口是MAC與PHY連接的標準接口。
  - GMII(Gigabit MII)
  - RMII(Reduced Media Independant Interface)

    ![ethernet_img06](./image/Ethernet/ethernet_img06.PNG)

- **PHY（Physical Layer，PHY）**是**IEEE802.3中定義的一個標準模塊**，STA（station management entity，管理實體，一般爲MAC或CPU）通過SMI（Serial Manage Interface）對PHY的行爲、狀態進行管理和控制，而具體管理和控制動作是通過讀寫PHY內部的寄存器實現的。

    ![ethernet_img07](./image/Ethernet/ethernet_img07.PNG)

<h1 id="2">快速入門</h1>

[[第1篇]_新學習路線_視頻介紹_資料下載.md](./[第1篇]_新學習路線_視頻介紹_資料下載.md)

[[第2篇]_安裝虛擬機_Ubuntu基本操作.md](./[第2篇]_安裝虛擬機_Ubuntu基本操作.md)

[[第3篇]_環境搭建與開發板操作(STM32MP157_Pro).md](./[第3篇]_環境搭建與開發板操作(STM32MP157_Pro).md)

*[[第4篇]_嵌入式Linux應用開發基礎知識.md](./[第4篇]_嵌入式Linux應用開發基礎知識.md)

*[[第5篇]_嵌入式Linux驅動開發基礎知識.md](./[第5篇]_嵌入式Linux驅動開發基礎知識.md)

[[第6篇]_項目實戰.md](./[第6篇]_項目實戰.md)

<h1 id="3">驅動大全</h1>

[[第7篇]_驅動大全.md](./[第7篇]_驅動大全.md)

