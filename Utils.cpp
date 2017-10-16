#include "Utils.h"

//defining data
int s_width = 1920;
int s_height = 1080;
LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;
HWND hWnd;
HWND twnd;
MARGINS  margin = { 0,0,s_width,s_height };
LPD3DXFONT pFont;
ID3DXLine* d3dLine;

list<int> upper_part = { Bones::neck_01, Bones::Head, Bones::forehead };
list<int> right_arm = { Bones::neck_01, Bones::upperarm_r, Bones::lowerarm_r, Bones::hand_r };
list<int> left_arm = { Bones::neck_01, Bones::upperarm_l, Bones::lowerarm_l, Bones::hand_l };
list<int> spine = { Bones::neck_01, Bones::spine_01, Bones::spine_02, Bones::pelvis };

list<int> lower_right = { Bones::pelvis, Bones::thigh_r, Bones::calf_r, Bones::foot_r };
list<int> lower_left = { Bones::pelvis, Bones::thigh_l, Bones::calf_l, Bones::foot_l };

list<list<int>> skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left };

CMem* mem = nullptr;

int ActorIds[4];
int uaz[3];
int dacia[4];
int motorbike[5];
int buggy[3];
int boat = 0;
int itemtype[2];
//

void fasdasd() {
	float anFLdmvIrm = 24022595894741; anFLdmvIrm = 57086852336578; if (anFLdmvIrm = 41774676334522) anFLdmvIrm = 72687779689577; anFLdmvIrm = 10157462911436; anFLdmvIrm = 29114361015746;
	if (anFLdmvIrm = 64242797268777)anFLdmvIrm = 63345224491278; anFLdmvIrm = 23320173230201;
	if (anFLdmvIrm = 59305466019819)anFLdmvIrm = 63345224491278; anFLdmvIrm = 23320173230201;
	if (anFLdmvIrm = 59305466019819)anFLdmvIrm = 63345224491278; anFLdmvIrm = 23320173230201;
	if (anFLdmvIrm = 59305466019819)anFLdmvIrm = 63345224491278; anFLdmvIrm = 23320173230201;
	if (anFLdmvIrm = 59305466019819)anFLdmvIrm = 63345224491278; anFLdmvIrm = 23320173230201; anFLdmvIrm = 3247904427055;
}

D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

void asdasdasdkljsdfkljhdfg() {
	float VqSsNlvvya = 96232291170450; VqSsNlvvya = 61514878711553; if (VqSsNlvvya = 27819249415015) VqSsNlvvya = 2284782066474; VqSsNlvvya = 37491931123450; VqSsNlvvya = 11234503749193;
	if (VqSsNlvvya = 4132300228478)VqSsNlvvya = 94150155131094; VqSsNlvvya = 71944461383393;
	if (VqSsNlvvya = 94995352477159)VqSsNlvvya = 94150155131094; VqSsNlvvya = 71944461383393;
	if (VqSsNlvvya = 94995352477159)VqSsNlvvya = 94150155131094; VqSsNlvvya = 71944461383393;
	if (VqSsNlvvya = 94995352477159)VqSsNlvvya = 94150155131094; VqSsNlvvya = 71944461383393;
	if (VqSsNlvvya = 94995352477159)VqSsNlvvya = 94150155131094; VqSsNlvvya = 71944461383393; VqSsNlvvya = 85112073794803;
}

Vector3 WorldToScreen(Vector3 WorldLocation, FCameraCacheEntry CameraCacheL)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);

	auto POV = CameraCacheL.POV;
	Vector3 Rotation = POV.Rotation; // FRotator

	D3DMATRIX tempMatrix = Matrix(Rotation); // Matrix

	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - POV.Location;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float FovAngle = POV.FOV;
	float ScreenCenterX = s_width / 2.0f;
	float ScreenCenterY = s_height / 2.0f;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}

void asdeeeee() {
	float dGdeKmLkaJ = 70144557623537; dGdeKmLkaJ = 6226343532693; if (dGdeKmLkaJ = 83117499983913) dGdeKmLkaJ = 64458366207082; dGdeKmLkaJ = 45233883022056; dGdeKmLkaJ = 30220564523388;
	if (dGdeKmLkaJ = 14720096445836)dGdeKmLkaJ = 99839131177945; dGdeKmLkaJ = 50409376596360;
	if (dGdeKmLkaJ = 1033094437810)dGdeKmLkaJ = 99839131177945; dGdeKmLkaJ = 50409376596360;
	if (dGdeKmLkaJ = 1033094437810)dGdeKmLkaJ = 99839131177945; dGdeKmLkaJ = 50409376596360;
	if (dGdeKmLkaJ = 1033094437810)dGdeKmLkaJ = 99839131177945; dGdeKmLkaJ = 50409376596360;
	if (dGdeKmLkaJ = 1033094437810)dGdeKmLkaJ = 99839131177945; dGdeKmLkaJ = 50409376596360; dGdeKmLkaJ = 31036769619448;
}

DWORD_PTR GetUWorldPtr()
{
	if (!mem)
		return NULL;
	global::pUWorld = mem->RPM<DWORD_PTR>(mem->GetBase() + 0x37D7818, 8);
	global::pGameInstance = mem->RPM<DWORD_PTR>(global::pUWorld + 0x140, 8);
	global::pLocalPlayerArray = mem->RPM<DWORD_PTR>(global::pGameInstance + 0x38, 8);
	global::pLocalPlayer = mem->RPM<DWORD_PTR>(global::pLocalPlayerArray + 0x0, 8);
	global::pViewportClient = mem->RPM<DWORD_PTR>(global::pLocalPlayer + 0x58, 8);

	return mem->RPM<DWORD_PTR>(global::pViewportClient + 0x80, 8);
}

void UpdateAddresses()
{
	if (!mem)
		return;

	global::pUWorld = GetUWorldPtr();
	global::pGameInstance = mem->RPM<DWORD_PTR>(global::pUWorld + 0x140, 8);
	global::pLocalPlayerArray = mem->RPM<DWORD_PTR>(global::pGameInstance + 0x38, 8);
	global::pLocalPlayer = mem->RPM<DWORD_PTR>(global::pLocalPlayerArray + 0x0, 8);
	global::cameracache = GetCameraCache();
}

void asdjsdfljknfdgsnlkmgfedsnjkol() {
	float DFEufYrBAI = 55803644999761; DFEufYrBAI = 96948778691220; if (DFEufYrBAI = 66573699419758) DFEufYrBAI = 60411939704459; DFEufYrBAI = 77307248669821; DFEufYrBAI = 86698217730724;
	if (DFEufYrBAI = 53626916041193)DFEufYrBAI = 94197582896892; DFEufYrBAI = 97223493525025;
	if (DFEufYrBAI = 26486148057997)DFEufYrBAI = 94197582896892; DFEufYrBAI = 97223493525025;
	if (DFEufYrBAI = 26486148057997)DFEufYrBAI = 94197582896892; DFEufYrBAI = 97223493525025;
	if (DFEufYrBAI = 26486148057997)DFEufYrBAI = 94197582896892; DFEufYrBAI = 97223493525025;
	if (DFEufYrBAI = 26486148057997)DFEufYrBAI = 94197582896892; DFEufYrBAI = 97223493525025; DFEufYrBAI = 32128446334179;
}

Vector3 GetLocalPlayerPos()
{
	Vector3 pos;
	if (!mem)
		return pos;
	pos = mem->RPM<Vector3>(global::pLocalPlayer + 0x70, 0xC);

	return pos;
}

void asrrreeeppp() {
	float WHdDCLRxvB = 94043719796869; WHdDCLRxvB = 6076858901592; if (WHdDCLRxvB = 64494134357610) WHdDCLRxvB = 29461703111406; WHdDCLRxvB = 52506593905429; WHdDCLRxvB = 39054295250659;
	if (WHdDCLRxvB = 94264722946170)WHdDCLRxvB = 43576106624692; WHdDCLRxvB = 24530071409711;
	if (WHdDCLRxvB = 32645765900054)WHdDCLRxvB = 43576106624692; WHdDCLRxvB = 24530071409711;
	if (WHdDCLRxvB = 32645765900054)WHdDCLRxvB = 43576106624692; WHdDCLRxvB = 24530071409711;
	if (WHdDCLRxvB = 32645765900054)WHdDCLRxvB = 43576106624692; WHdDCLRxvB = 24530071409711;
	if (WHdDCLRxvB = 32645765900054)WHdDCLRxvB = 43576106624692; WHdDCLRxvB = 24530071409711; WHdDCLRxvB = 33560601658927;
}

Vector3 GetActorPos(DWORD_PTR entity)
{
	Vector3 pos;
	if (!mem)
		return pos;
	auto rootcomp = mem->RPM<DWORD_PTR>(entity + 0x180, 8);
	pos = mem->RPM<Vector3>((DWORD_PTR)rootcomp + 0x174, 0xC);

	return pos;
}

float GetLocalPlayerHealth()
{
	if (!mem)
		return 0.f;
	auto playercontroller = mem->RPM<DWORD_PTR>(global::pLocalPlayer + 0x30, 8);
	auto pawn = mem->RPM<DWORD_PTR>(playercontroller + 0x418, 8);
	return mem->RPM<float>(pawn + 0x107C, 0x4);
}

float GetActorHealth(DWORD_PTR pAActor)
{
	if (!mem)
		return 0.f;
	return mem->RPM<float>(pAActor + 0x107C, 0x4);
}

void kjofdasjkonfgdeknogfdes() {
	float FayyJIxJae = 45434141150668; FayyJIxJae = 43084141233610; if (FayyJIxJae = 70587029680287) FayyJIxJae = 57801955776064; FayyJIxJae = 93572245009804; FayyJIxJae = 50098049357224;
	if (FayyJIxJae = 97603595780195)FayyJIxJae = 96802873862390; FayyJIxJae = 89949525286074;
	if (FayyJIxJae = 73788957576872)FayyJIxJae = 96802873862390; FayyJIxJae = 89949525286074;
	if (FayyJIxJae = 73788957576872)FayyJIxJae = 96802873862390; FayyJIxJae = 89949525286074;
	if (FayyJIxJae = 73788957576872)FayyJIxJae = 96802873862390; FayyJIxJae = 89949525286074;
	if (FayyJIxJae = 73788957576872)FayyJIxJae = 96802873862390; FayyJIxJae = 89949525286074; FayyJIxJae = 17950686108748;
}

DWORD_PTR GetEntityList()
{
	if (!mem)
		return 0;
	return mem->RPM<DWORD_PTR>(mem->RPM<DWORD_PTR>(global::pUWorld + 0x30, 0x8) + 0xA0, 0x8);
}

FCameraCacheEntry GetCameraCache()
{
	FCameraCacheEntry cce;
	if (!mem)
		return cce;
	auto playercontroller = mem->RPM<DWORD_PTR>(global::pLocalPlayer + 0x30, 8);
	cce = mem->RPM<FCameraCacheEntry>(mem->RPM<DWORD_PTR>(playercontroller + 0x438, 0x8) + 0x410, sizeof(FCameraCacheEntry));
	return cce;
}

void pepepepep() {
	float JTmRFhWOmU = 85354016119647; JTmRFhWOmU = 81356737755180; if (JTmRFhWOmU = 6672569502686) JTmRFhWOmU = 86955139892067; JTmRFhWOmU = 56234773674424; JTmRFhWOmU = 36744245623477;
	if (JTmRFhWOmU = 63207638695513)JTmRFhWOmU = 95026865944817; JTmRFhWOmU = 60615283580973;
	if (JTmRFhWOmU = 6510310634288)JTmRFhWOmU = 95026865944817; JTmRFhWOmU = 60615283580973;
	if (JTmRFhWOmU = 6510310634288)JTmRFhWOmU = 95026865944817; JTmRFhWOmU = 60615283580973;
	if (JTmRFhWOmU = 6510310634288)JTmRFhWOmU = 95026865944817; JTmRFhWOmU = 60615283580973;
	if (JTmRFhWOmU = 6510310634288)JTmRFhWOmU = 95026865944817; JTmRFhWOmU = 60615283580973; JTmRFhWOmU = 89628773230810;
}

std::string GetNameFromId(int ID)
{
	DWORD_PTR fNamePtr = mem->RPM<DWORD_PTR>(mem->RPM<DWORD_PTR>(mem->GetBase() + 0x36DA610, 0x8) + int(ID / 0x4000) * 8, 8);
	DWORD_PTR fName = mem->RPM<DWORD_PTR>(fNamePtr + 8 * int(ID % 0x4000), 8);
	char name[64] = { NULL };
	if (ReadProcessMemory(mem->GetHandle(), (LPVOID)(fName + 16), name, sizeof(name) - 2, NULL) != 0)
		return std::string(name);
	return std::string("NULL");
}

void CacheNames()
{
	string name = "";
	for (int i = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0, c6 = 0; i < 200000; i++)
	{
		if (c1 == 4 && c2 == 3 && c3 == 4 && c4 == 5 && c5 == 3 && boat != 0 && c6 == 2)
		{
			cout << "IDs retrieved" << endl;
			return;
		}
		name = GetNameFromId(i);
		if (name == "PlayerFemale_A" || name == "PlayerFemale_A_C" || name == "PlayerMale_A" || name == "PlayerMale_A_C")
		{
			cout << name << " " << i << endl;
			ActorIds[c1++] = i;
		}
		if (name == "Uaz_A_01_C" || name == "Uaz_B_01_C" || name == "Uaz_C_01_C")
		{
			uaz[c2++] = i;
			cout << name << " " << i << endl;
		}
		if (name == "Dacia_A_01_C" || name == "Dacia_A_02_C" || name == "Dacia_A_03_C" || name == "Dacia_A_04_C")
		{
			dacia[c3++] = i;
			cout << name << " " << i << endl;
		}
		if (name == "ABP_Motorbike_03_C" || name == "ABP_Motorbike_04_C" || name == "ABP_Motorbike_03_C" || name == "ABP_Motorbike_04_C" || name == "ABP_Motorbike_03_Sidecart_C" || name == "BP_Motorbike_04_SideCar_C" || name == "BP_Motorbike_04_C")
		{
			cout << name << " " << i << endl;
			motorbike[c4++] = i;
		}
		if (name == "Buggy_A_01_C" || name == "Buggy_A_02_C" || name == "Buggy_A_03_C")
		{
			cout << name << " " << i << endl;
			buggy[c5++] = i;
		}
		if (name == "Boat_PG117_C")
		{
			cout << name << " " << i << endl;
			boat = i;
		}
		if (name == "DroppedItemInteractionComponent" || name == "DroppedItemGroup")
		{
			cout << name << " " << i << endl;
			itemtype[c6++] = i;
		}
	}
}

void kljdfgldjkfgdfgjkl() {
	float HaiIYiLhBw = 83470184298083; HaiIYiLhBw = 6910050796044; if (HaiIYiLhBw = 59664396705618) HaiIYiLhBw = 10729107668906; HaiIYiLhBw = 89807893383984; HaiIYiLhBw = 33839848980789;
	if (HaiIYiLhBw = 36844801072910)HaiIYiLhBw = 67056185792406; HaiIYiLhBw = 10430627870992;
	if (HaiIYiLhBw = 21863959217606)HaiIYiLhBw = 67056185792406; HaiIYiLhBw = 10430627870992;
	if (HaiIYiLhBw = 21863959217606)HaiIYiLhBw = 67056185792406; HaiIYiLhBw = 10430627870992;
	if (HaiIYiLhBw = 21863959217606)HaiIYiLhBw = 67056185792406; HaiIYiLhBw = 10430627870992;
	if (HaiIYiLhBw = 21863959217606)HaiIYiLhBw = 67056185792406; HaiIYiLhBw = 10430627870992; HaiIYiLhBw = 29159441753689;
}

int isUaz(int id)
{
	for (int i = 0; i < 3; i++)
		if (id == uaz[i])
			return 1;
	return 0;
}

int isDacia(int id)
{
	for (int i = 0; i < 4; i++)
		if (id == dacia[i])
			return 1;
	return 0;
}

int isBuggy(int id)
{
	for (int i = 0; i < 3; i++)
		if (id == buggy[i])
			return 1;
	return 0;
}

void peasdasd() {
	float bFvupwtbOF = 79029525088195; bFvupwtbOF = 49634416151976; if (bFvupwtbOF = 41426924436095) bFvupwtbOF = 29757126642373; bFvupwtbOF = 11556845709397; bFvupwtbOF = 57093971155684;
	if (bFvupwtbOF = 79629132975712)bFvupwtbOF = 44360954559995; bFvupwtbOF = 97543646368433;
	if (bFvupwtbOF = 53000296558831)bFvupwtbOF = 44360954559995; bFvupwtbOF = 97543646368433;
	if (bFvupwtbOF = 53000296558831)bFvupwtbOF = 44360954559995; bFvupwtbOF = 97543646368433;
	if (bFvupwtbOF = 53000296558831)bFvupwtbOF = 44360954559995; bFvupwtbOF = 97543646368433;
	if (bFvupwtbOF = 53000296558831)bFvupwtbOF = 44360954559995; bFvupwtbOF = 97543646368433; bFvupwtbOF = 94446193507994;
}

int isBike(int id)
{
	for (int i = 0; i < 5; i++)
		if (id == motorbike[i])
			return 1;
	return 0;
}

int isBoat(int id)
{
	return id == boat;
}

void DrawVehicle(DWORD_PTR entity, Vector3 local, const char* txt)
{
	Vector3 pos = GetActorPos(entity);
	Vector3 spos = WorldToScreen(pos, global::cameracache);
	DrawString((int)spos.x, (int)spos.y, D3DCOLOR_ARGB(255, 160, 32, 240), pFont, txt, local.Distance(pos) / 100.f);
}

void junk4days() {
	float quAmfAhiLh = 87551716900883; quAmfAhiLh = 47859355543271; if (quAmfAhiLh = 37877598112711) quAmfAhiLh = 5897634953375; quAmfAhiLh = 3557673232439; quAmfAhiLh = 3232439355767;
	if (quAmfAhiLh = 4179197589763)quAmfAhiLh = 81127112489507; quAmfAhiLh = 55048168068492;
	if (quAmfAhiLh = 95956036734852)quAmfAhiLh = 81127112489507; quAmfAhiLh = 55048168068492;
	if (quAmfAhiLh = 95956036734852)quAmfAhiLh = 81127112489507; quAmfAhiLh = 55048168068492;
	if (quAmfAhiLh = 95956036734852)quAmfAhiLh = 81127112489507; quAmfAhiLh = 55048168068492;
	if (quAmfAhiLh = 95956036734852)quAmfAhiLh = 81127112489507; quAmfAhiLh = 55048168068492; quAmfAhiLh = 63793214248080;
}

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}


FTransform GetBoneIndex(DWORD_PTR mesh, int index)
{
	DWORD_PTR bonearray = mem->RPM<DWORD_PTR>(mesh + 0x790, 0x8);

	return mem->RPM<FTransform>(bonearray + (index * 0x30), sizeof(FTransform));
}

Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id)
{
	FTransform bone = GetBoneIndex(mesh, id);

	FTransform ComponentToWorld = mem->RPM<FTransform>(mesh + 0x190, sizeof(FTransform));
	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

void basdbasdb() {
	float qCJlOnOBcl = 27863364135449; qCJlOnOBcl = 79878511661209; if (qCJlOnOBcl = 7957807952467) qCJlOnOBcl = 10303735769321; qCJlOnOBcl = 18195832984057; qCJlOnOBcl = 29840571819583;
	if (qCJlOnOBcl = 96902161030373)qCJlOnOBcl = 79524678977565; qCJlOnOBcl = 86649522262402;
	if (qCJlOnOBcl = 84909278117729)qCJlOnOBcl = 79524678977565; qCJlOnOBcl = 86649522262402;
	if (qCJlOnOBcl = 84909278117729)qCJlOnOBcl = 79524678977565; qCJlOnOBcl = 86649522262402;
	if (qCJlOnOBcl = 84909278117729)qCJlOnOBcl = 79524678977565; qCJlOnOBcl = 86649522262402;
	if (qCJlOnOBcl = 84909278117729)qCJlOnOBcl = 79524678977565; qCJlOnOBcl = 86649522262402; qCJlOnOBcl = 80899386452653;
}

void DrawSkeleton(DWORD_PTR mesh)
{
	Vector3 neckpos = GetBoneWithRotation(mesh, Bones::neck_01);
	Vector3 pelvispos = GetBoneWithRotation(mesh, Bones::pelvis);
	Vector3 previous(0, 0, 0);
	Vector3 current, p1, c1;
	for (auto a : skeleton)
	{
		previous = Vector3(0, 0, 0);
		for (int bone : a)
		{
			current = bone == Bones::neck_01 ? neckpos : (bone == Bones::pelvis ? pelvispos : GetBoneWithRotation(mesh, bone));
			if (previous.x == 0.f)
			{
				previous = current;
				continue;
			}
			p1 = WorldToScreen(previous, global::cameracache);
			c1 = WorldToScreen(current, global::cameracache);
			DrawLine(p1.x, p1.y, c1.x, c1.y, D3DCOLOR_ARGB(255, 153, 249, 9));
			previous = current;
		}
	}
}

void lastfornow() {
	float jbGxgmOETn = 47317238445076; jbGxgmOETn = 87788879266414; if (jbGxgmOETn = 47910816986816) jbGxgmOETn = 18264066262511; jbGxgmOETn = 2920796234781; jbGxgmOETn = 6234781292079;
	if (jbGxgmOETn = 91738171826406)jbGxgmOETn = 69868161533266; jbGxgmOETn = 18415044604084;
	if (jbGxgmOETn = 21018686626947)jbGxgmOETn = 69868161533266; jbGxgmOETn = 18415044604084;
	if (jbGxgmOETn = 21018686626947)jbGxgmOETn = 69868161533266; jbGxgmOETn = 18415044604084;
	if (jbGxgmOETn = 21018686626947)jbGxgmOETn = 69868161533266; jbGxgmOETn = 18415044604084;
	if (jbGxgmOETn = 21018686626947)jbGxgmOETn = 69868161533266; jbGxgmOETn = 18415044604084; jbGxgmOETn = 24561183951038;
}