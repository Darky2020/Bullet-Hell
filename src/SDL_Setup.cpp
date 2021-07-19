#include "SDL_Setup.h"
#include "Fonts.h"

CSDL_Setup::CSDL_Setup(bool* running)
{

	if (SDL_Init( SDL_INIT_EVERYTHING) < 0 )  
	{  
	    std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;  
	    *running = false;
	}  

	TTF_Init();

	Mix_Init(MIX_INIT_OGG);

	window = NULL;
	window = SDL_CreateWindow("Unnamed bullet hell", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN_DESKTOP);  

	if(window == NULL)
	{
		std::cout << "Could not create window! SDL error: " << SDL_GetError() << std::endl;  
		*running = false;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	SDL_RenderSetLogicalSize(renderer, 1280, 720); 

	if(renderer == NULL)
	{
		std::cout << "Could not create renderer! SDL error" << SDL_GetError() << std::endl;  
		*running = false;
	}

	event = new SDL_Event();

	if(window != NULL && renderer != NULL)
	{
		*running = true;
	}

    ImGuiSDL::Initialize(renderer, 1280, 720);

    lastWheelScrollTimestamp = 0;
}

CSDL_Setup::~CSDL_Setup(void)
{
	ImGuiSDL::Deinitialize();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	ImGui::DestroyContext();
	delete event;
}

SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::GetEvent()
{
	return event;
}

SDL_Window* CSDL_Setup::GetWindow()
{
	return window;
}

void CSDL_Setup::ImGui_SDL2_ProcessEvent(const SDL_Event* event)
{
    ImGuiIO& io = ImGui::GetIO();

    int mouseX, mouseY;
    const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

    int wX, wY;
	SDL_GetWindowSize(GetWindow(), &wX, &wY);

	float scaleX, scaleY;
	scaleX = 1280.f/(float)wX;
	scaleY = 720.f/(float)wY;
	
	io.DeltaTime = 1.0f / 60.0f;
	io.MousePos = ImVec2(static_cast<float>(mouseX*scaleX), static_cast<float>(mouseY*scaleY));

	io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    io.MouseDown[2] = buttons & SDL_BUTTON(SDL_BUTTON_MIDDLE);

    switch (event->type)
    {
	    case SDL_WINDOWEVENT:
	    {
	    	if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				io.DisplaySize.x = static_cast<float>(event->window.data1);
				io.DisplaySize.y = static_cast<float>(event->window.data2);
			}
			break;
		}
	    case SDL_MOUSEWHEEL:
        {
        	// Do this cause SDL2's SDL_MOUSEWHEEL sometimes triggers the case statement multiple times with one event
        	if(lastWheelScrollTimestamp == event->wheel.timestamp) break;
        	else
        	{
	            if (event->wheel.x > 0) io.MouseWheelH += 0.4f;
	            if (event->wheel.x < 0) io.MouseWheelH -= 0.4f;
	            if (event->wheel.y > 0) io.MouseWheel += 0.4f;
	            if (event->wheel.y < 0) io.MouseWheel -= 0.4f;

	            // Do this cause the case statement on its own doesn't keep up with lots of SDL_MOUSEWHEEL events and that causes delays in the event queue
	            lastWheelScroll = event->wheel.timestamp;
	            SDL_Event temp_event;
        		while(SDL_PeepEvents(&temp_event, 1, SDL_GETEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL) > 0)
        		{
        			if (temp_event->wheel.x > 0) io.MouseWheelH += 0.4f;
		            if (temp_event->wheel.x < 0) io.MouseWheelH -= 0.4f;
		            if (temp_event->wheel.y > 0) io.MouseWheel += 0.4f;
		            if (temp_event->wheel.y < 0) io.MouseWheel -= 0.4f;
		            lastWheelScrollTimestamp = temp_event->wheel.timestamp;
        		}
	            break;
        	}
        }
	    case SDL_TEXTINPUT:
        {
            io.AddInputCharactersUTF8(event->text.text);
            break;
        }
	    case SDL_KEYDOWN:
	    case SDL_KEYUP:
        {
            int key = event->key.keysym.scancode;
            IM_ASSERT(key >= 0 && key < IM_ARRAYSIZE(io.KeysDown));
            io.KeysDown[key] = (event->type == SDL_KEYDOWN);
            io.KeyShift = ((SDL_GetModState() & KMOD_SHIFT) != 0);
            io.KeyCtrl = ((SDL_GetModState() & KMOD_CTRL) != 0);
            io.KeyAlt = ((SDL_GetModState() & KMOD_ALT) != 0);
		#ifdef _WIN32
	        io.KeySuper = false;
		#else
	        io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
		#endif
	        break;
		}
	    default:
    	{
    		break;
    	}
	}
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(event);
	SDL_RenderClear(renderer);
}

void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}