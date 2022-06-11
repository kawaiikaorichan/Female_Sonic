#include "pch.h"
#include "SADXVariables.h"
#include "sstextlist.h"

#include "SonicDressDC.h"
#include "SonicAthleticDC.h"
#include "SonicDressDX.h"
#include "SonicAthleticDX.h"
#include "PrincessDC.h"
#include "PrincessDX.h"
#include "FingerDC.h"
#include "FingerDX.h"
#include "SSball.h"
#include "lanternapi.h"

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

enum Version { Dreamcast, DX };
enum Style { Dress, Athletic };
enum Super { Same, Princess };

static int Version = Dreamcast;
static int Style = Athletic;
static int Super = Princess;

void Tornado_init(const HelperFunctions& helperFunctions);

//Light Dash Aura for DX, colors in Alpha, Red, Green, Blue
void __cdecl SetLSDColor()
{
	SetMaterialAndSpriteColor_Float(0.8f, 0.7f, 0.1f, 0.65f);
}

//Light Dash Aura for DC conversion
void __cdecl Sonic_DisplayLightDashModel_mod(EntityData1* data1, CharObj2** data2_pp, CharObj2* data2)
{
	int v3; // eax
	__int16 v4; // t1
	float v5; // st7
	float basedepth = 8000.0f;
	NJS_ACTION v8; // [esp+4h] [ebp-18h]
	NJS_OBJECT** ___SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(GetModuleHandle(L"CHRMODELS_orig"), "___SONIC_OBJECTS");
	if (!MissedFrames)
	{
		v3 = (unsigned __int16)data2->AnimationThing.Index;
		v8.object = ___SONIC_OBJECTS[54];
		if (data2->AnimationThing.State == 2)
		{
			v4 = data2->AnimationThing.LastIndex;
			v8.motion = data2->AnimationThing.action->motion;
		}
		else
		{
			v8.motion = data2->AnimationThing.AnimData[v3].Animation->motion;
		}
		v5 = (float)(FrameCounterUnpaused & 0x7F);
		if (v5 >= 64.0f)
		{
			v5 = 128.0f - v5;
		}
		//v5 = 0;
		njPushMatrixEx();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL | NJD_CONTROL_3D_ENABLE_ALPHA | NJD_CONTROL_3D_CONSTANT_ATTR);
		njColorBlendingMode(0, NJD_COLOR_BLENDING_ONE);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_ONE);
		// Main
		SetMaterialAndSpriteColor_Float(1.0f, 0.7, 0.06f + (64.0f - v5) / 880.0f, 0.65f);
		DrawQueueDepthBias = basedepth;
		late_ActionMesh(&v8, data2->AnimationThing.Frame, 0);
		// Outer 1
		njScale(0, 1.05f, 1.05f, 1.05f);
		SetMaterialAndSpriteColor_Float(1.0f, 0.73f, (64.0f - v5) / 1050.0f, 0.65f);
		DrawQueueDepthBias = basedepth + 300.0f;
		late_ActionMesh(&v8, data2->AnimationThing.Frame, 0);
		// Outer 2
		njScale(0, 1.05f, 1.05f, 1.05f);
		SetMaterialAndSpriteColor_Float(1.0f, 0.08f, (64.0f - v5) / 2000.0f, 0.1f);
		DrawQueueDepthBias = basedepth + 600.0f;
		late_ActionMesh(&v8, data2->AnimationThing.Frame, 0);
		njColorBlendingMode(0, NJD_COLOR_BLENDING_SRCALPHA);
		njColorBlendingMode(NJD_DESTINATION_COLOR, NJD_COLOR_BLENDING_INVSRCALPHA);
		njPopMatrixEx();
		DrawQueueDepthBias = 0;
	}
}

uint16_t Sonic_UpperArmIndices_mod[] = {
	0, 2,
	4, 6,
	5, 7,
	1, 3,
};

uint16_t Sonic_LowerArmIndices_mod[] = {
	4, 14,
	5, 15,
	1, 11,
	0, 10,
};

uint16_t Sonic_KneeIndices_mod[] = {
	0, 2,
	4, 6,
	5, 7,
	1, 3,
};

uint16_t Sonic_LegIndices_mod[] = {
	0, 2,
	1, 3,
	4, 6,
	5, 7,
};

uint16_t Sonic_DressShoeIndices_DC[] = {
	2, 3,
	3, 2,
	0, 1,
	1, 0,
};

uint16_t Sonic_AthleticShoeIndices_DC[] = {
	2, 3,
	12, 8,
	0, 1,
	1, 0,
	17, 13,
	3, 2,
};

uint16_t Sonic_HandIndices_DressDC[] = {
	0, 14,
	1, 13,
	5, 12,
	4, 15,
};

uint16_t Sonic_HandIndices_AthleticDC[] = {
	0, 13,
	1, 1,
	5, 3,
	4, 12,
};

uint16_t Sonic_DressShoeIndices_DX[] = {
	1, 0,
	0, 1,
	31, 26,
	34, 2,
	3, 23,
	30, 22,
	2, 24,
	33, 3,
	32, 25,
};

uint16_t Sonic_HandIndices_DX[] = {
	11, 50,
	0, 14,
	12, 13,
	1, 55,
	5, 54,
	8, 12,
	4, 15,
};

uint16_t Sonic_ShoeIndices_AthleticDX[] = {
	23, 30,
	2, 3,
	30, 32,
	12, 8,
	29, 29,
	0, 1,
	1, 0,
	28, 28,
	17, 13,
	31, 31,
	3, 2,
};

uint16_t Sonic_LSShoeIndices_AthleticDX[] = {
	29, 19,
	2, 3,
	39, 28,
	12, 8,
	0, 1,
	1, 0,
	17, 13,
	38, 27,
	3, 2,
};

uint16_t SS_PrincessLeg[] = {
	1, 2,
	0, 1,
	4, 3,
	5, 4,
};

uint16_t SS_PrincessHeelDC[] = {
	200, 4,
	43, 10,
	47, 11,
	48, 3,
	188, 149,
	203, 154,
	17, 2,
	11, 12,
	13, 9,
	3, 21,
	199, 5,
	10, 18,
	14, 7,
	16, 14,
	18, 15,
	19, 19,
	20, 20,
	32, 17,
	35, 16,
	36, 13,
	40, 8,
	42, 6,
	2, 30,
	0, 41,
	1, 31,
};

uint16_t SS_PrincessHeelDX[] = {
	244, 27,
	59, 28,
	86, 45,
	75, 29,
	30, 8,
	225, 176,
	227, 180,
	31, 18,
	76, 41,
	85, 42,
	52, 19,
	243, 20,
	54, 22,
	55, 23,
	56, 24,
	57, 25,
};

void _cdecl InitSonicWeldInfo_DressDC()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_DressShoeIndices_DC;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_DressDC()
{
	NJS_OBJECT* v0; // ebp
	NJS_OBJECT* v1; // ebp
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // ebp
	NJS_OBJECT* v4; // eax

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = 4;
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = 4;
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = 4;
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = 4;
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = 4;
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = 4;
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = 4;
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = 4;
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = 11;
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DC;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DC;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = 11;
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = 7;
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = (unsigned __int16*)Sonic_HandIndices_DressDC;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = 7;
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = (unsigned __int16*)Sonic_HandIndices_DressDC;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = 9;
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DC;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DC;
	NPCSonicWeldInfo[13].VertexPairCount = 9;
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	*(_DWORD*)&NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = 4;
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void Init_SonicDressDC()
{
	SONIC_OBJECTS[0] = &objectdcd_0056AF50;
	SONIC_OBJECTS[1] = &objectdcd_00563B7C;
	SONIC_OBJECTS[2] = &objectdcd_00563D0C;
	SONIC_OBJECTS[3] = &objectdcd_005654EC;
	SONIC_OBJECTS[4] = &objectdcd_00564CD0;
	SONIC_OBJECTS[5] = &objectdcd_005647B8;
	SONIC_OBJECTS[6] = &objectdcd_00564A78;
	SONIC_OBJECTS[7] = &objectdcd_00561F14;
	SONIC_OBJECTS[8] = &objectdcd_005620A4;
	SONIC_OBJECTS[9] = &objectdcd_005638CC;
	SONIC_OBJECTS[10] = &objectdcd_005630B0;
	SONIC_OBJECTS[11] = &objectdcd_00562B80;
	SONIC_OBJECTS[12] = &objectdcd_0056044C;
	SONIC_OBJECTS[13] = &objectdcd_005605DC;
	SONIC_OBJECTS[14] = &objectdcd_00561C68;
	SONIC_OBJECTS[15] = &objectdcd_005613F8;
	SONIC_OBJECTS[16] = &objectdcd_00560DD0;
	SONIC_OBJECTS[17] = &objectdcd_0055E99C;
	SONIC_OBJECTS[18] = &objectdcd_0055EB2C;
	SONIC_OBJECTS[19] = &objectdcd_005601B8;
	SONIC_OBJECTS[20] = &objectdcd_0055F948;
	SONIC_OBJECTS[21] = &objectdcd_0055F330;
	SONIC_OBJECTS[44] = &objectdcd_0057BC44;
	SONIC_OBJECTS[45] = &objectdcd_0056998C;
	SONIC_OBJECTS[46] = &objectdcd_00569594;
	SONIC_OBJECTS[47] = &objectdcd_001CFBD8;
	SONIC_OBJECTS[48] = &objectdcd_00569DEC;
	SONIC_OBJECTS[49] = &objectdcd_00569594;
	SONIC_OBJECTS[50] = &objectdcd_00569E20;
	SONIC_OBJECTS[51] = &objectdcd_00569CE8;
	SONIC_OBJECTS[52] = &objectdcd_005698F0;
	SONIC_OBJECTS[54] = &objectdcd_006837E8;
	SONIC_OBJECTS[55] = &objectdcd_00682EF4;
	SONIC_OBJECTS[58] = &objectdcd_00581FB8;
	SONIC_OBJECTS[59] = &objectdcd_005818AC;
	SONIC_OBJECTS[60] = &objectdcd_00582CC0;
	SONIC_OBJECTS[61] = &objectdcd_005825A4;
	SONIC_OBJECTS[62] = &objectdcd_00565520;
	SONIC_OBJECTS[63] = &objectdcd_00583284;
	SONIC_OBJECTS[64] = &objectdcd_00583904;
	SONIC_OBJECTS[65] = &objectdcd_00585EB4;
	SONIC_OBJECTS[66] = &objectdcd_005729CC;
	SONIC_OBJECTS[67] = &objectdcd_0057BC44;
	SONIC_ACTIONS[0]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[1]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[2]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[3]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[4]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[5]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[6]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[7]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[8]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[9]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[10]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[11]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[12]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[13]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[14]->object = &objectdcd_005729CC;
	SONIC_ACTIONS[15]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[16]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[17]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[18]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[19]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[20]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[21]->object = &objectdcd_0057BC44;
	SONIC_ACTIONS[22]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[23]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[27]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[28]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[29]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[30]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[31]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[32]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[33]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[34]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[35]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[36]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[37]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[38]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[39]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[40]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[41]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[42]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[43]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[44]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[45]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[46]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[47]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[48]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[49]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[50]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[51]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[52]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[53]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[54]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[55]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[56]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[57]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[58]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[59]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[60]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[61]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[62]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[63]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[64]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[65]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[66]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[67]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[68]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[69]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[70]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[71]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[72]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[87]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[88]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[89]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[90]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[91]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[92]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[93]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[94]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[95]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[96]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[97]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[98]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[99]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[100]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[101]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[102]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[103]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[104]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[105]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[106]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[107]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[108]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[109]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[113]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[114]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[115]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[116]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[117]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[118]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[119]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[120]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[121]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[122]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[123]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[124]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[125]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[126]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[127]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[128]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[129]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[134]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[135]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[136]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[137]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[145]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[146]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[147]->object = &objectdcd_0056AF50;
	SONIC_ACTIONS[148]->object = &objectdcd_0056AF50;
	SONIC_MODELS[0] = &attachdcd_0055F304;
	SONIC_MODELS[1] = &attachdcd_00560DA4;
	SONIC_MODELS[2] = &attachdcd_005735AC;
	SONIC_MODELS[3] = &attachdcd_00573DFC;
	SONIC_MODELS[4] = &attachdcd_0057464C;
	SONIC_MODELS[5] = &attachdcd_0057525C;
	SONIC_MODELS[6] = &attachdcd_00575AB4;
	SONIC_MODELS[7] = &attachdcd_0057630C;
	SONIC_MODELS[8] = &attachdcd_00569568;
	SONIC_MODELS[9] = &attachdcd_00579C68;
	SONIC_MOTIONS[0] = &SONIC_MOTIONSDCD_0;
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_DressDC);
	WriteData((NJS_OBJECT**)0x00664C3E, &FingerDC);
	WriteData((NJS_OBJECT**)0x0069E24B, &FingerDC);
	WriteData((NJS_OBJECT**)0x006D010C, &FingerDC);
	WriteData((NJS_OBJECT**)0x006D711E, &FingerDC);
}

void Init_SSonicDressDC()
{
	SONIC_OBJECTS[22] = &objectdcd_0062DE88;
	SONIC_OBJECTS[23] = &objectdcd_00626AB4;
	SONIC_OBJECTS[24] = &objectdcd_00626C44;
	SONIC_OBJECTS[25] = &objectdcd_0062840C;
	SONIC_OBJECTS[26] = &objectdcd_00627BF0;
	SONIC_OBJECTS[27] = &objectdcd_006276D8;
	SONIC_OBJECTS[28] = &objectdcd_00624E3C;
	SONIC_OBJECTS[29] = &objectdcd_00624FCC;
	SONIC_OBJECTS[30] = &objectdcd_006267F4;
	SONIC_OBJECTS[31] = &objectdcd_00625FD8;
	SONIC_OBJECTS[32] = &objectdcd_00625AA8;
	SONIC_OBJECTS[33] = &objectdcd_00623474;
	SONIC_OBJECTS[34] = &objectdcd_00623604;
	SONIC_OBJECTS[35] = &objectdcd_00624B78;
	SONIC_OBJECTS[36] = &objectdcd_00624308;
	SONIC_OBJECTS[37] = &objectdcd_00623C14;
	SONIC_OBJECTS[38] = &objectdcd_00621AC4;
	SONIC_OBJECTS[39] = &objectdcd_00621C54;
	SONIC_OBJECTS[40] = &objectdcd_006231E0;
	SONIC_OBJECTS[41] = &objectdcd_00622970;
	SONIC_OBJECTS[42] = &objectdcd_00622254;
	SONIC_ACTIONS[130]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[131]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[132]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[133]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[138]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[139]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[140]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[141]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[143]->object = &objectdcd_0062DE88;
	SONIC_ACTIONS[144]->object = &objectdcd_0062DE88;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_DressDC);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_DressDC);
}

void _cdecl InitSonicWeldInfo_AthleticDC()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_AthleticShoeIndices_DC;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_AthleticDC;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_AthleticDC;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_AthleticDC;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_AthleticDC;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_AthleticDC;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_AthleticDC;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_AthleticDC()
{
	NJS_OBJECT* v0; // ebp
	NJS_OBJECT* v1; // ebp
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // ebp
	NJS_OBJECT* v4; // eax

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = 4;
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = 4;
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = 4;
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = 4;
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = 4;
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = 4;
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = 4;
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = 4;
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = 11;
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = (unsigned __int16*)Sonic_AthleticShoeIndices_DC;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = (unsigned __int16*)Sonic_AthleticShoeIndices_DC;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = 11;
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = 7;
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = (unsigned __int16*)Sonic_HandIndices_AthleticDC;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = 7;
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = (unsigned __int16*)Sonic_HandIndices_AthleticDC;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = 9;
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = (unsigned __int16*)Sonic_AthleticShoeIndices_DC;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = (unsigned __int16*)Sonic_AthleticShoeIndices_DC;
	NPCSonicWeldInfo[13].VertexPairCount = 9;
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	*(_DWORD*)&NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = 4;
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void Init_SonicAthleticDC()
{
	SONIC_OBJECTS[0] = &objectdca_0056AF50;
	SONIC_OBJECTS[1] = &objectdca_00563B7C;
	SONIC_OBJECTS[2] = &objectdca_00563D0C;
	SONIC_OBJECTS[3] = &objectdca_005654EC;
	SONIC_OBJECTS[4] = &objectdca_00564CD0;
	SONIC_OBJECTS[5] = &objectdca_005647B8;
	SONIC_OBJECTS[6] = &objectdca_00564A78;
	SONIC_OBJECTS[7] = &objectdca_00561F14;
	SONIC_OBJECTS[8] = &objectdca_005620A4;
	SONIC_OBJECTS[9] = &objectdca_005638CC;
	SONIC_OBJECTS[10] = &objectdca_005630B0;
	SONIC_OBJECTS[11] = &objectdca_00562B80;
	SONIC_OBJECTS[12] = &objectdca_0056044C;
	SONIC_OBJECTS[13] = &objectdca_005605DC;
	SONIC_OBJECTS[14] = &objectdca_00561C68;
	SONIC_OBJECTS[15] = &objectdca_005613F8;
	SONIC_OBJECTS[16] = &objectdca_00560DD0;
	SONIC_OBJECTS[17] = &objectdca_0055E99C;
	SONIC_OBJECTS[18] = &objectdca_0055EB2C;
	SONIC_OBJECTS[19] = &objectdca_005601B8;
	SONIC_OBJECTS[20] = &objectdca_0055F948;
	SONIC_OBJECTS[21] = &objectdca_0055F330;
	SONIC_OBJECTS[44] = &objectdca_0057BC44;
	SONIC_OBJECTS[45] = &objectdca_0056998C;
	SONIC_OBJECTS[46] = &objectdca_00569594;
	SONIC_OBJECTS[47] = &objectdca_001CFBD8;
	SONIC_OBJECTS[48] = &objectdca_00569DEC;
	SONIC_OBJECTS[49] = &objectdca_00569594;
	SONIC_OBJECTS[50] = &objectdca_00569E20;
	SONIC_OBJECTS[51] = &objectdca_00569CE8;
	SONIC_OBJECTS[52] = &objectdca_005698F0;
	SONIC_OBJECTS[54] = &objectdca_006837E8;
	SONIC_OBJECTS[55] = &objectdca_00682EF4;
	SONIC_OBJECTS[58] = &objectdca_00581FB8;
	SONIC_OBJECTS[59] = &objectdca_005818AC;
	SONIC_OBJECTS[60] = &objectdca_00582CC0;
	SONIC_OBJECTS[61] = &objectdca_005825A4;
	SONIC_OBJECTS[62] = &objectdca_00565520;
	SONIC_OBJECTS[63] = &objectdca_00583284;
	SONIC_OBJECTS[64] = &objectdca_00583904;
	SONIC_OBJECTS[65] = &objectdca_00585EB4;
	SONIC_OBJECTS[66] = &objectdca_005729CC;
	SONIC_OBJECTS[67] = &objectdca_0057BC44;
	SONIC_ACTIONS[0]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[1]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[2]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[3]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[4]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[5]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[6]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[7]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[8]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[9]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[10]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[11]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[12]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[13]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[14]->object = &objectdca_005729CC;
	SONIC_ACTIONS[15]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[16]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[17]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[18]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[19]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[20]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[21]->object = &objectdca_0057BC44;
	SONIC_ACTIONS[22]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[23]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[27]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[28]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[29]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[30]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[31]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[32]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[33]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[34]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[35]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[36]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[37]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[38]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[39]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[40]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[41]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[42]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[43]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[44]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[45]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[46]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[47]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[48]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[49]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[50]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[51]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[52]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[53]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[54]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[55]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[56]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[57]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[58]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[59]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[60]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[61]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[62]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[63]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[64]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[65]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[66]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[67]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[68]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[69]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[70]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[71]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[72]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[87]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[88]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[89]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[90]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[91]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[92]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[93]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[94]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[95]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[96]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[97]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[98]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[99]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[100]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[101]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[102]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[103]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[104]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[105]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[106]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[107]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[108]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[109]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[113]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[114]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[115]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[116]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[117]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[118]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[119]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[120]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[121]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[122]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[123]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[124]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[125]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[126]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[127]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[128]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[129]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[134]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[135]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[136]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[137]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[145]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[146]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[147]->object = &objectdca_0056AF50;
	SONIC_ACTIONS[148]->object = &objectdca_0056AF50;
	SONIC_MODELS[0] = &attachdca_0055F304;
	SONIC_MODELS[1] = &attachdca_00560DA4;
	SONIC_MODELS[2] = &attachdca_005735AC;
	SONIC_MODELS[3] = &attachdca_00573DFC;
	SONIC_MODELS[4] = &attachdca_0057464C;
	SONIC_MODELS[5] = &attachdca_0057525C;
	SONIC_MODELS[6] = &attachdca_00575AB4;
	SONIC_MODELS[7] = &attachdca_0057630C;
	SONIC_MODELS[8] = &attachdca_00569568;
	SONIC_MODELS[9] = &attachdca_00579C68;
	SONIC_MOTIONS[0] = &SONIC_MOTIONSDCA_0;
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_AthleticDC);
	WriteData((NJS_OBJECT**)0x00664C3E, &FingerDC);
	WriteData((NJS_OBJECT**)0x0069E24B, &FingerDC);
	WriteData((NJS_OBJECT**)0x006D010C, &FingerDC);
	WriteData((NJS_OBJECT**)0x006D711E, &FingerDC);
}

void Init_SSonicAthleticDC()
{
	SONIC_OBJECTS[22] = &objectdca_0062DE88;
	SONIC_OBJECTS[23] = &objectdca_00626AB4;
	SONIC_OBJECTS[24] = &objectdca_00626C44;
	SONIC_OBJECTS[25] = &objectdca_0062840C;
	SONIC_OBJECTS[26] = &objectdca_00627BF0;
	SONIC_OBJECTS[27] = &objectdca_006276D8;
	SONIC_OBJECTS[28] = &objectdca_00624E3C;
	SONIC_OBJECTS[29] = &objectdca_00624FCC;
	SONIC_OBJECTS[30] = &objectdca_006267F4;
	SONIC_OBJECTS[31] = &objectdca_00625FD8;
	SONIC_OBJECTS[32] = &objectdca_00625AA8;
	SONIC_OBJECTS[33] = &objectdca_00623474;
	SONIC_OBJECTS[34] = &objectdca_00623604;
	SONIC_OBJECTS[35] = &objectdca_00624B78;
	SONIC_OBJECTS[36] = &objectdca_00624308;
	SONIC_OBJECTS[37] = &objectdca_00623C14;
	SONIC_OBJECTS[38] = &objectdca_00621AC4;
	SONIC_OBJECTS[39] = &objectdca_00621C54;
	SONIC_OBJECTS[40] = &objectdca_006231E0;
	SONIC_OBJECTS[41] = &objectdca_00622970;
	SONIC_OBJECTS[42] = &objectdca_00622254;
	SONIC_ACTIONS[130]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[131]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[132]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[133]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[138]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[139]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[140]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[141]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[143]->object = &objectdca_0062DE88;
	SONIC_ACTIONS[144]->object = &objectdca_0062DE88;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_AthleticDC);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_AthleticDC);
}

void _cdecl InitSonicWeldInfo_DressDX()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_DressShoeIndices_DX;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_DressDX()
{
	NJS_OBJECT* v0; // ebp
	NJS_OBJECT* v1; // ebp
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // ebp
	NJS_OBJECT* v4; // eax

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = 4;
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = 4;
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = 4;
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = 4;
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = 4;
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = 4;
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = 4;
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = 4;
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = 11;
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DX;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DX;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = 11;
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = 7;
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = (unsigned __int16*)Sonic_HandIndices_DX;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = 7;
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = (unsigned __int16*)Sonic_HandIndices_DX;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = 9;
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DX;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = (unsigned __int16*)Sonic_DressShoeIndices_DX;
	NPCSonicWeldInfo[13].VertexPairCount = 9;
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	*(_DWORD*)&NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = 4;
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void Init_SonicDressDX()
{
	SONIC_OBJECTS[0] = &objectdxd_0056AF50;
	SONIC_OBJECTS[1] = &objectdxd_00563B7C;
	SONIC_OBJECTS[2] = &objectdxd_00563D0C;
	SONIC_OBJECTS[3] = &objectdxd_005654EC;
	SONIC_OBJECTS[4] = &objectdxd_00564CD0;
	SONIC_OBJECTS[5] = &objectdxd_005647B8;
	SONIC_OBJECTS[6] = &objectdxd_00564A78;
	SONIC_OBJECTS[7] = &objectdxd_00561F14;
	SONIC_OBJECTS[8] = &objectdxd_005620A4;
	SONIC_OBJECTS[9] = &objectdxd_005638CC;
	SONIC_OBJECTS[10] = &objectdxd_005630B0;
	SONIC_OBJECTS[11] = &objectdxd_00562B80;
	SONIC_OBJECTS[12] = &objectdxd_0056044C;
	SONIC_OBJECTS[13] = &objectdxd_005605DC;
	SONIC_OBJECTS[14] = &objectdxd_00561C68;
	SONIC_OBJECTS[15] = &objectdxd_005613F8;
	SONIC_OBJECTS[16] = &objectdxd_00560DD0;
	SONIC_OBJECTS[17] = &objectdxd_0055E99C;
	SONIC_OBJECTS[18] = &objectdxd_0055EB2C;
	SONIC_OBJECTS[19] = &objectdxd_005601B8;
	SONIC_OBJECTS[20] = &objectdxd_0055F948;
	SONIC_OBJECTS[21] = &objectdxd_0055F330;
	SONIC_OBJECTS[44] = &objectdxd_0057BC44;
	SONIC_OBJECTS[45] = &objectdxd_0056998C;
	SONIC_OBJECTS[46] = &objectdxd_00569594;
	SONIC_OBJECTS[47] = &objectdxd_005812AC;
	SONIC_OBJECTS[48] = &objectdxd_00569DEC;
	SONIC_OBJECTS[49] = &objectdxd_00569594;
	SONIC_OBJECTS[50] = &objectdxd_00569E20;
	SONIC_OBJECTS[51] = &objectdxd_00569CE8;
	SONIC_OBJECTS[52] = &objectdxd_005698F0;
	SONIC_OBJECTS[54] = &objectdxd_006837E8;
	SONIC_OBJECTS[55] = &objectdxd_00682EF4;
	SONIC_OBJECTS[58] = &objectdxd_00581FB8;
	SONIC_OBJECTS[59] = &objectdxd_005818AC;
	SONIC_OBJECTS[60] = &objectdxd_00582CC0;
	SONIC_OBJECTS[61] = &objectdxd_005825A4;
	SONIC_OBJECTS[62] = &objectdxd_00565520;
	SONIC_OBJECTS[63] = &objectdxd_00583284;
	SONIC_OBJECTS[64] = &objectdxd_00583904;
	SONIC_OBJECTS[65] = &objectdxd_00585EB4;
	SONIC_OBJECTS[66] = &objectdxd_005729CC;
	SONIC_OBJECTS[67] = &objectdxd_0057BC44;
	SONIC_ACTIONS[0]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[1]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[2]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[3]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[4]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[5]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[6]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[7]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[8]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[9]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[10]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[11]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[12]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[13]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[14]->object = &objectdxd_005729CC;
	SONIC_ACTIONS[15]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[16]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[17]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[18]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[19]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[20]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[21]->object = &objectdxd_0057BC44;
	SONIC_ACTIONS[22]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[23]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[27]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[28]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[29]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[30]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[31]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[32]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[33]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[34]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[35]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[36]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[37]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[38]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[39]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[40]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[41]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[42]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[43]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[44]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[45]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[46]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[47]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[48]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[49]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[50]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[51]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[52]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[53]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[54]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[55]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[56]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[57]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[58]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[59]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[60]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[61]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[62]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[63]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[64]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[65]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[66]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[67]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[68]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[69]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[70]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[71]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[72]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[87]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[88]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[89]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[90]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[91]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[92]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[93]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[94]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[95]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[96]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[97]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[98]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[99]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[100]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[101]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[102]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[103]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[104]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[105]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[106]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[107]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[108]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[109]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[113]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[114]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[115]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[116]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[117]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[118]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[119]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[120]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[121]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[122]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[123]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[124]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[125]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[126]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[127]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[128]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[129]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[134]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[135]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[136]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[137]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[145]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[146]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[147]->object = &objectdxd_0056AF50;
	SONIC_ACTIONS[148]->object = &objectdxd_0056AF50;
	SONIC_MODELS[0] = &attachdxd_0055F304;
	SONIC_MODELS[1] = &attachdxd_00560DA4;
	SONIC_MODELS[2] = &attachdxd_005735AC;
	SONIC_MODELS[3] = &attachdxd_00573DFC;
	SONIC_MODELS[4] = &attachdxd_0057464C;
	SONIC_MODELS[5] = &attachdxd_0057525C;
	SONIC_MODELS[6] = &attachdxd_00575AB4;
	SONIC_MODELS[7] = &attachdxd_0057630C;
	SONIC_MODELS[8] = &attachdxd_00569568;
	SONIC_MODELS[9] = &attachdxd_00579C68;
	SONIC_MOTIONS[0] = &SONIC_MOTIONSDXD_0;
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_DressDX);
	WriteData((NJS_OBJECT**)0x00664C3E, &FingerDX);
	WriteData((NJS_OBJECT**)0x0069E24B, &FingerDX);
	WriteData((NJS_OBJECT**)0x006D010C, &FingerDX);
	WriteData((NJS_OBJECT**)0x006D711E, &FingerDX);
}

void Init_SSonicDressDX()
{
	SONIC_OBJECTS[22] = &objectdxd_0062DE88;
	SONIC_OBJECTS[23] = &objectdxd_00626AB4;
	SONIC_OBJECTS[24] = &objectdxd_00626C44;
	SONIC_OBJECTS[25] = &objectdxd_0062840C;
	SONIC_OBJECTS[26] = &objectdxd_00627BF0;
	SONIC_OBJECTS[27] = &objectdxd_006276D8;
	SONIC_OBJECTS[28] = &objectdxd_00624E3C;
	SONIC_OBJECTS[29] = &objectdxd_00624FCC;
	SONIC_OBJECTS[30] = &objectdxd_006267F4;
	SONIC_OBJECTS[31] = &objectdxd_00625FD8;
	SONIC_OBJECTS[32] = &objectdxd_00625AA8;
	SONIC_OBJECTS[33] = &objectdxd_00623474;
	SONIC_OBJECTS[34] = &objectdxd_00623604;
	SONIC_OBJECTS[35] = &objectdxd_00624B78;
	SONIC_OBJECTS[36] = &objectdxd_00624308;
	SONIC_OBJECTS[37] = &objectdxd_00623C14;
	SONIC_OBJECTS[38] = &objectdxd_00621AC4;
	SONIC_OBJECTS[39] = &objectdxd_00621C54;
	SONIC_OBJECTS[40] = &objectdxd_006231E0;
	SONIC_OBJECTS[41] = &objectdxd_00622970;
	SONIC_OBJECTS[42] = &objectdxd_00622254;
	SONIC_ACTIONS[130]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[131]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[132]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[133]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[138]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[139]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[140]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[141]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[143]->object = &objectdxd_0062DE88;
	SONIC_ACTIONS[144]->object = &objectdxd_0062DE88;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_DressDX);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_DressDX);
}

void _cdecl InitSonicWeldInfo_AthleticDX()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_AthleticDX;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_AthleticDX;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LSShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_LSShoeIndices_AthleticDX;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LSShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_LSShoeIndices_AthleticDX;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LSShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = Sonic_LSShoeIndices_AthleticDX;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LSShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = Sonic_LSShoeIndices_AthleticDX;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void __cdecl InitNPCSonicWeldInfo_AthleticDX()
{
	NJS_OBJECT* v0; // ebp
	NJS_OBJECT* v1; // ebp
	NJS_OBJECT* v2; // ebp
	NJS_OBJECT* v3; // ebp
	NJS_OBJECT* v4; // eax

	NPCSonicWeldInfo[0].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	NPCSonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[0].anonymous_5 = 0;
	NPCSonicWeldInfo[0].VertexBuffer = 0;
	NPCSonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[0].WeldType = 2;
	NPCSonicWeldInfo[0].VertexPairCount = 4;
	NPCSonicWeldInfo[1].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	NPCSonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	NPCSonicWeldInfo[1].VertexPairCount = 4;
	NPCSonicWeldInfo[1].WeldType = 2;
	NPCSonicWeldInfo[1].anonymous_5 = 0;
	NPCSonicWeldInfo[1].VertexBuffer = 0;
	NPCSonicWeldInfo[1].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[2].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	NPCSonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	NPCSonicWeldInfo[2].VertexPairCount = 4;
	NPCSonicWeldInfo[2].WeldType = 2;
	NPCSonicWeldInfo[2].anonymous_5 = 0;
	NPCSonicWeldInfo[2].VertexBuffer = 0;
	NPCSonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[3].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	v0 = SONIC_OBJECTS[9];
	NPCSonicWeldInfo[3].VertIndexes = (unsigned __int16*)&Sonic_LowerArmIndices_mod;
	NPCSonicWeldInfo[3].ModelB = v0;
	NPCSonicWeldInfo[3].VertexPairCount = 4;
	NPCSonicWeldInfo[3].WeldType = 2;
	NPCSonicWeldInfo[3].anonymous_5 = 0;
	NPCSonicWeldInfo[3].VertexBuffer = 0;
	NPCSonicWeldInfo[4].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	NPCSonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[4].VertexPairCount = 4;
	NPCSonicWeldInfo[4].WeldType = 2;
	NPCSonicWeldInfo[4].anonymous_5 = 0;
	NPCSonicWeldInfo[4].VertexBuffer = 0;
	NPCSonicWeldInfo[4].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[5].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	NPCSonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	NPCSonicWeldInfo[5].VertexPairCount = 4;
	NPCSonicWeldInfo[5].WeldType = 2;
	NPCSonicWeldInfo[5].anonymous_5 = 0;
	NPCSonicWeldInfo[5].VertexBuffer = 0;
	NPCSonicWeldInfo[5].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[6].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	NPCSonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	NPCSonicWeldInfo[6].VertexPairCount = 4;
	NPCSonicWeldInfo[6].WeldType = 2;
	NPCSonicWeldInfo[6].anonymous_5 = 0;
	NPCSonicWeldInfo[6].VertexBuffer = 0;
	NPCSonicWeldInfo[6].VertIndexes = (unsigned __int16*)Sonic_KneeIndices_mod;
	NPCSonicWeldInfo[7].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	v1 = SONIC_OBJECTS[19];
	NPCSonicWeldInfo[7].VertIndexes = (unsigned __int16*)Sonic_LegIndices_mod;
	NPCSonicWeldInfo[7].ModelB = v1;
	NPCSonicWeldInfo[7].VertexPairCount = 4;
	NPCSonicWeldInfo[7].WeldType = 2;
	NPCSonicWeldInfo[7].anonymous_5 = 0;
	NPCSonicWeldInfo[7].VertexBuffer = 0;
	NPCSonicWeldInfo[8].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	NPCSonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	NPCSonicWeldInfo[8].VertexPairCount = 11;
	NPCSonicWeldInfo[8].WeldType = 2;
	NPCSonicWeldInfo[8].anonymous_5 = 0;
	NPCSonicWeldInfo[8].VertexBuffer = 0;
	NPCSonicWeldInfo[8].VertIndexes = (unsigned __int16*)Sonic_ShoeIndices_AthleticDX;
	NPCSonicWeldInfo[9].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	v2 = SONIC_OBJECTS[21];
	NPCSonicWeldInfo[9].VertIndexes = (unsigned __int16*)Sonic_ShoeIndices_AthleticDX;
	NPCSonicWeldInfo[9].ModelB = v2;
	NPCSonicWeldInfo[9].VertexPairCount = 11;
	NPCSonicWeldInfo[9].WeldType = 2;
	NPCSonicWeldInfo[9].anonymous_5 = 0;
	NPCSonicWeldInfo[9].VertexBuffer = 0;
	NPCSonicWeldInfo[10].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	NPCSonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	NPCSonicWeldInfo[10].VertexPairCount = 7;
	NPCSonicWeldInfo[10].WeldType = 2;
	NPCSonicWeldInfo[10].anonymous_5 = 0;
	NPCSonicWeldInfo[10].VertexBuffer = 0;
	NPCSonicWeldInfo[10].VertIndexes = (unsigned __int16*)Sonic_HandIndices_DX;
	NPCSonicWeldInfo[11].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	NPCSonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	NPCSonicWeldInfo[11].VertexPairCount = 7;
	NPCSonicWeldInfo[11].WeldType = 2;
	NPCSonicWeldInfo[11].anonymous_5 = 0;
	NPCSonicWeldInfo[11].VertexBuffer = 0;
	NPCSonicWeldInfo[11].VertIndexes = (unsigned __int16*)Sonic_HandIndices_DX;
	NPCSonicWeldInfo[12].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	NPCSonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	NPCSonicWeldInfo[12].VertexPairCount = 9;
	NPCSonicWeldInfo[12].anonymous_5 = 0;
	NPCSonicWeldInfo[12].VertexBuffer = 0;
	NPCSonicWeldInfo[12].WeldType = 2;
	NPCSonicWeldInfo[12].VertIndexes = (unsigned __int16*)Sonic_LSShoeIndices;
	NPCSonicWeldInfo[13].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	v3 = SONIC_OBJECTS[61];
	NPCSonicWeldInfo[13].anonymous_5 = 0;
	NPCSonicWeldInfo[13].VertexBuffer = 0;
	NPCSonicWeldInfo[13].ModelB = v3;
	NPCSonicWeldInfo[13].VertIndexes = (unsigned __int16*)Sonic_LSShoeIndices;
	NPCSonicWeldInfo[13].VertexPairCount = 9;
	NPCSonicWeldInfo[13].WeldType = 2;
	NPCSonicWeldInfo[14].BaseModel = *SONIC_OBJECTS;
	NPCSonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	v4 = SONIC_OBJECTS[63];
	NPCSonicWeldInfo[14].anonymous_5 = 0;
	NPCSonicWeldInfo[14].VertexBuffer = 0;
	NPCSonicWeldInfo[15].BaseModel = 0;
	NPCSonicWeldInfo[15].ModelA = 0;
	NPCSonicWeldInfo[15].ModelB = 0;
	*(_DWORD*)&NPCSonicWeldInfo[15].VertexPairCount = 0;
	NPCSonicWeldInfo[15].VertexBuffer = 0;
	NPCSonicWeldInfo[14].VertexPairCount = 4;
	NPCSonicWeldInfo[14].ModelB = v4;
	NPCSonicWeldInfo[14].WeldType = 2;
	NPCSonicWeldInfo[14].VertIndexes = Sonic_UpperArmIndices_mod;
	NPCSonicWeldInfo[15].VertIndexes = 0;
}

void Init_SonicAthleticDX()
{
	SONIC_OBJECTS[0] = &objectdxa_0056AF50;
	SONIC_OBJECTS[1] = &objectdxa_00563B7C;
	SONIC_OBJECTS[2] = &objectdxa_00563D0C;
	SONIC_OBJECTS[3] = &objectdxa_005654EC;
	SONIC_OBJECTS[4] = &objectdxa_00564CD0;
	SONIC_OBJECTS[5] = &objectdxa_005647B8;
	SONIC_OBJECTS[6] = &objectdxa_00564A78;
	SONIC_OBJECTS[7] = &objectdxa_00561F14;
	SONIC_OBJECTS[8] = &objectdxa_005620A4;
	SONIC_OBJECTS[9] = &objectdxa_005638CC;
	SONIC_OBJECTS[10] = &objectdxa_005630B0;
	SONIC_OBJECTS[11] = &objectdxa_00562B80;
	SONIC_OBJECTS[12] = &objectdxa_0056044C;
	SONIC_OBJECTS[13] = &objectdxa_005605DC;
	SONIC_OBJECTS[14] = &objectdxa_00561C68;
	SONIC_OBJECTS[15] = &objectdxa_005613F8;
	SONIC_OBJECTS[16] = &objectdxa_00560DD0;
	SONIC_OBJECTS[17] = &objectdxa_0055E99C;
	SONIC_OBJECTS[18] = &objectdxa_0055EB2C;
	SONIC_OBJECTS[19] = &objectdxa_005601B8;
	SONIC_OBJECTS[20] = &objectdxa_0055F948;
	SONIC_OBJECTS[21] = &objectdxa_0055F330;
	SONIC_OBJECTS[44] = &objectdxa_0057BC44;
	SONIC_OBJECTS[45] = &objectdxa_0056998C;
	SONIC_OBJECTS[46] = &objectdxa_00569594;
	SONIC_OBJECTS[47] = &objectdxa_005812AC;
	SONIC_OBJECTS[48] = &objectdxa_00569DEC;
	SONIC_OBJECTS[49] = &objectdxa_00569594;
	SONIC_OBJECTS[50] = &objectdxa_00569E20;
	SONIC_OBJECTS[51] = &objectdxa_00569CE8;
	SONIC_OBJECTS[52] = &objectdxa_005698F0;
	SONIC_OBJECTS[54] = &objectdxa_006837E8;
	SONIC_OBJECTS[55] = &objectdxa_00682EF4;
	SONIC_OBJECTS[58] = &objectdxa_00581FB8;
	SONIC_OBJECTS[59] = &objectdxa_005818AC;
	SONIC_OBJECTS[60] = &objectdxa_00582CC0;
	SONIC_OBJECTS[61] = &objectdxa_005825A4;
	SONIC_OBJECTS[62] = &objectdxa_00565520;
	SONIC_OBJECTS[63] = &objectdxa_00583284;
	SONIC_OBJECTS[64] = &objectdxa_00583904;
	SONIC_OBJECTS[65] = &objectdxa_00585EB4;
	SONIC_OBJECTS[66] = &objectdxa_005729CC;
	SONIC_OBJECTS[67] = &objectdxa_0057BC44;
	SONIC_ACTIONS[0]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[1]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[2]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[3]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[4]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[5]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[6]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[7]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[8]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[9]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[10]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[11]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[12]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[13]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[14]->object = &objectdxa_005729CC;
	SONIC_ACTIONS[15]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[16]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[17]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[18]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[19]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[20]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[21]->object = &objectdxa_0057BC44;
	SONIC_ACTIONS[22]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[23]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[27]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[28]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[29]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[30]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[31]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[32]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[33]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[34]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[35]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[36]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[37]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[38]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[39]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[40]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[41]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[42]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[43]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[44]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[45]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[46]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[47]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[48]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[49]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[50]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[51]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[52]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[53]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[54]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[55]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[56]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[57]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[58]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[59]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[60]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[61]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[62]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[63]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[64]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[65]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[66]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[67]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[68]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[69]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[70]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[71]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[72]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[87]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[88]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[89]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[90]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[91]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[92]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[93]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[94]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[95]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[96]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[97]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[98]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[99]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[100]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[101]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[102]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[103]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[104]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[105]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[106]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[107]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[108]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[109]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[113]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[114]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[115]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[116]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[117]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[118]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[119]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[120]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[121]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[122]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[123]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[124]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[125]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[126]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[127]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[128]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[129]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[134]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[135]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[136]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[137]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[145]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[146]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[147]->object = &objectdxa_0056AF50;
	SONIC_ACTIONS[148]->object = &objectdxa_0056AF50;
	SONIC_MODELS[0] = &attachdxa_0055F304;
	SONIC_MODELS[1] = &attachdxa_00560DA4;
	SONIC_MODELS[2] = &attachdxa_005735AC;
	SONIC_MODELS[3] = &attachdxa_00573DFC;
	SONIC_MODELS[4] = &attachdxa_0057464C;
	SONIC_MODELS[5] = &attachdxa_0057525C;
	SONIC_MODELS[6] = &attachdxa_00575AB4;
	SONIC_MODELS[7] = &attachdxa_0057630C;
	SONIC_MODELS[8] = &attachdxa_00569568;
	SONIC_MODELS[9] = &attachdxa_00579C68;
	SONIC_MOTIONS[0] = &SONIC_MOTIONSDXA_0;
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_AthleticDX);
	WriteData((NJS_OBJECT**)0x00664C3E, &FingerDX);
	WriteData((NJS_OBJECT**)0x0069E24B, &FingerDX);
	WriteData((NJS_OBJECT**)0x006D010C, &FingerDX);
	WriteData((NJS_OBJECT**)0x006D711E, &FingerDX);
}

void Init_SSonicAthleticDX()
{
	SONIC_OBJECTS[22] = &objectdxa_0062DE88;
	SONIC_OBJECTS[23] = &objectdxa_00626AB4;
	SONIC_OBJECTS[24] = &objectdxa_00626C44;
	SONIC_OBJECTS[25] = &objectdxa_0062840C;
	SONIC_OBJECTS[26] = &objectdxa_00627BF0;
	SONIC_OBJECTS[27] = &objectdxa_006276D8;
	SONIC_OBJECTS[28] = &objectdxa_00624E3C;
	SONIC_OBJECTS[29] = &objectdxa_00624FCC;
	SONIC_OBJECTS[30] = &objectdxa_006267F4;
	SONIC_OBJECTS[31] = &objectdxa_00625FD8;
	SONIC_OBJECTS[32] = &objectdxa_00625AA8;
	SONIC_OBJECTS[33] = &objectdxa_00623474;
	SONIC_OBJECTS[34] = &objectdxa_00623604;
	SONIC_OBJECTS[35] = &objectdxa_00624B78;
	SONIC_OBJECTS[36] = &objectdxa_00624308;
	SONIC_OBJECTS[37] = &objectdxa_00623C14;
	SONIC_OBJECTS[38] = &objectdxa_00621AC4;
	SONIC_OBJECTS[39] = &objectdxa_00621C54;
	SONIC_OBJECTS[40] = &objectdxa_006231E0;
	SONIC_OBJECTS[41] = &objectdxa_00622970;
	SONIC_OBJECTS[42] = &objectdxa_00622254;
	SONIC_ACTIONS[130]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[131]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[132]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[133]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[138]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[139]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[140]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[141]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[143]->object = &objectdxa_0062DE88;
	SONIC_ACTIONS[144]->object = &objectdxa_0062DE88;
	WriteJump((void*)0x007D0B50, InitSonicWeldInfo_AthleticDX);
	WriteJump((void*)0x007D14D0, InitNPCSonicWeldInfo_AthleticDX);
}

void _cdecl InitSSonicWeldInfo_PrincessDDC()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_DressShoeIndices_DC;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DC) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_DressShoeIndices_DC;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDC) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = SS_PrincessHeelDC;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDC) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = SS_PrincessHeelDC;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void _cdecl InitSSonicWeldInfo_PrincessDDX()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_DressShoeIndices_DX;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_DressShoeIndices_DX) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_DressShoeIndices_DX;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDX) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = SS_PrincessHeelDX;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDX) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = SS_PrincessHeelDX;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void _cdecl InitSSonicWeldInfo_PrincessADC()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_AthleticShoeIndices_DC;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_AthleticDC;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_AthleticDC) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_AthleticDC;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_AthleticShoeIndices_DC) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_AthleticShoeIndices_DC;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDC) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = SS_PrincessHeelDC;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDC) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = SS_PrincessHeelDC;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DressDC;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DressDC;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DressDC) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void _cdecl InitSSonicWeldInfo_PrincessADX()
{
	NJS_OBJECT* v0; // ebp@1
	NJS_OBJECT* v1; // ebp@1
	NJS_OBJECT* v2; // ebp@1
	NJS_OBJECT* v3; // ebp@1
	NJS_OBJECT* v4; // edi@1
	NJS_OBJECT* v5; // eax@1

	// Hand fix (The Mod Loader's chrmodels replacement system does that wrong)
	SONIC_OBJECTS[4] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[5] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child->sibling;
	SONIC_OBJECTS[63]->sibling = SONIC_OBJECTS[4];

	// Shoe fix
	SONIC_OBJECTS[15] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[16] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;
	SONIC_OBJECTS[20] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling;
	SONIC_OBJECTS[21] = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->child->child->sibling->sibling->child;

	// Sonic

	SonicWeldInfo[0].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[0].ModelA = SONIC_OBJECTS[1];
	SonicWeldInfo[0].ModelB = SONIC_OBJECTS[2];
	SonicWeldInfo[0].anonymous_5 = 0;
	SonicWeldInfo[0].VertexBuffer = 0;
	SonicWeldInfo[0].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[0].WeldType = 2;
	SonicWeldInfo[0].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[1].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[1].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[1].ModelB = SONIC_OBJECTS[3];
	SonicWeldInfo[1].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[1].WeldType = 2;
	SonicWeldInfo[1].anonymous_5 = 0;
	SonicWeldInfo[1].VertexBuffer = 0;
	SonicWeldInfo[1].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[2].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[2].ModelA = SONIC_OBJECTS[7];
	SonicWeldInfo[2].ModelB = SONIC_OBJECTS[8];
	SonicWeldInfo[2].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[2].WeldType = 2;
	SonicWeldInfo[2].anonymous_5 = 0;
	SonicWeldInfo[2].VertexBuffer = 0;
	SonicWeldInfo[2].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[3].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[3].ModelA = SONIC_OBJECTS[8];
	SonicWeldInfo[3].ModelB = SONIC_OBJECTS[9];
	SonicWeldInfo[3].VertIndexes = Sonic_LowerArmIndices_mod;
	SonicWeldInfo[3].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[3].WeldType = 2;
	SonicWeldInfo[3].anonymous_5 = 0;
	SonicWeldInfo[3].VertexBuffer = 0;

	SonicWeldInfo[4].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[4].ModelA = SONIC_OBJECTS[12];
	SonicWeldInfo[4].ModelB = SONIC_OBJECTS[13];
	SonicWeldInfo[4].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[4].WeldType = 2;
	SonicWeldInfo[4].anonymous_5 = 0;
	SonicWeldInfo[4].VertexBuffer = 0;
	SonicWeldInfo[4].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[5].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[5].ModelA = SONIC_OBJECTS[13];
	SonicWeldInfo[5].ModelB = SONIC_OBJECTS[14];
	SonicWeldInfo[5].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[5].WeldType = 2;
	SonicWeldInfo[5].anonymous_5 = 0;
	SonicWeldInfo[5].VertexBuffer = 0;
	SonicWeldInfo[5].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[6].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[6].ModelA = SONIC_OBJECTS[17];
	SonicWeldInfo[6].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[6].ModelB = SONIC_OBJECTS[18];
	SonicWeldInfo[6].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[6].WeldType = 2;
	SonicWeldInfo[6].anonymous_5 = 0;
	SonicWeldInfo[6].VertexBuffer = 0;

	SonicWeldInfo[7].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[7].ModelA = SONIC_OBJECTS[18];
	SonicWeldInfo[7].ModelB = SONIC_OBJECTS[19];
	SonicWeldInfo[7].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LegIndices_mod) / 2);
	SonicWeldInfo[7].WeldType = 2;
	SonicWeldInfo[7].anonymous_5 = 0;
	SonicWeldInfo[7].VertexBuffer = 0;
	SonicWeldInfo[7].VertIndexes = Sonic_LegIndices_mod;

	SonicWeldInfo[8].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[8].ModelA = SONIC_OBJECTS[15];
	SonicWeldInfo[8].ModelB = SONIC_OBJECTS[16];
	SonicWeldInfo[8].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[8].WeldType = 2;
	SonicWeldInfo[8].anonymous_5 = 0;
	SonicWeldInfo[8].VertexBuffer = 0;
	SonicWeldInfo[8].VertIndexes = Sonic_ShoeIndices_AthleticDX;

	SonicWeldInfo[9].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[9].ModelA = SONIC_OBJECTS[20];
	SonicWeldInfo[9].VertIndexes = Sonic_ShoeIndices_AthleticDX;
	SonicWeldInfo[9].ModelB = SONIC_OBJECTS[21];
	SonicWeldInfo[9].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_ShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[9].WeldType = 2;
	SonicWeldInfo[9].anonymous_5 = 0;
	SonicWeldInfo[9].VertexBuffer = 0;

	SonicWeldInfo[10].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[10].ModelA = SONIC_OBJECTS[10];
	SonicWeldInfo[10].ModelB = SONIC_OBJECTS[11];
	SonicWeldInfo[10].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[10].WeldType = 2;
	SonicWeldInfo[10].anonymous_5 = 0;
	SonicWeldInfo[10].VertexBuffer = 0;
	SonicWeldInfo[10].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[11].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[11].ModelA = SONIC_OBJECTS[4];
	SonicWeldInfo[11].ModelB = SONIC_OBJECTS[5];
	SonicWeldInfo[11].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[11].WeldType = 2;
	SonicWeldInfo[11].anonymous_5 = 0;
	SonicWeldInfo[11].VertexBuffer = 0;
	SonicWeldInfo[11].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[12].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[12].ModelA = SONIC_OBJECTS[58];
	SonicWeldInfo[12].ModelB = SONIC_OBJECTS[59];
	SonicWeldInfo[12].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LSShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[12].WeldType = 2;
	SonicWeldInfo[12].anonymous_5 = 0;
	SonicWeldInfo[12].VertexBuffer = 0;
	SonicWeldInfo[12].VertIndexes = Sonic_LSShoeIndices_AthleticDX;

	SonicWeldInfo[13].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[13].ModelA = SONIC_OBJECTS[60];
	SonicWeldInfo[13].ModelB = SONIC_OBJECTS[61];
	SonicWeldInfo[13].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LSShoeIndices_AthleticDX) / 2);
	SonicWeldInfo[13].WeldType = 2;
	SonicWeldInfo[13].anonymous_5 = 0;
	SonicWeldInfo[13].VertexBuffer = 0;
	SonicWeldInfo[13].VertIndexes = Sonic_LSShoeIndices_AthleticDX;

	SonicWeldInfo[14].BaseModel = SONIC_OBJECTS[0];
	SonicWeldInfo[14].ModelA = SONIC_OBJECTS[2];
	SonicWeldInfo[14].ModelB = SONIC_OBJECTS[63];
	SonicWeldInfo[14].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[14].WeldType = 2;
	SonicWeldInfo[14].anonymous_5 = 0;
	SonicWeldInfo[14].VertexBuffer = 0;
	SonicWeldInfo[14].VertIndexes = Sonic_LowerArmIndices_mod;

	// Super Sonic

	SonicWeldInfo[22].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[22].ModelA = SONIC_OBJECTS[23];
	SonicWeldInfo[22].ModelB = SONIC_OBJECTS[24];
	SonicWeldInfo[22].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[22].WeldType = 2;
	SonicWeldInfo[22].anonymous_5 = 0;
	SonicWeldInfo[22].VertexBuffer = 0;
	SonicWeldInfo[22].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[23].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[23].ModelA = SONIC_OBJECTS[24];
	SonicWeldInfo[23].ModelB = SONIC_OBJECTS[25];
	SonicWeldInfo[23].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[23].WeldType = 2;
	SonicWeldInfo[23].anonymous_5 = 0;
	SonicWeldInfo[23].VertexBuffer = 0;
	SonicWeldInfo[23].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[24].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[24].ModelA = SONIC_OBJECTS[28];
	SonicWeldInfo[24].ModelB = SONIC_OBJECTS[29];
	SonicWeldInfo[24].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_UpperArmIndices_mod) / 2);
	SonicWeldInfo[24].WeldType = 2;
	SonicWeldInfo[24].anonymous_5 = 0;
	SonicWeldInfo[24].VertexBuffer = 0;
	SonicWeldInfo[24].VertIndexes = Sonic_UpperArmIndices_mod;

	SonicWeldInfo[25].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[25].ModelA = SONIC_OBJECTS[29];
	SonicWeldInfo[25].ModelB = SONIC_OBJECTS[30];
	SonicWeldInfo[25].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_LowerArmIndices_mod) / 2);
	SonicWeldInfo[25].WeldType = 2;
	SonicWeldInfo[25].anonymous_5 = 0;
	SonicWeldInfo[25].VertexBuffer = 0;
	SonicWeldInfo[25].VertIndexes = Sonic_LowerArmIndices_mod;

	SonicWeldInfo[26].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[26].ModelA = SONIC_OBJECTS[33];
	SonicWeldInfo[26].ModelB = SONIC_OBJECTS[34];
	SonicWeldInfo[26].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[26].WeldType = 2;
	SonicWeldInfo[26].anonymous_5 = 0;
	SonicWeldInfo[26].VertexBuffer = 0;
	SonicWeldInfo[26].VertIndexes = Sonic_KneeIndices_mod;

	SonicWeldInfo[27].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[27].ModelA = SONIC_OBJECTS[34];
	SonicWeldInfo[27].ModelB = SONIC_OBJECTS[35];
	SonicWeldInfo[27].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[27].WeldType = 2;
	SonicWeldInfo[27].anonymous_5 = 0;
	SonicWeldInfo[27].VertexBuffer = 0;
	SonicWeldInfo[27].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[28].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[28].ModelA = SONIC_OBJECTS[38];
	SonicWeldInfo[28].VertIndexes = Sonic_KneeIndices_mod;
	SonicWeldInfo[28].ModelB = SONIC_OBJECTS[39];
	SonicWeldInfo[28].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_KneeIndices_mod) / 2);
	SonicWeldInfo[28].WeldType = 2;
	SonicWeldInfo[28].anonymous_5 = 0;
	SonicWeldInfo[28].VertexBuffer = 0;

	SonicWeldInfo[29].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[29].ModelA = SONIC_OBJECTS[39];
	SonicWeldInfo[29].ModelB = SONIC_OBJECTS[40];
	SonicWeldInfo[29].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessLeg) / 2);
	SonicWeldInfo[29].WeldType = 2;
	SonicWeldInfo[29].anonymous_5 = 0;
	SonicWeldInfo[29].VertexBuffer = 0;
	SonicWeldInfo[29].VertIndexes = SS_PrincessLeg;

	SonicWeldInfo[30].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[30].ModelA = SONIC_OBJECTS[36];
	SonicWeldInfo[30].ModelB = SONIC_OBJECTS[37];
	SonicWeldInfo[30].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDX) / 2);
	SonicWeldInfo[30].WeldType = 2;
	SonicWeldInfo[30].anonymous_5 = 0;
	SonicWeldInfo[30].VertexBuffer = 0;
	SonicWeldInfo[30].VertIndexes = SS_PrincessHeelDX;

	SonicWeldInfo[31].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[31].ModelA = SONIC_OBJECTS[41];
	SonicWeldInfo[31].ModelB = SONIC_OBJECTS[42];
	SonicWeldInfo[31].VertexPairCount = (uint8_t)(LengthOfArray(SS_PrincessHeelDX) / 2);
	SonicWeldInfo[31].WeldType = 2;
	SonicWeldInfo[31].anonymous_5 = 0;
	SonicWeldInfo[31].VertexBuffer = 0;
	SonicWeldInfo[31].VertIndexes = SS_PrincessHeelDX;

	SonicWeldInfo[32].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[32].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[32].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[32].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[32].WeldType = 2;
	SonicWeldInfo[32].anonymous_5 = 0;
	SonicWeldInfo[32].VertexBuffer = 0;
	SonicWeldInfo[32].VertIndexes = Sonic_HandIndices_DX;

	SonicWeldInfo[33].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[33].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[33].anonymous_5 = 0;
	SonicWeldInfo[33].VertexBuffer = 0;
	SonicWeldInfo[33].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[33].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[33].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[33].WeldType = 2;

	SonicWeldInfo[34].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[34].ModelA = SONIC_OBJECTS[31];
	SonicWeldInfo[34].ModelB = SONIC_OBJECTS[32];
	SonicWeldInfo[34].anonymous_5 = 0;
	SonicWeldInfo[34].VertexBuffer = 0;
	SonicWeldInfo[34].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[34].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[34].WeldType = 2;

	SonicWeldInfo[35].BaseModel = SONIC_OBJECTS[22];
	SonicWeldInfo[35].ModelA = SONIC_OBJECTS[26];
	SonicWeldInfo[35].anonymous_5 = 0;
	SonicWeldInfo[35].VertexBuffer = 0;
	SonicWeldInfo[35].VertIndexes = Sonic_HandIndices_DX;
	SonicWeldInfo[35].VertexPairCount = (uint8_t)(LengthOfArray(Sonic_HandIndices_DX) / 2);
	SonicWeldInfo[35].ModelB = SONIC_OBJECTS[27];
	SonicWeldInfo[35].WeldType = 2;

	SonicWeldInfo[36].BaseModel = 0;
	SonicWeldInfo[36].ModelA = 0;
	SonicWeldInfo[36].ModelB = 0;
	SonicWeldInfo[36].VertexPairCount = 0;
	SonicWeldInfo[36].VertexBuffer = 0;
	SonicWeldInfo[36].VertIndexes = 0;
}

void Init_SSonicPrincessDC()
{
	SONIC_OBJECTS[22] = &objectspdc_0062DE88;
	SONIC_OBJECTS[23] = &objectspdc_00626AB4;
	SONIC_OBJECTS[24] = &objectspdc_00626C44;
	SONIC_OBJECTS[25] = &objectspdc_0062840C;
	SONIC_OBJECTS[26] = &objectspdc_00627BF0;
	SONIC_OBJECTS[27] = &objectspdc_006276D8;
	SONIC_OBJECTS[28] = &objectspdc_00624E3C;
	SONIC_OBJECTS[29] = &objectspdc_00624FCC;
	SONIC_OBJECTS[30] = &objectspdc_006267F4;
	SONIC_OBJECTS[31] = &objectspdc_00625FD8;
	SONIC_OBJECTS[32] = &objectspdc_00625AA8;
	SONIC_OBJECTS[33] = &objectspdc_00623474;
	SONIC_OBJECTS[34] = &objectspdc_00623604;
	SONIC_OBJECTS[35] = &objectspdc_00624B78;
	SONIC_OBJECTS[36] = &objectspdc_00624308;
	SONIC_OBJECTS[37] = &objectspdc_00623C14;
	SONIC_OBJECTS[38] = &objectspdc_00621AC4;
	SONIC_OBJECTS[39] = &objectspdc_00621C54;
	SONIC_OBJECTS[40] = &objectspdc_006231E0;
	SONIC_OBJECTS[41] = &objectspdc_00622970;
	SONIC_OBJECTS[42] = &objectspdc_00622254;
	SONIC_ACTIONS[130]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[131]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[132]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[133]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[138]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[139]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[140]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[141]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[142]->object = &objectspdc_0062FE6C;
	SONIC_ACTIONS[143]->object = &objectspdc_0062DE88;
	SONIC_ACTIONS[144]->object = &objectspdc_0062DE88;
}

void Init_SSonicPrincessDX()
{
	SONIC_OBJECTS[22] = &objectspdx_0062DE88;
	SONIC_OBJECTS[23] = &objectspdx_00626AB4;
	SONIC_OBJECTS[24] = &objectspdx_00626C44;
	SONIC_OBJECTS[25] = &objectspdx_0062840C;
	SONIC_OBJECTS[26] = &objectspdx_00627BF0;
	SONIC_OBJECTS[27] = &objectspdx_006276D8;
	SONIC_OBJECTS[28] = &objectspdx_00624E3C;
	SONIC_OBJECTS[29] = &objectspdx_00624FCC;
	SONIC_OBJECTS[30] = &objectspdx_006267F4;
	SONIC_OBJECTS[31] = &objectspdx_00625FD8;
	SONIC_OBJECTS[32] = &objectspdx_00625AA8;
	SONIC_OBJECTS[33] = &objectspdx_00623474;
	SONIC_OBJECTS[34] = &objectspdx_00623604;
	SONIC_OBJECTS[35] = &objectspdx_00624B78;
	SONIC_OBJECTS[36] = &objectspdx_00624308;
	SONIC_OBJECTS[37] = &objectspdx_00623C14;
	SONIC_OBJECTS[38] = &objectspdx_00621AC4;
	SONIC_OBJECTS[39] = &objectspdx_00621C54;
	SONIC_OBJECTS[40] = &objectspdx_006231E0;
	SONIC_OBJECTS[41] = &objectspdx_00622970;
	SONIC_OBJECTS[42] = &objectspdx_00622254;
	SONIC_ACTIONS[130]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[131]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[132]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[133]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[138]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[139]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[140]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[141]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[142]->object = &objectspdx_0062FE6C;
	SONIC_ACTIONS[143]->object = &objectspdx_0062DE88;
	SONIC_ACTIONS[144]->object = &objectspdx_0062DE88;
}

extern "C" __declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions & helperFunctions)
{
	HMODULE handle = GetModuleHandle(L"CHRMODELS_orig");
	NJS_OBJECT** ___SONIC_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___SONIC_OBJECTS");
	NJS_ACTION** ___SONIC_ACTIONS = (NJS_ACTION**)GetProcAddress(handle, "___SONIC_ACTIONS");
	NJS_MODEL_SADX** ___SONIC_MODELS = (NJS_MODEL_SADX**)GetProcAddress(handle, "___SONIC_MODELS");
	NJS_MOTION** ___SONIC_MOTIONS = (NJS_MOTION**)GetProcAddress(handle, "___SONIC_MOTIONS");

	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	std::string Version_String = "Dreamcast";
	Version_String = config->getString("Sonic", "Version", "Dreamcast");
	std::string Style_String = "Athletic";
	Style_String = config->getString("Sonic", "Style", "Athletic");
	std::string Super_String = "Princess";
	Super_String = config->getString("Sonic", "Super", "Princess");

	if (Version_String == "Dreamcast") Version = Dreamcast;
	if (Version_String == "DX") Version = DX;
	if (Style_String == "Dress") Style = Dress;
	if (Style_String == "Athletic") Style = Athletic;
	if (Super_String == "Same") Super = Same;
	if (Super_String == "Princess") Super = Princess;
	delete config;

	// Replace the light speed dash aura color
	WriteCall((void*)0x4A1705, SetLSDColor);
	WriteJump((void*)0x4A1630, Sonic_DisplayLightDashModel_mod);

	//To make Super form work
	WriteData((NJS_TEXLIST**)0x55E65C, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E751, SSAura01);
	WriteData((NJS_TEXLIST**)0x55E712, SSAura02);
	WriteData((NJS_TEXLIST**)0x55E7CD, SSWaterThing);
	WriteData((NJS_TEXLIST**)0x55F2B3, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1D1, SSHomingTex1);
	WriteData((NJS_TEXLIST**)0x55F1DC, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F2BE, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F677, SSHomingTex2);
	WriteData((NJS_TEXLIST**)0x55F669, SSHomingTex3);
	SUPERSONIC_TEXLIST = SS_PVM;

	if (Version == Dreamcast)
	{
		if (Style == Dress)
		{
			Init_SonicDressDC();
			ReplacePVM("sonic", "SonieDressDC");
		}

		else if (Style == Athletic)
		{
			Init_SonicAthleticDC();
			ReplacePVM("sonic", "SonieSportDC");
		}

		if (Super == Princess)
		{
			Init_SSonicPrincessDC();
			ReplacePVM("supersonic", "SuperSonieSpecialDC");
			ReplacePVM("hypersonic", "HyperSonieSpecialDC");

			if (Style == Dress)
			{
				WriteJump((void*)0x007D0B50, InitSSonicWeldInfo_PrincessDDC);
			}

			else if (Style == Athletic)
			{
				WriteJump((void*)0x007D0B50, InitSSonicWeldInfo_PrincessADC);
			}
		}
		
		else if (Super == Same)
		{
			if (Style == Dress)
			{
				Init_SSonicDressDC();
				ReplacePVM("supersonic", "SuperSonieDressDC");
				ReplacePVM("hypersonic", "HyperSonieDressDC");
				WriteJump((void*)0x007D0B50, InitSonicWeldInfo_DressDC);
			}

			else if (Style == Athletic)
			{
				Init_SSonicAthleticDC();
				ReplacePVM("supersonic", "SuperSonieSportDC");
				ReplacePVM("hypersonic", "HyperSonieSportDC");
				WriteJump((void*)0x007D0B50, InitSonicWeldInfo_AthleticDC);
			}
		}
	}

	else if (Version == DX)
	{
		if (Style == Dress)
		{
			Init_SonicDressDX();
			ReplacePVM("sonic", "SonieDressDX");
		}

		else if (Style == Athletic)
		{
			Init_SonicAthleticDX();
			ReplacePVM("sonic", "SonieSportDX");
		}

		if (Super == Princess)
		{
			Init_SSonicPrincessDX();
			ReplacePVM("supersonic", "SuperSonieSpecialDX");
			ReplacePVM("hypersonic", "HyperSonieSpecialDX");

			if (Style == Dress)
			{
				WriteJump((void*)0x007D0B50, InitSSonicWeldInfo_PrincessDDX);
			}

			else if (Style == Athletic)
			{
				WriteJump((void*)0x007D0B50, InitSSonicWeldInfo_PrincessADX);
			}
		}

		else if (Super == Same)
		{
			if (Style == Dress)
			{
				Init_SSonicDressDX();
				ReplacePVM("supersonic", "SuperSonieDressDX");
				ReplacePVM("hypersonic", "HyperSonieDressDX");
				WriteJump((void*)0x007D0B50, InitSonicWeldInfo_DressDX);
			}

			else if (Style == Athletic)
			{
				Init_SSonicAthleticDX();
				ReplacePVM("supersonic", "SuperSonieSportDX");
				ReplacePVM("hypersonic", "HyperSonieSportDX");
				WriteJump((void*)0x007D0B50, InitSonicWeldInfo_AthleticDX);
			}
		}
	}

	//Replace Sonic on Tornado
	Tornado_init(helperFunctions);

	//Replace textures
	ReplacePVM("son_eff", "sonie_eff");
}

extern "C" __declspec(dllexport) const ModInfo SADXModInfo = { ModLoaderVer };
