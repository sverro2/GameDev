#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Uncomment the following line to turn on Visual Leak Detector. (Needs to be installed!)


static const std::string BASEPATH = SDL_GetBasePath();
static const std::string RESOURCEPATH = BASEPATH + "Resources\\";
static const std::string SAVEPATH = BASEPATH + "Saves\\";
//static const double OPTIMALRESOLUTIONW = 1600;
//static const double OPTIMALRESOLUTIONH = 900;

static int ScreenWidth = 800;
static int ScreenHeight = 600;
//static double ScreenWidth = 1920;
//static double ScreenHeight = 1080;

static bool fullScreen = false;