# About
Easy to use and efficient trainer menu base for Grand Theft Auto V. 
![image](https://user-images.githubusercontent.com/36642285/103153771-316e2a00-4793-11eb-8450-5c98af361ad6.png)

# Building a Project
For build project You have to install [CMake Binaries](https://cmake.org/download/) to Your system. 
Create a Folder and Open terminal in that, then use this commands: 
```
git clone https://github.com/Xxsource98/SourceBase.git
cd SourceBase
mkdir build
cd build
cmake ..
```
Or You can even use CMake GUI version for easier create project.

After above steps, you are able to open project with a base. You can build an asi file via cmake by commands:
```
cd build
cmake -DCMAKE_BUILD_TYPE=Release .  (You can change Release to a Debug)
```

# How to Use
The "main" file is `script.cpp` where you are calling all drawing functions. There are few possible to draw options: 
```
BlankOption - Empty Option
ToggleOption - Toggling Boolean Variable Option 
SliderOption - Slider Option, supporting: float, int
VectorOption - Vector Option for drawing multiple strings on slide, supporting: std::vector<std::string>
SubmenuOption - Option for change current Submenu
```
You have to call `registerSubmenu` function from `Menu` class. It is registering your submenu and you can put all options there for registered submenu.
But that's not all, You have to first make a pointer and draw loop for a base class. The arguments of constructor are: `std::string menuName, MENU_STRUCT menuStruct`, where `menuName` is a displaying menu name and `menuStruct` is a struct, which has menu binds and menu colors. <br/>
In the `MainLoop` void function, you have to create a pointer (I recommend to use a smart pointer, I used shared_ptr, because You can create multiple menus in one project). You have to make here a `while` loop and call a `draw` function from the `Menu` class. Don't forget to add a `WAIT(0)` after every while in a project, it's important for a ScriptHookV. <br/><br/>
<b>All examples are in `script.cpp` file.</b> <br/>
<b>For load .asi mods you have to download a [ScriptHookV](http://www.dev-c.com/gtav/scripthookv/)</b>



# Features
```
- Responsive and Modern UI
- Easy to Use
- Efficient code
- Support for Controller
- Support for Create a couple Menus in One Project
```

# License
Project is under GNU General Public License v3.0. You can read more there: [www.gnu.org](https://www.gnu.org/licenses/gpl-3.0.html)
