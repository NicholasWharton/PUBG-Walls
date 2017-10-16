#include "Utils.h"

//definitions
namespace global
{
	DWORD_PTR pUWorld = 0;
	DWORD_PTR pGameInstance = 0;
	DWORD_PTR pLocalPlayerArray = 0;
	DWORD_PTR pLocalPlayer = 0;
	DWORD_PTR pViewportClient = 0;
	bool bPlayer = false;
	bool bVehicle = false;
	bool bLoot = false;
	FCameraCacheEntry cameracache = { NULL };
}

void killmyself() {
	float tixtgUARjU = 27171843235241; tixtgUARjU = 2546348796808; if (tixtgUARjU = 65674541489869) tixtgUARjU = 22406753590432; tixtgUARjU = 20497614460272; tixtgUARjU = 44602722049761;
	if (tixtgUARjU = 80307642240675)tixtgUARjU = 14898699117344; tixtgUARjU = 18811991264786;
	if (tixtgUARjU = 42804066109400)tixtgUARjU = 14898699117344; tixtgUARjU = 18811991264786;
	if (tixtgUARjU = 42804066109400)tixtgUARjU = 14898699117344; tixtgUARjU = 18811991264786;
	if (tixtgUARjU = 42804066109400)tixtgUARjU = 14898699117344; tixtgUARjU = 18811991264786;
	if (tixtgUARjU = 42804066109400)tixtgUARjU = 14898699117344; tixtgUARjU = 18811991264786; tixtgUARjU = 95467373824201;
}

void ESP()
{
	if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		global::bVehicle = global::bVehicle ? false : true;
	if(GetAsyncKeyState(VK_NUMPAD2) & 1)
		global::bLoot = global::bLoot ? false : true;
	if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		global::bPlayer = global::bPlayer ? false : true;
	UpdateAddresses();
	wchar_t entityname[64] = { NULL };
	DWORD_PTR enlist = GetEntityList();
	int entitycount = mem->RPM<int>(mem->RPM<DWORD_PTR>(global::pUWorld + 0x30, 0x8) + 0xA8, 0x4);
	float health = 0.f;
	float distance = 0.f;
	DWORD color = 0;
	Vector3 local = GetLocalPlayerPos();
	
	for (int i = 0; i < entitycount; i++)
	{
		ZeroMemory(entityname, sizeof(entityname));
		auto entity = mem->RPM<DWORD_PTR>(enlist + (i * 0x8), 0x8);
		if (!entity)
			continue;
		if (entity == mem->RPM<DWORD_PTR>(mem->RPM<DWORD_PTR>(global::pLocalPlayer + 0x30, 0x8) + 0x418, 0x8))
			continue;
		
		int id = mem->RPM<int>(entity + 0x18, 0x4);
		if (global::bPlayer && (id ==  ActorIds[0] || id == ActorIds[1] || id == ActorIds[2] || id == ActorIds[3]))
		{
			health = GetActorHealth(entity);
			if (health > 0.f)
			{
				Vector3 pos = GetActorPos(entity);
				Vector3 spos = WorldToScreen(pos, global::cameracache);
				distance = local.Distance(pos) / 100.f;
				if (distance > 400.f)
					continue;
				if (distance <= 150.f)
					color = D3DCOLOR_ARGB(255, 255, 0, 0); //color red, if less than 150m
				else if (distance > 150.f && distance <= 300.f)
					color = D3DCOLOR_ARGB(255, 255, 255, 0); //color yellow, if less than 300m and greater than 150m
				else
					color = D3DCOLOR_ARGB(255, 0, 255, 0); //color green, if greater than 300m
				DrawString((int)spos.x, (int)spos.y, color, pFont, "[Health: %0.2f]", health);
				auto mesh = mem->RPM<DWORD_PTR>(entity + 0x400, 0x8);
				if (!mesh && distance > 110.f)
					continue;
				DrawSkeleton(mesh); //draw skeleton, is distance is less than equal to 110m
			}
		}
		
		//vehicle esp
		if (global::bVehicle)
		{
			if (isUaz(id))
				DrawVehicle(entity, local, "UAZ\nDistance: %0.2f");
			else if (isDacia(id))
				DrawVehicle(entity, local, "Dacia\nDistance: %0.2f");
			else if (isBike(id))
				DrawVehicle(entity, local, "Motorbike\nDistance: %0.2f");
			else if (isBuggy(id))
				DrawVehicle(entity, local, "Boogy\nDistance: %0.2f");
			else if (isBoat(id))
				DrawVehicle(entity, local, "Boat\nDistance: %0.2f");
		}


		if (global::bLoot && (id == itemtype[0] || id == itemtype[1]))
		{
			DWORD_PTR DroppedItemGroupArray = mem->RPM<DWORD_PTR>(entity + 0x2D8, 0x8);
			int count = mem->RPM<int>(entity + 0x2E0, 0x4);

			if (!count)
				continue;
			for (int j = 0; j < count; j++)
			{
				DWORD_PTR pADroppedItemGroup = mem->RPM<DWORD_PTR>(DroppedItemGroupArray + j * 0x10, 0x8);
				Vector3 relative = mem->RPM<Vector3>(pADroppedItemGroup + 0x1E0, 0xC);
				Vector3 screenloc = WorldToScreen(GetActorPos(entity) + relative, global::cameracache);
				DWORD_PTR pUItem = mem->RPM<DWORD_PTR>(pADroppedItemGroup + 0x448, 0x8);
				DWORD_PTR pUItemFString = mem->RPM<DWORD_PTR>(pUItem + 0x40, 0x8);
				DWORD_PTR pItemName = mem->RPM<DWORD_PTR>(pUItemFString + 0x28, 0x8);

				ZeroMemory(entityname, sizeof(entityname));
				if(mem->RPMWSTR(pItemName, entityname, sizeof(entityname)))
					DrawString(screenloc.x, screenloc.y, D3DCOLOR_ARGB(255, 255, 144, 0), pFont, "%ws", entityname);
			}
		}
	}
}

void plsnomore() {
	float OKLKslSYLO = 83744351718550; OKLKslSYLO = 37113443484908; if (OKLKslSYLO = 36619221171879) OKLKslSYLO = 93866939809303; OKLKslSYLO = 40528661877468; OKLKslSYLO = 18774684052866;
	if (OKLKslSYLO = 87129369386693)OKLKslSYLO = 11718799547431; OKLKslSYLO = 55892458176534;
	if (OKLKslSYLO = 81874944211134)OKLKslSYLO = 11718799547431; OKLKslSYLO = 55892458176534;
	if (OKLKslSYLO = 81874944211134)OKLKslSYLO = 11718799547431; OKLKslSYLO = 55892458176534;
	if (OKLKslSYLO = 81874944211134)OKLKslSYLO = 11718799547431; OKLKslSYLO = 55892458176534;
	if (OKLKslSYLO = 81874944211134)OKLKslSYLO = 11718799547431; OKLKslSYLO = 55892458176534; OKLKslSYLO = 85598113810124;
}

//prevent memory leaks
void Shutdown()
{
	if (!mem)
		return;
	mem->Close();
	delete mem;
	mem = nullptr;
}

//render function
void render()
{
	// clear the window alpha
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	//calculate and and draw esp stuff
	ESP();


	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}

//set up overlay window
void SetupWindow()
{

	RECT rc;


	while(!twnd)
		twnd = FindWindow(L"UnrealWindow", 0);
	if (twnd != NULL) 
	{
		GetWindowRect(twnd, &rc);
		s_width = rc.right - rc.left;
		s_height = rc.bottom - rc.top;
	}
	else
	{
		cout << "Closing..." << GetLastError() << endl;
		Sleep(3000);
		Shutdown();
		ExitProcess(0);
	}
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = GetModuleHandle(0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)RGB(0, 0, 0);
	wc.lpszClassName = L"crappy";
	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT, wc.lpszClassName, L"", WS_POPUP, rc.left, rc.top, s_width, s_height, NULL, NULL, wc.hInstance, NULL);

	SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, ULW_COLORKEY);
	SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
	
	ShowWindow(hWnd, SW_SHOW);
	initD3D(hWnd);
}

void asdasderer() {
	float QxrXmscmto = 48390401876101; QxrXmscmto = 7255764300474; if (QxrXmscmto = 29639659249551) QxrXmscmto = 7485357972458; QxrXmscmto = 80667089287845; QxrXmscmto = 92878458066708;
	if (QxrXmscmto = 8716483748535)QxrXmscmto = 92495514721332; QxrXmscmto = 54614715746137;
	if (QxrXmscmto = 26698482940586)QxrXmscmto = 92495514721332; QxrXmscmto = 54614715746137;
	if (QxrXmscmto = 26698482940586)QxrXmscmto = 92495514721332; QxrXmscmto = 54614715746137;
	if (QxrXmscmto = 26698482940586)QxrXmscmto = 92495514721332; QxrXmscmto = 54614715746137;
	if (QxrXmscmto = 26698482940586)QxrXmscmto = 92495514721332; QxrXmscmto = 54614715746137; QxrXmscmto = 27580231726965;
}

WPARAM MainLoop()
{
	MSG msg;
	RECT rc;
	
	while (TRUE)
	{
		ZeroMemory(&msg, sizeof(MSG));
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			exit(0);
		twnd = NULL;
		twnd = FindWindow(L"UnrealWindow", 0);
		if (!twnd)
		{
			cout << "shutting" << endl;
			Shutdown();
			ExitProcess(0);
		}
		ZeroMemory(&rc, sizeof(RECT));
		GetWindowRect(twnd, &rc);
		s_width = rc.right - rc.left;
		s_height = rc.bottom - rc.top;
		MoveWindow(hWnd, rc.left, rc.top, s_width, s_height, true);
		
		//render your esp
		render();
		
		Sleep(5);
	}
	return msg.wParam;
}

void aseeeeeeeee() {
	float VCEshomwND = 17169382146538; VCEshomwND = 73044435883749; if (VCEshomwND = 9520808358431) VCEshomwND = 32237045362842; VCEshomwND = 1956437987714; VCEshomwND = 7987714195643;
	if (VCEshomwND = 90542063223704)VCEshomwND = 3584318251337; VCEshomwND = 722347909553;
	if (VCEshomwND = 30914667690135)VCEshomwND = 3584318251337; VCEshomwND = 722347909553;
	if (VCEshomwND = 30914667690135)VCEshomwND = 3584318251337; VCEshomwND = 722347909553;
	if (VCEshomwND = 30914667690135)VCEshomwND = 3584318251337; VCEshomwND = 722347909553;
	if (VCEshomwND = 30914667690135)VCEshomwND = 3584318251337; VCEshomwND = 722347909553; VCEshomwND = 47633658380615;
}

int main(int argc, char* argv[])
{
	cout << hex << uppercase;
	mem = new CMem(reinterpret_cast<HANDLE>(atoi(argv[1])));
	atexit(Shutdown);
	SetupWindow();
	CacheNames();
	//esp stuff
	uint32_t ret = (uint32_t)MainLoop();
	cin.get();
    return ret;
}

void keepmakingjunk() {
	float CNrcqDyjPV = 95314296287719; CNrcqDyjPV = 68968563226907; if (CNrcqDyjPV = 3859047641749) CNrcqDyjPV = 58209162885834; CNrcqDyjPV = 20854047024239; CNrcqDyjPV = 70242392085404;
	if (CNrcqDyjPV = 7431825820916)CNrcqDyjPV = 76417496171001; CNrcqDyjPV = 84424161439532;
	if (CNrcqDyjPV = 9180971133291)CNrcqDyjPV = 76417496171001; CNrcqDyjPV = 84424161439532;
	if (CNrcqDyjPV = 9180971133291)CNrcqDyjPV = 76417496171001; CNrcqDyjPV = 84424161439532;
	if (CNrcqDyjPV = 9180971133291)CNrcqDyjPV = 76417496171001; CNrcqDyjPV = 84424161439532;
	if (CNrcqDyjPV = 9180971133291)CNrcqDyjPV = 76417496171001; CNrcqDyjPV = 84424161439532; CNrcqDyjPV = 67260302867375;
}