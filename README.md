# MilkTea-Engine

MilkTea Engine is a simple, beginner-friendly 2D game engine designed for ease of use and flexibility. Inspired by the comforting and familiar aspects of tea, MilkTea Engine aims to provide a cozy and intuitive environment for game developers.

## Features
- Easy-to-use interface for asset management and scene building.
- Basic 2D rendering capabilities.
- Integration with Dear ImGui for UI elements.
- Support for simple sprite and sound assets.

## Getting Started
(Instructions on how to install, set up, and start using MilkTea Engine, coming soon!)

## Project Roadmap and Checklist

### Completed Tasks
- [x] **Initial Project Setup**: Set up the basic project structure and dependencies.
- [x] **Game Engine Foundation**: Laid down the basic framework for the game engine.
- [x] **GUI Refactoring**: Extracted the GUI into its own `GuiLoader` class for better modularity and organization.
- [x] **UUID Generator**: Built a primitive UUID generator to uniquely identify asset instances following the Factory Pattern.
- [x] ~~**GUI->AssetManager Callback**: Implemented a callback mechanism for the GuiLoader to invoke asset importing via AssetManager.~~
- [x] **Implementing Eventbus**: Building a simple Eventbus system (ChaiBus) to replace callbacks.
- [x] **Added WinAPI to the project**: Added OpenFileDialog method to handle asset import via AssetManager.
- [x] **Added Boost Filesystem**: Added the Boost Filesystem to the Engine.

### Ongoing Tasks
- [ ] **Documentation**: Regularly update documentation and inline comments for clarity and maintainability.
- [ ] **Testing and Debugging**: Continuously test new features and fix bugs.
- [ ] **Refining the eventbus / event system**: Expanding the functions of the eventbus

### Short-Term Goals
- [ ] **Asset Manager Implementation**:
  - [x] Develop a basic version of the `AssetManager` class.
  - [x] Implement asset-importing functionality for one asset type (e.g., images).
  - [ ] Create a simple UI for asset importation and display.

- [ ] **Asynchronous Asset Loading**:
  - [ ] Research and decide on an approach for asynchronous operations.
  - [ ] Implement asynchronous loading for the initial asset type.

- [ ] **Basic Editor Features**:
  - [ ] Implement a basic level editor.
  - [ ] Develop simple object placement and manipulation capabilities.

### Mid-Term Goals
- [ ] **Expand Asset Manager**:
  - [ ] Add support for additional asset types (audio, text, etc.).
  - [ ] Implement advanced features like search, filter, and metadata editing.

- [ ] **Enhanced Editor Functionality**:
  - [ ] Integrate the asset manager with the level editor.
  - [ ] Add more complex object manipulation features (scaling, rotation, etc.).

- [ ] **Scripting Integration**:
  - [ ] Evaluate and integrate a scripting language for game logic (e.g., Lua, Python).

### Long-Term Goals
- [ ] **Full Game Engine Capabilities**:
  - [ ] Implement a complete set of game engine features (physics, audio, AI, etc.).
  - [ ] Optimize engine performance and memory usage.

- [ ] **User-Friendly Editor**:
  - [ ] Develop an intuitive and feature-rich game editor.
  - [ ] Implement user customization options and themes.

- [ ] **Community and Feedback**:
  - [ ] Open the project for community contributions.
  - [ ] Regularly gather user feedback and iterate on it.

### Future Expansion
- [ ] **Mobile Platform Support**: Explore and implement compatibility with mobile platforms.
- [ ] **Networking Capabilities**: Add multiplayer or networking features to the engine.
- [ ] **Asset Store Integration**: Create or integrate with an asset store for additional resources.

## Contributing
Contributions to MilkTea Engine are welcome! Please read the contributing guidelines first.

## License
MilkTea Engine is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments
- SFML for rendering.
- Dear ImGui for UI components.
