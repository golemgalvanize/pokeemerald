#include "global.h"
#include "alloc.h"
#include "bg.h"
#include "data2.h"
#include "field_message_box.h"
#include "graphics.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "pokedex.h"
#include "pokemon.h"
#include "scanline_effect.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/species.h"

struct TestUIStruct
{
    MainCallback returnCallback;
    u8 indexId;
    u8 spriteId;
    u8 windowId;
    u16 tilemapBuffer[0x400];
    u16 bandAid[0x400];
};

static EWRAM_DATA struct TestUIStruct *UIStructPtr = NULL;
static EWRAM_DATA u8 *tilemap = NULL;

const struct BgTemplate UITest_BgTemplate[2] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
};

const u16 speciesTable[] = 
{
    SPECIES_NOSEPASS,
    SPECIES_NIDOKING,
    SPECIES_MIGHTYENA,
    SPECIES_METAGROSS,
    SPECIES_SWAMPERT,
    SPECIES_PORYGON,
    SPECIES_PORYGON2,
    SPECIES_CHARIZARD,
};

const struct WindowTemplate otherWindows[] =
{
    {
        .bg = 1,
		.tilemapLeft = 1,
        .tilemapTop = 15,
        .width = 29,
        .height = 5,
        .paletteNum = 15,
		.baseBlock = 0xF2,
    },
    DUMMY_WIN_TEMPLATE,
};

const u8 sFontColourTable[3] = {0, 1, 2};

const u8 gText_Animating[] = _("Animating...");

void TestUIInputManager(u8);
void TestUIReturn(u8);
void TestUISetup(MainCallback);
void TestUISetup2(void);
void UpdateTestUISprite(void);
void TestUIAnim(u8);
void TestUIWaitForAnim(u8);
void TestUITextTest(u8);
void TestUIRunTextPrinters(u8);

void TestUIVBlank(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void TestUICallback(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

void ImgTest(void)
{
    LZ77UnCompVram(gBattleAnimBackgroundImage_00, (void *)VRAM);
    LoadCompressedPalette(gBattleAnimBackgroundPalette_00, 0x20, 0x20);
    LZ77UnCompVram(gBattleAnimBackgroundTilemap_00, UIStructPtr->tilemapBuffer);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, UITest_BgTemplate, 2);
    SetBgTilemapBuffer(0, UIStructPtr->tilemapBuffer);
    SetBgTilemapBuffer(1, UIStructPtr->bandAid);
    ResetAllBgsCoordinates();
    CopyBgTilemapBufferToVram(0);
    ShowBg(0);
    ShowBg(1);
    UIStructPtr->spriteId = CreatePicSprite2(HoennPokedexNumToSpecies(UIStructPtr->indexId), 8, 0, 1, (DISPLAY_WIDTH / 2), (DISPLAY_HEIGHT / 2), 0, 0xFFFF);
}

void TestUIStartMenu(void)
{
    TestUISetup(CB2_ReturnToFieldWithOpenMenu);
}

void TestUISetup(MainCallback callback)
{
    UIStructPtr = AllocZeroed(sizeof(struct TestUIStruct));
    if (UIStructPtr == NULL)
    {
        SetMainCallback2(callback);
    }
    else
    {
        UIStructPtr->returnCallback = callback;
        UIStructPtr->indexId = 0;
        UIStructPtr->windowId = AddWindow(&otherWindows[0]);
        SetMainCallback2(TestUISetup2);
    }
}

void TestUISetup2(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        gMain.state++;
        break;
    case 1:
        ImgTest();
        TestUITextTest(UIStructPtr->windowId);
        gMain.state++;
        break;
    case 2:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 3:
        SetVBlankCallback(TestUIVBlank);
        SetMainCallback2(TestUICallback);
        FadeOutBGM(4);
        PlayBGM(MUS_RG_JUMP);
        CreateTask(TestUIInputManager, 0);
        break;
    }
}

void TestUIInputManager(u8 taskId)
{
    if ((gMain.newKeys & DPAD_UP) && UIStructPtr->indexId > 0)
    {
        UIStructPtr->indexId--;
        UpdateTestUISprite();
    }
    else if ((gMain.newKeys & DPAD_DOWN) && UIStructPtr->indexId < HOENN_DEX_COUNT - 1)
    {
        UIStructPtr->indexId++;
        UpdateTestUISprite();
    }
    else if (gMain.newKeys & A_BUTTON)
    {
        gTasks[taskId].func = TestUIAnim;
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 0x10, RGB_BLACK);
        gTasks[taskId].func = TestUIReturn;
    }
}

void TestUIReturn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        sub_8098374();
        FadeOutBGM(4);
        PlayBGM(GetCurrentMapMusic());
        SetMainCallback2(UIStructPtr->returnCallback);
        Free(UIStructPtr->returnCallback);
    }
}

void UpdateTestUISprite(void)
{
    PlaySE(SE_SELECT);
    FreeOamMatrix(gSprites[UIStructPtr->spriteId].oam.matrixNum);
    FreeAndDestroyMonPicSprite(UIStructPtr->spriteId);
    UIStructPtr->spriteId = CreatePicSprite2(HoennPokedexNumToSpecies(UIStructPtr->indexId), 8, 0, 1, (DISPLAY_WIDTH / 2), (DISPLAY_HEIGHT / 2), 0, 0xFFFF);
    FillWindowPixelBuffer(UIStructPtr->windowId, 17);
    AddTextPrinterParameterized2(UIStructPtr->windowId, 1, gSpeciesNames[HoennPokedexNumToSpecies(UIStructPtr->indexId)], GetPlayerTextSpeedDelay(), NULL, 2, 1, 3);
    CreateTask(TestUIRunTextPrinters, 0);
}

void TestUIAnim(u8 taskId)
{
    // PlayCry1(HoennPokedexNumToSpecies(UIStructPtr->indexId), 0);
    DoMonFrontSpriteAnimation(&gSprites[UIStructPtr->spriteId], HoennPokedexNumToSpecies(UIStructPtr->indexId), FALSE, 1);
    StringExpandPlaceholders(gStringVar4, gText_Animating);
    FillWindowPixelBuffer(UIStructPtr->windowId, 17);
    AddTextPrinterParameterized2(UIStructPtr->windowId, 1, gStringVar4, GetPlayerTextSpeedDelay(), NULL, 2, 1, 3);
    CreateTask(TestUIRunTextPrinters, 0);
    gTasks[taskId].func = TestUIWaitForAnim;
}

void TestUIWaitForAnim(u8 taskId)
{
    if (gSprites[UIStructPtr->spriteId].animEnded)
    {
        FillWindowPixelBuffer(UIStructPtr->windowId, 17);
        AddTextPrinterParameterized2(UIStructPtr->windowId, 1, gSpeciesNames[HoennPokedexNumToSpecies(UIStructPtr->indexId)], GetPlayerTextSpeedDelay(), NULL, 2, 1, 3);
        CreateTask(TestUIRunTextPrinters, 0);
        gTasks[taskId].func = TestUIInputManager;
    }
}

/* void TestUITextTest(u8 windowId)
{
    LoadMessageBoxGfx(UIStructPtr->windowId, 0xE2, 0x10);
    SetWindowBorderStyle(windowId, FALSE, 211, 1);
    StringExpandPlaceholders(gStringVar4, gText_Pokemon);
    FillWindowPixelBuffer(windowId, 0);
    PutWindowTilemap(windowId);
    AddTextPrinterParameterized3(windowId, 1, 0, 0, sFontColourTable, -1, gStringVar4);
    CopyWindowToVram(windowId, 3);
} */

void TestUITextTest(u8 windowId)
{
    LoadMessageBoxGfx(windowId, 0x183, 0x10);
    FillWindowPixelBuffer(windowId, 17);
    // SetWindowBorderStyle(windowId, FALSE, 0x164, 15);
    sub_8197B1C(windowId, TRUE, 0x183, 15);
    AddTextPrinterParameterized2(windowId, 1, gSpeciesNames[HoennPokedexNumToSpecies(UIStructPtr->indexId)], GetPlayerTextSpeedDelay(), NULL, 2, 1, 3);
    CreateTask(TestUIRunTextPrinters, 0);
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, 3);
    // CreateYesNoMenu(&sWindowTemplate_CostumeMenu[YES_NO_WINDOW], 211, 14, 1);
}

void TestUIRunTextPrinters(u8 taskId)
{
    if (RunTextPrintersRetIsActive(UIStructPtr->windowId) != TRUE)
    {
        DestroyTask(taskId);
    }
}
