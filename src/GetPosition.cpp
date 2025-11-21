#include "GetPosition.h"

#include "CleoFunctions.h"

bool hasFirstUpdated = false;

IContainer* labelTop = nullptr;
IContainer* mainContainer = nullptr;

int prevVehicle = 0;

void InitMod()
{
    
}

void OnGameUpdate()
{
    if(!hasFirstUpdated)
    {
        hasFirstUpdated = true;
        InitMod();
    }

    if(menuSZK->GetGlobalIntVariable("open_getposition") == 1)
    {
        menuSZK->SetGlobalIntVariable("open_getposition", 0);

        CreateWindow();
    }
}

void CreateWindow()
{
    fileLog->Log("Creating window");

    auto window = menuSZK->CreateWindow(400, 200, 800, "Get Position");

    fileLog->Log("Creating item");

    {
        auto item = window->AddText("On foot position: --");

        fileLog->Log("Setup event listener");

        item->titleContainer->onBeforeDraw->Add([item]() {

            auto pos = GetPlayerPosition();

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2);
            ss << "On foot position: " 
            << pos.x << ", " << pos.y << ", " << pos.z;

            item->titleContainer->text = ss.str();
        });
    }

    fileLog->Log("next?");

    {
        auto item = window->AddText("Vehicle position: --");
        item->titleContainer->onBeforeDraw->Add([item]() {

            auto carRef = GetVehiclePedIsUsing(GetPlayerActor());

            if(carRef <= 0)
            {
                item->titleContainer->text = "Vehicle position: NONE";
                return;
            }

            auto pos = GetCarPosition(carRef);

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2);
            ss << "Vehicle position: " 
            << pos.x << ", " << pos.y << ", " << pos.z;

            item->titleContainer->text = ss.str();
        });
    }

    {
        auto item = window->AddText("Angle:");
        item->titleContainer->onBeforeDraw->Add([item]() {

            float angle;
            auto carRef = GetVehiclePedIsUsing(GetPlayerActor());

            if(carRef > 0)
            {
                angle = GET_CAR_HEADING(carRef);
            } else {
                angle = 0;
            }

            std::stringstream ss;
            ss << std::fixed << std::setprecision(2);
            ss << "Angle: " << angle;

            item->titleContainer->text = ss.str();
        });
    }

    {
        auto button = window->AddButton("~r~" + GetTranslatedText("close"));
        button->onClick->Add([window]() {
            window->Close();
        });
    }
}