CC=/usr/local/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/aarch64-linux-gnu-g++
INSTALL_PATH :=/mnt/disk2/SF/cvTest

LD_FLAGS := -lopencv_highgui -lopencv_core -lopencv_imgproc -ltbb -lz -lopencv_imgcodecs -ljpeg -lpng16 -lopencv_videoio
C_FLAGS := -g
C_INC := -I./opencv/include     \
	-I./opencv/include/opencv    \
	-I./opencv/include/opencv2

LD_PATH := -L./opencv/usr/lib
LD_PATH += -L../Bosch_Home_Pro/cec_bosch_cv2x_sdk_3.0/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/tbb/usr/lib
LD_PATH += -L../Bosch_Home_Pro/cec_bosch_cv2x_sdk_3.0/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/zlib/usr/lib
LD_PATH += -L../Bosch_Home_Pro/cec_bosch_cv2x_sdk_3.0/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/libjpeg-turbo/usr/lib
LD_PATH += -L../Bosch_Home_Pro/cec_bosch_cv2x_sdk_3.0/cv2x_linux_sdk_3.0/ambarella/prebuild/oss/armv8-a/libpng/usr/lib

all:
	$(CC) $(C_INC) $(LD_PATH) $(LD_FLAGS) -o cvmain cvmain.cpp

.PHONY:clean
clean:
	-rm cvmain
