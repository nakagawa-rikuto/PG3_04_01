#include <Novice.h>

const char kWindowTitle[] = "LE2B_18_ナカガワ_リクト";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//画像の変数
	float screnPosX = 0.0f;
	float screnOnePosY = 0.0f;
	float screnTwoPosY = -720.0f;
	float screnSpeed = 5.0f;


	//状態管理の変数
	enum Scene {
		START,
		MIDDLE,
		END,
	};

	Scene scene;
	scene = START;

	//背景画像の読み込み
	int backGroundOne = Novice::LoadTexture("./Resource/BackScreen.png");

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (scene) {
		case 0:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = MIDDLE;
			}
			break;
		case 1:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = END;
			}
			break;
		case 2:
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				scene = START;
			}
			//画像の移動
			screnOnePosY = screnOnePosY + screnSpeed;
			screnTwoPosY = screnTwoPosY + screnSpeed;
			if (screnOnePosY >= 720.0f) {
				screnOnePosY = 0.0f;
				screnTwoPosY = -720.0f;
			}
			break;
		default:
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		switch (scene)
		{
		case 0:
			//フラグの値
			Novice::ScreenPrintf(10, 300, "scene:%d", scene);
			Novice::ScreenPrintf(10, 320, "Push Space to change scene");
			break;
		case 1:
			Novice::ScreenPrintf(10, 300, "scene:%d", scene);
			Novice::ScreenPrintf(10, 320, "Push Space to change scene");
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, RED, kFillModeSolid);
			break;
		case 2:
			Novice::ScreenPrintf(10, 300, "scene:%d", scene);
			Novice::ScreenPrintf(10, 320, "Push Space to change scene");
			Novice::DrawSprite(int(screnPosX), int(screnOnePosY), backGroundOne, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(int(screnPosX), int(screnTwoPosY), backGroundOne, 1, 1, 0.0f, WHITE);
			break;
		default:
			break;
		}

		//画像の描画

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
