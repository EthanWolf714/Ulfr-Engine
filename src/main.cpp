#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdint>
#include <vector>
#include <cstring>

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 800
#define screenHeight 450

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int worldMap[mapHeight][mapWidth] =
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};


double posX = 22, posY = 12;
double dirX = -1, dirY = 0;
double planeX = 0, planeY = 0.66;
//speed modifiers
double moveSpeed;//the constant value is in squares/second
double rotSpeed; //the constant value is in radians/second


int main()
{
    InitWindow(screenWidth, screenHeight, "Ulfr Engine (raycaster)");
    TraceLog(LOG_INFO, "Window created");


    TraceLog(LOG_INFO, "Starting raycaster...");
    std::vector<int> texture[8];
    for(int i = 0; i < 8; i++)texture[i].resize(texWidth * texHeight);

    //create blank img on cpu and generate a blank image at screen resolution
    Image img = GenImageColor(screenWidth, screenHeight, BLACK);
    //uplaod image to the GPU as a texture
    Texture2D screen = LoadTextureFromImage(img);
    //create cpu side pixel buffer using raylib Color
    //malloc allocated a flay array of Colors, once per pixel
    Color* pixels = (Color*)malloc(screenWidth * screenHeight * sizeof(Color));
    if(pixels == NULL) {
        CloseWindow();
        return -1;
    }
    //unload image from CPU memory since we don't need it anymore.
    UnloadImage(img);
    TraceLog(LOG_INFO, "Buffer created");

    // Initialization
    
    

   
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    
    //generate textures
    for(int x = 0; x < texWidth; x++)
    for(int y = 0; y < texHeight; y++)
    {
        int xorcolor = (x * 256 / texWidth) ^ (y + 256 / texHeight);
        //int xcolor = x * 256 / texHeight
        int ycolor = y * 256 / texHeight;
        int xycolor = y * 128 / texHeight + x * 128 / texWidth;
        texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
        texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
        texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
        texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
        texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
        texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
        texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
        texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
    }
    TraceLog(LOG_INFO, "Textures generated");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        moveSpeed = GetFrameTime() * 5.0;
        rotSpeed = GetFrameTime() * 3.0;
        
        // Update
        //move forware if no wall in front of you
        if(IsKeyDown(KEY_W)){
            if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == 0) posX += dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
            
        }
        //movebackward if no wall behind you
        if(IsKeyDown(KEY_S)){
             if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == 0) posX -= dirX * moveSpeed;
            if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == 0) posY -= dirY * moveSpeed;
        }

        //rotate to the right
        if(IsKeyDown(KEY_D)){
            //both camera and direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
            dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
            planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);

        }

        if(IsKeyDown(KEY_A)){
            //both camera and direction and camera plane must be rotated
            double oldDirX = dirX;
            dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
            dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
            double oldPlaneX = planeX;
            planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
            planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);

        }

        

        // Draw
       
        BeginDrawing();
            ClearBackground(BLACK); 
            for(int x = 0; x < screenWidth; x++){
                //calculate ray position and direction
                double cameraX = 2 * x / double(screenWidth) - 1; //x-coordinate in camera space
                double rayDirX = dirX + planeX * cameraX;
                double rayDirY = dirY + planeY * cameraX;

                //which box of the map we're in
                int mapX = int(posX);
                int mapY = int(posY);

                //length of ray from current postiions to next x or y-side
                double sideDistX;
                double sideDistY;

                //length of ray from one x or y-side to the next
                double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1/rayDirX);
                double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1/rayDirY);
                double perpWallDist;

                //what direction to step in x or y direction (+1 or -1)
                int stepX;
                int stepY;

                int hit = 0; //was there a wall hit?
                int side; //was a NS or a EW wall hit?

                //calculate step and initial sideDist
                if(rayDirX < 0){
                    stepX = -1;
                    sideDistX = (posX - mapX) * deltaDistX;
                }
                else{
                    stepX = 1;
                    sideDistX = (mapX + 1.0 - posX) * deltaDistX;
                }

                if(rayDirY < 0){
                    stepY = -1;
                    sideDistY = (posY - mapY) * deltaDistY;

                }
                else{
                    stepY = 1;
                    sideDistY = (mapY + 1.0 - posY) * deltaDistY;
                }

                //start DDA
                while(hit == 0){
                    if(sideDistX < sideDistY){
                        sideDistX += deltaDistX;
                        mapX += stepX;
                        side = 0;
                    }
                    else{ 
                        sideDistY += deltaDistY;
                        mapY += stepY;
                        side = 1;
                    }

                    //check for ray hit
                    if(worldMap[mapX][mapY] > 0) hit = 1;
                }

                //calculate dist projected on camera direction (Euclidean distance would give the fish eye effect)
                if(side == 0) perpWallDist = (sideDistX - deltaDistX);
                else          perpWallDist = (sideDistY - deltaDistY);

                
                //calculate height of line to draw on screen
                int lineHeight = (int)(screenHeight / perpWallDist);

                //calculate lowest and highest pixel to fille in current stripe
                int drawStart = -lineHeight / 2 + screenHeight / 2;
                if(drawStart < 0) drawStart = 0;
                int drawEnd = lineHeight / 2 + screenHeight / 2;
                if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

                //texturing calculations
                int textNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so texture 0 can be used

                //value of wallX
                double wallX;
                if(side == 0) wallX = posY + perpWallDist * rayDirY;
                else          wallX = posX + perpWallDist * rayDirX;
                wallX -= floor((wallX));
               
                //x coordinate on texture
                int texX = int(wallX * double(texWidth));
                if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
                if(side == 1 && rayDirX < 0) texX = texWidth - texX - 1;
                
                // how much to increase texture coordiate per screen pixel
                double step = 1.0 * texHeight / lineHeight;
                //start textureing coordinate
                double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
                for(int y = drawStart; y < drawEnd; y++)
                {
                    //cast texture coordinate to integer and mask with texHeight-1 in case of overflow
                    int texY = (int)texPos & (texHeight - 1);
                    texPos += step;
                    uint32_t color = texture[textNum][texHeight * texY + texX];
                    //make color darker for y sides: RGB bytes each divided through two with "shift" and an "and"
                    if(side == 1) color = (color >> 1) & 8355711;

                    //unpack uint32 color into sepearte r,g,b bytes
                    //shift bits to extract each channle
                    uint8_t r = (color >> 16) & 0xFF; //shift 16 bits right to get red
                    uint8_t g = (color >> 8) & 0xFF; //shift 8 bits left to get green
                    uint8_t b = color & 0xFF; // no shift for blue
                    //write as raylib color to the pixel buffer
                    // y * screenWidth + x converts 2D coordinates to flat array index
                    pixels[y * screenWidth + x] = (Color){r,g,b,255};
                }



                
            }

        
            
            //update textures each frame;    
            UpdateTexture(screen, pixels);
            DrawTexture(screen, 0,0, WHITE);
            

            DrawText(TextFormat("FPS: %02i", GetFPS()), 0, 0, 20, BLUE);

        EndDrawing();
        //CLEAR PIXEL BUFFER EACH FRAME
        memset(pixels, 0, screenWidth * screenHeight * sizeof(Color));
        
    }
    // De-Initialization
   
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
