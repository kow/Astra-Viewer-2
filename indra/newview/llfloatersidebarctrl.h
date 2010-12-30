/** 
 * @file llfloatersidebarctrl.h
 * @brief Container for sidebar control buttons 
 *
 * 
 * Copyright (c) 2009-2010, Kirstenlee Cinquetti.
 * 
 */

#ifndef LLFLOATERSIDEBARCTRL_H
#define LLFLOATERSIDEBARCTRL_H

#include "lltransientdockablefloater.h"


class LLFloaterReg;

class LLPanelSidebarctrlControls;



class LLFloaterSidebarctrl
	:	public LLTransientDockableFloater
{
	friend class LLFloaterReg;
	

public:

	
	/* determines actual mode and updates ui */
	void update();
	
	virtual void onOpen(const LLSD& key);
	virtual void onClose(bool app_quitting);

	
	LLPanelSidebarctrlControls*	mControls;

private:

	LLFloaterSidebarctrl(const LLSD& val);
	~LLFloaterSidebarctrl() {};

	/* return instance if it exists - created by LLFloaterReg */
	static LLFloaterSidebarctrl* findInstance();

	/*virtual*/ BOOL postBuild();

	
	/* updates the state (UI) according to the current mode */
	void updateState();

	

	BOOL mClosed;
};

#endif
