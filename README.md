# ExampleVR

This is an example MinVR project which can be used for a base for other projects.

### Build and Install

Set environment variables (i.e. execute in .bashrc)
  ```
  export MinVR_DIR=/path/to/install/MinVR
  ```

Build the project:
  ```
  make
  # build release
  make opt
  # build debug
  make debug
  ```

Install the project:
  ```
  make install
  ```

Run the program:
  ```
  ./build/Release/example desktop
  ```

