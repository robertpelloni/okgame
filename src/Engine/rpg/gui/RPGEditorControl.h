#pragma once

#include "bobtypes.h"
#include "src/Engine/shared/database/RPGDatabase.h"
#include <Gwen/Controls/Base.h>
#include <Gwen/Controls/Button.h>
#include <Gwen/Controls/Label.h>
#include <Gwen/Controls/TabControl.h>
#include <Gwen/Controls/ListBox.h>
#include <Gwen/Controls/TextBox.h>

namespace OKGame {

class RPGEditorControl : public Gwen::Controls::Base {
public:
    GWEN_CONTROL(RPGEditorControl, Gwen::Controls::Base);

    RPGEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName = "");

    void setDatabase(std::shared_ptr<RPGDatabase> db);

private:
    std::shared_ptr<RPGDatabase> database;

    Gwen::Controls::TabControl* tabs;

    // Actors Tab
    Gwen::Controls::ListBox* actorList;
    Gwen::Controls::TextBox* actorNameEdit;
    Gwen::Controls::TextBox* actorDescriptionEdit;

    // Items Tab
    Gwen::Controls::ListBox* itemList;
    Gwen::Controls::TextBox* itemNameEdit;
    Gwen::Controls::TextBox* itemDescriptionEdit;

    void onActorSelected(Gwen::Controls::Base* control);
    void onItemSelected(Gwen::Controls::Base* control);

    void refreshActorList();
    void refreshItemList();
};

}
