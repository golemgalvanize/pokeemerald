#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_camera.h"
#include "field_effect.h"
#include "party_menu.h"
#include "rom6.h"
#include "script.h"
#include "string_util.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/field_effects.h"

void HeadbuttFunc1(u8);
void DoHeadbuttShakingEffect(void);
void HeadbuttShakingEffect(u8);
void HeadbuttFunc2(u8);

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
