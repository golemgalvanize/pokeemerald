NavelRock_Bottom_MapScripts:: @ 8269255
	map_script 3, NavelRock_Bottom_MapScript1_269260
	map_script 5, NavelRock_Bottom_MapScript1_269284
	.byte 0

NavelRock_Bottom_MapScript1_269260: @ 8269260
	call_if_set FLAG_0x091, NavelRock_Bottom_EventScript_269273
	call_if_unset FLAG_0x091, NavelRock_Bottom_EventScript_269277
	end

NavelRock_Bottom_EventScript_269273:: @ 8269273
	setflag FLAG_HIDE_LUGIA
	return

NavelRock_Bottom_EventScript_269277:: @ 8269277
	goto_if_set FLAG_0x1DD, NavelRock_Bottom_EventScript_27374E
	clearflag FLAG_HIDE_LUGIA
	return

NavelRock_Bottom_MapScript1_269284: @ 8269284
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, NavelRock_Bottom_EventScript_26928E
	end

NavelRock_Bottom_EventScript_26928E:: @ 826928E
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, 7
	goto_if_ne NavelRock_Bottom_EventScript_27374E
	removeobject 1
	return

NavelRock_Bottom_EventScript_2692A2:: @ 82692A2
	lock
	faceplayer
	waitse
	delay 20
	playse SE_T_AME_E
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 3
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 2
	special sub_8139560
	delay 30
	playse SE_T_AME_E
	setvar VAR_0x8004, 0
	setvar VAR_0x8005, 3
	setvar VAR_0x8006, 4
	setvar VAR_0x8007, 2
	special sub_8139560
	delay 30
	delay 50
	waitse
	playmoncry SPECIES_LUGIA, 2
	waitmoncry
	delay 20
	setvar VAR_0x8004, 249
	setvar VAR_0x8005, 70
	setvar VAR_0x8006, 0
	special CreateObedientEnemyMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, 1
	goto_if_eq NavelRock_Bottom_EventScript_269336
	compare VAR_RESULT, 4
	goto_if_eq NavelRock_Bottom_EventScript_269344
	compare VAR_RESULT, 5
	goto_if_eq NavelRock_Bottom_EventScript_269344
	setflag FLAG_0x091
	release
	end

NavelRock_Bottom_EventScript_269336:: @ 8269336
	setflag FLAG_0x1DD
	setvar VAR_0x8004, 249
	goto NavelRock_Bottom_EventScript_273776
	end

NavelRock_Bottom_EventScript_269344:: @ 8269344
	setvar VAR_0x8004, 249
	goto NavelRock_Bottom_EventScript_273776
	end

