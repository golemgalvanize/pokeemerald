#include "global.h"
#include "battle.h"
#include "battle_frontier_2.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "event_data.h"
#include "malloc.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokemon.h"

struct UnkEWRamStruct
{
  u16 filler0[4];  
};

extern struct UnkEWRamStruct gUnknown_0203BC8C[];
extern u8 gUnknown_0203CEF8[];

extern void (*const gUnknown_0860D090[])(void);
extern u32 gUnknown_0860D0EC[][2];
extern u32 gUnknown_0860D0FC[][2];

struct Unk18F02C_1
{
    u8 filler[0x20];
};

struct Unk18F02C_2
{
    u8 filler[0x18];
};

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
/* THIS IS PROBABLY I N C R E D I B L Y INACCURATE

void sub_818F02C(void)
{
    int sp8 = 0;
    int spC = 0;
    int sp10 = 0;
    struct Unk18F02C_1 *sp18 = AllocZeroed(sizeof(struct Unk18F02C_1));
    struct Unk18F02C_2 *sp1C = AllocZeroed(sizeof(struct Unk18F02C_2));
    int i;
    int j;
    int k;
    
    gSaveBlock2Ptr->field_D0A = gSaveBlock2Ptr->frontierChosenLvl + 1;
    gSaveBlock2Ptr->field_D0B = VarGet(0x40CE) + 1;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_a = 0x3FF;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_b = 0;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_c = 0;
    gSaveBlock2Ptr->frontierStruct2[0].field_0_d = 0;
    
    for (i = 0; i <= 2; i++)
    {
        gSaveBlock2Ptr->field_D64[i] = GetMonData(gSaveBlock2Ptr->field_CAA[i] * sizeof(struct Pokemon) + &gBattleScripting.atk49_state, MON_DATA_SPECIES, 0);
        
        for (j = 0; j <= 3; j++)
            gSaveBlock2Ptr->frontierStruct[i].move[j] = GetMonData(gSaveBlock2Ptr->field_CAA[i] * sizeof(struct Pokemon) + &gBattleScripting.atk49_state, MON_DATA_MOVE1 + j, 0);
        
        for (j = 0; j <= 5; j++)
            gSaveBlock2Ptr->frontierStruct[i].ev[j] = GetMonData(gSaveBlock2Ptr->field_CAA[i] * sizeof(struct Pokemon) + &gBattleScripting.atk49_state, MON_DATA_HP_EV + j, 0);
        
        gSaveBlock2Ptr->frontierStruct[i].nature = GetNature((struct Pokemon*)(gSaveBlock2Ptr->field_CAA[i] * sizeof(struct Pokemon) + &gBattleScripting.atk49_state));
    }
    
    for (i = 1; i <= 15; i++)
    {
        u16 r4;
        u16 r6;
        
        if (i > 5)
        {
            while (k != i)
            {
                r4 = sub_8162548(sub_81A39C4(), 0);
                
                for (k = 1; k < i && gSaveBlock2Ptr->frontierStruct2[k].field_0_a != r4; k++)
                    ;
            }
            
            gSaveBlock2Ptr->frontierStruct2[1].field_0_a = r4;
        }
        else
        {
            while (k != i)
            {
                r4 = sub_8162548(sub_81A39C4() + 1, 0);
                
                for (k = 1; k < i && gSaveBlock2Ptr->frontierStruct2[k].field_0_a != r4; k++)
                    ;
            }
            
            gSaveBlock2Ptr->frontierStruct2[1].field_0_a = r4;
        }
        
        for (j = 0; j <= 2; j++)
        {
            
            while (k != j)
            {
                r6 = sub_8163524(r4);
                
                for (k = 0; k < j; k++)
                {
                    if (gSaveBlock2Ptr->field_D64[3 + k] != r6)
                        break;
                }
            }
        }
    }
} */
