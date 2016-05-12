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

const char *prompt = "hedgehog# ";
int run = 1;
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
