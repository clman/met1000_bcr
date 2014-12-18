#include "met1000.h"
#include "metio.h"
#include "metmenu.h"



/**********************************************************************************Start*
		menudisp
�v��F
		���j���[�\��
		void menudisp(unsigned int colum,unsigned int line, unsigned int cnt, unsigned int cur,MENUINFO *menu)
			colum			�ʒu�i�J�����j
			line			�ʒu�i���C���j
			cnt				�\�����C����
			cur				�J�[�\���\�����C����
			menu			�\�����j���[
����F
		���j���[ �Ŏw�肵����������w��ʒu�ɕ\�����Acur�Ŏw�肵���ʒu��
		�J�[�\���\�������s��
		
�߂�l�F
		�Ȃ�
************************************************************************************End*/
void menudisp(unsigned int line, unsigned int colum, unsigned int cur,unsigned int cnt, MENUINFO *menu)
{
	int i;
	for (i=0;i<cnt;i++){ 
		if (i != cur){
			dispstr(line+(i*2),colum ,(char *)&menu->str);

		}
		else{
			dispstrr(line+(i*2),colum ,(char *)&menu->str);
		}
		menu++;
	}
}



/**********************************************************************************Start*
	menukey
�v��F
		���j���[�p�L�[����
		unsigned int menukey(unsigned int *offset,unsigned int *cur,unsigned int maxline,unsigned int menusize)
			offset			�\���ʒu�iMSGINFO offset�l�j
			cur				�J�[�\���\�����C����
			maxline			�\�����C����
			menusize		�\�����j���[�T�C�Y
����F
		
�߂�l�F
		���̓L�[
************************************************************************************End*/
static unsigned long KeyPress = 0;
unsigned int menukey(unsigned int *offset,unsigned int *cur,unsigned int maxline,unsigned int menusize)
{
	unsigned int key;
	unsigned int keydata;
	unsigned long keypress;
	unsigned int timer_on = FALSE;

	maxline--;
	menusize--;
	if (!kbhit()){
		while (1){
			if (keypress = keypressing()){
				if (!timer_on){
					if(KeyPress == keypress){
						timer_start(0,2);
						timer_on = TRUE;
					}
					else if (0 == KeyPress){
						timer_start(0,20);
						timer_on = TRUE;
					}
					else {
					}
				}
				else{
					if (!timer_value(0)){
						if (KSTATE_S2 == keypress){
							KeyPress = KSTATE_S2;
							keywrite(0x14e2);
							BUZZER_CLICK();
							break;
						}
						else if (KSTATE_S1 == keypress){
							KeyPress = KSTATE_S1;
							keywrite(0x13e1);
							BUZZER_CLICK();
							break;
						}
						else if (KSTATE_BS == keypress){
							KeyPress = KSTATE_BS;
							keywrite(0x1208);
							BUZZER_CLICK();
							break;
						}
						else {
							KeyPress = 0;
							break;
						}
					}
				}
			}
			else {
				KeyPress = 0;
				break;
			}
		}
	}
	
	key = keycharwait();
	switch (key){
	case KEY_S1:
		if (0 == *cur){
			if (0 == *offset){
				BUZZER_ERR();
			}
			else {
				*offset -= 1;
			}
		}
		else {
			*cur -= 1;
		}
		break;
	case KEY_S2:
		if (maxline == *cur){
			if (menusize == (*offset + *cur)){
				BUZZER_ERR();
			}
			else {
				*offset += 1;
			}
		}
		else {
			*cur += 1;
		}
		break;
	case KEY_TRG:
		BUZZER_CLICK();
		break;
	}
	return key;
}
/*

unsigned int menukey(unsigned int *offset,unsigned int *cur,unsigned int maxline,unsigned int menusize)
{
	unsigned int key;

	maxline--;
	menusize--;

	key = keycharwait();
	switch (key){
	case KEY_S1:
		if (0 == *cur){
			if (0 == *offset){
				BUZZER_ERR();
			}
			else {
				*offset -= 1;
			}
		}
		else {
			*cur -= 1;
		}
		break;
	case KEY_S2:
		if (maxline == *cur){
			if (menusize == (*offset + *cur)){
				BUZZER_ERR();
			}
			else {
				*offset += 1;
			}
		}
		else {
			*cur += 1;
		}
		break;
	case KEY_TRG:
		BUZZER_CLICK();
		break;
	}
	return key;
}

*/
/*
void menuctrl(char *title,MENUINFO *menu,unsigned int size,unsigned int cur)
{	
	unsigned int offset = 0;
	unsigned int key;
	unsigned int line = 5;

	if (FONT16 == font_state()){
		line = 4;
	}
	if (ON == sysarea_state()){
		line--;
	}
	if (line > size){
		line = size;
	}

	while (1){
		clear_screen();
		dispstr(2,1,title);

		menudisp(4,1,cur,line,(menu+offset));
		key = menukey(&offset,&cur,line,size);
		if (KEY_TRG == key || KEY_ENT == key){
			(menu+offset+cur)->func();
		}
		if (KEY_BS == key){
			break;
		}
	}
}
*/
void menuctrl(char *title,MENUINFO *menu,unsigned int size,unsigned int cur,char *exit)
{	
	unsigned int offset = 0;
	unsigned int key;
	unsigned int line = 5;

	if (FONT16 == font_state()){
		line = 4;
	}
	if (ON == sysarea_state()){
		line--;
	}
	if (line > size){
		line = size;
	}

	while (1){
		clear_screen();
		dispstr(2,1,title);

		menudisp(4,1,cur,line,(menu+offset));
		key = menukey(&offset,&cur,line,size);
		if (KEY_TRG == key || KEY_ENT == key){
			(menu+offset+cur)->func();
		}

		if (0 != strchr(exit,(int)key)){
			break;
		}
	}
}
