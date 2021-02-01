#include "IDCreator.h"

namespace util {
typedef struct BoyiaId {
    BoyiaStr mStr;
    LUint mID;
    BoyiaId* mNext;
} BoyiaId;

typedef struct IdLink {
    BoyiaId* mBegin;
    BoyiaId* mEnd;
} IdLink;

IDCreator::IDCreator()
    : m_idCount(0)
    , m_idLink(kBoyiaNull)
{
}

LUint IDCreator::genIdentify(const String& str)
{
    return genIdentByStr((const LInt8*)str.GetBuffer(), str.GetLength());
}

LUint IDCreator::genIdentByStr(const LInt8* str, LInt len)
{
    BoyiaStr strId;
    strId.mPtr = (LInt8*)str;
    strId.mLen = len;
    return genIdentifier(&strId);
}

LUint IDCreator::genIdentifier(BoyiaStr* str)
{
    if (!m_idLink) {
        m_idLink = new IdLink;
        m_idLink->mBegin = kBoyiaNull;
        m_idLink->mEnd = kBoyiaNull;
    }

    BoyiaId* id = m_idLink->mBegin;
    while (id) {
        if (MStrcmp(str, &id->mStr)) {
            return id->mID;
        }

        id = id->mNext;
    }

    id = new BoyiaId;
    id->mID = m_idLink->mEnd ? m_idLink->mEnd->mID + 1 : m_idCount + 1;
    id->mStr.mPtr = NEW_BUFFER(LInt8, str->mLen);
    id->mStr.mLen = str->mLen;
    LMemcpy(id->mStr.mPtr, str->mPtr, str->mLen);
    id->mNext = kBoyiaNull;

    if (!m_idLink->mBegin) {
        m_idLink->mBegin = id;
    } else {
        m_idLink->mEnd->mNext = id;
    }

    m_idLink->mEnd = id;

    ++m_idCount;
    return id->mID;
}

LVoid IDCreator::getIdentName(LUint id, BoyiaStr* str)
{
    if (!m_idLink) {
        str->mLen = 0;
        str->mPtr = kBoyiaNull;
        return;
    }

    BoyiaId* bid = m_idLink->mBegin;
    while (bid) {
        if (bid->mID == id) {
            str->mLen = bid->mStr.mLen;
            str->mPtr = bid->mStr.mPtr;
            return;
        }

        bid = bid->mNext;
    }
}

OwnerPtr<String> IDCreator::idsToString()
{
    String buffer((LUint8)0, 1024);
    BoyiaId* bid = m_idLink->mBegin;
    while (bid) {
        buffer += String(_CS(bid->mStr.mPtr), LFalse, bid->mStr.mLen);
        buffer += _CS(":");
        LUint8 str[256];
        LInt2Str(bid->mID, str, 10);
        buffer += str;
        if (bid != m_idLink->mEnd) {
            buffer += _CS("\n");
        }

        bid = bid->mNext;
    }

    OwnerPtr<String> ownerString = new String(buffer.GetBuffer(), LFalse, buffer.GetLength());
    buffer.ReleaseBuffer();
    return ownerString;
}

LVoid IDCreator::appendIdentify(const String& str, LUint id)
{
    if (!m_idLink) {
        m_idLink = new IdLink;
        m_idLink->mBegin = kBoyiaNull;
        m_idLink->mEnd = kBoyiaNull;
    }

    BoyiaId* bid = new BoyiaId;
    bid->mID = id;
    bid->mStr.mPtr = NEW_BUFFER(LInt8, str.GetLength());
    bid->mStr.mLen = str.GetLength();
    LMemcpy(bid->mStr.mPtr, str.GetBuffer(), str.GetLength());
    bid->mNext = kBoyiaNull;

    if (!m_idLink->mBegin) {
        m_idLink->mBegin = bid;
    } else {
        m_idLink->mEnd->mNext = bid;
    }

    m_idLink->mEnd = bid;
    m_idCount = id;
}
}
