obj-m += kernel_rd_test.o

KERNEL_BUILD=../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_FL_EVT/cec_bosch_cv2x_sdk_3.0/cv2x_linux_sdk_3.0/ambarella/out/s6lm_bosch_home_outdoor/kernel/linux-5.4_kernel

ARCH = arm64
# Replace this path with your Ambarella toolchain installation
#CROSS_COMPILE = /usr/local/linaro-aarch64-2018.08-gcc8.2/bin/aarch64-linux-gnu-
CROSS_COMPILE=/usr/local/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/aarch64-linux-gnu-

PWD := $(CURDIR)

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) -C $(KERNEL_BUILD) modules

clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) -C $(KERNEL_BUILD) clean
