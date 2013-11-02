#include "Main.h"

RendererSDL* renderer = 0;
XAGUI::Form* form = 0;

char buffer[MAX_BUFFER];

XAGUI::MouseButton GetXAGUIMouseButton(uchar button)
{
	switch (button)
	{
		case SDL_BUTTON_LEFT:
			return XAGUI::MOUSE_BUTTON_LEFT;

		case SDL_BUTTON_MIDDLE:
			return XAGUI::MOUSE_BUTTON_MIDDLE;

		case SDL_BUTTON_RIGHT:
			return XAGUI::MOUSE_BUTTON_RIGHT;
	}
	return XAGUI::MOUSE_BUTTON_COUNT;
}

XAGUI::Key GetXAGUIKey(SDL_Scancode key)
{
	switch (key)
	{
		case SDL_SCANCODE_BACKSPACE:
			return XAGUI::KEY_BACKSPACE;

		case SDL_SCANCODE_RIGHT:
			return XAGUI::KEY_RIGHT_ARROW;

		case SDL_SCANCODE_LEFT:
			return XAGUI::KEY_LEFT_ARROW;
	}
	return XAGUI::KEY_COUNT;
}

bool FormEvent(XAGUI::Form* form, SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			form->MouseMoveEvent(event->motion.x, event->motion.y);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			return form->MouseButtonEvent(event->button.x, event->button.y, GetXAGUIMouseButton(
				event->button.button), (event->button.state == SDL_PRESSED) ? true : false);

		case SDL_FINGERMOTION:
			{
				form->TouchMoveEvent(static_cast<int>(SCREEN_WIDTH * event->tfinger.x), 
					static_cast<int>(SCREEN_HEIGHT * event->tfinger.y));
			}
			break;

		case SDL_FINGERDOWN:
			return form->TouchEvent(static_cast<int>(SCREEN_WIDTH * event->tfinger.x), 
				static_cast<int>(SCREEN_HEIGHT * event->tfinger.y), true);

		case SDL_FINGERUP:
			return form->TouchEvent(static_cast<int>(SCREEN_WIDTH * event->tfinger.x), 
				static_cast<int>(SCREEN_HEIGHT * event->tfinger.y), false);

		case SDL_KEYDOWN:
			return form->KeyEvent(GetXAGUIKey(event->key.keysym.scancode), true);
		
		case SDL_KEYUP:
			return form->KeyEvent(GetXAGUIKey(event->key.keysym.scancode), false);

		case SDL_TEXTINPUT:
			return form->TextInputEvent(event->text.text);
	}

	return false;
}

void OnSliderValueChanged(XAGUI::Control* control, int value)
{
	if (control == form->GetChild("sldHSlider"))
	{
		sprintf(buffer, "Horizontal Slider Value: %d", value);
		static_cast<XAGUI::Label*>(form->GetChild("lblHSliderValue"))->SetText(buffer);
	}
	else
	{
		sprintf(buffer, "Vertical Slider Value: %d", value);
		static_cast<XAGUI::Label*>(form->GetChild("lblVSliderValue"))->SetText(buffer);
	}
}

int main(int argc, char** argv)
{
	SDL_Window* window;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		Message(SDL_MESSAGEBOX_ERROR, SDL_GetError());
        return false;
    }

	SDL_DisplayMode display;
	uint windowFlags = SDL_WINDOW_SHOWN;
	SDL_GetDisplayMode(0, 0, &display);

#if defined(__ANDROID__) || defined(TARGET_OS_IPHONE)
	//
#else
	display.w = 1024;
	display.h = 768;
#endif

	window = SDL_CreateWindow("XAGUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		display.w, display.h, windowFlags);
    if (window == 0)
	{
		Message(SDL_MESSAGEBOX_ERROR, SDL_GetError());
        return false;
    }

	form = new XAGUI::Form();
	renderer = new RendererSDL(window, display.w, display.h);
	if (renderer->Initialize())
	{
		XAGUI::XAGUI::SetRenderer(renderer);
		XAGUI::XAGUI::SetStartTextInput(SDL_StartTextInput);
		XAGUI::XAGUI::SetStopTextInput(SDL_StopTextInput);
	
		tinyxml2::XMLError result = form->XAGUI::Form::Load("../res/form.xml");
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

			StaticTextSDL* fpsText;
			fpsText = renderer->GetStaticText("../res/arial.ttf", 10, "FPS: 0");
			fpsText->SetColor(255, 255, 255, 225);

			float lastX = 1.0f;
			float lastY = 1.0f;
			float stickValue;

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

				stickValue = static_cast<XAGUI::AnalogStick*>(form->GetChild(
					"asAnalogStick"))->GetValueX();
				if (stickValue != lastX)
				{
					sprintf(buffer, "Analog Stick Value X: %f", stickValue);
					static_cast<XAGUI::Label*>(form->GetChild("lblAnalogStickValueX"))->SetText(buffer);
					lastX = stickValue;
				}

				stickValue = static_cast<XAGUI::AnalogStick*>(form->GetChild(
					"asAnalogStick"))->GetValueY();
				if (stickValue != lastY)
				{
					sprintf(buffer, "Analog Stick Value Y: %f", stickValue);
					static_cast<XAGUI::Label*>(form->GetChild("lblAnalogStickValueY"))->SetText(buffer);
					lastY = stickValue;
				}


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
	}

	SAFE_DELETE(form);
	SAFE_DELETE(renderer);

    SDL_DestroyWindow(window);
	SDL_Quit();

    return 0;
}

void Message(uint flags, cchar* message)
{
#if !defined(__ANDROID__) && !defined(TARGET_OS_IPHONE)
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
