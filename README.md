
---

# Digital Music Manager

This project implements a Digital Music Manager using a dynamic doubly linked list in C (C11). It meets the requirements for PA2/PA3 and includes features such as load, store, display, edit, rate, play, insert, delete, sort, and shuffle, along with test functions.

## Project Files

- **main.c** – Contains the main menu and overall control flow.
- **musicManager.h / musicManager.c** – Implements the core functionality for managing music records and the doubly linked list.
- **testFunctions.h / testFunctions.c** – Contains test cases for the insert, delete, and shuffle features.
- **musicPlayList.csv** – A sample CSV file containing music records.
- **CMakeLists.txt** – CMake configuration file for building the project.
- **Makefile** – Optional Makefile for building the project on Unix-like systems (macOS/Linux).

## Compiling the Code

### Using CMake (Cross-platform)

1. **Open a terminal** and navigate to the project directory.
2. **Create a build directory**:
   ```bash
   mkdir build && cd build
   ```
3. **Generate build files**:
   ```bash
   cmake ..
   ```
4. **Build the project**:
   ```bash
   cmake --build .
   ```
5. **Run the executable**:
    - On macOS/Linux:
      ```bash
      ./Hernandez_Dominguez_PA3
      ```
    - On Windows:
      ```bash
      Hernandez_Dominguez_PA3.exe
      ```

### Using the Makefile (macOS/Linux)

1. **Open a terminal** and navigate to the project directory.
2. **Build the project** by running:
   ```bash
   make
   ```
3. **Run the executable**:
   ```bash
   ./Hernandez_Dominguez_PA3
   ```
4. **Clean the build** (if needed):
   ```bash
   make clean
   ```

### Using Visual Studio (Windows)

If you prefer to use Visual Studio:

1. Open Visual Studio and select **File > Open > CMake...**.
2. Choose the `CMakeLists.txt` file from the project directory.
3. Visual Studio will generate the build configuration automatically.
4. Build and run the project directly from Visual Studio.

## Running the Application

Once the project is built, launch the executable. The main menu will display options for:
- Loading and storing the playlist,
- Displaying, editing, rating, and playing records,
- Inserting, deleting, sorting, and shuffling the playlist,
- Running test functions (option 11).

**Note:** Ensure that `musicPlayList.csv` is located in the same directory as the executable so the program can access it.

## Additional Notes

- The project is set to compile using the C11 standard.
- The cross-platform code for pausing and clearing the screen is handled using `Sleep`/`system("cls")` on Windows and `sleep`/`system("clear")` on macOS/Linux.
- The test functions are integrated into the main menu (option 11) for convenience.

---

Thanks for reviewing my project, Jaehong!