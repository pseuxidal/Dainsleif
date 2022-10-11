#include "OffsetsToml.h"

std::map<std::string, uintptr_t> OffsetsToml::Fetch(std::string& filename) {
    auto saveData = toml::parse(filename);
    dwClientState = toml::find_or(saveData, "dwClientState", dwClientState);
    dwEntityList = toml::find_or(saveData, "dwEntityList", dwEntityList);
    dwLocalPlayer = toml::find_or(saveData, "dwLocalPlayer", dwLocalPlayer);
    dwGlowObjectManager = toml::find_or(saveData, "dwGlowObjectManager", dwGlowObjectManager);
    dwForceAttack = toml::find_or(saveData, "dwForceAttack", dwForceAttack);
    dwForceForward = toml::find_or(saveData, "dwForceForward", dwForceForward);
    dwForceBackward = toml::find_or(saveData, "dwForceBackward", dwForceBackward);
    dwForceRight = toml::find_or(saveData, "dwForceRight", dwForceRight);
    dwForceLeft = toml::find_or(saveData, "dwForceLeft", dwForceLeft);
    dwForceJump = toml::find_or(saveData, "dwForceJump", dwForceJump);
    dwViewMatrix = toml::find_or(saveData, "dwViewMatrix", dwViewMatrix);

    dwClientState_State = toml::find_or(saveData, "dwClientState_State", dwClientState_State);
    dwClientState_MaxPlayer = toml::find_or(saveData, "dwClientState_MaxPlayer", dwClientState_MaxPlayer);
    dwClientState_ViewAngles = toml::find_or(saveData, "dwClientState_ViewAngles", dwClientState_ViewAngles);
    dwppDirect3DDevice9 = toml::find_or(saveData, "dwppDirect3DDevice9", dwppDirect3DDevice9);
    m_vecOrigin = toml::find_or(saveData, "m_vecOrigin", m_vecOrigin);
    m_iHealth = toml::find_or(saveData, "m_iHealth", m_iHealth);
    m_fFlags = toml::find_or(saveData, "m_fFlags", m_fFlags);
    m_vecViewOffset = toml::find_or(saveData, "m_vecViewOffset", m_vecViewOffset);
    m_dwBoneMatrix = toml::find_or(saveData, "m_dwBoneMatrix", m_dwBoneMatrix);
    m_iTeamNum = toml::find_or(saveData, "m_iTeamNum", m_iTeamNum);
    m_iGlowIndex = toml::find_or(saveData, "m_iGlowIndex", m_iGlowIndex);
    m_aimPunchAngle = toml::find_or(saveData, "m_aimPunchAngle", m_aimPunchAngle);
    m_iShotsFired = toml::find_or(saveData, "m_iShotsFired", m_iShotsFired);
    m_iCrosshairId = toml::find_or(saveData, "m_iCrosshairId", m_iCrosshairId);
    m_iFOV = toml::find_or(saveData, "m_iFOV", m_iFOV);
    m_bDormant = toml::find_or(saveData, "m_bDormant", m_bDormant);
    m_hActiveWeapon = toml::find_or(saveData, "m_hActiveWeapon", m_hActiveWeapon);
    m_iItemDefinitionIndex = toml::find_or(saveData, "m_iItemDefinitionIndex", m_iItemDefinitionIndex);
    m_bSpotted = toml::find_or(saveData, "m_bSpotted", m_bSpotted);
    m_bIsScoped = toml::find_or(saveData, "m_bIsScoped", m_bIsScoped);

    return std::map<std::string, uintptr_t>
            {
        {"dwClientState", dwClientState},
        {"dwForceAttack", dwForceAttack},
        {"dwEntityList", dwEntityList},
        {"dwGlowObjectManager", dwGlowObjectManager},
        {"dwLocalPlayer", dwLocalPlayer},
        {"dwForceForward", dwForceForward},
        {"dwForceBackward", dwForceBackward},
        {"dwForceRight", dwForceRight},
        {"dwForceLeft", dwForceLeft},
        {"dwForceJump", dwForceJump},
        {"dwViewMatrix", dwViewMatrix}
            };
}

//This is a wrap function to be passed to std::async
uintptr_t Scan(std::string dllName, std::string signature, int offset, uintptr_t moduleBase, int extra) {
    return PatternScanner(dllName.data(), signature.data(), offset).CalculateOffset(moduleBase, extra);
}

void OffsetsToml::Update(std::string& filename)
{
    uintptr_t a_entityList = std::async(std::launch::async, Scan, "client.dll", "\xBB????\x83??\x7C?", 1, Modules::client, 0).get();
    uintptr_t a_glowObjectManager = std::async(std::launch::async, Scan, "client.dll", "\x11?????\x83??\xC7?????????\x0F\x28?????\x68????", 2, Modules::client, 0).get();
    uintptr_t a_localPlayer = std::async(std::launch::async, Scan, "client.dll", "\x8D\x34\x85????\x89\x15????\x8B\x41\x08\x8B\x48\x04\x83\xF9\xFF", 3, Modules::client, 4).get();
    uintptr_t a_clientState = std::async(std::launch::async, Scan, "engine.dll", "\xA1????\x8B?????\x85?\x74?\x8B?", 1, Modules::engine, 0).get();
    uintptr_t a_forceAttack = std::async(std::launch::async, Scan, "client.dll", "\x89\x0D????\x8B\x0D????\x8B\xF2\x8B\xC1\x83\xCE\x04", 2, Modules::client, 0).get();
    uintptr_t a_forceBackward = std::async(std::launch::async, Scan, "client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 287, Modules::client, 0).get();
    uintptr_t a_forceForward = std::async(std::launch::async, Scan, "client.dll","\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 245, Modules::client, 0).get();
    uintptr_t a_forceJump = std::async(std::launch::async, Scan, "client.dll", "\x8B\x0D????\x8B\xD6\x8B\xC1\x83\xCA\x02", 2, Modules::client, 0).get();
    uintptr_t a_forceLeft = std::async(std::launch::async, Scan, "client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 465, Modules::client, 0).get();
    uintptr_t a_forceRight = std::async(std::launch::async, Scan, "client.dll", "\x55\x8B\xEC\x51\x53\x8A\x5D\x08", 512, Modules::client, 0).get();
    uintptr_t a_viewMatrix = std::async(std::launch::async, Scan, "client.dll", "\x0F\x10\x05????\x8D\x85????\xB9", 3, Modules::client, 176).get();

    const toml::value data {
            {"dwForceAttack", a_forceAttack},
            {"dwEntityList", a_entityList},
            {"dwGlowObjectManager", a_glowObjectManager},
            {"dwLocalPlayer", a_localPlayer},
            {"dwClientState", a_clientState},
            {"dwForceBackward", a_forceBackward},
            {"dwForceForward", a_forceForward},
            {"dwForceRight", a_forceRight},
            {"dwForceJump", a_forceJump},
            {"dwForceLeft", a_forceLeft},
            {"dwViewMatrix", a_viewMatrix},
            {"dwClientState_State", 0x108},
            {"dwClientState_MaxPlayer", 0x388},
            {"dwClientState_ViewAngles", 0x4D90},
            {"dwppDirect3DDevice9", 0xA7050},
            {"m_vecOrigin", 0x138},
            {"m_iHealth", 0x100},
            {"m_fFlags", 0x104},
            {"m_vecViewOffset", 0x108},
            {"m_dwBoneMatrix", 0x26A8},
            {"m_iTeamNum", 0xF4},
            {"m_iGlowIndex", 0x10488},
            {"m_aimPunchAngle", 0x303C},
            {"m_iShotsFired", 0x103E0},
            {"m_iCrosshairId", 0x11438},
            {"m_iFOV", 0x31F4},
            {"m_bDormant", 0xED},
            {"m_bSpotted", 0x93D},
            {"m_hActiveWeapon", 0x2F08},
            {"m_iItemDefinitionIndex", 0x2FBA},
            {"m_bIsScoped", 0x9974},
    };

    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}


// When you add new offset, go to Initialize(), Update(), Fetch(), Offsets.cpp, Offsets.h
void OffsetsToml::Initialize(std::string& filename)
{
    const toml::value data {
            {"dwClientState", 0x58CFDC},
            {"dwForceAttack", 0x320DE20},
            {"dwForceBackward", 0x320DE74},
            {"dwForceForward", 0x320DE68},
            {"dwForceJump", 0x528791C},
            {"dwForceLeft", 0x320DE80},
            {"dwForceRight", 0x320DE8C},
            {"dwEntityList", 0x4DDD93C},
            {"dwLocalPlayer", 0xDC14CC},
            {"dwGlowObjectManager", 0x5326640},
            {"dwViewMatrix", 0x4DCF254},
            {"dwClientState_State", 0x108},
            {"dwClientState_MaxPlayer", 0x388},
            {"dwClientState_ViewAngles", 0x4D90},
            {"dwppDirect3DDevice9", 0xA6050},
            {"m_vecOrigin", 0x138},
            {"m_iHealth", 0x100},
            {"m_fFlags", 0x104},
            {"m_vecViewOffset", 0x108},
            {"m_dwBoneMatrix", 0x26A8},
            {"m_iTeamNum", 0xF4},
            {"m_iGlowIndex", 0x10488},
            {"m_aimPunchAngle", 0x303C},
            {"m_iShotsFired", 0x103E0},
            {"m_iCrosshairId", 0x11838},
            {"m_iFOV", 0x31F4},
            {"m_bDormant", 0xED},
            {"m_bSpotted", 0x93D},
            {"m_hActiveWeapon", 0x2F08},
            {"m_iItemDefinitionIndex", 0x2FBA},
            {"m_bIsScoped", 0x9974},
    };

    std::ofstream file;
    file.open(filename, std::ios::out);
    file << data;
    file.close();
}
