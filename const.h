#ifndef CONST_H
#define CONST_H

#ifdef Q_OS_SYMBIAN
   #define KLangSettingFile "C:\\system\\apps\\AppHider\\lang\\lang.setting"
   #define KLangFile "C:\\system\\apps\\AppHider\\lang\\strings.l"
   #define KConfigFile "C:\\System\\Apps\\AppHider\\config.ini"
   _LIT(KMyServer,"homescreen.exe");
#else
   #define KLangSettingFile "D:\\Symbian\\QtSDK\\workspace\\AppHider\\lang\\lang.setting"
   #define KLangFile "D:\\Symbian\\QtSDK\\workspace\\AppHider\\lang\\strings.l"
   #define KConfigFile "config.ini"
#endif

#endif // CONST_H
