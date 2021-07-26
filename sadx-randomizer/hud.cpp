#include "stdafx.h"

float xpos = 0;
float ypos = 0;
float vscale = 1.0f;
float hzscale = 1.0f;
float center_x = (float)HorizontalResolution / 2.0f;
float center_y = (float)VerticalResolution / 2.0f;

static float ActionButtonAlpha = 0;
static bool ActionButtonActive = false;


NJS_TEXNAME Hud_Rando_TEXNAMES[4];
NJS_TEXLIST Hud_Rando_TEXLIST = { arrayptrandlength(Hud_Rando_TEXNAMES) };
PVMEntry Hud_Rando = { "hud_rando", &Hud_Rando_TEXLIST };

enum RandoHudTextures {
	CmnHudTex_SA2ActionBody,
	CmnHudTex_SA2ActionButton,
	CmnHudTex_SA2Action,
};

enum RandoHudSprites {
	CmnHudSprite_SA2ActionBody,
	CmnHudSprite_SA2ActionButton,
	CmnHudSprite_SA2Action,
};

NJS_TEXANIM	Hud_Rando_TEXANIM[]{
	{ 40, 30, 0x24, 0xC, 0, 0, 0x100, 0x100, CmnHudTex_SA2ActionBody, 0x20 },
	{ 40, 30, 0x10, 0x10, 0, 0, 0x100, 0x100, CmnHudTex_SA2ActionButton, 0x20 },
	{ 90, 20, 0x35, 0x8, 0, 0, 0x100, 0x100, CmnHudTex_SA2Action, 0x20 },
	{ 85, 15, 0x35, 0x8, 0, 0, 0x100, 0x100, 3, 0x20 },
};


NJS_SPRITE HUD_Rando_SPRITE = { { 0, 0, 0 }, 1.0, 1.0, 0, &Hud_Rando_TEXLIST, Hud_Rando_TEXANIM };

void ShowActionButton() {
	ActionButtonActive = true;
}

void alphaButtonManagement() {
	if (ActionButtonActive == true) {

		ActionButtonActive = false;
		if (ActionButtonAlpha < 1)
			ActionButtonAlpha += 0.1f;
	}
	else if (ActionButtonAlpha <= 0) {
		return;
	}
	else {
		if (ActionButtonAlpha > 0)
			ActionButtonAlpha -= 0.2f;
	}
}

void DrawButton(int button) {

	if (button != 3)
		button = CmnHudSprite_SA2Action;

	help.PushScaleUI(uiscale::Align_Right, false, 1.0f, 1.0f);
	SetMaterialAndSpriteColor_Float(1, 1, 1, 1);
	vscale = (float)VerticalResolution / 480.0f;
	hzscale = (float)HorizontalResolution / 640.0f;

	ypos = 40;
	xpos = 520;

	HUD_Rando_SPRITE.p.x = xpos;
	HUD_Rando_SPRITE.p.y = ypos;


	HUD_Rando_SPRITE.sx = 1 + ActionButtonAlpha;
	njDrawSprite2D_ForcePriority(&HUD_Rando_SPRITE, CmnHudSprite_SA2ActionBody, -1.501, NJD_SPRITE_ALPHA);
	HUD_Rando_SPRITE.sx = 1;

	if (button == 2) {
		HUD_Rando_SPRITE.p.x = xpos + 20;
		HUD_Rando_SPRITE.p.y = ypos + 5;
	}
	else {
		HUD_Rando_SPRITE.p.x = xpos + ypos;
		HUD_Rando_SPRITE.p.y = ypos + 5;
	}
	

	njDrawSprite2D_ForcePriority(&HUD_Rando_SPRITE, CmnHudSprite_SA2ActionButton, -1.501, NJD_SPRITE_ALPHA);


	if (button == 2) {
		HUD_Rando_SPRITE.p.x = xpos - 13;
		HUD_Rando_SPRITE.p.y = ypos + 2;
	}
	else {
		HUD_Rando_SPRITE.p.x = xpos - 5;
	}


	if (ActionButtonAlpha >= 1) {
		njDrawSprite2D_ForcePriority(&HUD_Rando_SPRITE, button, -1.501, NJD_SPRITE_ALPHA);
	}
	ClampGlobalColorThing_Thing();
	help.PopScaleUI();
}

void Hud_ShowSwapButton() {


	if (!IsGamePaused()) {
		if (ControllerPointers[0]->PressedButtons & Buttons_Y) {
			ActionButtonActive = false;
		}
		else
			ShowActionButton();

		alphaButtonManagement();
	}
	else {

		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

		if (ActionButtonActive == false && ActionButtonAlpha <= 0) {
			return;
		}
	}

	DrawButton(2);
}


void Hud_ShowActionButton() {
	if (!IsGamePaused()) {
		if (ControllerPointers[0]->PressedButtons & Buttons_Y) {
			ActionButtonActive = false;
		}
		else {
			ShowActionButton();
		}

		alphaButtonManagement();
	}
	else {
		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);

		if (ActionButtonActive == false && ActionButtonAlpha <= 0) {
			return;
		}
	}

	DrawButton(3);
}


void Hud_DisplayOnframe() {
	if (!CharObj2Ptrs[0] || GameState != 15)
		return;

	if (isAIActive && isAIAllowed && SwapDelay > 149)
	{
		int action = EntityData1Ptrs[0]->Action;
		if (action == 1 || action == 2)
			Hud_ShowSwapButton();
	}
}

void initHud() {

	help.RegisterCommonObjectPVM(Hud_Rando);
}