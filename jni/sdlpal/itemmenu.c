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

#include "main.h"

static int     g_iNumInventory = 0;
static WORD    g_wItemFlags = 0;
static BOOL    g_fNoDesc = FALSE;
static int     g_iCurMenuItem = 0;
static int     g_currentSelectItem = 0;

#define PAGE_ITEM_AMOUNT 18

WORD
PAL_ItemSelectMenuUpdate(
   VOID
)
/*++
  Purpose:

    Initialize the item selection menu.

  Parameters:

    None.

  Return value:

    The object ID of the selected item. 0 if cancelled, 0xFFFF if not confirmed.

--*/
{
   int                i, j, k;
   WORD               wObject;
   BYTE               bColor;
   static BYTE        bufImage[2048];
   static WORD        wPrevImageIndex = 0xFFFF;
   SDL_Rect     mainBox;
   SDL_Rect   upPage, downPage;
   int currentPage, pageAmount;
    
#ifdef DEBUG
    if (g_InputState.touchEventType == TOUCH_UP) {
        printf("in item:\n");
    }
#endif

   //
   // Process input
   //
   if (g_InputState.dwKeyPress & kKeyUp)
   {
      g_iCurMenuItem -= 3;
	  g_currentSelectItem = g_iCurMenuItem;
   }
   else if (g_InputState.dwKeyPress & kKeyDown)
   {
	  g_iCurMenuItem += 3;
	  g_currentSelectItem = g_iCurMenuItem;
   }
   else if (g_InputState.dwKeyPress & kKeyLeft)
   {
	   g_iCurMenuItem--;
	   g_currentSelectItem = g_iCurMenuItem;
   }
   else if (g_InputState.dwKeyPress & kKeyRight)
   {
	   g_iCurMenuItem++;
	   g_currentSelectItem = g_iCurMenuItem;
   }
   else if (g_InputState.dwKeyPress & kKeyPgUp)
   {
	   g_iCurMenuItem -= PAGE_ITEM_AMOUNT;
	   g_currentSelectItem = g_iCurMenuItem;
   }
   else if (g_InputState.dwKeyPress & kKeyPgDn)
   {
	   g_iCurMenuItem += PAGE_ITEM_AMOUNT;
	   g_currentSelectItem = g_iCurMenuItem;
   }
   else if (g_InputState.dwKeyPress & kKeyMenu)
   {
      return 0;
   }

   //
   // Make sure the current menu item index is in bound
   //
   if (g_iCurMenuItem < 0)
   {
      g_iCurMenuItem = 0;
   }
   else if (g_iCurMenuItem >= g_iNumInventory)
   {
      g_iCurMenuItem = g_iNumInventory - 1;
   }

   if (g_currentSelectItem < 0) {
	   g_currentSelectItem = 0;
   }

   if (g_currentSelectItem >= g_iNumInventory) {
	   g_currentSelectItem = g_iNumInventory - 1;
   }

   //
   // Redraw the box
   //
   PAL_CreateBox(PAL_XY(2, 0), 6, 17, 1, FALSE, &mainBox);
   
   upPage.x = 20;
   upPage.y = 120;
   upPage.w = 50;
   upPage.h = 30;
   downPage.x = 260;
   downPage.y = 120;
   downPage.w = 50;
   downPage.h = 30;

   currentPage = g_iCurMenuItem / PAGE_ITEM_AMOUNT;
   pageAmount = g_iNumInventory / PAGE_ITEM_AMOUNT + (g_iNumInventory % PAGE_ITEM_AMOUNT == 0 ? 0 : 1);

   if (currentPage > 0) {
	   PAL_CreateSingleLineBox(PAL_XY(upPage.x, upPage.y), 2, FALSE);
	   PAL_DrawText(PAL_GetWord(LABEL_PAGE_UP), PAL_XY(upPage.x + 5, upPage.y + 10), MENUITEM_COLOR_CONFIRMED, FALSE, FALSE);
   }

   if (currentPage < pageAmount - 1) {
	   PAL_CreateSingleLineBox(PAL_XY(downPage.x, downPage.y), 2, FALSE);
	   PAL_DrawText(PAL_GetWord(LABEL_PAGE_DOWN), PAL_XY(downPage.x + 5, downPage.y + 10), MENUITEM_COLOR_CONFIRMED, FALSE, FALSE);
   }

   //
   // Draw the texts in the current page
   //
   i = g_iCurMenuItem / PAGE_ITEM_AMOUNT * PAGE_ITEM_AMOUNT;
   if (i < 0)
   {
      i = 0;
   }

   for (j = 0; j < 6; j++)
   {
      for (k = 0; k < 3; k++)
      {
         wObject = gpGlobals->rgInventory[i].wItem;
         bColor = MENUITEM_COLOR;

         if (i >= MAX_INVENTORY || wObject == 0)
         {
            //
            // End of the list reached
            //
            j = 6;
            break;
         }

         if (i == g_iCurMenuItem)
         {
            if (!(gpGlobals->g.rgObject[wObject].item.wFlags & g_wItemFlags) ||
               (SHORT)gpGlobals->rgInventory[i].nAmount <= (SHORT)gpGlobals->rgInventory[i].nAmountInUse)
            {
               //
               // This item is not selectable
               //
               bColor = MENUITEM_COLOR_SELECTED_INACTIVE;
            }
            else
            {
               //
               // This item is selectable
               //
               if (gpGlobals->rgInventory[i].nAmount == 0)
               {
                  bColor = MENUITEM_COLOR_EQUIPPEDITEM;
               }
               else
               {
                  bColor = MENUITEM_COLOR_SELECTED;
               }
            }
         }
         else if (!(gpGlobals->g.rgObject[wObject].item.wFlags & g_wItemFlags) ||
            (SHORT)gpGlobals->rgInventory[i].nAmount <= (SHORT)gpGlobals->rgInventory[i].nAmountInUse)
         {
            //
            // This item is not selectable
            //
            bColor = MENUITEM_COLOR_INACTIVE;
         }
         else if (gpGlobals->rgInventory[i].nAmount == 0)
         {
            bColor = MENUITEM_COLOR_EQUIPPEDITEM;
         }

         //
         // Draw the text
         //
         PAL_DrawText(PAL_GetWord(wObject), PAL_XY(15 + k * 100, 12 + j * 18),
            bColor, TRUE, FALSE);

         //
         // Draw the cursor on the current selected item
         //
         if (i == g_iCurMenuItem)
         {
            PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_CURSOR),
               gpScreen, PAL_XY(40 + k * 100, 22 + j * 18));
         }

         //
         // Draw the amount of this item
         //
		 if ((SHORT)gpGlobals->rgInventory[i].nAmount - (SHORT)gpGlobals->rgInventory[i].nAmountInUse > 1)
		 {
            PAL_DrawNumber(gpGlobals->rgInventory[i].nAmount - gpGlobals->rgInventory[i].nAmountInUse,
               2, PAL_XY(96 + k * 100, 17 + j * 18), kNumColorCyan, kNumAlignRight);
		 }

         i++;
      }
   }

   //
   // Draw the picture of current selected item
   //
   PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_ITEMBOX), gpScreen,
      PAL_XY(5, 140));

   wObject = gpGlobals->rgInventory[g_iCurMenuItem].wItem;

   if (gpGlobals->g.rgObject[wObject].item.wBitmap != wPrevImageIndex)
   {
      if (PAL_MKFReadChunk(bufImage, 2048,
         gpGlobals->g.rgObject[wObject].item.wBitmap, gpGlobals->f.fpBALL) > 0)
      {
         wPrevImageIndex = gpGlobals->g.rgObject[wObject].item.wBitmap;
      }
      else
      {
         wPrevImageIndex = 0xFFFF;
      }
   }

   if (wPrevImageIndex != 0xFFFF)
   {
      PAL_RLEBlitToSurface(bufImage, gpScreen, PAL_XY(12, 148));
   }

   //
   // Draw the description of the selected item
   //
   if (!g_fNoDesc && gpGlobals->lpObjectDesc != NULL)
   {
      char szDesc[512], *next;
      const char *d = PAL_GetObjectDesc(gpGlobals->lpObjectDesc, wObject);

      if (d != NULL)
      {
         k = 150;
         strcpy(szDesc, d);
         d = szDesc;

         while (TRUE)
         {
            next = strchr(d, '*');
            if (next != NULL)
            {
               *next = '\0';
               next++;
            }

            PAL_DrawText(d, PAL_XY(75, k), DESCTEXT_COLOR, TRUE, FALSE);
            k += 16;

            if (next == NULL)
            {
               break;
            }

            d = next;
         }
      }
   }

	if (g_InputState.touchEventType == TOUCH_DOWN) {
	   i = g_iCurMenuItem / PAGE_ITEM_AMOUNT * PAGE_ITEM_AMOUNT;
	   if (i < 0) {
		   i = 0;
	   }

	   for (j = 0; j < 6; j++)
	   {
		   for (k = 0; k < 3; k++)
		   {
			   if (i >= g_iNumInventory) {
				   j = 6;
				   break;
			   }

			   wObject = gpGlobals->rgInventory[i].wItem;
			   if (!wObject) {
				   j = 6;
				   break;
			   }

			   if (PAL_IsTouch(15 + k * 100, 12 + j * 18, 100, 18)) {
				   g_iCurMenuItem = i;
				   wObject = gpGlobals->rgInventory[g_iCurMenuItem].wItem;
			   }

			   ++i;
		   }
	   }
#ifdef DEBUG
        printf("item touch down: %d  %d\n", g_InputState.touchX, g_InputState.touchY);
#endif
   } else if (g_InputState.touchEventType == TOUCH_UP) {
	   i = g_iCurMenuItem % PAGE_ITEM_AMOUNT;

	   j = i / 3;
       k = i % 3;
#ifdef DEBUG
       printf("item touch up: %d  %d\n", g_InputState.touchX, g_InputState.touchY);
#endif
	   if (PAL_IsTouch(15 + k * 100, 12 + j * 18, 100, 18)) {
		   if (g_currentSelectItem != g_iCurMenuItem) {
			   g_currentSelectItem = g_iCurMenuItem;
		   } else {
			   if ((gpGlobals->g.rgObject[wObject].item.wFlags & g_wItemFlags) &&
				(SHORT)gpGlobals->rgInventory[g_iCurMenuItem].nAmount >
				(SHORT)gpGlobals->rgInventory[g_iCurMenuItem].nAmountInUse)
				  {
					 return wObject;
				  }
		   }
	   } else if (currentPage > 0 && PAL_IsTouch(upPage.x, upPage.y, upPage.w, upPage.h)) {
		   g_iCurMenuItem -= PAGE_ITEM_AMOUNT;
		   if (g_iCurMenuItem < 0) {
			   g_iCurMenuItem = 0;
		   }
		   g_currentSelectItem = g_iCurMenuItem;
	   } else if (currentPage < pageAmount - 1 && PAL_IsTouch(downPage.x, downPage.y, downPage.w, downPage.h)) {
		   g_iCurMenuItem += PAGE_ITEM_AMOUNT;
		   if (g_iCurMenuItem >= g_iNumInventory) {
			   g_iCurMenuItem = g_iNumInventory - 1;
		   }
		   g_currentSelectItem = g_iCurMenuItem;
	   } else if (!PAL_IsTouch(mainBox.x, mainBox.y, mainBox.w, mainBox.h)) {
		   return 0;
	   }
   }

   if (g_InputState.dwKeyPress & kKeySearch)
   {
      if ((gpGlobals->g.rgObject[wObject].item.wFlags & g_wItemFlags) &&
         (SHORT)gpGlobals->rgInventory[g_iCurMenuItem].nAmount >
         (SHORT)gpGlobals->rgInventory[g_iCurMenuItem].nAmountInUse)
      {
         if (gpGlobals->rgInventory[g_iCurMenuItem].nAmount > 0)
         {
            j = (g_iCurMenuItem % PAGE_ITEM_AMOUNT) / 3;
            k = g_iCurMenuItem % 3;

            PAL_DrawText(PAL_GetWord(wObject), PAL_XY(15 + k * 100, 12 + j * 18),
               MENUITEM_COLOR_CONFIRMED, FALSE, FALSE);
         }

         return wObject;
      }
   }

   return 0xFFFF;
}

VOID
PAL_ItemSelectMenuInit(
   WORD                      wItemFlags
)
/*++
  Purpose:

    Initialize the item selection menu.

  Parameters:

    [IN]  wItemFlags - flags for usable item.

  Return value:

    None.

--*/
{
   int           i, j;
   WORD          w;

   g_wItemFlags = wItemFlags;

   //
   // Compress the inventory
   //
   PAL_CompressInventory();

   //
   // Count the total number of items in inventory
   //
   g_iNumInventory = 0;
   while (g_iNumInventory < MAX_INVENTORY &&
      gpGlobals->rgInventory[g_iNumInventory].wItem != 0)
   {
      g_iNumInventory++;
   }

   //
   // Also add usable equipped items to the list
   //
   if ((wItemFlags & kItemFlagUsable) && !gpGlobals->fInBattle)
   {
      for (i = 0; i <= gpGlobals->wMaxPartyMemberIndex; i++)
      {
         w = gpGlobals->rgParty[i].wPlayerRole;

         for (j = 0; j < MAX_PLAYER_EQUIPMENTS; j++)
         {
            if (gpGlobals->g.rgObject[gpGlobals->g.PlayerRoles.rgwEquipment[j][w]].item.wFlags & kItemFlagUsable)
            {
               if (g_iNumInventory < MAX_INVENTORY)
               {
                  gpGlobals->rgInventory[g_iNumInventory].wItem = gpGlobals->g.PlayerRoles.rgwEquipment[j][w];
                  gpGlobals->rgInventory[g_iNumInventory].nAmount = 0;
                  gpGlobals->rgInventory[g_iNumInventory].nAmountInUse = (WORD)-1;

                  g_iNumInventory++;
               }
            }
         }
      }
   }
}

WORD
PAL_ItemSelectMenu(
   LPITEMCHANGED_CALLBACK    lpfnMenuItemChanged,
   WORD                      wItemFlags
)
/*++
  Purpose:

    Show the item selection menu.

  Parameters:

    [IN]  lpfnMenuItemChanged - Callback function which is called when user
                                changed the current menu item.

    [IN]  wItemFlags - flags for usable item.

  Return value:

    The object ID of the selected item. 0 if cancelled.

--*/
{
   int              iPrevIndex;
   WORD             w;
   DWORD            dwTime;

   PAL_ItemSelectMenuInit(wItemFlags);
   iPrevIndex = g_iCurMenuItem;

   PAL_ClearKeyState();

   if (lpfnMenuItemChanged != NULL)
   {
      g_fNoDesc = TRUE;
      (*lpfnMenuItemChanged)(gpGlobals->rgInventory[g_iCurMenuItem].wItem);
   }

   dwTime = SDL_GetTicks();

   while (TRUE)
   {
      if (lpfnMenuItemChanged == NULL)
      {
         PAL_MakeScene();
      }

      w = PAL_ItemSelectMenuUpdate();
       PAL_ClearKeyState();

      VIDEO_UpdateScreen(NULL);

      PAL_ProcessEvent();
      while (SDL_GetTicks() < dwTime)
      {
         PAL_ProcessEvent();
         if (g_InputState.touchEventType != TOUCH_NONE || g_InputState.dwKeyPress != 0)
         {
            break;
         }
         SDL_Delay(5);
      }

      dwTime = SDL_GetTicks() + FRAME_TIME;

      if (w != 0xFFFF)
      {
         g_fNoDesc = FALSE;
         return w;
      }

      if (iPrevIndex != g_iCurMenuItem)
      {
         if (g_iCurMenuItem >= 0 && g_iCurMenuItem < MAX_INVENTORY)
         {
            if (lpfnMenuItemChanged != NULL)
            {
               (*lpfnMenuItemChanged)(gpGlobals->rgInventory[g_iCurMenuItem].wItem);
            }
         }

         iPrevIndex = g_iCurMenuItem;
      }
   }

   assert(FALSE);
   return 0; // should not really reach here
}
