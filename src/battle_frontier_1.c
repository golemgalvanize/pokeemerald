#include "global.h"
#include "battle.h"
#include "battle_frontier_2.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "bg.h"
#include "constants/abilities.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/species.h"
#include "decompress.h"
#include "event_data.h"
#include "graphics.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "random.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "util.h"
#include "window.h"

struct UnkEWRamStruct
{
    u16 species;
    u16 move[4];
    u8 itemListId;
    u8 EVs;
    u8 nature;
    u8 field_D;
    u16 field_E;
};

struct Unk190400
{
    u8 unk_0[16];
    u8 unk_10;
    u8 filler[3];
};


extern struct UnkEWRamStruct *gUnknown_0203BC8C;
extern u8 gUnknown_0203CEF8[];
extern u32 gUnknown_0203CD70;
extern u32 gUnknown_0203CD74;
extern struct Unk190400* gUnknown_0203CD78;
extern u16 gBattle_BG0_X;
extern u16 gBattle_BG0_Y;
extern u16 gBattle_BG1_X;
extern u16 gBattle_BG1_Y;
extern u16 gBattle_BG2_X;
extern u16 gBattle_BG2_Y;
extern u16 gBattle_BG3_X;
extern u16 gBattle_BG3_Y;

//TEMPORARY UNTIL RODATA IS CONVERTED

extern const struct BgTemplate gUnknown_0860CE84[];
extern const struct WindowTemplate gUnknown_0860CEB4[];
extern const struct CompressedSpriteSheet gUnknown_0860CF50[];
extern const struct SpriteTemplate gUnknown_0860D050;
extern const struct SpriteTemplate gUnknown_0860D068;
extern void (*const gUnknown_0860D090[])(void);
extern const u32 gUnknown_0860D0EC[][2];
extern const u32 gUnknown_0860D0FC[][2];
extern const u8 gUnknown_0860D10C[][4];
extern const u8 gUnknown_0860D14C[];
extern const u8 gUnknown_0860D3C6[][2];

extern const u8* gRoundsStringTable[];
extern u16 gBattleFrontierHeldItems[];

extern u8 sub_8165C40(void);
extern bool8 sub_81A3610(void);
extern u16 sub_81A4FF0(u8);

void sub_818F720(u16, int, int, u8, u8, u32*);
void sub_818F904(int, int, u16*);
void sub_818FBDC(u16);
int sub_818FC78(u16);
int sub_818FCBC(u16, u8);
int sub_818FDB8(u16, u8);
int sub_818FEB4(int*, u8);
int sub_818FFC0(int, int, int);
u8 sub_8190168(u16);
u16 sub_81902AC(void);
void sub_8190400(u8);
void sub_8190CD4(u8);
void sub_81924E0(u8, u8);
void sub_819314C(u8, u8);
void sub_8194B54(void);
void sub_8194B70(void);
u16 sub_8195358(u16);
void sub_8195898(u8*, u16);

void sub_818E9AC(void)
{
    gUnknown_0860D090[gSpecialVar_0x8004]();
}

void sub_818E9CC(void)
{
    u8 chosenLevel = gSaveBlock2Ptr->frontierChosenLvl;
    u16 var = VarGet(0x40CE);

    gSaveBlock2Ptr->field_CA8 = 0;
    gSaveBlock2Ptr->battlePyramidWildHeaderId = 0;
    gSaveBlock2Ptr->field_CA9_a = 0;
    gSaveBlock2Ptr->field_CA9_b = 0;

    if ((gSaveBlock2Ptr->field_CDC & gUnknown_0860D0EC[var][chosenLevel]) == 0)
        gSaveBlock2Ptr->field_D0C[var][chosenLevel] = 0;

    saved_warp2_set(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, -1);
    gTrainerBattleOpponent_A = 0;
}

void sub_818EA84(void)
{
    u8 chosenLevel = gSaveBlock2Ptr->frontierChosenLvl;
    u16 var = VarGet(0x40CE);

    switch (gSpecialVar_0x8005)
    {
        case 0:
            gSpecialVar_Result = gSaveBlock2Ptr->field_D0C[var][chosenLevel];
            break;
        case 1:
            gSpecialVar_Result = (gSaveBlock2Ptr->field_CDC & gUnknown_0860D0EC[var][chosenLevel]) == 0 ? 0 : 1;
            break;
        case 2:
            gSpecialVar_Result = gSaveBlock2Ptr->field_D08_a;
            break;
        case 3:
            gSpecialVar_Result = gSaveBlock2Ptr->field_D08_b;
            break;
        case 4:
            gSpecialVar_Result = gSaveBlock2Ptr->field_D08_c;
            break;
        case 5:
            gSpecialVar_Result = gSaveBlock2Ptr->field_D08_d;
            break;
        case 6:
            if (VarGet(0x40CE) == 1)
            {
                if (chosenLevel != 0)
                    gSpecialVar_Result = gSaveBlock2Ptr->field_D08_f;
                else
                    gSpecialVar_Result = gSaveBlock2Ptr->field_D08_e;
            }
            else if (chosenLevel != 0)
            {
                gSpecialVar_Result = gSaveBlock2Ptr->field_D08_b;
            }
            else
            {
                gSpecialVar_Result = gSaveBlock2Ptr->field_D08_a;
            }
            break;
        case 7:
            if (VarGet(0x40CE) == 1)
            {
                if (chosenLevel != 0)
                    gSpecialVar_Result = gSaveBlock2Ptr->field_D08_h;
                else
                    gSpecialVar_Result = gSaveBlock2Ptr->field_D08_g;
            }
            else if (chosenLevel != 0)
            {
                gSpecialVar_Result = gSaveBlock2Ptr->field_D08_d;
            }
            else
            {
                gSpecialVar_Result = gSaveBlock2Ptr->field_D08_c;
            }
            break;
        case 8:
            sub_81B8558();
            gUnknown_0203CEF8[0] = gSaveBlock2Ptr->field_CAA[3];
            gUnknown_0203CEF8[1] = gSaveBlock2Ptr->field_CAA[3] >> 8;
            break;
        case 9:
            gSpecialVar_Result = (gSaveBlock2Ptr->field_D0A * 2 - 3) + gSaveBlock2Ptr->field_D0B;
            break;
    }
}

void sub_818ED28(void)
{
    u8 chosenLevel = gSaveBlock2Ptr->frontierChosenLvl;
    u16 var = VarGet(0x40CE);

    switch (gSpecialVar_0x8005)
    {
        case 0:
            gSaveBlock2Ptr->field_D0C[var][chosenLevel] = gSpecialVar_0x8006;
            break;
        case 1:
            if (gSpecialVar_0x8006)
                gSaveBlock2Ptr->field_CDC |= gUnknown_0860D0EC[var][chosenLevel];
            else
                gSaveBlock2Ptr->field_CDC &= gUnknown_0860D0FC[var][chosenLevel];
            break;
        case 2:
            gSaveBlock2Ptr->field_D08_a = gSpecialVar_0x8006;
            break;
        case 3:
            gSaveBlock2Ptr->field_D08_b = gSpecialVar_0x8006;
            break;
        case 4:
            gSaveBlock2Ptr->field_D08_c = gSpecialVar_0x8006;
            break;
        case 5:
            gSaveBlock2Ptr->field_D08_d = gSpecialVar_0x8006;
            break;
        case 6:
            if (VarGet(0x40CE) == 1)
            {
                if (chosenLevel != 0)
                    gSaveBlock2Ptr->field_D08_f = gSpecialVar_0x8006;
                else
                    gSaveBlock2Ptr->field_D08_e = gSpecialVar_0x8006;
            }
            else if (chosenLevel != 0)
            {
                gSaveBlock2Ptr->field_D08_b = gSpecialVar_0x8006;
            }
            else
            {
                gSaveBlock2Ptr->field_D08_a = gSpecialVar_0x8006;
            }
            break;
        case 7:
            if (VarGet(0x40CE) == 1)
            {
                if (chosenLevel != 0)
                    gSaveBlock2Ptr->field_D08_h = gSpecialVar_0x8006;
                else
                    gSaveBlock2Ptr->field_D08_g = gSpecialVar_0x8006;
            }
            else if (chosenLevel != 0)
            {
                gSaveBlock2Ptr->field_D08_d = gSpecialVar_0x8006;
            }
            else
            {
                gSaveBlock2Ptr->field_D08_c = gSpecialVar_0x8006;
            }
            break;
        case 8:
            gSaveBlock2Ptr->field_CAA[3] = gUnknown_0203CEF8[0] | (gUnknown_0203CEF8[1] << 8);
            break;
    }
}

// SOMEBODY FUCKING FIX THIS IT'S NOT EVEN CLOSE TO FUNCTIONALLY EQUIVALENT

#ifdef NONMATCHING
void sub_818F02C(void)
{
    int sp8[3];
    int var_48 = 0;
    int var_2C = 0;
    u16 *var_44;
    u32 *var_40;
    int i, j, k;
    s32 typeBits;
    s32 r4__;
    s32 r4____;
    sp8[0] = 0;
    sp8[1] = 0;
    sp8[2] = 0;
    var_44 = AllocZeroed(sizeof(u16[16]));
    var_40 = AllocZeroed(sizeof(u32[6]));

    gSaveBlock2Ptr->field_D0A = gSaveBlock2Ptr->frontierChosenLvl + 1;
    gSaveBlock2Ptr->field_D0B = VarGet(0x40CE) + 1;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_a = 0x3FF;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_b = 0;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_c = 0;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_d = 0;

    for (i = 0; i < 3; i++)
    {
        gSaveBlock2Ptr->field_D64[0][i] = GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_SPECIES, 0);

        for (j = 0; j < 4; j++)
            gSaveBlock2Ptr->frontierStruct[i].move[j] = GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_MOVE1 + j, 0);

        for (j = 0; j < 6; j++)
            gSaveBlock2Ptr->frontierStruct[i].ev[j] = GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_HP_EV + j, 0);

        gSaveBlock2Ptr->frontierStruct[i].nature = GetNature(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i]] - 1);
    }

    for (i = 1; i < 16; i++)
    {
        u16 r4;
        u16 r6;

        if (i > 5)
        {
            do
            {
                r4 = sub_8162548(sub_81A39C4(), 0);
                
                for (j = 1; j < i && gSaveBlock2Ptr->frontierStruct2[j].field_0_a != r4; j++)
                    ;
            }
            while (j != i);
                
            gSaveBlock2Ptr->frontierStruct2[2].field_0_a = r4; 
        }
        else
        {
            do
            {
                r4 = sub_8162548(sub_81A39C4() + 1, 0);
                
                for (j = 1; j < i && gSaveBlock2Ptr->frontierStruct2[j].field_0_a != r4; j++)
                    ;
            }
            while (j != i);
                
            gSaveBlock2Ptr->frontierStruct2[2].field_0_a = r4; 
        }

        for (j = 0; j < 3; j++)
        {
            do
            {
                r6 = sub_8163524(r4);

                for (k = 0; k < j; k++)
                {
                    if (gSaveBlock2Ptr->field_D64[1][k] == r6 || sp8[0] == gUnknown_0203BC8C[r6].species || sp8[1] == gUnknown_0203BC8C[r6].species || gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[1][k]].item == gUnknown_0203BC8C[r6].item)
                        break;
                }
            }
            while (k != j);

            gSaveBlock2Ptr->field_D64[1][j] = r6;
            sp8[j] = gUnknown_0203BC8C[r6].species;
        }

        gSaveBlock2Ptr->frontierStruct2[2].field_0_b = 0;
        gSaveBlock2Ptr->frontierStruct2[2].field_0_c = 0;
        gSaveBlock2Ptr->frontierStruct2[2].field_0_d = 0;
    }

    typeBits = 0;
    var_44[0] = 0;
    for (i = 0; i < 3; i++)
    {
        var_44[0] += GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_ATK, 0);
        var_44[0] += GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_DEF, 0);
        var_44[0] += GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_SPATK, 0);
        var_44[0] += GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_SPDEF, 0);
        var_44[0] += GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_SPEED, 0);
        var_44[0] += GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_MAX_HP, 0);
        typeBits |= gBitTable[gBaseStats[GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_SPECIES, 0)].type1];
        typeBits |= gBitTable[gBaseStats[GetMonData(&gPlayerParty[gSaveBlock2Ptr->field_CAA[i] - 1], MON_DATA_SPECIES, 0)].type2];
    }

    for (j = 0; j < 32; j++)
    {
        if (typeBits & 1)
            r4__++;
        typeBits >>= 1;
    }

    var_48 = sub_8165C40();
    var_44[0] += r4__ * var_48 / 20;
    
    for (i = 1; i < 16; i++)
    {
        int r8;
        
        typeBits = 0;
        var_44[i] = typeBits;
        r8 = sub_8190168(gSaveBlock2Ptr->frontierStruct2[i].field_0_a);
        
        for (j = 0; j < 3; j++)
        {
            int newFiller;
            
            sub_818F720(gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[i][j]].species, var_48, r8, gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[i][j]].EVs, gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[i][j]].nature, var_40);
            newFiller = var_40[1];
            newFiller += var_44[i];
            newFiller += var_40[2];
            newFiller += var_40[4];
            newFiller += var_40[5];
            newFiller += var_40[3];
            newFiller += var_40[0];
            var_44[i] = newFiller;
            typeBits |= gBitTable[gBaseStats[gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[i][j]].species].type1];
            typeBits |= gBitTable[gBaseStats[gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[i][j]].species].type2];
        }
        
        r4____ = 0;
        
        for (j = 0; j < 32; j++)
        {
            if (typeBits & 1)
                r4____++;
            typeBits >>= 1;
        }
        
        var_44[i] += (r4____ * var_48) / 20;
    }
    
    for (i = 0; i < 15; i++)
    {
        for (j = i + 1; j < 16; j++)
        {
            if (var_44[i] >= var_44[j])
            {
                if (var_44[i] != var_44[j])
                {
                    continue;
                }
                else if (gSaveBlock2Ptr->frontierStruct2[j].field_0_a == 0x3FF)
                {
                    _why:
                    sub_818F904(i, j, var_44);
                }
                else
                {
                    
                    if (gSaveBlock2Ptr->frontierStruct2[i].field_0_a > gSaveBlock2Ptr->frontierStruct2[j].field_0_a)
                        sub_818F904(i, j, var_44);
                }
            }
            else
            {
                goto _why;
            }
        }
    }
    
    if (sub_81A3610())
    {
        int r5;
        
        for (i = 0; i < 16 && gSaveBlock2Ptr->frontierStruct2[i].field_0_a != 0x3FF; i++)
            ;
        
        if (gUnknown_0860D3C6[21 + i][1])
        {
            r5 = 0;
            gSaveBlock2Ptr->frontierStruct2[0].field_0_a = 0x3FE;
        }
        else
        {
            r5 = 1;
            gSaveBlock2Ptr->frontierStruct2[1].field_0_a = 0x3FE;
        }
        
        for (i = 0; i < 3; i++)
        {
            gSaveBlock2Ptr->field_D64[r5][i] = sub_81A4FF0(i);
        }
    }

    Free(var_44);
    Free(var_40);
}
#else
NAKED
void sub_818F02C(void)
{
    asm_unified("push {r4-r7,lr}\n\
	mov r7, r10\n\
	mov r6, r9\n\
	mov r5, r8\n\
	push {r5-r7}\n\
	sub sp, 0x3C\n\
	movs r0, 0\n\
	str r0, [sp, 0x8]\n\
	str r0, [sp, 0xC]\n\
	str r0, [sp, 0x10]\n\
	movs r0, 0x20\n\
	bl AllocZeroed\n\
	str r0, [sp, 0x18]\n\
	movs r0, 0x18\n\
	bl AllocZeroed\n\
	str r0, [sp, 0x1C]\n\
	ldr r4, =gSaveBlock2Ptr\n\
	ldr r1, [r4]\n\
	ldr r2, =0x00000ca9\n\
	adds r0, r1, r2\n\
	ldrb r0, [r0]\n\
	lsls r0, 30\n\
	lsrs r0, 30\n\
	adds r0, 0x1\n\
	ldr r3, =0x00000d0a\n\
	adds r1, r3\n\
	strb r0, [r1]\n\
	ldr r0, =0x000040ce\n\
	bl VarGet\n\
	ldr r1, [r4]\n\
	adds r0, 0x1\n\
	ldr r5, =0x00000d0b\n\
	adds r1, r5\n\
	strb r0, [r1]\n\
	ldr r2, [r4]\n\
	ldr r7, =0x00000d24\n\
	adds r3, r2, r7\n\
	ldrh r0, [r3]\n\
	ldr r5, =0x000003ff\n\
	adds r1, r5, 0\n\
	orrs r0, r1\n\
	strh r0, [r3]\n\
	ldr r3, =0x00000d25\n\
	adds r2, r3\n\
	ldrb r1, [r2]\n\
	movs r0, 0x5\n\
	negs r0, r0\n\
	ands r0, r1\n\
	strb r0, [r2]\n\
	ldr r1, [r4]\n\
	adds r1, r3\n\
	ldrb r2, [r1]\n\
	movs r0, 0x19\n\
	negs r0, r0\n\
	ands r0, r2\n\
	strb r0, [r1]\n\
	ldr r1, [r4]\n\
	adds r1, r3\n\
	ldrb r2, [r1]\n\
	movs r0, 0x1F\n\
	ands r0, r2\n\
	strb r0, [r1]\n\
	movs r7, 0\n\
	mov r10, r7\n\
	mov r8, r4\n\
	ldr r0, =gBattleScripting + 0x14\n\
	mov r9, r0\n\
	movs r4, 0\n\
_0818F0BA:\n\
	mov r1, r8\n\
	ldr r0, [r1]\n\
	ldr r2, =0x00000caa\n\
	adds r0, r2\n\
	adds r0, r4\n\
	ldrh r0, [r0]\n\
	movs r3, 0x64\n\
	muls r0, r3\n\
	add r0, r9\n\
	movs r1, 0xB\n\
	movs r2, 0\n\
	bl GetMonData\n\
	mov r5, r8\n\
	ldr r1, [r5]\n\
	ldr r7, =0x00000d64\n\
	adds r1, r7\n\
	adds r1, r4\n\
	strh r0, [r1]\n\
	movs r5, 0\n\
	mov r0, r10\n\
	lsls r7, r0, 4\n\
	adds r6, r7, 0\n\
_0818F0E8:\n\
	mov r1, r8\n\
	ldr r0, [r1]\n\
	ldr r2, =0x00000caa\n\
	adds r0, r2\n\
	adds r0, r4\n\
	ldrh r0, [r0]\n\
	movs r3, 0x64\n\
	muls r0, r3\n\
	add r0, r9\n\
	adds r1, r5, 0\n\
	adds r1, 0xD\n\
	movs r2, 0\n\
	bl GetMonData\n\
	mov r2, r8\n\
	ldr r1, [r2]\n\
	ldr r3, =0x00000efc\n\
	adds r1, r3\n\
	adds r1, r6\n\
	strh r0, [r1]\n\
	adds r6, 0x2\n\
	adds r5, 0x1\n\
	cmp r5, 0x3\n\
	ble _0818F0E8\n\
	movs r5, 0\n\
	ldr r6, =gSaveBlock2Ptr\n\
_0818F11C:\n\
	ldr r0, [r6]\n\
	ldr r1, =0x00000caa\n\
	adds r0, r1\n\
	adds r0, r4\n\
	ldrh r0, [r0]\n\
	movs r2, 0x64\n\
	muls r0, r2\n\
	add r0, r9\n\
	adds r1, r5, 0\n\
	adds r1, 0x1A\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r1, [r6]\n\
	adds r2, r5, r7\n\
	ldr r3, =0x00000f04\n\
	adds r1, r3\n\
	adds r1, r2\n\
	strb r0, [r1]\n\
	adds r5, 0x1\n\
	cmp r5, 0x5\n\
	ble _0818F11C\n\
	mov r5, r8\n\
	ldr r0, [r5]\n\
	ldr r1, =0x00000caa\n\
	adds r0, r1\n\
	adds r0, r4\n\
	ldrh r0, [r0]\n\
	movs r2, 0x64\n\
	muls r0, r2\n\
	add r0, r9\n\
	bl GetNature\n\
	ldr r1, [r5]\n\
	adds r1, r7\n\
	ldr r3, =0x00000f0a\n\
	adds r1, r3\n\
	strb r0, [r1]\n\
	adds r4, 0x2\n\
	movs r5, 0x1\n\
	add r10, r5\n\
	mov r7, r10\n\
	cmp r7, 0x2\n\
	ble _0818F0BA\n\
	mov r10, r5\n\
	movs r0, 0x4\n\
	str r0, [sp, 0x34]\n\
	movs r1, 0x6\n\
	str r1, [sp, 0x38]\n\
_0818F17E:\n\
	mov r2, r10\n\
	cmp r2, 0x5\n\
	ble _0818F22C\n\
_0818F184:\n\
	bl sub_81A39C4\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	movs r1, 0\n\
	bl sub_8162548\n\
	lsls r0, 16\n\
	lsrs r4, r0, 16\n\
	movs r5, 0x1\n\
	cmp r5, r10\n\
	bge _0818F1CA\n\
	ldr r3, =gSaveBlock2Ptr\n\
	ldr r0, [r3]\n\
	ldr r7, =0x00000d28\n\
	adds r0, r7\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	lsrs r0, 22\n\
	adds r2, r3, 0\n\
	cmp r0, r4\n\
	beq _0818F1CA\n\
	ldr r3, =0x00000d24\n\
_0818F1B2:\n\
	adds r5, 0x1\n\
	cmp r5, r10\n\
	bge _0818F1CA\n\
	ldr r0, [r2]\n\
	lsls r1, r5, 2\n\
	adds r0, r1\n\
	adds r0, r3\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	lsrs r0, 22\n\
	cmp r0, r4\n\
	bne _0818F1B2\n\
_0818F1CA:\n\
	cmp r5, r10\n\
	bne _0818F184\n\
	ldr r0, =gSaveBlock2Ptr\n\
	ldr r3, [r0]\n\
	ldr r1, [sp, 0x34]\n\
	adds r3, r1\n\
	ldr r2, =0x00000d24\n\
	adds r3, r2\n\
	ldr r5, =0x000003ff\n\
	adds r0, r5, 0\n\
	adds r2, r4, 0\n\
	ands r2, r0\n\
	ldrh r0, [r3]\n\
	ldr r7, =0xfffffc00\n\
	adds r1, r7, 0\n\
	b _0818F292\n\
	.pool\n\
_0818F22C:\n\
	bl sub_81A39C4\n\
	adds r0, 0x1\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	movs r1, 0\n\
	bl sub_8162548\n\
	lsls r0, 16\n\
	lsrs r4, r0, 16\n\
	movs r5, 0x1\n\
	cmp r5, r10\n\
	bge _0818F274\n\
	ldr r1, =gSaveBlock2Ptr\n\
	ldr r0, [r1]\n\
	ldr r2, =0x00000d28\n\
	adds r0, r2\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	lsrs r0, 22\n\
	adds r2, r1, 0\n\
	cmp r0, r4\n\
	beq _0818F274\n\
	ldr r3, =0x00000d24\n\
_0818F25C:\n\
	adds r5, 0x1\n\
	cmp r5, r10\n\
	bge _0818F274\n\
	ldr r0, [r2]\n\
	lsls r1, r5, 2\n\
	adds r0, r1\n\
	adds r0, r3\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	lsrs r0, 22\n\
	cmp r0, r4\n\
	bne _0818F25C\n\
_0818F274:\n\
	cmp r5, r10\n\
	bne _0818F22C\n\
	ldr r5, =gSaveBlock2Ptr\n\
	ldr r3, [r5]\n\
	ldr r7, [sp, 0x34]\n\
	adds r3, r7\n\
	ldr r0, =0x00000d24\n\
	adds r3, r0\n\
	ldr r1, =0x000003ff\n\
	adds r0, r1, 0\n\
	adds r2, r4, 0\n\
	ands r2, r0\n\
	ldrh r0, [r3]\n\
	ldr r5, =0xfffffc00\n\
	adds r1, r5, 0\n\
_0818F292:\n\
	ands r0, r1\n\
	orrs r0, r2\n\
	strh r0, [r3]\n\
	movs r5, 0\n\
	lsls r4, 16\n\
	str r4, [sp, 0x2C]\n\
	ldr r7, [sp, 0x38]\n\
	str r7, [sp, 0x20]\n\
_0818F2A2:\n\
	lsls r0, r5, 1\n\
	mov r9, r0\n\
	adds r1, r5, 0x1\n\
	str r1, [sp, 0x24]\n\
	lsls r2, r5, 2\n\
	str r2, [sp, 0x28]\n\
_0818F2AE:\n\
	ldr r3, [sp, 0x2C]\n\
	lsrs r0, r3, 16\n\
	bl sub_8163524\n\
	lsls r0, 16\n\
	lsrs r6, r0, 16\n\
	movs r7, 0\n\
	cmp r7, r5\n\
	bge _0818F300\n\
	ldr r0, =gSaveBlock2Ptr\n\
	ldr r0, [r0]\n\
	ldr r1, [sp, 0x8]\n\
	mov r8, r1\n\
	ldr r2, [sp, 0xC]\n\
	mov r12, r2\n\
	ldr r3, =0x00000d64\n\
	adds r0, r3\n\
	ldr r1, [sp, 0x20]\n\
	adds r4, r1, r0\n\
_0818F2D4:\n\
	ldrh r3, [r4]\n\
	cmp r3, r6\n\
	beq _0818F300\n\
	ldr r2, =gUnknown_0203BC8C\n\
	ldr r1, [r2]\n\
	lsls r0, r6, 4\n\
	adds r2, r0, r1\n\
	ldrh r0, [r2]\n\
	cmp r8, r0\n\
	beq _0818F300\n\
	cmp r12, r0\n\
	beq _0818F300\n\
	lsls r0, r3, 4\n\
	adds r0, r1\n\
	ldrb r0, [r0, 0xA]\n\
	ldrb r2, [r2, 0xA]\n\
	cmp r0, r2\n\
	beq _0818F300\n\
	adds r4, 0x2\n\
	adds r7, 0x1\n\
	cmp r7, r5\n\
	blt _0818F2D4\n\
_0818F300:\n\
	cmp r7, r5\n\
	bne _0818F2AE\n\
	ldr r3, =gSaveBlock2Ptr\n\
	ldr r0, [r3]\n\
	ldr r1, [sp, 0x38]\n\
	add r1, r9\n\
	ldr r5, =0x00000d64\n\
	adds r0, r5\n\
	adds r0, r1\n\
	strh r6, [r0]\n\
	ldr r2, [sp, 0x28]\n\
	add r2, sp\n\
	adds r2, 0x8\n\
	ldr r0, =gUnknown_0203BC8C\n\
	ldr r1, [r0]\n\
	lsls r0, r6, 4\n\
	adds r0, r1\n\
	ldrh r0, [r0]\n\
	str r0, [r2]\n\
	ldr r5, [sp, 0x24]\n\
	cmp r5, 0x2\n\
	ble _0818F2A2\n\
	ldr r2, [r3]\n\
	ldr r7, [sp, 0x34]\n\
	adds r2, r7\n\
	ldr r0, =0x00000d25\n\
	adds r2, r0\n\
	ldrb r0, [r2]\n\
	movs r3, 0x5\n\
	negs r3, r3\n\
	adds r1, r3, 0\n\
	ands r0, r1\n\
	strb r0, [r2]\n\
	ldr r5, =gSaveBlock2Ptr\n\
	ldr r2, [r5]\n\
	adds r2, r7\n\
	ldr r7, =0x00000d25\n\
	adds r2, r7\n\
	ldrb r0, [r2]\n\
	subs r3, 0x14\n\
	adds r1, r3, 0\n\
	ands r0, r1\n\
	strb r0, [r2]\n\
	ldr r1, [r5]\n\
	ldr r5, [sp, 0x34]\n\
	adds r1, r5\n\
	adds r1, r7\n\
	ldrb r2, [r1]\n\
	movs r0, 0x1F\n\
	ands r0, r2\n\
	strb r0, [r1]\n\
	adds r5, 0x4\n\
	str r5, [sp, 0x34]\n\
	ldr r7, [sp, 0x38]\n\
	adds r7, 0x6\n\
	str r7, [sp, 0x38]\n\
	movs r0, 0x1\n\
	add r10, r0\n\
	mov r1, r10\n\
	cmp r1, 0xF\n\
	bgt _0818F37C\n\
	b _0818F17E\n\
_0818F37C:\n\
	movs r7, 0\n\
	ldr r2, [sp, 0x18]\n\
	strh r7, [r2]\n\
	movs r3, 0\n\
	mov r10, r3\n\
	ldr r6, =gBitTable\n\
	ldr r5, =gBaseStats\n\
_0818F38A:\n\
	ldr r0, =gSaveBlock2Ptr\n\
	ldr r0, [r0]\n\
	mov r2, r10\n\
	lsls r1, r2, 1\n\
	ldr r3, =0x00000caa\n\
	adds r0, r3\n\
	adds r0, r1\n\
	ldrh r0, [r0]\n\
	subs r4, r0, 0x1\n\
	movs r0, 0x64\n\
	muls r4, r0\n\
	ldr r0, =gPlayerParty\n\
	adds r4, r0\n\
	adds r0, r4, 0\n\
	movs r1, 0x3B\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r2, [sp, 0x18]\n\
	ldrh r1, [r2]\n\
	adds r1, r0\n\
	strh r1, [r2]\n\
	adds r0, r4, 0\n\
	movs r1, 0x3C\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r3, [sp, 0x18]\n\
	ldrh r1, [r3]\n\
	adds r1, r0\n\
	strh r1, [r3]\n\
	adds r0, r4, 0\n\
	movs r1, 0x3E\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r2, [sp, 0x18]\n\
	ldrh r1, [r2]\n\
	adds r1, r0\n\
	strh r1, [r2]\n\
	adds r0, r4, 0\n\
	movs r1, 0x3F\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r3, [sp, 0x18]\n\
	ldrh r1, [r3]\n\
	adds r1, r0\n\
	strh r1, [r3]\n\
	adds r0, r4, 0\n\
	movs r1, 0x3D\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r2, [sp, 0x18]\n\
	ldrh r1, [r2]\n\
	adds r1, r0\n\
	strh r1, [r2]\n\
	adds r0, r4, 0\n\
	movs r1, 0x3A\n\
	movs r2, 0\n\
	bl GetMonData\n\
	ldr r3, [sp, 0x18]\n\
	ldrh r1, [r3]\n\
	adds r1, r0\n\
	strh r1, [r3]\n\
	adds r0, r4, 0\n\
	movs r1, 0xB\n\
	movs r2, 0\n\
	bl GetMonData\n\
	lsls r1, r0, 3\n\
	subs r1, r0\n\
	lsls r1, 2\n\
	adds r1, r5\n\
	ldrb r0, [r1, 0x6]\n\
	lsls r0, 2\n\
	adds r0, r6\n\
	ldr r0, [r0]\n\
	orrs r7, r0\n\
	adds r0, r4, 0\n\
	movs r1, 0xB\n\
	movs r2, 0\n\
	bl GetMonData\n\
	lsls r1, r0, 3\n\
	subs r1, r0\n\
	lsls r1, 2\n\
	adds r1, r5\n\
	ldrb r0, [r1, 0x7]\n\
	lsls r0, 2\n\
	adds r0, r6\n\
	ldr r0, [r0]\n\
	orrs r7, r0\n\
	movs r0, 0x1\n\
	add r10, r0\n\
	mov r1, r10\n\
	cmp r1, 0x2\n\
	ble _0818F38A\n\
	movs r4, 0\n\
	movs r1, 0x1\n\
	movs r5, 0x1F\n\
_0818F458:\n\
	adds r0, r7, 0\n\
	ands r0, r1\n\
	cmp r0, 0\n\
	beq _0818F462\n\
	adds r4, 0x1\n\
_0818F462:\n\
	asrs r7, 1\n\
	subs r5, 0x1\n\
	cmp r5, 0\n\
	bge _0818F458\n\
	bl sub_8165C40\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	str r0, [sp, 0x14]\n\
	adds r2, r0, 0\n\
	adds r0, r4, 0\n\
	muls r0, r2\n\
	movs r1, 0x14\n\
	bl __divsi3\n\
	ldr r3, [sp, 0x18]\n\
	ldrh r1, [r3]\n\
	adds r1, r0\n\
	strh r1, [r3]\n\
	movs r5, 0x1\n\
	mov r10, r5\n\
	adds r6, r3, 0\n\
	adds r6, 0x2\n\
	movs r7, 0x2\n\
	str r7, [sp, 0x30]\n\
_0818F494:\n\
	movs r7, 0\n\
	strh r7, [r6]\n\
	ldr r1, =gSaveBlock2Ptr\n\
	ldr r0, [r1]\n\
	mov r2, r10\n\
	lsls r1, r2, 2\n\
	adds r0, r1\n\
	ldr r3, =0x00000d24\n\
	adds r0, r3\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	lsrs r0, 22\n\
	bl sub_8190168\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	mov r8, r0\n\
	movs r5, 0\n\
	ldr r0, [sp, 0x30]\n\
	mov r9, r0\n\
_0818F4BC:\n\
	ldr r1, =gSaveBlock2Ptr\n\
	ldr r0, [r1]\n\
	mov r4, r9\n\
	add r4, r10\n\
	adds r4, r5\n\
	lsls r4, 1\n\
	ldr r2, =0x00000d64\n\
	adds r0, r2\n\
	adds r0, r4\n\
	ldrh r1, [r0]\n\
	ldr r3, =gUnknown_0203BC8C\n\
	ldr r0, [r3]\n\
	lsls r1, 4\n\
	adds r1, r0\n\
	ldrh r0, [r1]\n\
	ldrb r3, [r1, 0xB]\n\
	ldrb r1, [r1, 0xC]\n\
	str r1, [sp]\n\
	ldr r1, [sp, 0x1C]\n\
	str r1, [sp, 0x4]\n\
	ldr r1, [sp, 0x14]\n\
	mov r2, r8\n\
	bl sub_818F720\n\
	ldr r2, [sp, 0x1C]\n\
	ldr r1, [r2, 0x4]\n\
	ldrh r0, [r6]\n\
	adds r0, r1\n\
	ldr r1, [r2, 0x8]\n\
	adds r0, r1\n\
	ldr r1, [r2, 0x10]\n\
	adds r0, r1\n\
	ldr r1, [r2, 0x14]\n\
	adds r0, r1\n\
	ldr r1, [r2, 0xC]\n\
	adds r0, r1\n\
	ldr r1, [r2]\n\
	adds r0, r1\n\
	strh r0, [r6]\n\
	ldr r3, =gSaveBlock2Ptr\n\
	ldr r0, [r3]\n\
	ldr r1, =0x00000d64\n\
	adds r0, r1\n\
	adds r0, r4\n\
	ldrh r0, [r0]\n\
	ldr r2, =gUnknown_0203BC8C\n\
	ldr r1, [r2]\n\
	lsls r0, 4\n\
	adds r0, r1\n\
	ldrh r0, [r0]\n\
	lsls r1, r0, 3\n\
	subs r1, r0\n\
	lsls r1, 2\n\
	ldr r3, =gBaseStats\n\
	adds r1, r3\n\
	ldrb r0, [r1, 0x6]\n\
	lsls r0, 2\n\
	ldr r2, =gBitTable\n\
	adds r0, r2\n\
	ldr r0, [r0]\n\
	orrs r7, r0\n\
	ldrb r0, [r1, 0x7]\n\
	lsls r0, 2\n\
	adds r0, r2\n\
	ldr r0, [r0]\n\
	orrs r7, r0\n\
	adds r5, 0x1\n\
	cmp r5, 0x2\n\
	ble _0818F4BC\n\
	movs r4, 0\n\
	movs r1, 0x1\n\
	movs r5, 0x1F\n\
_0818F54C:\n\
	adds r0, r7, 0\n\
	ands r0, r1\n\
	cmp r0, 0\n\
	beq _0818F556\n\
	adds r4, 0x1\n\
_0818F556:\n\
	asrs r7, 1\n\
	subs r5, 0x1\n\
	cmp r5, 0\n\
	bge _0818F54C\n\
	ldr r3, [sp, 0x14]\n\
	adds r0, r4, 0\n\
	muls r0, r3\n\
	movs r1, 0x14\n\
	bl __divsi3\n\
	ldrh r1, [r6]\n\
	adds r1, r0\n\
	strh r1, [r6]\n\
	adds r6, 0x2\n\
	ldr r5, [sp, 0x30]\n\
	adds r5, 0x2\n\
	str r5, [sp, 0x30]\n\
	movs r7, 0x1\n\
	add r10, r7\n\
	mov r0, r10\n\
	cmp r0, 0xF\n\
	ble _0818F494\n\
	movs r1, 0\n\
	mov r10, r1\n\
	ldr r2, =0x000003ff\n\
	mov r8, r2\n\
_0818F58A:\n\
	mov r5, r10\n\
	adds r5, 0x1\n\
	adds r7, r5, 0\n\
	cmp r5, 0xF\n\
	bgt _0818F626\n\
	mov r3, r10\n\
	lsls r0, r3, 1\n\
	ldr r1, [sp, 0x18]\n\
	adds r6, r0, r1\n\
	lsls r0, r5, 1\n\
	adds r4, r0, r1\n\
_0818F5A0:\n\
	ldrh r1, [r6]\n\
	ldrh r0, [r4]\n\
	cmp r1, r0\n\
	bcc _0818F5C2\n\
	cmp r1, r0\n\
	bne _0818F61E\n\
	ldr r0, =gSaveBlock2Ptr\n\
	ldr r1, [r0]\n\
	lsls r0, r5, 2\n\
	adds r0, r1, r0\n\
	ldr r2, =0x00000d24\n\
	adds r0, r2\n\
	ldrh r0, [r0]\n\
	lsls r2, r0, 22\n\
	lsrs r0, r2, 22\n\
	cmp r0, r8\n\
	bne _0818F602\n\
_0818F5C2:\n\
	mov r0, r10\n\
	adds r1, r5, 0\n\
	ldr r2, [sp, 0x18]\n\
	bl sub_818F904\n\
	b _0818F600\n\
	.pool\n\
_0818F600:\n\
	b _0818F61E\n\
_0818F602:\n\
	mov r3, r10\n\
	lsls r0, r3, 2\n\
	adds r0, r1, r0\n\
	ldr r1, =0x00000d24\n\
	adds r0, r1\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	cmp r0, r2\n\
	bls _0818F61E\n\
	mov r0, r10\n\
	adds r1, r5, 0\n\
	ldr r2, [sp, 0x18]\n\
	bl sub_818F904\n\
_0818F61E:\n\
	adds r4, 0x2\n\
	adds r5, 0x1\n\
	cmp r5, 0xF\n\
	ble _0818F5A0\n\
_0818F626:\n\
	mov r10, r7\n\
	mov r2, r10\n\
	cmp r2, 0xE\n\
	ble _0818F58A\n\
	bl sub_81A3610\n\
	lsls r0, 24\n\
	cmp r0, 0\n\
	beq _0818F6EE\n\
	movs r3, 0\n\
	mov r10, r3\n\
	ldr r0, =gSaveBlock2Ptr\n\
	ldr r1, [r0]\n\
	ldr r4, =0x00000d24\n\
	adds r1, r4\n\
	ldrh r1, [r1]\n\
	lsls r1, 22\n\
	lsrs r1, 22\n\
	ldr r3, =0x000003ff\n\
	adds r2, r0, 0\n\
	ldr r6, =gUnknown_0860D3F1\n\
	cmp r1, r3\n\
	beq _0818F674\n\
	adds r5, r2, 0\n\
_0818F656:\n\
	movs r7, 0x1\n\
	add r10, r7\n\
	mov r0, r10\n\
	cmp r0, 0xF\n\
	bgt _0818F674\n\
	ldr r0, [r5]\n\
	mov r7, r10\n\
	lsls r1, r7, 2\n\
	adds r0, r1\n\
	adds r0, r4\n\
	ldrh r0, [r0]\n\
	lsls r0, 22\n\
	lsrs r0, 22\n\
	cmp r0, r3\n\
	bne _0818F656\n\
_0818F674:\n\
	mov r1, r10\n\
	lsls r0, r1, 1\n\
	adds r0, r6\n\
	ldrb r0, [r0]\n\
	cmp r0, 0\n\
	beq _0818F6AC\n\
	movs r5, 0\n\
	ldr r2, [r2]\n\
	ldr r3, =0x00000d24\n\
	adds r2, r3\n\
	ldrh r1, [r2]\n\
	ldr r0, =0xfffffc00\n\
	ands r0, r1\n\
	ldr r7, =0x000003fe\n\
	adds r1, r7, 0\n\
	b _0818F6BE\n\
	.pool\n\
_0818F6AC:\n\
	movs r5, 0x1\n\
	ldr r2, [r2]\n\
	ldr r0, =0x00000d28\n\
	adds r2, r0\n\
	ldrh r1, [r2]\n\
	ldr r0, =0xfffffc00\n\
	ands r0, r1\n\
	ldr r3, =0x000003fe\n\
	adds r1, r3, 0\n\
_0818F6BE:\n\
	orrs r0, r1\n\
	strh r0, [r2]\n\
	movs r7, 0\n\
	mov r10, r7\n\
	lsls r0, r5, 1\n\
	adds r0, r5\n\
	lsls r4, r0, 1\n\
_0818F6CC:\n\
	mov r1, r10\n\
	lsls r0, r1, 24\n\
	lsrs r0, 24\n\
	bl sub_81A4FF0\n\
	ldr r1, =gSaveBlock2Ptr\n\
	ldr r1, [r1]\n\
	ldr r2, =0x00000d64\n\
	adds r1, r2\n\
	adds r1, r4\n\
	strh r0, [r1]\n\
	adds r4, 0x2\n\
	movs r3, 0x1\n\
	add r10, r3\n\
	mov r5, r10\n\
	cmp r5, 0x2\n\
	ble _0818F6CC\n\
_0818F6EE:\n\
	ldr r0, [sp, 0x18]\n\
	bl Free\n\
	ldr r0, [sp, 0x1C]\n\
	bl Free\n\
	add sp, 0x3C\n\
	pop {r3-r5}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	mov r10, r5\n\
	pop {r4-r7}\n\
	pop {r0}\n\
	bx r0\n\
	.pool\n");
}
#endif

#define BUFFER_STAT(base, buffer, iv, ev, statIndex, nature)                        \
{                                                                                   \
    buffer = (((2 * gBaseStats[species].base + iv + ev / 4) * b) / 100) + 5;        \
    buffer = (u8)ModifyStatByNature(nature, buffer, statIndex);                     \
}

void sub_818F720(u16 species, int b, int c, u8 d, u8 e, u32* f)
{
    int i;
    int count = 0;
    int arr[6];
    u16 r3;
    u8 mask = d;
    int r0;
    
    for (i = 0; i < 6; i++)
    {
        if (mask & 1)
            count++;
        mask >>= 1;
    }
    
    r3 = 0x1FE / count;
    
    for (i = 0; i < 6; i++)
    {
        arr[i] = 0;
        if (d & mask)
            arr[i] = r3;
        mask <<= 1;
    }
    
    if (species == SPECIES_SHEDINJA)
        f[0] = 1;
    else
        f[0] = ((((2 * gBaseStats[species].baseHP + c) + arr[0] / 4) * b) / 100) + b + 10;
    BUFFER_STAT(baseAttack, f[1], c, arr[1], 1, e);
    BUFFER_STAT(baseDefense, f[2], c, arr[2], 2, e);
    BUFFER_STAT(baseSpeed, f[3], c, arr[3], 3, e);
    BUFFER_STAT(baseSpAttack, f[4], c, arr[4], 4, e);
    BUFFER_STAT(baseSpDefense, f[5], c, arr[5], 5, e);
}

void sub_818F904(int a, int b, u16* c)
{
    
    int i;
    int buffer;
    
    buffer = c[a];
    c[a] = c[b];
    c[b] = buffer;
    buffer = gSaveBlock2Ptr->frontierStruct2[a].field_0_a;
    gSaveBlock2Ptr->frontierStruct2[a].field_0_a = gSaveBlock2Ptr->frontierStruct2[b].field_0_a;
    gSaveBlock2Ptr->frontierStruct2[b].field_0_a = buffer;
    
    for (i = 0; i < 3; i++)
    {
        buffer = gSaveBlock2Ptr->field_D64[a][i];
        gSaveBlock2Ptr->field_D64[a][i] = gSaveBlock2Ptr->field_D64[b][i];
        gSaveBlock2Ptr->field_D64[b][i] = buffer;
    }
}

void sub_818F9B0(void)
{
    StringCopy(gStringVar1, gRoundsStringTable[gSaveBlock2Ptr->battlePyramidWildHeaderId]);
}

void sub_818F9E0(void)
{
    StringCopy(gStringVar1, gRoundsStringTable[gSaveBlock2Ptr->battlePyramidWildHeaderId]);
    sub_8195898(gStringVar2, gTrainerBattleOpponent_A);
}

void sub_818FA20(void)
{
    gUnknown_0203CD70 = 0;
    gUnknown_0203CD74 = GetMonData(&gPlayerParty[0], MON_DATA_MAX_HP, 0);
    gUnknown_0203CD74 += GetMonData(&gPlayerParty[1], MON_DATA_MAX_HP, 0);
    CalculatePlayerPartyCount();
    sub_818FBDC(sub_8195358(gTrainerBattleOpponent_A));
}

void sub_818FA74(u8 a, u16 b, u8 c, int OT)
{
    u8 friendship = 255;
    u8 IVs = sub_8190168(b);
    int i;
    
    CreateMonWithEVSpreadPersonalityOTID(&gEnemyParty[a], gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[b][c]].species, sub_8165C40(), gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[b][c]].nature, IVs, gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[b][c]].EVs, OT);
    friendship = 255; // needed to match
    
    for (i = 0; i < 4; i++)
    {
        SetMonMoveSlot(&gEnemyParty[a], gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[b][c]].move[i], i);
        if (gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[b][c]].move[i] == MOVE_FRUSTRATION)
            friendship = 0;
    }
    
    SetMonData(&gEnemyParty[a], MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(&gEnemyParty[a], MON_DATA_HELD_ITEM, &gBattleFrontierHeldItems[gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[b][c]].itemListId]);
}

void sub_818FBDC(u16 a)
{
    u8 r6 = 0;
    int r5;
    u32 OT;
    int i;
    
    ZeroEnemyPartyMons();
    r5 = sub_818FC78(a);
    OT = Random() | (Random() << 16);
    if ((Random() % 10) > 5)
    {
        for (i = 0; i < 3; i++)
        {
            if (r5 & 1)
            {
                sub_818FA74(r6, a, i, OT);
                r6++;
            }
            r5 >>= 1;
        }
    }
    else
    {
        for (i = 2; i >= 0; i--)
        {
            if (r5 & 4)
            {
                sub_818FA74(r6, a, i, OT);
                r6++;
            }
            r5 <<= 1;
        }
    }
}

int sub_818FC78(u16 a)
{
    int var;
    
    if (Random() & 1)
    {
        var = sub_818FCBC(a, 0);
        if (var != 0)
            return var;
        else
            return sub_818FDB8(a, 1);
    }
    else
    {
        var = sub_818FDB8(a, 0);
        if (var != 0)
            return var;
        else
            return sub_818FCBC(a, 1);
    }
}

int sub_818FCBC(u16 a, u8 b)
{
    int sp[3];
    int i, j, k;
    
    for (i = 0; i < 3; i++)
    {
        sp[i] = 0;
        
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 3; k++)
            {
                if (gSaveBlock2Ptr->frontierStruct2[a].field_0_a == 0x3FE)
                    sp[i] += sub_818FFC0(sub_81A5060(i, j), GetMonData(&gPlayerParty[k], MON_DATA_SPECIES, 0), 0);
                else
                    sp[i] += sub_818FFC0(gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[a][i]].move[j], GetMonData(&gPlayerParty[k], MON_DATA_SPECIES, 0), 0);
            }
        }
    }
    
    return sub_818FEB4(sp, b);
}

int sub_818FDB8(u16 a, u8 b)
{
    int sp[3];
    int i, j, k;
    
    for (i = 0; i < 3; i++)
    {
        sp[i] = 0;
        
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 3; k++)
            {
                if (gSaveBlock2Ptr->frontierStruct2[a].field_0_a == 0x3FE)
                    sp[i] += sub_818FFC0(sub_81A5060(i, j), GetMonData(&gPlayerParty[k], MON_DATA_SPECIES, 0), 1);
                else
                    sp[i] += sub_818FFC0(gUnknown_0203BC8C[gSaveBlock2Ptr->field_D64[a][i]].move[j], GetMonData(&gPlayerParty[k], MON_DATA_SPECIES, 0), 1);
            }
        }
    }
    
    return sub_818FEB4(sp, b);
}

int sub_818FEB4(int *a, u8 b)
{
    int spC = 0;
    int sp[3];
    int i, j;
    
    for (i = 2; i >= 0; i--)
        sp[i] = i;
    
    if (a[0] == a[1] && a[0] == a[2])
    {
        if (b)
        {
            for (i = 0; i != 2; i)
            {
                int rand = Random() & 3;
                if (!(rand == 3 || (spC & gBitTable[rand])))
                {
                    spC |= gBitTable[rand];
                    i++;
                }
            }
        }
    }
    else
    {
        for (i = 0; i < 2; i++)
        {
            for (j = i + 1; j < 3; j++)
            {
                int buffer;
                
                if (a[i] < a[j])
                {
                    buffer = a[i];
                    a[i] = a[j];
                    a[j] = buffer;
                    buffer = sp[i];
                    sp[i] = sp[j];
                    sp[j] = buffer;
                }
                if (!(a[i] != a[j] || !(Random() & 1)))
                {
                    buffer = a[i];
                    a[i] = a[j];
                    a[j] = buffer;
                    buffer = sp[i];
                    sp[i] = sp[j];
                    sp[j] = buffer;
                }
            }
        }
        
        for (i = 0; i <= 1; i++)
            spC |= gBitTable[sp[i]];
    }
    return spC;
}

#ifdef NONMATCHING
int sub_818FFC0(int a, int b, int c)
{
    int i = 0;
    int r2 = 20;
    int r10;
    int r9;
    int r8;
    int sp4;
    
    if (a == 0 || a == 0xFFFF || gBattleMoves[a].power == 0)
        return 0;
    r10 = gBaseStats[b].type1;
    r9 = gBaseStats[b].type2;
    r8 = gBaseStats[b].ability1;
    sp4 = gBattleMoves[a].type;
    if (r8 == ABILITY_LEVITATE && sp4 == TYPE_GROUND)
    {
        if (c == 1)
            r2 = 8;
    }
    else
    {
        while (TYPE_EFFECT_ATK_TYPE(i) != TYPE_ENDTABLE)
        {
            if ((TYPE_EFFECT_ATK_TYPE(i) == TYPE_FORESIGHT))
            {
                i += 3;
                continue;
            }
            if (TYPE_EFFECT_ATK_TYPE(i) != sp4)
            {
                i += 3;
                continue;
            }
            if ((TYPE_EFFECT_DEF_TYPE(i) == r10) && (r8 != ABILITY_WONDER_GUARD || TYPE_EFFECT_MULTIPLIER(i) == 40))
                r2 = r2 * TYPE_EFFECT_MULTIPLIER(i) / 10;
            if (!(TYPE_EFFECT_DEF_TYPE(i) == r9 || r10 != r9) && (r8 != ABILITY_WONDER_GUARD || TYPE_EFFECT_MULTIPLIER(i) == 40))
                r2 = r2 * TYPE_EFFECT_MULTIPLIER(i) / 10;
            i += 3;
        }
    }
    switch (c)
    {
        case 0:
            switch (r2)
            {
                case 10:
                default:
                case 80:
                    r2 = 0;
                    break;
                case 20:
                    r2 = 2;
                    break;
                case 40:
                    r2 = 4;
                    break;
                
            }
            break;
        case 1:
            switch (r2)
            {
                case 0:
                    r2 = 8;
                    break;
                case 5:
                    r2 = 4;
                    break;
                case 10:
                    r2 = 2;
                    break;
                case 40:
                    r2 = -2;
                    break;
                case 80:
                    r2 = -8;
                    break;
                default:
                    r2 = 0;
                    break;
            }
            break;
        case 2:
            switch (r2)
            {
                case 0:
                    r2 = -16;
                    break;
                case 5:
                    r2 = -8;
                    break;
                case 10:
                default:
                    r2 = 0;
                    break;
                case 20:
                    r2 = 4;
                    break;
                case 40:
                    r2 = 12;
                    break;
                case 80:
                    r2 = 20;
                    break;
            }
            break;
    }
    return r2;
}
#else
NAKED
int sub_818FFC0(int a, int b, int c)
{
    asm_unified("push {r4-r7,lr}\n\
	mov r7, r10\n\
	mov r6, r9\n\
	mov r5, r8\n\
	push {r5-r7}\n\
	sub sp, 0x8\n\
	adds r3, r0, 0\n\
	adds r4, r1, 0\n\
	str r2, [sp]\n\
	movs r6, 0\n\
	movs r2, 0x14\n\
	cmp r3, 0\n\
	beq _0818FFF0\n\
	ldr r0, =0x0000ffff\n\
	cmp r3, r0\n\
	beq _0818FFF0\n\
	ldr r0, =gBattleMoves\n\
	lsls r1, r3, 1\n\
	adds r1, r3\n\
	lsls r1, 2\n\
	adds r3, r1, r0\n\
	ldrb r0, [r3, 0x1]\n\
	cmp r0, 0\n\
	bne _0818FFFC\n\
_0818FFF0:\n\
	movs r0, 0\n\
	b _08190156\n\
	.pool\n\
_0818FFFC:\n\
	ldr r1, =gBaseStats\n\
	lsls r0, r4, 3\n\
	subs r0, r4\n\
	lsls r0, 2\n\
	adds r0, r1\n\
	ldrb r1, [r0, 0x6]\n\
	mov r10, r1\n\
	ldrb r1, [r0, 0x7]\n\
	mov r9, r1\n\
	ldrb r0, [r0, 0x16]\n\
	mov r8, r0\n\
	ldrb r3, [r3, 0x2]\n\
	str r3, [sp, 0x4]\n\
	cmp r0, 0x1A\n\
	bne _0819002C\n\
	cmp r3, 0x4\n\
	bne _0819002C\n\
	ldr r0, [sp]\n\
	cmp r0, 0x1\n\
	bne _081900AA\n\
	movs r2, 0x8\n\
	b _081900A4\n\
	.pool\n\
_0819002C:\n\
	ldr r0, =gTypeEffectiveness\n\
	adds r1, r6, r0\n\
	ldrb r0, [r1]\n\
	ldr r7, =gTypeEffectiveness\n\
	cmp r0, 0xFF\n\
	beq _081900A4\n\
	adds r4, r1, 0\n\
_0819003A:\n\
	ldrb r0, [r4]\n\
	cmp r0, 0xFE\n\
	beq _08190096\n\
	ldrb r0, [r4]\n\
	ldr r1, [sp, 0x4]\n\
	cmp r0, r1\n\
	bne _08190096\n\
	ldrb r0, [r4, 0x1]\n\
	adds r5, r6, 0x1\n\
	cmp r0, r10\n\
	bne _0819006C\n\
	adds r1, r6, 0x2\n\
	mov r0, r8\n\
	cmp r0, 0x19\n\
	bne _0819005E\n\
	ldrb r0, [r4, 0x2]\n\
	cmp r0, 0x28\n\
	bne _0819006C\n\
_0819005E:\n\
	adds r0, r1, r7\n\
	ldrb r0, [r0]\n\
	muls r0, r2\n\
	movs r1, 0xA\n\
	bl __divsi3\n\
	adds r2, r0, 0\n\
_0819006C:\n\
	adds r0, r5, r7\n\
	ldrb r0, [r0]\n\
	cmp r0, r9\n\
	bne _08190096\n\
	cmp r10, r9\n\
	beq _08190096\n\
	adds r1, r6, 0x2\n\
	mov r0, r8\n\
	cmp r0, 0x19\n\
	bne _08190088\n\
	adds r0, r1, r7\n\
	ldrb r0, [r0]\n\
	cmp r0, 0x28\n\
	bne _08190096\n\
_08190088:\n\
	adds r0, r1, r7\n\
	ldrb r0, [r0]\n\
	muls r0, r2\n\
	movs r1, 0xA\n\
	bl __divsi3\n\
	adds r2, r0, 0\n\
_08190096:\n\
	adds r4, 0x3\n\
	adds r6, 0x3\n\
	ldr r1, =gTypeEffectiveness\n\
	adds r0, r6, r1\n\
	ldrb r0, [r0]\n\
	cmp r0, 0xFF\n\
	bne _0819003A\n\
_081900A4:\n\
	ldr r0, [sp]\n\
	cmp r0, 0x1\n\
	beq _081900E0\n\
_081900AA:\n\
	ldr r1, [sp]\n\
	cmp r1, 0x1\n\
	bgt _081900BC\n\
	cmp r1, 0\n\
	beq _081900C4\n\
	b _08190154\n\
	.pool\n\
_081900BC:\n\
	ldr r0, [sp]\n\
	cmp r0, 0x2\n\
	beq _08190114\n\
	b _08190154\n\
_081900C4:\n\
	cmp r2, 0xA\n\
	beq _08190146\n\
	cmp r2, 0xA\n\
	ble _08190146\n\
	cmp r2, 0x28\n\
	beq _0819014A\n\
	cmp r2, 0x28\n\
	bgt _081900DA\n\
	cmp r2, 0x14\n\
	beq _08190104\n\
	b _08190146\n\
_081900DA:\n\
	cmp r2, 0x50\n\
	bne _08190146\n\
	b _08190100\n\
_081900E0:\n\
	cmp r2, 0xA\n\
	beq _08190104\n\
	cmp r2, 0xA\n\
	bgt _081900F2\n\
	cmp r2, 0\n\
	beq _08190100\n\
	cmp r2, 0x5\n\
	beq _0819014A\n\
	b _08190146\n\
_081900F2:\n\
	cmp r2, 0x28\n\
	beq _08190108\n\
	cmp r2, 0x28\n\
	ble _08190146\n\
	cmp r2, 0x50\n\
	beq _0819010E\n\
	b _08190146\n\
_08190100:\n\
	movs r2, 0x8\n\
	b _08190154\n\
_08190104:\n\
	movs r2, 0x2\n\
	b _08190154\n\
_08190108:\n\
	movs r2, 0x2\n\
	negs r2, r2\n\
	b _08190154\n\
_0819010E:\n\
	movs r2, 0x4\n\
	negs r2, r2\n\
	b _08190154\n\
_08190114:\n\
	cmp r2, 0xA\n\
	beq _08190146\n\
	cmp r2, 0xA\n\
	bgt _08190126\n\
	cmp r2, 0\n\
	beq _0819013A\n\
	cmp r2, 0x5\n\
	beq _08190140\n\
	b _08190146\n\
_08190126:\n\
	cmp r2, 0x28\n\
	beq _0819014E\n\
	cmp r2, 0x28\n\
	bgt _08190134\n\
	cmp r2, 0x14\n\
	beq _0819014A\n\
	b _08190146\n\
_08190134:\n\
	cmp r2, 0x50\n\
	beq _08190152\n\
	b _08190146\n\
_0819013A:\n\
	movs r2, 0x10\n\
	negs r2, r2\n\
	b _08190154\n\
_08190140:\n\
	movs r2, 0x8\n\
	negs r2, r2\n\
	b _08190154\n\
_08190146:\n\
	movs r2, 0\n\
	b _08190154\n\
_0819014A:\n\
	movs r2, 0x4\n\
	b _08190154\n\
_0819014E:\n\
	movs r2, 0xC\n\
	b _08190154\n\
_08190152:\n\
	movs r2, 0x14\n\
_08190154:\n\
	adds r0, r2, 0\n\
_08190156:\n\
	add sp, 0x8\n\
	pop {r3-r5}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	mov r10, r5\n\
	pop {r4-r7}\n\
	pop {r1}\n\
	bx r1\n");
}
#endif

u8 sub_8190168(u16 a)
{
    u8 r1 = 3;
    if (a > 0x63)
    {
        r1 = 6;
        if (a > 0x77)
        {
            r1 = 9;
            if (a > 0x8B)
            {
                r1 = 12;
                if (a > 0x9F)
                {
                    r1 = 15;
                    if (a > 0xB3)
                    {
                        r1 = 18;
                        if (a > 0xC7)
                        {
                            r1 = 31;
                            if (a <= 0xDB)
                                r1 = 21;
                        }
                    }
                }
            }
        }
    }
    return r1;
}

int sub_81901A0(int a, int b)
{
    int i;
    int r4;
    int r2;
    
    for (i = 0; i < 16 && gSaveBlock2Ptr->frontierStruct2[i].field_0_a != b; i++)
        ;
    
    if (a)
    {
        if (a == 3)
            r4 = gUnknown_0860D10C[i][a] + 8;
        else
            r4 = gUnknown_0860D10C[i][a] + 4;
        r2 = gUnknown_0860D10C[i][a];
        
        while (r2 < r4 && (gUnknown_0860D14C[r2] == i || gSaveBlock2Ptr->frontierStruct2[gUnknown_0860D14C[r2]].field_0_b != 0))
            r2++;
        
        if (r2 != r4)
            return gUnknown_0860D14C[r2];
        else
            return 0xFF;
    }
    else
    {
        if (gSaveBlock2Ptr->frontierStruct2[gUnknown_0860D10C[i][0]].field_0_b == 0)
            return gUnknown_0860D10C[i][0];
        else
            return 0xFF;
    }
}

void sub_8190298(void)
{
    gTrainerBattleOpponent_A = sub_81902AC();
}

u16 sub_81902AC(void)
{
    return gSaveBlock2Ptr->frontierStruct2[sub_81901A0(gSaveBlock2Ptr->battlePyramidWildHeaderId, 0x3FF)].field_0_a;
}

void sub_81902E4(void)
{
    sub_8162614(gTrainerBattleOpponent_A, 0);
}

void sub_81902F8(void)
{
    gSaveBlock2Ptr->field_CA8 = gSpecialVar_0x8005;
    VarSet(0x4000, 0);
    gSaveBlock2Ptr->field_CA9_a = 1;
    sub_81A4C30();
}

void sub_819033C(void)
{
    u8 r4 = gSaveBlock2Ptr->frontierChosenLvl;
    u8 var = VarGet(0x40CE);
    
    if (gSaveBlock2Ptr->field_D0C[var][r4] <= 0x3E6)
        gSaveBlock2Ptr->field_D0C[var][r4]++;
    if (gSaveBlock2Ptr->field_D1C[var][r4] <= 0x3E6)
        gSaveBlock2Ptr->field_D1C[var][r4]++;
    if (gSaveBlock2Ptr->field_D0C[var][r4] > gSaveBlock2Ptr->field_D14[var][r4])
        gSaveBlock2Ptr->field_D14[var][r4] = gSaveBlock2Ptr->field_D0C[var][r4];
}

void sub_81903B8(void)
{
    u8 taskId = CreateTask(sub_8190400, 0);
    
    gTasks[taskId].data[0] = 0;
    gTasks[taskId].data[1] = sub_8195358(sub_81902AC());
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[3] = 0;
    SetMainCallback2(sub_8194B54);
}

#ifdef NONMATCHING
void sub_8190400(u8 taskId)
{
    int r5 = gTasks[taskId].data[1];
    int r9 = gTasks[taskId].data[2];
    int r7 = gTasks[taskId].data[3];
    int i;
    u8 taskId2;
    u8 spriteId;
    struct Sprite *sprite;
    
    switch (gTasks[taskId].data[0])
    {
        case 0:
            SetHBlankCallback(NULL);
            SetVBlankCallback(NULL);
            EnableInterrupts(1);
            CpuFill32(0, (void *)VRAM, 0x18000);
            ResetBgsAndClearDma3BusyFlags(0);
            InitBgsFromTemplates(0, gUnknown_0860CE84, 4);
            InitWindows(gUnknown_0860CEB4);
            DeactivateAllTextPrinters();
            gBattle_BG0_X = 0;
            gBattle_BG0_Y = 0;
            gBattle_BG1_X = 0;
            gBattle_BG1_Y = 0;
            gBattle_BG3_X = 0;
            gBattle_BG3_Y = 0;
            if (r9 == 2)
            {
                gBattle_BG2_X = 0;
                gBattle_BG2_Y = 0;
            }
            else
            {
                gBattle_BG2_X = 0;
                gBattle_BG2_Y = 0xA0;
            }
            gTasks[taskId].data[0]++;
            break;
        case 1:
            SetGpuReg(REG_OFFSET_BLDCNT, 0);
            SetGpuReg(REG_OFFSET_BLDALPHA, 0);
            SetGpuReg(REG_OFFSET_BLDY, 0);
            SetGpuReg(REG_OFFSET_MOSAIC, 0);
            SetGpuReg(REG_OFFSET_WIN0H, 0);
            SetGpuReg(REG_OFFSET_WIN0V, 0);
            SetGpuReg(REG_OFFSET_WIN1H, 0);
            SetGpuReg(REG_OFFSET_WIN1V, 0);
            SetGpuReg(REG_OFFSET_WININ, 0);
            SetGpuReg(REG_OFFSET_WINOUT, 0x3F);
            ResetPaletteFade();
            ResetSpriteData();
            FreeAllSpritePalettes();
            gReservedSpritePaletteCount = 4;
            gTasks[taskId].data[0]++;
            break;
        case 2:
            copy_decompressed_tile_data_to_vram_autofree(2, gUnknown_08D83D50, 0x2000, 0, 0);
            copy_decompressed_tile_data_to_vram_autofree(2, gUnknown_08D84970, 0x2000, 0, 1);
            copy_decompressed_tile_data_to_vram_autofree(3, gUnknown_08D84F00, 0x800, 0, 1);
            LoadCompressedObjectPic(gUnknown_0860CF50);
            LoadCompressedPalette(gUnknown_08D85358, 0, 0x200);
            LoadCompressedPalette(gUnknown_08D85444, 0x100, 0x200);
            LoadCompressedPalette(gUnknown_08D85600, 0xF0, 0x20);
            if (r9 == 2)
                LoadCompressedPalette(gUnknown_08D854C8, 0x50, 0x20);
            CpuFill32(0, gPlttBufferFaded, 0x400);
            ShowBg(0);
            ShowBg(1);
            ShowBg(2);
            ShowBg(3);
            gTasks[taskId].data[0]++;
            break;
        case 3:
            SetVBlankCallback(sub_8194B70);
            gUnknown_0203CD78 = AllocZeroed(sizeof(struct Unk190400));
            
            for (i = 0; i < 16; i++)
                gUnknown_0203CD78->unk_0[i] |= 0xFF;
            
            LoadMonIconPalettes();
            taskId2 = CreateTask(sub_8190CD4, 0);
            gTasks[taskId2].data[0] = 0;
            gTasks[taskId2].data[2] = 0;
            gTasks[taskId2].data[3] = r9;
            gTasks[taskId2].data[4] = r7;
            if (r9 == 2)
            {
                sub_819314C(0, r5);
                gUnknown_0203CD78->unk_10 = 1;
            }
            else
            {
                sub_81924E0(0, r5);
            }
            SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_BG_ALL_ON | DISPCNT_OBJ_1D_MAP);
            if (r9)
            {
                spriteId = CreateSprite(&gUnknown_0860D068, 0x78, 4, 0);
                StartSpriteAnim(&gSprites[spriteId], 0);
                gSprites[spriteId].data[0] = taskId2;
                spriteId = CreateSprite(&gUnknown_0860D068, 0x78, 0x9C, 0);
                StartSpriteAnim(&gSprites[spriteId], 1);
                gSprites[spriteId].data[0] = taskId2;
                spriteId = CreateSprite(&gUnknown_0860D050, 6, 0x50, 0);
                StartSpriteAnim(&gSprites[spriteId], 0);
                gSprites[spriteId].data[0] = taskId2;
                gSprites[spriteId].data[1] = 0;
                if (r9 == 1)
                    gSprites[spriteId].invisible = 1;
                spriteId = CreateSprite(&gUnknown_0860D050, 0xEA, 0x50, 0);
                StartSpriteAnim(&gSprites[spriteId], 1);
                gSprites[spriteId].data[0] = taskId2;
                gSprites[spriteId].data[1] = 1;
            }
            DestroyTask(taskId);
            break;
    }
}
#else
NAKED
void sub_8190400(u8 taskId)
{
    asm_unified("push {r4-r7,lr}\n\
	mov r7, r10\n\
	mov r6, r9\n\
	mov r5, r8\n\
	push {r5-r7}\n\
	sub sp, 0xC\n\
	lsls r0, 24\n\
	lsrs r0, 24\n\
	mov r10, r0\n\
	ldr r1, =gTasks\n\
	lsls r0, 2\n\
	add r0, r10\n\
	lsls r0, 3\n\
	adds r6, r0, r1\n\
	movs r0, 0xA\n\
	ldrsh r5, [r6, r0]\n\
	movs r2, 0xC\n\
	ldrsh r1, [r6, r2]\n\
	mov r9, r1\n\
	movs r0, 0xE\n\
	ldrsh r7, [r6, r0]\n\
	movs r1, 0x8\n\
	ldrsh r4, [r6, r1]\n\
	cmp r4, 0x1\n\
	beq _08190508\n\
	cmp r4, 0x1\n\
	bgt _08190440\n\
	cmp r4, 0\n\
	beq _0819044E\n\
	b _08190772\n\
	.pool\n\
_08190440:\n\
	cmp r4, 0x2\n\
	bne _08190446\n\
	b _08190570\n\
_08190446:\n\
	cmp r4, 0x3\n\
	bne _0819044C\n\
	b _08190634\n\
_0819044C:\n\
	b _08190772\n\
_0819044E:\n\
	movs r0, 0\n\
	bl SetHBlankCallback\n\
	movs r0, 0\n\
	bl SetVBlankCallback\n\
	movs r0, 0x1\n\
	bl EnableInterrupts\n\
	str r4, [sp, 0x4]\n\
	movs r1, 0xC0\n\
	lsls r1, 19\n\
	ldr r2, =0x05006000\n\
	add r0, sp, 0x4\n\
	bl CpuSet\n\
	movs r0, 0\n\
	bl ResetBgsAndClearDma3BusyFlags\n\
	ldr r1, =gUnknown_0860CE84\n\
	movs r0, 0\n\
	movs r2, 0x4\n\
	bl InitBgsFromTemplates\n\
	ldr r0, =gUnknown_0860CEB4\n\
	bl InitWindows\n\
	bl DeactivateAllTextPrinters\n\
	ldr r0, =gBattle_BG0_X\n\
	strh r4, [r0]\n\
	ldr r0, =gBattle_BG0_Y\n\
	strh r4, [r0]\n\
	ldr r0, =gBattle_BG1_X\n\
	strh r4, [r0]\n\
	ldr r0, =gBattle_BG1_Y\n\
	strh r4, [r0]\n\
	ldr r0, =gBattle_BG3_X\n\
	strh r4, [r0]\n\
	ldr r0, =gBattle_BG3_Y\n\
	strh r4, [r0]\n\
	mov r2, r9\n\
	cmp r2, 0x2\n\
	bne _081904DC\n\
	ldr r0, =gBattle_BG2_X\n\
	strh r4, [r0]\n\
	ldr r0, =gBattle_BG2_Y\n\
	strh r4, [r0]\n\
	b _081904E6\n\
	.pool\n\
_081904DC:\n\
	ldr r0, =gBattle_BG2_X\n\
	strh r4, [r0]\n\
	ldr r1, =gBattle_BG2_Y\n\
	movs r0, 0xA0\n\
	strh r0, [r1]\n\
_081904E6:\n\
	ldr r0, =gTasks\n\
	mov r2, r10\n\
	lsls r1, r2, 2\n\
	add r1, r10\n\
	lsls r1, 3\n\
	adds r1, r0\n\
	ldrh r0, [r1, 0x8]\n\
	adds r0, 0x1\n\
	strh r0, [r1, 0x8]\n\
	b _08190772\n\
	.pool\n\
_08190508:\n\
	movs r0, 0x50\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x52\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x54\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x4C\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x40\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x44\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x42\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x46\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x48\n\
	movs r1, 0\n\
	bl SetGpuReg\n\
	movs r0, 0x4A\n\
	movs r1, 0x3F\n\
	bl SetGpuReg\n\
	bl ResetPaletteFade\n\
	bl ResetSpriteData\n\
	bl FreeAllSpritePalettes\n\
	ldr r1, =gReservedSpritePaletteCount\n\
	movs r0, 0x4\n\
	strb r0, [r1]\n\
	b _08190602\n\
	.pool\n\
_08190570:\n\
	ldr r1, =gUnknown_08D83D50\n\
	movs r5, 0x80\n\
	lsls r5, 6\n\
	movs r7, 0\n\
	str r7, [sp]\n\
	movs r0, 0x2\n\
	adds r2, r5, 0\n\
	movs r3, 0\n\
	bl copy_decompressed_tile_data_to_vram_autofree\n\
	ldr r1, =gUnknown_08D84970\n\
	movs r4, 0x1\n\
	str r4, [sp]\n\
	movs r0, 0x2\n\
	adds r2, r5, 0\n\
	movs r3, 0\n\
	bl copy_decompressed_tile_data_to_vram_autofree\n\
	ldr r1, =gUnknown_08D84F00\n\
	movs r2, 0x80\n\
	lsls r2, 4\n\
	str r4, [sp]\n\
	movs r0, 0x3\n\
	movs r3, 0\n\
	bl copy_decompressed_tile_data_to_vram_autofree\n\
	ldr r0, =gUnknown_0860CF50\n\
	bl LoadCompressedObjectPic\n\
	ldr r0, =gUnknown_08D85358\n\
	movs r4, 0x80\n\
	lsls r4, 2\n\
	movs r1, 0\n\
	adds r2, r4, 0\n\
	bl LoadCompressedPalette\n\
	ldr r0, =gUnknown_08D85444\n\
	movs r1, 0x80\n\
	lsls r1, 1\n\
	adds r2, r4, 0\n\
	bl LoadCompressedPalette\n\
	ldr r0, =gUnknown_08D85600\n\
	movs r1, 0xF0\n\
	movs r2, 0x20\n\
	bl LoadCompressedPalette\n\
	mov r0, r9\n\
	cmp r0, 0x2\n\
	bne _081905DE\n\
	ldr r0, =gUnknown_08D854C8\n\
	movs r1, 0x50\n\
	movs r2, 0x20\n\
	bl LoadCompressedPalette\n\
_081905DE:\n\
	str r7, [sp, 0x8]\n\
	add r0, sp, 0x8\n\
	ldr r1, =gPlttBufferFaded\n\
	ldr r2, =0x05000100\n\
	bl CpuSet\n\
	movs r0, 0\n\
	bl ShowBg\n\
	movs r0, 0x1\n\
	bl ShowBg\n\
	movs r0, 0x2\n\
	bl ShowBg\n\
	movs r0, 0x3\n\
	bl ShowBg\n\
_08190602:\n\
	ldrh r0, [r6, 0x8]\n\
	adds r0, 0x1\n\
	strh r0, [r6, 0x8]\n\
	b _08190772\n\
	.pool\n\
_08190634:\n\
	ldr r0, =sub_8194B70\n\
	bl SetVBlankCallback\n\
	ldr r4, =gUnknown_0203CD78\n\
	movs r0, 0x14\n\
	bl AllocZeroed\n\
	str r0, [r4]\n\
	movs r6, 0\n\
	lsls r5, 24\n\
	movs r2, 0xFF\n\
_0819064A:\n\
	ldr r1, [r4]\n\
	adds r1, r6\n\
	ldrb r0, [r1]\n\
	orrs r0, r2\n\
	strb r0, [r1]\n\
	adds r6, 0x1\n\
	cmp r6, 0xF\n\
	ble _0819064A\n\
	bl LoadMonIconPalettes\n\
	ldr r0, =sub_8190CD4\n\
	movs r1, 0\n\
	bl CreateTask\n\
	lsls r0, 24\n\
	lsrs r6, r0, 24\n\
	ldr r1, =gTasks\n\
	lsls r0, r6, 2\n\
	adds r0, r6\n\
	lsls r0, 3\n\
	adds r0, r1\n\
	movs r1, 0\n\
	strh r1, [r0, 0x8]\n\
	strh r1, [r0, 0xC]\n\
	mov r1, r9\n\
	strh r1, [r0, 0xE]\n\
	strh r7, [r0, 0x10]\n\
	mov r2, r9\n\
	cmp r2, 0x2\n\
	bne _081906A8\n\
	lsrs r1, r5, 24\n\
	movs r0, 0\n\
	bl sub_819314C\n\
	ldr r0, =gUnknown_0203CD78\n\
	ldr r1, [r0]\n\
	movs r0, 0x1\n\
	strb r0, [r1, 0x10]\n\
	b _081906B0\n\
	.pool\n\
_081906A8:\n\
	lsrs r1, r5, 24\n\
	movs r0, 0\n\
	bl sub_81924E0\n\
_081906B0:\n\
	movs r1, 0xFA\n\
	lsls r1, 5\n\
	movs r0, 0\n\
	bl SetGpuReg\n\
	mov r0, r9\n\
	cmp r0, 0\n\
	beq _0819076C\n\
	ldr r5, =gUnknown_0860D068\n\
	adds r0, r5, 0\n\
	movs r1, 0x78\n\
	movs r2, 0x4\n\
	movs r3, 0\n\
	bl CreateSprite\n\
	lsls r0, 24\n\
	lsrs r7, r0, 24\n\
	lsls r4, r7, 4\n\
	adds r4, r7\n\
	lsls r4, 2\n\
	ldr r1, =gSprites\n\
	mov r8, r1\n\
	add r4, r8\n\
	adds r0, r4, 0\n\
	movs r1, 0\n\
	bl StartSpriteAnim\n\
	strh r6, [r4, 0x2E]\n\
	adds r0, r5, 0\n\
	movs r1, 0x78\n\
	movs r2, 0x9C\n\
	movs r3, 0\n\
	bl CreateSprite\n\
	lsls r0, 24\n\
	lsrs r7, r0, 24\n\
	lsls r4, r7, 4\n\
	adds r4, r7\n\
	lsls r4, 2\n\
	add r4, r8\n\
	adds r0, r4, 0\n\
	movs r1, 0x1\n\
	bl StartSpriteAnim\n\
	strh r6, [r4, 0x2E]\n\
	ldr r5, =gUnknown_0860D050\n\
	adds r0, r5, 0\n\
	movs r1, 0x6\n\
	movs r2, 0x50\n\
	movs r3, 0\n\
	bl CreateSprite\n\
	lsls r0, 24\n\
	lsrs r7, r0, 24\n\
	lsls r0, r7, 4\n\
	adds r0, r7\n\
	lsls r0, 2\n\
	mov r2, r8\n\
	adds r4, r0, r2\n\
	adds r0, r4, 0\n\
	movs r1, 0\n\
	bl StartSpriteAnim\n\
	strh r6, [r4, 0x2E]\n\
	movs r0, 0\n\
	strh r0, [r4, 0x30]\n\
	mov r1, r9\n\
	cmp r1, 0x1\n\
	bne _08190746\n\
	adds r0, r4, 0\n\
	adds r0, 0x3E\n\
	ldrb r1, [r0]\n\
	movs r2, 0x4\n\
	orrs r1, r2\n\
	strb r1, [r0]\n\
_08190746:\n\
	adds r0, r5, 0\n\
	movs r1, 0xEA\n\
	movs r2, 0x50\n\
	movs r3, 0\n\
	bl CreateSprite\n\
	lsls r0, 24\n\
	lsrs r7, r0, 24\n\
	lsls r4, r7, 4\n\
	adds r4, r7\n\
	lsls r4, 2\n\
	add r4, r8\n\
	adds r0, r4, 0\n\
	movs r1, 0x1\n\
	bl StartSpriteAnim\n\
	strh r6, [r4, 0x2E]\n\
	movs r0, 0x1\n\
	strh r0, [r4, 0x30]\n\
_0819076C:\n\
	mov r0, r10\n\
	bl DestroyTask\n\
_08190772:\n\
	add sp, 0xC\n\
	pop {r3-r5}\n\
	mov r8, r3\n\
	mov r9, r4\n\
	mov r10, r5\n\
	pop {r4-r7}\n\
	pop {r0}\n\
	bx r0\n\
	.pool\n");
}
#endif
