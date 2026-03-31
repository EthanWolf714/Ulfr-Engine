#include "raylib.h"
#include "raymath.h"
#include "engine/Camera.h"

#define GRAVITY 32.0f
#define MAX_SPEED 20.0f
#define CROUCH_SPEED 5.0f
#define JUMP_FORCE  12.0f
#define MAX_ACCEL 150.0f

#define FRICTION 0.86

#define AIR_DRAG 0.98

#define CONTROL 15.0f
#define CROUCH_HEIGHT 0.0f
#define STAND_HEIGHT 1.0f
#define BOTTOM_HEIGHT 0.5f

#define NORMALIZE_INPUT 0





class Player 
{
    

    public:
        
        void UpdateCamera();
        void Update();
        void Init();
        Camera& GetPlayerCamera();

    private:
        typedef struct {
            Vector3 position;
            Vector3 velocity;
            Vector3 dir;
            bool isGrounded;

        }Body;

        Body player;
        Camera m_playerCam;
        Vector2 lookRotation;
        float headTimer;
        float headLerp;
        float walkLerp;
        Vector2 lean;
        Vector2 sensitivity;
        
        void UpdateBody(float rot, char side, char forward, bool jumpPressed, bool crouchHold);

};



