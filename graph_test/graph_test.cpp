#include <Windows.h>

#define IMGUI_API

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>


void show_message_box(const char* msg, SDL_Window* window = NULL)
{
    SDL_MessageBoxData msgbox;
    msgbox.title = "Error";
    msgbox.window = window;
    msgbox.buttons = NULL;
    msgbox.message = msg;

    SDL_ShowMessageBox(&msgbox, NULL);
}

inline long perf_count(void)
{
    LARGE_INTEGER value;
    return QueryPerformanceCounter(&value) ? (long)value.QuadPart : GetTickCount64();
}

inline long perf_frequency(void)
{
    LARGE_INTEGER value;
    return QueryPerformanceFrequency(&value) ? (long)value.QuadPart : 1000;
}

inline void usleep(long us)
{
    typedef NTSTATUS (NTAPI * NtDelayExecutionFN)(BOOL, LARGE_INTEGER*);
    static NtDelayExecutionFN fn;

    if (!fn)
    {
        fn = (NtDelayExecutionFN)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtDelayExecution");
    }

    if (fn)
    {
        LARGE_INTEGER time;
        time.QuadPart = -us / 10;
        fn(FALSE, &time);
    }
    else
    {
        Sleep(us / 1000);
    }
}

extern "C" {
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;        // Nvidia 
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;  // AMD
}

int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPTSTR pCmdLine,
                      int nCmdShow)
{
    (void)hInstance;
    (void)hPrevInstance;
    (void)pCmdLine;
    (void)nCmdShow;


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        show_message_box(SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Tween Graph Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window)
    {
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    if (!glcontext)
    {
        show_message_box(SDL_GetError(), window);
        return 1;
    }                                     
    SDL_GL_SetSwapInterval(0); // Disable vsync

    glewExperimental  = GL_TRUE;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        show_message_box((const char*)glewGetErrorString(glGetError()), window);
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForOpenGL(window, glcontext);     
    ImGui_ImplOpenGL3_Init();    
    
    ImGui::StyleColorsDark();

    long frame_limit = perf_frequency() / 60;
    double ifreq = 1.0 / perf_frequency();
    float delta_time = 0.0f;
    SDL_Event event;
    while (1)
    {
        long ticks = perf_count();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            else
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
            }
        }

        if (event.type == SDL_QUIT)
        {
            break;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window, delta_time);
        ImGui::NewFrame();

        if (ImGui::Begin("Menu"))
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
        ImGui::End();

        ImGui::Render();     
        SDL_GL_MakeCurrent(window, glcontext);
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);

        // Calculate frame time and relax CPU usage
        long delta = perf_count() - ticks;
        if (delta < frame_limit)
        {
            double sleep_time = (frame_limit - delta) * ifreq;
            usleep((long)(sleep_time * 1000 * 1000));
            delta = frame_limit;
        }
        delta_time = (float)(delta * ifreq);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}