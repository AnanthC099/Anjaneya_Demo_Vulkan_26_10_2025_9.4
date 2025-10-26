cls

del *.spv *.bak *.txt *.res *.obj *.exe

glslangValidator.exe -V -H -o shader_Scene0.vert.spv shader_Scene0.vert

glslangValidator.exe -V -H -o shader_Scene0.frag.spv shader_Scene0.frag

glslangValidator.exe -V -H -o Shader_Scene1.vert.spv Shader_Scene1.vert

glslangValidator.exe -V -H -o Shader_Scene1.frag.spv Shader_Scene1.frag

glslangValidator.exe -V -H -o Shader_Scene2.vert.spv Shader_Scene2.vert

glslangValidator.exe -V -H -o Shader_Scene2.frag.spv Shader_Scene2.frag

cl.exe /c /EHsc /I C:\VulkanSDK\Anjaneya\Include SceneSwitcher.cpp 

rc.exe Scene0.rc

link.exe  SceneSwitcher.obj Scene0.res /LIBPATH:C:\VulkanSDK\Anjaneya\Lib /SUBSYSTEM:WINDOWS

SceneSwitcher.exe


