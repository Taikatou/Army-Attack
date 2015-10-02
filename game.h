#if !defined(__GAME_H__)
#define __GAME_H__

#include "scene.h"
#include "man.h"
#include "destroyable.h"


// Constants that are used to fit the game to different screen sizes
#define FONT_HEIGHT             15
#define FONT_DESIGN_WIDTH       320
#define GRAPHIC_DESIGN_WIDTH    768

typedef std::vector<CSprite*> csprite_vec;
typedef std::vector<Man*> man_vec;

typedef std::vector<CSprite*> sprite_vec;
/**
 * @enum  eGameState
 *
 * @brief List of game states.
 */
class Game : public Scene
{
protected:

	bool gameOver;
	CLabel*				label;
	CSprite*			optionsSprite;
	CSprite*			ChoicePanal;
	CSprite*			endGame;
	CSprite*			tempPos;
	
	CSprite**			batallions;

	Destroyable*		Castle;


	int					limitArmy;
	int					enemyLimit;
	int					enemyNumber;
	int					touch;

	int					dragging;
	int					greatestDistance;
	int					enemyIndexCheck;
	int					armyIndexChecker;

	int					greatestDistanceEnemy;
	int					coins;
	int					checker;

	man_vec				arrayMen;
	man_vec				enemyMen;

	sprite_vec			bullets;

	float				PreviousX;
	float				PreviousY;

public:

private:
	void            initUI();
public:
    Game() {}
    ~Game();

    // initialise the game
    void            Init();

    // Update the game
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    // Render the game
    void            Render();
	void			MakeBatallion(int i, int PosX, int divide, float actualFontHeight, float floatscale);
	void			AddAI(int x, int y, int endPos, bool type);
	bool			CheckCollision(Destroyable* Men1, std::vector<Man*>& Men2);

	void			RemoveMan(int index, std::vector<Man*>& Men1);
	void			ShootBullet(Man*& Men, std::vector<Man*>& otherMen, int distance);
	void			CheckGreatestDistance();
	void			CheckInputEvents();
	void			NewGame();

	void			RemoveBullet(int index);
	void			MoveAI(Man* m, int endPos);

	void			OutputLine(int i);
	void			CheckDragging();
	void			WobbleSprite(CSprite*);
};


#endif  // __GAME_H__


