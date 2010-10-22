/** 
 * @file llfloaterhud.cpp
 * @brief Implementation of HUD floater
 *
 * 
 * Copyright (C) 2010, KirstenLee Cinquetti.
 * 
 * Converted  Redundant Floater Tutorial For live Help web app
 */

#include "llviewerprecompiledheaders.h"

#include "llfloaterhud.h"

// Viewer libs
#include "llviewercontrol.h"
#include "llmediactrl.h"

// Linden libs
#include "llnotificationsutil.h"
#include "lluictrlfactory.h"


///----------------------------------------------------------------------------
/// Class LLFloaterHUD
///----------------------------------------------------------------------------
#define super LLFloater	/* superclass */

// Default constructor
LLFloaterHUD::LLFloaterHUD(const LLSD& key)
:	LLFloater(key),
	mWebBrowser(0)
{
	// do not build the floater if there the url is empty
	if (gSavedSettings.getString("KirstensLiveURL") == "")
	{
			return;
	}
	
	setTitleVisible(true);
	
	// Opaque background since we never get the focus
	setBackgroundOpaque(TRUE);
}

BOOL LLFloaterHUD::postBuild()
{
	mWebBrowser = getChild<LLMediaCtrl>("floater_hud_browser" );
	if (mWebBrowser)
	{
		
		std::string base_url = gSavedSettings.getString("KirstensLiveURL"); // from saved settings points to the support URL
		
		std::string url = base_url;
		mWebBrowser->navigateTo(url);
	}
	
	return TRUE;
}

// Destructor
LLFloaterHUD::~LLFloaterHUD()
{
}
