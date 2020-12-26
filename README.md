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

# License
Project is under GNU General Public License v3.0. You can read more there: [www.gnu.org](https://www.gnu.org/licenses/gpl-3.0.html)
