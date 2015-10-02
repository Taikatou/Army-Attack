#include "MainMenu.h"
#include "IwGx.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "game.h"
#include "s3eAudio.h"

MainMenu::~MainMenu()
{
}


void MainMenu::startGame(CTween* pTween)
{
	// Switch to game scene
	Game* game = (Game*)g_pSceneManager->Find("game");
	g_pSceneManager->SwitchTo(game);

	// Start game music

	s3eAudioPlay("audio/MainTheme.wav", 0);

	// Create new game
}


void MainMenu::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
	if (m_Manager->GetCurrent() == this)
	{

		Scene::Update(deltaTime, alphaMul);

		// Detect screen tap
		if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
		{
			g_pInput->Reset();
			if (playButton->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				// Animate the play button
				m_Tweener.Tween(0.5f,
					FLOAT, &playButton->m_Angle, 360.0f,
					FLOAT, &playButton->m_Alpha, 0.0f,
					ONCOMPLETE, startGame,
					END);
			}
		}
	}
}

void MainMenu::Render()
{
    Scene::Render();
}

void MainMenu::Init()
{
    Scene::Init();
	// Create menu background
	int w = IwGxGetScreenWidth();
	int h = IwGxGetScreenHeight();

	if (w > h)
	{
		int temp = w;
		w = h;
		h = temp;
	}

	CSprite* background = new CSprite();
	background->m_X = (float)w / 2;
	background->m_Y = (float)h / 2;
	background->SetImage(g_pResources->getMenuBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to screen size
	background->m_ScaleX = (float)w / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)h / background->GetImage()->GetHeight();
	AddChild(background);

	playButton = new CSprite();
	playButton->SetImage(g_pResources->getPlayButton());
	playButton->m_X = w / 2.0f;
	playButton->m_Y = h / 2.0f;
	playButton->m_W = playButton->GetImage()->GetWidth();
	playButton->m_H = playButton->GetImage()->GetHeight();
	playButton->m_AnchorX = 0.5f;
	playButton->m_AnchorY = 0.5f;
	playButton->m_ScaleX = (float)(w * 0.4) / playButton->GetImage()->GetWidth();
	playButton->m_ScaleY = playButton->m_ScaleX;
	AddChild(playButton);


	// Create pause menu sprite (docked to top of screen)
	optionsSprite = new CSprite();
	optionsSprite->SetImage(g_pResources->getSettingsButton());
	optionsSprite->m_X = (int)IwGxGetDeviceWidth() * 0.9;
	optionsSprite->m_Y = (int)IwGxGetDeviceHeight() * 0.9;
	optionsSprite->m_W = optionsSprite->GetImage()->GetWidth();
	optionsSprite->m_H = optionsSprite->GetImage()->GetHeight();
	optionsSprite->m_AnchorX = 0.5;
	optionsSprite->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.13) / optionsSprite->GetImage()->GetWidth();
	optionsSprite->m_ScaleY = optionsSprite->m_ScaleX;
	AddChild(optionsSprite);


	// Start menu music
	//Audio::PlayMusic("audio/frontend.mp3");
}

