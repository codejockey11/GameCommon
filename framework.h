#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_
#define CURL_STATICLIB
#define _USE_MATH_DEFINES

#define MYMAKEFOURCC(str) ((DWORD)(BYTE)(str[0]) | ((DWORD)(BYTE)(str[1]) << 8) | ((DWORD)(BYTE)(str[2]) << 16) | ((DWORD)(BYTE)(str[3]) << 24 ))

#include <atlbase.h>
#include <comdef.h>
#include <CommCtrl.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1_3.h>
#include <d3d11.h>
#include <d3d11on12.h>
#include <d3d12.h>
#include <D3d12SDKLayers.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <dwrite.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <ExDisp.h>
#include <iphlpapi.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <memory.h>
#include <Mmdeviceapi.h>
#include <mmsystem.h>
#include <mysql.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strsafe.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <wininet.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <X3DAudio.h>
#include <xapofx.h>
#include <XAudio2.h>
#include <XAudio2fx.h>

#include <zlib.h>

#include <curl\curl.h>

using namespace DirectX;

#include <Functiondiscoverykeys_devpkey.h>

#include <wrl.h>
#include <wrl/client.h>
#include <wil/com.h>
#include "WebView2.h"
#include <WebView2EnvironmentOptions.h>

using namespace Microsoft::WRL;

static const DWORD c_IEND = MYMAKEFOURCC("IEND");
static const DWORD c_IDAT = MYMAKEFOURCC("IDAT");
static const DWORD c_bKGD = MYMAKEFOURCC("bKGD");
static const DWORD c_cHRM = MYMAKEFOURCC("cHRM");
static const DWORD c_cICP = MYMAKEFOURCC("cICP");
static const DWORD c_dSIG = MYMAKEFOURCC("dSIG");
static const DWORD c_eXIf = MYMAKEFOURCC("eXIf");
static const DWORD c_gAMA = MYMAKEFOURCC("gAMA");
static const DWORD c_hIST = MYMAKEFOURCC("hIST");
static const DWORD c_iCCP = MYMAKEFOURCC("iCCP");
static const DWORD c_iTXt = MYMAKEFOURCC("iTXt");
static const DWORD c_pHYs = MYMAKEFOURCC("pHYs");
static const DWORD c_sBIT = MYMAKEFOURCC("sBIT");
static const DWORD c_sPLT = MYMAKEFOURCC("sPLT");
static const DWORD c_sRGB = MYMAKEFOURCC("sRGB");
static const DWORD c_sTER = MYMAKEFOURCC("sTER");
static const DWORD c_tEXt = MYMAKEFOURCC("tEXt");
static const DWORD c_tIME = MYMAKEFOURCC("tIME");
static const DWORD c_tRNS = MYMAKEFOURCC("tRNS");
static const DWORD c_zTXt = MYMAKEFOURCC("zTXt");

static int32_t SwizzleInt32(char* bytes)
{
	int32_t out = 0;

	char outBytes[4] = {};

	outBytes[0] = bytes[3];
	outBytes[1] = bytes[2];
	outBytes[2] = bytes[1];
	outBytes[3] = bytes[0];

	memcpy((void*)&out, outBytes, 4);

	return out;
}


#pragma comment(lib, "msxml6.lib")

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Ws2_32.lib")

#pragma comment(lib, "XAudio2.lib")

#pragma comment(lib, "libmysql.lib")

#pragma comment(lib, "libcurl.lib")

#pragma comment(lib, "zlibd.lib")

static const float DEG2RAD = 0.01745329251994329576923690768489f; // M_PI / 180.0f
static const float RAD2DEG = 57.295779513082320876798154814105f; // 180 / M_PI
static const float EPSILON = 0.000050f;

static const int32_t MAX_ENTITIES = 1024;
static const int32_t MAX_SIDES = 128;
static const int32_t MAX_MATERIALS = 1024;
static const int32_t MAX_BRUSH_VERTICES = 256;

static const int32_t SHORT_STRING = 32;
static const int32_t LONG_STRING = 128;

static const int32_t MINUS_ONE = -1;

#define SAFE_DELETE(p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) { delete[] p; p = nullptr; }
