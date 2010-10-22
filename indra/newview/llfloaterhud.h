/** 
 * @file llfloaterhud.h
 * @brief A floater showing the Kirstens Live Help
 *
 * 
 *
 * Copyright (C) 2010, Kirstenlee Cinquetti
 * 
 * Based on the redundant tutorial HUD and redone to support the KL viewer Live Help system
 */

#ifndef LL_LLFLOATERHUD_H
#define LL_LLFLOATERHUD_H

#include "llfloater.h"

class LLMediaCtrl;

class LLFloaterHUD : public LLFloater
{
	friend class LLFloaterReg;
public:

	BOOL postBuild();
	
private:
	// Handles its own construction and destruction, so private.
	LLFloaterHUD(const LLSD& key);
	/*virtual*/ ~LLFloaterHUD();

private:
	LLMediaCtrl* mWebBrowser; ///< the actual web browser control
};

#endif // LL_LLFLOATERHUD_H
