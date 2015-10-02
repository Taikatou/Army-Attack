#if !defined(__DESTROYABLE_H)
#define __DESTROYABLE_H

#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Destroyable : public CSprite
{
protected:
	int         Life;
	int			divisions;
public:
	int         getLife() { return Life; }
	void		setLife(int l) { Life = l; }
	void		subtractFromLife(int a) { Life -= a; }


	int			getDivisions() { return divisions; }
	void		setDivisions(int a) { divisions = a; }
public:
	Destroyable()  {}
	~Destroyable();

	void init(int life);

};

#endif  // __GEM_H
