#pragma once
#include "Object.h"
#include "../FrameWork/Utils.h"

class TextObj : public Object
{
protected:
	Text text;

public:
	TextObj();
	virtual ~TextObj();

	Text& GetSfmlText() { return text; }

	virtual void Draw(RenderWindow& window) override;
	


	void SetFont(Font& font);
	void SetText(wstring text);
	void SetPos(const Vector2f& pos);
	void SetColor(Color color);
	FloatRect GetGlobalBounds();
	void SetOrigin(Origins origin);
	const string& GetText() const;
};

