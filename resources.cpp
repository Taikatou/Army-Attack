#include "resources.h"
#include "Iw2D.h"


Resources::Resources()
{
	GameBG			=		Iw2DCreateImage("textures/bg0.png");
	PlayButton		=		Iw2DCreateImage("textures/play.png");
	// Load fonts

	soldier1		=		Iw2DCreateImage("textures/soldier1.png");
	soldier4		=		Iw2DCreateImage("textures/soldiershield.png");
	soldier5		=		Iw2DCreateImage("textures/aircraft.png");


	soldier5_plane_enemy =	Iw2DCreateImage("textures/aircraft_enemy.png");

	Font			=		Iw2DCreateFont("fonts/arial8.gxfont");
	NewGame			=		Iw2DCreateImage("textures/new_game.png");
	MenuBG			=		Iw2DCreateImage("textures/menu_bkg.jpg");
	MenuButton		=		Iw2DCreateImage("textures/button_bg.png");
	PauseIcon		=		Iw2DCreateImage("textures/pause_icon.png");
	grassImage		=		Iw2DCreateImage("textures/grass.png");
	Castle			=		Iw2DCreateImage("textures/castle.png");
	Castle1			=		Iw2DCreateImage("textures/castle01.png");
	Castle2			=		Iw2DCreateImage("textures/castle02.png");
	Castle3			=		Iw2DCreateImage("textures/castle03.png");
	PlacardImage	=		Iw2DCreateImage("textures/placard.png");
	backGroundImage =		Iw2DCreateImage("textures/mountains1.png");
	settingsButtonImage =	Iw2DCreateImage("textures/settings-button.png");
	soldierShooting =		Iw2DCreateImage("textures/soldier_shooting_anim.png");
	soldierShootingEnemy =	Iw2DCreateImage("textures/soldier_shooting_anim_enemy.png");
	bullet			=		Iw2DCreateImage("textures/bullet.png");
	soldierWalking =		Iw2DCreateImage("textures/soldier_walking.png");
	soldierWalkingEnemy =	Iw2DCreateImage("textures/soldier_walking_enemy.png");
	selector = Iw2DCreateImage("textures/selector.png");

	shieldWalking = Iw2DCreateImage("textures/soldiershield_animation.png");
	shieldWalkingEnemy = Iw2DCreateImage("textures/soldier_shooting_anim_enemy.png");

	shieldShooting = Iw2DCreateImage("textures/shield_shooting_anim.png");
	shieldShootingEnemy = Iw2DCreateImage("textures/shield_shooting_anim_enemy.png");

	int frame_w = (int)(soldierWalking->GetWidth() / 1);
	int frame_h = (int)(soldierWalking->GetHeight() / 6);

	soldierWalkingAnim =		new CAtlas(frame_w, frame_h, 6, soldierWalking);
	soldierWalkingAnimEnemy = new CAtlas(frame_w, frame_h, 6, soldierWalkingEnemy);

	frame_w = (int)(soldierShooting->GetWidth() / 1);
	frame_h = (int)(soldierShooting->GetHeight() / 3);


	soldierShootingAnim =	new CAtlas(frame_w, frame_h, 3, soldierShooting);
	soldierShootingAnimEnemy = new CAtlas(frame_w, frame_h, 3, soldierShootingEnemy);



	frame_w = (int)(shieldWalking->GetWidth() / 1);
	frame_h = (int)(shieldWalking->GetHeight() / 2);

	shieldWalkingAnim = new CAtlas(frame_w, frame_h, 2, shieldWalking);
	shieldWalkingAnimEnemy = new CAtlas(frame_w, frame_h, 2, shieldWalkingEnemy);


	frame_w = (int)(shieldShooting->GetWidth() / 1);
	frame_h = (int)(shieldShooting->GetHeight() / 3);

	shieldShootingAnim = new CAtlas(frame_w, frame_h, 3, shieldShooting);
	shieldShootingAnimEnemy = new CAtlas(frame_w, frame_h, 3, shieldShootingEnemy);



	frame_w = (int)(soldier5->GetWidth() / 1);
	frame_h = (int)(soldier5->GetHeight() / 1);

	plane = new CAtlas(frame_w, frame_h, 1, soldier5);
	plane_enemy = new CAtlas(frame_w, frame_h, 1, soldier5_plane_enemy);


}

Resources::~Resources()
{

	delete MenuBG;
	delete GameBG;
	delete MenuButton;
	delete PauseIcon;
	delete PlayButton;
	delete Font;
	delete selector;
	delete NewGame;
	delete grassImage;
	delete Castle;
	delete PlacardImage;
	delete backGroundImage;
	delete settingsButtonImage;
	delete Castle1;
	delete Castle2;
	delete Castle3;
	delete soldierShooting;
	delete soldierShootingEnemy;
	delete bullet;

	delete soldierWalking;
	delete soldierWalkingEnemy;

	delete soldierWalkingAnim;
	delete soldierWalkingAnimEnemy;

	delete soldierShootingAnim;
	delete soldierShootingAnimEnemy;

	delete shieldShootingAnim;
	delete shieldShootingAnimEnemy;

	delete soldier1;
	delete soldier4;
	delete soldier5;
	delete soldier5_plane_enemy;


	delete shieldWalking;
	delete shieldWalkingEnemy;

	delete shieldShooting;
	delete shieldShootingEnemy;


	delete plane;
	delete plane_enemy;

}

// Global resources
Resources* g_pResources = 0;



