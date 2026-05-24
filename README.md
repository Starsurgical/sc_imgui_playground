# sc_imgui_playground
Viability testing repo

## Libraries
- SDL3
- Dear ImGUI (TTF files and UI)
- SDL3_image (only PCX needed)
- SDL3_mixer (only WAV and OGG needed)
- libSmacker (SMK files, video only)
- ?? (DDS, WEBM files from remaster?)

### Notes
ImGUI has TTF support built in, so SDL_ttf is not needed.

## Building
`git submodule update --init` (do NOT use --recursive)

