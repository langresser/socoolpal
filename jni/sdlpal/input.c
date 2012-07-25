//
// Copyright (c) 2009, Wei Mingzhi <whistler_wmz@users.sf.net>.
// Portions Copyright (c) 2009, netwan.
//
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

#include "main.h"
#include <math.h>
#include "SDL_events.h"
#include "hack.h"

PALINPUTSTATE            g_InputState;
#ifdef PAL_HAS_JOYSTICKS
static SDL_Joystick     *g_pJoy = NULL;
#endif
BOOL                     g_fUseJoystick = TRUE;

#if defined(GPH)
#define MIN_DEADZONE -16384
#define MAX_DEADZONE 16384
#endif
int get_dir_by_key(DWORD key)
{
	BOOL isLeftPress = (key & kKeyLeft) != 0;
	BOOL isRightPress = (key & kKeyRight) != 0;
	BOOL isUpPress = (key & kKeyUp) != 0;
	BOOL isDownPress = (key & kKeyDown) != 0;
	int keyNumber = isLeftPress + isRightPress + isUpPress + isDownPress;

	// 只有一个按键，最好办，直接取按键方向
	if (keyNumber == 0) {
		return kDirUnknown;
	} else if (keyNumber == 1) {
		if (isLeftPress) {
			return kDirWest;
		} else if (isRightPress) {
			return kDirEast;
		} else if (isUpPress) {
			return kDirNorth;
		} else if (isDownPress) {
			return kDirSouth;
		} else {
			return kDirUnknown;
		}
	}

	switch (g_InputState.dir) {
	case kDirNorth:
		if (isUpPress) {
			return kDirNorth;
		} else if (isLeftPress) {
			return kDirWest;
		} else if (isRightPress) {
			return kDirEast;
		} else if (isDownPress) {
			return kDirSouth;
		}
		break;
	case kDirSouth:
		if (isDownPress) {
			return kDirSouth;
		} else if (isLeftPress) {
			return kDirWest;
		} else if (isRightPress) {
			return kDirEast;
		} else if (isUpPress) {
			return kDirNorth;
		}
		break;
	case kDirWest:
		if (isLeftPress) {
			return kDirWest;
		} else if (isUpPress) {
			return kDirNorth;
		} else if (isDownPress) {
			return kDirSouth;
		} else if (isRightPress) {
			return kDirEast;
		} 
		break;
	case kDirEast:
		if (isRightPress) {
			return kDirEast;
		} else if (isUpPress) {
			return kDirNorth;
		} else if (isDownPress) {
			return kDirSouth;
		} else if (isLeftPress) {
			return kDirWest;
		}
		break;
	case kDirUnknown:
		return kDirUnknown;
		break;
	}

	return kDirUnknown;
}

VOID
PAL_KeyboardEventFilter(
   const SDL_Event       *lpEvent
)
/*++
  Purpose:

    Handle keyboard events.

  Parameters:

    [IN]  lpEvent - pointer to the event.

  Return value:

    None.

--*/
{
   switch (lpEvent->type)
   {
   case SDL_KEYDOWN:
      //
      // Pressed a key
      //
      if (lpEvent->key.keysym.mod & KMOD_ALT)
      {
         if (lpEvent->key.keysym.sym == SDLK_F4)
         {
            //
            // Pressed Alt+F4 (Exit program)...
            //
            PAL_Shutdown();
            exit(0);
         }
      }

	  LOGI("key down: %d", lpEvent->key.keysym.sym);
      switch (lpEvent->key.keysym.sym)
      {
#ifdef __SYMBIAN32__
      //
      // Symbian-specific stuff
      //
      case SDLK_0:
         VIDEO_ToggleScaleScreen();
         break;
      case SDLK_1:
         SOUND_AdjustVolume(0);
         break;
      case SDLK_3:
         SOUND_AdjustVolume(1);
         break;
#endif
      case SDLK_UP:
	  case SDLK_KP8:
         g_InputState.dir = kDirNorth;
		 g_InputState.dwKeyPress |=kKeyUp;
         g_InputState.dirKeyPress |= kKeyUp;
         break;

      case SDLK_DOWN:
      case SDLK_KP2:
         g_InputState.dir = kDirSouth;
		 g_InputState.dwKeyPress |= kKeyDown;
         g_InputState.dirKeyPress |= kKeyDown;
         break;

      case SDLK_LEFT:
      case SDLK_KP4:
         g_InputState.dir = kDirWest;
		 g_InputState.dwKeyPress |= kKeyLeft;
         g_InputState.dirKeyPress |= kKeyLeft;
         break;

      case SDLK_RIGHT:
      case SDLK_KP6:
         g_InputState.dir = kDirEast;
		 g_InputState.dwKeyPress |= kKeyRight;
         g_InputState.dirKeyPress |= kKeyRight;
         break;

#if defined(DINGOO)
      case SDLK_SPACE:
		 g_InputState.dwKeyPress = kKeyMenu;
         break;

      case SDLK_LCTRL:
		 g_InputState.dwKeyPress = kKeySearch;
         break;
#else
      case SDLK_ESCAPE:
      case SDLK_INSERT:
      case SDLK_LALT:
      case SDLK_RALT:
      case SDLK_KP0:
	  case SDLK_MENU:   // android menu键
         g_InputState.dwKeyPress |= kKeyMenu;
         break;
	  case SDLK_AC_HOME: // android home键(或许这里应该结束程序)
		  break;
      case SDLK_RETURN:
      case SDLK_SPACE:
      case SDLK_KP_ENTER:
      case SDLK_LCTRL:
         g_InputState.dwKeyPress |= kKeySearch;
         break;

      case SDLK_PAGEUP:
      case SDLK_KP9:
         g_InputState.dwKeyPress |= kKeyPgUp;
         break;

      case SDLK_PAGEDOWN:
      case SDLK_KP3:
         g_InputState.dwKeyPress |= kKeyPgDn;
         break;

      case SDLK_7: //7 for mobile device
      case SDLK_r:
         g_InputState.dwKeyPress |= kKeyRepeat;
         break;

      case SDLK_2: //2 for mobile device
      case SDLK_a:
         g_InputState.dwKeyPress |= kKeyAuto;
         break;

      case SDLK_d:
         g_InputState.dwKeyPress |= kKeyDefend;
         break;

      case SDLK_e:
         g_InputState.dwKeyPress |= kKeyUseItem;
         break;

      case SDLK_w:
         g_InputState.dwKeyPress |= kKeyThrowItem;
         break;

      case SDLK_q:
         g_InputState.dwKeyPress |= kKeyFlee;
         break;

      case SDLK_s:
         g_InputState.dwKeyPress |= kKeyStatus;
         break;

      case SDLK_f:
      case SDLK_5: // 5 for mobile device
         g_InputState.dwKeyPress |= kKeyForce;
         break;

      case SDLK_HASH: //# for mobile device
      case SDLK_p:
         VIDEO_SaveScreenshot();
         break;
#endif

      default:
         break;
      }
      break;

   case SDL_KEYUP:
      //
      // Released a key
      //
	   LOGI("key up: %d", lpEvent->key.keysym.sym);
      switch (lpEvent->key.keysym.sym)
      {
      case SDLK_UP:
      case SDLK_KP8:
		  if ((g_InputState.dirKeyPress & kKeyUp) != 0) {
			  g_InputState.dirKeyPress ^= kKeyUp;
		  }
		  
         g_InputState.dir = get_dir_by_key(g_InputState.dirKeyPress);
         break;

      case SDLK_DOWN:
      case SDLK_KP2:
		  if ((g_InputState.dirKeyPress & kKeyDown) != 0) {
			  g_InputState.dirKeyPress ^= kKeyDown;
		  }
         g_InputState.dir = get_dir_by_key(g_InputState.dirKeyPress);
         break;

      case SDLK_LEFT:
      case SDLK_KP4:
		  if ((g_InputState.dirKeyPress & kKeyLeft) != 0) {
			  g_InputState.dirKeyPress ^= kKeyLeft;
		  }
         g_InputState.dir = get_dir_by_key(g_InputState.dirKeyPress);
         break;

      case SDLK_RIGHT:
      case SDLK_KP6:
		  if ((g_InputState.dirKeyPress & kKeyRight) != 0) {
			  g_InputState.dirKeyPress ^= kKeyRight;
		  }
         g_InputState.dir = get_dir_by_key(g_InputState.dirKeyPress);
         break;

      default:
         break;
      }
      break;
   }
}


int GetInputDir(int mouseX, int mouseY)
{
	int nScrW = 320;
	int nScrH = 200;
    
	// 目前来看人物似乎总是在屏幕中心，即使走到地图边上;
	int nHeroX = nScrW / 2;
	int nHeroY = nScrH / 2;
    
	int nDeltaX = mouseX - nHeroX;
	int nDeltaY = nHeroY - mouseY;
    
    if (nDeltaY >= 0 && nDeltaX >= 0) {
        return kDirNorth;
    } else if (nDeltaY >= 0 && nDeltaX < 0) {
        return kDirWest;
    } else if (nDeltaY < 0 && nDeltaX >= 0) {
        return kDirEast;
    } else if (nDeltaY < 0 && nDeltaX < 0) {
        return kDirSouth;
    }
    
    return kDirUnknown;
}

int GetMouseMoveDir(int nMouseX, int nMouseY)
{
	// why use initial ? Maybe fix later 
	int nScrW = 320;
	int nScrH = 200;

	// 目前来看人物似乎总是在屏幕中心，即使走到地图边上;
	int nHeroX = nScrW / 2;
	int nHeroY = nScrH / 2;

	int nDeltaX = nMouseX - nHeroX;
	int nDeltaY = nHeroY - nMouseY;

	int nAbsDeltaX = abs(nDeltaX);
	int nAbsDeltaY = abs(nDeltaY);

	int nDir = eMoveDirUnknown;

	if (nDeltaX > 0) {
		if (nDeltaY > 0) {
			// 第一象限,N;
			if (nAbsDeltaX > nAbsDeltaY) {
				nDir = eMoveDirNE;
			} else if (nAbsDeltaX == nAbsDeltaY) {
				nDir = eMoveDirNorth;
			} else {
				nDir = eMoveDirNW;
			}
		} else {
			// 第四象限,E;
			if (nAbsDeltaX > nAbsDeltaY) {
				nDir = eMoveDirEN;
			} else if (nAbsDeltaX == nAbsDeltaY) {
				nDir = eMoveDirEast;
			} else {
				nDir = eMoveDirES;
			}
		}
	} else {
		if (nDeltaY > 0) {
			// 第二象限,W;
			if (nAbsDeltaX > nAbsDeltaY) {
				nDir = eMoveDirWS;
			} else if (nAbsDeltaX == nAbsDeltaY) {
				nDir = eMoveDirWest;
			} else {
				nDir = eMoveDirWN;
			}
		} else {
			// 第三象限,S;
			if (nAbsDeltaX > nAbsDeltaY) {
				nDir = eMoveDirSW;
			} else if (nAbsDeltaX == nAbsDeltaY) {
				nDir = eMoveDirSouth;
			} else {
				nDir = eMoveDirSE;
			}
		}
	}

	return nDir;
}

VOID
PAL_MouseEventFilter(
   const SDL_Event *lpEvent
)
/*++
  Purpose:

    Handle mouse events.

  Parameters:

    [IN]  lpEvent - pointer to the event.

  Return value:

    None.

--*/
{
#ifdef PAL_HAS_MOUSE
   static short hitTest = 0; // Double click detect;

   double       screenWidth, gridWidth;
   double       screenHeight, gridHeight;
   double       mx, my;
   double       thumbx;
   double       thumby;
   INT          gridIndex;
   static INT   lastReleaseButtonTime, lastPressButtonTime;
   static INT   lastPressx = 0;
   static INT   lastPressy = 0;
   static INT   lastReleasex = 0;
   static INT   lastReleasey = 0;
   static INT   lastMotionX = 0;
   static INT   lastMotionY = 0;
   int mouseX, mouseY;
   int eventType;
#ifdef __ANDROID__
   eventType = lpEvent->tfinger.type;
    if (lpEvent->tfinger.type!= SDL_FINGERDOWN && lpEvent->tfinger.type != SDL_FINGERUP
	   && lpEvent->tfinger.type != SDL_FINGERMOTION)
      return;
#else
    eventType = lpEvent->tfinger.type;
   if (lpEvent->type!= SDL_MOUSEBUTTONDOWN && lpEvent->type != SDL_MOUSEBUTTONUP
	   && lpEvent->type != SDL_MOUSEMOTION)
      return;
#endif
   screenWidth = g_wInitialWidth;
   screenHeight = g_wInitialHeight;
   gridWidth = screenWidth / 3;
   gridHeight = screenHeight / 3;

#ifdef __ANDROID__
   mx = lpEvent->tfinger.x;
   my = lpEvent->tfinger.y;
   mouseX = lpEvent->tfinger.x;
   mouseY = lpEvent->tfinger.y;
#else
   mx = lpEvent->button.x;
   my = lpEvent->button.y;
   mouseX = lpEvent->button.x;
   mouseY = lpEvent->button.y;
#endif

   thumbx = ceil(mx / gridWidth);
   thumby = floor(my / gridHeight);
   gridIndex = thumbx + thumby * 3 - 1;
  
   // 斜45度，人他妈是斜着走的
/*
0   1   2
3   4   5
6   7   8
*/

   g_InputState.controlType = CONTROL_TYPE_NONE;

   switch (eventType)
   {
#ifdef __ANDROID__
       case SDL_FINGERDOWN:
#else
   case SDL_MOUSEBUTTONDOWN:
#endif
   LOGI("SDL_FINGERDOWN: %d  %d  %d     %d  %d", eventType, mouseX,  mouseY, g_wInitialWidth, g_wInitialHeight);
      lastPressButtonTime = SDL_GetTicks();

      lastPressx = mouseX;
      lastPressy = mouseY;

	  g_InputState.touchEventType = TOUCH_DOWN;
	  g_InputState.touchX = mouseX * 320.0 / g_wInitialWidth;
	  g_InputState.touchY = mouseY * 200.0 / g_wInitialHeight;
      
       g_InputState.controlType = CONTROL_TYPE_MOUSE_WALK;
       g_InputState.nMoveDir = GetMouseMoveDir(g_InputState.touchX, g_InputState.touchY);
           	  
	  switch (gridIndex)
	  {
	  case 2:
		  g_InputState.dir = kDirNorth;
		  break;
	  case 6:
		  g_InputState.dir = kDirSouth;
		  break;
	  case 0:
		  g_InputState.dir = kDirWest;
		  break;
	  case 8:
		  g_InputState.dir = kDirEast;
		  break;
	  case 1:
		  g_InputState.dir = kDirNorth;
		  break;
	  case 7:
		  g_InputState.dir = kDirSouth; 
		  break;
	  case 3:
		  g_InputState.dir = kDirWest;
		  break;
	  case 5:
		  g_InputState.dir = kDirEast;
		  break;
       case 4:
              g_InputState.dir = GetInputDir(g_InputState.touchX, g_InputState.touchY);
        break;
	  }
      break;
#ifdef __ANDROID__
       case SDL_FINGERMOTION:
#else
   case SDL_MOUSEMOTION:
	   if (lpEvent->motion.state == 0) {
		   break;
	   }
#endif
       if (mouseX == lastMotionX && mouseY == lastMotionY) {
           break;
       }
  LOGI("SDL_MOUSEMOTION: %d  %d  %d     %d  %d", eventType, mouseX,  mouseY, g_wInitialWidth, g_wInitialHeight);
    lastMotionX = mouseX;
       lastMotionY = mouseY;

       g_InputState.controlType = CONTROL_TYPE_MOUSE_WALK;
       g_InputState.nMoveDir = GetMouseMoveDir(mouseX * 320.0 / g_wInitialWidth, mouseY * 200.0 / g_wInitialHeight);

	  switch (gridIndex)
	  {
	  case 2:
		  g_InputState.dir = kDirNorth;
		  break;
	  case 6:
		  g_InputState.dir = kDirSouth;
		  break;
	  case 0:
		  g_InputState.dir = kDirWest;
		  break;
	  case 8:
		  g_InputState.dir = kDirEast;
		  break;
	  case 1:
		  g_InputState.dir = kDirNorth;
		  break;
	  case 7:
		  g_InputState.dir = kDirSouth; 
		  break;
	  case 3:
		  g_InputState.dir = kDirWest;
		  break;
	  case 5:
		  g_InputState.dir = kDirEast;
		  break;
          case 4:
              g_InputState.dir = GetInputDir(g_InputState.touchX, g_InputState.touchY);
	  }
	   break;
#ifdef __ANDROID__
       case SDL_FINGERUP:
#else
   case SDL_MOUSEBUTTONUP:
#endif
      LOGI("SDL_FINGERUP: %d  %d  %d     %d  %d", eventType, mouseX,  mouseY, g_wInitialWidth, g_wInitialHeight);
       lastReleaseButtonTime = SDL_GetTicks();
      lastReleasex = mouseX;
      lastReleasey = mouseY;
      hitTest ++;

	  if (lastReleaseButtonTime - lastPressButtonTime <= 1000) {
		g_InputState.touchEventType = TOUCH_UP;
		g_InputState.touchX = mouseX * 320.0 / g_wInitialWidth;
		g_InputState.touchY = mouseY * 200.0 / g_wInitialHeight;
	  } else {
		g_InputState.touchEventType = TOUCH_NONE;
	  }
           
       if (gridIndex == 4) {
           if (abs(lastReleasex - lastPressx) <= 25
               && abs(lastReleasey - lastPressy) <= 25) {
               if (lastReleaseButtonTime - lastPressButtonTime <= 500) {
                   g_InputState.dwKeyPress |= kKeyMainSearch;
               }
           }
       }
               

	  g_InputState.dir = kDirUnknown;
	  g_InputState.nMoveDir = eMoveDirUnknown;
      break;
   }
#endif
}

VOID
PAL_JoystickEventFilter(
   const SDL_Event       *lpEvent
)
/*++
  Purpose:

    Handle joystick events.

  Parameters:

    [IN]  lpEvent - pointer to the event.

  Return value:

    None.

--*/
{
#ifdef PAL_HAS_JOYSTICKS
   switch (lpEvent->type)
   {
#if defined (GEKKO)
   case SDL_JOYHATMOTION:
      switch (lpEvent->jhat.value)
      {
      case SDL_HAT_LEFT:
        g_InputState.dir = kDirWest;
        g_InputState.dwKeyPress = kKeyLeft;
        break;

      case SDL_HAT_RIGHT:
        g_InputState.dir = kDirEast;
        g_InputState.dwKeyPress = kKeyRight;
        break;

      case SDL_HAT_UP:
        g_InputState.dir = kDirNorth;
        g_InputState.dwKeyPress = kKeyUp;
        break;

	  case SDL_HAT_DOWN:
        g_InputState.dir = kDirSouth;
        g_InputState.dwKeyPress = kKeyDown;
        break;
      }
      break;
#else
   case SDL_JOYAXISMOTION:
      //
      // Moved an axis on joystick
      //
      switch (lpEvent->jaxis.axis)
      {
      case 0:
         //
         // X axis
         //
#if defined(GPH)
		if (lpEvent->jaxis.value > MAX_DEADZONE) {
			g_InputState.dir = kDirEast;
			g_InputState.dwKeyPress = kKeyRight;
		} else if (lpEvent->jaxis.value < MIN_DEADZONE) {
			g_InputState.dir = kDirWest;
			g_InputState.dwKeyPress = kKeyLeft;
		} else {
			g_InputState.dir = kDirUnknown;
		}
#else
         if (lpEvent->jaxis.value > 20000)
         {
            if (g_InputState.dir != kDirEast)
            {
               g_InputState.dwKeyPress |= kKeyRight;
            }
            g_InputState.dir = kDirEast;
         }
         else if (lpEvent->jaxis.value < -20000)
         {
            if (g_InputState.dir != kDirWest)
            {
               g_InputState.dwKeyPress |= kKeyLeft;
            }
            g_InputState.dir = kDirWest;
         }
         else
         {
            g_InputState.dir = kDirUnknown;
         }
#endif
         break;

      case 1:
         //
         // Y axis
         //
#if defined(GPH)
		if (lpEvent->jaxis.value > MAX_DEADZONE) {
			g_InputState.prevdir = (gpGlobals->fInBattle ? kDirUnknown : g_InputState.dir);
			g_InputState.dir = kDirSouth;
			g_InputState.dwKeyPress = kKeyDown;
		} else if (lpEvent->jaxis.value < MIN_DEADZONE) {
			g_InputState.prevdir = (gpGlobals->fInBattle ? kDirUnknown : g_InputState.dir);
			g_InputState.dir = kDirNorth;
			g_InputState.dwKeyPress = kKeyUp;
		} else {
			g_InputState.dir = kDirUnknown;
		}
#else
         if (lpEvent->jaxis.value > 20000)
         {
            if (g_InputState.dir != kDirSouth)
            {
               g_InputState.dwKeyPress |= kKeyDown;
            }
            g_InputState.dir = kDirSouth;
         }
         else if (lpEvent->jaxis.value < -20000)
         {
            if (g_InputState.dir != kDirNorth)
            {
               g_InputState.dwKeyPress |= kKeyUp;
            }
            g_InputState.dir = kDirNorth;
         }
         else
         {
            g_InputState.dir = kDirUnknown;
         }
#endif
         break;
      }
      break;
#endif

   case SDL_JOYBUTTONDOWN:
      //
      // Pressed the joystick button
      //
#if defined(GPH)
      switch (lpEvent->jbutton.button)
      {
#if defined(GP2XWIZ)
		case 14:
#elif defined(CAANOO)
		case 3:
#endif
			g_InputState.dwKeyPress = kKeyMenu;
			break;

#if defined(GP2XWIZ)
		case 13:
#elif defined(CAANOO)
		case 2:
#endif
			g_InputState.dwKeyPress = kKeySearch;
			break;
#else
#if defined(GEKKO)
      switch (lpEvent->jbutton.button)
      {
		case 2:
         g_InputState.dwKeyPress |= kKeyMenu;
         break;

		case 3:
         g_InputState.dwKeyPress |= kKeySearch;
         break;
#else
      switch (lpEvent->jbutton.button & 1)
      {
      case 0:
         g_InputState.dwKeyPress |= kKeyMenu;
         break;

      case 1:
         g_InputState.dwKeyPress |= kKeySearch;
         break;
#endif
#endif
      }
      break;
   }
#endif
}

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION <= 2
static int SDLCALL
PAL_EventFilter(
   const SDL_Event       *lpEvent
)
#else
int PAL_EventFilter(
   void                  *userdata,
   const SDL_Event       *lpEvent
)
#endif
/*++
  Purpose:

    SDL event filter function. A filter to process all events.

  Parameters:

    [IN]  lpEvent - pointer to the event.

  Return value:

    1 = the event will be added to the internal queue.
    0 = the event will be dropped from the queue.

--*/
{
   switch (lpEvent->type)
   {
   case SDL_WINDOWEVENT:
	   if (lpEvent->window.event == SDL_WINDOWEVENT_RESIZED) {
// 		   VIDEO_Resize(lpEvent->window.data1, lpEvent->window.data2);
// 		   g_wInitialWidth = lpEvent->window.data1;
// 		   g_wInitialHeight = lpEvent->window.data2;
// 		   LOGI("SDL_WINDOWEVENT_RESIZED: %d  %d", g_wInitialWidth, g_wInitialHeight);
	   }
      break;

   case SDL_QUIT:
      //
      // clicked on the close button of the window. Quit immediately.
      //
      PAL_Shutdown();
      exit(0);
	  break;
   }

   PAL_KeyboardEventFilter(lpEvent);
   PAL_MouseEventFilter(lpEvent);
   PAL_JoystickEventFilter(lpEvent);

   //
   // All events are handled here; don't put anything to the internal queue
   //
   return 0;
}

VOID
PAL_ClearKeyState(
   VOID
)
/*++
  Purpose:

    Clear the record of pressed keys.

  Parameters:

    None.

  Return value:

    None.

--*/
{   
   g_InputState.dwKeyPress = 0;
    g_InputState.touchEventType = TOUCH_NONE;   
}

VOID
PAL_InitInput(
   VOID
)
/*++
  Purpose:

    Initialize the input subsystem.

  Parameters:

    None.

  Return value:

    None.

--*/
{
   memset(&g_InputState, 0, sizeof(g_InputState));
   g_InputState.dir = kDirUnknown;

#ifndef __ANDROID__
   SDL_SetEventFilter(PAL_EventFilter, NULL);
#endif

   //
   // Check for joystick
   //
#ifdef PAL_HAS_JOYSTICKS
   if (SDL_NumJoysticks() > 0 && g_fUseJoystick)
   {
      g_pJoy = SDL_JoystickOpen(0);
      if (g_pJoy != NULL)
      {
         SDL_JoystickEventState(SDL_ENABLE);
      }
   }
#endif
}

VOID
PAL_ShutdownInput(
   VOID
)
/*++
  Purpose:

    Shutdown the input subsystem.

  Parameters:

    None.

  Return value:

    None.

--*/
{
#ifdef PAL_HAS_JOYSTICKS
   if (SDL_JoystickOpened(0))
   {
      assert(g_pJoy != NULL);
      SDL_JoystickClose(g_pJoy);
      g_pJoy = NULL;
   }
#endif
}

VOID
PAL_ProcessEvent(
   VOID
)
/*++
  Purpose:

    Process all events.

  Parameters:

    None.

  Return value:

    None.

--*/
{
#ifdef __ANDROID__
	SDL_Event evt;
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
			case SDL_WINDOWEVENT:
			   if (evt.window.event == SDL_WINDOWEVENT_RESIZED) {
		// 		   VIDEO_Resize(lpEvent->window.data1, lpEvent->window.data2);
		// 		   g_wInitialWidth = lpEvent->window.data1;
		// 		   g_wInitialHeight = lpEvent->window.data2;
		// 		   LOGI("SDL_WINDOWEVENT_RESIZED: %d  %d", g_wInitialWidth, g_wInitialHeight);
			   } else if (evt.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
				   extern BOOL g_hasInGame;
				   LOGI("in SDL_WINDOWEVENT_FOCUS_LOST");
				   g_isInBackground = SDL_TRUE;

				   if (g_hasInGame) {
					  PAL_SaveGame("9.rpg", 0);
				   }
			   } else if (evt.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
				   LOGI("in SDL_WINDOWEVENT_FOCUS_GAINED");
				   g_isInBackground = SDL_FALSE;
				   VIDEO_Resize(g_wInitialWidth, g_wInitialHeight);
			   }
			  break;

			case SDL_QUIT:
			  //
			  // clicked on the close button of the window. Quit immediately.
			  //
			  PAL_Shutdown();
			  exit(0);
			  break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				PAL_KeyboardEventFilter(&evt);
				return;
			  break;
			case SDL_FINGERDOWN:
			case SDL_FINGERUP:
				PAL_MouseEventFilter(&evt);
				return;
				break;
			case SDL_FINGERMOTION:
				PAL_MouseEventFilter(&evt);
				break;
			case SDL_JOYBUTTONDOWN:
			case SDL_JOYBUTTONUP:
				PAL_JoystickEventFilter(&evt);
				return;
				break;
			case SDL_JOYAXISMOTION:
			case SDL_JOYBALLMOTION:
			case SDL_JOYHATMOTION:
				PAL_JoystickEventFilter(&evt);
				break;
		}

   }
#else
#ifdef PAL_HAS_NATIVEMIDI
   MIDI_CheckLoop();
#endif
   while (SDL_PollEvent(NULL));
#endif
}

BOOL PAL_IsTouch(int x, int y, int w, int h)
{
//	LOGI("is touch: %d %d %d %d %d %d", x, y, w, h, g_InputState.touchX, g_InputState.touchY);
	if (g_InputState.touchEventType == TOUCH_NONE) {
		return FALSE;
	}

//	LOGI("yes is touch: %d %d %d %d %d %d", x, y, w, h, g_InputState.touchX, g_InputState.touchY);
	if (g_InputState.touchX >= x && g_InputState.touchX <= x + w
		&& g_InputState.touchY >= y && g_InputState.touchY <= y + h) {
//			LOGI("yes is touch in: %d %d %d %d %d %d", x, y, w, h, g_InputState.touchX, g_InputState.touchY);
			return TRUE;
	}

	return FALSE;
}

BOOL PAL_IsTouchDown(int x, int y, int w, int h)
{
	if (g_InputState.touchEventType != TOUCH_DOWN) {
		return FALSE;
	}

	if (g_InputState.touchX >= x && g_InputState.touchX <= x + w
		&& g_InputState.touchY >= y && g_InputState.touchY <= y + h) {
			return TRUE;
	}

	return FALSE;
}

BOOL PAL_IsTouchUp(int x, int y, int w, int h)
{
	if (g_InputState.touchEventType != TOUCH_UP) {
		return FALSE;
	}

	if (g_InputState.touchX >= x && g_InputState.touchX <= x + w
		&& g_InputState.touchY >= y && g_InputState.touchY <= y + h) {
			return TRUE;
	}

	return FALSE;
}
