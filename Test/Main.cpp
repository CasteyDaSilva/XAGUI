#include "Main.h"

XAGUI::Renderer* renderer = 0;
XAGUI::Form* form = 0;

char buffer[MAX_BUFFER];

bool FormEvent(XAGUI::Form* form, SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			form->MouseMoveEvent(event->motion.x, event->motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
			{
				if (form->MouseButtonDownEvent(event->button.x, event->button.y, event->button.button) 
					!= 0) return true;
			}
			return false;

		case SDL_MOUSEBUTTONUP:
			{
				form->MouseButtonUpEvent(event->button.x, event->button.y, event->button.button);
			}
			break;

		case SDL_FINGERMOTION:
			{
				form->TouchMoveEvent(static_cast<int>(SCREEN_WIDTH * event->tfinger.x), 
					static_cast<int>(SCREEN_HEIGHT * event->tfinger.y));
			}
			break;

		case SDL_FINGERDOWN:
			{
				if (form->TouchDownEvent(static_cast<int>(SCREEN_WIDTH * event->tfinger.x), 
					static_cast<int>(SCREEN_HEIGHT * event->tfinger.y)) != 0)
					return true;
			}
			return false;

		case SDL_FINGERUP:
			{
				form->TouchUpEvent(static_cast<int>(SCREEN_WIDTH * event->tfinger.x), 
					static_cast<int>(SCREEN_HEIGHT * event->tfinger.y));
			}
			break;

		case SDL_KEYDOWN:
			return form->KeyDownEvent(event->key.keysym.scancode);
		
		case SDL_KEYUP:
			return form->KeyUpEvent(event->key.keysym.scancode);

		case SDL_TEXTINPUT:
			return form->TextInputEvent(event->text.text);
	}
	return false;
}

void OnSliderValueChanged(XAGUI::Control* control)
{
	if (control == form->GetChild("sldHSlider"))
	{
		sprintf(buffer, "Horizontal Slider Value: %d", static_cast<XAGUI::Slider*>(control)->GetValue());
		static_cast<XAGUI::Label*>(form->GetChild("lblHSliderValue"))->SetText(buffer);
	}
	else
	{
		sprintf(buffer, "Vertical Slider Value: %d", static_cast<XAGUI::Slider*>(control)->GetValue());
		static_cast<XAGUI::Label*>(form->GetChild("lblVSliderValue"))->SetText(buffer);
	}
}

void OnAnalogStickValueChanged(XAGUI::Control* control)
{
	XAGUI::AnalogStick* analogStick = static_cast<XAGUI::AnalogStick*>(control);

	sprintf(buffer, "Analog Stick Value X: %f", analogStick->GetValueX());
	static_cast<XAGUI::Label*>(form->GetChild("lblAnalogStickValueX"))->SetText(buffer);

	sprintf(buffer, "Analog Stick Value Y: %f", analogStick->GetValueY());
	static_cast<XAGUI::Label*>(form->GetChild("lblAnalogStickValueY"))->SetText(buffer);
}

tinyxml2::XMLError LoadForm(XAGUI::Form* form, cchar* file)
{
#if defined(__ANDROID__)
	SDL_RWops* xmlFile = SDL_RWFromFile(file, "rb");
	char buf[8192];
	SDL_RWread(xmlFile, buf, sizeof (buf), 1);
	tinyxml2::XMLError result = form->XAGUI::Form::LoadFromMemory(buf);
	SDL_RWclose(xmlFile);
#else
	tinyxml2::XMLError result = form->XAGUI::Form::Load(file);
#endif
	return result;
}

int main(int argc, char** argv)
{
	SDL_Window* window;

	// Initializes SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Message(SDL_MESSAGEBOX_ERROR, SDL_GetError());
        return false;
    }

	// Gets current display
	SDL_DisplayMode display;
	SDL_GetDisplayMode(0, 0, &display);

	// For Android and iOS devices the size of window should be the same as screen resolution
#if !defined(__ANDROID__) && !defined(__IPHONEOS__)
	display.w = 1024;
	display.h = 768;
#endif

	// Creates window
	window = SDL_CreateWindow("XAGUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		display.w, display.h, SDL_WINDOW_SHOWN);
    if (window == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, SDL_GetError());
        return false;
    }

	renderer = new XAGUI::Renderer(window, display.w, display.h);
	if (renderer->Initialize())
	{
		XAGUI::XAGUI::SetRenderer(renderer);
		
		form = new XAGUI::Form();
		tinyxml2::XMLError result = LoadForm(form, "res/form.xml");
		if (result != 0)
		{
			sprintf(buffer, "Cannot load form! XML Error: %u", result);
			Message(SDL_MESSAGEBOX_ERROR, buffer);
		}
		else
		{
			static_cast<XAGUI::Slider*>(form->GetChild("sldHSlider"))->onValueChanged.bind(
				&OnSliderValueChanged);

			static_cast<XAGUI::Slider*>(form->GetChild("sldVSlider"))->onValueChanged.bind(
				&OnSliderValueChanged);
			
			static_cast<XAGUI::AnalogStick*>(form->GetChild("asAnalogStick"))->onValueChanged.bind(
				&OnAnalogStickValueChanged);

			XAGUI::StaticText* fpsText;
			fpsText = renderer->GetStaticText("res/arial.ttf", 10, "FPS: 0");
			fpsText->SetColor(255, 255, 255, 225);
		
			uint newTime;
			float deltaTime;
			float fpsTime = 0.0f;
			uint frames = 0;
			uint time = SDL_GetTicks();

			SDL_Event event;
			bool quit = false;
			while (!quit)
			{
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
						case SDL_QUIT:
							quit = true;
							break;

						default:
							FormEvent(form, &event);
							break;
					}
				}
				newTime = SDL_GetTicks();
				deltaTime = (newTime - time) / 1000.0f;
				time = newTime;

				renderer->Clear();

				form->Render();

				renderer->Render(fpsText, 3, 3);

				renderer->Present();

				++frames;
				fpsTime += deltaTime;
				if (fpsTime >= 1.0f)
				{
					sprintf(buffer, "FPS: %u", static_cast<uint>(frames / fpsTime));
					fpsText->Set(buffer);

					frames = 0;
					fpsTime = 0.0f;
				}
			}

			SAFE_DELETE(fpsText);
		}

		SAFE_DELETE(form);
	}

	SAFE_DELETE(renderer);

    SDL_DestroyWindow(window);
	SDL_Quit();
    return 0;
}

void Message(uint flags, cchar* message)
{
#if !defined(__ANDROID__) && !defined(__IPHONEOS__)
	switch (flags)
	{
		case SDL_MESSAGEBOX_ERROR:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "XAGUI", message, 0);
			break;

		case SDL_MESSAGEBOX_WARNING:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "XAGUI", message, 0);
			break;
		
		case SDL_MESSAGEBOX_INFORMATION:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "XAGUI", message, 0);
			break;
	}
#else
	switch (flags)
	{
		case SDL_MESSAGEBOX_ERROR:
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message);
			break;

		case SDL_MESSAGEBOX_WARNING:
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, message);
			break;
		
		case SDL_MESSAGEBOX_INFORMATION:
			SDL_Log(message);
			break;
	}
#endif
}
