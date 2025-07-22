#include "text.hpp"

Text::Text():
font(nullptr),
textTexture(nullptr)
{
    status = TTF_Init();
    if(!status){
        SDL_Log("Failed to start TTF from font: %s", SDL_GetError());
        return;
    }
}

Text::~Text(){
    TTF_Quit();
    if(textTexture) SDL_DestroyTexture(textTexture);
}

void Text::closeFont(){
    TTF_CloseFont(this->font);
}


void Text::start(std::string fontPath, float fontSize, SDL_Renderer* renderer){
    this->fontPath = fontPath;
    this->fontSize=fontSize;
    this->renderer = renderer;

    font = TTF_OpenFont(this->fontPath.c_str(), fontSize);
    if (font == NULL) {
        SDL_Log("Error loading font: %s", SDL_GetError());
        return;
    }
}

void Text::createText(){
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), text.length(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    SDL_SetTextureBlendMode(textTexture, SDL_BLENDMODE_BLEND);
}

void Text::renderText(SDL_Renderer* renderer, SDL_FRect dstRect){

    bool status = SDL_RenderTexture(renderer, textTexture, NULL, &dstRect);

    if(!status){
        SDL_Log("Error rendering text: %s", SDL_GetError());
    }
}

void Text::setText(std::string text){
    this->text = text;
}

void Text::setFontSize(float fontSize){
    this->fontSize = fontSize;
}

void Text::setTextColor(SDL_Color textColor){
    this->textColor = textColor;
}

std::string Text::getText(){
    return text;
}