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

#include "hedge"
#include "shell.h"

const int crashfail = 0;
const char *prompt = "hedgehog% ";
int run = 1;
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
      run = 0;


    char *command = input();
    //HHPrint(command);
    if ((HHStrCmp(command, "test", 4)) == 0) {
      void test();
      test();
    } /*else if ((HHStrCmp(command, "help", 4)) == 0){
      void help();
      help();
    } */else if ((HHStrCmp(command, "sysinfo", 7)) == 0){
      void sysinfo();
      sysinfo();
    } else if ((HHStrCmp(command, "whoami", 6)) == 0) {
      void whoami();
      whoami();
    } else {
      void notFound(command);
      notFound(command);
    }
  }
}

char *input() {
  char buf[2000];
  char inp;
  int i = 0;
  inp = HHGetCharFromKbd();
  while (inp != '\n' && i<1999) {
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
  } else if (faillevel == 1) {
    HHPrint("hsh: command not found: ");
    HHPrint(command);
    HHPrint("\nTry `help' or `sysinfo'.\n");
  } else if (faillevel == -1) {
    HHPrint("E");
  } else {
    HHPrint("hsh: command not found: ");
    HHPrint(command);
    HHPrint("\n");
  }
}
