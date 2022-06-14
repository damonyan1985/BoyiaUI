package com.boyia.app.shell

import android.content.Intent
import android.graphics.Color
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.view.View
import android.widget.FrameLayout
import androidx.activity.compose.setContent
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AppCompatActivity
import androidx.compose.material.Text
import com.boyia.app.common.utils.BoyiaLog
import com.boyia.app.shell.module.BaseFragment
import com.boyia.app.shell.module.IModuleContext
import com.boyia.app.shell.module.ModuleManager
import com.boyia.app.shell.service.BoyiaNotifyService
import com.boyia.app.shell.util.CommonFeatures

// 主页面，用来呈现应用列表信息
class BoyiaHomeActivity: AppCompatActivity(), IModuleContext {
    companion object {
        const val TAG = "BoyiaHomeActivity"
    }
    private var rootView: FrameLayout? = null

//    activity已经创建，并且persistableMode设置persistAcrossReboots才会调用
//    override fun onCreate(savedInstanceState: Bundle?, persistentState: PersistableBundle?) {
//        super.onCreate(savedInstanceState, persistentState)
//    }

//    private val pickLauncher = registerForActivityResult(ActivityResultContracts.GetContent()){ uri: Uri? ->
//        uri?.let { it ->
//            BoyiaLog.d("tag", it.toString())
//        }
//    }
    private val pickLauncher = CommonFeatures.registerPickerImage(this)

    override fun onCreate(bundle: Bundle?) {
        super.onCreate(bundle)
        BoyiaLog.d(TAG, "BoyiaHomeActivity onCreate")
        initHome()
        initNotifyService()
        CommonFeatures.registerPickerImage(this);
    }

    private fun initHome() {
        BoyiaLog.d(TAG, "BoyiaHomeActivity initHome")
        rootView = FrameLayout(this)
        rootView?.id = View.generateViewId()
        rootView?.setBackgroundColor(Color.BLUE)
        rootView?.fitsSystemWindows = true

        setContentView(rootView)

        val ipcModule = ModuleManager.instance().getModule(ModuleManager.IPC)
        ipcModule?.show(this)

        val homeModule = ModuleManager.instance().getModule(ModuleManager.HOME)
        homeModule?.show(this)
    }

    override fun rootId(): Int {
        return rootView?.id!!
    }

    override fun getActivity(): AppCompatActivity {
        return this
    }

    override fun pickImage() {
        pickLauncher.launch(null)
    }

    private fun initNotifyService() {
        val intent = Intent(this, BoyiaNotifyService::class.java)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            startForegroundService(intent)
        } else {
            startService(intent)
        }
    }

    override fun onBackPressed() {
        if (supportFragmentManager.backStackEntryCount == 0) {
            super.onBackPressed()
        } else {
            val list = supportFragmentManager.fragments
            val fragment = list.last() as BaseFragment
            if (fragment.canPop()) {
                fragment.hide()
            }
        }
    }

    override fun onDestroy() {
        ModuleManager.instance().hide()
        super.onDestroy()
    }
}