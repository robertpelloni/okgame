#pragma once

#include "bobtypes.h"
#include "GameType.h"
#include "Piece.h"

#include <Gwen/Controls/Base.h>
#include <Gwen/Controls/Button.h>
#include <Gwen/Controls/Label.h>
#include <Gwen/Controls/TabControl.h>

#include <map>
#include <memory>
#include <utility>

class BobsGame;

class CustomGameEditorControl : public Gwen::Controls::Base
{
public:
	static const char* GetIdentifier()
	{
		static const char* ident = "Base:CustomGameEditorControl";
		return ident;
	}

	Gwen::Controls::Base* DynamicCast(const char* variable)
	{
		if (GetIdentifier() == variable) return this;
		return Gwen::Controls::Base::DynamicCast(variable);
	}

	const char* GetTypeName() { return "CustomGameEditorControl"; }
	const char* GetBaseTypeName() { return Gwen::Controls::Base::GetTypeName(); }

	CustomGameEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName = "", BobsGame* b = nullptr);

	void initPreviewGame();
	virtual void Render(Gwen::Skin::Base* skin) override;
	void saveAllToCurrentGameType();

	void onAddPieceButton(Gwen::Controls::Base* control);
	void onDuplicatePieceButton(Gwen::Controls::Base* control);
	void onRemovePieceButton(Gwen::Controls::Base* control);
	void onAddRotationButton(Gwen::Controls::Base* control);
	void onDuplicateRotationButton(Gwen::Controls::Base* control);
	void onRemoveRotationButton(Gwen::Controls::Base* control);
	void onPrevPieceButton(Gwen::Controls::Base* control);
	void onNextPieceButton(Gwen::Controls::Base* control);
	void onPrevRotationButton(Gwen::Controls::Base* control);
	void onNextRotationButton(Gwen::Controls::Base* control);
	void onClearRotationButton(Gwen::Controls::Base* control);
	void onCellButton(Gwen::Controls::Base* control);

private:
	BobsGame* bobsGame = nullptr;
	sp<GameType> currentGameType = nullptr;

	Gwen::Controls::Label* settingsLabel = nullptr;
	Gwen::Controls::Label* pieceLabel = nullptr;
	Gwen::Controls::Label* rotationLabel = nullptr;
	Gwen::Controls::Label* summaryLabel = nullptr;

	Gwen::Controls::Button* addPieceBtn = nullptr;
	Gwen::Controls::Button* duplicatePieceBtn = nullptr;
	Gwen::Controls::Button* removePieceBtn = nullptr;
	Gwen::Controls::Button* addRotationBtn = nullptr;
	Gwen::Controls::Button* duplicateRotationBtn = nullptr;
	Gwen::Controls::Button* removeRotationBtn = nullptr;
	Gwen::Controls::Button* prevPieceBtn = nullptr;
	Gwen::Controls::Button* nextPieceBtn = nullptr;
	Gwen::Controls::Button* prevRotationBtn = nullptr;
	Gwen::Controls::Button* nextRotationBtn = nullptr;
	Gwen::Controls::Button* clearRotationBtn = nullptr;

	Gwen::Controls::Button* cellButtons[4][4] = {};
	std::map<Gwen::Controls::Base*, std::pair<int, int>> cellLookup;

	int selectedPieceIndex = -1;
	int selectedRotationIndex = 0;

	void addPiece();
	void duplicatePiece();
	void removePiece();
	void addRotation();
	void duplicateRotation();
	void removeRotation();
	void cyclePiece(int delta);
	void cycleRotation(int delta);
	void clearRotation();
	void toggleCell(int x, int y);
	void refreshEditorState();

	shared_ptr<PieceType> getSelectedPieceType();
	Rotation* getSelectedRotation();
	int getCurrentRotationBlockCount();
	int getTotalRotationCount();
};
