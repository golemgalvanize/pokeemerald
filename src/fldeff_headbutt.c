#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_camera.h"
#include "field_effect.h"
#include "fldeff.h"
#include "party_menu.h"
#include "random.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/songs.h"

struct HeadbuttItemData
{
    u8 mapGroup;
    u8 mapNum;
    u16 dropRate;
    u16 items[5];
};

void HeadbuttFunc1(u8);
void DoHeadbuttShakingEffect(void);
void HeadbuttShakingEffect(u8);
void HeadbuttFunc2(u8);

const struct HeadbuttItemData gHeadbuttItems[] =
{
    {
        .mapGroup = MAP_GROUP(ROUTE101),
        .mapNum = MAP_NUM(ROUTE101), 
        .dropRate = 100,
        .items = {ITEM_STICK, ITEM_STICK, ITEM_STICK, ITEM_STICK, ITEM_STICK,},
    },
    
    {
        .mapGroup = MAP_GROUP(OLDALE_TOWN),
        .mapNum = MAP_NUM(OLDALE_TOWN), 
        .dropRate = 100,
        .items = {ITEM_ORAN_BERRY, ITEM_ORAN_BERRY, ITEM_ORAN_BERRY, ITEM_ORAN_BERRY, ITEM_ORAN_BERRY,},
    },
};

u8 FldEff_UseHeadbutt(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext1_SetupScript(FieryPath_EventScript_2908FD);
}

bool8 HeadbuttInit(void)
{
    u8 taskId = oei_task_add();
    gTasks[taskId].data[8] = (u32)DoHeadbuttShakingEffect >> 16;
    gTasks[taskId].data[9] = (u32)DoHeadbuttShakingEffect;
    GetMonNickname(&gPlayerParty[gFieldEffectArguments[0]], gStringVar1);
    return FALSE;
}

/* void HeadbuttFunc1(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_HEADBUTT);
    EnableBothScriptContexts();
} */

void DoHeadbuttShakingEffect(void)
{
    u8 taskId = CreateTask(HeadbuttShakingEffect, 9);

    gTasks[taskId].data[1] = 0;
    gTasks[taskId].data[2] = 0;
    gTasks[taskId].data[4] = 5;
    gTasks[taskId].data[5] = 4;
    gTasks[taskId].data[6] = 8;
    SetCameraPanningCallback(0);
    PlaySE(SE_W233B);
}

void HeadbuttShakingEffect(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    task->data[1]++;

    if (!(task->data[1] % task->data[5]))
    {
        task->data[1] = 0;
        task->data[2]++;
        task->data[4] = -task->data[4];
        /* if (task->data[2] == 25)
        {
            if (task->data[4] < 0)
                task->data[4]++;
            else
                task->data[4]--;
        } */
        SetCameraPanning(0, task->data[4]);
        if (task->data[2] == task->data[6])
        {
            InstallCameraPanAheadCallback();
            task->func = HeadbuttFunc1;
        }
    }
}

void HeadbuttFunc1(u8 taskId)
{
    struct EventObject *player = &gEventObjects[gPlayerAvatar.eventObjectId];
    
    gFieldEffectArguments[0] = player->currentCoords.x;
    gFieldEffectArguments[1] = player->currentCoords.y;
    MoveCoords(player->facingDirection, (s16 *)&gFieldEffectArguments[0], (s16 *)&gFieldEffectArguments[1]);
    gFieldEffectArguments[2] = player->previousElevation;
    gFieldEffectArguments[3] = gSprites[player->spriteId].oam.priority;
    FieldEffectStart(FLDEFF_DUST);
    gTasks[taskId].func = HeadbuttFunc2;
}

void HeadbuttFunc2(u8 taskId)
{
    if (!FieldEffectActiveListContains(FLDEFF_DUST))
    {
        DestroyTask(taskId);
        FieldEffectActiveListRemove(FLDEFF_USE_HEADBUTT);
        EnableBothScriptContexts();
    }
}

void HeadbuttFunc3(void)
{
    u16 rng;
    u16 i;
    
    for (i = 0; i < ARRAY_COUNT(gHeadbuttItems); i++)
    {
        if (gHeadbuttItems[i].mapGroup == gSaveBlock1Ptr->location.mapGroup &&
            gHeadbuttItems[i].mapNum == gSaveBlock1Ptr->location.mapNum)
            break;
    }
    if (i == ARRAY_COUNT(gHeadbuttItems))
    {
        gSpecialVar_0x8004 = ITEM_NONE;
    }
    else
    {
        rng = Random2() % 100;
        if (rng < gHeadbuttItems[i].dropRate)
        {
            rng = Random2() % 100;
            if (rng < 60)                  // 60% chance
                gSpecialVar_0x8004 = gHeadbuttItems[i].items[0];
            else if (rng >= 60 && rng < 90)    // 30% chance
                gSpecialVar_0x8004 = gHeadbuttItems[i].items[1];
            else if (rng >= 90 && rng < 95)    // 5% chance
                gSpecialVar_0x8004 = gHeadbuttItems[i].items[2];
            else if (rng >= 95 && rng < 99)    // 4% chance
                gSpecialVar_0x8004 = gHeadbuttItems[i].items[3];
            else                            // 1% chance
                gSpecialVar_0x8004 = gHeadbuttItems[i].items[4];
        }
        else
        {
            gSpecialVar_0x8004 = ITEM_NONE;
        }
    }
}
