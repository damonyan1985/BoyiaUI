package com.boyia.app.shell.model

import com.boyia.app.common.json.BoyiaJson
import com.boyia.app.common.utils.BoyiaLog
import com.boyia.app.common.utils.BoyiaShare


class BoyiaLoginInfo {
    companion object {
        const val TAG = "BoyiaLoginInfo"
        const val USER_KEY = "user"
        const val TOKEN_KEY = "token"

        fun instance() = Holder.shared
    }

    private object Holder {
        val shared = BoyiaLoginInfo()
    }

    var user: BoyiaUserInfo? = null
        get() {
            if (field == null) {
                val info = BoyiaShare.getImpl(USER_KEY, null)
                BoyiaLog.d(TAG, "get field = $info")
                field = BoyiaJson.jsonParse(info, BoyiaUserInfo::class.java)
            }

            return field
        }
        set(value) {
            field = value
            if (value == null) {
                BoyiaShare.remove(USER_KEY)
            } else {
                val data = BoyiaJson.toJson(value)
                BoyiaLog.d(TAG, "set field = $data")
                BoyiaShare.putImpl(USER_KEY, BoyiaJson.toJson(value))
            }
        }

    var token: String? = null
        get() {
            if (field == null) {
                field = BoyiaShare.getImpl(TOKEN_KEY, null)
            }

            return field
        }
        set(value) {
            field = value
            if (value == null) {
                BoyiaShare.remove(TOKEN_KEY)
            } else {
                BoyiaShare.putImpl(TOKEN_KEY, value)
            }
        }

    fun logout() {
        BoyiaLoginModel.logout()

        user = null
        token = null
    }

    fun isLogin(): Boolean {
        return token != null
    }
}