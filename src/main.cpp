#include <mod/amlmod.h>
#include <mod/config.h>

MYMODCFG(com.daniloszk.getposition, GetPosition, 1.0.0, DaniloSZK)

#include "pch.h"

#include "GetPosition.h"

ModData* modData = new ModData("getPosition");
Logger* localLogger = new Logger("getPosition");

extern "C" void OnModPreLoad()
{
    fileLog->Clear();
    fileLog->Log("Log initialized");
    fileLog->Log("OnModPreLoad");
}

extern "C" void OnModLoad()
{
    fileLog->Log("OnModLoad");

    loadInterface(&cleo, "CLEO", true);
    if(!cleo) return;

    loadInterface(&menuSZK, "MenuSZK");
    if(!menuSZK) return;

    loadInterface(&sautils, "SAUtils");
    if(!sautils) return;

    fileLog->Log("Finding addresses...");

    DoHooks();

    fileLog->Log("Initializing mod...");

    menuSZK->onGameUpdate->Add([]() {
        OnGameUpdate();
    });

    fileLog->Log("Mod loaded!");
}