/******************************************************************************
   metmenu.h	- MET Series Menu Function Header

   Copyright (C) 2007 Nippon Systems Development Co.,Ltd. All Rights Reserved
   
   êVãK


******************************************************************************/
#ifndef	_METMENU_H_
#define	_METMENU_H_

typedef struct {
	char str[24];
	unsigned int (* func)(void);
} MENUINFO;

void menudisp(unsigned int line, unsigned int colum, unsigned int cur,unsigned int cnt, MENUINFO *menu);
unsigned int menukey(unsigned int *offset,unsigned int *cur,unsigned int maxline,unsigned int menusize);
//void menuctrl(char *title,MENUINFO *menu,unsigned int size,unsigned int cur);
void menuctrl(char *title,MENUINFO *menu,unsigned int size,unsigned int cur,char *exit);

#endif

