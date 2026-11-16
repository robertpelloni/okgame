#include "stdafx.h"
#include "RPGEditorControl.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/ListBox.h"
#include "Gwen/Controls/TextBox.h"

namespace OKGame {

RPGEditorControl::RPGEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName)
    : Gwen::Controls::Base(pParent, pName) {

    SetBounds(0, 0, 800, 600);

    tabs = new Gwen::Controls::TabControl(this);
    tabs->Dock(Gwen::Pos::Fill);

    // Actors Page
    Gwen::Controls::Base* actorPage = tabs->AddPage("Actors")->GetPage();
    actorList = new Gwen::Controls::ListBox(actorPage);
    actorList->SetBounds(10, 10, 200, 500);
    actorList->onRowSelected.Add(this, &RPGEditorControl::onActorSelected);

    new Gwen::Controls::Label(actorPage);
    actorNameEdit = new Gwen::Controls::TextBox(actorPage);
    actorNameEdit->SetBounds(220, 10, 200, 25);

    actorDescriptionEdit = new Gwen::Controls::TextBox(actorPage);
    actorDescriptionEdit->SetBounds(220, 45, 200, 100);

    // Items Page
    Gwen::Controls::Base* itemPage = tabs->AddPage("Items")->GetPage();
    itemList = new Gwen::Controls::ListBox(itemPage);
    itemList->SetBounds(10, 10, 200, 500);
    itemList->onRowSelected.Add(this, &RPGEditorControl::onItemSelected);

    itemNameEdit = new Gwen::Controls::TextBox(itemPage);
    itemNameEdit->SetBounds(220, 10, 200, 25);

    itemDescriptionEdit = new Gwen::Controls::TextBox(itemPage);
    itemDescriptionEdit->SetBounds(220, 45, 200, 100);
}

void RPGEditorControl::setDatabase(std::shared_ptr<RPGDatabase> db) {
    database = db;
    refreshActorList();
    refreshItemList();
}

void RPGEditorControl::refreshActorList() {
    actorList->Clear();
    if (!database) return;
    for (int i = 0; i < database->actors.size(); i++) {
        auto actor = database->actors.get(i);
        actorList->AddItem(Gwen::Utility::StringToUnicode(actor->name));
    }
}

void RPGEditorControl::refreshItemList() {
    itemList->Clear();
    if (!database) return;
    for (int i = 0; i < database->items.size(); i++) {
        auto item = database->items.get(i);
        itemList->AddItem(Gwen::Utility::StringToUnicode(item->name));
    }
}

void RPGEditorControl::onActorSelected(Gwen::Controls::Base* control) {
    Gwen::Controls::ListBox* list = (Gwen::Controls::ListBox*)control;
    int index = list->GetSelectedRowIndex();
    if (index >= 0 && index < database->actors.size()) {
        auto actor = database->actors.get(index);
        actorNameEdit->SetText(Gwen::Utility::StringToUnicode(actor->name));
        actorDescriptionEdit->SetText(Gwen::Utility::StringToUnicode(actor->description));
    }
}

void RPGEditorControl::onItemSelected(Gwen::Controls::Base* control) {
    Gwen::Controls::ListBox* list = (Gwen::Controls::ListBox*)control;
    int index = list->GetSelectedRowIndex();
    if (index >= 0 && index < database->items.size()) {
        auto item = database->items.get(index);
        itemNameEdit->SetText(Gwen::Utility::StringToUnicode(item->name));
        itemDescriptionEdit->SetText(Gwen::Utility::StringToUnicode(item->description));
    }
}

}
