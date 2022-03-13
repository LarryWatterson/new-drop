// add include 

#ifdef NEW_DROP_MANAGER
#include "NewDropManager.h"
#endif

// find in void CHARACTER::Dead(LPCHARACTER pkKiller, bool bImmediateDead)

			CGuildManager::instance().Kill(pkKiller, this);
		}

// add

#ifdef NEW_DROP_MANAGER
	CNewDropManager::instance().NewDropKillAction(pkKiller, GetRaceNum());
#endif