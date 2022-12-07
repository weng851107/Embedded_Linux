CC=/usr/local/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/aarch64-linux-gnu-gcc
INSTALL_PATH :=/mnt/disk2/SF/maintest

LD_FLAGS := -lm -liniparser -lsystemd -llzma -pthread -ljson-c -lcecbh
LD_FLAGS += -lamdev -lamp -limg_algo_v5_dyn -limg_dsp_v5_dyn -limg_aaa_flow_v5
LD_FLAGS += -llua
C_FLAGS := -g
C_INC := -I./include                                    \
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/iniparser/include	\
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/systemd/include   \
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/json-c/include 	\
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/include 									\
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/include/arch_v5 							\
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/app/chicony/mw/bosch_pro/src/include           \
	-I../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/packages/img_mw/mw/arch_v5/include

LD_PATH := -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/iniparser/usr/lib
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/systemd/usr/lib
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/xz/usr/lib
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/json-c/usr/lib
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/out/s6lm_bosch_home_outdoor/packages/img_mw/mw/arch_v5/src
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/out/s6lm_bosch_home_outdoor/packages/img_mw/dev/arch_v5
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/imgproc/img_lib/arch_v5
LD_PATH += -L../Bosch_Home_Gen2/bosch_smt_sdk3.0.1_Verification/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/lua/usr/lib
LD_PATH += -L.

MAIN_OBJS := $(INSTALL_PATH)/cecmain.o
TARGET := $(INSTALL_PATH)/cecmain

all:$(MAIN_OBJS)
	$(CC) $(C_INC) -Wall $(C_FLAGS) $(MAIN_OBJS) -o $(TARGET) $(LD_PATH) $(LD_FLAGS)

$(MAIN_OBJS):%.o:%.c
	$(CC) $(C_INC) $(LD_PATH) $(C_FLAGS) -c -Wall -o $@ $< $(LD_FLAGS)

.PHONY:clean
clean:
	-rm $(TARGET)
