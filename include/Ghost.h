#ifndef GHOST_H_
#define GHOST_H_

#include "Character.h"

class Ghost : public Character
{

	public:
		std::vector<int> CalculatePath(GraphVertex *origin, GraphVertex *destiny);

};

#endif /* GHOST_H_ */
