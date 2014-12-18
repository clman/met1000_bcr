#include <stdio.h>

#include <apver.h>
#include <met1000.h>
#include "metio.h"
#include "metmenu.h"


SCANINFO ScanInfo;
SCANINFO_EX ScanInfoEx;

unsigned long DBKey;

char *ExitKey_BS = "\x08";
char *ExitKey_BS_ENT = "\x08""\x0d""\xe0";



void numinput(unsigned short line, unsigned short colum, unsigned short len, unsigned short displen, char *buff)
{
	char s[] = "[                   ";
	unsigned int maxcolum = 20;

	if (FONT16 == font_state()){
		maxcolum = 14;
	}
	if (maxcolum > colum+displen){
		s[displen+1] = ']';
		s[displen+2] = 0;
	}
	dispstr(line, colum-1, s);
	blockcursor(ON);
	inputline(line, colum, buff, len, displen, "\x0d");
	cursoroff();

}


unsigned int bcr(void);
unsigned int check(void);
unsigned int timeout(void);
unsigned int length(void);
unsigned int samecode(void);
unsigned int goodread(void);



MENUINFO MenuMain[] ={
	" バーコード種別     ",bcr,
	" 照合回数           ",check,
	" 読取桁数           ",length,
	" 読取タイムアウト   ",timeout,
	" 同一バーコード読取 ",samecode,
	" 正読設定           ",goodread,
};







/****** バーコード種別 ****************************************************************/

unsigned int wpc(void);
unsigned int code39(void);
unsigned int code93(void);
unsigned int code128(void);
unsigned int nw7(void);
unsigned int stf(void);
unsigned int itf(void);
unsigned int rss14(void);
unsigned int rssli(void);
unsigned int rssex(void);
unsigned int collective(void);

MENUINFO MenuBar[] ={
	" WPC                ",wpc,
	" CODE39             ",code39,
	" CODE93             ",code93,
	" COCE128            ",code128,
	" NW7                ",nw7,
	" STF                ",stf,
	" ITF                ",itf,
	" RSS14              ",rss14,
	" RSS Limited        ",rssli,
	" RSS Expanded       ",rssex,
	" 一括設定           ",collective,
};

void bcrtype(void)
{
	unsigned short bcr;
	int i;
	bcr = ScanInfo.read.word;
	for (i=0;i<7;i++){
		if (bcr & 0x8000){
			MenuBar[i].str[0] = '*';
		}
		else {
			MenuBar[i].str[0] = ' ';
		}
		bcr<<=1;
	}
}

unsigned int bcr(void)
{
	char s[] = "<<barcode種別>>";

	bcrtype();
//	menuctrl(s,MenuBar,sizeof(MenuBar)/sizeof(MENUINFO),0);
	menuctrl(s,MenuBar,sizeof(MenuBar)/sizeof(MENUINFO),0,ExitKey_BS); 
}

/****** collective ************************************************************/

void alloff(void);
void allon(void);
MENUINFO MenuCollectiveSet[] ={
	" 読取全クリア       ",alloff,
	" 読取全設定         ",allon,
};

void alloff(void)
{
	int i;
	ScanInfo.read.word = 0x0000;
	ScanInfoEx.read.word = 0x0000;
	for(i=0;i<10;i++){
		MenuBar[i].str[0] = ' ';
	}
}
void allon(void)
{
	int i;
	ScanInfo.read.word = 0xFE00;
	ScanInfoEx.read.word = 0xE000;
	for(i=0;i<10;i++){
		MenuBar[i].str[0] = '*';
	}
}


unsigned int collective(void)
{
	char s[] = "<<一括設定>>";

//	menuctrl(s,MenuCollectiveSet,sizeof(MenuCollectiveSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuCollectiveSet,sizeof(MenuCollectiveSet)/sizeof(MENUINFO),0,ExitKey_BS);
}


/****** WPC *******************************************************************/

void wpcread(void);
void wpcaddon(void);
void wpcprange(void);
void wpcmargin(void);
void wpcpreamblee(void);
void wpcpreamblea(void);
void wpcupcetoa(void);
void wpcean8to13(void);

MENUINFO MenuWpcSet[] ={
	" WPC読取          : ",wpcread,
	" ADDON読取        : ",wpcaddon,
	" 寸法誤差許容範囲 : ",wpcprange,
	" マージンチェック : ",wpcmargin,
	" UPCEプリアンブル : ",wpcpreamblee,
	" UPCAプリアンブル : ",wpcpreamblea,
	" UPCE->UPCA変換   : ",wpcupcetoa,
	" EAN8->EAN13変換  : ",wpcean8to13,
};



void wpcoff(void);
void wpcon(void);
MENUINFO MenuWpcRead[] ={
	" WPC読取禁止        ",wpcoff,
	" WPC読取許可        ",wpcon,
};

void wpcaddonoff(void);
void wpcaddonon(void);
void wpcaddoncoer(void);
MENUINFO MenuWpcAddon[] ={
	" ADDON禁止          ",wpcaddonoff,
	" ADDON許可          ",wpcaddonon,
	" ADDON強制          ",wpcaddoncoer,
};
void wpcprangeoff(void);
void wpcprangeon(void);
MENUINFO MenuWpcPrange[] ={
	" 許容範囲指定無効   ",wpcprangeoff,
	" 許容範囲指定有効   ",wpcprangeon,
};
void wpcmarginoff(void);
void wpcmarginon(void);
MENUINFO MenuWpcMargin[] ={
	" 調整なし           ",wpcmarginoff,
	" 調整あり           ",wpcmarginon,
};

void wpcpreambleeoff(void);
void wpcpreambleeon(void);
MENUINFO MenuWpcPreambleE[] ={
	" プリアンブルなし   ",wpcpreambleeoff,
	" プリアンブルあり   ",wpcpreambleeon,
};
void wpcpreambleaoff(void);
void wpcpreambleaon(void);
MENUINFO MenuWpcPreambleA[] ={
	" プリアンブルなし   ",wpcpreambleaoff,
	" プリアンブルあり   ",wpcpreambleaon,
};
void wpcupcetoaoff(void);
void wpcupcetoaon(void);
MENUINFO MenuWpcUpcetoa[] ={
	" 変換なし           ",wpcupcetoaoff,
	" 変換あり           ",wpcupcetoaon,
};
void wpcean8to13off(void);
void wpcean8to13on(void);
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

//	menuctrl(s,MenuWpcRead,sizeof(MenuWpcRead)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcRead,sizeof(MenuWpcRead)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[0].str[19] = ScanInfo.read.bit.wpc + '0';
}
void wpcaddon(void)
{
	char s[] = "<<ADDON読取>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.addon;

//	menuctrl(s,MenuWpcAddon,sizeof(MenuWpcAddon)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcAddon,sizeof(MenuWpcAddon)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[1].str[19] = ScanInfo.wpc.bit.addon + '0';
}
void wpcprange(void)
{
	char s[] = "<<寸法誤差>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.prange;

//	menuctrl(s,MenuWpcPrange,sizeof(MenuWpcPrange)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcPrange,sizeof(MenuWpcPrange)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[2].str[19] = ScanInfo.wpc.bit.prange + '0';
}
void wpcmargin(void)
{
	char s[] = "<<マージンチェック>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.margin;

//	menuctrl(s,MenuWpcMargin,sizeof(MenuWpcMargin)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcMargin,sizeof(MenuWpcMargin)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[3].str[19] = ScanInfo.wpc.bit.margin + '0';
}
void wpcpreamblee(void)
{
	char s[] = "<<UPCEプリアンブル>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.preamble_e;

//	menuctrl(s,MenuWpcPreambleE,sizeof(MenuWpcPreambleE)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcPreambleE,sizeof(MenuWpcPreambleE)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[4].str[19] = ScanInfo.wpc.bit.preamble_e + '0';
}
void wpcpreamblea(void)
{
	char s[] = "<<UPCAプリアンブル>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.preamble_a;

//	menuctrl(s,MenuWpcPreambleA,sizeof(MenuWpcPreambleA)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcPreambleA,sizeof(MenuWpcPreambleA)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[5].str[19] = ScanInfo.wpc.bit.preamble_a + '0';
}
void wpcupcetoa(void)
{
	char s[] = "<<UPCE->UPCA>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.upcetoa;

//	menuctrl(s,MenuWpcUpcetoa,sizeof(MenuWpcUpcetoa)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcUpcetoa,sizeof(MenuWpcUpcetoa)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[6].str[19] = ScanInfo.wpc.bit.upcetoa + '0';
}

void wpcean8to13(void)
{
	char s[] = "<<UPCE->UPCA>>";
	unsigned int sw = (unsigned short)ScanInfo.wpc.bit.ean8to13;

//	menuctrl(s,MenuWpcEan8to13,sizeof(MenuWpcEan8to13)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuWpcEan8to13,sizeof(MenuWpcEan8to13)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuWpcSet[7].str[19] = ScanInfo.wpc.bit.ean8to13 + '0';
}


unsigned int wpc(void)
{
	char s[] = "<<WPC設定>>";

	MenuWpcSet[0].str[19] = ScanInfo.read.bit.wpc + '0';
	MenuWpcSet[1].str[19] = ScanInfo.wpc.bit.addon + '0';
	MenuWpcSet[2].str[19] = ScanInfo.wpc.bit.prange + '0';
	MenuWpcSet[3].str[19] = ScanInfo.wpc.bit.margin + '0';
	MenuWpcSet[4].str[19] = ScanInfo.wpc.bit.preamble_e + '0';
	MenuWpcSet[5].str[19] = ScanInfo.wpc.bit.preamble_a + '0';
	MenuWpcSet[6].str[19] = ScanInfo.wpc.bit.upcetoa + '0';
	MenuWpcSet[7].str[19] = ScanInfo.wpc.bit.ean8to13 + '0';


//	menuctrl(s,MenuWpcSet,sizeof(MenuWpcSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuWpcSet,sizeof(MenuWpcSet)/sizeof(MENUINFO),0,ExitKey_BS);
}





/****** CODE39 ****************************************************************/

void code39off(void);
void code39on(void);

void code39cdcheckoff(void);
void code39cdcheckon(void);

void code39cddataoff(void);
void code39cddataon(void);

void code39marginoff(void);
void code39marginon(void);

void code39stspoff(void);
void code39stspon(void);

void code39fullasciioff(void);
void code39fullasciion(void);

void code39read(void);
void code39cdcheck(void);
void code39cddata(void);
void code39margin(void);
void code39stsp(void);
void code39fullascii(void);

unsigned int code39(void);


MENUINFO MenuCode39Set[] ={
	" CODE39読取       : ",code39read,
	" CD チェック      : ",code39cdcheck,
	" CD 付加          : ",code39cddata,
	" マージンチェック : ",code39margin,
	" Start･Stop 付加  : ",code39stsp,
	" フルアスキー     : ",code39fullascii,
};
MENUINFO MenuCode39Read[] ={
	" CODE39読取禁止     ",code39off,
	" CODE39読取許可     ",code39on,
};

MENUINFO MenuCode39Cdcheck[] ={
	" CD チェックなし    ",code39cdcheckoff,
	" CD チェックあり    ",code39cdcheckon,
};
MENUINFO MenuCode39Cddata[] ={
	" CD 付加しない      ",code39cddataoff,
	" CD 付加する        ",code39cddataon,
};
MENUINFO MenuCode39Margin[] ={
	" 調整なし           ",code39marginoff,
	" 調整あり           ",code39marginon,
};
MENUINFO MenuCode39Stsp[] ={
	" 付加しない         ",code39stspoff,
	" 付加する           ",code39stspon,
};
MENUINFO MenuCode39Fullascii[] ={
	" 変換しない         ",code39fullasciioff,
	" 変換する           ",code39fullasciion,
};


void code39off(void)
{
	ScanInfo.read.bit.code39 = 0;
	MenuBar[1].str[0] = ' ';
}
void code39on(void)
{
	ScanInfo.read.bit.code39 = 1;
	MenuBar[1].str[0] = '*';
}

void code39cdcheckoff(void)
{
	ScanInfo.code39.bit.cd_check = 0;
}
void code39cdcheckon(void)
{
	ScanInfo.code39.bit.cd_check = 1;
}
void code39cddataoff(void)
{
	ScanInfo.code39.bit.cd_data = 0;
}
void code39cddataon(void)
{
	ScanInfo.code39.bit.cd_data = 1;
}
void code39marginoff(void)
{
	ScanInfo.code39.bit.margin = 0;
}
void code39marginon(void)
{
	ScanInfo.code39.bit.margin = 1;
}
void code39stspoff(void)
{
	ScanInfo.code39.bit.stsp = 0;
}
void code39stspon(void)
{
	ScanInfo.code39.bit.stsp = 1;
}
void code39fullasciioff(void)
{
	ScanInfo.code39.bit.fullascii = 0;
}
void code39fullasciion(void)
{
	ScanInfo.code39.bit.fullascii = 1;
}



void code39read(void)
{
	char s[] = "<<CODE39読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.code39;

//	menuctrl(s,MenuCode39Read,sizeof(MenuCode39Read)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode39Read,sizeof(MenuCode39Read)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode39Set[0].str[19] = ScanInfo.read.bit.code39 + '0';
}
void code39cdcheck(void)
{
	char s[] = "<<CD チェック>>";
	unsigned int sw = (unsigned short)ScanInfo.code39.bit.cd_check;

//	menuctrl(s,MenuCode39Cdcheck,sizeof(MenuCode39Cdcheck)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode39Cdcheck,sizeof(MenuCode39Cdcheck)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode39Set[1].str[19] = ScanInfo.code39.bit.cd_check + '0';
}
void code39cddata(void)
{
	char s[] = "<<CD 付加>>";
	unsigned int sw = (unsigned short)ScanInfo.code39.bit.cd_data;

//	menuctrl(s,MenuCode39Cddata,sizeof(MenuCode39Cddata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode39Cddata,sizeof(MenuCode39Cddata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode39Set[2].str[19] = ScanInfo.code39.bit.cd_data + '0';
}
void code39margin(void)
{
	char s[] = "<<マージンチェック>>";
	unsigned int sw = (unsigned short)ScanInfo.code39.bit.margin;

//	menuctrl(s,MenuCode39Margin,sizeof(MenuCode39Margin)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode39Margin,sizeof(MenuCode39Margin)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode39Set[3].str[19] = ScanInfo.code39.bit.margin + '0';
}
void code39stsp(void)
{
	char s[] = "<<START･STOP 付加>>";
	unsigned int sw = (unsigned short)ScanInfo.code39.bit.stsp;

//	menuctrl(s,MenuCode39Stsp,sizeof(MenuCode39Stsp)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode39Stsp,sizeof(MenuCode39Stsp)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode39Set[4].str[19] = ScanInfo.code39.bit.stsp + '0';
}

void code39fullascii(void)
{
	char s[] = "<<フルアスキー>>";
	unsigned int sw = (unsigned short)ScanInfo.code39.bit.fullascii;

//	menuctrl(s,MenuCode39Fullascii,sizeof(MenuCode39Fullascii)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode39Fullascii,sizeof(MenuCode39Fullascii)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode39Set[5].str[19] = ScanInfo.code39.bit.fullascii + '0';
}

unsigned int code39(void)
{
	char s[] = "<<CODE39設定>>";

	MenuCode39Set[0].str[19] = ScanInfo.read.bit.code39 + '0';
	MenuCode39Set[1].str[19] = ScanInfo.code39.bit.cd_check + '0';
	MenuCode39Set[2].str[19] = ScanInfo.code39.bit.cd_data + '0';
	MenuCode39Set[3].str[19] = ScanInfo.code39.bit.margin + '0';
	MenuCode39Set[4].str[19] = ScanInfo.code39.bit.stsp + '0';
	MenuCode39Set[5].str[19] = ScanInfo.code39.bit.fullascii + '0';

//	menuctrl(s,MenuCode39Set,sizeof(MenuCode39Set)/sizeof(MENUINFO),0);
	menuctrl(s,MenuCode39Set,sizeof(MenuCode39Set)/sizeof(MENUINFO),0,ExitKey_BS);
}


/****** CODE93 *****************************************************************/

void code93off(void);
void code93on(void);
void code93read(void);
unsigned int code93(void);



MENUINFO MenuCode93Set[] ={
	" CODE93読取       : ",code93read,
};
MENUINFO MenuCode93Read[] ={
	" CODE93読取禁止     ",code93off,
	" CODE93読取許可     ",code93on,
};


void code93off(void)
{
	ScanInfo.read.bit.code93 = 0;
	MenuBar[2].str[0] = ' ';
}
void code93on(void)
{
	ScanInfo.read.bit.code93 = 1;
	MenuBar[2].str[0] = '*';
}

void code93read(void)
{
	char s[] = "<<CODE93読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.code93;

//	menuctrl(s,MenuCode93Read,sizeof(MenuCode93Read)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode93Read,sizeof(MenuCode93Read)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode93Set[0].str[19] = ScanInfo.read.bit.code93 + '0';

}

unsigned int code93(void)
{
	char s[] = "<<CODE93設定>>";

	MenuCode93Set[0].str[19] = ScanInfo.read.bit.code93 + '0';
//	menuctrl(s,MenuCode93Set,sizeof(MenuCode93Set)/sizeof(MENUINFO),0);
	menuctrl(s,MenuCode93Set,sizeof(MenuCode93Set)/sizeof(MENUINFO),0,ExitKey_BS);
}



/****** CODE128 *****************************************************************/


void code128off(void);
void code128on(void);
void code128cdcheckoff(void);
void code128cdcheckon(void);
void code128ean128off(void);
void code128ean128on(void);

void code128read(void);
void code128cdcheck(void);
void code128ean128(void);

unsigned int code128(void);


MENUINFO MenuCode128Set[] ={
	" CODE128読取      : ",code128read,
	" CD チェック      : ",code128cdcheck,
	" EAN128           : ",code128ean128,
};
MENUINFO MenuCode128Read[] ={
	" CODE128読取禁止    ",code128off,
	" CODE128読取許可    ",code128on,
};

MENUINFO MenuCode128Cdcheck[] ={
	" CD チェックなし    ",code128cdcheckoff,
	" CD チェックあり    ",code128cdcheckon,
};
MENUINFO MenuCode128Ean128[] ={
	" 対応しない         ",code128ean128off,
	" 対応する           ",code128ean128on,
};


void code128off(void)
{
	ScanInfo.read.bit.code128 = 0;
	MenuBar[3].str[0] = ' ';
}
void code128on(void)
{
	ScanInfo.read.bit.code128 = 1;
	MenuBar[3].str[0] = '*';
}
void code128cdcheckoff(void)
{
	ScanInfo.code128.bit.cd_check = 0;
}
void code128cdcheckon(void)
{
	ScanInfo.code128.bit.cd_check = 1;
}
void code128ean128off(void)
{
	ScanInfo.code128.bit.ean128 = 0;
}
void code128ean128on(void)
{
	ScanInfo.code128.bit.ean128 = 1;
}


void code128read(void)
{
	char s[] = "<<CODE128読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.code128;

//	menuctrl(s,MenuCode128Read,sizeof(MenuCode128Read)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode128Read,sizeof(MenuCode128Read)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode128Set[0].str[19] = ScanInfo.read.bit.code128 + '0';
}
void code128cdcheck(void)
{
	char s[] = "<<CD チェック>>";
	unsigned int sw = (unsigned short)ScanInfo.code128.bit.cd_check;

//	menuctrl(s,MenuCode128Cdcheck,sizeof(MenuCode128Cdcheck)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode128Cdcheck,sizeof(MenuCode128Cdcheck)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode128Set[1].str[19] = ScanInfo.code128.bit.cd_check + '0';
}
void code128ean128(void)
{
	char s[] = "<<EAN128>>";
	unsigned int sw = (unsigned short)ScanInfo.code128.bit.ean128;

//	menuctrl(s,MenuCode128Ean128,sizeof(MenuCode128Ean128)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuCode128Ean128,sizeof(MenuCode128Ean128)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuCode128Set[2].str[19] = ScanInfo.code128.bit.ean128 + '0';
}


unsigned int code128(void)
{
	char s[] = "<<CODE128設定>>";

	MenuCode128Set[0].str[19] = ScanInfo.read.bit.code128 + '0';
	MenuCode128Set[1].str[19] = ScanInfo.code128.bit.cd_check + '0';
	MenuCode128Set[2].str[19] = ScanInfo.code128.bit.ean128 + '0';

//	menuctrl(s,MenuCode128Set,sizeof(MenuCode128Set)/sizeof(MENUINFO),0);
	menuctrl(s,MenuCode128Set,sizeof(MenuCode128Set)/sizeof(MENUINFO),0,ExitKey_BS);
}


/****** NW7 *****************************************************************/


void nw7off(void);
void nw7on(void);
void nw7cdcheckoff(void);
void nw7cdcheckon(void);
void nw7cddataoff(void);
void nw7cddataon(void);
void nw7marginoff(void);
void nw7marginon(void);
void nw7stspoff(void);
void nw7stspon(void);
void nw7stspcheroff(void);
void nw7stspcheron(void);


void nw7read(void);
void nw7cdcheck(void);
void nw7cddata(void);
void nw7margin(void);
void nw7stsp(void);
void nw7stspcher(void);

unsigned int nw7(void);


MENUINFO MenuNw7Set[] ={
	" Nw7読取          : ",nw7read,
	" CD チェック      : ",nw7cdcheck,
	" CD 付加          : ",nw7cddata,
	" マージンチェック : ",nw7margin,
	" START･STOP 付加  : ",nw7stsp,
	" フルアスキー     : ",nw7stspcher,
};
MENUINFO MenuNw7Read[] ={
	" NW7読取禁止     ",nw7off,
	" NW7読取許可     ",nw7on,
};

MENUINFO MenuNw7Cdcheck[] ={
	" CD チェックなし    ",nw7cdcheckoff,
	" CD チェックあり    ",nw7cdcheckon,
};
MENUINFO MenuNw7Cddata[] ={
	" CD 付加しない      ",nw7cddataoff,
	" CD 付加する        ",nw7cddataon,
};
MENUINFO MenuNw7Margin[] ={
	" 調整なし           ",nw7marginoff,
	" 調整あり           ",nw7marginon,
};
MENUINFO MenuNw7Stsp[] ={
	" 付加しない         ",nw7stspoff,
	" 付加する           ",nw7stspon,
};
MENUINFO MenuNw7Stspcher[] ={
	" 大文字指定         ",nw7stspcheroff,
	" 小文字指定         ",nw7stspcheron,
};


void nw7off(void)
{
	ScanInfo.read.bit.nw7 = 0;
	MenuBar[4].str[0] = ' ';
}
void nw7on(void)
{
	ScanInfo.read.bit.nw7 = 1;
	MenuBar[4].str[0] = '*';
}

void nw7cdcheckoff(void)
{
	ScanInfo.nw7.bit.cd_check = 0;
}
void nw7cdcheckon(void)
{
	ScanInfo.nw7.bit.cd_check = 1;
}
void nw7cddataoff(void)
{
	ScanInfo.nw7.bit.cd_data = 0;
}
void nw7cddataon(void)
{
	ScanInfo.nw7.bit.cd_data = 1;
}
void nw7marginoff(void)
{
	ScanInfo.nw7.bit.margin = 0;
}
void nw7marginon(void)
{
	ScanInfo.nw7.bit.margin = 1;
}
void nw7stspoff(void)
{
	ScanInfo.nw7.bit.stsp = 0;
}
void nw7stspon(void)
{
	ScanInfo.nw7.bit.stsp = 1;
}
void nw7stspcheroff(void)
{
	ScanInfo.nw7.bit.stspcher = 0;
}
void nw7stspcheron(void)
{
	ScanInfo.nw7.bit.stspcher = 1;
}



void nw7read(void)
{
	char s[] = "<<NW7読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.nw7;

//	menuctrl(s,MenuNw7Read,sizeof(MenuNw7Read)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuNw7Read,sizeof(MenuNw7Read)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuNw7Set[0].str[19] = ScanInfo.read.bit.nw7 + '0';
}
void nw7cdcheck(void)
{
	char s[] = "<<CD チェック>>";
	unsigned int sw = (unsigned short)ScanInfo.nw7.bit.cd_check;

//	menuctrl(s,MenuNw7Cdcheck,sizeof(MenuNw7Cdcheck)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuNw7Cdcheck,sizeof(MenuNw7Cdcheck)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuNw7Set[1].str[19] = ScanInfo.nw7.bit.cd_check + '0';
}
void nw7cddata(void)
{
	char s[] = "<<CD 付加>>";
	unsigned int sw = (unsigned short)ScanInfo.nw7.bit.cd_data;

//	menuctrl(s,MenuNw7Cddata,sizeof(MenuNw7Cddata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuNw7Cddata,sizeof(MenuNw7Cddata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuNw7Set[2].str[19] = ScanInfo.nw7.bit.cd_data + '0';
}
void nw7margin(void)
{
	char s[] = "<<マージンチェック>>";
	unsigned int sw = (unsigned short)ScanInfo.nw7.bit.margin;

//	menuctrl(s,MenuNw7Margin,sizeof(MenuNw7Margin)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuNw7Margin,sizeof(MenuNw7Margin)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuNw7Set[3].str[19] = ScanInfo.nw7.bit.margin + '0';
}
void nw7stsp(void)
{
	char s[] = "<<START･STOP 付加>>";
	unsigned int sw = (unsigned short)ScanInfo.nw7.bit.stsp;

//	menuctrl(s,MenuNw7Stsp,sizeof(MenuNw7Stsp)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuNw7Stsp,sizeof(MenuNw7Stsp)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuNw7Set[4].str[19] = ScanInfo.nw7.bit.stsp + '0';
}

void nw7stspcher(void)
{
	char s[] = "<<START･STOP 文字>>";
	unsigned int sw = (unsigned short)ScanInfo.nw7.bit.stspcher;

//	menuctrl(s,MenuNw7Stspcher,sizeof(MenuNw7Stspcher)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuNw7Stspcher,sizeof(MenuNw7Stspcher)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuNw7Set[5].str[19] = ScanInfo.nw7.bit.stspcher + '0';
}

unsigned int nw7(void)
{
	char s[] = "<<NW7設定>>";

	MenuNw7Set[0].str[19] = ScanInfo.read.bit.nw7 + '0';
	MenuNw7Set[1].str[19] = ScanInfo.nw7.bit.cd_check + '0';
	MenuNw7Set[2].str[19] = ScanInfo.nw7.bit.cd_data + '0';
	MenuNw7Set[3].str[19] = ScanInfo.nw7.bit.margin + '0';
	MenuNw7Set[4].str[19] = ScanInfo.nw7.bit.stsp + '0';
	MenuNw7Set[5].str[19] = ScanInfo.nw7.bit.stspcher + '0';

//	menuctrl(s,MenuNw7Set,sizeof(MenuNw7Set)/sizeof(MENUINFO),0);
	menuctrl(s,MenuNw7Set,sizeof(MenuNw7Set)/sizeof(MENUINFO),0,ExitKey_BS);
}


/****** STF *****************************************************************/

void stfoff(void);
void stfon(void);
void stfcdcheckoff(void);
void stfcdcheckon(void);
void stfcddataoff(void);
void stfcddataon(void);


void stfread(void);
void stfcdcheck(void);
void stfcddata(void);

unsigned int stf(void);


MENUINFO MenuStfSet[] ={
	" STF読取          : ",stfread,
	" CD チェック      : ",stfcdcheck,
	" CD 付加          : ",stfcddata,
};
MENUINFO MenuStfRead[] ={
	" STF読取禁止     ",stfoff,
	" STF読取許可     ",stfon,
};

MENUINFO MenuStfCdcheck[] ={
	" CD チェックなし    ",stfcdcheckoff,
	" CD チェックあり    ",stfcdcheckon,
};
MENUINFO MenuStfCddata[] ={
	" CD 付加しない      ",stfcddataoff,
	" CD 付加する        ",stfcddataon,
};




void stfoff(void)
{
	ScanInfo.read.bit.stf = 0;
	MenuBar[5].str[0] = ' ';
}
void stfon(void)
{
	ScanInfo.read.bit.stf = 1;
	MenuBar[5].str[0] = '*';
}

void stfcdcheckoff(void)
{
	ScanInfo.stf.bit.cd_check = 0;
}
void stfcdcheckon(void)
{
	ScanInfo.stf.bit.cd_check = 1;
}
void stfcddataoff(void)
{
	ScanInfo.stf.bit.cd_data = 0;
}
void stfcddataon(void)
{
	ScanInfo.stf.bit.cd_data = 1;
}



void stfread(void)
{
	char s[] = "<<STF読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.stf;

//	menuctrl(s,MenuStfRead,sizeof(MenuStfRead)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuStfRead,sizeof(MenuStfRead)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuStfSet[0].str[19] = ScanInfo.read.bit.stf + '0';
}
void stfcdcheck(void)
{
	char s[] = "<<CD チェック>>";
	unsigned int sw = (unsigned short)ScanInfo.stf.bit.cd_check;

//	menuctrl(s,MenuStfCdcheck,sizeof(MenuStfCdcheck)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuStfCdcheck,sizeof(MenuStfCdcheck)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuStfSet[1].str[19] = ScanInfo.stf.bit.cd_check + '0';
}
void stfcddata(void)
{
	char s[] = "<<CD 付加>>";
	unsigned int sw = (unsigned short)ScanInfo.stf.bit.cd_data;

//	menuctrl(s,MenuStfCddata,sizeof(MenuStfCddata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuStfCddata,sizeof(MenuStfCddata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuStfSet[2].str[19] = ScanInfo.stf.bit.cd_data + '0';
}


unsigned int stf(void)
{
	char s[] = "<<STF設定>>";

	MenuStfSet[0].str[19] = ScanInfo.read.bit.stf + '0';
	MenuStfSet[1].str[19] = ScanInfo.stf.bit.cd_check + '0';
	MenuStfSet[2].str[19] = ScanInfo.stf.bit.cd_data + '0';

//	menuctrl(s,MenuStfSet,sizeof(MenuStfSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuStfSet,sizeof(MenuStfSet)/sizeof(MENUINFO),0,ExitKey_BS);
}


/****** ITF *****************************************************************/

void itfoff(void);
void itfon(void);
void itfcdcheckoff(void);
void itfcdcheckon(void);
void itfcddataoff(void);
void itfcddataon(void);

void itfread(void);
void itfcdcheck(void);
void itfcddata(void);

unsigned int itf(void);

MENUINFO MenuItfSet[] ={
	" ITF読取          : ",itfread,
	" CD チェック      : ",itfcdcheck,
	" CD 付加          : ",itfcddata,
};
MENUINFO MenuItfRead[] ={
	" ITF読取禁止       ",itfoff,
	" ITF読取許可       ",itfon,
};

MENUINFO MenuItfCdcheck[] ={
	" CD チェックなし    ",itfcdcheckoff,
	" CD チェックあり    ",itfcdcheckon,
};
MENUINFO MenuItfCddata[] ={
	" CD 付加しない      ",itfcddataoff,
	" CD 付加する        ",itfcddataon,
};


void itfoff(void)
{
	ScanInfo.read.bit.itf = 0;
	MenuBar[6].str[0] = ' ';
}
void itfon(void)
{
	ScanInfo.read.bit.itf = 1;
	MenuBar[6].str[0] = '*';
}

void itfcdcheckoff(void)
{
	ScanInfo.itf.bit.cd_check = 0;
}
void itfcdcheckon(void)
{
	ScanInfo.itf.bit.cd_check = 1;
}
void itfcddataoff(void)
{
	ScanInfo.itf.bit.cd_data = 0;
}
void itfcddataon(void)
{
	ScanInfo.itf.bit.cd_data = 1;
}

void itfread(void)
{
	char s[] = "<<ITF読取>>";
	unsigned int sw = (unsigned short)ScanInfo.read.bit.itf;

//	menuctrl(s,MenuItfRead,sizeof(MenuItfRead)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuItfRead,sizeof(MenuItfRead)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuItfSet[0].str[19] = ScanInfo.read.bit.itf + '0';
}
void itfcdcheck(void)
{
	char s[] = "<<CD チェック>>";
	unsigned int sw = (unsigned short)ScanInfo.itf.bit.cd_check;

//	menuctrl(s,MenuItfCdcheck,sizeof(MenuItfCdcheck)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuItfCdcheck,sizeof(MenuItfCdcheck)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuItfSet[1].str[19] = ScanInfo.itf.bit.cd_check + '0';
}
void itfcddata(void)
{
	char s[] = "<<CD 付加>>";
	unsigned int sw = (unsigned short)ScanInfo.itf.bit.cd_data;

//	menuctrl(s,MenuItfCddata,sizeof(MenuItfCddata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuItfCddata,sizeof(MenuItfCddata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuItfSet[2].str[19] = ScanInfo.itf.bit.cd_data + '0';
}

unsigned int itf(void)
{
	char s[] = "<<ITF設定>>";

	MenuItfSet[0].str[19] = ScanInfo.read.bit.itf + '0';
	MenuItfSet[1].str[19] = ScanInfo.itf.bit.cd_check + '0';
	MenuItfSet[2].str[19] = ScanInfo.itf.bit.cd_data + '0';

//	menuctrl(s,MenuItfSet,sizeof(MenuItfSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuItfSet,sizeof(MenuItfSet)/sizeof(MENUINFO),0,ExitKey_BS_ENT);
}

/****** RSS 14 *****************************************************************/

void rss14off(void);
void rss14on(void);
void rss14aidataoff(void);
void rss14aidataon(void);
void rss14cddataoff(void);
void rss14cddataon(void);
void rss14read(void);
void rss14aidata(void);
void rss14cddata(void);


MENUINFO MenuRss14Set[] ={
	" RSS14 読取       : ",rss14read,
	" AI 付加          : ",rss14aidata,
	" CD 付加          : ",rss14cddata,
};
MENUINFO MenuRss14Read[] ={
	" RSS14読取禁止     ",rss14off,
	" RSS14読取許可     ",rss14on,
};

MENUINFO MenuRss14Aidata[] ={
	" AI 付加しない      ",rss14aidataoff,
	" AI 付加する        ",rss14aidataon,
};

MENUINFO MenuRss14Cddata[] ={
	" CD 付加しない      ",rss14cddataoff,
	" CD 付加する        ",rss14cddataon,
};

void rss14off(void)
{
	ScanInfoEx.read.bit.rss14 = 0;
	MenuBar[7].str[0] = ' ';
}
void rss14on(void)
{
	ScanInfoEx.read.bit.rss14 = 1;
	MenuBar[7].str[0] = '*';
}

void rss14aidataoff(void)
{
	ScanInfoEx.rss14.bit.ai_data = 0;
}
void rss14aidataon(void)
{
	ScanInfoEx.rss14.bit.ai_data = 1;
}
void rss14cddataoff(void)
{
	ScanInfoEx.rss14.bit.cd_data = 0;
}
void rss14cddataon(void)
{
	ScanInfoEx.rss14.bit.cd_data = 1;
}

void rss14read(void)
{
	char s[] = "<<RSS14 読取>>";
	unsigned int sw = (unsigned short)ScanInfoEx.read.bit.rss14;

//	menuctrl(s,MenuRss14Read,sizeof(MenuRss14Read)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRss14Read,sizeof(MenuRss14Read)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRss14Set[0].str[19] = ScanInfoEx.read.bit.rss14 + '0';
}
void rss14aidata(void)
{
	char s[] = "<<AI 付加>>";
	unsigned int sw = (unsigned short)ScanInfoEx.rss14.bit.ai_data;

//	menuctrl(s,MenuRss14Aidata,sizeof(MenuRss14Aidata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRss14Aidata,sizeof(MenuRss14Aidata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRss14Set[1].str[19] = ScanInfoEx.rss14.bit.ai_data + '0';
}
void rss14cddata(void)
{
	char s[] = "<<CD 付加>>";
	unsigned int sw = (unsigned short)ScanInfoEx.rss14.bit.cd_data;

//	menuctrl(s,MenuRss14Cddata,sizeof(MenuRss14Cddata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRss14Cddata,sizeof(MenuRss14Cddata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRss14Set[2].str[19] = ScanInfoEx.rss14.bit.cd_data + '0';
}


unsigned int rss14(void)
{
	char s[] = "<<RSS14 設定>>";

	MenuRss14Set[0].str[19] = ScanInfoEx.read.bit.rss14 + '0';
	MenuRss14Set[1].str[19] = ScanInfoEx.rss14.bit.ai_data + '0';
	MenuRss14Set[2].str[19] = ScanInfoEx.rss14.bit.cd_data + '0';

//	menuctrl(s,MenuRss14Set,sizeof(MenuRss14Set)/sizeof(MENUINFO),0);
	menuctrl(s,MenuRss14Set,sizeof(MenuRss14Set)/sizeof(MENUINFO),0,ExitKey_BS);
}

/****** RSS Limited *****************************************************************/

void rsslioff(void);
void rsslion(void);
void rssliaidataoff(void);
void rssliaidataon(void);
void rsslicddataoff(void);
void rsslicddataon(void);
void rssliread(void);
void rssliaidata(void);
void rsslicddata(void);


MENUINFO MenuRssliSet[] ={
	" RSS Limited 読取 : ",rssliread,
	" AI 付加          : ",rssliaidata,
	" CD 付加          : ",rsslicddata,
};
MENUINFO MenuRssliRead[] ={
	" 読取禁止           ",rsslioff,
	" 読取許可           ",rsslion,
};

MENUINFO MenuRssliAidata[] ={
	" AI 付加しない      ",rssliaidataoff,
	" AI 付加する        ",rssliaidataon,
};

MENUINFO MenuRssliCddata[] ={
	" CD 付加しない      ",rsslicddataoff,
	" CD 付加する        ",rsslicddataon,
};

void rsslioff(void)
{
	ScanInfoEx.read.bit.rssli = 0;
	MenuBar[8].str[0] = ' ';
}
void rsslion(void)
{
	ScanInfoEx.read.bit.rssli = 1;
	MenuBar[8].str[0] = '*';
}

void rssliaidataoff(void)
{
	ScanInfoEx.rssli.bit.ai_data = 0;
}
void rssliaidataon(void)
{
	ScanInfoEx.rssli.bit.ai_data = 1;
}
void rsslicddataoff(void)
{
	ScanInfoEx.rssli.bit.cd_data = 0;
}
void rsslicddataon(void)
{
	ScanInfoEx.rssli.bit.cd_data = 1;
}

void rssliread(void)
{
	char s[] = "<RSS Limited 読取>";
	unsigned int sw = (unsigned short)ScanInfoEx.read.bit.rssli;

//	menuctrl(s,MenuRssliRead,sizeof(MenuRssliRead)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRssliRead,sizeof(MenuRssliRead)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRssliSet[0].str[19] = ScanInfoEx.read.bit.rssli + '0';
}
void rssliaidata(void)
{
	char s[] = "<<AI 付加>>";
	unsigned int sw = (unsigned short)ScanInfoEx.rssli.bit.ai_data;

//	menuctrl(s,MenuRssliAidata,sizeof(MenuRssliAidata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRssliAidata,sizeof(MenuRssliAidata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRssliSet[1].str[19] = ScanInfoEx.rssli.bit.ai_data + '0';
}
void rsslicddata(void)
{
	char s[] = "<<CD 付加>>";
	unsigned int sw = (unsigned short)ScanInfoEx.rssli.bit.cd_data;

//	menuctrl(s,MenuRssliCddata,sizeof(MenuRssliCddata)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRssliCddata,sizeof(MenuRssliCddata)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRssliSet[2].str[19] = ScanInfoEx.rssli.bit.cd_data + '0';
}

unsigned int rssli(void)
{
	char s[] = "<RSS Limited 設定>";

	MenuRssliSet[0].str[19] = ScanInfoEx.read.bit.rssli + '0';
	MenuRssliSet[1].str[19] = ScanInfoEx.rssli.bit.ai_data + '0';
	MenuRssliSet[2].str[19] = ScanInfoEx.rssli.bit.cd_data + '0';

//	menuctrl(s,MenuRssliSet,sizeof(MenuRssliSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuRssliSet,sizeof(MenuRssliSet)/sizeof(MENUINFO),0,ExitKey_BS);
}

/****** RSS Expanded *****************************************************************/

void rssexoff(void);
void rssexon(void);
void rssexfnc1gsoff(void);
void rssexfnc1gson(void);
void rssexread(void);
void rssexfnc1gs(void);


MENUINFO MenuRssexSet[] ={
	" RSS Expanded 読取: ",rssexread,
	" FNC1->GS変換     : ",rssexfnc1gs,
};
MENUINFO MenuRssexRead[] ={
	" 読取禁止          ",rssexoff,
	" 読取許可          ",rssexon,
};

MENUINFO MenuRssexFnc1gs[] ={
	" 変換しない         ",rssexfnc1gsoff,
	" 変換する           ",rssexfnc1gson,
};

void rssexoff(void)
{
	ScanInfoEx.read.bit.rssex = 0;
	MenuBar[9].str[0] = ' ';
}
void rssexon(void)
{
	ScanInfoEx.read.bit.rssex = 1;
	MenuBar[9].str[0] = '*';
}

void rssexfnc1gsoff(void)
{
	ScanInfoEx.rssex.bit.fnc1_gs = 0;
}
void rssexfnc1gson(void)
{
	ScanInfoEx.rssex.bit.fnc1_gs = 1;
}

void rssexread(void)
{
	char s[] = "<RSS Expanded 読取>";
	unsigned int sw = (unsigned short)ScanInfoEx.read.bit.rssex;

//	menuctrl(s,MenuRssexRead,sizeof(MenuRssexRead)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRssexRead,sizeof(MenuRssexRead)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRssexSet[0].str[19] = ScanInfoEx.read.bit.rssex + '0';
}
void rssexfnc1gs(void)
{
	char s[] = "<<FNC1->GS変換>>";
	unsigned int sw = (unsigned short)ScanInfoEx.rssex.bit.fnc1_gs;

//	menuctrl(s,MenuRssexFnc1gs,sizeof(MenuRssexFnc1gs)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuRssexFnc1gs,sizeof(MenuRssexFnc1gs)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
	MenuRssexSet[1].str[19] = ScanInfoEx.rssex.bit.fnc1_gs + '0';
}


unsigned int rssex(void)
{
	char s[] = "<RSS Expanded 設定>";

	MenuRssexSet[0].str[19] = ScanInfoEx.read.bit.rssex + '0';
	MenuRssexSet[1].str[19] = ScanInfoEx.rssex.bit.fnc1_gs + '0';

//	menuctrl(s,MenuRssexSet,sizeof(MenuRssexSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuRssexSet,sizeof(MenuRssexSet)/sizeof(MENUINFO),0,ExitKey_BS);
}




/****** 照合回数 *****************************************************************/

unsigned int check(void)
{
	unsigned short val;
	char buff[2];
	char title[] = "<<照合回数>>";

	while (1){
		sprintf(buff,"%d",ScanInfo.check);
		clear_screen();
		dispstr(2, 1, title);
		numinput(6, 9, 1, 1, buff);
		val = atoi(buff);
		if (2 <= val && 5 >= val){
			ScanInfo.check = val;
			break;				
		}
		else {
			BUZZER_ERR();
		}
	}
	cursor(OFF);

}

/****** 読取桁数指定  *****************************************************************/

unsigned int length0(void);
unsigned int length1(void);
unsigned int length2(void);
unsigned int length3(void);
unsigned int length4(void);
unsigned int length5(void);
unsigned int length6(void);
unsigned int length7(void);


MENUINFO MenuLengthSet[] ={
	" 桁数指定0          ",length0,
	" 桁数指定1          ",length1,
	" 桁数指定2          ",length2,
	" 桁数指定3          ",length3,
	" 桁数指定4          ",length4,
	" 桁数指定5          ",length5,
	" 桁数指定6          ",length6,
	" 桁数指定7          ",length7,
};

unsigned int lengthset(unsigned int num)
{
	unsigned short val;
	char buff[4];
	char title[] = "<<桁数指定  >>";
	unsigned short maxlen = 127;

	if (KSTATE_F4 == (DBKey & KSTATE_F4)){
		maxlen = 128;
	}
	title[11] = num+'0';
	
	while (1){
		clear_screen();
		sprintf(buff,"%d",ScanInfo.length[num]);
		dispstr(2, 1, title);
		numinput(6, 7, 3, 3, buff);
		val = atoi(buff);
		if (0 <= val && maxlen >= val){
			ScanInfo.length[num] = val;
			break;				
		}
		else {
			BUZZER_ERR();
		}
	}
}

unsigned int length0(void)
{
	lengthset(0);
}
unsigned int length1(void)
{
	lengthset(1);
}
unsigned int length2(void)
{
	lengthset(2);
}
unsigned int length3(void)
{
	lengthset(3);
}
unsigned int length4(void)
{
	lengthset(4);
}
unsigned int length5(void)
{
	lengthset(5);
}
unsigned int length6(void)
{
	lengthset(6);
}
unsigned int length7(void)
{
	lengthset(7);
}


unsigned int length(void)
{
	char s[] = "<<読取桁数指定>>";

//	menuctrl(s,MenuLengthSet,sizeof(MenuLengthSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuLengthSet,sizeof(MenuLengthSet)/sizeof(MENUINFO),0,ExitKey_BS);
}

/****** 読取タイムアウト *****************************************************************/
unsigned int timeout(void)
{
	unsigned short val;
	char buff[4];
	char title[] = "<<読取タイムアウト>>";

	while (1){
		sprintf(buff,"%d",ScanInfo.timeout);
		clear_screen();
		dispstr(2, 1, title);
		numinput(6, 9, 2, 2, buff);
		val = atoi(buff);
		if (1 <= val && 10 >= val){
			ScanInfo.timeout = val;
			break;				
		}
		else {
			BUZZER_ERR();
		}
	}
}

/****** 同一バーコード読取 ************************************************************/
void samecodeoff(void);
void samecodeon(void);
MENUINFO MenuSamecodeSet[] ={
	" 読取禁止           ",samecodeoff,
	" 読取許可           ",samecodeon,
};

void samecodeoff(void)
{
		ScanInfo.samecode = 0;
}
void samecodeon(void)
{
		ScanInfo.samecode = 1;
}
unsigned int samecode(void)
{
	char s[] = "<<同一バーコード>>";
	unsigned int sw = (unsigned short)ScanInfo.samecode;

//	menuctrl(s,MenuSamecodeSet,sizeof(MenuSamecodeSet)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuSamecodeSet,sizeof(MenuSamecodeSet)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
}

/****** 正読指標  *****************************************************************/
void ledoff(void);
void ledon(void);
void ledset(void);

void buzzeroff(void);
void buzzeron(void);
void buzzerset(void);


void vibratoroff(void);
void vibratoron(void);
void vibratorset(void);

void grtime(void);
void bzfreq(void);
void vbtime(void);

MENUINFO MenuGoodreadSet[] ={
	" LED 点灯設定       ",ledset,
	" ブザー鳴動設定     ",buzzerset,
	" バイブ動作設定     ",vibratorset,
	" LED 動作時間       ",grtime,
	" ブザー音域設定     ",bzfreq,
	" バイブ動作時間     ",vbtime,
};

MENUINFO MenuLedSet[] ={
	" LED 非点灯         ",ledoff,
	" LED 点灯           ",ledon,
};

MENUINFO MenuBuzzerSet[] ={
	" ブザー非鳴動       ",buzzeroff,
	" ブザー鳴動         ",buzzeron,
};
MENUINFO MenuVivratorSet[] ={
	" バイブ非動作       ",vibratoroff,
	" バイブ動作         ",vibratoron,
};


void ledoff(void)
{
	ScanInfo.goodread.bit.led = 0;
}
void ledon(void)
{
	ScanInfo.goodread.bit.led = 1;
}
void ledset(void)
{
	char s[] = "<<LED 点灯>>";
	unsigned int sw = (unsigned short)ScanInfo.goodread.bit.led;

//	menuctrl(s,MenuLedSet,sizeof(MenuLedSet)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuLedSet,sizeof(MenuLedSet)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
}

void buzzeroff(void)
{
	ScanInfo.goodread.bit.buzzer = 0;
	
}
void buzzeron(void)
{
	ScanInfo.goodread.bit.buzzer = 1;
}
void buzzerset(void)
{
	char s[] = "<<ブザー鳴動>>";
	unsigned int sw = (unsigned short)ScanInfo.goodread.bit.buzzer;

//	menuctrl(s,MenuBuzzerSet,sizeof(MenuBuzzerSet)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuBuzzerSet,sizeof(MenuBuzzerSet)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
}


void vibratoroff(void)
{
	ScanInfo.goodread.bit.vibrator = 0;
	
}
void vibratoron(void)
{
	ScanInfo.goodread.bit.vibrator = 1;
}
void vibratorset(void)
{
	char s[] = "<<バイブ動作>>";
	unsigned int sw = (unsigned short)ScanInfo.goodread.bit.vibrator;

//	menuctrl(s,MenuVivratorSet,sizeof(MenuVivratorSet)/sizeof(MENUINFO),sw);
	menuctrl(s,MenuVivratorSet,sizeof(MenuVivratorSet)/sizeof(MENUINFO),sw,ExitKey_BS_ENT);
}

void grtime(void)
{
	unsigned short val;
	char buff[4];
	char title[] = "<<indicat 時間>>";

	
	while (1){
		sprintf(buff,"%d",ScanInfo.grtime);
		clear_screen();
		dispstr(2, 1, title);
		numinput(6, 7, 2, 2, buff);
		val = atoi(buff);
		if (3 <= val && 10 >= val){
			ScanInfo.grtime = val;
			break;				
		}
		else {
			BUZZER_ERR();
		}
	}
}
void bzfreq(void)
{
	unsigned short val;
	char buff[6];
	char title[] = "<<ブザー音域>>";

	
	while (1){
		clear_screen();
		sprintf(buff,"%d",ScanInfo.bzfreq);
		dispstr(2, 1, title);
		numinput(6, 6, 5, 5, buff);
		val = atoi(buff);
		if (50 <= val && 10000 >= val){
			ScanInfo.bzfreq = val;
			break;				
		}
		else {
			BUZZER_ERR();
		}
	}
}

void vbtime(void)
{
	unsigned short val;
	char buff[4];
	char title[] = "<<バイブ動作時間>>";

	
	while (1){
		clear_screen();
		sprintf(buff,"%d",ScanInfo.vbtime);
		dispstr(2, 1, title);
		numinput(6, 7, 2, 2, buff);
		val = atoi(buff);
		if (10 <= val && 50 >= val){
			ScanInfo.vbtime = val;
			break;				
		}
		else {
			BUZZER_ERR();
		}
	}
}

unsigned int goodread(void)
{
	char s[] = "<<正読設定>>";

//	menuctrl(s,MenuGoodreadSet,sizeof(MenuGoodreadSet)/sizeof(MENUINFO),0);
	menuctrl(s,MenuGoodreadSet,sizeof(MenuGoodreadSet)/sizeof(MENUINFO),0,ExitKey_BS);
}


/****** 読取処理  *****************************************************************/
const char BcrId[][22] = {
	"             ",
	"WPC          ",
	"NW7          ",
	"ITF          ",
	"STF          ",
	"CODE39       ",
	"CODE93       ",
	"CODE128      ",
	"EAN128       ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"             ",
	"RSS-14       ",
	"RSS Limited  ",
	"RSS Expanded ",
	"RSS Expanded ",
};

unsigned char fn_scanwait(void)
{
	short id;
	unsigned char buff[128] = "\x00";
	int len;
	int result;
	unsigned char key;
	char s[22];

	clear_screen();
	dispstr(2,1,"<<SCANWAIT>>");
	dispstr(4,1,"CODE = ");
	dispstr(6,1,"LEN  = ");
	dispstr(8,1,"[                  ]");


	while (1){
		blockcursor(ON);
		key = inputline(8,2,(char *)buff,127,18,"\xe0\xF1\xF2\xF3\xF4");
		cursoroff();

		if (0xF1 <= key && 0xF4 >= key){
			break;
		}
		keywrite(0x15e0);
		result = scanwait(&id,buff,&len);
		if (1 == result){
			sprintf(s,"%3d",len);
			dispstr(4,8,BcrId[id]);
			dispstr(6,8,s);
			dispstr(8,1,"[                  ]");

		}
	}
	return key;
}
unsigned char fn_scanread(void)
{
	short id;
	unsigned char buff[128] = "\x00";
	int len;
	int result;
	unsigned char key;
	char s[22];

	clear_screen();
	dispstr(2,1,"<<SCANREAD>>");
	dispstr(4,1,"CODE = ");
	dispstr(6,1,"LEN  = ");
	dispstr(8,1,"[                  ]");


	while (1){
		blockcursor(ON);
		key = inputline(8,2,(char *)buff,127,18,"\xe0\xF1\xF2\xF3\xF4");
		cursoroff();

		if (0xF1 <= key && 0xF4 >= key){
			break;
		}
		result = scanread(&id,buff,&len);
		if (1 == result){
			sprintf(s,"%3d",len);
			dispstr(4,8,BcrId[id]);
			dispstr(6,8,s);
			dispstr(8,1,"[                  ]");

		}
	}
	return key;
}
unsigned char fn_scan(void)
{
	short id;
	unsigned char buff[128] = "\x00";
	int len;
	int result;
	unsigned char key;
	char s[22];

	clear_screen();
	dispstr(2,1,"<<SCAN>>");
	dispstr(4,1,"CODE = ");
	dispstr(6,1,"LEN  = ");
	dispstr(8,1,"[                  ]");


	while (1){
		blockcursor(ON);
		key = inputline(8,2,(char *)buff,127,18,"\xe0\xF1\xF2\xF3\xF4");
		cursoroff();

		if (0xF1 <= key && 0xF4 >= key){
			break;
		}
		result = scan(1,&id,buff,&len);
		if (1 == result){
			sprintf(s,"%3d",len);
			dispstr(4,8,BcrId[id]);
			dispstr(6,8,s);
			dispstr(8,1,"[                  ]");

		}
	}
	return key;
}

void main(void)
{
	unsigned char key = 0xF1;
	unsigned char prekey = 0xF1;
	int result;
	char s[2][3][22];

	BUZZER_CLICK();
	DBKey = keypressing();

	font(FONT12);
	sysarea(OFF);
	result = scanmode(MODE_DEFAULT,&ScanInfo);
	sprintf(s[0][0],"%d",result);
	result = scanmode_ex(MODE_DEFAULT,&ScanInfoEx);
	sprintf(s[1][0],"%d",result);

	while (1){
		switch (key){
		case 0xF1:
			prekey = key;
			key = fn_scan();
			break;
		case 0xF2:
			prekey = key;
			key = fn_scanread();
			break;
		case 0xF3:
			prekey = key;
			key = fn_scanwait();
			break;
		case 0xF4:
			result = scanmode(MODE_GET,&ScanInfo);
			sprintf(s[0][1],"%d",result);
			result = scanmode_ex(MODE_GET,&ScanInfoEx);
			sprintf(s[1][1],"%d",result);

//			menuctrl("<<設定>>",MenuMain,sizeof(MenuMain)/sizeof(MENUINFO),0);
			menuctrl("<<設定>>",MenuMain,sizeof(MenuMain)/sizeof(MENUINFO),0,ExitKey_BS);

			result = scanmode(MODE_SET,&ScanInfo);
			sprintf(s[0][2],"%d",result);
			result = scanmode_ex(MODE_SET,&ScanInfoEx);
			sprintf(s[1][2],"%d",result);

			if (KSTATE_F4 == (DBKey & KSTATE_F4)){
				clear_screen();
				dispstr(2,1,"<RETURN VAL CHECK>");
				dispstr(4,1,"<<scanmode>>");
				dispstr(6,1,"GET = ");		dispstr(6,7,s[0][1]);
				dispstr(6,10,"SET = ");		dispstr(6,17,s[0][2]);
				dispstr(8,1,"<<scanmode_ex>>");
				dispstr(10,1,"GET = ");		dispstr(10,7,s[1][1]);
				dispstr(10,10,"SET = ");	dispstr(10,17,s[1][2]);

				 keywait("\x0d");
			}

			key = prekey;
			break;
		}
	}
}
