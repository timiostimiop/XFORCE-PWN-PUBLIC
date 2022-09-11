# XFORCE-PWN PUBLIC

Open source XForce 6.9b7 Crack [ Patched , use this as learning ressource :) ]

They be using VirtualProtect to protect several functions - if you just comment it out you'll get a nasty bsod.
Incase you're on a older ( pre 21h2 ) windows versions returning nothing at NtRaiseHardError won't prevent you from a bsod.
You could improve it by dynamically patching VirtualProtect or just hooking it yourself - I'll leave it up to you.

0. Unzip X-Folder.rar to C:\
1. Install Minhook via Nuget
2. Compile in x64 Release
3. Inject XFORCE-PWN PUBLIC.dll
4. Inject xf.dll

Use v140 toolset to compile.

![Alt text](/pics/xxx.png?raw=true "pic1")


Installing Nuget:


![Alt text](/pics/PIC1.png?raw=true "pic12")
![Alt text](/pics/pic2.png?raw=true "pic122")


Crash on inject?
Apply the correct bytes , they will automatically be dumped on first inject into current console.

![Alt text](/pics/bytes.png?raw=true "cbytes")
![Alt text](/pics/shitalloc.png?raw=true "cbytesx")





