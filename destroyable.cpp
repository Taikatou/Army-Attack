#include "man.h"
#include "game.h"
#include "explosion.h"
#include "resources.h"
#include "main.h"


Destroyable::~Destroyable()
{
}


void Destroyable::init(int life)
{
	Life = life;
}