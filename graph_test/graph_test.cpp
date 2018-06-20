#include <Windows.h>

#define IMGUI_API
#define IMGUI_DEFINE_MATH_OPERATORS
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include "../tween.hpp"


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
    return QueryPerformanceCounter(&value) ? (long)value.QuadPart : (long)GetTickCount64();
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
        time.QuadPart = -us * 10;
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

namespace ImGui
{
    template<int steps>
    void tween_table(ImVec2 results[steps + 1], float (*func)(float, float, float))
    {
        for (unsigned step = 0; step <= steps; ++step)
        {
            ImVec2 point = {
                (float)step / steps,
                func(0, 1, (float)step / steps)
            };
            results[step] = point;
        }
    }

    void TweenGraph(const char *label, float (*func)(float, float, float))
    {
        // visuals
        enum { SMOOTHNESS = 128 }; // curve smoothness: the higher number of segments, the smoother curve
        enum { CURVE_WIDTH = 2 }; // main curved line width
        enum { LINE_WIDTH = 1 }; // handlers: small lines width
        enum { GRAB_RADIUS = 6 }; // handlers: circle radius
        enum { GRAB_BORDER = 2 }; // handlers: circle border width

        const ImGuiStyle& Style = GetStyle();
        const ImGuiIO& IO = GetIO();
        ImDrawList* DrawList = GetWindowDrawList();
        ImGuiWindow* Window = GetCurrentWindow();
        if (Window->SkipItems)
            return;

        const float avail = GetContentRegionAvailWidth();
        const float dim = ImMin(avail, 512.f);
        ImVec2 Canvas(dim, dim * 0.5f);
        
        ImRect bb(Window->DC.CursorPos, Window->DC.CursorPos + Canvas);
        ItemSize(bb);
        if (!ItemAdd(bb, NULL))
            return;
        RenderFrame(bb.Min, bb.Max, GetColorU32(ImGuiCol_FrameBg, 1), true, Style.FrameRounding);
        // background grid
        for (int i = 0; i <= Canvas.x; i += (Canvas.x / 1))
        {
            DrawList->AddLine(
                ImVec2(bb.Min.x + i, bb.Min.y),
                ImVec2(bb.Min.x + i, bb.Max.y),
                GetColorU32(ImGuiCol_TextDisabled));
        }
        for (int i = 0; i <= Canvas.y; i += (Canvas.y / 1))
        {
            DrawList->AddLine(
                ImVec2(bb.Min.x, bb.Min.y + i),
                ImVec2(bb.Max.x, bb.Min.y + i),
                GetColorU32(ImGuiCol_TextDisabled));
        }

        ImVec2 results[SMOOTHNESS + 1];
        tween_table<SMOOTHNESS>(results, func);
        ImColor color(GetStyle().Colors[ImGuiCol_PlotLines]);
        for (int i = 0; i < SMOOTHNESS; ++i)
        {
            ImVec2 p = { results[i + 0].x, 1 - results[i + 0].y };
            ImVec2 q = { results[i + 1].x, 1 - results[i + 1].y };
            ImVec2 r(p.x * (bb.Max.x - bb.Min.x) + bb.Min.x, p.y * (bb.Max.y - bb.Min.y) + bb.Min.y);
            ImVec2 s(q.x * (bb.Max.x - bb.Min.x) + bb.Min.x, q.y * (bb.Max.y - bb.Min.y) + bb.Min.y);
            DrawList->AddLine(r, s, color, CURVE_WIDTH);
        }
    }
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

    /* Initialize runtime */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        show_message_box(SDL_GetError());
        return 1;
    }

    /* Create window and context */
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

    /* Load OpenGL functions with GLEW */
    glewExperimental  = GL_TRUE;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        show_message_box((const char*)glewGetErrorString(glGetError()), window);
        return 1;
    }

    /* Intialize ImGui */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForOpenGL(window, glcontext);     
    ImGui_ImplOpenGL3_Init();    
    
    ImGui::StyleColorsDark();

#define TWEEN_FUNC(x) x ,
    typedef float (*tween_f)(float, float, float);
    tween_f tween_funcs[] =
    {
    #include "tween_funcs.h"
    };
#undef TWEEN_FUNC

#define TWEEN_FUNC(x) #x ,
    const char* tween_funcnames[] = 
    {
    #include "tween_funcs.h"
    };
#undef TWEEN_FUNC

    /* Main loop */
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

        static int func = 0;
        static float pos;
        if (ImGui::Begin("Menu"))
        {
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            if (ImGui::Combo("Functions", &func, tween_funcnames, IM_ARRAYSIZE(tween_funcnames)))
            {
                pos = 0;
            }
        }
        ImGui::End();

        if (ImGui::Begin("Graph"))
        {
            ImGui::Text("Functions: %s", tween_funcnames[func]);
            ImGui::TweenGraph(tween_funcnames[func], tween_funcs[func]);
        }
        ImGui::End();

        if (ImGui::Begin("Animation"))
        {
            ImDrawList* DrawList = ImGui::GetWindowDrawList();
            ImGuiWindow* Window  = ImGui::GetCurrentWindow();
            if (!Window->SkipItems)
            {
                const ImVec2 size = ImGui::GetContentRegionAvail();
                const ImVec2 cursor = Window->DC.CursorPos;

                static float time = 0;
                static float sign = 1;
                time += delta_time;
                if (time >= 1.0f)
                {
                    sign = -sign;
                    time = 0.0f;
                }

                if (sign > 0)
                {
                    pos = tween_funcs[func](size.x * 0.1f, size.x * 0.9f, time);
                }
                else
                {
                    pos = tween_funcs[func](size.x * 0.9f, size.x * 0.1f, time);
                }
                DrawList->AddCircle(ImVec2(cursor.x + pos, cursor.y + size.y * 0.5f), 12.0f, ImGui::GetColorU32(ImGuiCol_TextDisabled));
            }
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