AMB_SDK_PATH=../../bosch_smt_sdk3.0.1/cec_bosch_cv2x_sdk_3.0/cv2x_linux_sdk_3.0/ambarella/
CROSS_COMPILE=/usr/local/linaro-aarch64-2020.09-gcc10.2-linux5.4/bin/aarch64-linux-gnu
CC=${CROSS_COMPILE}-gcc
LD=${CROSS_COMPILE}-ld
STRIP=${CROSS_COMPILE}-strip

#choose cec_radar_tester.c or testtty.c
SRCS := cec_hal_radar_ts24gtr12s.c 	\
		cec_radar.c					\
		cec_internal_uart_cfg.c		\
		cec_radar_tester.c          
		

CFLAGS  := -Wall -I. -DBOSCH_HOME_OUTDOOR -DBOSCH_HOME_OUTDOOR_RADAR_VALID_OBJECTS=2
LDFLAGS := -lpthread


PROG := cec_radar_tester_test #testtty_radar0 #testtty_radar1 #cec_radar_tester

all:
	$(CC) $(CFLAGS) -o $(PROG)   $(SRCS) $(LDFLAGS)

.PHONE: clean

clean:
	-rm $(PROG)