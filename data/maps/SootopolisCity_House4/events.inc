SootopolisCity_House4_EventObjects: @ 85333DC
	object_event 1, EVENT_OBJ_GFX_MAN_1, 0, 2, 4, 3, MOVEMENT_TYPE_FACE_RIGHT, 0, 0, 0, 0, SootopolisCity_House4_EventScript_226D16, 0
	object_event 2, EVENT_OBJ_GFX_WOMAN_4, 0, 5, 2, 3, MOVEMENT_TYPE_FACE_UP, 1, 2, 0, 0, SootopolisCity_House4_EventScript_226D1F, 0
	object_event 3, EVENT_OBJ_GFX_AZUMARILL, 0, 2, 3, 3, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, 0, 0, SootopolisCity_House4_EventScript_226D28, 0

SootopolisCity_House4_MapWarps: @ 8533424
	warp_def 3, 6, 0, 7, MAP_SOOTOPOLIS_CITY
	warp_def 4, 6, 0, 7, MAP_SOOTOPOLIS_CITY

SootopolisCity_House4_MapEvents:: @ 8533434
	map_events SootopolisCity_House4_EventObjects, SootopolisCity_House4_MapWarps, 0x0, 0x0

