#include "IwGx.h"
#include "IwHashString.h"

#include "game.h"
#include "main.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "pauseMenu.h"
#include <math.h>
#include <vector>
#include "s3eVibra.h"
#include "line.h"

// Grid background offset
#define NUM_ARMIES 6
#define NUM_PERSON 10
#define LIMIT_ARMY 9
#define BULLET_STRENGTH 20


Game::~Game()
{
	if (batallions != 0)
	{
		delete[] batallions;
	}
}

int lifesArray[6] = { 100, 150, 200, 250, 200, 250 };
// Initialise a round

// Starts a new game - Called from the main and pause menus

void Game::Update(float deltaTime, float alphaMul)
{
	if (!m_IsActive)
		return;
	if (m_Manager->GetCurrent() == this)
	{
		// Update base scene
		Scene::Update(deltaTime, alphaMul);

		if (!gameOver)
		{

			if (m_IsInputActive)
			{
				CheckInputEvents();
			}

			//up to here working
			if (enemyIndexCheck < enemyMen.size())
			{
				if (enemyMen.at(enemyIndexCheck)->m_Y == enemyMen.at(enemyIndexCheck)->getEndPosition())
				{
					if (abs(enemyMen.at(enemyIndexCheck)->m_Y - greatestDistance) < IwGxGetDeviceHeight() * 0.15)
					{
						if (!enemyMen.at(enemyIndexCheck)->getShooting())
						{
							ShootBullet(enemyMen.at(enemyIndexCheck), arrayMen, (int)(-(IwGxGetDeviceHeight() * 0.15)));
						}

					}
					else
					{
						if (enemyMen.at(enemyIndexCheck)->getShooting())
						{
							enemyMen.at(enemyIndexCheck)->setShooting(false);
							RemoveBullet(enemyMen.at(enemyIndexCheck)->getBulletIndex());
						}
						if (enemyMen.at(enemyIndexCheck)->m_Y - (float)(IwGxGetDeviceHeight() / 5) > greatestDistance)
						{
							MoveAI(enemyMen.at(enemyIndexCheck), (int)(enemyMen.at(enemyIndexCheck)->m_Y - (float)(IwGxGetDeviceHeight() / 5)));
						}
						else
						{
							MoveAI(enemyMen.at(enemyIndexCheck), (int)(greatestDistance + (IwGxGetDeviceHeight() * 0.13)));
						}
					}
				}

				if (CheckCollision(enemyMen.at(enemyIndexCheck), arrayMen))
				{
					coins += 10;
					RemoveMan(enemyIndexCheck, enemyMen);
					enemyLimit--;
				}

				enemyIndexCheck++;
			}
			else
			{
				enemyIndexCheck = 0;
			}

			if (armyIndexChecker < arrayMen.size())
			{
				if (arrayMen.at(armyIndexChecker)->m_Y == arrayMen.at(armyIndexChecker)->getEndPosition())
				{
					if (!arrayMen.at(armyIndexChecker)->getShooting())
					{
						ShootBullet(arrayMen.at(armyIndexChecker), enemyMen, (int)(IwGxGetDeviceHeight() * 0.15));
					}
				}

				if (CheckCollision(arrayMen.at(armyIndexChecker), enemyMen))
				{
					RemoveMan(armyIndexChecker, arrayMen);
					CheckGreatestDistance();
				}

				armyIndexChecker++;
			}
			else
			{
				if (CheckCollision(Castle, enemyMen))
				{
					gameOver = true;
					endGame = new CSprite();
					endGame->SetImage(g_pResources->getNewButton());
					endGame->m_X = (int)IwGxGetDeviceWidth() / 2;
					endGame->m_Y = (int)IwGxGetDeviceHeight() / 2;
					endGame->m_W = endGame->GetImage()->GetWidth();
					endGame->m_H = endGame->GetImage()->GetHeight();
					endGame->m_AnchorX = 0.5;
					endGame->m_ScaleX = (float)(IwGxGetDeviceWidth() / 4) / endGame->GetImage()->GetWidth();
					endGame->m_ScaleY = endGame->m_ScaleX;
					AddChild(endGame);
					s3eVibraStop();

					int i;
					for (i = 0; i < arrayMen.size(); i++)
					{
						if (arrayMen.at(i)->getShooting())
						{
							RemoveChild(bullets.at(arrayMen.at(i)->getBulletIndex()));
						}
					}

					for (i = 0; i < enemyMen.size(); i++)
					{
						if (enemyMen.at(i)->getShooting())
						{
							RemoveChild(bullets.at(enemyMen.at(i)->getBulletIndex()));
						}
					}

					bullets.clear();

				}
				armyIndexChecker = 0;
			}

			checker++;
			if (checker % 30 == 0)
			{
				if (rand() % 100 < 5)
				{
					if (enemyLimit < LIMIT_ARMY)
					{
						int upDown;
						bool fly = rand() % 10 < 2;
						if (fly)
						{
							int temp = (IwGxGetDeviceWidth() / 3);
							upDown = temp + (int)(rand() % (temp * 2));
						}
						else
						{
							upDown = (int)(rand() % (int)(IwGxGetDeviceWidth() / 3));
						}
						AddAI(upDown, (int)IwGxGetDeviceHeight() * 1.1, IwGxGetDeviceHeight() - (IwGxGetDeviceHeight() / 5), fly);
					}
				}
				checker = 0;
				coins++;
				label->m_Text = "Coins: ";
				char str[16];
				snprintf(str, 16, "%d", coins);
				label->m_Text += str;
			}
		}
		else
		{
			if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
			{
				g_pInput->Reset();
				if (endGame->HitTest(g_pInput->m_X, g_pInput->m_Y))
				{
					int i;
					for (i = 0; i < arrayMen.size(); i++)
					{
						RemoveChild(arrayMen.at(i));
					}

					for (i = 0; i < enemyMen.size(); i++)
					{
						RemoveChild(enemyMen.at(i));
					}

					RemoveChild(Castle);

					arrayMen.clear();
					enemyMen.clear();


					RemoveChild(endGame);

					endGame = NULL;

					NewGame();
				}
			}
		}
	}
}

void Game::CheckGreatestDistance()
{
	int temp = Castle->m_Y;
	int i;
	for (i = 0; i < arrayMen.size(); i++)
	{
		if (arrayMen.at(i)->m_Y > temp)
		{
			temp = arrayMen.at(i)->m_Y;
		}
	}

	if (temp != greatestDistance)
	{
		greatestDistance = temp;
	}
}

void Game::CheckInputEvents()
{
	if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
	{
		g_pInput->Reset();
		if (optionsSprite->HitTest(g_pInput->m_X, g_pInput->m_Y))
		{
			PauseMenu* pause = (PauseMenu*)g_pSceneManager->Find("pausemenu");
			g_pSceneManager->SwitchTo(pause);
		}

		if (dragging > -1)
		{
			arrayMen.at(dragging)->m_X = PreviousX;

			arrayMen.at(dragging)->m_Y = PreviousY;

			arrayMen.at(dragging)->m_ScaleX = (float)(arrayMen.at(dragging)->m_ScaleX / 1.1);
			arrayMen.at(dragging)->m_ScaleY = (float)(arrayMen.at(dragging)->m_ScaleY / 1.1);

			if (g_pInput->m_Y < greatestDistanceEnemy - (IwGxGetDeviceHeight() * 0.15))
			{
				int divThree = IwGxGetDeviceWidth() / 3;
				bool enter;
				if (!arrayMen.at(dragging)->getFlying())
				{
					enter = g_pInput->m_X < divThree;
				}
				else
				{
					enter = g_pInput->m_X > divThree;
				}
				if (enter)
				{
					arrayMen.at(dragging)->SetAtlas(g_pResources->getSoldierWalking(arrayMen.at(dragging)->getType()));

					arrayMen.at(dragging)->setEndPosition((int)g_pInput->m_Y);

					int dx = arrayMen.at(dragging)->m_X - g_pInput->m_X;
					int dy = arrayMen.at(dragging)->m_Y - g_pInput->m_Y;

					float distance_time = sqrt((double)dx*dx + dy*dy);

					distance_time /= arrayMen.at(dragging)->getSpeed();

					m_Tweener.Tween(distance_time,
						FLOAT, &arrayMen.at(dragging)->m_Y, (float)g_pInput->m_Y,
						FLOAT, &arrayMen.at(dragging)->m_X, (float)g_pInput->m_X,
						END);

					//this is working correctly
					CheckGreatestDistance();
				}
				else
				{
					arrayMen.at(dragging)->setEndPosition(PreviousY);
				}
			}
			else
			{
				arrayMen.at(dragging)->setEndPosition(PreviousY);
			}

			dragging = -1;

			if (tempPos != NULL)
			{
				RemoveChild(tempPos);
				tempPos = NULL;
			}
			g_pLine->setActive(false);
		}

		else if (touch > -1)
		{

			int temp = touch;
			touch = -1;
			if ((batallions[temp]->m_X > IwGxGetDeviceWidth() / 3 ^ temp >= 4) || ChoicePanal->HitTest(batallions[temp]->m_X, batallions[temp]->m_Y) || ((temp + 1) * 10) > coins)
			{
				m_Tweener.Tween(0.5f,
					FLOAT, &batallions[temp]->m_X, PreviousX,
					FLOAT, &batallions[temp]->m_Y, PreviousY,
					END);
			}
			else
			{
				if (limitArmy < LIMIT_ARMY)
				{
					coins -= (temp + 1) * 10;
					Man* tempSprite = new Man();
					tempSprite->SetAtlas(g_pResources->getSoldierWalking(temp - (temp % 2)));
					tempSprite->SetAnimDuration(2);
					tempSprite->SetAnimRepeat(-1);
					tempSprite->m_X = (int)batallions[temp]->m_X;
					tempSprite->m_Y = (int)IwGxGetDeviceHeight() * 0.1;
					tempSprite->m_W = tempSprite->GetImage()->GetWidth();
					tempSprite->m_H = tempSprite->GetImage()->GetHeight();
					tempSprite->m_AnchorX = 0.5;
					tempSprite->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.12) / tempSprite->GetImage()->GetWidth();
					tempSprite->m_ScaleY = tempSprite->m_ScaleX;
					tempSprite->setType(temp - (temp % 2));
					tempSprite->init(lifesArray[temp]);
					if (temp < 4)
					{
						tempSprite->setSpeed(IwGxGetDeviceHeight() / 20);
					}
					else
					{
						tempSprite->setSpeed(IwGxGetDeviceHeight() / 10);
					}

					int y = batallions[temp]->m_Y;

					if (y > greatestDistanceEnemy + (IwGxGetDeviceHeight() * 0.07))
					{
						y = greatestDistanceEnemy - (IwGxGetDeviceHeight() * 0.07);
					}
					if (y > greatestDistance)
					{
						greatestDistance = y;
					}

					tempSprite->setEndPosition(y);

					tempSprite->setWidth((IwGxGetDeviceWidth() * 0.12));
					tempSprite->setFlying(temp >= 4);


					AddChild(tempSprite);

					arrayMen.push_back(tempSprite);


					float time_taken = y - arrayMen.back()->m_Y;
					time_taken /= arrayMen.back()->getSpeed();

					m_Tweener.Tween(time_taken,
						FLOAT, &arrayMen.back()->m_Y, (float)y,
						END);


					limitArmy++;
				}


				batallions[temp]->m_X = PreviousX;
				batallions[temp]->m_Y = PreviousY;

			}

		}

	}
	else if (g_pInput->m_Touched && !g_pInput->m_PrevTouched)
	{
		CheckDragging();
		//check If the player is dragging a army man around
	}
}

void Game::WobbleSprite(CSprite* s)
{

}

void Game::CheckDragging()
{
	if (touch == -1)
	{
		int i;
		for (i = 0; i < NUM_ARMIES; i++)
		{
			if (batallions[i]->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				PreviousX = batallions[i]->m_X;
				PreviousY = batallions[i]->m_Y;
				WobbleSprite(batallions[i]);
				touch = i;
				return;
			}
		}
	}
	else
	{
		batallions[touch]->m_X = g_pInput->m_X;
		batallions[touch]->m_Y = g_pInput->m_Y;
	}

	if (dragging == -1)
	{
		int i;
		for (i = 0; i < arrayMen.size(); i++)
		{
			if (arrayMen.at(i)->HitTest(g_pInput->m_X, g_pInput->m_Y))
			{
				if (arrayMen.at(i)->getShooting())
				{
					OutputLine(i);
					RemoveBullet(arrayMen.at(i)->getBulletIndex());
					arrayMen.at(i)->setShooting(false);
					PreviousX = arrayMen.at(i)->m_X;
					PreviousY = arrayMen.at(i)->m_Y;
					arrayMen.at(i)->setEndPosition(-1);

					WobbleSprite(arrayMen.at(i));

					m_Tweener.Tween(0.5f,
						FLOAT, &arrayMen.at(i)->m_ScaleX, (float)(arrayMen.at(i)->m_ScaleX * 1.1),
						FLOAT, &arrayMen.at(i)->m_ScaleY, (float)(arrayMen.at(i)->m_ScaleY * 1.1),
						END);

					dragging = i;

					OutputLine(i);
					g_pLine->setFirstPoint(PreviousX, PreviousY);

					if (!arrayMen.at(i)->getFlying())
					{
						tempPos = new CSprite();
						tempPos->m_X = arrayMen.at(i)->m_X;
						tempPos->m_Y = arrayMen.at(i)->m_Y + (int)(IwGxGetDeviceWidth() * 0.06);
						tempPos->SetImage(g_pResources->getSelector());
						tempPos->m_W = tempPos->GetImage()->GetWidth();
						tempPos->m_H = tempPos->GetImage()->GetHeight();
						tempPos->m_AnchorX = 0.5;
						tempPos->m_AnchorY = 0.5;
						// Fit backgroundTwo to Device size
						tempPos->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.05) / tempPos->GetImage()->GetWidth();
						tempPos->m_ScaleY = tempPos->m_ScaleX;
						tempPos->m_Angle = 270.0f;
						AddChild(tempPos);
					}
				}
				return;
			}
		}
	}
	else
	{
		arrayMen.at(dragging)->m_X = g_pInput->m_X;
		arrayMen.at(dragging)->m_Y = g_pInput->m_Y;
		g_pLine->setSecondPoint(g_pInput->m_X, g_pInput->m_Y);
		if (!g_pLine->getActive())
		{
			g_pLine->setActive(true);
		}
	}
}

void Game::ShootBullet(Man*& Men, std::vector<Man*>& otherMen, int distance)
{
	CSprite* tempSprite = new CSprite();
	tempSprite->SetImage(g_pResources->getBullet());
	tempSprite->m_W = tempSprite->GetImage()->GetWidth();
	tempSprite->m_H = tempSprite->GetImage()->GetHeight();
	tempSprite->m_AnchorX = 0.5;
	tempSprite->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.01) / tempSprite->GetImage()->GetWidth();
	tempSprite->m_ScaleY = tempSprite->m_ScaleX;

	AddChild(tempSprite);

	bullets.push_back(tempSprite);

	Men->setBulletIndex(bullets.size() - 1);
	Men->setShooting(true);

	Men->SetAtlas(g_pResources->getSoldierShooting(Men->getType()));
	Men->SetAnimDuration(1.5f);
	Men->SetAnimRepeat(-1);

	if (Men->getFlying())
	{
		int temp = (int)(Men->getWidth() / 2);
		tempSprite->m_X = (int)Men->m_X - temp;
		tempSprite->m_Y = (int)Men->getEndPosition() + temp;

		bool shootDown = true;
		int i;
		for (i = 0; i < otherMen.size(); i++)
		{
			if (otherMen.at(i)->getFlying())
			{
				if (abs(otherMen.at(i)->m_Y - greatestDistance) < IwGxGetDeviceHeight() / 20)
				{
					shootDown = false;
					break;
				}
			}
		}

		if (shootDown)
		{
			m_Tweener.Tween(1.5f,
				FLOAT, &bullets.back()->m_Y, (float)(tempSprite->m_Y + distance),
				FLOAT, &bullets.back()->m_X, 0.0f,
				FLOAT, &bullets.back()->m_Alpha, 0.0f,
				REPEAT,
				END);

			return;
		}
	}


	tempSprite->m_X = (int)Men->m_X;
	tempSprite->m_Y = (int)Men->getEndPosition() + Men->getWidth();
	m_Tweener.Tween(1.5f,
		FLOAT, &bullets.back()->m_Y, (float)(tempSprite->m_Y + distance),
		FLOAT, &bullets.back()->m_Alpha, 0.0f,
		REPEAT,
		END);

}

void Game::RemoveBullet(int index)
{
	RemoveChild(bullets.at(index));
	bullets.erase(bullets.begin() + index);
	int m;
	for (m = 0; m < arrayMen.size(); m++)
	{
		if (arrayMen.at(m)->getBulletIndex() > index)
		{
			arrayMen.at(m)->setBulletIndex(arrayMen.at(m)->getBulletIndex() - 1);
		}
	}

	for (m = 0; m < enemyMen.size(); m++)
	{
		if (enemyMen.at(m)->getBulletIndex() > index)
		{
			enemyMen.at(m)->setBulletIndex(enemyMen.at(m)->getBulletIndex() - 1);
		}
	}
}

void Game::RemoveMan(int index, std::vector<Man*>& Men1)
{
	if (Men1.at(index)->getShooting())
	{
		RemoveBullet(Men1.at(index)->getBulletIndex());
	}

	RemoveChild(Men1.at(index));
	Men1.erase(Men1.begin() + index);
}

bool Game::CheckCollision(Destroyable* Men1, std::vector<Man*>& Men2)
{
	Man* i;
	int j;
	for (j = 0; j < Men2.size(); j++)
	{
		i = Men2.at(j);
		if (i->getShooting())
		{
			if (Men1->HitTest((int)bullets.at(i->getBulletIndex())->m_X, (int)bullets.at(i->getBulletIndex())->m_Y))
			{
				if (i->getShooting())
				{
					RemoveBullet(i->getBulletIndex());
					i->setShooting(false);
				}

				i->setEndPosition((int)i->m_Y);
				int temp = Men1->getLife();
				Men1->subtractFromLife(BULLET_STRENGTH);
				if (Men1->getDivisions() > 0 && (int)(temp / Men1->getDivisions()) != (int)(Men1->getLife() / Men1->getDivisions()))
				{
					Men1->SetImage(g_pResources->getCastleDivisions(Men1->getDivisions()));
					OutputLine(Men1->getDivisions() - 1);
					Men1->setDivisions(Men1->getDivisions() - 1);
					Men1->setLife(300);
					if (s3eVibraGetInt(S3E_VIBRA_AVAILABLE) != 0)
					{
						if (!s3eVibraGetInt(S3E_VIBRA_ENABLED))
						{
							s3eVibraSetInt(S3E_VIBRA_ENABLED, true);
						}

						s3eVibraVibrate(255, 1000);
					}
				}

				if (Men1->getLife() <= 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Game::AddAI(int x, int y, int Pos, bool type)
{
	enemyNumber--;
	enemyLimit++;
	Man* tempSprite = new Man();
	if (type)
	{
		tempSprite->setType(5);
		tempSprite->setSpeed(IwGxGetDeviceHeight() / 10);
	}

	else
	{
		tempSprite->setType(1);
		tempSprite->setSpeed(IwGxGetDeviceHeight() / 20);
	}

	tempSprite->SetAtlas(g_pResources->getSoldierWalking(tempSprite->getType()));
	tempSprite->SetAnimDuration(2);
	tempSprite->SetAnimRepeat(-1);
	tempSprite->m_X = x;
	tempSprite->m_Y = y;
	tempSprite->m_W = tempSprite->GetImage()->GetWidth();
	tempSprite->m_H = tempSprite->GetImage()->GetHeight();
	tempSprite->m_AnchorX = 0.5;
	tempSprite->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.12) / tempSprite->GetImage()->GetWidth();
	tempSprite->m_ScaleY = tempSprite->m_ScaleX;
	tempSprite->init(lifesArray[tempSprite->getType()]);
	tempSprite->setWidth(0);

	tempSprite->setDivisions(0);
	tempSprite->setFlying(type);
	enemyMen.push_back(tempSprite);

	MoveAI(enemyMen.back(), Pos);

	AddChild(enemyMen.back());
}

void Game::MoveAI(Man* m, int Pos)
{
	float timeTaken = Pos / m->getSpeed();
	m_Tweener.Tween(timeTaken,
		FLOAT, &m->m_Y, (float)Pos,
		DELAY, 1.0f,
		END);

	m->SetAtlas(g_pResources->getSoldierWalking(m->getType()));

	m->setEndPosition((int)Pos);

	if (Pos > greatestDistanceEnemy)
	{
		greatestDistanceEnemy = Pos;
	}
}

void Game::Render()
{
	Scene::Render();
}

// Initialise the games user interface
void Game::initUI()
{
	float limit = IwGxGetDeviceHeight() / 2;
	float width = ceil(IwGxGetDeviceWidth() / 6);

	CSprite* grass = new CSprite();
	grass->m_X = (float)width;
	grass->m_Y = limit;
	grass->SetImage(g_pResources->getGrassImage());
	grass->m_W = grass->GetImage()->GetWidth();
	grass->m_H = grass->GetImage()->GetHeight();
	grass->m_AnchorX = 0.5;
	grass->m_AnchorY = 0.5;
	// Fit backgroundTwo to Device size
	width *= 2;
	grass->m_ScaleX = (float)(width) / grass->GetImage()->GetWidth();
	grass->m_ScaleY = (float)IwGxGetDeviceHeight() / grass->GetImage()->GetHeight();
	AddChild(grass);

	CSprite* background = new CSprite();
	background->m_X = (float)width * 2;
	background->m_Y = (float)limit;
	background->SetImage(g_pResources->getGameBG());
	background->m_W = background->GetImage()->GetWidth();
	background->m_H = background->GetImage()->GetHeight();
	background->m_AnchorX = 0.5;
	background->m_AnchorY = 0.5;
	// Fit background to Device size
	background->m_ScaleX = (float)(IwGxGetDeviceWidth() - width) / background->GetImage()->GetWidth();
	background->m_ScaleY = (float)IwGxGetDeviceHeight() / background->GetImage()->GetHeight();
	AddChild(background);



	CSprite* Mountains = new CSprite();
	Mountains->m_X = (float)(IwGxGetDeviceWidth() / 12) + (grass->m_X * 2);
	Mountains->m_Y = limit;
	Mountains->SetImage(g_pResources->getBackGroundImage());
	Mountains->m_W = Mountains->GetImage()->GetWidth();
	Mountains->m_H = Mountains->GetImage()->GetHeight();
	Mountains->m_AnchorX = 0.5;
	Mountains->m_AnchorY = 0.5;
	// Fit backgroundTwo to Device size
	Mountains->m_ScaleX = (float)(IwGxGetDeviceWidth() / 6) / Mountains->GetImage()->GetWidth();
	Mountains->m_ScaleY = (float)IwGxGetDeviceHeight() / Mountains->GetImage()->GetHeight();
	AddChild(Mountains);



	// Create pause menu sprite (docked to top of screen)
	optionsSprite = new CSprite();
	optionsSprite->SetImage(g_pResources->getPauseIcon());
	optionsSprite->m_X = (int)IwGxGetDeviceWidth() * 0.9;
	optionsSprite->m_Y = (int)IwGxGetDeviceHeight() * 0.9;
	optionsSprite->m_W = optionsSprite->GetImage()->GetWidth();
	optionsSprite->m_H = optionsSprite->GetImage()->GetHeight();
	optionsSprite->m_AnchorX = 0.5;
	optionsSprite->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.13) / optionsSprite->GetImage()->GetWidth();
	optionsSprite->m_ScaleY = optionsSprite->m_ScaleX;
	AddChild(optionsSprite);


	// Create pause menu sprite (docked to top of screen)
	ChoicePanal = new CSprite();
	ChoicePanal->SetImage(g_pResources->getPlacardImage());
	ChoicePanal->m_X = (int)IwGxGetDeviceWidth() * 0.9;
	ChoicePanal->m_Y = (int)IwGxGetDeviceHeight() * 0.1;
	ChoicePanal->m_W = ChoicePanal->GetImage()->GetWidth();
	ChoicePanal->m_H = ChoicePanal->GetImage()->GetHeight();
	ChoicePanal->m_AnchorX = 0.5;
	ChoicePanal->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.13) / ChoicePanal->GetImage()->GetWidth();

	float temp = IwGxGetDeviceHeight() / 1.5;
	temp -= (int)temp % (NUM_ARMIES);


	ChoicePanal->m_ScaleY = (float)(temp) / ChoicePanal->GetImage()->GetHeight();
	AddChild(ChoicePanal);


	int divide = (int)(temp / (NUM_ARMIES));

	batallions = new CSprite*[NUM_ARMIES];

	int startPos = ChoicePanal->m_X;
	startPos -= (temp / 2) + (divide * 1.5);

	float fontScale = (float)IwGxGetScreenWidth() / FONT_DESIGN_WIDTH;
	float actualFontHeight = FONT_HEIGHT * fontScale;

	int j;
	for (j = 0; j < NUM_ARMIES; j++)
	{
		MakeBatallion(j, startPos, divide, actualFontHeight, fontScale);
		startPos += divide;
	}



	label = new CLabel();
	label->m_X = optionsSprite->m_X + (IwGxGetDeviceWidth() * 0.1);
	label->m_Y = optionsSprite->m_Y * 0.85;
	label->m_W = FONT_DESIGN_WIDTH;
	label->m_H = actualFontHeight;
	label->m_Text = "Coins: 100";
	label->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	label->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	label->m_Font = g_pResources->getFont();
	label->m_ScaleX = fontScale;
	label->m_ScaleY = fontScale;
	label->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	label->m_Angle = 270;
	AddChild(label);

}

void Game::MakeBatallion(int i, int PosX, int divide, float actualFontHeight, float fontScale)
{
	batallions[i] = new CSprite();
	batallions[i]->SetImage(g_pResources->getSoldiersStanding(i / 2));
	batallions[i]->m_X = (int)IwGxGetDeviceWidth() * 0.9;
	batallions[i]->m_Y = (int)PosX;
	batallions[i]->m_W = batallions[i]->GetImage()->GetWidth();
	batallions[i]->m_H = batallions[i]->GetImage()->GetHeight();
	batallions[i]->m_AnchorX = 0.5;
	batallions[i]->m_ScaleX = (float)(IwGxGetDeviceWidth() * 0.1) / batallions[i]->GetImage()->GetWidth();
	batallions[i]->m_ScaleY = (divide * 0.9) / batallions[i]->GetImage()->GetHeight();
	AddChild(batallions[i]);


	char str[16];
	snprintf(str, 16, "%d", ((i + 1) * 10));

	CLabel* batallionslabel = new CLabel();
	batallionslabel->m_X = batallions[i]->m_X;
	batallionslabel->m_Y = batallions[i]->m_Y + (IwGxGetDeviceWidth() * 0.1);
	batallionslabel->m_W = FONT_DESIGN_WIDTH;
	batallionslabel->m_H = actualFontHeight;
	batallionslabel->m_Text = str;
	batallionslabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	batallionslabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	batallionslabel->m_Font = g_pResources->getFont();
	batallionslabel->m_ScaleX = fontScale;
	batallionslabel->m_ScaleY = fontScale;
	batallionslabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	batallionslabel->m_Angle = 270;

	AddChild(batallionslabel);

	CLabel* LebelLabel = new CLabel();
	LebelLabel->m_X = batallions[i]->m_X + (IwGxGetDeviceWidth() * 0.05);
	LebelLabel->m_Y = batallionslabel->m_Y;
	LebelLabel->m_W = FONT_DESIGN_WIDTH;
	LebelLabel->m_H = actualFontHeight;
	if (i % 2 == 0)
	{
		LebelLabel->m_Text = "LV: 1";
	}
	else
	{
		LebelLabel->m_Text = "LV: 2";
	}
	LebelLabel->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
	LebelLabel->m_AlignVer = IW_2D_FONT_ALIGN_TOP;
	LebelLabel->m_Font = g_pResources->getFont();
	LebelLabel->m_ScaleX = fontScale * .66;
	LebelLabel->m_ScaleY = LebelLabel->m_ScaleX;
	LebelLabel->m_Color = CColor(0x00, 0x00, 0x00, 0xff);
	LebelLabel->m_Angle = 270;

	AddChild(LebelLabel);
}

void Game::Init()
{
	initUI();
	NewGame();
}

void Game::OutputLine(int i)
{
	char str[16];
	snprintf(str, 16, "%d", i);
	s3eDebugOutputString(str);
}

void Game::NewGame()
{
	touch = -1;
	dragging = -1;
	limitArmy = 0;
	enemyLimit = 0;
	enemyIndexCheck = 0;
	armyIndexChecker = 0;
	gameOver = false;

	Castle = new Destroyable();
	Castle->m_X = (float)(IwGxGetDeviceWidth() / 2.5);
	Castle->m_Y = (float)(IwGxGetDeviceHeight() / 10);
	Castle->SetImage(g_pResources->getCastleImage());
	Castle->m_W = Castle->GetImage()->GetWidth();
	Castle->m_H = Castle->GetImage()->GetHeight();
	Castle->m_AnchorX = 0.5;
	Castle->m_AnchorY = 0.5;
	// Fit backgroundTwo to Device size
	Castle->m_ScaleX = (float)(IwGxGetDeviceWidth() / 1.5) / Castle->GetImage()->GetWidth();
	Castle->m_ScaleY = (float)(IwGxGetDeviceHeight() / 5) / Castle->GetImage()->GetHeight();
	Castle->init(1000);
	Castle->setDivisions(3);
	AddChild(Castle);

	greatestDistance = Castle->m_Y;

	coins = 100;
	checker = 0;
	greatestDistanceEnemy = IwGxGetDeviceHeight() - (IwGxGetDeviceHeight() / 5);
	tempPos = NULL;
}