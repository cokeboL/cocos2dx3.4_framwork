#ifndef _BlurSprite_H_
#define _BlurSprite_H_

#include "cocos2d.h"

USING_NS_CC;

class BlurSprite : public Sprite
{
public:
	~BlurSprite();
	bool initWithTexture(Texture2D* texture, const Rect&  rect);
	void initGLProgram();

	static BlurSprite* create(const char *pszFileName);

#if 0
	void setBlurRadius(float radius);
	void setBlurSampleNum(float num);

protected:
	float _blurRadius;
	float _blurSampleNum;
#endif

};

#endif //_BlurSprite_H_
