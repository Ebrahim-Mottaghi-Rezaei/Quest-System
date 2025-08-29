cls
echo off

set "PROJECT_PATH=C:\Users\emott\OneDrive\Documents\Unreal Projects\QuestProject"

:: Navigate to project folder
cd /d "%PROJECT_PATH%"

:: Delete project-level files and folders
echo Deleting project-level folders and files...
del /q "%PROJECT_PATH%\*.sln"
del /q "%PROJECT_PATH%\*.vsconfig"
rmdir /s /q "%PROJECT_PATH%\.idea"
rmdir /s /q "%PROJECT_PATH%\.github"
rmdir /s /q "%PROJECT_PATH%\.vs"
rmdir /s /q "%PROJECT_PATH%\Binaries"
rmdir /s /q "%PROJECT_PATH%\Build"
rmdir /s /q "%PROJECT_PATH%\Builds"
rmdir /s /q "%PROJECT_PATH%\Intermediate"
rmdir /s /q "%PROJECT_PATH%\DerivedDataCache"
rmdir /s /q "%PROJECT_PATH%\Saved"

:: Delete Intermediate and Binaries from all plugins (recursively)
::echo Deleting plugin Intermediate and Binaries folders...

for /d /r "%PROJECT_PATH%\Plugins" %%d in (*) do (
    if /i "%%~nxd"=="Binaries" (
        echo Deleting %%d
        rmdir /s /q "%%d"
    )
    if /i "%%~nxd"=="Intermediate" (
        echo Deleting %%d
        rmdir /s /q "%%d"
    )
)

exit