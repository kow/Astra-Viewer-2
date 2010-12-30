/** 
 * @file llfloatersidebarctrl.cpp
 * @brief Container for sidepanel buttons
 *
 * 
 * Copyright (c) 2008-2010, Kirstenlee Cinquetti (Lee Quick).
 * 
 */

#include "llviewerprecompiledheaders.h"

#include "llfloatersidebarctrl.h"

// Library includes
#include "llfloaterreg.h"

// Viewer includes

#include "llviewercontrol.h"
#include "llbottomtray.h"
#include "llsidetray.h"
#include "llsidetraypanelcontainer.h"
#include "lltoolmgr.h"
#include "lltoolfocus.h"

// Constants here if any...


class LLPanelSidebarctrlControls
:	public LLPanel
{
	friend class LLSideTray;
    friend class LLSideTrayTab;

	LOG_CLASS(LLPanelSidebarctrlControls);
public:
	LLPanelSidebarctrlControls();

	/* virtual */ BOOL	postBuild();
	/* virtual */ void	draw();

public:
	void	onHomeHeldDown();
    void    onProfileHeldDown();
	void	onPeopleHeldDown();
	void	onPlacesHeldDown();
	void    onInventoryHeldDown();
	void    onAppearanceHeldDown();
	void    onCloseHeldDown();

private:
	LLButton*	mHomeBtn;
	LLButton*   mProfileBtn;
	LLButton*   mPeopleBtn;
	LLButton*   mPlacesBtn;
	LLButton*	mInventoryBtn;
	LLButton*	mAppearanceBtn;
	LLButton*	mCloseSidebarBtn;

};
static LLRegisterPanelClassWrapper<LLPanelSidebarctrlControls> t_sidebar_controls_panel("sidebar_controls_panel");

//-------------------------------------------------------------------------------
// LLPanelSidebarctrlControls
//-------------------------------------------------------------------------------

LLPanelSidebarctrlControls::LLPanelSidebarctrlControls()
:	mProfileBtn(NULL),
    mPeopleBtn(NULL),
	mPlacesBtn(NULL),
	mInventoryBtn(NULL),
	mAppearanceBtn(NULL),
	mCloseSidebarBtn(NULL),
    mHomeBtn( NULL )
{
    mCommitCallbackRegistrar.add("sidebar_profile_btn", boost::bind(&LLPanelSidebarctrlControls::onProfileHeldDown, this));
    mCommitCallbackRegistrar.add("sidebar_people_btn", boost::bind(&LLPanelSidebarctrlControls::onPeopleHeldDown, this));
	mCommitCallbackRegistrar.add("sidebar_places_btn", boost::bind(&LLPanelSidebarctrlControls::onPlacesHeldDown, this));
	mCommitCallbackRegistrar.add("sidebar_inventory_btn", boost::bind(&LLPanelSidebarctrlControls::onInventoryHeldDown, this));
	mCommitCallbackRegistrar.add("sidebar_appearance_btn", boost::bind(&LLPanelSidebarctrlControls::onAppearanceHeldDown, this));
    mCommitCallbackRegistrar.add("sidebar_close_btn", boost::bind(&LLPanelSidebarctrlControls::onCloseHeldDown, this));
	mCommitCallbackRegistrar.add("sidebar_home_btn", boost::bind(&LLPanelSidebarctrlControls::onHomeHeldDown, this));
}
BOOL LLPanelSidebarctrlControls::postBuild()
{
	return LLPanel::postBuild();
}
void LLPanelSidebarctrlControls::draw()
{
	LLPanel::draw();
}

void LLPanelSidebarctrlControls::onHomeHeldDown()
{ 

	if (!LLSideTray::getInstance()->isPanelActive("panel_home"))
    {
	LLSideTray::getInstance()->collapseSideBar();
	LLSideTray::getInstance()->showPanel("panel_home",LLSD());
    }
    else
    {
	  LLSideTray::getInstance()->collapseSideBar();
    }
	
}

void LLPanelSidebarctrlControls::onProfileHeldDown()  // KL both profile and people sit in panel_container.currently there is no way to interrogate a sub_panel..
{
	
   if(!LLSideTray::getInstance()->isPanelActive("panel_container_me")) // So we use specifically xml named panel containers to determine the state.
   {
	LLSideTray::getInstance()->collapseSideBar();
    LLSideTray::getInstance()->showPanel("panel_me",LLSD());
	
   }
   else
   {
    LLSideTray::getInstance()->collapseSideBar();
	 
   }
 	
}

void LLPanelSidebarctrlControls::onPeopleHeldDown()  
{ 
   
   if(!LLSideTray::getInstance()->isPanelActive("panel_container_people"))
   {
	LLSideTray::getInstance()->collapseSideBar();
    LLSideTray::getInstance()->showPanel("panel_people",LLSD());
   }
   else
   {
    LLSideTray::getInstance()->collapseSideBar();
   } 
   
	
}

void LLPanelSidebarctrlControls::onPlacesHeldDown()
{ 

	if (!LLSideTray::getInstance()->isPanelActive("panel_places"))
    {
	LLSideTray::getInstance()->collapseSideBar();
	LLSideTray::getInstance()->showPanel("panel_places",LLSD());
    }
    else
    {
	  LLSideTray::getInstance()->collapseSideBar();
    }
	
}

void LLPanelSidebarctrlControls::onInventoryHeldDown()
{ 

	if (!LLSideTray::getInstance()->isPanelActive("sidepanel_inventory"))
    {
	LLSideTray::getInstance()->collapseSideBar();
	LLSideTray::getInstance()->showPanel("sidepanel_inventory",LLSD());
    }
    else
    {
	  LLSideTray::getInstance()->collapseSideBar();
    }
	
}

void LLPanelSidebarctrlControls::onAppearanceHeldDown()
{ 

	if (!LLSideTray::getInstance()->isPanelActive("sidepanel_appearance"))
    {
	LLSideTray::getInstance()->collapseSideBar();
	LLSideTray::getInstance()->showPanel("sidepanel_appearance",LLSD());
    }
    else
    {
	  LLSideTray::getInstance()->collapseSideBar();
    }
	
}

void LLPanelSidebarctrlControls::onCloseHeldDown()
{ 

	if (!LLSideTray::getInstance()->getCollapsed())
    {
	LLSideTray::getInstance()->collapseSideBar();
	}
    else
    {
	LLSideTray::getInstance()->collapseSideBar(); // Just Close the fecker already ! ^^
    }
	
}
//
// Member functions
//




void LLFloaterSidebarctrl::update()
{
	
}



LLFloaterSidebarctrl* LLFloaterSidebarctrl::findInstance()
{
	return LLFloaterReg::findTypedInstance<LLFloaterSidebarctrl>("sidebarctrl");
}

void LLFloaterSidebarctrl::onOpen(const LLSD& key)
{
	LLButton *anchor_panel = LLBottomTray::getInstance()->getChild<LLButton>("sidebar_btn");

	setDockControl(new LLDockControl(
		anchor_panel, this,
		getDockTongue(), LLDockControl::TOP));

	
	mClosed = FALSE;
}

void LLFloaterSidebarctrl::onClose(bool app_quitting)
{
	//We done :) if app is quitting
	if(app_quitting)
		return;
	
	if ( !isDocked() )
		setDocked(true);
	mClosed = TRUE;
}

LLFloaterSidebarctrl::LLFloaterSidebarctrl(const LLSD& val)
:	LLTransientDockableFloater(NULL, true, val),
	mClosed(FALSE)
{
}

// virtual
BOOL LLFloaterSidebarctrl::postBuild()
{
	setIsChrome(TRUE);
	setTitleVisible(TRUE); 

	mControls = findChild<LLPanelSidebarctrlControls>("sidebar_controls_panel");
	
	update();

	return LLDockableFloater::postBuild();
}


