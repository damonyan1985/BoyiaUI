package com.boyia.app.shell.module

import com.boyia.app.shell.api.IBoyiaHomeLoader

interface IHomeModule: IModule, IBoyiaHomeLoader {
    fun getContext(): IModuleContext?
}