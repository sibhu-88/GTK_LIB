# GTK3 Project Template
This is a template for creating GTK3 projects in C. It includes a basic structure with source files, header files, and a Makefile.

## Directory Structure
- `src`: Contains the source code files.  
- `include`: Contains the header files.  
- `resources`: Contains CSS and icon files.  
- `build`: Contains the compiled binaries.  

## GTK3 Installation
Before building the project, make sure GTK3 development packages are installed on your system.

### Ubuntu:
```bash
sudo apt update
sudo apt install libgtk-3-dev
````
###To verify the installation:
```bash
pkg-config --cflags gtk+-3.0
```

## Build Instructions
To build the project, navigate to the project directory and run:
```bash
make
```

## Run Instructions
To run the project, use:
```bash
make run
```

## Clean Instructions
To clean the project, use:
```bash
make clean
```
