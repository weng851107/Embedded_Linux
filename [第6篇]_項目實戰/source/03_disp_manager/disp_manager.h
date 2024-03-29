#ifndef _DISP_MANAGER_H
#define _DISP_MANAGER_H

typedef struct DispBuff {
	int iXres;
	int iYres;
	int iBpp;
	char *buff;
}DispBuff, *PDispBuff;


typedef struct Region {
	int iLeftUpX;
	int iLeftUpY;
	int iWidth;
	int iHeigh;
}Region, *PRegion;

typedef struct DispOpr {
	char *name;
	int DeviceInit(void);
	int DeviceExit(void);
	int GetBuffer(PDispBuff ptDispBuff);
	int FlushRegion(PRegion ptRegion, PDispBuff ptDispBuff);
	struct DispOpr *ptNext;
}DispOpr, *PDispOpr;

void RegisterDisplay(PDispOpr ptDispOpr);

void DisplayInit(void);
int SelectDefaultDisplay(char *name);
int InitDefaultDisplay(void);
int PutPixel(int x, int y, unsigned int dwColor);
int FlushDisplayRegion(PRegion ptRegion, PDispBuff ptDispBuff);


#endif




