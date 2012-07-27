#include "main.h"
#include "hack.h"

BOOL g_isFlyMode = FALSE;
BOOL g_isNoEnemy = FALSE;

BOOL isFlyMode()
{
	return g_isFlyMode;
}

void setFlyMode(BOOL isFly)
{
	g_isFlyMode = isFly;
}

BOOL isNoEnemy()
{
	return g_isNoEnemy;
}

void setNoEnemy(BOOL isTrans)
{
	g_isNoEnemy = isTrans;
}

void addMoney()
{
	gpGlobals->dwCash += 5000;
}

void uplevel()
{
	const SDL_Rect   rect = {65, 60, 200, 100};
	const SDL_Rect   rect1 = {80, 0, 180, 200};
	BOOL fLevelUp;
	int i, j, iTotalCount;
	WORD w;
	DWORD dwExp;
	PLAYERROLES      OrigPlayerRoles;
	OrigPlayerRoles = gpGlobals->g.PlayerRoles;

	for (i = 0; i <= gpGlobals->wMaxPartyMemberIndex; i++)
	{
		fLevelUp = FALSE;

		w = gpGlobals->rgParty[i].wPlayerRole;

		if (gpGlobals->g.PlayerRoles.rgwLevel[w] > MAX_LEVELS)
		{
			gpGlobals->g.PlayerRoles.rgwLevel[w] = MAX_LEVELS;
			continue;
		}

		fLevelUp = TRUE;
		PAL_PlayerLevelUp(w, 1);

		gpGlobals->g.PlayerRoles.rgwHP[w] = gpGlobals->g.PlayerRoles.rgwMaxHP[w];
		gpGlobals->g.PlayerRoles.rgwMP[w] = gpGlobals->g.PlayerRoles.rgwMaxMP[w];

		if (fLevelUp)
		{
			//
			// Player has gained a level. Show the message
			//
			PAL_CreateSingleLineBox(PAL_XY(80, 0), 10, FALSE);
			PAL_CreateBox(PAL_XY(82, 32), 7, 8, 1, FALSE, NULL);

			PAL_DrawText(PAL_GetWord(gpGlobals->g.PlayerRoles.rgwName[w]), PAL_XY(110, 10), 0,
				FALSE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_LEVEL), PAL_XY(110 + 16 * 3, 10), 0, FALSE, FALSE);
			PAL_DrawText(PAL_GetWord(BATTLEWIN_LEVELUP_LABEL), PAL_XY(110 + 16 * 5, 10), 0, FALSE, FALSE);

			for (j = 0; j < 8; j++)
			{
				PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_ARROW),
					gpScreen, PAL_XY(183, 48 + 18 * j));
			}

			PAL_DrawText(PAL_GetWord(STATUS_LABEL_LEVEL), PAL_XY(100, 44), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_HP), PAL_XY(100, 62), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_MP), PAL_XY(100, 80), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_ATTACKPOWER), PAL_XY(100, 98), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_MAGICPOWER), PAL_XY(100, 116), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_RESISTANCE), PAL_XY(100, 134), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_DEXTERITY), PAL_XY(100, 152), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);
			PAL_DrawText(PAL_GetWord(STATUS_LABEL_FLEERATE), PAL_XY(100, 170), BATTLEWIN_LEVELUP_LABEL_COLOR,
				TRUE, FALSE);

			//
			// Draw the original stats and stats after level up
			//
			PAL_DrawNumber(OrigPlayerRoles.rgwLevel[w], 4, PAL_XY(133, 47),
				kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(gpGlobals->g.PlayerRoles.rgwLevel[w], 4, PAL_XY(195, 47),
				kNumColorYellow, kNumAlignRight);

			PAL_DrawNumber(OrigPlayerRoles.rgwHP[w], 4, PAL_XY(133, 64),
				kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(OrigPlayerRoles.rgwMaxHP[w], 4, PAL_XY(154, 68),
				kNumColorBlue, kNumAlignRight);
			PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_SLASH), gpScreen,
				PAL_XY(156, 66));
			PAL_DrawNumber(gpGlobals->g.PlayerRoles.rgwHP[w], 4, PAL_XY(195, 64),
				kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(gpGlobals->g.PlayerRoles.rgwMaxHP[w], 4, PAL_XY(216, 68),
				kNumColorBlue, kNumAlignRight);
			PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_SLASH), gpScreen,
				PAL_XY(218, 66));

			PAL_DrawNumber(OrigPlayerRoles.rgwMP[w], 4, PAL_XY(133, 82),
				kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(OrigPlayerRoles.rgwMaxMP[w], 4, PAL_XY(154, 86),
				kNumColorBlue, kNumAlignRight);
			PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_SLASH), gpScreen,
				PAL_XY(156, 84));
			PAL_DrawNumber(gpGlobals->g.PlayerRoles.rgwMP[w], 4, PAL_XY(195, 82),
				kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(gpGlobals->g.PlayerRoles.rgwMaxMP[w], 4, PAL_XY(216, 86),
				kNumColorBlue, kNumAlignRight);
			PAL_RLEBlitToSurface(PAL_SpriteGetFrame(gpSpriteUI, SPRITENUM_SLASH), gpScreen,
				PAL_XY(218, 84));

			PAL_DrawNumber(OrigPlayerRoles.rgwAttackStrength[w] + PAL_GetPlayerAttackStrength(w) -
				gpGlobals->g.PlayerRoles.rgwAttackStrength[w],
				4, PAL_XY(133, 101), kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(PAL_GetPlayerAttackStrength(w), 4, PAL_XY(195, 101),
				kNumColorYellow, kNumAlignRight);

			PAL_DrawNumber(OrigPlayerRoles.rgwMagicStrength[w] + PAL_GetPlayerMagicStrength(w) -
				gpGlobals->g.PlayerRoles.rgwMagicStrength[w],
				4, PAL_XY(133, 119), kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(PAL_GetPlayerMagicStrength(w), 4, PAL_XY(195, 119),
				kNumColorYellow, kNumAlignRight);

			PAL_DrawNumber(OrigPlayerRoles.rgwDefense[w] + PAL_GetPlayerDefense(w) -
				gpGlobals->g.PlayerRoles.rgwDefense[w],
				4, PAL_XY(133, 137), kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(PAL_GetPlayerDefense(w), 4, PAL_XY(195, 137),
				kNumColorYellow, kNumAlignRight);

			PAL_DrawNumber(OrigPlayerRoles.rgwDexterity[w] + PAL_GetPlayerDexterity(w) -
				gpGlobals->g.PlayerRoles.rgwDexterity[w],
				4, PAL_XY(133, 155), kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(PAL_GetPlayerDexterity(w), 4, PAL_XY(195, 155),
				kNumColorYellow, kNumAlignRight);

			PAL_DrawNumber(OrigPlayerRoles.rgwFleeRate[w] + PAL_GetPlayerFleeRate(w) -
				gpGlobals->g.PlayerRoles.rgwFleeRate[w],
				4, PAL_XY(133, 173), kNumColorYellow, kNumAlignRight);
			PAL_DrawNumber(PAL_GetPlayerFleeRate(w), 4, PAL_XY(195, 173),
				kNumColorYellow, kNumAlignRight);

			//
			// Update the screen and wait for key
			//
			VIDEO_UpdateScreen(&rect1);
			PAL_WaitForKey(3000);

			OrigPlayerRoles = gpGlobals->g.PlayerRoles;
		}

		//
		// Increasing of other hidden levels
		//
		iTotalCount = 0;

		iTotalCount += gpGlobals->Exp.rgAttackExp[w].wCount;
		iTotalCount += gpGlobals->Exp.rgDefenseExp[w].wCount;
		iTotalCount += gpGlobals->Exp.rgDexterityExp[w].wCount;
		iTotalCount += gpGlobals->Exp.rgFleeExp[w].wCount;
		iTotalCount += gpGlobals->Exp.rgHealthExp[w].wCount;
		iTotalCount += gpGlobals->Exp.rgMagicExp[w].wCount;
		iTotalCount += gpGlobals->Exp.rgMagicPowerExp[w].wCount;

		if (iTotalCount > 0)
		{
#define CHECK_HIDDEN_EXP(expname, statname, label)          \
			{                                                           \
			dwExp = g_Battle.iExpGained;                             \
			dwExp *= gpGlobals->Exp.expname[w].wCount;               \
			dwExp /= iTotalCount;                                    \
			dwExp *= 2;                                              \
			\
			dwExp += gpGlobals->Exp.expname[w].wExp;                 \
			\
			if (gpGlobals->Exp.expname[w].wLevel > MAX_LEVELS)       \
			{                                                        \
			gpGlobals->Exp.expname[w].wLevel = MAX_LEVELS;        \
		}                                                        \
		\
		while (dwExp >= gpGlobals->g.rgLevelUpExp[gpGlobals->Exp.expname[w].wLevel]) \
			{                                                        \
			dwExp -= gpGlobals->g.rgLevelUpExp[gpGlobals->Exp.expname[w].wLevel]; \
			gpGlobals->g.PlayerRoles.statname[w] += RandomLong(1, 2); \
			if (gpGlobals->Exp.expname[w].wLevel < MAX_LEVELS)    \
			{                                                     \
			gpGlobals->Exp.expname[w].wLevel++;                \
		}                                                     \
		}                                                        \
		\
		gpGlobals->Exp.expname[w].wExp = (WORD)dwExp;            \
		\
		if (gpGlobals->g.PlayerRoles.statname[w] !=              \
		OrigPlayerRoles.statname[w])                          \
			{                                                        \
			PAL_CreateSingleLineBox(PAL_XY(83, 60), 8, FALSE);    \
			PAL_DrawText(PAL_GetWord(gpGlobals->g.PlayerRoles.rgwName[w]), PAL_XY(95, 70), \
			0, FALSE, FALSE);                                  \
			PAL_DrawText(PAL_GetWord(label), PAL_XY(143, 70),     \
			0, FALSE, FALSE);                                  \
			PAL_DrawText(PAL_GetWord(BATTLEWIN_LEVELUP_LABEL), PAL_XY(175, 70),  \
			0, FALSE, FALSE);                                  \
			PAL_DrawNumber(gpGlobals->g.PlayerRoles.statname[w] - \
			OrigPlayerRoles.statname[w],                       \
			5, PAL_XY(188, 74), kNumColorYellow, kNumAlignRight); \
			VIDEO_UpdateScreen(&rect);                            \
			PAL_WaitForKey(3000);                                 \
		}                                                        \
		}

			CHECK_HIDDEN_EXP(rgHealthExp, rgwMaxHP, STATUS_LABEL_HP);
			CHECK_HIDDEN_EXP(rgMagicExp, rgwMaxMP, STATUS_LABEL_MP);
			CHECK_HIDDEN_EXP(rgAttackExp, rgwAttackStrength, STATUS_LABEL_ATTACKPOWER);
			CHECK_HIDDEN_EXP(rgMagicPowerExp, rgwMagicStrength, STATUS_LABEL_MAGICPOWER);
			CHECK_HIDDEN_EXP(rgDefenseExp, rgwDefense, STATUS_LABEL_RESISTANCE);
			CHECK_HIDDEN_EXP(rgDexterityExp, rgwDexterity, STATUS_LABEL_DEXTERITY);
			CHECK_HIDDEN_EXP(rgFleeExp, rgwFleeRate, STATUS_LABEL_FLEERATE);

#undef CHECK_HIDDEN_EXP
		}

		//
		// Learn all magics at the current level
		//
		j = 0;

		while (j < gpGlobals->g.nLevelUpMagic)
		{
			if (gpGlobals->g.lprgLevelUpMagic[j].m[w].wMagic == 0 ||
				gpGlobals->g.lprgLevelUpMagic[j].m[w].wLevel > gpGlobals->g.PlayerRoles.rgwLevel[w])
			{
				j++;
				continue;
			}

			if (PAL_AddMagic(w, gpGlobals->g.lprgLevelUpMagic[j].m[w].wMagic))
			{
				PAL_CreateSingleLineBox(PAL_XY(65, 105), 10, FALSE);

				PAL_DrawText(PAL_GetWord(gpGlobals->g.PlayerRoles.rgwName[w]),
					PAL_XY(75, 115), 0, FALSE, FALSE);
				PAL_DrawText(PAL_GetWord(BATTLEWIN_ADDMAGIC_LABEL), PAL_XY(75 + 16 * 3, 115),
					0, FALSE, FALSE);
				PAL_DrawText(PAL_GetWord(gpGlobals->g.lprgLevelUpMagic[j].m[w].wMagic),
					PAL_XY(75 + 16 * 5, 115), 0x1B, FALSE, FALSE);

				VIDEO_UpdateScreen(&rect);
				PAL_WaitForKey(3000);
			}

			j++;
		}
	}
}