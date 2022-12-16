// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//








#ifndef __ANIMATEDTEXTURE_H
#define __ANIMATEDTEXTURE_H
#include "Texture.h"
#include "Timer.h"
namespace SDLFramework {
    class AnimatedTexture :
        public Texture {
    };
}
#endif

[Tuesday 8:22 AM] Dennis Hubley
public:
    enum WrapMode { Once = 0, Loop = 1 };
    enum AnimDir { Horizontal = 0, Vertical = 1 };

    [Tuesday 8:24 AM] Dennis Hubley
private:
    Timer* mTimer;
    int mStartX;
    int mStartY;

    [Tuesday 8:26 AM] Dennis Hubley
        int mFrameCount; // total frames
    float mAnimationSpeed; // in seconds
    float mTimePerFrame; // time to display
    float mAnimationTimer; // time displayed

    [Tuesday 8:27 AM] Dennis Hubley
        WrapMode mWrapMode;
    AnimDir mAnimationDirection;
    bool mAnimationDone;
    laugh 1

        [Tuesday 8:27 AM] Dennis Hubley
public:
    AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, AnimDir animationDir, bool managed = false);
    ~AnimatedTexture();

    [Tuesday 8:29 AM] Dennis Hubley
        void SetWrapMode(WrapMode mode);
    void ResetAnimation();
    bool IsAnimating();
    void Update();

    [Tuesday 8:30 AM] Dennis Hubley
        #include "AnimatedTexture.h"
        namespace SDLFramework {
        AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, AnimDir animationDir, bool managed)
            : Texture(filename, x, y, w, h, managed) {
        }
    }

    [Tuesday 8:31 AM] Dennis Hubley
        mTimer = Timer::Instance();
    mStartX = x;
    mStartY = y;

    [Tuesday 8:32 AM] Dennis Hubley
        mFrameCount = frameCount;
    mAnimationSpeed = animationSpeed;
    mTimePerFrame = mAnimationSpeed / mFrameCount;
    mAnimationTimer = 0.0f;

    [Tuesday 8:33 AM] Dennis Hubley
        mWrapMode = Loop;
    mAnimationDirection = animationDir;
    mAnimationDone = false;

    [Tuesday 8:33 AM] Dennis Hubley
        AnimatedTexture::~AnimatedTexture() { }
    void AnimatedTexture::SetWrapMode(WrapMode wrapMode) {
        mWrapMode = wrapMode;
    }



[Tuesday 9:07 AM] Dennis Hubley
#include <SDL_ttf.h>

[Tuesday 9:08 AM] Dennis Hubley
SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);


[Tuesday 9:11 AM] Dennis Hubley
SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        std::cerr << "CreateTextTexture:: TTF_RenderText_Solid Error: " << TTF_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (tex == nullptr) {
        std::cerr << "CreateTextTexture:: SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return tex;
}

[Tuesday 9:14 AM] Dennis Hubley
if (TTF_Init() == -1) {
    std::cerr << "Unable to initialized SDL_ttf! TTF Error: " << TTF_GetError() << std::endl;
    return false;
}



[Tuesday 9:16 AM] Dennis Hubley
std::map<std::string, TTF_Font*> mFonts;
std::map<std::string, SDL_Texture*> mText;

[Tuesday 9:17 AM] Dennis Hubley
TTF_Font* GetFont(std::string filename, int size);

[Tuesday 9:18 AM] Dennis Hubley
SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);

[Tuesday 9:19 AM] Dennis Hubley
#include <sstream>

[Tuesday 9:21 AM] Dennis Hubley
TTF_Font* AssetManager::GetFont(std::string filename, int size) {
    std::string fullPath = SDL_GetBasePath();
    fullPath.append("Assets/" + filename);
}

[Tuesday 9:22 AM] Dennis Hubley
std::stringstream ss;
ss << size;
std::string key = fullPath + ss.str();

[Tuesday 9:24 AM] Dennis Hubley
if (mFonts[key] == nullptr) {
    mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
    if (mFonts[key] == nullptr) {
        std::cerr << "Unable to load font " << filename << "! TTF Error: " << TTF_GetError() << std::endl;
    }
}
return mFonts[key];

[Tuesday 9:25 AM] Dennis Hubley
SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed) {
    std::stringstream ss;
    ss << size << (int)color.r << (int)color.g << (int)color.b;
    std::string key = text + filename + ss.str();
    if (mText[key] == nullptr) {
        TTF_Font* font = GetFont(filename, size);
        mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
    }
    if (mText[key] != nullptr && managed) {
        mTextureRefCount[mText[key]] += 1;
    }
    return mText[key];
}

[Tuesday 9:30 AM] Dennis Hubley
for (auto elem : mText) {
    if (elem.second == texture) {
        SDL_DestroyTexture(elem.second);
        mText.erase(elem.first);
        return; // work finished, leave function
    }
}

[Tuesday 9:31 AM] Dennis Hubley
Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = false);



[Tuesday 9:35 AM] Dennis Hubley
Texture* mFontTex;

[Tuesday 9:36 AM] Dennis Hubley
mFontTex = new Texture("Hello World!", "ARCADE.TTF", 72, { 255, 0, 0 });
mFontTex->Position(Vector2(400, 200));

[Tuesday 9:37 AM] Dennis Hubley
delete mFontTex;
mFontTex = nullptr;



[Tuesday 9:59 AM] Dennis Hubley
#include <SDL_Mixer.h>

[Tuesday 10:00 AM] Dennis Hubley
std::map<std::string, Mix_Music*> mMusic;
std::map<std::string, Mix_Chunk*> mSFX;

std::map<Mix_Music*, unsigned> mMusicRefCount;
std::map<Mix_Chunk*, unsigned*> mSFXRefCount;

[Tuesday 10:08 AM] Dennis Hubley


#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.h"
#include <SDL_Mixer.h>
#include <map>
#include <sstream>
namespace SDLFramework {
    class AssetManager {
    private:
        static AssetManager* sInstance;
        std::map<std::string, SDL_Texture*> mTextures;
        std::map<std::string, TTF_Font*> mFonts;
        std::map<std::string, SDL_Texture*> mText;
        std::map<std::string, Mix_Music*> mMusic;
        std::map<std::string, Mix_Chunk*> mSFX;
        std::map<SDL_Texture*, unsigned> mTextureRefCount;
        std::map<Mix_Music*, unsigned> mMusicRefCount;
        std::map<Mix_Chunk*, unsigned*> mSFXRefCount;
    private:
        TTF_Font* GetFont(std::string filename, int size);
        AssetManager();
        ~AssetManager();
    public:
        static AssetManager* Instance();
        static void Release();
        SDL_Texture* GetTexture(std::string filename, bool managed = false);
        SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);
        Mix_Music* GetMusic(std::string filename, bool managed = false);
        Mix_Chunk* GetSFX(std::string filename, bool managed = false);
        void DestroyTexture(SDL_Texture* texture);
        void DestroyMusic(Mix_Music* music);
        void DestroySFX(Mix_Chuck* sfx);
    };
}
#endif

#ifndef __ASSETMANAGER_H
#define __ASSETMANAGER_H
#include "Graphics.h"
#include <SDL_Mixer.h>
#include <map>
#include <sstream>
namespace SDLFramework {
    class AssetManager {
    private:
        static AssetManager* sInstance;
        std::map<std::string, SDL_Texture*> mTextures;
        std::map<std::string, TTF_Font*> mFonts;
        std::map<std::string, SDL_Texture*> mText;
        std::map<std::string, Mix_Music*> mMusic;
        std::map<std::string, Mix_Chunk*> mSFX;
        std::map<SDL_Texture*, unsigned> mTextureRefCount;
        std::map<Mix_Music*, unsigned> mMusicRefCount;
        std::map<Mix_Chunk*, unsigned*> mSFXRefCount;
    private:
        TTF_Font* GetFont(std::string filename, int size);
        AssetManager();
        ~AssetManager();
    public:
        static AssetManager* Instance();
        static void Release();
        SDL_Texture* GetTexture(std::string filename, bool managed = false);
        SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color, bool managed = false);
        Mix_Music* GetMusic(std::string filename, bool managed = false);
        Mix_Chunk* GetSFX(std::string filename, bool managed = false);
        void DestroyTexture(SDL_Texture* texture);
        void DestroyMusic(Mix_Music* music);
        void DestroySFX(Mix_Chuck* sfx);
    };
}
#endif
class B;
class A
{
    int _val;
    B* _b;
public:

    A(int val)
        :_val(val)
    {
    }

    void SetB(B* b)
    {
        _b = b;
        _b->Print(); // COMPILER ERROR: C2027: use of undefined type 'B'
    }

    void Print()
    {
        cout << "Type:A val=" << _val << endl;
    }
};
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

static const short SCREEN_WIDTH = 1024;
static const short SCREEN_HEIGHT = 896;
const char* WINDOW_TITLE = "Galaga";

mWindow = SDL_CreateWindow(
    WINDOW_TITLE,               // window title
    SDL_WINDOWPOS_UNDEFINED,    // window x pos
    SDL_WINDOWPOS_UNDEFINED,    // window y pos
    SCREEN_WIDTH,               // window width
    SCREEN_HEIGHT,              // window height
    SDL_WINDOW_SHOWN);          // window flags

#ifndef __STARTSCREEN_H
#define __STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"
using namespace SDLFramework;
class StartScreen : public GameEntity {
private:
    Timer* mTimer;
    InputManager* mInputManager;
};

// Top Bar Entities
GameEntitiy* mTopBar;
Texture* mPlayerOne;
Texture* mPlayerTwo;
Texture* mHiScore;

public:
    StartScreen();
    ~StartScreen();
    void Update() override;
    void Render() override;

        StartScreen::StartScreen() {
        mTimer = Timer::Instance();
        mInput = InputManager::Instance();
    }

#include "StartScreen.h"

        StartScreen::StartScreen() {
        mTimer = Timer::Instance();
        mInputManager = InputManager::Instance();

    }

        mTopBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, 80.0f);
    mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200, 0, 0 });
    mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200, 0, 0 });
    mHiScore = new Texture("HI SCORE", "emulogic.ttf", 32, { 200, 0, 0 });

        mTopBar->Parent(this);
    mPlayerOne->Parent(mTopBar);
    mPlayerTwo->Parent(mTopBar);
    mHiScore->Parent(mTopBar);

        mPlayerOne->Position(-Graphics::SCREEN_WIDTH * 0.35f, 0.0f);
    mPlayerTwo->Position(Graphics::SCREEN_WIDTH * 0.2f, 0.0f);
    mHiScore->Position(-30.0f, 0.0f);

        StartScreen::~StartScreen() {
        // top bar entities
        delete mTopBar;
        mTopBar = nullptr;
        delete mPlayerOne;
        mPlayerOne = nullptr;
        delete mPlayerTwo;
        mPlayerTwo = nullptr;
        delete mHiScore;
        mTimer = nullptr;
        mInput = nullptr;
        }

        void StartScreen::Update() {
        }
    void StartScreen::Render() {
        mPlayerOne->Render();
        mPlayerTwo->Render();
        mHiScore->Render();
    }

        #include "StartScreen.h"

        StartScreen * mStartScreen;

        mStartScreen = new StartScreen();

        delete mStartScreen;
    mStartScreen = nullptr;

        mStartScreen->Update();

        mStartScreen->Render();

            // Play Mode Entities
            GameEntity* mPlayModes;
        Texture* mOnePlayerMode;
        Texture* mTwoPlayerMode;
        Texture* mCursor;

            // play mode entities
            mPlayModes = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f);
        mOnePlayerMode = new Texture("1 Player ", "emulogic.ttf", 32, { 230, 230, 230 });
        mTwoPlayerMode = new Texture("2 Players", "emulogic.ttf", 32, { 230, 230, 230 });
        mCursor = new Texture("Cursor.png");

     
            mPlayModes->Parent(this);
        mOnePlayerMode->Parent(mPlayModes);
        mTwoPlayerMode->Parent(mPlayModes);
        mCursor->Parent(mPlayModes);
        mOnePlayerMode->Position(0.0f, -35.0f);
        mTwoPlayerMode->Position(0.0f, 35.0f);
        mCursor->Position(-175.0f, -35.0f);
        mOnePlayerMode->Render();
        mTwoPlayerMode->Render();
        mCursor->Render();

            // Bottom Bar Entities
            GameEntity* mBottomBar;
        Texture* mNamco;
        Texture* mDates;
        Texture* mRights;

            mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
        mNamco = new Texture("namcot", "namco__.ttf", 36, { 200, 0, 0 });
        mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
        mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

            mBottomBar->Parent(this);
        mNamco->Parent(mBottomBar);
        mDates->Parent(mBottomBar);
        mRights->Parent(mBottomBar);
        mNamco->Position(Vec2_Zero);
        mDates->Position(0.0f, 90.0f);
        mRights->Position(0.0f, 170.0f);

            // bottom bar entities
            delete mBottomBar;
        mBottomBar = nullptr;
        delete mNamco;
        mNamco = nullptr;
        delete mDates;
        mDates = nullptr;
        delete mRights;
        mRights = nullptr;

            mNamco->Render();
        mDates->Render();
        mRights->Render();


            // Bottom Bar Entities
            GameEntity* mBottomBar;
        Texture* mNamco;
        Texture* mDates;
        Texture* mRights;


            mBottomBar = new GameEntity(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f);
        mNamco = new Texture("namcot", "namco__.ttf", 36, { 200, 0, 0 });
        mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230, 230, 230 });
        mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230, 230, 230 });

        
            mBottomBar->Parent(this);
        mNamco->Parent(mBottomBar);
        mDates->Parent(mBottomBar);
        mRights->Parent(mBottomBar);
        mNamco->Position(Vec2_Zero);
        mDates->Position(0.0f, 90.0f);
        mRights->Position(0.0f, 170.0f);

       
            // bottom bar entities
            delete mBottomBar;
        mBottomBar = nullptr;
        delete mNamco;
        mNamco = nullptr;
        delete mDates;
        mDates = nullptr;
        delete mRights;
        mRights = nullptr;

       
            mNamco->Render();
        mDates->Render();
        mRights->Render();
            // Logo Entities
            Texture* mLogo;

            // logo entities
            mLogo = new Texture("GalagaLogo.png", 0, 0, 360, 180);

            mLogo->Parent(this);

            mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);

            // logo entities
            delete mLogo;
            mLogo = nullptr;
            mLogo->Render();

            // Screen Animation Variables
            Vector2 mAnimationStartPos;
            Vector2 mAnimationEndPos;
            float mAnimationTotalTime;
            float mAnimationTimer;
            bool mAnimationDone;

            // screen animation variables
            mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
            mAnimationEndPos = Vec2_Zero;
            mAnimationTotalTime = 5.0f;
            mAnimationTimer = 0.0f;
            mAnimationDone = false;

            Position(mAnimationStartPos);


            if (!mAnimationDone) {
                mAnimationTimer += mTimer->DeltaTime();

                if (mAnimationTimer >= mAnimationTotalTime) {
                    mAnimationDone = true;
                }
            }

            Position(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

          
                if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP)) {
                    mAnimationTimer = mAnimationTotalTime;
                }

                AnimatedTexture* mAnimatedLogo;

                [9:21 AM] Dennis Hubley
                    // logo entities
                    mLogo = new Texture("GalagaLogo.png", 0, 0, 360, 180);
                mAnimatedLogo = new AnimatedTexture("GalagaLogo.png", 0, 0, 360, 180, 3, 0.2f, AnimatedTexture::Vertical);
                mLogo->Parent(this);
                mAnimatedLogo->Parent(this);
                mLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);
                mAnimatedLogo->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.32f);

              
                    // logo entities
                    delete mLogo;
                mLogo = nullptr;
                delete mAnimatedLogo;
                mAnimatedLogo = nullptr;

                else {
                    mAnimatedLogo->Update();
                }

                if (!mAnimationDone) {
                    mLogo->Render();
                }
                else {
                    mAnimatedLogo->Render();
                }

         
                    Vector2 mCursorStartPos;
                Vector2 mCursorOffset;
                int mSelectedMode;

                    void ChangeSelectedMode(int change)
                    mCursorStartPos = mCursor->Position(Local);
                mCursorOffset = Vector2(0.0f, 70.0f);
                mSelectedMode = 0;

                void StartScreen::ChangeSelectedMode(int change) {
                    mSelectedMode += change;

                    if (mSelectedMode < 0) {
                        mSelectedMode = 1;
                    }
                    else if (mSelectedMode > 1) {
                        mSelectedMode = 0;
                    }

                    mCursor->Position(mCursorStartPos + mCursorOffset * (float)mSelectedMode);
                }

                if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
                    ChangeSelectedMode(1);
                }
                else if (mInput->KeyPressed(SDL_SCANCODE_UP)) {
                    ChangeSelectedMode(-1);
                }

                #ifndef __RANDOM_H
                #define __RANDOM_H
                #include <random>
                #include <chrono>

                namespace SDLFramework {

                    class Random {
                    private:
                        static Random* sInstance;

                    public:
                        static Random* Instance();
                        static void Release();

                    private:
                        Random();
                        ~Random();
                    };
                }

                
                    std::mt19937 mGenerator;

                
                    unsigned RandomInt(); // [0,unsigned max]
                float RandomFloat(); // [0.0,1.0)
                int RandomRange(int lo, int hi); // [lo,hi]
                float RandomRange(float lo, float hi); // [lo,hi)

                [9:39 AM] Dennis Hubley
                    #include "Random.h"
                    namespace SDLFramework {
                    Random* Random::sInstance = nullptr;
                    Random* Random::Instance() {
                        if (sInstance == nullptr) {
                            sInstance = new Random();
                        }
                        return sInstance;
                    }
                    void Random::Release() {
                        delete sInstance;
                        sInstance = nullptr;
                    }
                }

                Random::Random() {
                    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
                    mGenerator.seed(seed);
                }

                Random::~Random() {
                }
                unsigned Random::RandomInt() {
                    return mGenerator();
                }
                float Random::RandomFloat() {
                    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
                    return dist(mGenerator);
                }

                int SDLFramework::Random::RandomRange(int lo, int hi) {
                    std::uniform_int_distribution<int> dist(lo, hi);
                    return dist(mGenerator);
                }

                float SDLFramework::Random::RandomRange(float lo, float hi) {
                    std::uniform_real_distribution<float> dist(lo, hi);
                    return dist(mGenerator);
                }
                #ifndef __STAR_H;
                #define __STAR_H;
                #include "Texture.h";

                using namespace SDLFramework;

                class Star : public Texture {

                private:

                public:
                    Star(int layer);
                    ~Star();

                    void Update() override;
                    void Render() override;
                };
                
                #include "Timer.h";
                #include "Random.h";

                    static bool mScroll;
                Timer* mTimer;
                Random* mRand;
                bool mVisible;
                float mFlickerTimer;
                float mFlickerSpeed;
                float mScrollSpeed;

              static void Scroll(bool b);

              private:
              void ScrollStar();

#include "Star.h"

              bool Star::mScroll = false;

              void Star::Scroll(bool b) {
                  mScroll = b;
              }

              Star::Star(int layer)
                  : Texture("Stars.png", 0, 0, 4, 4) {
                  mTimer = Timer::Instance();
                  mRand = Random::Instance();
              }
            
                  int starColor = mRand->RandomInt() % 4;
              mSourceRect.x = starColor * 4;
              Position(Vector2((float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_WIDTH), (float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_HEIGHT)));

                  mFlickerTimer = 0.0f;
              mFlickerSpeed = mRand->RandomRange(0.15f, 1.0f);
              float inverseLayer = 1.0f / layer;
              Scale(Vec2_One* inverseLayer);
              mScrollSpeed = 4.0f / layer;

                  Star::~Star() {
                  mTimer = nullptr;
                  mRand = nullptr;
              }
                  void Star::ScrollStar() {
                      Translate(Vec2_Up * mScrollSpeed, World);

                      Vector2 pos = Position(Local);

                      if (pos.y > Graphics::Instance()->SCREEN_HEIGHT) {
                          pos.y = 0.0f;
                          pos.x = (float)(mRand->RandomInt() % Graphics::Instance()->SCREEN_WIDTH);
                          Position(pos);
                      }
                  }
                  void Star::Update() {
                      mFlickerTimer += mTimer->DeltaTime();

                      if (mFlickerTimer >= mFlickerSpeed) {
                          mVisible = !mVisible;
                          mFlickerTimer = 0.0f;
                      }

                      if (mScroll) {
                          ScrollStar();
                      }
                  }
                  void Star::Render() {
                      if (mVisible) {
                          Texture::Render();
                      }
                  }
#ifndef __STARLAYER_H
#define __STARLAYER_H
#include "Star.h"

                  class StarLayer {
                  private:
                      static const int STAR_COUNT = 30;
                      Star* mStars[STAR_COUNT];

                  public:
                      StarLayer(int layer);
                      ~StarLayer();

                      void Update();
                      void Render();
                  };

#endif

                  [11:14 AM] Dennis Hubley
                      #include "StarLayer.h"
                      StarLayer::StarLayer(int layer) {
                      for (int i = 0; i < STAR_COUNT; i++) {
                          mStars[i] = new Star(layer);
                      }
                  }
                  StarLayer::~StarLayer() {
                      for (int i = 0; i < STAR_COUNT; i++) {
                          delete mStars[i];
                          mStars[i] = nullptr;
                      }
                  }
                  void StarLayer::Update() {
                      for (auto star : mStars) {
                          star->Update();
                      }
                  }
                  void StarLayer::Render() {
                      for (auto star : mStars) {
                          star->Render();
                      }
                  }

                  [11:17 AM] Dennis Hubley
#ifndef __BACKGROUNDSTARS_H
#define __BACKGROUNDSTARS_H
                      #include "StarLayer.h"
                      class BackgroundStars {
                      private:
                          static BackgroundStars* sInstance;
                          static const int LAYER_COUNT = 3;
                          StarLayer* mLayers[LAYER_COUNT];
                      public:
                          static BackgroundStars* Instance();
                          static void Release();
                          void Scroll(bool b);
                          void Update();
                          void Render();
                      private:
                          BackgroundStars();
                          ~BackgroundStars();
                  };
#endif

                  BackgroundStars* mStars;

#include "BackgroundStars.h"

                  mStars = BackgroundStars::Instance();
                  BackgroundStars::Release();
                  mStars = nullptr;
                  mStars->Update();
                  mStars->Render();

#ifndef __SCOREBOARD_H
#define __SCOREBOARD_H
#include "Texture.h"
#include <vector>

                  using namespace SDLFramework;

                  class Scoreboard : public GameEntity {
                  private:
                      std::vector<Texture*> mScore;

                      SDL_Color mColor;

                  public:
                      Scoreboard();
                      Scoreboard(SDL_Color color);
                      ~Scoreboard();

                      void Score(int score);

                      void Render();

                  private:
                      void ClearBoard();
                  };
#endif
                  void Scoreboard::ClearBoard() {
                      for (unsigned i = 0; i < mScore.size(); i++) {
                          delete mScore[i];
                          mScore[i] = nullptr;
                      }

                      mScore.clear();
                  }

               #include "Scoreboard.h"
               
                  void Scoreboard::Score(int score) {
                      ClearBoard();

                      if (score == 0) {
                          for (int i = 0; i < 2; i++) {
                              mScore.push_back(new Texture("0", "emulogic.ttf", 32, mColor));
                              mScore[i]->Parent(this);
                              mScore[i]->Position(Vector2(-32.0f * i, 0.0f));
                          }
                      }
                  }

                  else {
                      std::string str = std::to_string(score);
                      unsigned lastIndex = (unsigned)str.length() - 1;

                      for (unsigned i = 0; i <= lastIndex; i++) {
                          mScore.push_back(new Texture(str.substr(i, 1), "emulogic.ttf", 32, mColor));
                          mScore[i]->Parent(this);
                          mScore[i]->Position(Vector2(-32.0f * (lastIndex - i), 0.0f));
                      }
    }


        Scoreboard::Scoreboard()
        : Scoreboard({ 230, 230, 230 }) {
    }
    Scoreboard::Scoreboard(SDL_Color color) {
        mColor = color;
        Score(0);
    }
    Scoreboard::~Scoreboard() {
        ClearBoard();
    }

        void Scoreboard::Render() {
        for (auto digit : mScore) {
            digit->Render();
        }
    }
            #include "Scoreboard.h"
            #include "Scoreboard.h"
                mPlayerOneScore = new Scoreboard();
            mPlayerTwoScore = new Scoreboard();
            mTopScore = new Scoreboard();
                mPlayerOneScore->Parent(mTopBar);
            mPlayerTwoScore->Parent(mTopBar);
            mTopScore->Parent(mTopBar);
            mPlayerOneScore->Position(-Graphics::SCREEN_WIDTH * 0.23f, 40.0f);
            mPlayerTwoScore->Position(Graphics::SCREEN_WIDTH * 0.32f, 40.0f);
            mTopScore->Position(Graphics::SCREEN_WIDTH * 0.05f, 40.0f);
            delete mPlayerOneScore;
            mPlayerOneScore = nullptr;
            delete mPlayerTwoScore;
            mPlayerTwoScore = nullptr;
            delete mTopScore;
            mTopScore = nullptr;
            mPlayerOneScore->Render();
            mPlayerTwoScore->Render();
            mTopScore->Render();
#ifndef __SCREENMANAGER_H
#define __SCREENMANAGER_H
#include "StartScreen.h"

            class ScreenManager {
            private:
                static ScreenManager* sInstance;

            public:
                static ScreenManager* Instance();
                static void Release();

            private:
                ScreenManager();
                ~ScreenManager();
            };
#endif
            enum Screens { Start, Play };
            Screens mCurrentScreen;
            InputManager* mInput;

            BackgroundStars* mBackgroundStars;
            StartScreen* mStartScreen;
#include "BackgroundStars.h"
            void Update();
            void Render();
#include "ScreenManager.h"

            ScreenManager* ScreenManager::sInstance = nullptr;

            ScreenManager* ScreenManager::Instance() {
                if (sInstance == nullptr) {
                    sInstance = new ScreenManager();
                }

                return sInstance;
            }

            void ScreenManager::Release() {
                delete sInstance;
                sInstance = nullptr;
            }
            ScreenManager::ScreenManager() {
                mInput = InputManager::Instance();

                mBackgroundStars = BackgroundStars::Instance();
                mStartScreen = new StartScreen();

                mCurrentScreen = Start;
            }

            ScreenManager::~ScreenManager() {
                mInput = nullptr;

                BackgroundStars::Release();
                mBackgroundStars = nullptr;

                delete mStartScreen;
                mStartScreen = nullptr;
            }
            [8:25 AM] Dennis Hubley
                void ScreenManager::Update() {
                mBackgroundStars->Update();
                switch (mCurrentScreen) {
                case Start:
                    mStartScreen->Update();
                    break;
                case Play:
                    break;
                }
            }
            void ScreenManager::Render() {
                mBackgroundStars->Render();
                switch (mCurrentScreen) {
                case Start:
                    mStartScreen->Render();
                    break;
                case Play:
                    break;
                }
            }

            void ScreenManager::Update() {
                mBackgroundStars->Update();

                switch (mCurrentScreen) {
                case Start:
                    mStartScreen->Update();

                    if (mInput->KeyPressed(SDL_SCANCODE_RETURN)) {
                        mCurrentScreen = Play;
                    }
                    break;
                case Play:
                    if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
                        mCurrentScreen = Start;
                    }
                    break;
                }
            }
#include "ScreenManager.h"
            ScreenManager* mScreenManager;
                mScreenManager->Update();
                mScreenManager->Render();
                mScreenManager = ScreenManager::Instance();
                ScreenManager::Release();
            mScreenManager = nullptr;
            [8:38 AM] Dennis Hubley
                void ResetAnimation();
            int SelectedMode();
                void StartScreen::ResetAnimation() {
                // screen animation variables
                mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
                mAnimationEndPos = Vec2_Zero;
                mAnimationTotalTime = 5.0f;
                mAnimationTimer = 0.0f;
                mAnimationDone = false;

                Position(mAnimationStartPos);
            }
                int StartScreen::SelectedMode() {
                    int StartScreen::SelectedMode() {
                    return mSelectedMode;
                }
#include "BackgroundStars.h"
                    BackgroundStars* mStars;
                    mStars = BackgroundStars::Instance();
                mStars->Scroll(true);
                    mCursorStartPos = mCursor->Position(Local);
                mCursorOffset = Vector2(0.0f, 70.0f);
                mSelectedMode = 0;
                    mStartScreen->ResetAnimation();
                    mSelectedMode = 0;
                    mCursor->Position(mCursorStartPos + mCursorOffset * (float)mSelectedMode);
                    mStars->Scroll(false);
#ifndef __PLAYSCREEN_H
#define __PLAYSCREEN_H
#include "AudioManager.h"
#include "BackgroundStars.h"

                    class PlayScreen : public GameEntity {
                    private:
                        Timer* mTimer;
                        AudioManager* mAudio;

                        BackgroundStars* mStars;

                    public:
                        PlayScreen();
                        ~PlayScreen();

                        void Update() override;
                        void Render() override;

                    };
#endif
                    PlayScreen::PlayScreen() {
                        mTimer = Timer::Instance();
                        mAudio = AudioManager::Instance();

                        mStars = BackgroundStars::Instance();
                    }

                    PlayScreen::~PlayScreen() {
                        mTimer = nullptr;
                        mAudio = nullptr;

                        mStars = nullptr;
                    }

                    void PlayScreen::Update() {
                    }

                    void PlayScreen::Render() {
                    }
                    PlayScreen* mPlayScreen;
                        mPlayScreen->Update();
                        mPlayScreen->Render();
                            mPlayScreen = new PlayScreen();
                            delete mPlayScreen;
                        mPlayScreen = nullptr;
                        // temporary background colour change
                        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
#ifndef __PLAYSIDEBAR_H
#define __PLAYSIDEBAR_H
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

                        class PlaySideBar : public GameEntity {
                        private:
                            Timer* mTimer;
                            AudioManager* mAudio;

                            Texture* mBackground;

                        public:
                            PlaySideBar();
                            ~PlaySideBar();

                            void Update() override;
                            void Render() override;
                        };
#endif
                        PlaySideBar::PlaySideBar() {
                            mTimer = Timer::Instance();
                            mAudio = AudioManager::Instance();

                            mBackground = new Texture("Black.png");
                            mBackground->Parent(this);
                        }

                        PlaySideBar::~PlaySideBar() {
                            mTimer = nullptr;
                            mAudio = nullptr;

                            delete mBackground;
                            mBackground = nullptr;
                        }
                        void PlaySideBar::Update() {
                        }

                        void PlaySideBar::Render() {
                            mBackground->Render();
                        }
#include "PlaySideBar.h"
PlaySideBar* mSideBar;
mSideBar = new PlaySideBar();
mSideBar->Parent(this);
mSideBar->Position(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f);
delete mSideBar;
void PlayScreen::Update() {
mSideBar->Update();
}

void PlayScreen::Render() {
mSideBar->Render();
}
                    
mBackground = new Texture("Black.png");
mBackground->Parent(this);
mBackground->Scale(Vector2(3.0f, 10.0f));
 mBackground->Position(45.0f, 380.0f);
 mSideBar->Position(Graphics::SCREEN_WIDTH * 0.87f, Graphics::SCREEN_HEIGHT * 0.05f);
 Texture* mHighLabel;
 Texture* mScoreLabel;
 Scoreboard* mHighScoreboard;
     mHighLabel = new Texture("HIGH", "emulogic.ttf", 32, { 150, 0, 0 });
 mHighLabel->Parent(this);
 mHighLabel->Position(-25.0f, 0.0f);
 mScoreLabel = new Texture("SCORE", "emulogic.ttf", 32, { 150, 0, 0 });
 mScoreLabel->Parent(this);
 mScoreLabel->Position(25.0f, 32.0f);
 mHighScoreboard = new Scoreboard();
 mHighScoreboard->Parent(this);
 mHighScoreboard->Position(90.0f, 64.0f);

     delete mHighLabel;
 mHighLabel = nullptr;
 delete mScoreLabel;
 mScoreLabel = nullptr;
 delete mHighScoreboard;
 mHighScoreboard = nullptr;
 mHighLabel->Render();
 mScoreLabel->Render();
 mHighScoreboard->Render();
 Texture* mPlayerOneLabel;
 float mBlinkTimer;
 float mBlinkInterval;
 bool mPlayerOneLabelVisible;
 Scoreboard* mPlayerOneScore;
 mPlayerOneLabel = new Texture("1UP", "emulogic.ttf", 32, { 150, 0, 0 });
 mPlayerOneLabel->Parent(this);
 mPlayerOneLabel->Position(-45.0f, 160.0f);

 mBlinkTimer = 0.0f;
 mBlinkInterval = 0.5f;
 mPlayerOneLabelVisible = true;

 mPlayerOneScore = new Scoreboard();
 mPlayerOneScore->Parent(this);
 mPlayerOneScore->Position(90.0f, 192.0f);
 delete mPlayerOneLabel;
 mPlayerOneLabel = nullptr;

 delete mPlayerOneScore;
 mPlayerOneScore = nullptr;
 mBlinkTimer += mTimer->DeltaTime();
 if (mBlinkTimer >= mBlinkInterval) {
     mPlayerOneLabelVisible = !mPlayerOneLabelVisible;
     mBlinkTimer = 0.0f;
 }

 if (mPlayerOneLabelVisible) {
     mPlayerOneLabel->Render();
 }
 mPlayerOneScore->Render();
 static const int MAX_SHIP_TEXTURES = 5;
 GameEntity* mShips;
 Texture* mShipTextures[MAX_SHIP_TEXTURES];
 Scoreboard* mTotalShipsLabel;
 int mTotalShips;
 mShips = new GameEntity();
 mShips->Parent(this);
 mShips->Position(-40.0f, 420.0f);

 for (int i = 0; i < MAX_SHIP_TEXTURES; ++i) {
     mShipTextures[i] = new Texture("PlayerShips.png", 0, 0, 60, 64);
     mShipTextures[i]->Parent(mShips);
     mShipTextures[i]->Position(62.0f * (i % 3), 70.0f * (i / 3));
 }

 mTotalShipsLabel = new Scoreboard();
 mTotalShipsLabel->Parent(mShips);
 mTotalShipsLabel->Position(140.0f, 80.0f);
 delete mShips;
 mShips = nullptr;

 for (int i = 0; i < MAX_SHIP_TEXTURES; ++i) {
     delete mShipTextures[i];
     mShipTextures[i] = nullptr;
 }

 delete mTotalShipsLabel;
 mTotalShipsLabel = nullptr;
 for (int i = 0; i < MAX_SHIP_TEXTURES && i < mTotalShips; ++i) {
     mShipTextures[i]->Render();
 }

 if (mTotalShips > MAX_SHIP_TEXTURES) {
     mTotalShipsLabel->Render();
 }
 void SetHighScore(int score);
 void SetPlayerScore(int score);
 void SetShips(int ships);
 void PlaySideBar::SetHighScore(int score) {
     mHighScoreboard->Score(score);
 }

 void PlaySideBar::SetPlayerScore(int score) {
     mPlayerOneScore->Score(score);
 }

 void PlaySideBar::SetShips(int ships) {
     mTotalShips = ships;

     if (ships > MAX_SHIP_TEXTURES) {
         mTotalShipsLabel->Score(ships);
     }
 }
 void StartNewGame();
 void PlayScreen::StartNewGame() {
     mSideBar->SetHighScore(30000);
     mSideBar->SetShips(2);
 }
 mPlayScreen->StartNewGame();















// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
