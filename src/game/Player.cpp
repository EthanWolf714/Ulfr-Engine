#include "game/player.h"

void Player::Init()
{
    m_playerCam.fovy = 60.0f;
    m_playerCam.projection = CAMERA_PERSPECTIVE;
    m_playerCam.position = (Vector3){
        player.position.x,
        player.position.y + (BOTTOM_HEIGHT + headLerp),
        player.position.z,
    };

    player.position = {0, 0, 0};
    player.velocity = {0, 0, 0};
    player.dir = {0, 0, 0};
    player.isGrounded = true;

    sensitivity = {0.001f, 0.001f};
    lookRotation = {0, 0};
    headTimer = 0.0f;
    headLerp = STAND_HEIGHT;
    walkLerp = 0.0f;
    lean = {0, 0};
}

void Player::Update()
{
    Vector2 mouseDelta = GetMouseDelta();
        lookRotation.x -= mouseDelta.x*sensitivity.x;
        lookRotation.y += mouseDelta.y*sensitivity.y;

        char sideway = (IsKeyDown(KEY_D) - IsKeyDown(KEY_A));
        char forward = (IsKeyDown(KEY_W) - IsKeyDown(KEY_S));
        bool crouching = IsKeyDown(KEY_LEFT_CONTROL);
        UpdateBody(lookRotation.x, sideway, forward, IsKeyPressed(KEY_SPACE), crouching);

        float delta = GetFrameTime();
        headLerp = Lerp(headLerp, (crouching ? CROUCH_HEIGHT : STAND_HEIGHT), 20.0f*delta);
        m_playerCam.position = (Vector3){
            player.position.x,
            player.position.y + (BOTTOM_HEIGHT + headLerp),
            player.position.z,
        };

        if (player.isGrounded && ((forward != 0) || (sideway != 0)))
        {
            headTimer += delta*3.0f;
            walkLerp = Lerp(walkLerp, 1.0f, 10.0f*delta);
            m_playerCam.fovy = Lerp(m_playerCam.fovy, 55.0f, 5.0f*delta);
        }
        else
        {
            walkLerp = Lerp(walkLerp, 0.0f, 10.0f*delta);
            m_playerCam.fovy = Lerp(m_playerCam.fovy, 60.0f, 5.0f*delta);
        }

        lean.x = Lerp(lean.x, sideway*0.02f, 10.0f*delta);
        lean.y = Lerp(lean.y, forward*0.015f, 10.0f*delta);
}

void Player::UpdateBody(float rot, char side, char forward, bool jumpPressed, bool crouchHold)
{
    Vector2 input = {(float)side, (float)-forward};

    #if defined(NORMALIZE_INPUT)
        if((side != 0) && (forward != 0)) input = Vector2Normalize(input);
    #endif

    float delta = GetFrameTime();

    if(!player.isGrounded) player.velocity.y -= GRAVITY*delta;

    if(player.isGrounded && jumpPressed)
    {
        player.velocity.y = JUMP_FORCE;
        player.isGrounded = false;
    } 

    Vector3 front = (Vector3){sinf(rot), 0.f, cosf(rot)};
    Vector3 right = (Vector3){cosf(-rot), 0.f, sinf(-rot)};

    Vector3 desiredDir = (Vector3){input.x*right.x + input.y*front.x, 0.0f, input.x*right.z + input.y*front.z, };
    player.dir = Vector3Lerp(player.dir, desiredDir, CONTROL*delta);

    float decel = (player.isGrounded ? FRICTION : AIR_DRAG);
    Vector3 hvel = (Vector3){player.velocity.x*decel, 0.0f, player.velocity.z*decel};

    float hvelLength = Vector3Length(hvel);
    if(hvelLength < (MAX_SPEED*0.01f)) hvel = (Vector3){0};

    float speed = Vector3DotProduct(hvel, player.dir);

    float maxSpeed = (crouchHold ? CROUCH_SPEED : MAX_SPEED);

    float accel = Clamp(maxSpeed - speed, 0.f, MAX_ACCEL * delta);

    hvel.x += player.dir.x*accel;
    hvel.z += player.dir.z*accel;

    player.velocity.x = hvel.x;
    player.velocity.z = hvel.z;

    
    player.position.x += player.velocity.x*delta;
    player.position.y += player.velocity.y*delta;
    player.position.z += player.velocity.z*delta;

    if(player.position.y <= 0.0f)
    {
        player.position.y = 0.0f;
        player.velocity.y = 0.0f;
        player.isGrounded = true;
    }

}

void Player::UpdateCamera()
{
    Camera& camera = m_playerCam;
    const Vector3 up = (Vector3) {0.0f,1.0f, 0.0f};
    const Vector3 targetOffset = (Vector3) {0.0f,0.0f,-1.0f};

    //left right
    Vector3 yaw = Vector3RotateByAxisAngle(targetOffset, up, lookRotation.x);

    //clamp up view
    float maxAngleUp = Vector3Angle(up, yaw);
    maxAngleUp -= 0.001f;
    if(-(lookRotation.y) > maxAngleUp) {lookRotation.y = -maxAngleUp;}

    float maxAngleDown = Vector3Angle(Vector3Negate(up), yaw);
    maxAngleDown *= -1.0f;
    maxAngleDown += 0.001f;
    if(-(lookRotation.y) < maxAngleDown) {lookRotation.y = -maxAngleDown;}

    Vector3 right = Vector3Normalize(Vector3CrossProduct(yaw, up));

    float pitchAngle = -lookRotation.y -lean.y;
    pitchAngle = Clamp(pitchAngle, -PI/2 + 0.0001f, PI/2 - 0.0001f);
    Vector3 pitch = Vector3RotateByAxisAngle(yaw, right, pitchAngle);

    float headSin = sinf(headTimer*PI);
    float headCos = cosf(headTimer*PI);
    const float stepRotation = 0.01f;
    camera.up = Vector3RotateByAxisAngle(up, pitch, headSin*stepRotation + lean.x);

     // Camera BOB
    const float bobSide = 0.1f;
    const float bobUp = 0.15f;
    Vector3 bobbing = Vector3Scale(right, headSin*bobSide);
    bobbing.y = fabsf(headCos*bobUp);

    camera.position = {
        player.position.x,
        player.position.y + (BOTTOM_HEIGHT + headLerp),
        player.position.z   
    };
    camera.target = Vector3Add(camera.position, pitch);

}

Camera& Player::GetPlayerCamera()
{
    return m_playerCam;
}