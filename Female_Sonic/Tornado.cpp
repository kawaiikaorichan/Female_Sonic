#include "pch.h"

static ModelInfo* SonicPlaneMdl = nullptr;

DataPointer(NJS_OBJECT, Tornado1_Object, 0x28B1DA0);
DataPointer(NJS_OBJECT, Tornado2Before_Object, 0x27EB198);
DataPointer(NJS_OBJECT, Tornado2Change_Object, 0x280C158);

bool CheckIfSonicPlane(NJS_MODEL_SADX* model) {
	return SonicPlaneMdl->getlabel(model) != "";
}

void __cdecl TornadoCallBack(NJS_MODEL_SADX* model, int blend, int idk) {
	NonStaticFunctionPointer(void, sub_407FC0, (NJS_MODEL_SADX*, int), 0x407FC0);

	// If the currently drawn model is part of SONIC_PLANE, we use the character's texlist instead
	if (CheckIfSonicPlane(model)) {
		NJS_TEXLIST* tex_orig = CurrentTexList;

		njSetTexture(&SONIC_TEXLIST);
		sub_407FC0(model, blend);
		njSetTexture(tex_orig);
	}
	else {
		sub_407FC0(model, blend);
	}
}

void njAction_Queue_Tornado(NJS_ACTION* action, float frame, QueuedModelFlagsB flags) {
	DisplayAnimationFrame(action, frame, flags, 0.0, TornadoCallBack);
}

void TornadoDCD_init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SONICDCD_PLANE.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		SonicPlaneMdl = mdl;

		// We only replace Sonic's part of the plane
		Tornado1_Object.child->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Before_Object.child->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Change_Object.child->sibling->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();

		// Hack to use our own texture for Female Sonic's part of the plane, allowing compatibility with dc mods.
		WriteCall((void*)0x62753A, njAction_Queue_Tornado);
	}
	else {
		PrintDebug("[Female Sonic] Cannot open \"SONICDCD_PLANE.sa1mdl\".\n");
	}
}

void TornadoDCA_init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SONICDCA_PLANE.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		SonicPlaneMdl = mdl;

		// We only replace Sonic's part of the plane
		Tornado1_Object.child->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Before_Object.child->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Change_Object.child->sibling->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();

		// Hack to use our own texture for Female Sonic's part of the plane, allowing compatibility with dc mods.
		WriteCall((void*)0x62753A, njAction_Queue_Tornado);
	}
	else {
		PrintDebug("[Female Sonic] Cannot open \"SONICDCA_PLANE.sa1mdl\".\n");
	}
}

void TornadoDXD_init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SONICDXD_PLANE.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		SonicPlaneMdl = mdl;

		// We only replace Sonic's part of the plane
		Tornado1_Object.child->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Before_Object.child->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Change_Object.child->sibling->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();

		// Hack to use our own texture for Female Sonic's part of the plane, allowing compatibility with dc mods.
		WriteCall((void*)0x62753A, njAction_Queue_Tornado);
	}
	else {
		PrintDebug("[Female Sonic] Cannot open \"SONICDXD_PLANE.sa1mdl\".\n");
	}
}

void TornadoDXA_init(const HelperFunctions& helperFunctions) {
	ModelInfo* mdl = new ModelInfo(helperFunctions.GetReplaceablePath("system\\SONICDXA_PLANE.sa1mdl"));

	if (mdl->getformat() == ModelFormat_Basic) {
		SonicPlaneMdl = mdl;

		// We only replace Sonic's part of the plane
		Tornado1_Object.child->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Before_Object.child->sibling->sibling->child = SonicPlaneMdl->getmodel();
		Tornado2Change_Object.child->sibling->sibling->sibling->sibling->child = SonicPlaneMdl->getmodel();

		// Hack to use our own texture for Female Sonic's part of the plane, allowing compatibility with dc mods.
		WriteCall((void*)0x62753A, njAction_Queue_Tornado);
	}
	else {
		PrintDebug("[Female Sonic] Cannot open \"SONICDXA_PLANE.sa1mdl\".\n");
	}
}