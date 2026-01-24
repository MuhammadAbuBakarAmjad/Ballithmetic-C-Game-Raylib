#include<raylib.h>                                          
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define numberOfTriangles 35
#define numberOfPlatforms 33
#define numberOfRectangles 30

char questionGenerator(int[3], int);
int answerCheck(int);
int CheckCollisionCircleTriangle(Vector2 center, int radius, Vector2 v1, Vector2 v2, Vector2 v3);
int CheckCollisionCircleLineCustom(Vector2 center, float radius, Vector2 start, Vector2 end);
int timeInSecs();

typedef struct {
	Vector2 v1;
	Vector2 v2;
	Vector2 v3;
}triangle;

typedef struct {
	int x;
	int y;
	int width;
	int height;
}platform;

typedef struct {
	int x;
	int y;
	int width;
	int height;
}rectangle;

int main() {

	srand(time(NULL));
	
	int windowWidth = 1600;
	int windowHeight = 900;
	int gameDifficulty = 1;
	
	InitWindow(windowWidth, windowHeight, "Ballithmetic");

	InitAudioDevice();

	start:

	Image Back = LoadImage("assets/images/background.png");
	Texture2D Back2 = LoadTextureFromImage(Back);
	UnloadImage(Back);
	int x1 = 0, x2 = 1600;

	Texture ball = LoadTexture("assets/images/ballTexture.png");

	float rotation = 1.0;
	float ballX = windowWidth / 2.0f;
	float ballY = windowHeight / 2.0f;
	int ballSize = 38;
	int ballX_Vel = 0;
	int ballY_Vel = 2;
	int gravity = 1;
	Camera2D camera = { 0 };
	camera.target = (Vector2){ ballX, ballY };
	camera.offset = (Vector2){ windowWidth / 2.0f, windowHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	int QnA[3] = { 2,2,4 };
	char oper = '+';
	int rangeOfAnswers = 9;
	bool pause = false;
	int collisionCheck = 0;
	int speed;
	int time = 1;
	int score = 0;
	int collisionWin = 0;
	int platformCheck;
	int game_over = 0;

	Sound jump = LoadSound("assets/sounds/jump2.mp3");
	Sound mainMenu = LoadSound("assets/sounds/mainMenu.mp3");
	Sound gameOver = LoadSound("assets/sounds/gameOver.mp3");

	PlaySound(mainMenu);

	SetTargetFPS(60);

	triangle t1 = { { windowWidth * 1.2f,windowHeight * 0.85f },
			{ windowWidth * 1.16f,windowHeight * 1.0f },
			{ windowWidth * 1.24f,windowHeight * 1.0f } };

	triangle t2 = { { windowWidth * 2.3f, windowHeight * 0.7f},
		{windowWidth * 2.26f, windowHeight * 1.0f},
		{windowWidth * 2.34f,windowHeight * 1.0f } };

	triangle t3 = { { windowWidth * 11.5f, windowHeight * 0.75f},
		{windowWidth * 11.45f, windowHeight * 1.0f},
		{windowWidth * 11.55f,windowHeight * 1.0f } };

	triangle t4 = { { windowWidth * 12.478f, windowHeight * 0.6f},
	{windowWidth * 12.45f, windowHeight * 1.0f},
	{windowWidth * 12.51f,windowHeight * 1.0f } };

	triangle t5 = { { windowWidth * 13.1f,windowHeight * 0.85f },
			{ windowWidth * 13.06f,windowHeight * 1.0f },
			{ windowWidth * 13.14f,windowHeight * 1.0f } };

	triangle t6 = { { windowWidth * 15.4f,windowHeight * 0.72f },
			{ windowWidth * 15.35f,windowHeight * 0.82f },
			{ windowWidth * 15.45f,windowHeight * 0.82f } };

	triangle t7 = { { windowWidth * 16.0f, windowHeight * 0.7f},
		{windowWidth * 15.95f, windowHeight * 1.0f},
		{windowWidth * 16.05f,windowHeight * 1.0f } };

	triangle t8 = { { windowWidth * 18.4f ,windowHeight * 0.85f },
			{ windowWidth * 18.36f ,windowHeight * 1.0f },
			{ windowWidth * 18.44f ,windowHeight * 1.0f } };

	triangle t9 = { { windowWidth * 18.48f ,windowHeight * 0.85f },
			{ windowWidth * 18.44f ,windowHeight * 1.0f },
			{ windowWidth * 18.52f ,windowHeight * 1.0f } };

	triangle t10 = { { windowWidth * 18.56f ,windowHeight * 0.85f },
			{ windowWidth * 18.52f ,windowHeight * 1.0f },
			{ windowWidth * 18.60f ,windowHeight * 1.0f } };
`
	triangle t11 = { { windowWidth * 18.64f ,windowHeight * 0.85f },
			{ windowWidth * 18.60f ,windowHeight * 1.0f },
			{ windowWidth * 18.68f ,windowHeight * 1.0f } };

	triangle t12 = { { windowWidth * 22.0f ,windowHeight * 0.85f },
			{ windowWidth * 22.1f ,windowHeight * 0.0f },
			{ windowWidth * 21.9f ,windowHeight * 0.0f } };

	triangle t13 = { { windowWidth * 22.12f, windowHeight * 0.78f},
		{windowWidth * 22.07f, windowHeight * 1.0f},
		{windowWidth * 22.17f,windowHeight * 1.0f } };

	triangle t14 = { { windowWidth * (11.5f+12.8f), windowHeight * 0.75f},
		{windowWidth * (11.45f+12.8f), windowHeight * 1.0f},
		{windowWidth * (11.55f+12.8f),windowHeight * 1.0f } };

	triangle t15 = { { windowWidth * (12.478f+12.8f), windowHeight * 0.6f},
	{windowWidth * (12.45f+12.8f), windowHeight * 1.0f},
	{windowWidth * (12.51f+12.8f),windowHeight * 1.0f } };

	triangle t16 = { { windowWidth * (13.1f+12.8f),windowHeight * 0.85f },
			{ windowWidth * (13.06f+12.8f),windowHeight * 1.0f },
			{ windowWidth * (13.14f+12.8f),windowHeight * 1.0f } };

	triangle t17 = { { windowWidth * (15.4f+12.8f),windowHeight * 0.72f },
			{ windowWidth * (15.35f+12.8f),windowHeight * 0.82f },
			{ windowWidth * (15.45f+12.8f),windowHeight * 0.82f } };

	triangle t18 = { { windowWidth * (16.0f+12.8f), windowHeight * 0.7f},
		{windowWidth * (15.95f+12.8f), windowHeight * 1.0f},
		{windowWidth * (16.05f+12.8f),windowHeight * 1.0f } };

	triangle t19 = { { windowWidth * (18.4f +12.8f),windowHeight * 0.85f },
			{ windowWidth * (18.36f+12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.44f+12.8f) ,windowHeight * 1.0f } };

	triangle t20 = { { windowWidth * (18.48f+12.8f) ,windowHeight * 0.85f },
			{ windowWidth * (18.44f+12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.52f+12.8f) ,windowHeight * 1.0f } };

	triangle t21 = { { windowWidth * (18.56f+12.8f) ,windowHeight * 0.85f },
			{ windowWidth * (18.52f+12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.60f+12.8f) ,windowHeight * 1.0f } };

	triangle t22 = { { windowWidth * (18.64f+12.8f) ,windowHeight * 0.85f },
			{ windowWidth * (18.60f+12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.68f+12.8f) ,windowHeight * 1.0f } };

	triangle t23 = { { windowWidth * (22.0f +12.8f),windowHeight * 0.85f },
			{ windowWidth * (22.1f +12.8f),windowHeight * 0.0f },
			{ windowWidth * (21.9f +12.8f),windowHeight * 0.0f } };

	triangle t24 = { { windowWidth * (22.12f+12.8f), windowHeight * 0.78f},
		{windowWidth * (22.07f+12.8f), windowHeight * 1.0f},
		{windowWidth * (22.17f+12.8f),windowHeight * 1.0f } };

	triangle t25 = { { windowWidth * (11.5f + 2*12.8f), windowHeight * 0.75f},
		{windowWidth * (11.45f + 2*12.8f), windowHeight * 1.0f},
		{windowWidth * (11.55f + 2*12.8f),windowHeight * 1.0f } };

	triangle t26 = { { windowWidth * (12.478f + 2*12.8f), windowHeight * 0.6f},
	{windowWidth * (12.45f + 2*12.8f), windowHeight * 1.0f},
	{windowWidth * (12.51f + 2*12.8f),windowHeight * 1.0f } };

	triangle t27 = { { windowWidth * (13.1f + 2*12.8f),windowHeight * 0.85f },
			{ windowWidth * (13.06f + 2*12.8f),windowHeight * 1.0f },
			{ windowWidth * (13.14f + 2*12.8f),windowHeight * 1.0f } };

	triangle t28 = { { windowWidth * (15.4f + 2*12.8f),windowHeight * 0.72f },
			{ windowWidth * (15.35f + 2*12.8f),windowHeight * 0.82f },
			{ windowWidth * (15.45f + 2*12.8f),windowHeight * 0.82f } };

	triangle t29 = { { windowWidth * (16.0f + 2*12.8f), windowHeight * 0.7f},
		{windowWidth * (15.95f + 2*12.8f), windowHeight * 1.0f},
		{windowWidth * (16.05f + 2*12.8f),windowHeight * 1.0f } };

	triangle t30 = { { windowWidth * (18.4f + 2*12.8f),windowHeight * 0.85f },
			{ windowWidth * (18.36f + 2*12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.44f + 2*12.8f) ,windowHeight * 1.0f } };

	triangle t31 = { { windowWidth * (18.48f + 2*12.8f) ,windowHeight * 0.85f },
			{ windowWidth * (18.44f + 2*12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.52f + 2*12.8f) ,windowHeight * 1.0f } };

	triangle t32 = { { windowWidth * (18.56f + 2*12.8f) ,windowHeight * 0.85f },
			{ windowWidth * (18.52f + 2*12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.60f + 2*12.8f) ,windowHeight * 1.0f } };

	triangle t33 = { { windowWidth * (18.64f + 2*12.8f) ,windowHeight * 0.85f },
			{ windowWidth * (18.60f + 2*12.8f) ,windowHeight * 1.0f },
			{ windowWidth * (18.68f + 2*12.8f) ,windowHeight * 1.0f } };

	triangle t34 = { { windowWidth * (22.0f + 2*12.8f),windowHeight * 0.85f },
			{ windowWidth * (22.1f + 2*12.8f),windowHeight * 0.0f },
			{ windowWidth * (21.9f + 2*12.8f),windowHeight * 0.0f } };

	triangle t35 = { { windowWidth * (22.12f + 2*12.8f), windowHeight * 0.78f},
		{windowWidth * (22.07f + 2*12.8f), windowHeight * 1.0f},
		{windowWidth * (22.17f + 2*12.8f),windowHeight * 1.0f } };

	triangle Tobstacles[numberOfTriangles] = {t1,t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25, t26, t27, t28, t29, t30, t31, t32, t33, t34, t35};

	platform p1 = { windowWidth * 3.80f, windowHeight * 0.65f, 340, 15};
	platform p2 = { windowWidth * 5.7f, windowHeight * 0.65f, 340, 15 };
	platform p3 = { windowWidth * 6.05f, windowHeight * 0.44f, 340, 15 };
	platform p4 = { windowWidth * 10.2f, windowHeight * 0.65f, 650, 15 };
	platform p5 = { windowWidth * 10.8f, windowHeight * 0.44f, 600, 15 };
	platform p6 = { windowWidth * 14.3f, windowHeight * 0.61f, 1000, 15 };
	platform p7 = { windowWidth * 15.0f, windowHeight * 0.40f, 800, 15 };
	platform p8 = { windowWidth * 15.0f, windowHeight * 0.82f, 800, 15 };
	platform p9 = { windowWidth * 16.8f, windowHeight * 0.65f, 800, 15 };
	platform p10 = { windowWidth * 18.1f, windowHeight * 0.65f, 570, 15 };
	platform p11 = { windowWidth * 18.6f, windowHeight * 0.42f, 1300, 15 };
	platform p12 = { windowWidth * 19.58f, windowHeight * 0.42f, 372, 15 };
	platform p13 = { windowWidth * 20.9f, windowHeight * 0.62f, 1200, 15 };
	platform p14 = { windowWidth * (10.2f+12.8f), windowHeight * 0.65f, 650, 15 };
	platform p15 = { windowWidth * (10.8f+12.8f), windowHeight * 0.44f, 600, 15 };
	platform p16 = { windowWidth * (14.3f+12.8f), windowHeight * 0.61f, 1000, 15 };
	platform p17 = { windowWidth * (15.0f+12.8f), windowHeight * 0.40f, 800, 15 };
	platform p18 = { windowWidth * (15.0f+12.8f), windowHeight * 0.82f, 800, 15 };
	platform p19 = { windowWidth * (16.8f+12.8f), windowHeight * 0.65f, 800, 15 };
	platform p20 = { windowWidth * (18.1f+12.8f), windowHeight * 0.65f, 570, 15 };
	platform p21 = { windowWidth * (18.6f+12.8f), windowHeight * 0.42f, 1300, 15 };
	platform p22 = { windowWidth * (19.58f+12.8f), windowHeight * 0.42f, 372, 15 };
	platform p23 = { windowWidth * (20.9f+12.8f), windowHeight * 0.62f, 1200, 15 };
	platform p24 = { windowWidth * (10.2f + 2*12.8f), windowHeight * 0.65f, 650, 15 };
	platform p25 = { windowWidth * (10.8f + 2*12.8f), windowHeight * 0.44f, 600, 15 };
	platform p26 = { windowWidth * (14.3f + 2*12.8f), windowHeight * 0.61f, 1000, 15 };
	platform p27 = { windowWidth * (15.0f + 2*12.8f), windowHeight * 0.40f, 800, 15 };
	platform p28 = { windowWidth * (15.0f + 2*12.8f), windowHeight * 0.82f, 800, 15 };
	platform p29 = { windowWidth * (16.8f + 2*12.8f), windowHeight * 0.65f, 800, 15 };
	platform p30 = { windowWidth * (18.1f + 2*12.8f), windowHeight * 0.65f, 570, 15 };
	platform p31 = { windowWidth * (18.6f + 2*12.8f), windowHeight * 0.42f, 1300, 15 };
	platform p32 = { windowWidth * (19.58f + 2*12.8f), windowHeight * 0.42f, 372, 15 };
	platform p33 = { windowWidth * (20.9f + 2*12.8f), windowHeight * 0.62f, 1200, 15 };

	platform platforms[numberOfPlatforms] = { p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, p21, p22, p23, p24, p25, p26, p27, p28, p29, p30, p31, p32, p33 };

	rectangle r1 = { windowWidth * 3.9702f, windowHeight * 0.7f, 70, 300 };
	rectangle r2 = { windowWidth * 6.22f, windowHeight * 0.49f, 70, 500 };
	rectangle r3 = { windowWidth * 8.4f, windowHeight * 0.66f, 15, 500 };
	rectangle r4= { windowWidth * 11.15f, windowHeight * 0, 100, 800 };
	rectangle r5 = { windowWidth * 12.45f, windowHeight * 0, 80, 400 };
	rectangle r6 = { windowWidth * 13.6f, windowHeight * 0.7f, 70, 300 };
	rectangle r7 = { windowWidth * 15.4f, windowHeight * 0, 80, 362 };
	rectangle r8 = { windowWidth * 17.4f, windowHeight * 0.535f, 70, 700 };
	rectangle r9 = { windowWidth * 19.76f, windowHeight * 0, 80, 378 };
	rectangle r10 = { windowWidth * 20.0f, windowHeight * 0.7f, 70, 300 };
	rectangle r11 = { windowWidth * 21.58f, windowHeight * 0.4f, 80, 197 };
	rectangle r12 = { windowWidth * 22.7f, windowHeight * 0.7f, 70, 300 };
	rectangle r13 = { windowWidth * (11.15f+12.8f), windowHeight * 0, 100, 800 };
	rectangle r14 = { windowWidth * (12.45f+12.8f), windowHeight * 0, 80, 400 };
	rectangle r15 = { windowWidth * (13.6f+12.8f), windowHeight * 0.7f, 70, 300 };
	rectangle r16 = { windowWidth * (15.4f+12.8f), windowHeight * 0, 80, 362 };
	rectangle r17 = { windowWidth * (17.4f+12.8f), windowHeight * 0.535f, 70, 700 };
	rectangle r18 = { windowWidth * (19.76f+12.8f), windowHeight * 0, 80, 378 };
	rectangle r19 = { windowWidth * (20.0f+12.8f), windowHeight * 0.7f, 70, 300 };
	rectangle r20 = { windowWidth * (21.58f+12.8f), windowHeight * 0.4f, 80, 197 };
	rectangle r21 = { windowWidth * (22.7f+12.8f), windowHeight * 0.7f, 70, 300 };
	rectangle r22 = { windowWidth * (11.15f + 2*12.8f), windowHeight * 0, 100, 800 };
	rectangle r23 = { windowWidth * (12.45f + 2*12.8f), windowHeight * 0, 80, 400 };
	rectangle r24 = { windowWidth * (13.6f + 2*12.8f), windowHeight * 0.7f, 70, 300 };
	rectangle r25 = { windowWidth * (15.4f + 2*12.8f), windowHeight * 0, 80, 362 };
	rectangle r26 = { windowWidth * (17.4f + 2*12.8f), windowHeight * 0.535f, 70, 700 };
	rectangle r27 = { windowWidth * (19.76f + 2*12.8f), windowHeight * 0, 80, 378 };
	rectangle r28 = { windowWidth * (20.0f + 2*12.8f), windowHeight * 0.7f, 70, 300 };
	rectangle r29 = { windowWidth * (21.58f + 2*12.8f), windowHeight * 0.4f, 80, 197 };
	rectangle r30 = { windowWidth * (22.7f + 2*12.8f), windowHeight * 0.7f, 70, 300 };

	Rectangle win = { windowWidth * 49.5f, windowHeight * 0.0f, 80, 1000 };

	rectangle rectangles[numberOfRectangles] = { r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30 };

	while(!WindowShouldClose()){

		if (ballX_Vel == 0) {
			switch (gameDifficulty) {         
			case 1: rangeOfAnswers = 5;
				speed = 7; break;
			case 2: rangeOfAnswers = 9; 
				speed = 8; break;
			case 3: rangeOfAnswers = 20; 
				speed = 9; break;
			}
		}
		
		if (ballX_Vel != 0) {
			if (timeInSecs()) {
				speed++;
			}
		}
		
		if (ballY + ballSize >= windowHeight) {
			ballY_Vel = 0;
			ballY = windowHeight - ballSize;
		}
		if (ballY - ballSize <= 10) {
			ballY = ballSize+10;
		}

		if (answerCheck(QnA[2])) {
			PlaySound(jump);
			ballY_Vel = -27; 
			score += 25;
			oper = questionGenerator(QnA, rangeOfAnswers);
		}

		BeginDrawing();
		ClearBackground(WHITE);

		if (ballX == windowWidth/2) {
			DrawTexture(Back2, x1, 0, WHITE);
		}

		if (ballX != windowWidth / 2) {
			DrawTexture(Back2, x1, 0, WHITE);
			DrawTexture(Back2, x2, 0, WHITE);
			if (ballX_Vel != 0) {
				x1 -= speed;
				x2 -= speed;
				if (x1 <= -1600)
					x1 = 1600;
				if (x2 <= -1600)
					x2 = 1600;
			}
		}
		
		BeginMode2D(camera);
		
		if (IsKeyPressed(KEY_ENTER)) {
			ballX_Vel = speed;
			StopSound(mainMenu);
		}

		if (IsKeyPressed(KEY_E)) {
			gameDifficulty = 1;
		}
		if (IsKeyPressed(KEY_M)) {
			gameDifficulty = 2;
		}
		if (IsKeyPressed(KEY_H)) {
			gameDifficulty = 3;
		}
		if (IsKeyPressed(KEY_P)) {
			pause = !pause;
		}

		if (ballX == windowWidth / 2) {
			DrawText("Answer Correctly to Jump", windowWidth*0.34f, windowHeight*0.35f, 40, RED);
			DrawText("Are You Ready?", windowWidth * 0.4f, windowHeight * 0.45f, 40, BLUE);
			DrawText("Press Enter", windowWidth * 0.43f, windowHeight * 0.55f, 40, BLACK);
			DrawText("Press E, M or H to toggle between game difficulty:", windowWidth * 0.57f, windowHeight * 0.10f, 20, BLACK);
		}
		if (gameDifficulty == 1 && ballX == windowWidth / 2) {
			DrawText("Easy", windowWidth * 0.915f, windowHeight * 0.10f, 20, GREEN);
		}
		if (gameDifficulty == 2 && ballX == windowWidth / 2) {
			DrawText("Medium", windowWidth * 0.91f, windowHeight * 0.10f, 20, YELLOW);
		}
		if (gameDifficulty == 3 && ballX == windowWidth / 2) {
			DrawText("Hard", windowWidth * 0.915f, windowHeight * 0.10f, 20, RED);
		}

		for (int i = 0; i < numberOfTriangles; i++) {
			DrawTriangle(Tobstacles[i].v1, Tobstacles[i].v2, Tobstacles[i].v3, BLUE);
		}
		for (int i = 0; i < numberOfPlatforms; i++) {
			DrawRectangle(platforms[i].x, platforms[i].y, platforms[i].width, platforms[i].height, BLACK);
		}
		for (int i = 0;i < numberOfRectangles;i++) {
			DrawRectangle(rectangles[i].x, rectangles[i].y, rectangles[i].width, rectangles[i].height, DARKGRAY);
		}
		DrawRectangleRec(win, GREEN);

		if (ballX_Vel != 0) {
			DrawText("Press 4 to JUMP!", windowWidth * 1.08f, windowHeight * 0.5f, 40, RED);
			DrawText("A Bigger JUMP!", windowWidth * 1.9f, windowHeight * 0.5f, 40, RED);
			DrawText("You can also Jump on the           Platforms", windowWidth * 2.79f, windowHeight * 0.5f, 30, RED);
			DrawText("BLACK", windowWidth * 3.0465f, windowHeight * 0.5f, 30, BLACK);
			DrawText("Get Ready for a double JUMP!", windowWidth * 4.8f, windowHeight * 0.5f, 40, RED);
			DrawText("Now try doing a Double Jump without Platforms", windowWidth * 7.05f, windowHeight * 0.5f, 30, BLACK);
			DrawText("Easy Right? Now you're on your own!", windowWidth * 9.2f, windowHeight * 0.5f, 30, RED);
		}

		Rectangle source = { 0.0f, 0.0f, (float)ball.width, (float)ball.height };
		Rectangle dest = {ballX-ballSize+40, ballY-ballSize+36.5f, ballSize*2+10, ballSize*2+12 };
		Vector2 origin = { dest.width / 2, dest.height / 2 };
		DrawTexturePro(ball, source, dest, origin, rotation, WHITE);

		EndMode2D();

		if (ballX_Vel != 0) {
			DrawText(TextFormat("Question: %d %c %d = ?", QnA[0], oper, QnA[1]), windowWidth*0.085f, windowHeight*0.22f, 50, DARKGRAY);
		}
		if (ballX != windowWidth / 2) {
			DrawText(TextFormat("Score: %d", score), windowWidth * 0.07f, windowHeight * 0.9f, 30, BLACK);
		}
		if (pause && ballX != windowWidth / 2) {
			ballX_Vel = 0;
			ballY_Vel = 0;
			DrawText("Paused", windowWidth * 0.45f, windowHeight * 0.40f, 40, BLACK);
		}
		if (pause) {
			oper = questionGenerator(QnA, rangeOfAnswers);
		}
		else if (!pause && ballX != windowWidth / 2 && !collisionCheck && !collisionWin) {
			ballX_Vel = speed;
		}

		ballY += ballY_Vel;
		ballY_Vel += gravity;
		ballX += ballX_Vel;
		camera.target.x = ballX;

		for (int i = 0;i < numberOfTriangles ;i++) {
			if (CheckCollisionCircleTriangle((Vector2){ ballX, ballY }, ballSize,
				Tobstacles[i].v1, Tobstacles[i].v2, Tobstacles[i].v3))
			{
				collisionCheck = 1;
			}
		}
		
		platformCheck = 0;
		for (int i = 0; i < numberOfPlatforms; i++) {
			Rectangle platform = { (float)platforms[i].x, (float)platforms[i].y, (float)platforms[i].width, (float)platforms[i].height };
			if (CheckCollisionCircleRec((Vector2){ ballX, ballY }, ballSize, platform)) {
				platformCheck = 1;
				if (ballY_Vel > 0) {
					ballY = platforms[i].y - ballSize;
					ballY_Vel = 0;
				}
				else if (ballY_Vel <= 0) {
					ballY = platforms[i].y + platforms[i].height + ballSize + 0.25f;
				}
			}
		}
		
		for (int i = 0; i < numberOfRectangles; i++) {
			Rectangle rec = { (float)rectangles[i].x, (float)rectangles[i].y, (float)rectangles[i].width, (float)rectangles[i].height };
			if (CheckCollisionCircleRec((Vector2){ ballX, ballY }, ballSize, rec)) {
				collisionCheck = 1;
			}
		}
		
		if (collisionCheck) {
			if (game_over == 0) {
				PlaySound(gameOver);
				game_over = 1;
			}
			ballX_Vel = 0;
			ballY_Vel = 0;
			DrawText("Game Over", windowWidth * 0.45f, windowHeight * 0.30f, 40, BLACK);
			DrawText("Press Enter to Restart", windowWidth * 0.39f, windowHeight * 0.42f, 30, RED);
			DrawText("OR", windowWidth * 0.5f, windowHeight * 0.47f, 30, GREEN);
			DrawText("Press R to Return to Main Menu", windowWidth * 0.35f, windowHeight * 0.52f, 30, BLUE);

			if (IsKeyPressed(KEY_R)) {
				UnloadTexture(Back2);
				UnloadTexture(ball);
				UnloadSound(jump);
				UnloadSound(mainMenu);
				UnloadSound(gameOver);
				goto start;
			}
			if (IsKeyPressed(KEY_ENTER)) {
				UnloadTexture(Back2);
				UnloadTexture(ball);
				UnloadSound(jump);
				UnloadSound(mainMenu);
				UnloadSound(gameOver);
				goto start;
			}
		}
		
		if (CheckCollisionCircleRec((Vector2){ ballX, ballY }, ballSize, win)) {
			collisionWin = 1;
		}
		
		if (collisionWin) {
			ballX_Vel = 0;
			ballY_Vel = 0;
			DrawText("You Win!", windowWidth * 0.45f, windowHeight * 0.30f, 40, RED);
			DrawText("Press Enter to Restart", windowWidth * 0.39f, windowHeight * 0.42f, 30, RED);
			DrawText("OR", windowWidth * 0.5f, windowHeight * 0.47f, 30, GREEN);
			DrawText("Press R to Return to Main Menu", windowWidth * 0.35f, windowHeight * 0.52f, 30, BLUE);

			if (IsKeyPressed(KEY_R)) {
				UnloadTexture(Back2);
				UnloadTexture(ball);
				UnloadSound(jump);
				UnloadSound(mainMenu);
				UnloadSound(gameOver);
				goto start;
			}
			if (IsKeyPressed(KEY_ENTER)) {
				UnloadTexture(Back2);
				UnloadTexture(ball);
				UnloadSound(jump);
				UnloadSound(mainMenu);
				UnloadSound(gameOver);
				goto start;
			}
		}
		
		if ((platformCheck && ballX_Vel != 0) || (ballX_Vel != 0 && ballY == windowHeight - ballSize)) {
			rotation += speed / 2.5f;
		}
		
		EndDrawing();
	}
	
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

char questionGenerator(int array[3], int rangeOfAnswers) {
	while (1) {
		array[0] = rand() % 20 + 1;
		array[1] = rand() % 20 + 1;
		switch (rand() % 3) {
		case 0: 
			array[2] = array[0] + array[1];
			if (array[2] <= rangeOfAnswers) {
				return '+';
			}
			break;
		case 1: 
			array[2] = array[0] - array[1];
			if ((array[2] <= rangeOfAnswers) && array[2] >= 0) {
				return '-';
			}
			break;
		case 2: 
			array[2] = array[0] * array[1];
			if (array[2] <= rangeOfAnswers) {
				return '*';
			}
			break;
		}
	}
}

int answerCheck(int num) {
	// Check two-digit numbers FIRST (10-20)
	// Both keys must be held down simultaneously
	if (num == 10 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_0)) return 1;
	if (num == 11 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_1)) return 1;
	if (num == 12 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_2)) return 1;
	if (num == 13 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_3)) return 1;
	if (num == 14 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_4)) return 1;
	if (num == 15 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_5)) return 1;
	if (num == 16 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_6)) return 1;
	if (num == 17 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_7)) return 1;
	if (num == 18 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_8)) return 1;
	if (num == 19 && IsKeyDown(KEY_KP_1) && IsKeyDown(KEY_KP_9)) return 1;
	if (num == 20 && IsKeyDown(KEY_KP_2) && IsKeyDown(KEY_KP_0)) return 1;
	
	// Check single-digit numbers AFTER (0-9)
	// Only match if ONLY that single key is down
	if (num == 0 && IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2)) return 1;
	if (num == 1 && IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 2 && IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 3 && IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 4 && IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 5 && IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 6 && IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 7 && IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 8 && IsKeyDown(KEY_KP_8) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_9)) return 1;
	if (num == 9 && IsKeyDown(KEY_KP_9) && !IsKeyDown(KEY_KP_0) && !IsKeyDown(KEY_KP_1) && !IsKeyDown(KEY_KP_2) && !IsKeyDown(KEY_KP_3) && !IsKeyDown(KEY_KP_4) && !IsKeyDown(KEY_KP_5) && !IsKeyDown(KEY_KP_6) && !IsKeyDown(KEY_KP_7) && !IsKeyDown(KEY_KP_8)) return 1;
	
	return 0;
}

int CheckCollisionCircleTriangle(Vector2 center, int radius, Vector2 v1, Vector2 v2, Vector2 v3)
{
	if (CheckCollisionCircleLineCustom(center, radius, v1, v2) ||
		CheckCollisionCircleLineCustom(center, radius, v2, v3) ||
		CheckCollisionCircleLineCustom(center, radius, v3, v1))
	{
		return 1;
	}
	return 0;
}

int CheckCollisionCircleLineCustom(Vector2 center, float radius, Vector2 start, Vector2 end){
	Vector2 difference;
	difference.x = end.x - start.x;
	difference.y = end.y - start.y;

	float length = sqrt(difference.x * difference.x + difference.y * difference.y);

	Vector2 direction;
	direction.x = difference.x / length;
	direction.y = difference.y / length;

	Vector2 startToCenter;
	startToCenter.x = center.x - start.x;
	startToCenter.y = center.y - start.y;

	float projection = startToCenter.x * direction.x + startToCenter.y * direction.y;

	Vector2 closestPoint;

	if (projection < 0)
	{
		closestPoint = start;
	}
	else if (projection > length)
	{
		closestPoint = end;
	}
	else
	{
		closestPoint.x = start.x + direction.x * projection;
		closestPoint.y = start.y + direction.y * projection;
	}

	return CheckCollisionPointCircle(closestPoint, center, radius);
}

int timeInSecs() {
	int sec = 0;
	static int frames = 0;
	frames++;
	if (frames == 1800) {
		sec = 1;
		frames = 0;
	}
	return sec;
}