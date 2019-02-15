#include "UIViewThread.h"
#include "UIView.h"
#include "NetworkBase.h"
#include "LGdi.h"

namespace yanbo
{
LVoid BoyiaEvent::execute()
{
	run();
	delete this;
}

UIViewThread* UIViewThread::s_instance = NULL;

UIViewThread* UIViewThread::instance()
{
    if (!s_instance)
    {
    	s_instance = new UIViewThread();
    	s_instance->start();
    }

    return s_instance;
}

UIViewThread::UIViewThread()
{
}

LVoid UIViewThread::handleMessage(MiniMessage* msg)
{
	switch (msg->type)
	{
	case UIView_INIT:
		{
			String url(_CS(msg->obj), LTrue,  msg->arg0);
			UIView::getInstance()->loadPage(url);
		}
		break;
	case UIView_DRAW:
		{
			HtmlView* view = (HtmlView*) msg->arg0;
			UIView::getInstance()->getLoader()->repaint(view);
		}
		break;
	case UIView_QUIT:
		{
			UIView::getInstance()->destroy();
			m_continue = LFalse;
		}
		break;
	case UIView_KEYEVENT:
		{
			LKeyEvent* evt = (LKeyEvent*)msg->obj;
			UIView::getInstance()->handleKeyEvent(*evt);
			delete evt;
		}
		break;
	case UIView_LOAD_FINISHED:
		{
			KFORMATLOG("uithread threadid=%d", getId());
			//String data((LUint8*)msg->obj, LTrue, msg->arg0);
			NetworkClient* client = (NetworkClient*)msg->arg1;
			if (client)
			{
				client->onLoadFinished();
			}
		}
		break;
	case UIView_LOAD_ERROR:
		{
			yanbo::NetworkClient* client = (yanbo::NetworkClient*)msg->arg1;
			if (client)
			{
				client->onLoadError(msg->arg0);
			}
		}
		break;
	case UIView_IMAGE_LOADED:
		{
			if (!msg->arg0) return;
			LImage* image = (LImage*) msg->arg0;
			image->setLoaded(LTrue);
		}
		break;
	case UIView_DATA_RECV:
	    {
            if (!msg->obj || !msg->arg0) return;
            NetworkClient* client = (NetworkClient*)msg->arg1;
            client->onDataReceived((LByte*)msg->obj, msg->arg0);
	    }
	    break;
	case UIView_SEND_EVENT:
	    {
            if (!msg->obj) return;
            static_cast<BoyiaEvent*>(msg->obj)->execute();
	    }
	    break; 
	}
}

LVoid UIViewThread::destroy()
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_QUIT;

	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::load(const String& url)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_INIT;
	msg->obj = url.GetBuffer();
	msg->arg0 = url.GetLength();

	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::loadFinished(LIntPtr callback)
{
	MiniMessage* msg = m_queue->obtain();
    msg->type = UIView_LOAD_FINISHED;
	msg->arg1 = callback;
	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::loadError(LIntPtr callback, LInt error)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_LOAD_ERROR;
    msg->arg0 = error;
	msg->arg1 = callback;

	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::imageLoaded(LIntPtr item)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_IMAGE_LOADED;
    msg->arg0 = item;

	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::handleKeyEvent(LKeyEvent* evt)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_KEYEVENT;
    msg->obj = evt;

	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::draw(LIntPtr item)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_DRAW;
	msg->arg0 = item;
	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::dataReceived(LByte* bytes, LInt len, LIntPtr callback)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_DATA_RECV;
	msg->obj = bytes;
	msg->arg0 = len;
	msg->arg1 = callback;
	m_queue->push(msg);
	notify();
}

LVoid UIViewThread::sendEvent(BoyiaEvent* event)
{
	MiniMessage* msg = m_queue->obtain();
	msg->type = UIView_SEND_EVENT;
	msg->obj = event;
	m_queue->push(msg);
	notify();
}
}
