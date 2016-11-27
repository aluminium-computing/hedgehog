// Licenced under APL
// Copyright © 2016 Aluminium Computing, Inc.


#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG
#define AIM_KERNEL
#define LICENSE AIM_PUBLIC

#include <hedgehog.h>
#include <shell.h>
#include <gfx.h>

const int crashfail = 0;
const char *prompt = "hedgehog% "; // % = SYSTEM, # = su >/$ = regular user
int faillevel = 1;

void ShellMain() {
  //initShell();
  runShell();

}

void initShell() {
}

void runShell() {
  while (1) {
    HHPrint(prompt);
    char *command = input();
    if ((HHStrCmp(command, "test", 4)) == 0) {
      test();
    } else if ((HHStrCmp(command, "help", 4)) == 0){
      help();
    } else if ((HHStrCmp(command, "sysinfo", 7)) == 0){
      sysinfo();
    } else if ((HHStrCmp(command, "whoami", 6)) == 0) {
      whoami();
    } else if ((HHStrCmp(command, "crash", 5)) == 0) {
      HHCrash("0x17_SHELL");
    } else if ((HHStrCmp(command, "gfx", 3)) == 0) {
      gfx();
    } else {
      notFound(command);
    }
  }
}

char *input() {
  char buf[MAX_COMMAND];
  char inp;
  int i = 0;
  inp = HHGetCharFromKbd();
  while (inp != '\n' && i < MAX_COMMAND) {
    if (inp != NULL) {

      buf[i] = inp;
      i++;
    }
    inp = HHGetCharFromKbd();
  }
  //return HHStrTok(buf, " ");
  //HHPrint("retinput");
  return buf;
}

void test() {
  //if (run != 1) {
    HHPrint("Hello World!\n");
    /*run = 1;
    //HHPrint(prompt);*/
}

void sysinfo() {
  HHPrint("Hedgehog Version......");
  HHPrint(VERSION);
  HHPrint("\n");
  HHPrint("`hsh' Version:........");
  HHPrint(SVERSION);
  HHPrint("\n");
  #ifdef DEBUG
    HHPrint("Debug Build:..........YES\n");
  #else
    HHPrint("Debug Build:..........NO\n");
  #endif // DEBUG
  #ifdef IDSTR
    HHPrint("Aluminium Support ID..");
    HHPrint(IDSTR);
    HHPrint("\n");
  #elif DEBUG
    HHPrint("Aluminium Support ID..DEBUG\n");
  #else
    HHPrint("Aluminium Support ID..00SRC\n")
  #endif // IDSTR, DEBUG
  HHPrint("Graphics Mode.........VGA Text\n");
  HHPrint("Screen Resolution:....80x24\n");
  HHPrint("Storage:..............0B/0B saved, 0B/0B RAM, 8KiB/8KiB ROM\n");
  HHPrint("              If you require technical support, please AimConnect 124.\n");
}

void whoami() {
  HHPrint("SYSTEM\n");
}

void notFound(char *command) {
  if (faillevel == 2) {
    HHCrash(command);
  } else if (faillevel == -1) {
    HHPrint("E");
  } else {
    HHPrint("hsh: command not found: ");
    HHPrint(command);
    HHPrint("\n");
  }
}

void help() {
  HHPrint("  `crash': Crashes the system with error code 0x17_SHELL.\n");
  HHPrint("   `test': Prints a test message. Has no purpose outside of testing.\n");
  HHPrint("`sysinfo': Prints system information.\n");
  HHPrint(" `whoami': Prints current user.\n");
  HHPrint("    `gfx': Tests Hedgehog Graphical System(TM).\n");
}

void gfx() {
  GXInit();
  GXSetColours('0','2');
  GXAddHLine(15, 30, 10);
  GXAddVLine(1,1,10);
  GXAddText(20,40, "Hedgehog!");
  GXAddPixel(15,10);
  GXAddPixel(14,10);
  GXAddPixel(13,10);
  GXAddPixel(12,10);
  GXAddPixel(11,10);
  GXAddPixel(10,10);
  GXAddPixel(9,10);
  GXAddPixel(8,10);
  GXAddPixel(7,10);
  GXAddPixel(11,11);
  GXAddPixel(11,12);
  GXAddPixel(11,13);
  GXAddPixel(11,14);
  GXAddPixel(11,15);
  GXAddPixel(11,16);
  GXAddPixel(11,17);
  GXAddPixel(11,18);
  GXAddPixel(15,18);
  GXAddPixel(14,18);
  GXAddPixel(13,18);
  GXAddPixel(12,18);
  GXAddPixel(11,18);
  GXAddPixel(10,18);
  GXAddPixel(9,18);
  GXAddPixel(8,18);
  GXAddPixel(7,18);


  GXUpdate();
  for (;;) {
    //HHPrint("12347237423942334235823525");
  }
}
