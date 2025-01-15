#include "graphics.h"
#include <math.h>
#include <iostream>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include "Map.h"
#include "Enemies.h"
#include "Colissions.h"
#include "Colectibles.h"
#include "Loader.h"
#include "miniaudio.h"

using namespace std;

ma_engine engine;
ma_sound JumpEffect, CoinEffect, ColideEffect, GombaDeadEffect, BackGroundMusic, DeathEffect, StageClear, StarTheme, plinc, incplace, mapediRO, mapediEN, blselecRO,
blselecEN, OneUpEffect, PauseEffect, FireBallEffect, PowerUpAppearEffect, PowerUpEffect, DmgEffect, MenuMusic, MapEditorMusic, FlagEffect, CreditMusic;


void SoundInitialisation() {
    // Initialize MiniAudio engine
    if (ma_engine_init(NULL, &engine) != MA_SUCCESS) {
        printf("Failed to initialize MiniAudio engine.\n");
        exit(0);
    }

    // Initialize sound effects
    if (ma_sound_init_from_file(&engine, "jump_small.wav", 0, NULL, NULL, &JumpEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 1.\n");
        ma_sound_uninit(&JumpEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "coin.wav", 0, NULL, NULL, &CoinEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&CoinEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "bump.wav", 0, NULL, NULL, &ColideEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&ColideEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "stomp.wav", 0, NULL, NULL, &GombaDeadEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&GombaDeadEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "LevelBackgroundMusic.wav", 0, NULL, NULL, &BackGroundMusic) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&BackGroundMusic);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "gameover.wav", 0, NULL, NULL, &DeathEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&DeathEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "stage_clear.wav", 0, NULL, NULL, &StageClear) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&StageClear);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "StarTheme.wav", 0, NULL, NULL, &StarTheme) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&StageClear);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "plasareincorecta.wav", 0, NULL, NULL, &plinc) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&plinc);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "incorecplace.wav", 0, NULL, NULL, &incplace) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&incplace);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "mapeditRO.wav", 0, NULL, NULL, &mapediRO) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&mapediRO);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "mapeditEN.wav", 0, NULL, NULL, &mapediEN) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&mapediEN);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "blselecRO.wav", 0, NULL, NULL, &blselecRO) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&blselecRO);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "blselecEN.wav", 0, NULL, NULL, &blselecEN) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&blselecEN);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "one_up.wav", 0, NULL, NULL, &OneUpEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&OneUpEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "pause.wav", 0, NULL, NULL, &PauseEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&PauseEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "mario_fireball.wav", 0, NULL, NULL, &FireBallEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&FireBallEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "mario_powerup_appear.wav", 0, NULL, NULL, &PowerUpAppearEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&PowerUpAppearEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "mario_powerup.wav", 0, NULL, NULL, &PowerUpEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&PowerUpEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "mario_dmg.wav", 0, NULL, NULL, &DmgEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&DmgEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "MenuMusic.wav", 0, NULL, NULL, &MenuMusic) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&MenuMusic);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "MapEditorMusic.wav", 0, NULL, NULL, &MapEditorMusic) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&MapEditorMusic);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "flagpole.wav", 0, NULL, NULL, &FlagEffect) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&FlagEffect);
        ma_engine_uninit(&engine);
        exit(0);
    }
    if (ma_sound_init_from_file(&engine, "CreditMusic.wav", 0, NULL, NULL, &CreditMusic) != MA_SUCCESS) {
        printf("Failed to load sound effect 2.\n");
        ma_sound_uninit(&CreditMusic);
        ma_engine_uninit(&engine);
        exit(0);
    }
}

void SoundUnInit() {
    ma_sound_uninit(&JumpEffect);
    ma_sound_uninit(&CoinEffect);
    ma_sound_uninit(&ColideEffect);
    ma_sound_uninit(&GombaDeadEffect);
    ma_sound_uninit(&BackGroundMusic);
    ma_sound_uninit(&DeathEffect);
    ma_sound_uninit(&StageClear);
    ma_sound_uninit(&StageClear);
    ma_engine_uninit(&engine);
}