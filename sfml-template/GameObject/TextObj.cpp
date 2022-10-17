#include "TextObj.h"
#include "../Framework/ResourceMgr.h"


TextObj::TextObj()
{
	text.setFont(*RESOURCE_MGR->GetFont("fonts/NotoSansKR-Bold.otf"));
}

TextObj::~TextObj()
{
}

void TextObj::Draw(RenderWindow& window)
{
	window.draw(text);
}

void TextObj::SetFont(Font& font)
{
	text.setFont(font);
}

void TextObj::SetText(wstring str)
{

	text.setString(str);
}

void TextObj::SetPos(const Vector2f& pos)
{
	text.setPosition(pos);
}

void TextObj::SetColor(Color color)
{
	text.setFillColor(color);
}

FloatRect TextObj::GetGlobalBounds()
{
	return text.getGlobalBounds();
}

void TextObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(text, origin);
}

const string& TextObj::GetText() const
{
	return text.getString();
}

