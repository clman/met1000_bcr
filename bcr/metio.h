/******************************************************************************
   metio.h	- MET Series input/output Function Header

   Copyright (C) 2005 Nippon Systems Development Co.,Ltd. All Rights Reserved
   
   $Log: metio.h,v $
   Revision 1.1.1.1  2005/07/01 05:39:17  f
   新規


******************************************************************************/
#ifndef	_METIO_H_
#define	_METIO_H_

/* 画面表示メッセージ情報 構造体*/
typedef struct {
	unsigned short line;				/* 表示開始ライン位置 		*/
	unsigned short colum;				/* 表示開始カラム位置 		*/
	char str[21];						/* 表示文字列         		*/
} MSGINFO;

typedef struct {
	unsigned short line;				/* 表示開始ライン位置		*/
	unsigned short colum;				/* 表示開始カラム位置		*/
	int attr;							/* 文字列修飾属性			*/
	char str[21];						/* 表示文字列				*/
} MSGATTRINFO;


#define dispch(c)		put_character((unsigned short)(c))
#define BUZZER_ERR()	buzzer(500,30)
#define buzzer_err()	BUZZER_ERR()

#define BUZZER_CLICK()	buzzer(4200,5)


void dispchar(unsigned short line, unsigned short colum, int size, int attr, unsigned short c);
void dispstr(unsigned short line, unsigned short colum, char *str);
void dispstrr(unsigned short line, unsigned short colum , char *str);
void dispnstr(unsigned short line, unsigned short colum, char *str, unsigned short cnt);
void dispstrattr(unsigned short line, unsigned short colum, int attr, char *str);
void dispmsgline(MSGINFO *msg,int attr);
void dispmsg(MSGINFO *msg, unsigned int size);
void dispmsgattr(MSGATTRINFO *msg, unsigned int size);
unsigned char anykey(void);
unsigned char keywait(char *s);
unsigned char keywaitbz(char *s,int buzz);
unsigned int menu(MSGINFO *msg, unsigned int size);
void blockcursor(int blink);
void linecursor(int blink);
void cursoroff(void);
unsigned char keygetchar(unsigned short line, unsigned short colum);
unsigned char inputline(unsigned short line, unsigned short colum,char *buff, unsigned short len, unsigned short displen, char *exitchar);
#endif