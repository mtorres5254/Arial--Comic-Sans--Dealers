#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFont.h"
#include <string.h>

#include "SDL/include/SDL.h"

// Constructor
ModuleFont::ModuleFont() : Module()
{}

// Destructor
ModuleFont::~ModuleFont()
{}

bool ModuleFont::Start() {

	return true;
}

// Load new texture from file path
int ModuleFont::Load(const char* texture_path, const char* characters)
{
	for (int i = 0; i < MAX_FONTS; i++) {
		if (fonts[i].graphic == nullptr) {

			int width;
			int height;

			if (texture_path == nullptr || characters == nullptr)
			{
				LOG("Could not load font");
			}

			SDL_Texture* tex = App->textures->Load(texture_path);

			if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
			{
				LOG("Could not load font at %s with characters '%s'", texture_path, characters);
			}

			SDL_QueryTexture(tex, NULL, NULL, &width, &height);

			fonts[i].graphic = tex; // graphic: pointer to the texture
			fonts[i].len = strlen(characters); // len: length of the table
			strcpy_s(fonts[i].table, characters);
			fonts[i].char_h = height;
			fonts[i].char_w = width / strlen(characters);

			LOG("Successfully loaded BMP font from %s", texture_path);
			return i;
			break;
		}
		break;
	}
}

void ModuleFont::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleFont::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || App->font->fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &App->font->fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (int i = 0; i < len; i++)
	{
		bool foundCharacter = false;
		int j = 0;
		do
		{
			if (font->table[j] == text[i]) {
				rect.x = j * font->char_w;
				rect.y = 0;
				App->render->Blit(font->graphic, x, y, &rect, false);

				x += font->char_w;
				foundCharacter = true;
			}
			else
				j++;

		} while (!foundCharacter && j < font->len);
	}
}
