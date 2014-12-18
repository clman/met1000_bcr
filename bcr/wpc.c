
#include <met1000.h>
#include "metio.h"
#include "metmenu.h"


extern SCANINFO ScanInfo;

void wpcoff(void);
void wpcon(void);
void wpcaddonoff(void);
void wpcaddonon(void);
void wpcaddoncoer(void);
void wpcprangeoff(void);
void wpcprangeon(void);
void wpcmarginoff(void);
void wpcmarginon(void);
void wpcpreambleeoff(void);
void wpcpreambleeon(void);
void wpcpreambleaoff(void);
void wpcpreambleaon(void);
void wpcupcetoaoff(void);
void wpcupcetoaon(void);
void wpcean8to13off(void);
void wpcean8to13on(void);

void wpcread(void);
void wpcaddon(void);
void wpcprange(void);
void wpcmargin(void);
void wpcpreamblee(void);
void wpcpreamblea(void);
void wpcupcetoa(void);
void wpcean8to13(void);


MENUINFO MenuWpcSet[] ={
	" WPC�ǎ�            ",wpcread,
	" ADDON�ǎ�          ",wpcaddon,
	" ���@�덷���e�͈�   ",wpcprange,
	" �}�[�W���`�F�b�N   ",wpcmargin,
	" UPCE�v���A���u��   ",wpcpreamblee,
	" UPCA�v���A���u��   ",wpcpreamblea,
	" UPCE->UPCA�ϊ�     ",wpcupcetoa,
	" EAN8->EAN13�ϊ�    ",wpcean8to13,
};

MENUINFO MenuWpcRead[] ={
	" WPC�ǎ�֎~        ",wpcoff,
	" WPC�ǎ拖��        ",wpcon,
};

MENUINFO MenuWpcAddon[] ={
	" ADDON�֎~          ",wpcaddonoff,
	" ADDON����          ",wpcaddonon,
	" ADDON����          ",wpcaddoncoer,
};

MENUINFO MenuWpcPrange[] ={
	" ���e�͈͎w�薳��   ",wpcprangeoff,
	" ���e�͈͎w��L��   ",wpcprangeon,
};

MENUINFO MenuWpcMargin[] ={
	" �����Ȃ�           ",wpcmarginoff,
	" ��������           ",wpcmarginon,
};
MENUINFO MenuWpcPreambleE[] ={
	" �v���A���u���Ȃ�   ",wpcpreambleeoff,
	" �v���A���u������   ",wpcpreambleeon,
};
MENUINFO MenuWpcPreambleA[] ={
	" �v���A���u���Ȃ�   ",wpcpreambleaoff,
	" �v���A���u������   ",wpcpreambleaon,
};
MENUINFO MenuWpcUpcetoa[] ={
	" �ϊ��Ȃ�           ",wpcupcetoaoff,
	" �ϊ�����           ",wpcupcetoaon,
};
MENUINFO MenuWpcEan8to13[] ={
	" �ϊ��Ȃ�           ",wpcean8to13off,
	" �ϊ�����           ",wpcean8to13on,
};


void wpcoff(void)
{
	ScanInfo.read.bit.wpc = 0;
	MenuBar[0].str[0] = ' ';
}
void wpcon(void)
{
	ScanInfo.read.bit.wpc = 1;
	MenuBar[0].str[0] = '*';
}
void wpcaddonoff(void)
{
	ScanInfo.wpc.bit.addon = 0;
}
void wpcaddonon(void)
{
	ScanInfo.wpc.bit.addon = 1;
}
void wpcaddoncoer(void)
{
	ScanInfo.wpc.bit.addon = 2;
}
void wpcprangeoff(void)
{
	ScanInfo.wpc.bit.prange = 0;
}
void wpcprangeon(void)
{
	ScanInfo.wpc.bit.prange = 1;
}
void wpcmarginoff(void)
{
	ScanInfo.wpc.bit.margin = 0;
}
void wpcmarginon(void)
{
	ScanInfo.wpc.bit.margin = 1;
}
void wpcpreambleeoff(void)
{
	ScanInfo.wpc.bit.preamble_e = 0;
}
void wpcpreambleeon(void)
{
	ScanInfo.wpc.bit.preamble_e = 1;
}
void wpcpreambleaoff(void)
{
	ScanInfo.wpc.bit.preamble_a = 0;
}
void wpcpreambleaon(void)
{
	ScanInfo.wpc.bit.preamble_a = 1;
}
void wpcupcetoaoff(void)
{
	ScanInfo.wpc.bit.upcetoa = 0;
}
void wpcupcetoaon(void)
{
	ScanInfo.wpc.bit.upcetoa = 1;
}
void wpcean8to13off(void)
{
	ScanInfo.wpc.bit.ean8to13 = 0;
}
void wpcean8to13on(void)
{
	ScanInfo.wpc.bit.ean8to13 = 1;
}


void wpcread(void)
{
	char s[] = "<<WPC�ǎ�>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.wpc;

	menuctrl(s,MenuWpcRead,sizeof(MenuWpcRead)/sizeof(MENUINFO),sw);
}
void wpcaddon(void)
{
	char s[] = "<<ADDON�ǎ�>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.addon;

	menuctrl(s,MenuWpcAddon,sizeof(MenuWpcAddon)/sizeof(MENUINFO),sw);
}
void wpcprange(void)
{
	char s[] = "<<���@�덷>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.prange;

	menuctrl(s,MenuWpcPrange,sizeof(MenuWpcPrange)/sizeof(MENUINFO),sw);
}
void wpcmargin(void)
{
	char s[] = "<<�}�[�W���`�F�b�N>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.margin;

	menuctrl(s,MenuWpcMargin,sizeof(MenuWpcMargin)/sizeof(MENUINFO),sw);
}
void wpcpreamblee(void)
{
	char s[] = "<<UPCE�v���A���u��>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.preamble_e;

	menuctrl(s,MenuWpcPreambleE,sizeof(MenuWpcPreambleE)/sizeof(MENUINFO),sw);
}
void wpcpreamblea(void)
{
	char s[] = "<<UPCA�v���A���u��>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.preamble_a;

	menuctrl(s,MenuWpcPreambleA,sizeof(MenuWpcPreambleA)/sizeof(MENUINFO),sw);
}
void wpcupcetoa(void)
{
	char s[] = "<<UPCE->UPCA>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.upcetoa;

	menuctrl(s,MenuWpcUpcetoa,sizeof(MenuWpcUpcetoa)/sizeof(MENUINFO),sw);
}

void wpcean8to13(void)
{
	char s[] = "<<UPCE->UPCA>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.ean8to13;

	menuctrl(s,MenuWpcEan8to13,sizeof(MenuWpcEan8to13)/sizeof(MENUINFO),sw);
}


unsigned int wpc(void)
{
	char s[] = "<<WPC�ݒ�>>";

	menuctrl(s,MenuWpcSet,sizeof(MenuWpcSet)/sizeof(MENUINFO),0);
}

