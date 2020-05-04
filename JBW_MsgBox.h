#pragma once
#include "Jbw_Base.h"
#include "Jbw_Button.h"

class Jbw_MsgBox : Jbw_Frame {
public:
	SDL_Window* MsgWindow = NULL; 
	TTF_Font* Font = NULL;
	SDL_Texture* txtImage = NULL;
	Jbw_EditBox* Header = NULL;
	Jbw_Button* btnAck = NULL;
	Jbw_Button* btnNo = NULL;
	SDL_Surface* txtSurf = NULL;
	J_Type MbxType;

	int Window_w;
	int Window_h;
	int TxtSize = 10;

	Jbw_MsgBox() {};
	Jbw_MsgBox(std::string Title, std::string Msg, J_Type OkYesNo,
		int x, int y, int w = 150, int h = 100);
	~Jbw_MsgBox();
	
	J_Type MsgBox(std::string Title, std::string Msg, J_Type OkYesNo,
		int x, int y, int w = 150, int h = 100);

	void RenderMsg(std::string Msg, int Line, bool DoRender);
	void RenderBox(void);
	void Parser(std::string Txt, bool DoRender);

};