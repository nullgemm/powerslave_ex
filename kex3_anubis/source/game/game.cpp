//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//      Game logic
//

#include "kexlib.h"
#include "renderMain.h"
#include "renderView.h"
#include "game.h"
#include "titlescreen.h"
#include "localization.h"
#include "world.h"
#include "player.h"

static kexGame gameLocal;
kexGame *kex::cGame = &gameLocal;

//
// map
//

COMMAND(map)
{
    int argc = kex::cCommands->GetArgc();

    if(argc != 2)
    {
        kex::cSystem->Printf("map <filename>\n");
        return;
    }

    if(gameLocal.World()->LoadMap(kex::cCommands->GetArgv(1)))
    {
        kex::cGame->SetGameState(GS_LEVEL);
    }
}

//
// kexGame::kexGame
//

kexGame::kexGame(void)
{
    this->smallFont = NULL;
    this->bigFont   = NULL;
    this->ticks     = 0;
    this->gameState = GS_NONE;

    this->titleScreen   = new kexTitleScreen;
    this->translation   = new kexTranslation;
    this->world         = new kexWorld;
    this->player        = new kexPlayer;
    this->renderView    = new kexRenderView;
}

//
// kexGame::~kexGame
//

kexGame::~kexGame(void)
{
    delete titleScreen;
    delete translation;
    delete world;
    delete player;
    delete renderView;
}

//
// kexGame::Init
//

void kexGame::Init(void)
{
    smallFont   = kexFont::Alloc("smallfont");
    bigFont     = kexFont::Alloc("bigfont");

    titleScreen->Init();
    translation->Init();

    player->Reset();
    gameState = GS_TITLE;
}

//
// kexGame::Shutdown
//

void kexGame::Shutdown(void)
{
    Mem_Purge(kexWorld::hb_world);
}

//
// kexGame::Tick
//

void kexGame::Tick(void)
{
    player->Cmd().BuildCommands();

    switch(gameState)
    {
    case GS_TITLE:
        titleScreen->Tick();
        break;

    case GS_LEVEL:
        break;

    default:
        break;
    }

    player->Cmd().Reset();
    ticks++;
}

//
// kexGame::Draw
//

void kexGame::Draw(void)
{
    switch(gameState)
    {
    case GS_TITLE:
        titleScreen->Draw();
        break;

    case GS_LEVEL:
        {
            // TEMP
            renderView->Render();
            kexRender::cBackend->LoadProjectionMatrix(renderView->ProjectionView());
            kexRender::cBackend->LoadModelViewMatrix(renderView->ModelView());
            kexRender::cUtils->DrawBoundingBox(kexBBox(
                kexVec3(-64, -128, -32),
                kexVec3(64, 128, 32)), 255, 0, 0);
        }
        break;

    default:
        break;
    }
}

//
// kexGame::ProcessInput
//

bool kexGame::ProcessInput(inputEvent_t *ev)
{
    switch(ev->type)
    {
    case ev_mouse:
        player->Cmd().SetTurnXY(ev->data1, ev->data2);
        break;

    case ev_keydown:
    case ev_mousedown:
        kex::cActions->ExecuteCommand(ev->data1, false, ev->type);
        break;

    case ev_keyup:
    case ev_mouseup:
        kex::cActions->ExecuteCommand(ev->data1, true, ev->type);
        break;
    }

    switch(gameState)
    {
    case GS_TITLE:
       if(titleScreen->ProcessInput(ev))
        {
            return true;
        }
        break;

    default:
        break;
    }

    return false;
}

//
// kexGame::DrawSmallString
//

void kexGame::DrawSmallString(const char *string, float x, float y, float scale, bool center,
                              byte r, byte g, byte b)
{
    kexRender::cBackend->SetBlend(GLSRC_SRC_ALPHA, GLDST_ONE_MINUS_SRC_ALPHA);
    smallFont->DrawString(string, x+1, y+1, scale, center, RGBA(0, 0, 0, 0xff));
    smallFont->DrawString(string, x, y, scale, center, RGBA(r, g, b, 0xff));
}

//
// kexGame::DrawBigString
//

void kexGame::DrawBigString(const char *string, float x, float y, float scale, bool center,
                            byte r, byte g, byte b)
{
    kexRender::cBackend->SetBlend(GLSRC_SRC_ALPHA, GLDST_ONE_MINUS_SRC_ALPHA);
    bigFont->DrawString(string, x+1, y+1, scale, center, RGBA(0, 0, 0, 0xff));
    bigFont->DrawString(string, x, y, scale, center, RGBA(r, g, b, 0xff));
}