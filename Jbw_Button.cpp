#include "Jbw_Button.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::Jbw_Button(Jbw_Handles* handles, int x, int y, int w, int h,
	std::string Text, int Fsize)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;
	Caption.assign(Text);
	TxtSize = Fsize;
	
	CreateButton();
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::~Jbw_Button() 
{

}

/*-----------------------------------------------------------------------------------------
	COPY CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_Button::Jbw_Button(const Jbw_Button& cp, std::string NewCaption) : Jbw_Base(cp)
{
	BtnColor = cp.BtnColor;
	BtnBorderColor = cp.BtnBorderColor;
	HoverColor = cp.HoverColor;
	HoverBorderColor = cp.HoverBorderColor;
	ClickColor = cp.ClickColor;
	TxtSize = cp.TxtSize;
	TxtAlign = cp.TxtAlign;
	Caption = NewCaption;
	
	Tbx = new Jbw_TextBox(*cp.Tbx);
	Tbx->Text.assign(Caption);
	Tbx->CreateTexture();
}

/*-----------------------------------------------------------------------------------------
	ASIGNMENT OPERATOR OVERLOAD
------------------------------------------------------------------------------------------*/
Jbw_Button& Jbw_Button::operator=(const Jbw_Button& cp)
{
	if (this != &cp)// Self assign check
	{
		Jbw_Base::operator=(cp); // Calling Baseclass copy
		BtnColor = cp.BtnColor;
		BtnBorderColor = cp.BtnBorderColor;
		HoverColor = cp.HoverColor;
		HoverBorderColor = cp.HoverBorderColor;
		ClickColor = cp.ClickColor;
		TxtSize = cp.TxtSize;
		TxtAlign = cp.TxtAlign;
		Caption = cp.Caption;
		
		delete Tbx;
		Tbx = new Jbw_TextBox(*cp.Tbx);
	}
	return *this;
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitBtn
------------------------------------------------------------------------------------------*/
void Jbw_Button::InitBtn(Jbw_Handles* handles, int x, int y, int w, int h,
	std::string Text, int Fsize)
{
	Jhandle = handles;
	Obj.x = x;
	Obj.y = y;
	Obj.w = w;
	Obj.h = h;
	Caption.assign(Text);
	TxtSize = Fsize;

	CreateButton();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: CreateButton
------------------------------------------------------------------------------------------*/
void Jbw_Button::CreateButton(void)
{	
	if (Tbx == NULL) {
		Tbx = new Jbw_TextBox(Jhandle, Caption, Obj.x, Obj.y, Obj.w, Obj.h, TxtSize);
		Tbx->Align = TxtAlign;
		Tbx->FrameOn = true;
		Tbx->FillOn = true;
		Tbx->Border->FillColor = BtnColor;
		Tbx->Border->LineColor = BtnBorderColor;
	}
	else {
		Tbx->Obj = Obj;
		Tbx->CreateTbx();
	}
	Tbx->CreateTexture();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrBtn
------------------------------------------------------------------------------------------*/
void Jbw_Button::RdrBtn(void)
{
	if (Visible == false) {
		return;
	}
	Tbx->CreateTexture();
	Tbx->RdrTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: BtnEvent
------------------------------------------------------------------------------------------*/
J_Type Jbw_Button::BtnEvent(SDL_Event* Event)
{
	J_Type EventType = J_NULL;

	if (Visible == false || Enabled == false) {
		return EventType;
	}

	//If mouse event happened
	if (Event->type == SDL_MOUSEMOTION || Event->type == SDL_MOUSEBUTTONDOWN ||
		Event->type == SDL_MOUSEBUTTONUP) {
		// Get mouse position
		int msX, msY;
		SDL_GetMouseState(&msX, &msY);

		// Mouse pointer over button
		if (msX > Obj.x && msX < Obj.x + Obj.w && msY > Obj.y && msY < Obj.y + Obj.h)
		{
			if (msOver == false) {
				msOver = true;
				DoRender = true;
			}
			
			switch (Event->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				Tbx->Border->FillColor = ClickColor;
				DoRender = true;
				EventType = J_BTN_CLICK;
				break;

			case SDL_MOUSEBUTTONUP:
				Tbx->Border->FillColor = HoverColor;
				DoRender = true;
				break;
			}		
			Tbx->Border->FillColor = HoverColor;
			Tbx->Border->LineColor = HoverBorderColor;
		}
		else {
			if (msOver == true) {
				msOver = false;
				DoRender = true;
			}
			Tbx->Border->LineColor = BtnBorderColor;
			Tbx->Border->FillColor = BtnColor;
		}

		if (DoRender == true) {
			DoRender = false;
			RdrBtn();
		}
	}
	return EventType;
}