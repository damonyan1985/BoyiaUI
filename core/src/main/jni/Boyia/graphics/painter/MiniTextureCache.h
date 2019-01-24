#ifndef MiniTextureCache_h
#define MiniTextureCache_h

#include "BoyiaPtr.h"
#include "KList.h"
#include "HtmlView.h"
#include <GLES3/gl3.h>
//#include <GLES2/gl2ext.h>

namespace yanbo
{
class MiniTexture : public BoyiaRef
{
public:
	MiniTexture();
	LVoid initWithData(LVoid* data, LUint key, LInt width, LInt height);

	virtual ~MiniTexture();

	GLuint texId;
	LUint  texKey;
	LInt width;
	LInt height;
};

class TexturePair : public BoyiaRef
{
public:
	TexturePair();

	HtmlView* item;
	BoyiaPtr<MiniTexture> tex;
};

typedef KList<BoyiaPtr<TexturePair> > TextureMap;
class MiniTextureCache
{
public:
	static MiniTextureCache* getInst();
	LVoid clear();
	MiniTexture* put(const LImage* image);
	MiniTexture* find(LVoid* image);
    MiniTexture* updateTexture(const LImage* image);

private:
    MiniTexture* fetchTexture(HtmlView* item, const LRect& rect, const LImage* image, LUint key);
    MiniTexture* find(HtmlView* item, LUint key);

    TextureMap m_texMap;
    static MiniTextureCache* s_instance;
};
}
#endif
