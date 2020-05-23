#ifndef BoyiaLib_h
#define BoyiaLib_h

#include "BoyiaCore.h"

char* convertMStr2Str(BoyiaStr* str);

LInt getFileContent(LVoid* vm);

LInt addElementToVector(LVoid* vm);

LInt getElementFromVector(LVoid* vm);

LInt getVectorSize(LVoid* vm);

LInt clearVector(LVoid* vm);

LInt logPrint(LVoid* vm);

LInt jsonParseWithCJSON(LVoid* vm);

LInt createJSDocument(LVoid* vm);

LInt appendView(LVoid* vm);

LInt getRootDocument(LVoid* vm);

LInt setDocument(LVoid* vm);

LInt removeDocument(LVoid* vm);

LInt setViewXpos(LVoid* vm);

LInt setViewYpos(LVoid* vm);

LInt drawView(LVoid* vm);

LInt startScale(LVoid* vm);

LInt startOpacity(LVoid* vm);

LInt removeElementWidthIndex(LVoid* vm);

LInt removeElementFromVector(LVoid* vm);

LInt getViewXpos(LVoid* vm);

LInt getViewYpos(LVoid* vm);

LInt getViewWidth(LVoid* vm);

LInt getViewHeight(LVoid* vm);

LInt setViewStyle(LVoid* vm);

LInt loadDataFromNative(LVoid* vm);

LInt callStaticMethod(LVoid* vm);

LInt startTranslate(LVoid* vm);

LInt getHtmlItem(LVoid* vm);

LInt loadImageByUrl(LVoid* vm);

LInt setViewGroupText(LVoid* vm);

LInt setInputViewText(LVoid* vm);

LInt addEventListener(LVoid* vm);

LInt setToNativeView(LVoid* vm);

LInt instanceOfClass(LVoid* vm);

LInt createViewGroup(LVoid* vm);

LInt setImageUrl(LVoid* vm);

LInt viewCommit(LVoid* vm);

#endif // !BoyiaLib_h
