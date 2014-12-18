/******************************************************************************
   metio.c	- MET Series input/output Function

   Copyright (C) 2005 Nippon Systems Development Co.,Ltd. All Rights Reserved
   
   $Log: metio.c,v $
   Revision 1.2  2005/07/01 06:48:59  f
   inputline [S1]キー 不具合修正

   Revision 1.1.1.1  2005/07/01 05:39:17  f
   新規


******************************************************************************/
/*
本プログラム使用に関する規約
   
   ・本プログラムは、カスタマイズが行える様ソースプログラムとして提供します。
   　本プログラムをライブラリ化しての使用は行わないでください。
   ・関数を変更して使用する場合は、変更したい関数抜き出し別ファイルで変更するか、
     または、上記のファイルヘッダに変更内容を記載してください。（この場合は、
     個人での管理お願いします。）
   ・本プログラムを使用する際は、開発したアプリケーションにおいて必ず動作の
   　検証十分を行ってください。
   　（本プログラムを使用してのアプリケーション不具合は一切責任はもてません。
   　　自己責任で使用してください。）

   ・上記項目に承諾できない場合は、使用しないでください。
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <met1000.h>

#include "metio.h"
/*
#define dispch(c)		put_character((unsigned short)(c))
#define BUZZER_ERR()	buzzer(500,30)
#define buzzer_err()	BUZZER_ERR()
*/

/**************************************************************************************************
	dispchar
要約：
   	文字表示
	void dispchar(unsigned short line, unsigned short colum, int size, int attr, unsigned short c)
   		line	表示開始ライン位置
   		colum	表示開始カラム位置
		size	表示文字サイズ（ANK,1/4）
   		deco	文字修飾（通常,反転）
   		c		表示文字
解説：
   指定したline,columの位置に、sizeの大きさのでdecoの修飾でcを表示する
戻り値：
   	なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispchar(unsigned short line, unsigned short colum, int size, int attr, unsigned short c)
{
	int sizestat;
	int attrstat;
	
	sizestat=charsize_state();
	attrstat=chardeco_state();
	
	charsize(size);
	chardeco(attr);

	gotoxy(colum,line);
	dispch(c);

	charsize(sizestat);
	chardeco(attrstat);
}

/**************************************************************************************************
   dispstr
要約：
   	文字表示
	void dispstr(unsigned short line, unsigned short colum, char *str)
   		line	表示開始ライン位置
   		colum	表示開始カラム位置
   		str		表示文字列
解説：
   	指定したline，columの位置に文字列strを表示する。
戻り値：
   	なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispstr(unsigned short line, unsigned short colum, char *str)
{
	gotoxy(colum,line);
	put_string(str);
}
/**************************************************************************************************
	dispstrr
要約：
   反転文字列表示
	void dispstrr(unsigned short line, unsigned short colum , char *str)
   		line	表示開始ライン位置
   		colum	表示開始カラム位置
   		str		表示文字列
解説:
   	指定したline，columの位置に文字列strを反転表示する。
戻り値：
   	なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispstrr(unsigned short line, unsigned short colum , char *str)
{
	int stat;

	stat=chardeco_state();
	chardeco(REVERSE);
	gotoxy(colum,line);
	put_string(str);
	chardeco(stat);
}

/**************************************************************************************************
	dispnstr
 要約：
   	表示文字数指定の文字列表示
	void dispnstr(unsigned short line, unsigned short colun, char *str, unsigned short cnt)
  		line	表示開始ライン位置
   		colum	表示開始カラム位置
   		str		表示文字列
   		cnt		表示文字数
 解説：
   	指定したline，columの位置に文字列steをcnt分表示する
戻り値：
   	なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispnstr(unsigned short line, unsigned short colum, char *str, unsigned short cnt)
{
	unsigned short i;
	
	gotoxy(colum,line);
	for (i=0;i<cnt;i++,str++){
		if (!(*str))
			break;
		dispch(*str);
	}
}

/**************************************************************************************************
	dispstrattr
要約：
   	修飾指定文字列表示
	void dispstrattr(unsigned short line, unsigned short colum, int attr, char *str)
解説：
   指定したline,columの位置にattrで指定した修飾で文字列strを表示する。
戻り値：
   	なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispstrattr(unsigned short line, unsigned short colum, int attr, char *str)
{
	int stat;

	stat=chardeco_state();
	chardeco(attr);
	gotoxy(colum,line);
	put_string(str);
	chardeco(stat);		
}


/**************************************************************************************************
	dispmsgline
要約：
   	メッセージ表示（1行表示）
   	void dispmsgline(MSGINFO *msg,int attr)
		msg		画面表示情報構造体
   		attr	表示属性（通常表示,反転表示）
解説：
   	msg で指定した画面情報を、attrで指定した表示属性で表示する。
   	（1行分のみ）
   	
   msg 構造体
   メンバー					内容						12dot	16dot
   --------------------------------------------------------------------
	unsigned short line;	表示開始ライン位置 			1～10	1～8
	unsigned short colum;	表示開始カラム位置 			1～20	1～14
	char str[21];			表示文字列         		

 	arrt に NORMAL を指定すると、通常文字でmsgを表示
   	attr に REVERSEを指定すると、反転文字で msgを表示
戻り値：
   		なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispmsgline(MSGINFO *msg,int attr)
{
	dispstrattr(msg->line,msg->colum,attr,msg->str);
}



/**************************************************************************************************
  	dispmsg
要約：
	画面表示
   	void dispmsg(MSGINFO *msg, int size)
   		msg		画面表示の為の構造体
   		size 	メッセージ表示サイズ
解説：
   	msgで指定した情報に従い画面表示を行う

	MSGINFO構造体は、以下のメンバーから構成される
   
   メンバー					内容						12dot	16dot
   --------------------------------------------------------------------
	unsigned short line;	表示開始ライン位置 			1～10	1～8
	unsigned short colum;	表示開始カラム位置 			1～20	1～14
	char str[21];			表示文字列         		


戻り値：
   なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispmsg(MSGINFO *msg, unsigned int size)
{
	clear_screen();
	while (size--){
		dispstr(msg->line,msg->colum,msg->str);
		msg++;
	}
}

/**************************************************************************************************
  	dispmsgattr
要約：
	画面表示
   	void dispmsgattr(MSGATTRINFO *msg, unsigned int size)
   		msg		画面表示の為の構造体
   		size 	メッセージ表示サイズ
解説：
   	msgで指定した情報に従い画面表示を行う

	MSGATTRINFO構造体は、以下のメンバーから構成される
   
   メンバー					内容						12dot	16dot
   --------------------------------------------------------------------
	unsigned short line;	表示開始ライン位置 			1～10	1～8
	unsigned short colum;	表示開始カラム位置 			1～20	1～14
    int attr;				文字列修飾属性
   	char str[21];			表示文字列         		


戻り値：
   なし
注意：
    予めパラメータに設定する値は、エラーにならない値を設定すること
**************************************************************************************************/
void dispmsgattr(MSGATTRINFO *msg, unsigned int size)
{
	clear_screen();
	while (size--){
		dispstrattr(msg->line,msg->colum,msg->attr,msg->str);
		msg++;
	}
}

/**************************************************************************************************
 	anykey
要約：
   	任意のキー待ち
	unsigned char anykey(void)
解説：
   	任意のキーを待つ
戻り値：
   	押されたキーキャラクタを返す。
注意：
   	本関数では、キーバッファをクリアしてから任意のキー待ち
   	を行う。キーバッファ内のデータを使用する場合は、使用しないこと
**************************************************************************************************/
unsigned char anykey(void)
{
	keyclear();
	return keycharwait();
}
/**************************************************************************************************
	keywait
要約：
   	指定キー押下待ち
	unsigned char keywait(char *s)
   		s		キー待ちの文字列 (終端は\0)
解説：
   	sにキー待ちを行うキーキャラクタを格納し、本関数を呼び出すことで
    s指定したキーが押されると本関数から戻る。
戻り値：
   押下されたキーキャラクタ
**************************************************************************************************/
unsigned char keywait(char *s)
{
	int i = TRUE;
	unsigned char c;
	keyclear();
	while (i){
		c = keycharwait();
		if (0 != strchr(s,(int)c)){
			i = FALSE;
		}
		else {
			BUZZER_ERR();
		}

	}
	return c;
}
/**************************************************************************************************
	keywaitbz
要約：
   	指定キー押下待ち
	unsigned char keywaitbz(char *s,int buzz)
   		s		キー待ちの文字列 (終端は\0)
   		buzz	キー待ち以外押下の時のブザーの有無（TRUE or FALSE）
解説：
   	sにキー待ちを行うキーキャラクタを格納し、本関数を呼び出すことで
    s指定したキーが押されると本関数から戻る。
    sに指定した以外のキーが押されたとき、ブザーを鳴らしたい場合
    buzzにTRUEを指定する。鳴らしたくない場合は、FALSEをしていする。
戻り値：
   押下されたキーキャラクタ
**************************************************************************************************/
unsigned char keywaitbz(char *s,int buzz)
{
	int i = TRUE;
	unsigned char c;
	keyclear();
	while (i){
		c = keycharwait();
		if (0 != strchr(s,(int)c)){
			i = FALSE;
		}
		else {
			if (buzz){
				BUZZER_ERR();
			}
		}
	}
	return c;
}

/**************************************************************************************************
	menu
要約：
   	メニュー選択
    unsigned short menu(MSGINFO *msg, unsigned short size)
		msg			メッセージ（メニュー）表示情報
   		size		メッセージ情報サイズ
解説：
   	msgで指定された表示情報に従いメニューを表示する。
    [1]～sizeで指定した値（キー）が入力可能
   	選択されたメニュー番号を反転表示し、[ENT]キーでメニューを
   	確定する。
戻り値：
    選択されたキーの数値（1～sizeで指定した値）

**************************************************************************************************/
unsigned int menu(MSGINFO *msg, unsigned int size)
{
	unsigned char key;								/* キーキャラクタ格納	*/
	unsigned int code;								/* コード格納			*/
	unsigned int num = 0;							/* メニュー番号格納		*/
	
	dispmsg(msg,size);
	do {
		dispmsgline(msg+num,REVERSE);
		key = keycharwait();
		if (isdigit((int)key)){
			code = key - '0';
			if (1 <= code && size >= code){
				dispmsgline(msg+num,NORMAL);
				num = code -1;
			}
		}
	} while (KEY_ENT != key);
	
	return (num+1);
}
/**************************************************************************************************
	blockcursor
要約：
   	ブロックカーソル表示
	void blockcursor(int blk)
   		blk		ブリンク表示指定
解説：
	blinkの指定に従いブロックカーソルを表示する。
戻り値：
   	なし
**************************************************************************************************/
void blockcursor(int blk)
{
	blink(blk);
	cursor(BLOCK);
}
/**************************************************************************************************
	linecursor
要約：
   	ラインカーソル表示
   void linecursor(int blk)
   		blk		ブリンク表示指定
解説：
	blinkの指定に従いブロックカーソルを表示する。
戻り値：
   	なし
**************************************************************************************************/
void linecursor(int blk)
{
	blink(blk);
	cursor(UNDERBAR);
}
/**************************************************************************************************
	void cursoroff(void)
要約：
   	カーソル非表示
   	void cursoroff(void)
解説：
	カーソルを非表示にする。
戻り値：
   	なし
**************************************************************************************************/
void cursoroff(void)
{
	cursor(OFF);
}

/**************************************************************************************************
	keygetcharinit
要約：
   keygetchar関数初期化処理
   void keygetcharinit(void)
解説：
   keygetchar関数を呼び出す前に、本関数を呼出しkeygetchar関数の初期化を行う
   指定したline,colum の位置でキー入力待ちを行う。
戻り値：
   なし
**************************************************************************************************/
static unsigned char PreKey;							/* シフトモード用 前回キー格納エリア	*/
void keygetcharinit(void)
{
	PreKey = 0;
}

/**************************************************************************************************
	keygetchar
要約：
   キー入力（文字列入力補助用関数）
   unsigned char keygetchar(unsigned short line, unsigned short colum)
   		line	入力キー表示ライン位置
   		colum	入力キー表示カラム位置
解説：
   	指定したline,colum の位置でキー入力待ちを行う。
戻り値：
	入力されたキーキャラクタ
注意：
	予めパラメータに設定する値は、エラーにならない値を設定すること
   	キー入力処理（文字列入力）等で使用するための補助的な関数なため単独では使用しないこと
   	本関数の使用方法は、inputline関数を参照す
**************************************************************************************************/
/* シフトモード キーテーブル	*/
static const char KeyNum[4][10] = {						/* [1]～[9]*/
	"ADGJMPSVY",
	"BEHKNQTWZ",
	"CFILORUX-",
	"123456789"
};
static const char KeyZero[9] = "$%+/:*\\0";				/*［0］*/
static const char KeyDot[3] = " .";						/* [.] */

static unsigned short KeyData = 0;
static unsigned long KeyPress = 0;
static int Repeat = FALSE;
unsigned char keygetchar(unsigned short line, unsigned short colum)
{
	unsigned char key;
	unsigned char c =0;
	unsigned short prec = 0;
	int loop = TRUE;
	int togglecnt = 0;
	int shiftstat;
	
	gotoxy(colum,line);
	if ('1' <= PreKey && '9' >= PreKey){
		c = KeyNum[togglecnt][PreKey - '1'];
		dispch(c);
		gotoxy(colum,line);
		prec = c;
		togglecnt++;
	}
	else if ('0' == PreKey){
		c = KeyZero[togglecnt];
		dispch(c);
		gotoxy(colum,line);
		prec = c;
		togglecnt++;
	}
	else if ('.' == PreKey){
		c = KeyDot[togglecnt];
		dispch(c);
		gotoxy(colum,line);
		prec = c;
		togglecnt++;
	}
	else if (0 != PreKey){
		c = PreKey;
		if (KEY_S1 == PreKey){
			PreKey = 0xFF;
		}
		else if (0xFF == PreKey){
			PreKey = 0;
			c = KEY_S1;
		}
		else {
			PreKey = 0;
		}
		loop = FALSE;
	}
	

	if (!kbhit()){
		if(0 !=  KeyPress){
			if (KeyPress == keypressing()){
				if (FALSE == Repeat){
					timer_start(0,50);
				}
				else {
					timer_start(0,5);
				}
				while (KeyPress == keypressing()){
					if (!timer_value(0)){
						BUZZER_CLICK();
						keywrite(KeyData);
						Repeat=TRUE;
						break;
					}
				}
			}
//			else {
//				KeyPress = 0;
//				Repeat=FALSE;
//			}
		}
	}
//	else {
//		KeyPress = 0;
//		Repeat=FALSE;
//	}
	shiftstat = shiftkey_state();
	while (loop){
		
		if (0 != prec && (ON == shiftstat && OFF == shiftkey_state())){
			PreKey = 0;
			loop = FALSE;
		}
		if (0 == keypressing()){
			KeyPress = 0;
			Repeat=FALSE;		
		}
		if (kbhit()){
//			key = keycharread();
			KeyPress = keypressing();
			KeyData = keyread();
			key = KeyData & 0x00FF;
			if (!(shiftstat = shiftkey_state())){
				if (('0' <= key && '9' >= key) || '.' == key){
					dispch(key);
				}
				c = key;
				PreKey = 0;
				loop = FALSE;
			}
			else {
				if (0 == prec || PreKey == key){
					if ('1' <= key && '9' >= key){
						c = KeyNum[togglecnt][key - '1'];
						dispch(c);
						gotoxy(colum,line);
						if (3>togglecnt){
							togglecnt++;
						}
						else {
							togglecnt = 0;
						}
						PreKey = key;
						prec = c;
					}
					else if ('0' == key){
						c = KeyZero[togglecnt];
						dispch(c);
						gotoxy(colum,line);
						if (7>togglecnt){
							togglecnt++;
						}
						else {
							togglecnt = 0;
						}
						PreKey = key;
						prec = c;
					}
					else if ('.' == key){
						c = KeyDot[togglecnt];
						dispch(c);
						gotoxy(colum,line);
						if (1>togglecnt){
							togglecnt++;
						}
						else {
							togglecnt = 0;
						}
						PreKey = key;
						prec = c;
					}
					else {
						c = key;
						PreKey = 0;
						loop = FALSE;
					}
				}
				else {
					if (KEY_S2 == key){
						PreKey = 0;
					}
					else {
						PreKey = key;
					}
					loop = FALSE;
				}
			}
		}
	}
	return c;
}
/*

unsigned char keygetchar(unsigned short line, unsigned short colum)
{
	unsigned char key;
	unsigned char c =0;
	unsigned short prec = 0;
	int loop = TRUE;
	int togglecnt = 0;
	int shiftstat;
	
	gotoxy(colum,line);
	if ('1' <= PreKey && '9' >= PreKey){
		c = KeyNum[togglecnt][PreKey - '1'];
		dispch(c);
		gotoxy(colum,line);
		prec = c;
		togglecnt++;
	}
	else if ('0' == PreKey){
		c = KeyZero[togglecnt];
		dispch(c);
		gotoxy(colum,line);
		prec = c;
		togglecnt++;
	}
	else if ('.' == PreKey){
		c = KeyDot[togglecnt];
		dispch(c);
		gotoxy(colum,line);
		prec = c;
		togglecnt++;
	}
	else if (0 != PreKey){
		c = PreKey;
		if (KEY_S1 == PreKey){
			PreKey = 0xFF;
		}
		else if (0xFF == PreKey){
			PreKey = 0;
			c = KEY_S1;
		}
		else {
			PreKey = 0;
		}
		loop = FALSE;
	}
	
	shiftstat = shiftkey_state();
	while (loop){
		if (0 != prec && (ON == shiftstat && OFF == shiftkey_state())){
			PreKey = 0;
			loop = FALSE;
		}
		if (kbhit()){
			key = keycharread();
			if (!(shiftstat = shiftkey_state())){
				if (('0' <= key && '9' >= key) || '.' == key){
					dispch(key);
				}
				c = key;
				PreKey = 0;
				loop = FALSE;
			}
			else {
				if (0 == prec || PreKey == key){
					if ('1' <= key && '9' >= key){
						c = KeyNum[togglecnt][key - '1'];
						dispch(c);
						gotoxy(colum,line);
						if (3>togglecnt){
							togglecnt++;
						}
						else {
							togglecnt = 0;
						}
						PreKey = key;
						prec = c;
					}
					else if ('0' == key){
						c = KeyZero[togglecnt];
						dispch(c);
						gotoxy(colum,line);
						if (7>togglecnt){
							togglecnt++;
						}
						else {
							togglecnt = 0;
						}
						PreKey = key;
						prec = c;
					}
					else if ('.' == key){
						c = KeyDot[togglecnt];
						dispch(c);
						gotoxy(colum,line);
						if (1>togglecnt){
							togglecnt++;
						}
						else {
							togglecnt = 0;
						}
						PreKey = key;
						prec = c;
					}
					else {
						c = key;
						PreKey = 0;
						loop = FALSE;
					}
				}
				else {
					if (KEY_S2 == key){
						PreKey = 0;
					}
					else {
						PreKey = key;
					}
					loop = FALSE;
				}
			}
		}
	}
	return c;
}
*/
/**************************************************************************************************
	inputline
要約：
   文字列入力（シフトモード対応）
   unsigned char inputline(unsigned short line, unsigned short colum,char *buff, unsigned short len, unsigned short displen, char *exitchar)
   		line		入力キー表示開始ライン位置
   		colum		入力キー表示開始カラム位置
   		displen		入力文字列表示長
   		buff		入力文字列格納アドレス
   		len			入力文字列長
   		exitchar	終了キー格納アドレス
解説：
   	指定したline,colum の位置より、len分キーの文字入力を行い、displen で指定したデータ長分表示する。
   	exitcharに指定したキーキャラクタが押されると、本関数を終了する。
   
戻り値：
	終了キーキャラクタ
注意：
	予めパラメータに設定する値は、エラーにならない値を設定すること
	本関数は、カーソルを表示してから使用すること。
**************************************************************************************************/
unsigned char inputline(unsigned short line, unsigned short colum,char *buff, unsigned short len, unsigned short displen, char *exitchar)
{
	unsigned char c;						/* キー入力格納用 */
	unsigned int inpos = 0;
	unsigned int nullpos = 0;
	unsigned int curpos = 0;
	unsigned int disppos = 0;
	unsigned int dispmax = displen -1;

	int loop = TRUE;
	int i;
	
	keyclear();
	keygetcharinit();

	nullpos = strlen(buff);
	dispnstr(line,colum,buff,displen);
	
	while (loop){
		c = keygetchar(line,(unsigned short)(colum+curpos));
		if (0 != strchr(exitchar,(int)c)){
			loop = FALSE;
		}
		else if (0x20 <= c && 0x5F >= c){
			*(buff+inpos) = c;
			if (nullpos == inpos){
				nullpos++;
				*(buff+nullpos)= 0;
			}
			if (len -1 != inpos){
				inpos++;
			}
			if (dispmax != curpos){
				curpos++;
			}
			disppos = inpos - curpos;
			dispnstr(line,colum,buff+disppos,displen);
		}
		else if (KEY_CLR == c){
			if (0 == nullpos){
				buzzer_err();
			}
			else {
				gotoxy(colum,line);
				for (i=0;i<=dispmax;i++){
					dispch(' ');
				}
				gotoxy(colum,line);
			}
			inpos = 0;
			nullpos = 0;
			curpos = 0;
			disppos = 0;
			*(buff) = 0;
		}
		else if (KEY_BS == c){
			if (0 == inpos){
				buzzer_err();
			}
			else if (nullpos == len && len -1 == inpos){
				nullpos--;
				*(buff+nullpos) = 0;
				disppos = inpos - curpos;
				dispnstr(line,colum,buff+disppos,displen);
				dispch(' ');
			}
			else {
				strncpy(buff+inpos -1,buff+inpos,(size_t)(nullpos -inpos));
				nullpos--;
				inpos--;
				*(buff+nullpos) = 0;
				if (curpos > inpos){
					curpos--;
				}
				disppos = inpos - curpos;
				dispnstr(line,colum,buff+disppos,displen);
				if (dispmax >= (nullpos - inpos)+curpos){
					dispch(' ');
				}
			}
		}
		else if (KEY_S1 == c){
			if (0 == inpos){
				buzzer_err();
			}
			else {
				inpos--;
				if (0 != curpos){
					curpos--;
				}
				else {
					disppos = inpos-curpos;
					dispnstr(line,colum,buff+disppos,displen);
				}
			}
		}
		else if (KEY_S2 == c){
			if (nullpos == inpos || len-1 ==inpos){
				buzzer_err();
			}
			else {
				inpos++;
				if (dispmax != curpos){
					curpos++;
				}
				disppos = inpos -curpos;
				dispnstr(line,colum,buff+disppos,displen);
				if (nullpos == inpos){
					dispch(' ');
				}
			}
		}
		else {
			buzzer_err();
		}
	}
	return c;
}
