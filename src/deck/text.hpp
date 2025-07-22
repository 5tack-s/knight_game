#ifndef eText
#define eText
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

class Text {
    public:
        Text();
        ~Text();
    
    public:
        void start(std::string fontPath, float fontSize, SDL_Renderer* renderer);
        void createText();
        void renderText(SDL_Renderer* renderer, SDL_FRect dstRect);

    public:
        void setText(std::string text);
        void setTextColor(SDL_Color textColor);
        void setFontSize(float fontSize);
    
    public:
        void closeFont();

    public:
        std::string getText();

    private:
        TTF_Font* font;
        std::string fontPath;
        std::string text;
        SDL_Color textColor;
        float fontSize;
        SDL_Texture* textTexture;

    private:
        int status;
        SDL_Renderer* renderer;
};

#endif