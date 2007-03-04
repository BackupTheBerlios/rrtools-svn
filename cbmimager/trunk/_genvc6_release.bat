echo off
IF defined WXWIN (
        bakefile -f msvc6prj -I%WXWIN%\build\bakefiles\wxpresets\presets -DBUILD=release -o netx_usb netx_usb.bkl
) ELSE (
        echo *************
        echo *** ERROR ***
        echo *************
        echo The wxwidgets environment variable 'WXWIN' is not set!
        echo Please set this variable to the root of you wxwidgets installation,
        echo e.g. c:\wxWidgets-2.6.2
)