#include "Jbw_EditBox.h"

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::Jbw_EditBox(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	J_Properties P;
	P.handles.JbwRdr = Rdr; 
	P.x = x; 
	P.y = y; 
	P.w = w;
	P.h = h;
	P.Fsize = Fsize;
	InitEbx(&P);
}

/*-----------------------------------------------------------------------------------------
	CONSTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::Jbw_EditBox(J_Properties *Prop)
{
	InitEbx(Prop);
}

/*-----------------------------------------------------------------------------------------
	DESTRUCTOR
------------------------------------------------------------------------------------------*/
Jbw_EditBox::~Jbw_EditBox() {

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: InitEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::InitEbx(SDL_Renderer* Rdr, int x, int y, int w, int h, int Fsize)
{
	J_Properties P;
	P.handles.JbwRdr = Rdr;
	P.x = x;
	P.y = y;
	P.w = w;
	P.h = h;
	P.Fsize = Fsize;
	InitEbx(&P);
}
/*-----------------------------------------------------------------------------------------
	FUNCTION: InitEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::InitEbx(J_Properties *Prop)
{
	Id = Prop->Id;
	Tag.assign(Prop->Tag);
	Jrdr = Prop->handles.JbwRdr;
	TbxX = Prop->x + 1; TbxY = Prop->y + 1; TbxW = Prop->w - 2; TbxH = Prop->h - 2;
	Border.InitFrame(Prop);
	Border.Fill = true;
	Border.LineColor = J_C_Frame;
	
	TxtSize = Prop->Fsize;
}

/*-----------------------------------------------------------------------------------------
FUNCTION: Set
------------------------------------------------------------------------------------------*/
bool Jbw_EditBox::SetEbx(std::string* Var, const char* Val)
{
	return SetTbx(Var, Val);
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: RdrEbx
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::RdrEbx(void)
{
	ShowFrame = true;
	RdrTbx();
}

/*-----------------------------------------------------------------------------------------
	FUNCTION: EVENT HANDLER
------------------------------------------------------------------------------------------*/
void Jbw_EditBox::EbxEvent(Jbw_Handles* h)
{
	bool Flag = false;
	//If mouse event happened
	if (h->Event.type == SDL_MOUSEMOTION || h->Event.type == SDL_MOUSEBUTTONDOWN || h->Event.type == SDL_MOUSEBUTTONUP){
		// Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		// Mouse pointer inside Edit box
		if (x > TbxX && x < TbxX + TbxW && y > TbxY && y < TbxY + TbxH)
		{
			msOver = true;

			switch (h->Event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
				if (h->Event.button.button == 1) {
					Focus = true;
				}
				else if (h->Event.button.button == 3) {
				Add(SDL_GetClipboardText());
				RdrEbx();
				}
				break;

			case SDL_MOUSEBUTTONUP:
			//	BackColor = { 255, 255, 255, 255 };
				break;
			}
			

			


			Border.LineColor = J_C_Black;
			if (DoRender == false) {
				DoRender = true;
				RdrEbx();
			}
		}
		else {
			msOver = false;
			if (h->Event.type == SDL_MOUSEBUTTONDOWN) {
				Focus = false;
				Border.LineColor = J_C_Frame;
				RdrEbx();
			}

			Border.LineColor = J_C_Frame;
			if (DoRender == true) {
				DoRender = false;
				RdrEbx();
			}
		}
	}

	if (Focus == true && Enabled == true) {
		if (h->Event.type == SDL_TEXTINPUT){
			Add(h->Event.text.text);
		}
		else if (h->Event.type == SDL_KEYDOWN){
			if (h->Event.key.keysym.sym == SDLK_BACKSPACE) {
				BackSpace();
			}
			else if (h->Event.key.keysym.sym == SDLK_DELETE) {

			}
		}
		Border.LineColor = J_C_Black;
		RdrEbx();
	}

	
	return;

	//if (0) {
	//	if (h->Event.type == SDL_USEREVENT) {
	//		h->Event.user.data1;
	//		my_function();
	//		//	Uint32* AAA{ static_cast<Uint32*>(e->user.data1) };
	//		//	void (*A) (void*) = e->type.user.data2;
	//		//	*A();


	//	}
	//}

	//Uint32 delay = (330 / 10) * 10; // To round it down to the nearest 10 ms 
//SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, &Dp);
//	Uint32 delay = (3300 / 10) * 10; // To round it down to the nearest 10 ms 

//	SDL_TimerID my_timer_id = SDL_AddTimer(delay, Flashy, Trdr);

}

/*-----------------------------------------------------------------------------------------
	FUNCTION: FLASHY
------------------------------------------------------------------------------------------*/
Uint32 Jbw_EditBox::Flashy(Uint32 interval, void* param)
{
	SDL_Event event;
	SDL_UserEvent userevent;

	userevent.type = SDL_USEREVENT;
	userevent.code = 0;
	userevent.data1 = &my_function;
	userevent.data2 = param;

	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return(interval);
}
