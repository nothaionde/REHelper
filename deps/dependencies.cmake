include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(imgui SYSTEM
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.8
    GIT_SHALLOW ON
    GIT_PROGRESS ON
)