package com.boyia.app.shell

import android.app.Activity
import android.graphics.Color
import android.net.Uri
import android.os.Bundle
import android.os.Environment
import android.view.View
import androidx.appcompat.app.AppCompatActivity
import androidx.coordinatorlayout.widget.CoordinatorLayout
import com.boyia.app.common.utils.BoyiaLog
import com.boyia.app.common.utils.BoyiaUtils
import com.boyia.app.common.utils.ProcessUtil
import com.boyia.app.loader.mue.TestObservable
import com.boyia.app.shell.module.IModuleContext

/**
 * shell程序共用activity基类
 */
open class BoyiaShellActivity: AppCompatActivity(), IModuleContext {
    companion object {
        const val TAG = ""
    }
    protected var rootView: CoordinatorLayout? = null

    override fun onCreate(bundle: Bundle?) {
        super.onCreate(bundle)
        rootView = CoordinatorLayout(this)
        rootView?.id = View.generateViewId()
        rootView?.setBackgroundColor(Color.WHITE)
        rootView?.fitsSystemWindows = false
        rootView?.clipToPadding = false

        setContentView(rootView)

        TestObservable.test()
    }

    override fun rootId(): Int {
        return rootView?.id!!
    }

    override fun getActivity(): AppCompatActivity {
        return this
    }
}