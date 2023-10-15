# OpenGL Program for Collision Detection

## System Specifications
* *OS* - Arch Linux
* *Library* - `freeglut`
  * *Dependency* - `OpenGL`

## Prerequisites
To run openGL programs in the system, the following things need to be installed:
- `mesa` video driver for integrated graphics.
- `nvidia` or `amd` for respective external cards.
- For installation instructions on installing graphics drivers, openCL, GPGPU etc., refer to this [Video Tutorial](https://www.youtube.com/watch?v=gIVIHJmW1P0)

## How to Run
- **Prerequisites:** `run.sh` file needs to have the executable access. Run *(if not ran already)*: `sudo chmod +x run.sh` from the same directory. **(First Time ONLY)**
- In the terminal: `./run` and then choose between `Assisted` and `Advanced`. 
  - `Assisted Mode` compiles and runs the program with default file setup and `CLI Args`. It also spits out a file named `output`.
  - `Advanced Mode` lets the user choose all the files to compile, use additional `CLI Args` and choose a custom output file name.
