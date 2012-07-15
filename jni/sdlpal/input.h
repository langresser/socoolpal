//
// Copyright (c) 2009, Wei Mingzhi <whistler_wmz@users.sf.net>.
// All rights reserved.
//
// This file is part of SDLPAL.
//
// SDLPAL is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "palcommon.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define TOUCH_NONE 0
#define TOUCH_DOWN 1
#define TOUCH_UP	2

#define GAME_MODE_OPEN 0
#define GAME_MODE_MAIN 1
#define GAME_MODE_BATTLE 2
#define GAME_MODE_MENU 3

typedef enum CONTROL_TYPE
{
	CONTROL_TYPE_NONE,
	CONTROL_TYPE_MOUSE_WALK,
};

typedef struct tagPALINPUTSTATE
{
   PALDIRECTION           dir;
   DWORD				  dirKeyPress;
   DWORD                  dwKeyPress;
   int					  touchEventType;
   DWORD					touchX;
   DWORD					touchY;
   int					gameMode;
   int nMoveDir;
   int controlType;
} PALINPUTSTATE;

extern PALINPUTSTATE g_InputState;

enum PALKEY
{
   kKeyMenu        = (1 << 0),
   kKeySearch      = (1 << 1),
   kKeyDown        = (1 << 2),
   kKeyLeft        = (1 << 3),
   kKeyUp          = (1 << 4),
   kKeyRight       = (1 << 5),
   kKeyPgUp        = (1 << 6),
   kKeyPgDn        = (1 << 7),
   kKeyRepeat      = (1 << 8),
   kKeyAuto        = (1 << 9),
   kKeyDefend      = (1 << 10),
   kKeyUseItem     = (1 << 11),
   kKeyThrowItem   = (1 << 12),
   kKeyFlee        = (1 << 13),
   kKeyStatus      = (1 << 14),
   kKeyForce       = (1 << 15),
   kKeyMainMenu		= (1 << 16),
   kKeyMainSearch	= (1 << 17),
};

VOID
PAL_ClearKeyState(
   VOID
);

VOID
PAL_InitInput(
   VOID
);

VOID
PAL_ProcessEvent(
   VOID
);

VOID
PAL_ShutdownInput(
   VOID
);

BOOL PAL_IsTouch(int x, int y, int w, int h);
BOOL PAL_IsTouchDown(int x, int y, int w, int h);
BOOL PAL_IsTouchUp(int x, int y, int w, int h);

extern BOOL g_fUseJoystick;

#ifdef __cplusplus
}
#endif

#endif
