/* vim: set sw=4 ts=4 et: */
/*
 * This file is part of Meecast for Tizen2
 *
 * Copyright (C) 2013 Vlad Vasilyeu
 *     for the code
 *
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU  General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 * You should have received a copy of the GNU  General Public
 * License along with this software; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
*/


#ifndef _MEECAT_FULL_WEATHER_FORM_H_
#define _MEECAST_FULL_WEATHER_FORM_H_

#include <FBase.h>
#include <FMedia.h>
#include <FUi.h>
#include "configtizen.h"

#include <FSystem.h>
#include <FLocales.h>

#include <libintl.h>
#include <locale.h>
#define _(String) gettext(String)

#define SAFE_DELETE(x)  if (x) { delete x; x = null; }



class meecastFullWeatherForm
    : public Tizen::Ui::Controls::Form
    , public Tizen::Ui::IActionEventListener
    , public Tizen::Ui::Controls::IFormBackEventListener
    , public Tizen::Ui::Controls::IFormMenuEventListener
    , public Tizen::Ui::Scenes::ISceneEventListener
    , public Tizen::Ui::ITouchEventListener
    , public Tizen::Ui::Controls::ITableViewItemEventListener
    , public Tizen::Ui::Controls::ITableViewItemProvider
    , public Tizen::Ui::ITouchFlickGestureEventListener
     {
public:
    enum Current_Selected_Tab{
            NOW = 0,
            DAY = 1,
            NIGHT = 2,
            HOURLY = 3
    };


    meecastFullWeatherForm(void);
    virtual ~meecastFullWeatherForm(void);
    bool Initialize(void);
    void CreateContextMenuList(Tizen::Graphics::Point Corner_Point);
public:
    virtual result OnInitializing(void);
    virtual result OnTerminating(void);
    virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
    virtual void OnFormMenuRequested(Tizen::Ui::Controls::Form& source);
    virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
    virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
                                   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
    virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
                                    const Tizen::Ui::Scenes::SceneId& nextSceneId);
// from ITouchEventListener
    virtual void OnTouchPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo);
    virtual void OnTouchDoublePressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo){}
    virtual void OnTouchFocusIn(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo){}
    virtual void OnTouchFocusOut(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo){}
    virtual void OnTouchLongPressed(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo){}
    virtual void OnTouchMoved(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo){}
    virtual void OnTouchReleased(const Tizen::Ui::Control& source, const Tizen::Graphics::Point& currentPosition, const Tizen::Ui::TouchEventInfo& touchInfo){}
    void ReInitElements(void);

    Tizen::Graphics::Color* GetTemperatureColor(int t);
    /* Table */


    //ITableViewItemProvider
    virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int index, int itemWidth);
    virtual bool DeleteItem(int index, Tizen::Ui::Controls::TableViewItem* pItem);
    virtual int GetItemCount(void);
    virtual void UpdateItem(int index, Tizen::Ui::Controls::TableViewItem* pItem);
    virtual int GetDefaultItemHeight(void);
    // ITableViewItemEventListener
    virtual void OnTableViewItemStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
    virtual void OnTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::TableView& tableView, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated);
    virtual void OnTableViewItemReordered(Tizen::Ui::Controls::TableView& tableView, int itemIndexFrom, int itemIndexTo);

    //Gesture
    virtual void OnFlickGestureDetected(Tizen::Ui::TouchFlickGestureDetector& gestureDetector);
    virtual void OnFlickGestureCanceled(Tizen::Ui::TouchFlickGestureDetector& gestureDetector);


         
/*
	virtual void OnSectionTableViewItemStateChanged(Tizen::Ui::Controls::SectionTableView& tableView, int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status){}
	virtual void OnSectionTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::SectionTableView& tableView, int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated){}
	virtual int GetSectionCount(void);
	virtual int GetItemCount(int sectionIndex);
	virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int sectionIndex, int itemIndex, int itemWidth);
	virtual bool DeleteItem(int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual void UpdateItem(int sectionIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	virtual Tizen::Base::String GetSectionHeader(int sectionIndex);
	virtual bool HasSectionHeader(int sectionIndex);
	virtual Tizen::Base::String GetSectionFooter(int sectionIndex);
	virtual bool HasSectionFooter(int sectionIndex);
	virtual int GetDefaultItemHeight(void);
*/



protected:
    static const int ID_BUTTON_NOW = 1905;
    static const int ID_BUTTON_DAY = 1906;
    static const int ID_BUTTON_NIGHT = 1907;
    static const int ID_BUTTON_HOURLY = 1908;
    static const int ID_SET_LOCATIONS = 909;
    static const int ID_MENU_SETTINGS = 906;
    static const int ID_BUTTON_MENU = 905;
    static const int ID_MENU_ABOUT = 907;
    static const int DURATION = 500;
    static const int PROGRESS_COUNT = 30;
    static const int INDICATE_HEIGHT = 70;
private:
    ConfigTizen *_config;
    int _dayCount;
    int _dayNumber;
    Tizen::Ui::Controls::ContextMenu* __pContextMenuText;
    Tizen::Ui::Controls::FooterItem* __nowButton;
    Tizen::Ui::Controls::FooterItem* __dayButton;
    Tizen::Ui::Controls::FooterItem* __nightButton;
    Tizen::Ui::Controls::FooterItem* __hourlyButton;
    Tizen::Ui::Controls::TableView* __pTableView;
    int _current_selected_tab;
    int __clientWidth;
    int __clientHeight;
    Tizen::Base::Collection::ArrayList* _pKeyList;
    Tizen::Base::Collection::ArrayList* _pValueList;
    int _count_of_hours; 
    Tizen::Ui::TouchFlickGestureDetector* __pFlickGesture;
    bool __gestureDetected;
};

#endif	//_MEECAST_FULL_WEATHER_FORM_H_
