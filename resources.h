#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
* @class Resources
*
* @brief Resources class
*
* The that manages the lifetime of the following types of resources:
* - Images
* - Fonts
* - Atlases
*/
class Resources
{
protected:

	CIw2DImage*     MenuBG;
	CIw2DImage*     GameBG;
	CIw2DImage*     Castle;
	CIw2DImage*     Castle1;
	CIw2DImage*     Castle2;
	CIw2DImage*     Castle3;
	CIw2DImage*		PlacardImage;
	CIw2DImage*     MenuButton;
	CIw2DImage*     PauseIcon;
	CIw2DImage*     PlayButton;
	CIw2DFont*      Font;
	CIw2DImage*		NewGame;
	CIw2DImage*		grassImage;
	CIw2DImage*		backGroundImage;
	CIw2DImage*		settingsButtonImage;
	CIw2DImage*		selector;


	CIw2DImage*		soldier1;
	CIw2DImage*		soldier4;
	CIw2DImage*		soldier5;

	CIw2DImage*		soldier5_plane_enemy;

	CIw2DImage*		soldierShooting;
	CIw2DImage*		soldierShootingEnemy;

	CIw2DImage*		soldierWalking;
	CIw2DImage*		soldierWalkingEnemy;

	CIw2DImage*		shieldWalking;
	CIw2DImage*		shieldWalkingEnemy;

	CIw2DImage*		shieldShooting;
	CIw2DImage*		shieldShootingEnemy;

	CIw2DImage*		bullet;

	CAtlas*			soldierWalkingAnim;
	CAtlas*			soldierWalkingAnimEnemy;

	CAtlas*			soldierShootingAnim;
	CAtlas*			soldierShootingAnimEnemy;


	CAtlas*			shieldWalkingAnim;
	CAtlas*			shieldWalkingAnimEnemy;

	CAtlas*			shieldShootingAnim;
	CAtlas*			shieldShootingAnimEnemy;

	CAtlas*			plane;
	CAtlas*			plane_enemy;

public:
	CIw2DImage*     getMenuBG()                 { return MenuBG; }
	CIw2DImage*     getGameBG()                 { return GameBG; }
	CIw2DImage*     getPlacardImage ()          { return PlacardImage; }
	CIw2DImage*     getMenuButton()             { return MenuButton; }
	CIw2DImage*     getPlayButton()             { return PlayButton; }
	CIw2DImage*     getPauseIcon()              { return PauseIcon; }
	CIw2DFont*      getFont()                   { return Font; }
	CIw2DImage*     getNewButton()				{ return NewGame; }
	CIw2DImage*     getGrassImage()             { return grassImage; }
	CIw2DImage*     getCastleImage()            { return Castle; }
	CIw2DImage*     getBackGroundImage()        { return backGroundImage; }
	CIw2DImage*     getSettingsButton()			{ return settingsButtonImage; }

	CIw2DImage*     getBullet()			{ return bullet; }
	CIw2DImage*     getSelector()			{ return selector; }


	CIw2DImage*     getSoldiersStanding(int i)	{
		switch (i){
		case 0: return soldier1;
				break;
		case 1: return soldier4;
			break;
		case 2: return soldier5;
			break;
		}
	}


	CIw2DImage*     getCastleDivisions(int i)	{
		switch (i){
		case 1: return Castle3;
			break;
		case 2: return Castle2;
			break;
		case 3: return Castle1;
			break;
		}
	}


	CAtlas*         getSoldierWalking(int i)         {
		switch (i){
		case 0: return soldierWalkingAnim;
			break;
		case 1: return soldierWalkingAnimEnemy;
			break;
		case 2: return shieldWalkingAnim;
			break;
		case 3: return shieldWalkingAnimEnemy;
			break;
		case 4: return plane;
			break;
		case 5: return plane_enemy;
			break;
		}
	}

	CAtlas*         getSoldierShooting(int i)         {
		switch (i){
		case 0: return soldierShootingAnim;
			break;
		case 1: return soldierShootingAnimEnemy;
			break;
		case 2: return shieldShootingAnim;
			break;
		case 3: return shieldShootingAnimEnemy;
			break;
		case 4: return plane;
			break;
		case 5: return plane_enemy;
			break;
		}
	}



public:
	Resources();
	~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


