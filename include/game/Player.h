#include "raylib.h"
#include "raymath.h"
#include "Camera.h"

#define GRAVITY 32.0f
#define MAX_SPEED 20.0f
#define CROUCH_SPEED 5.0f
#define MAX_ACCEL 150.0f

#define FRICTION 0.86

#define AIR_DRAG 0.98

#define CONTROL 15.0f
#define CROUCH_HEIGHT 0.0f
#define STAND_HEIHGT 1.0f
#define BOTTOM_HEIGHT 0.5f

#define NORMALIZE_INPUT 0

typedef struct {
    Vector3 position;
    Vector3 velocity;
    Vector3 dir;
    bool isGrounded;

}Body;

static Body player = {0};
static Vector2 lookRotation = {0};
static float headTimer = 0.0f;
static float headLerp = STAND_HEIHGT;
static Vector2 lean = {0};

class Player 
{
    public:
        
        void UpdateCamera(Camera *camera);
        void UpdateBody(Body *body, float rot, char side, char forward, bool jumpPressed, bool crouchHold);


    private:
        Camera m_playerCam;
};