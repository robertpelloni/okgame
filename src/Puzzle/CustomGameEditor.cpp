#include "stdafx.h"
#include "CustomGameEditor.h"

#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/TabControl.h"

//=========================================================================================================================
CustomGameEditorControl::CustomGameEditorControl(Gwen::Controls::Base* pParent, const Gwen::String& pName, BobsGame* b) : Gwen::Controls::Base(pParent, pName)
{//=========================================================================================================================
	bobsGame = b;
	currentGameType = make_shared<GameType>();

	Gwen::Controls::TabControl* tabs = new Gwen::Controls::TabControl(this);
	tabs->SetBounds(10, 10, 860, 640);
	tabs->SetTabStripPosition(Gwen::Pos::Top);

	// Settings Page
	Gwen::Controls::Base* settingsPage = tabs->AddPage("Settings")->GetPage();
	settingsLabel = new Gwen::Controls::Label(settingsPage);
	settingsLabel->SetText("Custom puzzle rules now expose live piece/rotation summaries for native parity.");
	settingsLabel->SetBounds(10, 10, 720, 20);

	summaryLabel = new Gwen::Controls::Label(settingsPage);
	summaryLabel->SetText("No custom game data yet.");
	summaryLabel->SetBounds(10, 40, 780, 20);

	// Blocks Page
	Gwen::Controls::Base* blockPage = tabs->AddPage("Blocks")->GetPage();
	Gwen::Controls::Label* blockLabel = new Gwen::Controls::Label(blockPage);
	blockLabel->SetText("Block editor parity pass pending. Piece editing is now interactive below.");
	blockLabel->SetBounds(10, 10, 720, 20);

	// Pieces Page
	Gwen::Controls::Base* piecePage = tabs->AddPage("Pieces")->GetPage();
	addPieceBtn = new Gwen::Controls::Button(piecePage);
	addPieceBtn->SetText(L"Add Piece Type");
	addPieceBtn->SetBounds(10, 10, 130, 28);
	addPieceBtn->onPress.Add(this, &CustomGameEditorControl::onAddPieceButton);

	duplicatePieceBtn = new Gwen::Controls::Button(piecePage);
	duplicatePieceBtn->SetText(L"Duplicate Piece");
	duplicatePieceBtn->SetBounds(150, 10, 130, 28);
	duplicatePieceBtn->onPress.Add(this, &CustomGameEditorControl::onDuplicatePieceButton);

	removePieceBtn = new Gwen::Controls::Button(piecePage);
	removePieceBtn->SetText(L"Remove Piece");
	removePieceBtn->SetBounds(290, 10, 130, 28);
	removePieceBtn->onPress.Add(this, &CustomGameEditorControl::onRemovePieceButton);

	addRotationBtn = new Gwen::Controls::Button(piecePage);
	addRotationBtn->SetText(L"Add Rotation");
	addRotationBtn->SetBounds(430, 10, 130, 28);
	addRotationBtn->onPress.Add(this, &CustomGameEditorControl::onAddRotationButton);

	duplicateRotationBtn = new Gwen::Controls::Button(piecePage);
	duplicateRotationBtn->SetText(L"Duplicate Rotation");
	duplicateRotationBtn->SetBounds(570, 10, 140, 28);
	duplicateRotationBtn->onPress.Add(this, &CustomGameEditorControl::onDuplicateRotationButton);

	removeRotationBtn = new Gwen::Controls::Button(piecePage);
	removeRotationBtn->SetText(L"Remove Rotation");
	removeRotationBtn->SetBounds(720, 10, 130, 28);
	removeRotationBtn->onPress.Add(this, &CustomGameEditorControl::onRemoveRotationButton);

	clearRotationBtn = new Gwen::Controls::Button(piecePage);
	clearRotationBtn->SetText(L"Clear Rotation");
	clearRotationBtn->SetBounds(10, 50, 130, 28);
	clearRotationBtn->onPress.Add(this, &CustomGameEditorControl::onClearRotationButton);

	prevPieceBtn = new Gwen::Controls::Button(piecePage);
	prevPieceBtn->SetText(L"< Piece");
	prevPieceBtn->SetBounds(150, 50, 100, 26);
	prevPieceBtn->onPress.Add(this, &CustomGameEditorControl::onPrevPieceButton);

	nextPieceBtn = new Gwen::Controls::Button(piecePage);
	nextPieceBtn->SetText(L"Piece >");
	nextPieceBtn->SetBounds(260, 50, 100, 26);
	nextPieceBtn->onPress.Add(this, &CustomGameEditorControl::onNextPieceButton);

	prevRotationBtn = new Gwen::Controls::Button(piecePage);
	prevRotationBtn->SetText(L"< Rot");
	prevRotationBtn->SetBounds(380, 50, 100, 26);
	prevRotationBtn->onPress.Add(this, &CustomGameEditorControl::onPrevRotationButton);

	nextRotationBtn = new Gwen::Controls::Button(piecePage);
	nextRotationBtn->SetText(L"Rot >");
	nextRotationBtn->SetBounds(490, 50, 100, 26);
	nextRotationBtn->onPress.Add(this, &CustomGameEditorControl::onNextRotationButton);

	pieceLabel = new Gwen::Controls::Label(piecePage);
	pieceLabel->SetText("Piece: none");
	pieceLabel->SetBounds(10, 88, 420, 20);

	rotationLabel = new Gwen::Controls::Label(piecePage);
	rotationLabel->SetText("Rotation: none");
	rotationLabel->SetBounds(10, 112, 420, 20);

	int startX = 10;
	int startY = 150;
	int cellSize = 38;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			Gwen::Controls::Button* cellBtn = new Gwen::Controls::Button(piecePage);
			cellBtn->SetText(L".");
			cellBtn->SetBounds(startX + x * cellSize, startY + y * cellSize, cellSize, cellSize);
			cellBtn->onPress.Add(this, &CustomGameEditorControl::onCellButton);
			cellButtons[y][x] = cellBtn;
			cellLookup[cellBtn] = std::make_pair(x, y);
		}
	}

	addPiece();
	refreshEditorState();
}

void CustomGameEditorControl::initPreviewGame()
{
	// Preview bootstrapping stays stubbed for now; this parity pass focuses on live editing state.
}

void CustomGameEditorControl::Render(Gwen::Skin::Base* skin)
{
	Gwen::Controls::Base::Render(skin);

	Rotation* rotation = getSelectedRotation();
	if (rotation == nullptr) return;

	Gwen::Rect bounds = GetInnerBounds();

	int startX = bounds.x + 200;
	int startY = bounds.y + 100;
	int blockSize = 16;

	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	Gwen::Color blockColor = Gwen::Color(100, 100, 255, 255);

	if (pieceType != nullptr && pieceType->blocks.size() > 0)
	{
		BlockType* bType = pieceType->blocks.get(0).get();
		if (bType && bType->useSpecialColor)
		{
			blockColor = Gwen::Color(bType->color.r * 255, bType->color.g * 255, bType->color.b * 255, 255);
		}
	}

	for (int i = 0; i < rotation->blockOffsets.size(); i++)
	{
		BlockOffset* offset = rotation->blockOffsets.get(i);
		skin->GetRender()->SetDrawColor(blockColor);
		skin->GetRender()->DrawFilledRect(Gwen::Rect(startX + offset->x() * blockSize, startY + offset->y() * blockSize, blockSize, blockSize));
		skin->GetRender()->SetDrawColor(Gwen::Color(0, 0, 0, 100));
		skin->GetRender()->DrawLinedRect(Gwen::Rect(startX + offset->x() * blockSize, startY + offset->y() * blockSize, blockSize, blockSize));
	}
}

void CustomGameEditorControl::saveAllToCurrentGameType()
{
	refreshEditorState();
}

void CustomGameEditorControl::onAddPieceButton(Gwen::Controls::Base* control)
{
	addPiece();
}

void CustomGameEditorControl::onDuplicatePieceButton(Gwen::Controls::Base* control)
{
	duplicatePiece();
}

void CustomGameEditorControl::onRemovePieceButton(Gwen::Controls::Base* control)
{
	removePiece();
}

void CustomGameEditorControl::onAddRotationButton(Gwen::Controls::Base* control)
{
	addRotation();
}

void CustomGameEditorControl::onDuplicateRotationButton(Gwen::Controls::Base* control)
{
	duplicateRotation();
}

void CustomGameEditorControl::onRemoveRotationButton(Gwen::Controls::Base* control)
{
	removeRotation();
}

void CustomGameEditorControl::onPrevPieceButton(Gwen::Controls::Base* control)
{
	cyclePiece(-1);
}

void CustomGameEditorControl::onNextPieceButton(Gwen::Controls::Base* control)
{
	cyclePiece(1);
}

void CustomGameEditorControl::onPrevRotationButton(Gwen::Controls::Base* control)
{
	cycleRotation(-1);
}

void CustomGameEditorControl::onNextRotationButton(Gwen::Controls::Base* control)
{
	cycleRotation(1);
}

void CustomGameEditorControl::onClearRotationButton(Gwen::Controls::Base* control)
{
	clearRotation();
}

void CustomGameEditorControl::onCellButton(Gwen::Controls::Base* control)
{
	auto it = cellLookup.find(control);
	if (it == cellLookup.end()) return;
	toggleCell(it->second.first, it->second.second);
}

void CustomGameEditorControl::addPiece()
{
	shared_ptr<PieceType> pieceType = make_shared<PieceType>();
	pieceType->name = "Piece " + to_string(currentGameType->pieceTypes.size() + 1);
	pieceType->useAsNormalPiece = true;
	currentGameType->pieceTypes.add(pieceType);
	selectedPieceIndex = currentGameType->pieceTypes.size() - 1;
	selectedRotationIndex = 0;
	refreshEditorState();
}

void CustomGameEditorControl::duplicatePiece()
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	if (pieceType == nullptr) return;
	shared_ptr<PieceType> duplicate = make_shared<PieceType>(*pieceType);
	duplicate->name = pieceType->name + " Copy";
	currentGameType->pieceTypes.add(selectedPieceIndex + 1, duplicate);
	selectedPieceIndex = selectedPieceIndex + 1;
	selectedRotationIndex = 0;
	refreshEditorState();
}

void CustomGameEditorControl::removePiece()
{
	if (currentGameType == nullptr) return;
	if (selectedPieceIndex < 0 || selectedPieceIndex >= currentGameType->pieceTypes.size()) return;

	static int removalConfirmations = 0;
	if (removalConfirmations == 0)
	{
		if (removePieceBtn) removePieceBtn->SetText("Click Again to Confirm");
		removalConfirmations++;
		return;
	}

	if (removePieceBtn) removePieceBtn->SetText("Remove Piece");
	removalConfirmations = 0;

	currentGameType->pieceTypes.removeAt(selectedPieceIndex);
	if (currentGameType->pieceTypes.size() == 0)
	{
		selectedPieceIndex = -1;
		selectedRotationIndex = 0;
	}
	else
	{
		selectedPieceIndex = min(selectedPieceIndex, currentGameType->pieceTypes.size() - 1);
		selectedRotationIndex = 0;
	}
	refreshEditorState();
}

void CustomGameEditorControl::addRotation()
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	if (pieceType == nullptr)
	{
		addPiece();
		pieceType = getSelectedPieceType();
	}
	if (pieceType == nullptr) return;

	Rotation* rotation = new Rotation();
	pieceType->rotationSet.add(rotation);
	selectedRotationIndex = pieceType->rotationSet.size() - 1;
	refreshEditorState();
}

void CustomGameEditorControl::duplicateRotation()
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	if (pieceType == nullptr || pieceType->rotationSet.size() == 0) return;
	Rotation* source = pieceType->rotationSet.get(selectedRotationIndex);
	Rotation* duplicate = new Rotation(*source);
	pieceType->rotationSet.add(duplicate);
	selectedRotationIndex = pieceType->rotationSet.size() - 1;
	refreshEditorState();
}

void CustomGameEditorControl::removeRotation()
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	if (pieceType == nullptr || pieceType->rotationSet.size() == 0) return;

	static int removalConfirmationsRot = 0;
	if (removalConfirmationsRot == 0)
	{
		if (removeRotationBtn) removeRotationBtn->SetText("Click Again to Confirm");
		removalConfirmationsRot++;
		return;
	}

	if (removeRotationBtn) removeRotationBtn->SetText("Remove Rotation");
	removalConfirmationsRot = 0;

	pieceType->rotationSet.removeAt(selectedRotationIndex);
	if (pieceType->rotationSet.size() == 0)
	{
		selectedRotationIndex = 0;
	}
	else
	{
		selectedRotationIndex = min(selectedRotationIndex, pieceType->rotationSet.size() - 1);
	}
	refreshEditorState();
}

void CustomGameEditorControl::cyclePiece(int delta)
{
	if (currentGameType == nullptr || currentGameType->pieceTypes.size() == 0) return;
	if (selectedPieceIndex < 0) selectedPieceIndex = 0;
	selectedPieceIndex = (selectedPieceIndex + delta + currentGameType->pieceTypes.size()) % currentGameType->pieceTypes.size();
	selectedRotationIndex = 0;
	refreshEditorState();
}

void CustomGameEditorControl::cycleRotation(int delta)
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	if (pieceType == nullptr || pieceType->rotationSet.size() == 0) return;
	selectedRotationIndex = (selectedRotationIndex + delta + pieceType->rotationSet.size()) % pieceType->rotationSet.size();
	refreshEditorState();
}

void CustomGameEditorControl::clearRotation()
{
	Rotation* rotation = getSelectedRotation();
	if (rotation == nullptr) return;
	rotation->blockOffsets.clear();
	refreshEditorState();
}

void CustomGameEditorControl::toggleCell(int x, int y)
{
	Rotation* rotation = getSelectedRotation();
	if (rotation == nullptr)
	{
		addRotation();
		rotation = getSelectedRotation();
	}
	if (rotation == nullptr) return;

	for (int i = 0; i < rotation->blockOffsets.size(); i++)
	{
		BlockOffset* existing = rotation->blockOffsets.get(i);
		if (existing != nullptr && existing->x == x && existing->y == y)
		{
			rotation->blockOffsets.removeAt(i);
			refreshEditorState();
			return;
		}
	}

	rotation->blockOffsets.add(new BlockOffset(x, y));
	refreshEditorState();
}

shared_ptr<PieceType> CustomGameEditorControl::getSelectedPieceType()
{
	if (currentGameType == nullptr) return nullptr;
	if (selectedPieceIndex < 0 || selectedPieceIndex >= currentGameType->pieceTypes.size()) return nullptr;
	return currentGameType->pieceTypes.get(selectedPieceIndex);
}

Rotation* CustomGameEditorControl::getSelectedRotation()
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	if (pieceType == nullptr || pieceType->rotationSet.size() == 0) return nullptr;
	if (selectedRotationIndex < 0) selectedRotationIndex = 0;
	if (selectedRotationIndex >= pieceType->rotationSet.size()) selectedRotationIndex = pieceType->rotationSet.size() - 1;
	return pieceType->rotationSet.get(selectedRotationIndex);
}

int CustomGameEditorControl::getCurrentRotationBlockCount()
{
	Rotation* rotation = getSelectedRotation();
	if (rotation == nullptr) return 0;
	return rotation->blockOffsets.size();
}

int CustomGameEditorControl::getTotalRotationCount()
{
	if (currentGameType == nullptr) return 0;
	int total = 0;
	for (int i = 0; i < currentGameType->pieceTypes.size(); i++)
	{
		shared_ptr<PieceType> pieceType = currentGameType->pieceTypes.get(i);
		if (pieceType != nullptr) total += pieceType->rotationSet.size();
	}
	return total;
}

void CustomGameEditorControl::refreshEditorState()
{
	shared_ptr<PieceType> pieceType = getSelectedPieceType();
	Rotation* rotation = getSelectedRotation();

	if (removePieceBtn) removePieceBtn->SetText("Remove Piece");
	if (removeRotationBtn) removeRotationBtn->SetText("Remove Rotation");

	string pieceSummary = "Piece: none";
	if (pieceType != nullptr)
	{
		pieceSummary = "Piece: " + pieceType->name + " (" + to_string(selectedPieceIndex + 1) + "/" + to_string(currentGameType->pieceTypes.size()) + ")";
	}
	pieceLabel->SetText(Gwen::Utility::StringToUnicode(pieceSummary));

	string rotationSummary = "Rotation: none";
	if (rotation != nullptr)
	{
		rotationSummary = "Rotation: " + to_string(selectedRotationIndex) + " (" + to_string(rotation->blockOffsets.size()) + " blocks)";
	}
	rotationLabel->SetText(Gwen::Utility::StringToUnicode(rotationSummary));

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			bool filled = false;
			if (rotation != nullptr)
			{
				for (int i = 0; i < rotation->blockOffsets.size(); i++)
				{
					BlockOffset* block = rotation->blockOffsets.get(i);
					if (block != nullptr && block->x == x && block->y == y)
					{
						filled = true;
						break;
					}
				}
			}
			cellButtons[y][x]->SetText(filled ? L"#" : L".");
		}
	}

	string summary = "Mode: ";
	summary += currentGameType != nullptr && currentGameType->gameMode == GameMode::STACK ? "STACK" : "DROP";
	summary += " | Grid: ";
	summary += to_string(currentGameType != nullptr ? currentGameType->gridWidth : 0);
	summary += "x";
	summary += to_string(currentGameType != nullptr ? currentGameType->gridHeight : 0);
	summary += " | Pieces: ";
	summary += to_string(currentGameType != nullptr ? currentGameType->pieceTypes.size() : 0);
	summary += " | Rotations: ";
	summary += to_string(getTotalRotationCount());
	summary += " | Filled cells: ";
	summary += to_string(getCurrentRotationBlockCount());
	summary += " | Hold/Next: ";
	summary += currentGameType != nullptr && currentGameType->holdPieceEnabled ? "hold on" : "hold off";
	summary += ", next=";
	summary += to_string(currentGameType != nullptr ? currentGameType->numberOfNextPiecesToShow : 0);
	summaryLabel->SetText(Gwen::Utility::StringToUnicode(summary));
}
