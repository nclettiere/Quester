# Quester
Quest manager for UE4 based projects. Specially made for *Project: Moolight* Game.

### !!-> PRE-ALPHA: This program is currently on development and it lacks of many features. You will experience bugs/crashes and other weird things.

---

Preview of the quest graph editor
![Preview of the graph editor](https://github.com/Noriaki-Kakyoin/Quester/blob/master/readme_img.png)

---

## Features

- Add, Remove, Update Quests
- Modular Quest Tweaking (add custom values/parameters)
- Dialogue Manager (individual dialogues and inside quests)
- Graph editor for quest/dialogues
- Modern C++
- Export/Import Graph Flows
- Use common JSON, CSV files (compatible with UE4 datatable)
- TODO: UE4 quest plugin --> will deal with it later boi too much work to do     . . .

## Dependencies

1. [Qt5](https://www.qt.io/)
2. [CMake](https://cmake.org/)
3. [nodeeditor](https://github.com/paceholder/nodeeditor) -> used for Quest/Dialogue graphs
4. [Poco](https://pocoproject.org/) -> used for SQLite libraries

!!-> The Poco library must be compiled, build and installed using CMake system-wide. [Check here for more info](https://pocoproject.org/download.html)

Run this code to download the nodeeditor dependecy and others `git submodule update --init --recursive`


## Special Thanks
To [paceholder](https://github.com/paceholder) for his Node Editor. It was the inspiration for this project man.<br />
To [Daguerreo](https://github.com/Daguerreo) for his amazing fork on the Node Editor! couldn't continue without this lol<br />
To [The Poco C++ Libraries](https://pocoproject.org/) Great library for network stuff! Also includes alot of useful libraries (similar to boost)<br />
<br />
To [The Qt Project](https://www.qt.io/)