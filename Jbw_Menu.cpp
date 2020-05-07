#include "Jbw_Menu.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Menu::Jbw_Menu(Jbw_Handles* handles)
{
	h = handles;
	Jrdr = h->JbwRdr; // Moet dit fix in Base class
	// Create Frame at the top of the screen
	FrameX = 0;
	FrameY = 0; // Hide Top line of Frame
	FrameH = 18;
	FrameW = h->GuiArea.w;
	LineColor = J_C_White;
	FillColor = J_C_White;
	Fill = true;
	CreatePts(); // Create the frame points from above info
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Menu::~Jbw_Menu()
{
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: Create
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MenuAdd(std::string NewText, int w)
{
	Jbw_Button* TmpMainMenu = new Jbw_Button[MnuCnt + 1];

	if (MnuCnt > 0) {
		for (int I = 0; I < MnuCnt; I++) {
			TmpMainMenu[I] = MainMenu[I];
		}
		delete[] MainMenu;
	}
	MainMenu = TmpMainMenu;

	MainMenu[MnuCnt].Jrdr = h->JbwRdr;
	MainMenu[MnuCnt].TbxX = TotalWidth + 1;
	MainMenu[MnuCnt].TbxY = 1;
	MainMenu[MnuCnt].TbxW = w-2;
	MainMenu[MnuCnt].TbxH = 16;
	MainMenu[MnuCnt].TxtSize = 12;
	MainMenu[MnuCnt].Align = J_CENTRE;
	MainMenu[MnuCnt].Add(NewText);

	MainMenu[MnuCnt].Border.Jrdr = h->JbwRdr;
	MainMenu[MnuCnt].Border.FrameX = TotalWidth;
	MainMenu[MnuCnt].Border.FrameY = 0;
	MainMenu[MnuCnt].Border.FrameW = w;
	MainMenu[MnuCnt].Border.FrameH = 18;
	MainMenu[MnuCnt].Border.CreatePts();

	MainMenu[MnuCnt].Border.Fill = true;
	MainMenu[MnuCnt].Border.LineColor = J_C_White;
	MainMenu[MnuCnt].Border.FillColor = J_C_White;	
	MainMenu[MnuCnt].BtnColor = J_C_White;
	MainMenu[MnuCnt].BtnBorderColor = J_C_White;
	MainMenu[MnuCnt].HoverColor = J_C_msOver;
	MainMenu[MnuCnt].HoverBorderColor = J_C_Frame;
	MainMenu[MnuCnt].ClickColor = J_C_BtnDwn;
	
	MnuCnt++;
	TotalWidth += w;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrCbx
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MnuRdr(Jbw_Handles* h)
{
	RdrFrame();
	for (int I = 0; I < MnuCnt; I++) {
		MainMenu[I].RdrBtn();
	}
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CbxEvent
------------------------------------------------------------------------------------------*/
void Jbw_Menu::MnuEvent(Jbw_Handles* h)
{
	for (int I = 0; I < MnuCnt; I++) {
		MainMenu[I].BtnEvent(h);
	}

}





