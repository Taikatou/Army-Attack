#include "man.h"
#include "game.h"
#include "explosion.h"
#include "resources.h"
#include "main.h"
#include "destroyable.h"

Man::~Man()
{
}


void Man::init(int life)
{
	Destroyable::init(life);
	shooting = false;
}