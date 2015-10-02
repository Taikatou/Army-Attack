#if !defined(__LINE_H__)
#define __LINE_H__

#include "Iw2D.h"

class Line
{
private:
	CIwFVec2 line1;
	CIwFVec2 line2;

	bool active;

public:
	Line() { active = false; };

	void setFirstPoint(int x, int y) {
		line1 = CIwSVec2(x, y);
	}

	void setSecondPoint(int x, int y) {
		line2 = CIwSVec2(x, y);
	}

	CIwFVec2 getLine1() { return line1; }
	CIwFVec2 getLine2() { return line2; }

	void setActive(bool a) {
		active = a;
	}

	bool getActive(){ return active; }
};

extern Line* g_pLine;

#endif