#include "BlurSprite.h"


BlurSprite::~BlurSprite()
{
}

BlurSprite* BlurSprite::create(const char *pszFileName)
{
	BlurSprite* pRet = new (std::nothrow) BlurSprite();
	if (pRet && pRet->initWithFile(pszFileName))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool BlurSprite::initWithTexture(Texture2D* texture, const Rect& rect)
{
	//_blurRadius = 0;
	if (Sprite::initWithTexture(texture, rect))
	{
#if CC_ENABLE_CACHE_TEXTURE_DATA
		auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
			setGLProgram(nullptr);
			initGLProgram();
		});

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif

		initGLProgram();

		return true;
	}

	return false;
}

void BlurSprite::initGLProgram()
{
	GLchar * fragSource = (GLchar*)String::createWithContentsOfFile(
		FileUtils::getInstance()->fullPathForFilename("Shaders/example_Blur.fsh").c_str())->getCString();
	auto program = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource);

	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(program);
	setGLProgramState(glProgramState);

	auto size = getTexture()->getContentSizeInPixels();
	getGLProgramState()->setUniformVec2("resolution", size);
	getGLProgramState()->setUniformFloat("blurRadius", 8.00f);
	getGLProgramState()->setUniformFloat("sampleNum", 7.0f);
}

#if 0
void BlurSprite::setBlurRadius(float radius)
{
	_blurRadius = radius;
	getGLProgramState()->setUniformFloat("blurRadius", _blurRadius);
}

void BlurSprite::setBlurSampleNum(float num)
{
	_blurSampleNum = num;
	getGLProgramState()->setUniformFloat("sampleNum", _blurSampleNum);
}

#endif
