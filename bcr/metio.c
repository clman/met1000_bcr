/******************************************************************************
   metio.c	- MET Series input/output Function

   Copyright (C) 2005 Nippon Systems Development Co.,Ltd. All Rights Reserved
   
   $Log: metio.c,v $
   Revision 1.2  2005/07/01 06:48:59  f
   inputline [S1]�L�[ �s��C��

   Revision 1.1.1.1  2005/07/01 05:39:17  f
   �V�K


******************************************************************************/
/*
�{�v���O�����g�p�Ɋւ���K��
   
   �E�{�v���O�����́A�J�X�^�}�C�Y���s����l�\�[�X�v���O�����Ƃ��Ē񋟂��܂��B
   �@�{�v���O���������C�u���������Ă̎g�p�͍s��Ȃ��ł��������B
   �E�֐���ύX���Ďg�p����ꍇ�́A�ύX�������֐������o���ʃt�@�C���ŕύX���邩�A
     �܂��́A��L�̃t�@�C���w�b�_�ɕύX���e���L�ڂ��Ă��������B�i���̏ꍇ�́A
     �l�ł̊Ǘ����肢���܂��B�j
   �E�{�v���O�������g�p����ۂ́A�J�������A�v���P�[�V�����ɂ����ĕK�������
   �@���؏\�����s���Ă��������B
   �@�i�{�v���O�������g�p���ẴA�v���P�[�V�����s��͈�ؐӔC�͂��Ă܂���B
   �@�@���ȐӔC�Ŏg�p���Ă��������B�j

   �E��L���ڂɏ����ł��Ȃ��ꍇ�́A�g�p���Ȃ��ł��������B
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
�v��F
   	�����\��
	void dispchar(unsigned short line, unsigned short colum, int size, int attr, unsigned short c)
   		line	�\���J�n���C���ʒu
   		colum	�\���J�n�J�����ʒu
		size	�\�������T�C�Y�iANK,1/4�j
   		deco	�����C���i�ʏ�,���]�j
   		c		�\������
����F
   �w�肵��line,colum�̈ʒu�ɁAsize�̑傫���̂�deco�̏C����c��\������
�߂�l�F
   	�Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
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
�v��F
   	�����\��
	void dispstr(unsigned short line, unsigned short colum, char *str)
   		line	�\���J�n���C���ʒu
   		colum	�\���J�n�J�����ʒu
   		str		�\��������
����F
   	�w�肵��line�Ccolum�̈ʒu�ɕ�����str��\������B
�߂�l�F
   	�Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
**************************************************************************************************/
void dispstr(unsigned short line, unsigned short colum, char *str)
{
	gotoxy(colum,line);
	put_string(str);
}
/**************************************************************************************************
	dispstrr
�v��F
   ���]������\��
	void dispstrr(unsigned short line, unsigned short colum , char *str)
   		line	�\���J�n���C���ʒu
   		colum	�\���J�n�J�����ʒu
   		str		�\��������
���:
   	�w�肵��line�Ccolum�̈ʒu�ɕ�����str�𔽓]�\������B
�߂�l�F
   	�Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
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
 �v��F
   	�\���������w��̕�����\��
	void dispnstr(unsigned short line, unsigned short colun, char *str, unsigned short cnt)
  		line	�\���J�n���C���ʒu
   		colum	�\���J�n�J�����ʒu
   		str		�\��������
   		cnt		�\��������
 ����F
   	�w�肵��line�Ccolum�̈ʒu�ɕ�����ste��cnt���\������
�߂�l�F
   	�Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
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
�v��F
   	�C���w�蕶����\��
	void dispstrattr(unsigned short line, unsigned short colum, int attr, char *str)
����F
   �w�肵��line,colum�̈ʒu��attr�Ŏw�肵���C���ŕ�����str��\������B
�߂�l�F
   	�Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
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
�v��F
   	���b�Z�[�W�\���i1�s�\���j
   	void dispmsgline(MSGINFO *msg,int attr)
		msg		��ʕ\�����\����
   		attr	�\�������i�ʏ�\��,���]�\���j
����F
   	msg �Ŏw�肵����ʏ����Aattr�Ŏw�肵���\�������ŕ\������B
   	�i1�s���̂݁j
   	
   msg �\����
   �����o�[					���e						12dot	16dot
   --------------------------------------------------------------------
	unsigned short line;	�\���J�n���C���ʒu 			1�`10	1�`8
	unsigned short colum;	�\���J�n�J�����ʒu 			1�`20	1�`14
	char str[21];			�\��������         		

 	arrt �� NORMAL ���w�肷��ƁA�ʏ핶����msg��\��
   	attr �� REVERSE���w�肷��ƁA���]������ msg��\��
�߂�l�F
   		�Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
**************************************************************************************************/
void dispmsgline(MSGINFO *msg,int attr)
{
	dispstrattr(msg->line,msg->colum,attr,msg->str);
}



/**************************************************************************************************
  	dispmsg
�v��F
	��ʕ\��
   	void dispmsg(MSGINFO *msg, int size)
   		msg		��ʕ\���ׂ̈̍\����
   		size 	���b�Z�[�W�\���T�C�Y
����F
   	msg�Ŏw�肵�����ɏ]����ʕ\�����s��

	MSGINFO�\���̂́A�ȉ��̃����o�[����\�������
   
   �����o�[					���e						12dot	16dot
   --------------------------------------------------------------------
	unsigned short line;	�\���J�n���C���ʒu 			1�`10	1�`8
	unsigned short colum;	�\���J�n�J�����ʒu 			1�`20	1�`14
	char str[21];			�\��������         		


�߂�l�F
   �Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
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
�v��F
	��ʕ\��
   	void dispmsgattr(MSGATTRINFO *msg, unsigned int size)
   		msg		��ʕ\���ׂ̈̍\����
   		size 	���b�Z�[�W�\���T�C�Y
����F
   	msg�Ŏw�肵�����ɏ]����ʕ\�����s��

	MSGATTRINFO�\���̂́A�ȉ��̃����o�[����\�������
   
   �����o�[					���e						12dot	16dot
   --------------------------------------------------------------------
	unsigned short line;	�\���J�n���C���ʒu 			1�`10	1�`8
	unsigned short colum;	�\���J�n�J�����ʒu 			1�`20	1�`14
    int attr;				������C������
   	char str[21];			�\��������         		


�߂�l�F
   �Ȃ�
���ӁF
    �\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
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
�v��F
   	�C�ӂ̃L�[�҂�
	unsigned char anykey(void)
����F
   	�C�ӂ̃L�[��҂�
�߂�l�F
   	�����ꂽ�L�[�L�����N�^��Ԃ��B
���ӁF
   	�{�֐��ł́A�L�[�o�b�t�@���N���A���Ă���C�ӂ̃L�[�҂�
   	���s���B�L�[�o�b�t�@���̃f�[�^���g�p����ꍇ�́A�g�p���Ȃ�����
**************************************************************************************************/
unsigned char anykey(void)
{
	keyclear();
	return keycharwait();
}
/**************************************************************************************************
	keywait
�v��F
   	�w��L�[�����҂�
	unsigned char keywait(char *s)
   		s		�L�[�҂��̕����� (�I�[��\0)
����F
   	s�ɃL�[�҂����s���L�[�L�����N�^���i�[���A�{�֐����Ăяo�����Ƃ�
    s�w�肵���L�[���������Ɩ{�֐�����߂�B
�߂�l�F
   �������ꂽ�L�[�L�����N�^
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
�v��F
   	�w��L�[�����҂�
	unsigned char keywaitbz(char *s,int buzz)
   		s		�L�[�҂��̕����� (�I�[��\0)
   		buzz	�L�[�҂��ȊO�����̎��̃u�U�[�̗L���iTRUE or FALSE�j
����F
   	s�ɃL�[�҂����s���L�[�L�����N�^���i�[���A�{�֐����Ăяo�����Ƃ�
    s�w�肵���L�[���������Ɩ{�֐�����߂�B
    s�Ɏw�肵���ȊO�̃L�[�������ꂽ�Ƃ��A�u�U�[��炵�����ꍇ
    buzz��TRUE���w�肷��B�炵�����Ȃ��ꍇ�́AFALSE�����Ă�����B
�߂�l�F
   �������ꂽ�L�[�L�����N�^
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
�v��F
   	���j���[�I��
    unsigned short menu(MSGINFO *msg, unsigned short size)
		msg			���b�Z�[�W�i���j���[�j�\�����
   		size		���b�Z�[�W���T�C�Y
����F
   	msg�Ŏw�肳�ꂽ�\�����ɏ]�����j���[��\������B
    [1]�`size�Ŏw�肵���l�i�L�[�j�����͉\
   	�I�����ꂽ���j���[�ԍ��𔽓]�\�����A[ENT]�L�[�Ń��j���[��
   	�m�肷��B
�߂�l�F
    �I�����ꂽ�L�[�̐��l�i1�`size�Ŏw�肵���l�j

**************************************************************************************************/
unsigned int menu(MSGINFO *msg, unsigned int size)
{
	unsigned char key;								/* �L�[�L�����N�^�i�[	*/
	unsigned int code;								/* �R�[�h�i�[			*/
	unsigned int num = 0;							/* ���j���[�ԍ��i�[		*/
	
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
�v��F
   	�u���b�N�J�[�\���\��
	void blockcursor(int blk)
   		blk		�u�����N�\���w��
����F
	blink�̎w��ɏ]���u���b�N�J�[�\����\������B
�߂�l�F
   	�Ȃ�
**************************************************************************************************/
void blockcursor(int blk)
{
	blink(blk);
	cursor(BLOCK);
}
/**************************************************************************************************
	linecursor
�v��F
   	���C���J�[�\���\��
   void linecursor(int blk)
   		blk		�u�����N�\���w��
����F
	blink�̎w��ɏ]���u���b�N�J�[�\����\������B
�߂�l�F
   	�Ȃ�
**************************************************************************************************/
void linecursor(int blk)
{
	blink(blk);
	cursor(UNDERBAR);
}
/**************************************************************************************************
	void cursoroff(void)
�v��F
   	�J�[�\����\��
   	void cursoroff(void)
����F
	�J�[�\�����\���ɂ���B
�߂�l�F
   	�Ȃ�
**************************************************************************************************/
void cursoroff(void)
{
	cursor(OFF);
}

/**************************************************************************************************
	keygetcharinit
�v��F
   keygetchar�֐�����������
   void keygetcharinit(void)
����F
   keygetchar�֐����Ăяo���O�ɁA�{�֐����ďo��keygetchar�֐��̏��������s��
   �w�肵��line,colum �̈ʒu�ŃL�[���͑҂����s���B
�߂�l�F
   �Ȃ�
**************************************************************************************************/
static unsigned char PreKey;							/* �V�t�g���[�h�p �O��L�[�i�[�G���A	*/
void keygetcharinit(void)
{
	PreKey = 0;
}

/**************************************************************************************************
	keygetchar
�v��F
   �L�[���́i��������͕⏕�p�֐��j
   unsigned char keygetchar(unsigned short line, unsigned short colum)
   		line	���̓L�[�\�����C���ʒu
   		colum	���̓L�[�\���J�����ʒu
����F
   	�w�肵��line,colum �̈ʒu�ŃL�[���͑҂����s���B
�߂�l�F
	���͂��ꂽ�L�[�L�����N�^
���ӁF
	�\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
   	�L�[���͏����i��������́j���Ŏg�p���邽�߂̕⏕�I�Ȋ֐��Ȃ��ߒP�Ƃł͎g�p���Ȃ�����
   	�{�֐��̎g�p���@�́Ainputline�֐����Q�Ƃ�
**************************************************************************************************/
/* �V�t�g���[�h �L�[�e�[�u��	*/
static const char KeyNum[4][10] = {						/* [1]�`[9]*/
	"ADGJMPSVY",
	"BEHKNQTWZ",
	"CFILORUX-",
	"123456789"
};
static const char KeyZero[9] = "$%+/:*\\0";				/*�m0�n*/
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
�v��F
   ��������́i�V�t�g���[�h�Ή��j
   unsigned char inputline(unsigned short line, unsigned short colum,char *buff, unsigned short len, unsigned short displen, char *exitchar)
   		line		���̓L�[�\���J�n���C���ʒu
   		colum		���̓L�[�\���J�n�J�����ʒu
   		displen		���͕�����\����
   		buff		���͕�����i�[�A�h���X
   		len			���͕�����
   		exitchar	�I���L�[�i�[�A�h���X
����F
   	�w�肵��line,colum �̈ʒu���Alen���L�[�̕������͂��s���Adisplen �Ŏw�肵���f�[�^�����\������B
   	exitchar�Ɏw�肵���L�[�L�����N�^���������ƁA�{�֐����I������B
   
�߂�l�F
	�I���L�[�L�����N�^
���ӁF
	�\�߃p�����[�^�ɐݒ肷��l�́A�G���[�ɂȂ�Ȃ��l��ݒ肷�邱��
	�{�֐��́A�J�[�\����\�����Ă���g�p���邱�ƁB
**************************************************************************************************/
unsigned char inputline(unsigned short line, unsigned short colum,char *buff, unsigned short len, unsigned short displen, char *exitchar)
{
	unsigned char c;						/* �L�[���͊i�[�p */
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
