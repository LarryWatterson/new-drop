// add include

#ifdef NEW_DROP_MANAGER
#include "NewDropManager.h"
#endif

// find

	DSManager dsManager;

// add under

#ifdef NEW_DROP_MANAGER
	CNewDropManager		newDropMng;
#endif

// find

	//if game server
	if (!g_bAuthServer)


// add in if

#ifdef NEW_DROP_MANAGER
		newDropMng.Initialize();
#endif