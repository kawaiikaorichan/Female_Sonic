#pragma once

#pragma warning(push)
#pragma warning(disable: 4267 4838)

#include "SADXModLoader.h"

NJS_MATERIAL matlist_0006E6CC[] = {
	{ { 0xFFB2B2B2 }, { 0xFFFFFFFF }, 11, 3, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_FLAG_IGNORE_SPECULAR | NJD_DA_INV_SRC | NJD_SA_SRC },
	{ { 0xFFB2B2B2 }, { 0xFFFFFFFF }, 11, 3, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_FLAG_CLAMP_V | NJD_FLAG_CLAMP_U | NJD_FLAG_IGNORE_SPECULAR | NJD_FLAG_USE_TEXTURE | NJD_DA_INV_SRC | NJD_SA_SRC },
	{ { 0xFFB2B2B2 }, { 0xFFFFFFFF }, 11, 3, NJD_D_100 | NJD_FILTER_BILINEAR | NJD_FLAG_IGNORE_SPECULAR | NJD_FLAG_DOUBLE_SIDE | NJD_DA_INV_SRC | NJD_SA_SRC }
};

Sint16 poly_0006E6A4[] = {
	3, 3, 7, 2,
	0x8000u | 5, 2, 6, 7, 10, 11,
	3, 0, 4, 1,
	0x8000u | 5, 1, 5, 4, 9, 8
};

Sint16 poly_0006E658[] = {
	6, 10, 20, 6, 22, 2, 24,
	6, 27, 1, 16, 5, 18, 9,
	4, 8, 19, 9, 18,
	6, 19, 8, 17, 4, 25, 0,
	4, 11, 21, 10, 20,
	6, 3, 26, 7, 23, 11, 21
};

Sint16 poly_0006E608[] = {
	5, 14, 0, 13, 1, 12,
	10, 25, 0, 24, 14, 2, 15, 3, 12, 27, 1,
	3, 21, 23, 20,
	0x8000u | 7, 20, 22, 23, 24, 26, 27, 3,
	0x8000u | 6, 18, 16, 17, 27, 25, 24,
	3, 18, 19, 17
};

NJS_TEX uv_0006E588[] = {
	{ 204, 210 },
	{ 88, 212 },
	{ 230, 75 },
	{ 69, 76 },
	{ 248, 9 },
	{ 60, 9 },
	{ 61, 108 },
	{ 1, 107 },
	{ 64, 141 },
	{ 28, 139 },
	{ 79, 254 },
	{ 59, 253 },
	{ 238, 81 },
	{ 188, 80 },
	{ 220, 184 },
	{ 178, 185 },
	{ 75, 213 },
	{ 51, 213 },
	{ 59, 76 },
	{ 16, 76 },
	{ 52, 20 },
	{ 1, 18 },
	{ 29, 185 },
	{ 168, 184 },
	{ 8, 81 },
	{ 172, 81 },
	{ 249, 108 },
	{ 64, 107 },
	{ 209, 153 },
	{ 76, 139 },
	{ 195, 255 },
	{ 87, 254 }
};

NJS_MESHSET_SADX meshlist_0006E530[] = {
	{ NJD_MESHSET_TRIMESH | 0, 4, poly_0006E6A4, NULL, NULL, NULL, NULL, NULL },
	{ NJD_MESHSET_TRIMESH | 1, 6, poly_0006E658, NULL, NULL, NULL, uv_0006E588, NULL },
	{ NJD_MESHSET_TRIMESH | 2, 6, poly_0006E608, NULL, NULL, NULL, NULL, NULL }
};

NJS_VECTOR vertex_0006E3E0[] = {
	{ 0.37592f, -0.575543f, -0.309987f },
	{ -0.062272f, -0.614509f, 0.102222f },
	{ 0.337738f, 0.613524f, -0.233775f },
	{ -0.09728599f, 0.573958f, 0.114044f },
	{ 0.565339f, -0.525053f, -0.322063f },
	{ 0.418836f, -0.500466f, 0.003884f },
	{ 0.374932f, 0.445071f, 0.16427f },
	{ -0.090821f, 0.381253f, 0.252864f },
	{ 1.010213f, -0.442996f, -0.454079f },
	{ 0.9219739f, -0.427267f, -0.225773f },
	{ -0.044907f, 0.189608f, 0.597231f },
	{ -0.299989f, 0.149614f, 0.509587f },
	{ -0.149031f, 0.446801f, 0.142295f },
	{ -0.121935f, -0.5346209f, 0.133834f },
	{ 0.254129f, -0.576098f, -0.337102f },
	{ 0.222392f, 0.531709f, -0.326727f },
	{ 0.408255f, -0.254702f, 0.003436f },
	{ 0.556483f, -0.259832f, -0.322798f },
	{ 0.905403f, -0.191087f, -0.24248f },
	{ 0.995375f, -0.193517f, -0.471732f },
	{ -0.034236f, -0.134182f, 0.590462f },
	{ -0.281584f, -0.207105f, 0.507261f },
	{ 0.396343f, -0.176813f, 0.148606f },
	{ -0.063733f, -0.253782f, 0.241496f },
	{ 0.367881f, -0.293445f, -0.244496f },
	{ 0.373407f, -0.311144f, -0.298698f },
	{ -0.06916299f, -0.302943f, 0.102181f },
	{ -0.071026f, -0.317392f, 0.105177f }
};

NJS_VECTOR normal_0006E290[] = {
	{ 0.307295f, -0.769141f, -0.5603499f },
	{ -0.037686f, -0.8501059f, 0.525261f },
	{ 0.459314f, 0.7997929f, -0.386472f },
	{ -0.504241f, 0.841051f, 0.195896f },
	{ 0.06911f, -0.782366f, -0.6189719f },
	{ 0.352818f, -0.557146f, 0.751736f },
	{ 0.689423f, 0.506393f, 0.517941f },
	{ -0.735791f, 0.59504f, 0.323325f },
	{ 0.684052f, -0.490989f, -0.5394469f },
	{ 0.644878f, -0.483928f, 0.591562f },
	{ 0.160069f, 0.361909f, 0.918368f },
	{ -0.878554f, 0.3185f, 0.35595f },
	{ 0.291689f, 0.317121f, 0.902415f },
	{ 0.376523f, -0.337629f, 0.862692f },
	{ 0.116086f, -0.720395f, -0.68378f },
	{ 0.134054f, 0.45835f, -0.878604f },
	{ 0.128728f, 0.738253f, 0.6621259f },
	{ -0.234538f, 0.686045f, -0.688719f },
	{ 0.47884f, 0.727235f, 0.491774f },
	{ 0.556657f, 0.5873049f, -0.587542f },
	{ 0.254679f, -0.452245f, 0.854759f },
	{ -0.737119f, -0.618681f, 0.271827f },
	{ 0.801372f, -0.482685f, 0.353295f },
	{ -0.499616f, -0.864455f, 0.055683f },
	{ 0.8356709f, -0.548815f, -0.021359f },
	{ 0.297578f, 0.504356f, -0.8106f },
	{ 0.272725f, -0.624736f, 0.7316599f },
	{ 0.428162f, -0.08244199f, 0.899934f }
};

NJS_MODEL_SADX attach_000EEC68 = { vertex_0006E3E0, normal_0006E290, LengthOfArray<Sint32>(vertex_0006E3E0), meshlist_0006E530, matlist_0006E6CC, LengthOfArray<Uint16>(meshlist_0006E530), LengthOfArray<Uint16>(matlist_0006E6CC), { 0.355112f, -0.000493f, 0.06275f }, 0.845475f, NULL };

NJS_OBJECT Finger = { NJD_EVAL_UNIT_ANG | NJD_EVAL_UNIT_SCL | NJD_EVAL_BREAK, &attach_000EEC68, 1.035896f, 0.033785f, -0.042846f, 0, 0, 0, 1, 1, 1, NULL, NULL };

#pragma warning(pop)