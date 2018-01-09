#pragma once

extern	HWND g_hWnd;
extern float	g_fLoadingCnt;
extern int		g_iRoomMobCnt1;
extern int		g_iRoomMobCnt2;
extern int		g_iRoomMobCnt3;
extern int		g_iRoomMobCnt4;
extern int		g_iRoomMobCntBoss;

extern int		g_iBossTotalHp;

extern bool		g_DoubleShot;
extern bool		g_bTripleShot;
extern bool		g_bQurdShot;
extern bool		g_bGuideMode;
extern bool		g_bEpicFetus;



const int WINCX = 1024;
const int WINCY = 768;

const WORD	MIN_STR		= 64;
const WORD	MIDDLE_STR	= 128;
const WORD	MAX_STR		= 256;

// ≈∏¿œ

const int	TILECX = 68;
const int	TILECY = 68;

const int	TILEX = 101;
const int	TILEY = 22;

const DWORD		KEY_LBUTTON = 0x00000001;
const DWORD		KEY_ENTER	= 0x00000002;
const DWORD		KEY_UP		= 0x00000004;
const DWORD		KEY_DOWN	= 0x00000008;
const DWORD		KEY_LEFT	= 0x00000010;
const DWORD		KEY_RIGHT	= 0x00000020;
const DWORD		KEY_W		= 0x00000040;
const DWORD		KEY_S		= 0x00000080;
const DWORD		KEY_A		= 0x00000100;
const DWORD		KEY_D		= 0x00000200;
const DWORD		KEY_CTRL	= 0x00000400;
const DWORD		KEY_Q		= 0x00000800;
const DWORD		KEY_SPACE	= 0x00001000;
const DWORD		KEY_1	= 0x00002000;
const DWORD		KEY_2	= 0x00004000;
const DWORD		KEY_3	= 0x00008000;
const DWORD		KEY_4	= 0x00010000;