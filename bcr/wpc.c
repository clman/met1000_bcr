
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
	" WPC読取            ",wpcread,
	" ADDON読取          ",wpcaddon,
	" 寸法誤差許容範囲   ",wpcprange,
	" マージンチェック   ",wpcmargin,
	" UPCEプリアンブル   ",wpcpreamblee,
	" UPCAプリアンブル   ",wpcpreamblea,
	" UPCE->UPCA変換     ",wpcupcetoa,
	" EAN8->EAN13変換    ",wpcean8to13,
};

MENUINFO MenuWpcRead[] ={
	" WPC読取禁止        ",wpcoff,
	" WPC読取許可        ",wpcon,
};

MENUINFO MenuWpcAddon[] ={
	" ADDON禁止          ",wpcaddonoff,
	" ADDON許可          ",wpcaddonon,
	" ADDON強制          ",wpcaddoncoer,
};

MENUINFO MenuWpcPrange[] ={
	" 許容範囲指定無効   ",wpcprangeoff,
	" 許容範囲指定有効   ",wpcprangeon,
};

MENUINFO MenuWpcMargin[] ={
	" 調整なし           ",wpcmarginoff,
	" 調整あり           ",wpcmarginon,
};
MENUINFO MenuWpcPreambleE[] ={
	" プリアンブルなし   ",wpcpreambleeoff,
	" プリアンブルあり   ",wpcpreambleeon,
};
MENUINFO MenuWpcPreambleA[] ={
	" プリアンブルなし   ",wpcpreambleaoff,
	" プリアンブルあり   ",wpcpreambleaon,
};
MENUINFO MenuWpcUpcetoa[] ={
	" 変換なし           ",wpcupcetoaoff,
	" 変換あり           ",wpcupcetoaon,
};
MENUINFO MenuWpcEan8to13[] ={
	" 変換なし           ",wpcean8to13off,
	" 変換あり           ",wpcean8to13on,
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
	char s[] = "<<WPC読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.wpc;

	menuctrl(s,MenuWpcRead,sizeof(MenuWpcRead)/sizeof(MENUINFO),sw);
}
void wpcaddon(void)
{
	char s[] = "<<ADDON読取>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.addon;

	menuctrl(s,MenuWpcAddon,sizeof(MenuWpcAddon)/sizeof(MENUINFO),sw);
}
void wpcprange(void)
{
	char s[] = "<<寸法誤差>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.prange;

	menuctrl(s,MenuWpcPrange,sizeof(MenuWpcPrange)/sizeof(MENUINFO),sw);
}
void wpcmargin(void)
{
	char s[] = "<<マージンチェック>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.margin;

	menuctrl(s,MenuWpcMargin,sizeof(MenuWpcMargin)/sizeof(MENUINFO),sw);
}
void wpcpreamblee(void)
{
	char s[] = "<<UPCEプリアンブル>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.preamble_e;

	menuctrl(s,MenuWpcPreambleE,sizeof(MenuWpcPreambleE)/sizeof(MENUINFO),sw);
}
void wpcpreamblea(void)
{
	char s[] = "<<UPCAプリアンブル>>";
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
	char s[] = "<<WPC設定>>";

	menuctrl(s,MenuWpcSet,sizeof(MenuWpcSet)/sizeof(MENUINFO),0);
}

