/*******************************************************************************************
*
*   raylib example - Conway's game of life!
*   Game has two states: edit and run.
*   In the edit state, the game is paused and we can click to toggle cells alive or dead
*   In the run state, the simulation moves forward one iteration per 30 frames
*
********************************************************************************************/

#include "raylib.h"
#include <stdio.h>

typedef enum GameState { EDIT = 0, RUN = 1} GameState;


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int boxSize = 20;
    const int nH = screenHeight / boxSize;
    const int nW = screenWidth / boxSize;
    GameState currentState = EDIT;
    int state = 0;

    InitWindow(screenWidth, screenHeight, "raylib test - game of life");
    int gridArray[nH][nW];
    int newArray[nH][nW];
    Vector2 location;

    int i, j;
    for (i=0;i<nH;i++){
      for (j=0;j<nW;j++){
        printf("%d, %d\n", i, j);
        gridArray[i][j] = 0;
        newArray[i][j] = 0;
      }
    }

    int frameCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        if (state == 0)
        {
          if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            location = GetMousePosition();
            int x = location.x;
            int y = location.y;
            j = x / boxSize;
            i = y / boxSize;
            if (gridArray[i][j] == 0){
              gridArray[i][j] = 1;
            } else {
              gridArray[i][j] = 0;
            }
          }
          if (IsKeyPressed(KEY_ENTER)) {
            currentState = RUN;
            state = 1;
            printf("toggle! state: %d \n", state);
          }
        }
        else if (state == 1)
        {
          frameCounter++;
          if (IsKeyPressed(KEY_ENTER)) {
            frameCounter = 0;
            currentState = EDIT;
            state = 0;
            printf("toggle! state: %d \n", state);
          }
          if (frameCounter == 30){

            for (i=0;i<nH;i++){
              for (j=0;j<nW;j++){
                // Count adjacent cells
                int adj = 0;
                if (i > 0) { adj += gridArray[i-1][j];}
                if (j > 0) { adj += gridArray[i][j-1];}
                if (i < (nH-1)) { adj += gridArray[i+1][j];}
                if (j < (nW-1)) { adj += gridArray[i][j+1];}
                if (i > 0 && j > 0) { adj += gridArray[i-1][j-1];}
                if (i > 0 && j < nW-1) {adj += gridArray[i-1][j+1];}
                if (i < (nH -1) && j > 0) {adj += gridArray[i+1][j-1];}
                if (i < (nH -1) && j < (nW -1)) {adj += gridArray[i+1][j+1];}
                // Set new state
                if (gridArray[i][j] == 1){
                  if (adj == 2 || adj == 3){
                    newArray[i][j] = 1;
                  }
                  else{
                    newArray[i][j] = 0 ;
                  }
                }
                else if (gridArray[i][j] == 0){
                  if (adj == 3){
                    newArray[i][j] = 1;
                  }
                  else{
                    newArray[i][j] = 0;
                  }
                }
              }
            }
          }
          else if (frameCounter == 31){
            //Replace content of gridArray with newArray
            i = 0;
            j = 0;
            printf("%d, %d\n", nH, nW);
            for (i=0;i<nH;i++){
              for (j=0;j<nW;j++){
                //printf("%d, %d\n", i, j);
                gridArray[i][j] = newArray[i][j];
              }
            }

            printf("tick: %d, state: %d\n", frameCounter, state);
            frameCounter = 0;
          }

        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            if (currentState == EDIT){
              DrawText("Click to toggle cell states!", 190, 200, 20, LIGHTGRAY);
            }
            DrawText("Press Enter to start/stop", 190, 400, 20, LIGHTGRAY);
            for (i=0;i<nH;i++){
              for (j=0;j<nW;j++){
                if (gridArray[i][j] == 1) {
                  DrawRectangle(j*boxSize, i*boxSize, boxSize-1, boxSize-1, DARKBLUE);
                }
              }
            }


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
