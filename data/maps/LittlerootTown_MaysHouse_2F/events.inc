LittlerootTown_MaysHouse_2F_EventObjects: @ 852D480
	object_event 1, EVENT_OBJ_GFX_RIVAL_MAY_NORMAL, 0, 1, 1, 0, MOVEMENT_TYPE_FACE_DOWN, 1, 0, 0, 0, LittlerootTown_MaysHouse_2F_EventScript_1F94C1, FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	object_event 2, EVENT_OBJ_GFX_VAR_0, 0, 0, 6, 0, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_1
	object_event 3, EVENT_OBJ_GFX_VAR_1, 0, 1, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_2
	object_event 4, EVENT_OBJ_GFX_VAR_2, 0, 2, 6, 0, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_3
	object_event 5, EVENT_OBJ_GFX_VAR_3, 0, 3, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_4
	object_event 6, EVENT_OBJ_GFX_VAR_4, 0, 4, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_5
	object_event 7, EVENT_OBJ_GFX_VAR_5, 0, 5, 6, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_6
	object_event 8, EVENT_OBJ_GFX_VAR_6, 0, 0, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_7
	object_event 9, EVENT_OBJ_GFX_VAR_7, 0, 1, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_8
	object_event 10, EVENT_OBJ_GFX_VAR_8, 0, 2, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_9
	object_event 11, EVENT_OBJ_GFX_VAR_9, 0, 3, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_10
	object_event 12, EVENT_OBJ_GFX_VAR_A, 0, 4, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_11
	object_event 13, EVENT_OBJ_GFX_VAR_B, 0, 5, 7, 3, MOVEMENT_TYPE_LOOK_AROUND, 0, 0, 0, 0, 0x0, FLAG_DECORATION_12
	object_event 14, EVENT_OBJ_GFX_MOM, 0, 1, 1, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 0, 0, 0, 0x0, FLAG_HIDE_LITTLE_ROOT_TOWN_PLAYERS_BEDROOM_MOM
	object_event 15, EVENT_OBJ_GFX_PICHU_DOLL, 0, 3, 4, 4, MOVEMENT_TYPE_FACE_DOWN, 1, 1, 0, 0, 0x0, FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	object_event 16, EVENT_OBJ_GFX_ITEM_BALL, 0, 5, 4, 0, MOVEMENT_TYPE_LOOK_AROUND, 1, 1, 0, 0, LittlerootTown_MaysHouse_2F_EventScript_1F9334, FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL

LittlerootTown_MaysHouse_2F_MapWarps: @ 852D600
	warp_def 1, 1, 0, 2, MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F

LittlerootTown_MaysHouse_2F_MapBGEvents: @ 852D608
	bg_event 5, 1, 0, BG_EVENT_PLAYER_FACING_ANY, LittlerootTown_MaysHouse_2F_EventScript_1F865F
	bg_event 7, 1, 0, BG_EVENT_PLAYER_FACING_ANY, LittlerootTown_MaysHouse_2F_EventScript_1F8656
	bg_event 3, 1, 0, BG_EVENT_PLAYER_FACING_ANY, LittlerootTown_MaysHouse_2F_EventScript_29278D
	bg_event 8, 1, 0, BG_EVENT_PLAYER_FACING_ANY, EventScript_PlayerPCFemale

LittlerootTown_MaysHouse_2F_MapEvents:: @ 852D638
	map_events LittlerootTown_MaysHouse_2F_EventObjects, LittlerootTown_MaysHouse_2F_MapWarps, 0x0, LittlerootTown_MaysHouse_2F_MapBGEvents

