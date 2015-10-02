#if !defined(__MAN_H)
#define __MAN_H

#include "Iw2DSceneGraph.h"
#include "destroyable.h"
#include "IwTween.h"

using namespace IwTween;
using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;


class Man : public Destroyable
{
protected:
	int			Width;
	int			endPosition;
	int			speed;
	int			bullet;
	int			type;

	bool		flying;
	bool		shooting;

public:
	int         getWidth() { return Width; }
	void		setWidth(int a) { Width = a; }

	int         getType() { return type; }
	void		setType(int a) { type = a; }

	bool        getFlying() { return flying; }
	void		setFlying(bool a) { flying = a; }

	void		setBulletIndex(int b) { bullet = b; }
	int			getBulletIndex() { return bullet;  }

	bool		getShooting() { return shooting; }
	void		setShooting(bool a) { shooting = a; }

	int			getSpeed() { return speed; }
	void		setSpeed(int a) { speed = a; }

	int			getEndPosition() { return endPosition; }
	void		setEndPosition(int a) { endPosition = a; }
public:
	Man()  {}
	~Man();

	void init(int life);

};

#endif  // __GEM_H
