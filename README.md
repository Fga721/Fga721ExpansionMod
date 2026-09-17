# Fga721ExpansionMod
this is a repo for lib pvz2 by inline hooking, using and64inlinehook as base, you can inject the library to the game and enjoy of features;
this library has the propuse of be a start point for the people who doesnt know to lib in arm64 because all the public libs are arm (32 bits)

## Features
this lib has features for modders, like:
* Integer ID Backport!
* Piano Softcode: You can put new zombies for dance with the piano!
* Mummy Memory Fix Ported To Arm64!
* Softcodes like Arcade, Tomb Raiser, Magician and Powerlily!
* Teleportatomine Fix! (By RenoJson)

## Credits
* Blazey and RenoJson (Teeri): for helping me to learn to lib
* RenoJson (Teeri): Teleportatomine Fix and RtWeakPtr Fix

## Future Plans
* add gis, projectiles and popanimrig support
* recreate more layout of the original game
* other stuff

## How To Inject?
arm64 is different to arm, so you can inject it by this steps:
* compile the library with the architecture of release, arm64 (other architectures will have errors)
* Decompile the apk via apktool or any other thing
* Delete the armeabi-v7a folder (or it will crash)
* In arm64-v8a, you must paste the libFga721.so after compiling it with visual studio
* In apk\smali_classes2\com\popcap\PvZ2\PvZ2GameActivity.smali, after load the pvz2lib (const-string v0, "PVZ2"), after the invoke_static you have to paste this:

      const-string v0, "Fga721"

      .line 57
      invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V

  ## CAUTION:
  the owner of that project, isnt responsable for the improper use of that library, all the responsability for damages, hacking or improper monetization, is for the user who compiles and distributes it, because this library isnt damaging the integrity of the apk user, only is a test for hooking simple functions
